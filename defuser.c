#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
	size_t count = 1;
	uint32_t values[MAX_FIELDS] = {0};
    // 根据 phase_01 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    	uint32_t low32  = (uint32_t)challenge;
    	uint32_t high32 = (uint32_t)(challenge >> 32);
   	uint32_t mid    = (uint32_t)(challenge >> 16);

    	uint32_t s2 = UINT32_C(5) * (high32 - low32) + UINT32_C(0x937a);
    	uint32_t s0 = (mid + UINT32_C(0x3f2e)) ^ low32;
    	uint32_t s1 = UINT32_C(2) * s0 + (s2 ^ UINT32_C(0x6825));

    	values[0] = s1;

    	return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
	uint32_t values[MAX_FIELDS] = {0};
        size_t count = 6;

        values[0] = (uint32_t)((challenge >> 8) & 0x3f) ^ UINT32_C(6);

        for (int i = 0; i < 5; ++i) {
        	uint32_t t = (uint32_t)((challenge >> (27 + 4 * i)) & 0xf);
        	values[i + 1] = (t + values[i]) ^ (uint32_t)(2 + 2 * i);
    	}

        return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 2;

    uint32_t idx = (uint32_t)challenge & 7u;
    uint32_t t   = (uint32_t)(challenge >> 32) ^ (uint32_t)(challenge >> 3);
    uint32_t a2;

    switch (idx) {
        case 0: a2 = 5u * t + UINT32_C(0x18862); break;
        case 1: a2 = (t * 4u) ^ UINT32_C(0x64ee); break;
        case 2: a2 = (t ^ UINT32_C(0x5aa1)) + (t >> 1); break;
        case 3: a2 = (t ^ UINT32_C(0x7a45)) + (t >> 1); break;
        case 4: a2 = 5u * t + UINT32_C(0xdf8e);  break;
        case 5: a2 = (2u * t) ^ UINT32_C(0xbe1b); break;
        case 6: a2 = 5u * t + UINT32_C(0x4089e); break;
        case 7: a2 = 5u * t + UINT32_C(0xd2d);   break;
        default: a2 = 0; break;
    }

    values[0] = idx;
    values[1] = a2;

    return write_answer(out, cap, values, count);
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    return 1;
}
