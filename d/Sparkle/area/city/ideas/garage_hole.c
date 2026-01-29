/*
 * /d/Sparkle/area/city/bank/room/garage_hole.c
 *
 * This is the guard room for the second floor vaults of the main branch
 * of the Gnomes of Genesis in Sparkle.
 *
 * Created Feb 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard";

/* Prototypes */


/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
    set_short("A dark hole");
    set_long("Garage hole station of the Gnomes of Genesis.\n\n");


    add_cmd_item(({"hole", "through the hole", "through hole" }),
                   "crawl", "@@crawl");
    /* Exits */

    
} /* create_bank_room */

public int
crawl()
{
    write("You crawl into the dark hole.\n");
    this_player()->move_living("crawling through the dark hole", 
               "/d/Sparkle/area/city/bank/room/garage" );
    return 1;
} /* crawl */


/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
    object spawn;
    int num_spawn;
    object hammer;
    int num_hammer;
    
    if (!present("owlrat")) {
        num_spawn = random(1) + 2;    
        for (int i = 0; i < num_spawn; ++i) {
            spawn = 
            clone_object("/d/Sparkle/area/city/sewer/npc/owlrat_scout");
            spawn->move(this_object());
        }
    }
    
    if (!present("quest_hammer")) {
        {
            hammer = 
            clone_object("/d/Sparkle/area/city/bank/obj/quest_hammer");
            hammer->add_prop(OBJ_I_HIDE, 20);
            hammer->move(this_object());
        }
    }
    
} /* reset_room */
