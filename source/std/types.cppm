module;
// language support headers
#include <cstdint>
#include <initializer_list>

export module std.types;

/* --- basic integral types --- */
export {
    // data model is selected automatically
    using std::uint8_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::uint64_t;
    using std::int8_t;
    using std::int16_t;
    using std::int32_t;
    using std::int64_t;
    using float32_t = _Float32;
    using float64_t = _Float64;
};


/* --- additional integral types --- */
export {
    using size_t = decltype(sizeof(nullptr));
    using ptrdiff_t = decltype((int *) nullptr - (int *) nullptr);
    using nullptr_t = decltype(nullptr);
};


/* --- type traits --- */
export {
    template <class T>
    T declval();

    /* --- boolean types --- */
    struct false_type {
        static constexpr bool value = false;
    };

    struct true_type {
        static constexpr bool value = true;
    };

    template <class From, class To>
    concept convertible_to = requires (From f) {
        To(f);
    };

    template <class T>
    concept boolean_testable = convertible_to<T, bool>;

    /* --- make_signed --- */
    template <class T> struct make_signed;
    template <> struct make_signed<  signed short    > { using type = short    ; };
    template <> struct make_signed<unsigned short    > { using type = short    ; };
    template <> struct make_signed<  signed int      > { using type = int      ; };
    template <> struct make_signed<unsigned int      > { using type = int      ; };
    template <> struct make_signed<  signed long     > { using type = long     ; };
    template <> struct make_signed<unsigned long     > { using type = long     ; };
    template <> struct make_signed<  signed long long> { using type = long long; };
    template <> struct make_signed<unsigned long long> { using type = long long; };
    template <class T>
        using make_signed_t = typename make_signed<T>::type; 
    /* --- */

    /* --- is_same --- */
    template <class A, class B>
    struct is_same : false_type {};

    template <class T>
    struct is_same<T, T> : true_type {};

    template <class A, class B>
    inline constexpr bool is_same_v = is_same<A, B>::value;
    /* --- */

    /* --- is_pointer --- */
    template<class T>
    struct is_pointer : false_type {};

    template<class T>
    struct is_pointer<T *> : true_type {};

    template<class T>
    struct is_pointer<T * const> : true_type {};

    template<class T>
    struct is_pointer<T * volatile> : true_type {};

    template<class T>
    struct is_pointer<T * const volatile> : true_type {};

    template<class T>
    inline constexpr bool is_pointer_v = is_pointer<T>::value;

    /* --- underlying_type --- */
    template <class T>
    struct underlying_type {
        using type = __underlying_type(T);
    };

    template <class T>
    using underlying_type_t = underlying_type<T>::type;

    template <class Enum>
    constexpr underlying_type_t<Enum> to_underlying(Enum e) {
        return static_cast<underlying_type_t<Enum>>(e);
    }

    /* --- remove_* --- */
    template<class T> struct remove_cv { using type = T; };
    template<class T> struct remove_cv<const T> { using type = T; };
    template<class T> struct remove_cv<volatile T> { using type = T; };
    template<class T> struct remove_cv<const volatile T> { using type = T; };

    template<class T>
    using remove_cv_t = typename remove_cv<T>::type;

    template<class T> struct remove_pointer { using type = T; };
    template<class T> struct remove_pointer<T*> { using type = T; };
    template<class T> struct remove_pointer<T* const> { using type = T; };
    template<class T> struct remove_pointer<T* volatile> { using type = T; };
    template<class T> struct remove_pointer<T* const volatile> { using type = T; };

    template<class T>
    using remove_pointer_t = typename remove_pointer<T>::type;
};

/* --- basic containers --- */
export {
    /* --- span --- */
    template <typename T>
    using element_t = remove_cv_t<
        remove_pointer_t<decltype(data(declval<T &>()))>
    >;

    template <class T>
    concept const_span = requires(T x) {
        { data(x) } -> convertible_to<const element_t<T> *>;
        { size(x) } -> convertible_to<size_t>;
    };

    template <class T>
    concept span = requires(T x) {
        { data(x) } -> convertible_to<element_t<T> *>;
        { size(x) } -> convertible_to<size_t>;
    };

    template <class T>
    const element_t<T> * begin(T &x) requires const_span<T> {
        return data(x);
    }

    template <class T>
    const element_t<T> * end(T &x) requires const_span<T> {
        return data(x) + size(x);
    } 

    /* --- sequence --- */
    template <class T>
    concept const_sequence = const_span<T> && requires(T x, size_t i) {
        { x[i] }     -> convertible_to<const element_t<T> &>;
    };

    template <class T>
    concept sequence = span<T> && requires(T x, size_t i, element_t<T> e) {
        { x[i] }     -> convertible_to<element_t<T> &>;
        x[i] = e;
    };
};

export namespace std {
    using std::initializer_list;
};
