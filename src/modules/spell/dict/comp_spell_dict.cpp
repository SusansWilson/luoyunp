//
// Copyright (C) 2012~2012 by Yichao Yu
// yyc1992@gmail.com
// Copyright (C) 2017~2017 by CSSlayer
// wengxt@gmail.com
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; see the file COPYING. If not,
// see <http://www.gnu.org/licenses/>.
//

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#if defined(__linux__) || defined(__GLIBC__)
#include <endian.h>
#else
#include <sys/endian.h>
#endif
#include "fcitx-utils/fs.h"
#include "fcitx-utils/unixfd.h"
#include <cstring>
#include <functional>

using namespace fcitx;

#define DICT_BIN_MAGIC "FSCD0000"
const char null_byte = '\0';

static int compile_dict(int ifd, int ofd) {
    struct stat istat_buf;
    uint32_t wcount = 0;
    char *p;
    char *ifend;
    if (fstat(ifd, &istat_buf) == -1)
        return 1;

    auto unmap = [&istat_buf](void *p) {
        if (p && p != MAP_FAILED) {
            munmap(p, istat_buf.st_size + 1);
        }
    };
    std::unique_ptr<void, std::function<void(void *)>> mmapped(nullptr, unmap);

    mmapped.reset(
        mmap(nullptr, istat_buf.st_size + 1, PROT_READ, MAP_PRIVATE, ifd, 0));
    if (mmapped.get() == MAP_FAILED) {
        return 1;
    }
    p = static_cast<char *>(mmapped.get());
    ifend = istat_buf.st_size + p;
    fs::safeWrite(ofd, DICT_BIN_MAGIC, strlen(DICT_BIN_MAGIC));
    if (lseek(ofd, sizeof(uint32_t), SEEK_CUR) == static_cast<off_t>(-1)) {
        return 1;
    }
    while (p < ifend) {
        char *start;
        long int ceff;
        uint16_t ceff_buff;
        ceff = strtol(p, &p, 10);
        if (*p != ' ')
            return 1;
        ceff_buff = htole16(ceff > UINT16_MAX ? UINT16_MAX : ceff);
        fs::safeWrite(ofd, &ceff_buff, sizeof(uint16_t));
        start = ++p;
        p += strcspn(p, "\n");
        fs::safeWrite(ofd, start, p - start);
        fs::safeWrite(ofd, &null_byte, 1);
        wcount++;
        p++;
    }
    if (lseek(ofd, strlen(DICT_BIN_MAGIC), SEEK_SET) ==
        static_cast<off_t>(-1)) {
        return 1;
    }
    wcount = htole32(wcount);
    fs::safeWrite(ofd, &wcount, sizeof(uint32_t));
    return 0;
}

int main(int argc, char *argv[]) {
    const char *action = argv[1];
    if (strcmp(action, "--comp-dict") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Wrong number of arguments.\n");
            exit(1);
        }
        UnixFD ifd = UnixFD::own(open(argv[2], O_RDONLY));
        UnixFD ofd =
            UnixFD::own(open(argv[3], O_WRONLY | O_TRUNC | O_CREAT, 0644));
        if (!ifd.isValid() || !ofd.isValid()) {
            return 1;
        }
        return compile_dict(ifd.fd(), ofd.fd());
    }
    return 1;
}
