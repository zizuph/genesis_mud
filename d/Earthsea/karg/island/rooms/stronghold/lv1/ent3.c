#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Entrance to the stronghold");
 set_long("You are standing in front of the dark corridor leading "+
   "north, while it splits to northeast and northwest. Back to south "+
   "you see gates.\n");

 add_item(({"arch","gate","gates"}),"Sturdy wooden gates can easily "+
   "block entrance to any unwelcomed creature.\n");

 add_item("corridor","It leads into the stronghold.\n");

 add_exit(STRHOLD_LVL1+"ent2","south");
 add_exit(STRHOLD_LVL1+"cor1","north");
 add_exit(STRHOLD_LVL1+"cor18","northwest");
 add_exit(STRHOLD_LVL1+"cor19","northeast");
}

