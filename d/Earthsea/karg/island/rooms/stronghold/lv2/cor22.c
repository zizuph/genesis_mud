#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in rather small corridor. It connects with bigger "+
   "corridor to southwest and leads towards east.\n");

 add_exit(STRHOLD_LVL2+"cor17","southwest");
 add_exit(STRHOLD_LVL2+"cor23","east");
}

