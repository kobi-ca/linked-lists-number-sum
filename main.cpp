#include <forward_list>
#include <list>
#include "fmt/format.h"

// TODO:
//  carry might create a longer output list for example 99 11 will generate output of size 3
//  the input lists might be in a different lengths

namespace {

    struct zip final {

        struct zip_iterator_end final {
            std::forward_list<unsigned int>::const_iterator l1_iter_;
            std::forward_list<unsigned int>::const_iterator l2_iter_;
            zip_iterator_end(const std::forward_list<unsigned int>::const_iterator l1,
                             const std::forward_list<unsigned int>::const_iterator l2) :
                    l1_iter_{l1}, l2_iter_{l2} {}
        };

        struct zip_iterator_begin final {
            std::forward_list<unsigned int>::const_iterator l1_iter_;
            std::forward_list<unsigned int>::const_iterator l2_iter_;
            const std::forward_list<unsigned int> &l1_;
            const std::forward_list<unsigned int> &l2_;

            zip_iterator_begin(const std::forward_list<unsigned int> &l1,
                               const std::forward_list<unsigned int> &l2) :
                    l1_iter_(l1.cbegin()), l2_iter_(l2.cbegin()),
                    l1_{l1}, l2_{l2} {}

            void operator++() noexcept {
                if (l1_iter_ != std::cend(l1_)) {
                    ++l1_iter_;
                }
                if (l2_iter_ != std::cend(l2_)) {
                    ++l2_iter_;
                }
            }

            [[nodiscard]]
            auto operator*() const noexcept {
                unsigned int l1{}, l2{};
                if(l1_iter_ != std::cend(l1_)) {
                    l1 = *l1_iter_;
                }
                if(l2_iter_ != std::cend(l2_)) {
                    l2 = *l2_iter_;
                }
                return std::make_tuple(l1, l2);
            }

            [[nodiscard]]
            auto operator!=(const zip_iterator_end &zi) const noexcept {
                return zi.l1_iter_ != l1_iter_ || zi.l2_iter_ != l2_iter_;
            }
        };

        const std::forward_list<unsigned int>& l1_;
        const std::forward_list<unsigned int>& l2_;
        zip(const std::forward_list<unsigned int>& l1,
            const std::forward_list<unsigned int>& l2) : l1_{l1}, l2_{l2} {}

        [[nodiscard]]
        auto begin() const noexcept {
            return zip_iterator_begin(l1_, l2_);
        }
        [[nodiscard]]
        auto end() const noexcept {
            return zip_iterator_end(l1_.cend(), l2_.cend());
        }

    };

    [[nodiscard]]
    std::list<unsigned int> compute(const std::forward_list<unsigned int>& l1,
                                    const std::forward_list<unsigned int>& l2) {
        std::list<unsigned int> out;
        auto carry = 0ULL;
        for (const auto[digit1, digit2] : zip(l1, l2)) {
            const auto sum = digit1 + digit2 + carry;
            if (sum > 9) {
                carry = 1;
            } else {
                carry = 0;
            }
            out.push_back(sum % 10);
        }
        if(carry) {
            out.push_back(carry);
        }
        return out;
    }

    void print(const std::list<unsigned int>& l) {
        for (const auto v: l) {
            fmt::print("{}\n", v);
        }
        fmt::print("\n");
    }

}

int main() {
    {
        // 1234, 2001 --> 3235
        std::forward_list<unsigned int> l1{4, 3, 2, 1}, l2{1, 0, 0, 2};
        const auto out = compute(l1, l2);
        print(out);
    }

    {
        // 1234, 8086 --> 9320
        std::forward_list<unsigned int> l1{4, 3, 2, 1}, l2{6, 8, 0, 8};
        const auto out = compute(l1, l2);
        print(out);
    }

    {
        // 1234, 9086 --> 10320
        std::forward_list<unsigned int> l1{4, 3, 2, 1}, l2{6, 8, 0, 9};
        const auto out = compute(l1, l2);
        print(out);
    }

    {
        // 99, 1 --> 100
        std::forward_list<unsigned int> l1{9, 9}, l2{1};
        const auto out = compute(l1, l2);
        print(out);
    }

    return 0;
}
