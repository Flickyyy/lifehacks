template <typename Ty>
class Vec {
public:
    Vec () = default;
    Vec(const Vec& other) {
        *this = other;
    }
    Vec(std::initializer_list<Ty> init_list) {
        check_capacity(init_list.size());
        _size = init_list.size();
        for (int i = 0; i < init_list.size(); ++i) {
            _data[i] = *std::next(init_list.begin(), i);
        }
    }
    explicit Vec(size_t n, Ty val = Ty{}) {
        assign(n, val);
    }
    void assign(size_t n, Ty val = Ty{}) {
        check_capacity(n);
        _size = n;
        for (size_t i = 0; i < n; ++i) {
            _data[i] = val;
        }
    }
    long long size() const {
        return _size;
    }
    void push_back(const Ty& val) {
        check_capacity(_size + 1);
        _data[_size++] = val;
    }
    Vec& operator=(const Vec& other) {
        check_capacity(other._size);
        _size = other._size;
        for (size_t i = 0; i < other._size; ++i) {
            _data[i] = other[i];
        }
        return *this;
    }
    Vec operator[](pii range) {
        Vec sub(range.second - range.first);
        for (size_t i = range.first; i < range.second; ++i) {
            sub[i - range.first] = _data[i];
        }
        return sub;
    }
    Ty& operator[](long long ind) {
        if (ind >= _size || -ind > (ll)_size) {
            throw std::range_error(
                    std::to_string(ind) + " out of range in vector with size " + std::to_string(_size)
            );
        }
        if (ind < 0) {
            return _data[_size + ind];
        } else {
            return _data[ind];
        }
    }
    const Ty& operator[](long long ind) const {
        if (ind >= _size || -ind > _size) {
            throw std::range_error(
                    std::to_string(ind) + " out of range in vector with size " + std::to_string(_size)
            );
        }
        if (ind < 0) {
            return _data[_size + ind];
        } else {
            return _data[ind];
        }
    }
    bool operator==(const Vec<Ty>& other) {
        if (other._size != _size) return false;
        for (size_t i = 0; i < _size; ++i) {
            if (other[i] != _data[i]) return false;
        }
        return true;
    }
    Vec operator+ (const Vec<Ty>& other) {
        Vec res(_size + other._size);
        for (size_t i = 0; i < _size; ++i) {
            res[i] = _data[i];
        }
        for (size_t i = 0; i < other._size; ++i) {
            res[i + _size] = other[i];
        }
        return res;
    }
    friend std::ostream& operator<<(std::ostream& out, const Vec& arr) {
        for (const auto& e : arr) out << ' ' << e;
        out << '\n';
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Vec& arr) {
        for (auto& e : arr) in >> e;
        return in;
    }

    Ty* begin() const {
        return _data;
    }
    Ty* end() const {
        return _data + _size;
    }

private:
    const long long small_buff_size = 32;
    void check_capacity(size_t need) {
        if (need > _cap) {
            size_t new_cap  = 2 * need;
            Ty* new_data = new Ty[new_cap];
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = _data[i];
            }
            delete[] _data;
            _data = new_data;
            _cap = new_cap;
        }
    }

    Ty* _data = new Ty[small_buff_size];
    long long _cap{small_buff_size}, _size{0};
};

template <typename Ty>
Ty reversed(Ty cont) {
    std::reverse(std::begin(cont), std::end(cont));
    return cont;
}
