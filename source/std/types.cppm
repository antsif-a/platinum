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

/* --- POSIX.1 --- */
export {
    using dev_t      = unsigned long int;
    using uid_t      = unsigned int;
    using gid_t      = unsigned int;
    using ino_t      = unsigned long;
    using ino64_t    = unsigned long int;
    using mode_t     = unsigned int;
    using nlink_t    = unsigned long;
    using off_t      = signed   long;
    using off64_t    = signed   long int;
    using pid_t      = signed   int;
    using blkcnt_t   = signed   long;
    using blkcnt64_t = signed   long int;
    using time_t     = signed   long;
    using blksize_t  = signed   long;
    using ssize_t    = signed   long int;
};

/* --- type traits --- */
export {
    template <class T>
    T declval();

    template <class From, class To>
    concept convertible_to = requires {
        static_cast<To>(declval<From>());
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
    struct is_same {
        static constexpr bool value = false;
    };

    template <class T>
    struct is_same<T, T> {
        static constexpr bool value = true;
    };

    template <class A, class B>
    inline constexpr bool is_same_v = is_same<A, B>::value;
    /* --- */
};

/* --- additional integral types --- */
export {
    using size_t = decltype(sizeof(nullptr));
    using ptrdiff_t = decltype((int *) nullptr - (int *) nullptr);
    using nullptr_t = decltype(nullptr);
};

