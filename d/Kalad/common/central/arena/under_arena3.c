/* 
 * /d/Kalad/common/central/arena/under_arena3.c
 * Purpose    : Beneath the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Below the arena */ 
/* Made by Korat 1101-95 */ 

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h" 
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int lion_loose; 

void create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short ("Below the arena"); 
   
   set_long ("Barely lit up by a torch, this damp stone-corridor "+
      "is very plain to look at. The only thing that catches your "+
      "attention is a grating in the ceiling and a cage in the corner. ");
   
   set_time_desc ("Some sunlight manages to creep down from the "+
      "grating and makes the blood on the floor to shine.\n",
      "Its hard to make out any details in this darkness.\n");
   
   add_exit (CENTRAL(arena/under_arena2),"northeast",0,-1,-1);
   
   add_item ("torch","The wooden torch is securely fastened to the wall.\n");
   
   add_item (({"wall","walls"}),"The walls are of rough-cut stone.\n");
   
   add_item ("grating","The grating is of metal, and securely locked. "+
      "You can hear sounds of fighting through it; the sound of metal "+
      "hitting flesh is a sound you know very well.\n");
   
   add_item ("blood","You bend down and touch the blood: Its fresh..."+
      "not dried up yet.\n");
   
   set_alarm (0.0,0.0,"reset_room");
   
   
   add_item ("cage","The cage itself has metal bars and a hatch on "+
      "the left side. From the smell of the cage, you "+
      "understand that it is a lion-cage. The lions are probably "+
      "kept here to make them even more wild than "+
      "they were before...the smell of fresh blood must "+
      "drive them crazy. These are not animals that you want to meet "+
      "in a fight! So you better leave the cage alone...\n");
   
   add_item ("hatch","@@release_lion");
   
   set_alarm(60.0,400.0,"drag_corpse");
   set_alarm(30.0,60.0,"flickering_light");
   
}

void
reset_room()
{
   lion_loose = 0;
   return;
}

drag_corpse()
{
   tell_room (TO,
      "A tall human comes walking in. He unlocks and opens the grating. "+
      "After a while your hear sounds of a wagon from above...then "+
      "something is dragged towards the grating.\n\n"+
      "Suddenly a corpse of an unfortunate gladiator falls down and "+
      "lands in front of your feet. The tall human grips the hair of "+
      "the corpse and leaves the room, dragging the corpse after him.\n"+
      "\nWhen you look down at the floor, you notice the fresh blood "+
      "that shines with a deep red colour...\n");
   return 0;
}

flickering_light()
{
   tell_room(TO,"The torch flickers slighty in the weak draft.\n");
   return 0;
}

release_lion()
{
   say(QCTNAME(TP) + " walks closer to the cage to look at the hatch.\n");
   if (lion_loose)
      return("The hatch is broken...\n");
   lion_loose = 1;
   tell_room (TO,"The lions inside the cage sense the "+
      "presence of a person close to the cage. They go crazy! "+
      "They run at the hatch, and the hatch breaks up with "+
      "a deafening crash...the lions are loose!\n");
   clone_object ("/d/Kalad/common/central/npc/cage_lion")->
   move_living("xxx",TO);
   clone_object ("/d/Kalad/common/central/npc/cage_lion")-> move_living("xxx",TO);
   return ("");
}
