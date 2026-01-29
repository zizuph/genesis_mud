
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"


public void create_gondor();
public void reset_room();

/*
object Npc;
*/
object *Rangers = allocate(4);

public void
create_gondor()
{
    set_short("a small clearing");
    set_long("The woods grow thin here, forming a large " +
      "clearing.  " +
      "The sky is visible above, granting a sense of space in " +
      "the otherwise crowded forest.  " +
      "Many items lay strewn about the area, the remaining " +
      "pieces of a hastily broken camp.  " +
      "\n");
    add_item("ground","The ground is covered with grass, very boring.\n");
    add_item(({"camp","items","item","piece","pieces","area"}),
      "The fragments of a camp litter the area with useless " +
      "junk.  " +
      "A dented pot, pieces of clothing, and straps of " +
      "leather are the more immediately recognizable items.\n");
    add_item(({"tree","trees"}),"The trees here are not as " +
      "thick as in some areas of the woods, but still " +
      "stand tall and strong.\n");
    add_item(({"pot","dented pot","clothing","pieces of clothing",
	"clothes","straps","straps of leather","leather straps",
	"junk","fragments"}),
      "Simply a piece of useless junk left over from someone's camp.\n");
    add_item("sky","The sky seems to extend forever above you.\n");

    add_exit(CAMP_ROOM_DIR + "trail3","north");
    add_exit(CAMP_ROOM_DIR + "trail4","west");

    reset_room();

}


public void
reset_room()
{
    /*
	if (!objectp(Npc))
	{
	    Npc = clone_npc(Npc, CAMP_NPC_DIR + "gondorian");
	}
    */


    if (!objectp(Rangers))
    {
	set_alarm(2.0, 0.0, &clone_npcs(Rangers, NPC_DIR + "i_ranger", 1.0));
    }
}





