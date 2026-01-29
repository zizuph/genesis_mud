/* 
 * /d/Kalad/common/central/arena/under_arena4.c
 * Purpose    : Beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Below the arena */ 
/* Made by Korat 1101-95 */ 

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h" 

void 
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short ("Below the arena"); 

   set_long ("Barely lit up by a torch, this damp stone-corridor "+
      "is very plain to look at. The only thing that catches your "+
      "attention is a grating in the ceiling and some fresh blood "+
      "on the floor. ");
 
   set_time_desc ("Some sunlight manages to creep down from the "+
      "grating and makes the blood on the floor to shine.\n",
      "Its hard to make out any details in this darkness.\n");

   add_exit (CENTRAL(arena/under_arena1),"east",0,-1,-1);
   add_exit (CENTRAL(arena/under_arena5),"southwest",0,-1,-1);

   add_item ("torch","The wooden torch is securely fastened to the wall.\n");

   add_item (({"wall","walls"}),"The walls are of rough-cut stone.\n");

   add_item ("grating","The grating is of metal, and securely locked. "+
      "You can hear sounds of fighting through it; the sound of metal "+
      "hitting flesh is a sound you know very well.\n");

   add_item ("blood","You bend down and touch the blood: Its fresh..."+
      "not dried up yet.\n");

   set_alarm(60.0,240.0,"drag_corpse");
   set_alarm(30.0,60.0,"flickering_light");
 
}

void
drag_corpse()
{
   tell_room (TO,
      "A tall human comes walking in. He unlocks and opens the grating. "+
      "After a while your hear sounds of a wagon from above...then "+
      "something is dragged towards the grating.\n\n"+
      "Suddenly a corpse of an unfortunate lion falls down and "+
      "lands in front of your feet. The tall human grips the hair of "+
      "the corpse and leaves the room, dragging the corpse after him.\n"+
      "\nWhen you look down at the floor, you notice the fresh blood "+
      "that shines with a deep red colour...\n");
   return 0;
}

flickering_light()
{
   tell_room(TO,"The torches flicker slighty in the weak draft.\n");
}






