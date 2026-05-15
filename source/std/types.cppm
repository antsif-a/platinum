module;
// language support freestanding headers
#include <cstdint>
#include <initializer_list>
#include <concepts>

export module std.types;

/* --- basic integral types --- */
export {
    // data model is derived automatically
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
/* we could define these types ourselves but standard library does it better;
 * they does not require any linking and are part of language itself */
export {
    using std::declval;

    using std::false_type;
    using std::true_type;

    using std::convertible_to;

    template <class T>
    concept boolean_testable = convertible_to<T, bool>;

    using std::make_signed;
    using std::make_signed_t;

    using std::is_same;
    using std::is_same_v;

    using std::is_pointer;
    using std::is_pointer_v;

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

    using std::remove_cv;
    using std::remove_cv_t;
    using std::remove_pointer;
    using std::remove_pointer_t;
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
