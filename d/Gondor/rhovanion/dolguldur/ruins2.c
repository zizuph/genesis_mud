/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/ruins2.c
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
        if (this_player()->query_prop(MM_GURUQUEST) == 2)
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
    set_long("You are amogst the ruins of Dol Guldur, not far from the " +
        "broken tower that rises up in the " + VBFC("daylight_desc") +
        " at the heart of the city. Amongst the debris here, you see " +
        "the remains of what might have been a blacksmithy. A broken " +
        "forge and bellows can be seen in the nearby rubble. The ruins " +
        "spread out in every direction, although you do notice some " +
        "restored buildings off to the southwest. There is not a clear " +
        "path away from here in any direction.\n");

    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are somewhere southwest of here, in the " +
        "restored quarter of the city.\n");
    add_item( ({"main road", "wide road", "road"}),
        "This appears to be the main road of Dol Guldur, running in a " +
        "straight line from the ruined tower to the city gates.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "This ruined and broken tower is rises high in the northwestern " +
        "horizon, rising high above the rest of the city.\n");
    add_item( ({"smith", "smithy", "blacksmith", "blacksmithy"}),
        "Judging by the broken forge and the huge bellows which are " +
        "cracked and split, it seems reasonable to assume that this " +
        "was once the pride and joy of some blacksmith.\n");
    add_item( ({"bellows", "huge bellows", "cracked bellows",
            "split bellows", "broken bellows"}),
        "The remains of these wooden bellows are quite impressive, as " +
        "they clearly reached six feet in length when whole. However, " +
        "they are now cracked and split, nothing more than garbage " +
        "like almost everything else you see in Dol Guldur.\n");
    add_item( ({"forge", "broken forge", "masonry", "crumbled masonry"}),
        "You see the crumbled masonry which once housed a blacksmith's " +
        "forge. But the forge is now broken, and the smithy it was " +
        "housed in too.\n");

    set_no_exit_msg( ({"north", "northeast", "east", "southeast", 
            "southwest", "northwest"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");

    add_exit(DG_DIR + "ruins1", "north", "@@climb@@", 5, 1);
    add_exit(DG_DIR + "ruins3", "south", "@@climb@@", 5, 1);
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