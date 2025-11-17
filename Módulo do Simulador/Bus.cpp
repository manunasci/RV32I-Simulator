#include "Bus.h"
#include "memoria.h"
#include "IO_Device.h"
#include <iostream>

Bus::Bus() : ram(nullptr), vram(nullptr), io(nullptr) {}

void Bus::conectarRAM(Memoria* m) { ram = m; }
void Bus::conectarVRAM(Memoria* m) { vram = m;}
void Bus::conectarIO(IODevice* d) { io = d; }

Bus:: Region Bus::decodificarEndereco(uint32_t addr){
    if (addr <= 0x7FFFF) return Region::RAM;
    if (addr >= 0x80000 && addr <= 0x8FFFF) return Region::VRAM;
    if (addr >= 0x9FC00 && addr <= 0x9FFFF) return Region::IO;
    return Region::INVALID;
}

uint8_t Bus::read8(uint32_t addr){
    switch (decodificarEndereco(addr))
    {
    case Region::RAM: return ram->read8(addr);
    case Region::VRAM: return vram->read8(addr - 0x80000);
    case Region::IO: return io->read(addr);
    default:
        std::cerr << "Leitura invalida em 0x" << std::hex << addr << "\n";
        return 0;
    }
}

uint16_t Bus::read16(uint32_t addr){
    uint16_t low = read8(addr);
    uint16_t high = read8(addr + 1);
    return low | (high << 8);
}

uint32_t Bus::read32(uint32_t addr){
    uint32_t b0 = read8(addr);
    uint32_t b1 = read8(addr + 1);
    uint32_t b2 = read8(addr + 2);
    uint32_t b3 = read8(addr + 3);
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

void Bus::write8(uint32_t addr, uint8_t val) {
    switch (decodificarEndereco(addr))
    {
    case Region::RAM: ram->write8(addr, val); break;
    case Region::VRAM: vram->write8(addr - 0x80000, val); break;
    case Region::IO: io->write(addr, val); break;
    default:
        std::cerr <<"Escrita invalida em 0x" << std::hex << addr << "\n";
    }
}

void Bus::write16(uint32_t addr, uint16_t val){
    write8(addr, val & 0xFF);
    write8(addr + 1, (val >> 8) & 0xFF);
}

void Bus::writw32(uint32_t addr, uint32_t val){
    write8(addr, val & 0xFF);
    write8(addr + 1, (val >> 8) & 0xFF);
    write8(addr + 2, (val >> 16) & 0xFF);
    write8(addr + 3, (val >> 24) & 0xFF);

}