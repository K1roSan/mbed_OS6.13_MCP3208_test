#include "mcp3208.h"


#define START_BIT   0x04
#define MODE_SINGLE 0x02    // Single-ended mode
#define MODE_DIFF   0x00    // Differential mode


MCP3208::MCP3208(int frequency, PinName _mosi,PinName _miso ,PinName _sck ,PinName _cs):
m_bus(_mosi,_miso,_sck),m_cs(_cs)//I modified this line K.Nishimura
{
    m_frequency = frequency;
    deselect();
}

MCP3208::~MCP3208() {}


void MCP3208::select() {m_cs = 0;}
void MCP3208::deselect() {m_cs = 1; wait_us(1);}


int MCP3208::read_input(int channel)
{
    int command_high = START_BIT | MODE_SINGLE | ((channel & 0x04) >> 2);
    int command_low = (channel & 0x03) << 6;

    m_bus.frequency(m_frequency);
    
    select();
    
    // Odd writing requirements, see the datasheet for details
    m_bus.write(command_high);
    int high_byte = m_bus.write(command_low) & 0x0F;
    int low_byte = m_bus.write(0);
    
    deselect();
    
    int conv_result = (high_byte << 8) | low_byte;
    
    //return ((float)conv_result) / 4096;
    return conv_result;
}


int MCP3208::read_diff_input(int channel, Polarity polarity)
{
    int command_high = START_BIT | MODE_DIFF | ((channel & 0x02) >> 1);
    int command_low = ((channel & 0x01) << 7) | (polarity << 6);

    m_bus.frequency(m_frequency);

    select();
    
    // Odd writing and reading requirements, see the datasheet for details.
    m_bus.write(command_high);
    int high_byte = m_bus.write(command_low) & 0x0F;
    int low_byte = m_bus.write(0);
    
    deselect();
    
    int conv_result = (high_byte << 8) | low_byte;
    
    //return float(conv_result) / 4096;
    return conv_result;
}
