export module std.types;

/* --- basic integral types --- */
export {
    // LP64 data model
    using uint8_t  = unsigned char;
    using uint16_t = unsigned short;
    using uint32_t = unsigned int;
    using uint64_t = unsigned long;
    using int8_t   = signed char;
    using int16_t  = signed short;
    using int32_t  = signed int;
    using int64_t  = signed long;
    using float32_t = float;
    using float64_t = double;
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
};

/* --- additional integral types --- */
export {
    using size_t = decltype(sizeof(nullptr));
    using ptrdiff_t = decltype((int *) nullptr - (int *) nullptr);
    using nullptr_t = decltype(nullptr);
};

