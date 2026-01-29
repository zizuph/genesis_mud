#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small and dusty corridor on the second "+
   "level of the stronghold. To east this corridor runs into broad "+
   "corridor, and continues to southwest.\n");

 add_exit(STRHOLD_LVL2+"cor14","east");
 add_exit(STRHOLD_LVL2+"cor32","southwest");
}

