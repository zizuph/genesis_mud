/*
 * Created by Aridor 07/06/93
 * Herbs added by Aridor, 08/11/94
 *
 * 03.2006 Adapted by Mortis for upgraded Palanthas.
 *
 */

#include "../local.h"
#include <macros.h>

inherit MERCH_BASE;

#define  GONDOR_HERB_PATH   "/d/Gondor/common/herbs/"

#include "/d/Krynn/common/herbsearch.h"
#include CLOCKH

int can_dig, has_hop, has_malt;

string
query_to_jail()
{
    return "southwest";
}

void
reset_palan_room()
{
    set_searched(0);
    can_dig = 2;   /* two worms per reset :-) */
    has_hop = 10;
    has_malt = 10;
}

void
create_palan_room()
{
    
    SHORT("Garden");
    LONG("You are standing in a small garden. There is a little " +
	     "hut there, almost invisible behind the green. There are " +
	     "fruit trees and bushes, but the " +
	     "owner grows vegetables here as well. Since the ground " +
	     "seems very damp everything is flowering and prospering.\n");
    
    ITEM("garden",
	     "It's a beautiful green and flowering garden.\n");
    ITEM(({"tree","fruit tree","trees","fruit trees"}),
	     "You can make out an apple tree, a peach tree and a plum tree.\n");
    ITEM(({"apple tree","peach tree","plum tree","vegetables"}),
	     "You can't see anything special.\n");
    ITEM(({"bush","bushes"}),
	     "These bushes grow like vines, the leaves of some bushes " +
	     "seem to give off a bitter smell.\n");
    ITEM(({"hop","hops","leaf","leaves"}),
	     "There are several leafy vines of hop growing in the back "
	     +    "of the garden.\n");
    ITEM("hut",
	     "This hut is more like a shed containing some tools. " +
	     "You notice some " +
	     "vines winding their way up the shed into the trees.\n");
    ITEM("tools","These tools are old, rusty, and worthless.\n");
    ITEM(({"vines","malt"}),"Some malt vines wind their way up the "
	     +    "shed and the trees.\n");
    ITEM(({"ground","grass"}),"You think you saw something moving.\n");
    CMD(({"hut","shed"}),"enter",
		 "The hut is very small so you cannot enter it.\n");
    CMD(({"ground","grass","here"}),"dig","@@find_worm");
    CMD(({"hop","hops","leaf","leaves"}),"pick","@@pick_hop");
    CMD(({"malt","vine","vines"}),"pick","@@pick_malt");
    
    reset_palan_room();

    seteuid(getuid(TO));

    set_search_places(({"garden","bushes","ground","grass"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(GONDOR_HERB_PATH + "dill");
    add_herb_file(GONDOR_HERB_PATH + "fennel");
    add_herb_file(GONDOR_HERB_PATH + "mint");
    add_herb_file(GONDOR_HERB_PATH + "oregano");
    add_herb_file(GONDOR_HERB_PATH + "thyme");
    add_herb_file(GONDOR_HERB_PATH + "garlic");

	EXIT(MERCH + "wr3", "southwest", 0, 0);
}



find_worm()
{
    if (can_dig)
    {
        say(QCTNAME(TP) + " picks something off the ground.\n");
        write("You find a little earthworm in the grass and pick it up.\n");
        clone_object(MERCH + "obj/worm")->move(TP);
        can_dig--;
        return 1;
    }
    else
    {
        write("You dig through the ground but can't find anything!\n");
        return 1;
    }
}


pick_hop()
{
    if (has_hop)
    {
        say(QCTNAME(TP) + " picks some leaves from a bush.\n");
        write("You pick some hop leaves from a bush.\n");
        clone_object(MERCH + "obj/hop")->move(TP);
        has_hop--;
        return 1;
    }
    else
    {
        write("It seems there are no more leaves left to pick here!\n");
        return 1;
    }
}

pick_malt()
{
    if (has_malt)
    {
        say(QCTNAME(TP) + " picks some grains from a vine.\n");
        write("You pick some malt grains from a vine.\n");
        clone_object(MERCH + "obj/malt")->move(TP);
        has_malt--;
        return 1;
    }
    else
    {
        write("It seems there are no more grains left to pick here!\n");
        return 1;
    }
}

