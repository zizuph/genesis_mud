/*
 * A beach in Roke by Ckrik, 9/2003
 */
#include "defs.h"

inherit ROKE_BEACH + "std/base_beach_rocky.c";
 
void
create_beach()
{ 
    add_my_desc("\n");
    add_exit(ROKE_BEACH+"rooms/beach08","north");
    add_exit(ROKE_BEACH+"rooms/beach06","southwest");
}
