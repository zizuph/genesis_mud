#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in rather small corridor. It looks dark and "+
   "seems to be abandoned long ago.\n");

 add_exit(STRHOLD_LVL2+"cor23","northwest");
 add_exit(STRHOLD_LVL2+"guard2","southwest");
}

