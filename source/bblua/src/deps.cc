/**
 * Copyright (c) Jason White
 *
 * MIT License
 *
 * Description:
 * Handles sending dependencies to parent build system.
 */
#include "deps.h"

#include <stdlib.h>

ImplicitDeps::ImplicitDeps() : _f(NULL) {
    int fd;
    const char* var = getenv("BB_DEPS");
    if (var && (fd = atoi(var))) {
        _f = fdopen(fd, "a");
    }
}

ImplicitDeps::~ImplicitDeps() {
    if (_f) fclose(_f);
}

bool ImplicitDeps::hasParent() const {
    return _f != NULL;
}

void ImplicitDeps::add(const Dependency& dep) {
    if (!_f) return;

    fwrite(&dep, sizeof(dep) + dep.length, 1, _f);
}

void ImplicitDeps::addInputFile(const char* name, size_t length) {
    if (!_f) return;

    if (length > UINT16_MAX)
        length = UINT16_MAX;

    Dependency dep = {0};
    dep.output = 0;
    dep.length = (uint16_t)length;

    fwrite(&dep, sizeof(dep), 1, _f);
    fwrite(name, 1, dep.length, _f);
}

void ImplicitDeps::addOutputFile(const char* name, size_t length) {
    if (!_f) return;

    if (length > UINT16_MAX)
        length = UINT16_MAX;

    Dependency dep = {0};
    dep.output = 1;
    dep.length = (uint16_t)length;

    fwrite(&dep, sizeof(dep), 1, _f);
    fwrite(name, 1, dep.length, _f);
}
