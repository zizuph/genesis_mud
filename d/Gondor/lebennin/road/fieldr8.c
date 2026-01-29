/*
 * /d/Gondor/lebennin/road/fieldr8.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/defs.h"

static object  Rabbit;

public void
create_area_room()
{
    set_area("southeast");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(2);
    set_areadesc("field");
    set_grass("green");
    add_exit(LEB_DIR + "road/fieldr6", "south", 0,2);
   
    add_item(({"house","hut","building"}),
        "This old hut seems inhabited, but you think you should not try to go in.\n");
   
    set_extraline("A hut to your north is in sharp contrast to the lack "+
        "of civilization in this area.");
   
    set_up_herbs( ({ HERBS[random(sizeof(HERBS))],
		     HERBS[random(sizeof(HERBS))],
		     HERBS[random(sizeof(HERBS))], }),
		  ({ "bushes","bush","field","fields","ground","grass"}), 8);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    Rabbit = clone_npc(Rabbit, NPC_DIR + "wrabbit", LEB_DIR);
    Rabbit->set_random_move(5);
}

public int
enter_house(string str)
{
    NFN("Enter where?\n");
    if (!strlen(str))
	return 0;
    NFN("Enter what?");
    if ((str != "hut") && (str != "house"))
	return 0;
    set_dircmd(str);
    write("You enter the little hut.\n");
    TP->move_living("into the hut", LEB_DIR + "road/hut1");
    return 1;
}

public void
init()
{
    ::init();
    add_action(enter_house, "enter");
}
