/* 
 * /d/Kalad/common/central/arena/under_arena9.c
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
   hear_bell = 1;
   add_prop(ROOM_I_INSIDE,1);
   set_short ("Under the arena");
   set_long (
      "You find yourself at the end of the low hallway. Further "+
      "southwestwards this hallway leads to a solid, wooden door."+
      " Some corridors bend away to the west and south, barely "+
      "lit up by the torches that hangs on the walls, and the main "+
      "corridor extends itself to the northeast. "+
      "Some snoring can be heard from the west.\n");
   
   add_item (({"corridor","corridors"}),"Off the three "+
      "corridors you see, the middle one is the broadest. The "+
      "two smaller ones narrows down into the semi-darkess; one "+
      "to the south and one to the west.\n");
   
   add_item (({"torch","torches"}),"The wooden torches are "+
      "securely fastened to the walls. They throw out a yellow "+
      "flickering light that barely manages to light the room.\n");
   
   add_item (({"wall","walls"}),"The walls are made "+
      "of rough-cut stone, and are damp to the touch.\n");
   
   add_item ("stone","They are damp to the touch.\n");
   
   add_item ("plaque","Its made of bronce and has some "+
      "words engraved on it.\n");
   
   add_item ("read","@@read_plaque");
   
   add_exit (CENTRAL(arena/under_arena10),"south",0,-1,-1);
   add_exit (CENTRAL(arena/under_arena11),"west",0,-1,-1);
   add_exit (CENTRAL(arena/under_arena6),"northeast",0,-1,-1);
   clone_object("/d/Kalad/common/central/doors/glad_door1")->move(TO);
   
   set_alarm (10.0,60.0,"flickering_light");
}

flickering_light()
{
   tell_room (TO,"The torches flicker slighty in the weak draft.\n");
}

read_plaque(string str)
{
   if (!str) return "Read what?\n";
   if (str != "plaque") return "Read what?\n";
   return ("The plaque reads: KAROTH - Master of the Arena.\n"+
      "Office hours : from nine in the morning to eight in the "+
      "evening.\n");
}


