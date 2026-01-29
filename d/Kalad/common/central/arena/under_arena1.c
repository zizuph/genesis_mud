/* 
 * /d/Kalad/common/central/arena/under_arena1.c
 * Purpose    : Beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Under the arena */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short ("Under the arena");
   set_long (
      "You find yourself in a low hallway made of rough-cut stone. "+
      "You see some corridors bend away here, barely lit up "+
      "by the torches that hangs on the walls. "+
      "A stairway leads back up to the archway. ");
   
   set_time_desc("Some sunlight manages to lighten the corners "+
      "of the room that the torch-light cannot reach.\n",
      "The darkness is only barely pushed away by the "+
      "yellow, flickering light of the torches.\n");
   
   add_item (({"stairway","stairs"}),"The stairway ascends upwards into "+
      "the archway. Its very dirty and probably slippery "+
      "to walk.\n");
   
   add_item (({"corridor","corridors"}),"Of the three "+
      "corridors you see, the middle one is the broadest. The "+
      "two smaller ones narrows down into the semi-darkess; one "+
      "to the south and one to the west.\n");
   
   add_item (({"torch","torches"}),"The wooden torches are "+
      "securely fastened to the walls.\n");
   
   add_item (({"wall","walls"}),"The walls are made "+
      "of rough-cut stone, and are damp to the touch.\n");
   
   add_item ("stone","They are damp to the touch.\n");
   
   add_exit (CENTRAL(arena/outer_circle8),"up","@@walk_stairs",-1,-1);
   add_exit (CENTRAL(arena/under_arena2),"south","@@warning",-1,-1);
   add_exit (CENTRAL(arena/under_arena4),"west","@@warning",-1,-1);
   add_exit (CENTRAL(arena/under_arena6),"southwest",0,1);
   set_alarm (10.0,60.0,"flickering_light");
   
}

flickering_light()
{
   tell_room (TO,"The torches flicker slighty in the weak draft.\n");
}

walk_stairs()
{
   TP -> catch_msg(
      "You hasten upwards the stairway, happy to leave "+
      "this place alive. On the topmost step you loose your footings "+
      "and fall flatfaced onto the hard stone-floor.\n");
}
warning()
{
   TP -> catch_msg(
      "Someone shouts after you: Hey, be careful in there!\n");
}
