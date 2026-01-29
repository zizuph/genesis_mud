// Grainne Abair - a villager who receives a letter in postman tour
// Refactored, Tapakah 08/2021

#pragma strict_types

#include "defs.h"

inherit BASE_ASHLAGH;
 
void
create_khalakhor_human ()
{
   create_villager(1,"grainne"); //1=female
   set_monster_home(ROOM+"home3");
   set_random_move(60);
}
 
