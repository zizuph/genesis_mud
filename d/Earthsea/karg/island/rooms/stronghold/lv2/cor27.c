#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small corridor on the second level "+
   "of the stronghold. To the west this corridor connects with bigger "+
   "one , while it continues towards northeast.\n");

 add_exit(STRHOLD_LVL2+"cor6","west");
 add_exit(STRHOLD_LVL2+"cor28","northeast");
}

