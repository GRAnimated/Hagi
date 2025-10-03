#pragma once

class Program {
public:
    struct Option {
        const char* shortOpt;
        const char* longOpt;
        int requiresArg;
        const char* help;
    };

    Program(const char* name, const char* acceptedInputExtensions, Option* options, int descriptionLines);

    virtual void sub_710016C0F0();
    virtual void sub_710016C110();
    virtual void nullsub_193();
    virtual void Initialize() = 0;
};
