inherit "/std/object";
#include "/d/Kalad/defs.h"
/* The Bell within the Bell Tower of Kabal 
/* by Antharanos 

// Polish functions moved from bell to room, so they can hint if
// the quest npc isnt in the room. - 26/6-2021 Meton. */

void
create_object()
{
   set_name("bell");
   set_adj("great");
   add_adj("bronze");
   set_long("A bell of epic proportions that rings at every hour of the day "+
      "here in the city of Kabal. The bell looks quite dirty.\n");
   add_prop(OBJ_I_VALUE,34560);
   add_prop(OBJ_I_VOLUME,500000);
   add_prop(OBJ_I_WEIGHT,500000);
   add_prop(OBJ_M_NO_GET,"Are you out of your mind?!?\n");
}