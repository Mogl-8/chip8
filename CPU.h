#include <cstdint>
#include <string.h>
#define TOTAL_RAM 4096
#define TOTAL_REGISTERS 16
#define TOTAL_STACK 16
#define TOTAL_SPRITES_BYTES 80 //16 *5 

class CPU
{

private:

    uint8_t MEM[TOTAL_RAM];

    /*Registers V0 to VF: The VF register doubles as a flag
    for some instructions; thus, it should be avoided.*/
    uint8_t V[TOTAL_REGISTERS]; 

    //16 bit register I for address, uses only the lowest 12 bits.
    uint16_t I : 12;     

    //16 bit program counter pseudo register
    uint16_t PC;   

    //8 bit stack pinter pseudo register
    uint8_t SP;    

    /*The stack is an array of 16 16 - bit values,
    used to store the address that the interpreter
    should return to when finished with a subroutine.*/
    //uint16_t STACK[TOTAL_STACK]; 

public:
    //test method

    void init(){
        const static uint8_t def_sprites[] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

        memcpy(MEM, def_sprites, 80);

    }
    uint8_t* get_RAM() {
        return MEM;
    }
    uint8_t get_RAM_data(uint16_t addr) {
        return MEM[addr];
    }
    void set_RAM_data(uint8_t data, uint16_t addr) {
        MEM[addr] = data;
    }
    uint8_t* getRegisters() {
        return V;
    }

};