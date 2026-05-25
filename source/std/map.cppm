export module std.map;

import std.types;
import std.view;
import std.result;
import std.array;
import std.algorithm;

export template <typename T>
using map_key_t = remove_cv_t<
    remove_pointer_t<decltype(keys(declval<T &>()))>
>;

export template <typename T>
using map_value_t = remove_cv_t<
    remove_pointer_t<decltype(values(declval<T &>()))>
>;

export template <class T>
concept map = requires(T x, map_key_t<T> k, map_value_t<T> v) {
    { size(x) }   -> convertible_to<size_t>;
    { x[k] }      -> convertible_to<map_value_t<T> &>;
    x[k] = v;
};

export template <class T>
concept const_map = requires(T x, map_key_t<T> k, map_value_t<T> v) {
    { size(x) }   -> convertible_to<size_t>;
    { x[k] }      -> convertible_to<const map_value_t<T> &>;
};

export class hash_map;
export class tree_map;

export {
    template <class K, class V>
    class flat_map {
    public:
        struct entry {
            K key;
            V value;
        };

        enum struct error {
            not_found
        };

        flat_map(size_t capacity):
            entries(capacity) {}

        size_t size() {
            return ::size(entries);
        }

        size_t capacity() {
            return entries.capacity();
        }

        entry * data() {
            return ::data(entries);
        }

        result<const V *, error> get(const K &key) const {
            auto index = find_if(entries, [&key] (const entry &p) { return p.key == key; });
            if (!index)
                return error::not_found;
            return &entries[index.value].value;
        }

        void put(const K &key, const V &value) {
            result index = find_if(entries, [&key] (const entry &p) { return p.key == key; });
            if (!index) {
                entries.push_back(entry(key, value));
            } else {
                entries[index.value].value = value;
            }
        }

        operator view<entry>() {
            return {data(entries), size(entries)};
        }

        operator const_view<entry>() {
            return {data(entries), size(entries)};
        }
    private:
        dynamic_array<entry> entries;
    };

    template <class K, class V>
    size_t size(flat_map<K, V> &m) {
        return m.size();
    }

    template <class K, class V>
    flat_map<K, V>::entry * data(flat_map<K, V> &m) {
        return m.data();
    }
};

