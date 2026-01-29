#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("In the library");
 set_long("This big room is used by kargs as a library. Rows of "+
   "shelves contain lots of books , and as it is well known : "+
   "knowlegde is power.\n");

 add_item("shelves","Lines of shelves were put here. They might "+
   "contain lots of books , that might contain usefull information.\n");
 add_item("books","Books are everywhere on the shelves. It must be "+
   "thouthands of them here. You wonder of what those books may "+ 
   "contain!\n");

 add_exit(STRHOLD_LVL1+"cor31","southwest");
}

