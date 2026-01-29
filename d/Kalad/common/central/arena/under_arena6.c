/* 
 * /d/Kalad/common/central/arena/under_arena6.c
 * Purpose    : Beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Under the arena */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   add_prop(ROOM_I_INSIDE,1);
   set_short ("Under the arena");
   set_long (
      "You find yourself in a low hallway made of rough-cut stone. "+
      "Some corridors bend away to the west and south, barely "+
      "lit up by the torches that hangs on the walls, and the main "+
      "corridor extends itself to the southwest and the northeast. "+
      "A faint smell of food "+
      "drifts in from the west. To the south you hear sounds of "+
      "metal hitting metal.\n");
   
   add_item (({"corridor","corridors"}),"Of the three "+
      "corridors you see, the middle one is the broadest. The "+
      "two smaller ones narrows down into the semi-darkess; one "+
      "to the south and one to the west.\n");
   
   add_item (({"torch","torches"}),"The wooden torches are "+
      "securely fastened to the walls. They throw out a yellow "+
      "flickering light that barely manages to light the room.\n");
   
   add_item (({"wall","walls"}),"The walls are made "+
      "of rough-cut stone, and are damp to the touch.\n");
   
   add_item ("stone","They are damp to the touch.\n");
   
   add_exit (CENTRAL(arena/under_arena8),"south",0,-1,-1);
   add_exit (CENTRAL(arena/under_arena7),"west",0,-1,-1);
   add_exit (CENTRAL(arena/under_arena9),"southwest",0,-1,-1);
   add_exit (CENTRAL(arena/under_arena1),"northeast",0,-1,-1);
   
   set_alarm(0.0,0.0,"reset_room");
   set_alarm (10.0,60.0,"flickering_light");
}

flickering_light()
{
   tell_room (TO,"The torches flicker slighty in the weak draft.\n");
}

reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/bull");
      ob1 -> move_living("xxx",TO);
      ob1 -> command("emote grunts.");
   }
}
