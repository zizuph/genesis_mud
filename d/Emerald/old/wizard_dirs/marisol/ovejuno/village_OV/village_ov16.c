
/* Re Albi village. Village's path XVI.
 * Coded by Marisol (04/15/98)
 * Modified by Marisol (08/04/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#include "/d/Emerald/sys/macros.h"
#pragma strict_types
#include "defs.h"
#define FISHOOK OV_VILLAGE_NPC + "villager02"
#define OAKHEART OV_VILLAGE_NPC + "villager03"
inherit OV_VILLAGE;

object fishook;
object oakheart;


void reset_room()
{
 if(!objectp(fishook))
  {
  fishook=clone_object(FISHOOK);
  fishook->move(TO);
  fishook->command("emote walks in.");
  }

 if(!objectp(oakheart))
  {
  oakheart=clone_object(OAKHEART);
  oakheart->move(TO);
  oakheart->command("emote walks in.");
  }
}

void
create_ov_room()
{

    set_long("A village path in Ovejuno. The small trail "+
        "end here in the back of the blacksmith's shop. You hear "+
        "faintly the rhythmical beating of a hammer over an anvil. "+
        "From here you can see the beautiful view of mountains and "+
        "valleys, and farthest the sea. You can always find some men "+
        "villagers sitting here chatting about the weather or their "+
        "day life, enjoying the fresh breeze of the mountains and "+
        "the specutacular view. Blue-grey smokes rise from the smith's "+
        "drifting lazily in the cool wind. In the distance, puffy "+
        "white clouds sail with the mountain breeze.\n");

    add_item("clouds",
        "White puffy clouds like cotton candy sail softly "+
        "to the mountains. If you gaze closely to the clouds, "+
        "you will detect the outline of a fiery drake.\n");

    add_item(({"blacksmith's shop", "shop"}),
        "The back of the blacksmith's shop is as sturdy as the "+
        "front of it.\n");

    add_item("view",
        "Blue-green mountains rise and fall in the distance, "+
        "creating deep valleys and ravines. At the end of your vision, "+
        "you can see faintly, the aquamarine blue of the sea.\n");

    reset_room();


    add_exit("village_ov12.c", "northwest");
   
}                                                                      

