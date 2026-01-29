/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/ruins6.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

#define MM_GURUQUEST           "_on_mm_quest"
#define FOUND_MM_BOOK          "_found_mm_book"


string do_search(object searcher, string str)
{
    if (str == "ruins")
    {
        // No MM, no quest.
        if (!this_player()->query_guild_name_occ("Morgul Mages"))
        {
            return "";
        }
        
        // If the quest is done, nothing can be found.
        if(this_player()->test_bit("Gondor", 2, 1))
        {
            return "";
        }
        
        // Already found the book
        if (this_player()->query_prop(FOUND_MM_BOOK))
        {
            return "";
        }
        
        // No timerobject means not on the quest.
        if (!present("_mm_timerobject1_", this_player()))
        {
            return "";
        }
        
        // If paralyzeobject is present for some reason, nothing can 
        // be found.
        if (present("_mm_cutscene_paralyze_item", this_player()))
        {
            return "";
        }
        
        //If player carries the quest spellbook, nothing can be found.
        if (present("_mm_spellbook", this_player()))
        {
            return "";
        }
        
        // Ruin 7 only accept 7 on the prop.
        if (this_player()->query_prop(MM_GURUQUEST) == 6)
        {
            object cutscene_paralyze_item;

            cutscene_paralyze_item = clone_object(RHOVANION_DIR 
                + "dolguldur/obj/cutscene_paralyze_item")->move(this_player(), 1);;
            
            tell_room(this_object(), QCTNAME(this_player()) + " finds "
                + "something in the ruins.\n", this_player());
                
            this_player()->add_prop(FOUND_MM_BOOK, 1);
                
            return "You find a spellbook in the ruins!\n";
        }
        
        return "";

    }
    
    return "";
}

/*
 * Function name:        create_dg_room()
 * Description  :        Creates the dg from from the base file
 *                       /d/Gondor/rhovanion/dolguldur/std/base.c
 */
void 
create_dg_room()
{
    seteuid(getuid());

    set_items_broken();
    set_items_ruins();
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);
    
    set_short("Dol Guldur");
    set_long("The ruins of Dol Guldur surround you here, including " +
        "the remains of what appears to have been a library in better " +
        "days. Nearby to the northeast stands a tall tower, broken " +
        "and jagged as it stands out in the " + VBFC("daylight_desc") +
        ". The rubble continues in every direction, but you do see " +
        "some restored buildings off to the south. There is not " +
        "a clear path away from here in any direction.\n");

    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are somewhere southwest of here, in the " +
        "restored quarter of the city.\n");
    add_item( ({"main road", "wide road", "road"}),
        "This appears to be the main road of Dol Guldur, running in a " +
        "straight line from the ruined tower to the city gates.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "This ruined and broken tower is rises high in the northwestern " +
        "horizon, rising high above the rest of the city.\n");
    add_item( ({"library", "building", "broken building", "broken library"}),
        "Jutting up out of the rubble is a broken building, the " +
        "remains of what was once a library. It is hard to see details " +
        "as rubble has filled in the building.\n");

    set_no_exit_msg( ({"north", "northeast", "east", "southeast", 
            "southwest", "northwest"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");

    add_exit(DG_DIR + "ruins5", "east", "@@climb@@", 5, 1);
    add_exit(DG_DIR + "ruins7", "west", "@@climb@@", 5, 1);
}

/* A message which indicates climbing through the rubble when using 
   the hidden exits. */
int
climb()
{
    write("With a great deal of effort, you climb over broken blocks " +
        "of stone and wooden beams as you leave the main road.\n");
    return 0;
}