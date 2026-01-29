
/* 
    ~Domain/sys/direc.h 

    Include file for map directions. 

    Coded by Maniac@Genesis, March 1997 

    Copyright (C) Miguel leith 1997.  
*/ 

#ifndef DIREC_DEFS
#define DIREC_DEFS

#define NORTH 1 
#define SOUTH 2
#define EAST 4
#define WEST 8
#define NORTHEAST 16
#define SOUTHWEST 32
#define NORTHWEST 64
#define SOUTHEAST 128
#define UP 256
#define DOWN 512

#define C_NORTH ({ 0, 1, 0 })
#define C_SOUTH ({ 0, -1, 0 })
#define C_EAST ({ 1, 0, 0 })
#define C_WEST ({ -1, 0, 0 })
#define C_NORTHEAST ({ 1, 1, 0 })
#define C_SOUTHWEST ({ -1, -1, 0 })
#define C_NORTHWEST ({ -1, 1, 0 })
#define C_SOUTHEAST ({ 1, -1, 0 })
#define C_UP ({ 0, 0, 1 })
#define C_DOWN ({ 0, 0, -1 })

#endif

