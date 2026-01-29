#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Small corridor in the stronghold");
 set_long("You are in the small, dark and very narrow corridor in "+
   "the stronghold. The corridor seems to be unfinished here. "+
   "You wonder is it safe to continue...\n");

 add_exit(STRHOLD_LVL1+"cor30","northeast");
 add_exit(STRHOLD_LVL1+"cor38","west");
}

