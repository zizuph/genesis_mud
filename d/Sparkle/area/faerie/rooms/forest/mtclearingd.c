/*
 * A clearing near the road between Sparkle and Faerie
 * By Nerull, August 2009
 *
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "";

void
create_forest_room()
{
    set_short("At the rocky base of a tall mountain");
    set_long(mt_desc10(extra_line));

    set_add_valley();
    add_std_herbs("forest");
    reset_room();

    set_conifer_trees();
    set_add_forest_debris();


    add_exit(FOREST_DIR + "mtroad10", "southeast");

    reset_room();

}

public void
init()
{
    ::init();
}

void
reset_room()
{
	object guardian;

   if (random(4) == 1)
   	{
       if (!present("_skeleton_champion"))
        {
          guardian = clone_object(DRAGON_DIR +"npc/skel_champ");
          guardian->move(this_object(), 1);
        }
    }

    set_searched(0);
}
