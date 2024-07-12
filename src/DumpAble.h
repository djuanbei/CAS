//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_DUMPABLE_H
#define CAS_DUMPABLE_H

#include <iostream>

namespace cas {

    class DumpAble {
    public:
        virtual ~DumpAble() = default;

        virtual std::ostream &dump(std::ostream &out, int tab_indent) const = 0;
    };

}

#endif //CAS_DUMPABLE_H
