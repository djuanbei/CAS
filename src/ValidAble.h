//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_VALIDABLE_H
#define CAS_VALIDABLE_H

namespace cas {

    class ValidAble {
    public:
        virtual ~ValidAble() = default;

        [[nodiscard]] virtual bool valid() const = 0;

    };
}

#endif //CAS_VALIDABLE_H
