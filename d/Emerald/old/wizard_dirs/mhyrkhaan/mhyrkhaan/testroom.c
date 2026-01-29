inherit "/std/workroom";
#include "/d/Kalad/defs.h"

create_workroom()
{
   set_short("A very bloody room");
   set_long("You are in a room, with blood covered walls, the floor is"+
   " littered with remains, and hunks of gore. You can feel the presence "+
   "of all the lost souls that have been torn and slashed to pieces in here.\n");
   clone_object("/d/Kalad/mhyrkhaan/private/grate2")->move(TO);
}
