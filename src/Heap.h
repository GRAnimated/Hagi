#pragma once

class Heap {
    static Heap* s_pInstance;
    static Heap* GetInstance();

public:
    virtual void* Alloc(int size, int alignment, void*);
    virtual ~Heap();

    void* Allocate(int size, int alignment, void*);
    void Free(void* ptr);
};
