#include <forward_list>
#include <list>
#include "fmt/format.h"

// TODO:
//  carry might create a longer output list for example 99 11 will generate output of size 3
//  the input lists might be in a different lengths

namespace {

    struct zip final {

        struct zip_iterator {
            std::forward_list<unsigned int>::const_iterator l1_;
            std::forward_list<unsigned int>::const_iterator l2_;
            zip_iterator(const std::forward_list<unsigned int>::const_iterator l1,
                         const std::forward_list<unsigned int>::const_iterator l2) : l1_{l1}, l2_{l2} {}

            void operator++() noexcept {
                ++l1_; ++l2_;
            }

            [[nodiscard]]
            auto operator*() const noexcept {
                return std::make_tuple(*l1_, *l2_);
            }

            [[nodiscard]]
            auto operator!=(const zip_iterator& zi) const noexcept {
                return std::tie(l1_, l2_) != std::tie(zi.l1_, zi.l2_);
            }

        };

        const std::forward_list<unsigned int>& l1_;
        const std::forward_list<unsigned int>& l2_;
        zip(const std::forward_list<unsigned int>& l1,
            const std::forward_list<unsigned int>& l2) : l1_{l1}, l2_{l2} {}

        [[nodiscard]]
        auto begin() const noexcept {
            return zip_iterator(l1_.cbegin(), l2_.cbegin());
        }
        [[nodiscard]]
        auto end() const noexcept {
            return zip_iterator(l1_.cend(), l2_.cend());
        }

    };

    [[nodiscard]]
    std::list<unsigned int> compute(const std::forward_list<unsigned int>& l1,
                                    const std::forward_list<unsigned int>& l2) {
        std::list<unsigned int> out;
        auto carry = 0ULL;
        for (const auto[digit1, digit2]: zip(l1, l2)) {
            const auto sum = digit1 + digit2 + carry;
            if (sum > 9) {
                carry = 1;
            } else {
                carry = 0;
            }
            out.push_back(sum % 10);
        }
        return out;
    }

    void print(const std::list<unsigned int>& l) {
        for (const auto v: l) {
            fmt::print("{}\n", v);
        }
    }

}

int main() {
    {
        // 1234, 2001 --> 3235
        std::forward_list<unsigned int> l1{4, 3, 2, 1}, l2{1, 0, 0, 2};
        const auto out = compute(l1, l2);
        print(out);
    }

    fmt::print("\n");

    {
        // 1234, 8086 --> 9320
        std::forward_list<unsigned int> l1{4, 3, 2, 1}, l2{6, 8, 0, 8};
        const auto out = compute(l1, l2);
        print(out);
    }

    return 0;
}
