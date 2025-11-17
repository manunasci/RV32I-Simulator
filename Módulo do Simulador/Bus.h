#ifndef BUS_H
#define BUS_H

#include <cstdint>

class Memoria;
class IODevice;

class Bus{
    public:
        Bus();

        void conectarRAM(Memoria* mem);
        void conectarVRAM(Memoria* vram);
        void conectarIO(IODevice* io);

        uint8_t read8(uint32_t addr);
        uint16_t read16(uint32_t addr);
        uint32_t read32(uint32_t addr);

        void write8(uint32_t addr, uint8_t val);
        void write16(uint32_t addr, uint16_t val);
        void writw32(uint32_t addr, uint32_t val);

    private:
        Memoria* ram;
        Memoria* vram;
        IODevice* io;

        enum class Region{
            RAM,
            VRAM,
            IO,
            INVALID
        };  

        Region decodificarEndereco(uint32_t addr);
};

#endif