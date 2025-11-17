#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <array>

class Bus;

class CPU{
    public:
        CPU();
        explicit CPU(Bus* bus);

        void connecBus(Bus* bus);
        void reset(uint32_t reset_pc = 0);

        void step();

        void run(uint64_t max_steps = 100000);

        void setDebug(bool b) { debug = b;}
    
    private:
    Bus* bus;
    std::array<uint32_t, 32> x;
    uint32_t pc;
    bool debug = false;

    uint32_t fetch32(uint32_t addr);

    void decode_execute(uint32_t instr);
    void handle_unknown(uint32_t instr);

    uint32_t reg_read(unsigned idx) const;
    void reg_write(unsigned idx, uint32_t val);

    static uint32_t get_bits(uint32_t value, unsigned hi, unsigned lo);
    static uint32_t sext(uint32_t val, unsigned bits);

    int32_t imm_i(uint32_t) const;
    int32_t imm_s(uint32_t) const;
    int32_t imm_b(uint32_t) const;
    int32_t imm_u(uint32_t) const;
    int32_t imm_j(uint32_t) const;
};

#endif