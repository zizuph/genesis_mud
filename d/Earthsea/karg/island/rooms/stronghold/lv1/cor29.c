#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. It looks abandoned, and you wonder what the "+
   "hell are you doing here!\n");

 add_exit(STRHOLD_LVL1+"cor24","east");
 add_exit(STRHOLD_LVL1+"cor30","west");
}

