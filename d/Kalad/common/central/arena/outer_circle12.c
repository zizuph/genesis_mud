/* 
 * /d/Kalad/common/central/arena/outer_circle12.c
 * Purpose    : The outer circle of the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* The outer circle of the arena */ 
/* Made by Korat 0601-95 */ 

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h"  

void create_room()
{
   
   ::create_room(); 
   hear_bell = 3;
   set_short ("The outer circle of the arena"); 
   
   set_long ("You walk below the outer archway of the arena. "+
      "Several cracked marble pillars seems to hold the weight of "+
      "the arches that vaults above you, barely lit up by some "+
      "wooden torches. The cracks in the walls, the dust and "+
      "some refuse that lies scattered around on the floor, shows "+
      "the decay this once grand arena has been a victim off." 
   );
   
   set_time_desc (" You see several people walking below the arches, "+
      "some off to watch the games and others off to fight in them.\n",
      " The archway is deserted, leaving you alone in the darkness.\n"); 
   
   add_exit (CENTRAL(arena/outer_circle11),"northeast",0,1);
   add_exit (CENTRAL(arena/outer_circle13),"southwest",0,1);
   add_exit (CENTRAL(arena/inner_circle7),"northwest","@@archway",0,1);
   
   add_item (({"archway","arch","arches"}),
      "The arches vaults high above you. You notice some decorations "+
      "in them, but time and carelessness have scarred their surface "+
      "enough to make their beauty fade.\n"); 
   
   add_item (({"arena"}),
      "You stand below the hugh arena, making it hard for you to "+
      "look at it from here.\n");
   
   add_item (({"pillar","pillars"}),
      "They are made of polished marble that would be a sight if it "+
      "wasn't for all the cracks and graffitti that ruins their "+
      "beauty.\n"); 
   
   add_item (({"graffitti"}),"Several faces, names and words are "+
      "cut into the surface. You recognize one or two...friends "+
      "of yours?\n"); 
   
   add_item (({"refuse","dust"}),
      "It is scattered all over, littering down the archway.\n"); 
   
   add_item (({"torch","torches"}),
      "The torches flicker slightly in the weak draft, "+
      "creating long yellow dancing shadows on the walls.\n");
   
   add_item (({"crack","cracks"}),
      "The cracks seems to have been there for a while, and "+
      "will probably stay there for ever until the walls fall down.\n");
   
   add_item (({"shadows","shadowes","shadow"}),
      "The shadows gives you a feeling of small hands that touch "+
      "you. Creepy...\n");
   
   set_alarm (10.0,60.0,"flickering_light");
}

flickering_light()
{
   tell_room (TO,
      "The torches flicker slightly in the draft.\n");
}

archway()
{
   TP -> catch_msg(
      "As you walk into the archway the sounds of battle grows higher, "+
      "only to be drowned in the noise of the excited audience you find "+
      "yourself in.\n");
   return 0;
}


