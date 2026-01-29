#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in rather small corridor. It connects with bigger "+
   "corridor to southeast and leads towards west.\n");

 add_exit(STRHOLD_LVL2+"cor3","southeast");
 add_exit(STRHOLD_LVL2+"cor20","west");
}

