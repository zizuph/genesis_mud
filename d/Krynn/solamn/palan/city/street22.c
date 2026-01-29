/* created by Aridor 07/06/93 */
/* herbs added by Aridor, 08/11/94 */

#include "../local.h"

inherit STREET_BASE

#include <macros.h>
#include "/d/Krynn/common/herbsearch.h"
#define  GONDOR_HERB_PATH   "/d/Gondor/common/herbs/"

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
    
    set_short("Garden");
    set_long("You are standing in a small garden. There is a little " +
	     "hut there, almost invisible behind the green. There are " +
	     "fruit trees and bushes, but the " +
	     "owner grows vegetables here as well. Since the ground " +
	     "seems very damp everything is flowering and prospering.\n");
    
    OUTSIDE;
    
    add_item("garden",
	     "It's a beautiful green and flowering garden.\n");
    add_item(({"tree","fruit tree","trees","fruit trees"}),
	     "You can make out an apple tree, a peach tree and a plum tree.\n");
    add_item(({"apple tree","peach tree","plum tree","vegetables"}),
	     "You can't see anything special.\n");
    add_item(({"bush","bushes"}),
	     "These bushes grow like vines, the leaves of some bushes " +
	     "seem to give off a bitter smell.\n");
    add_item(({"hop","hops","leaf","leaves"}),
	     "There are several leafy vines of hop growing in the back "
	     +    "of the garden.\n");
    add_item("hut",
	     "This hut is more like a shed containing some tools. " +
	     "You notice some " +
	     "vines winding their way up the shed into the trees.\n");
    add_item("tools","These tools are old, rusty, and worthless.\n");
    add_item(({"vines","malt"}),"Some malt vines wind their way up the "
	     +    "shed and the trees.\n");
    add_item(({"ground","grass"}),"You think you saw something moving.\n");
    add_cmd_item(({"hut","shed"}),"enter",
		 "The hut is very small so you cannot enter it.\n");
    add_cmd_item(({"ground","grass","here"}),"dig","@@find_worm");
    add_cmd_item(({"hop","hops","leaf","leaves"}),"pick","@@pick_hop");
    add_cmd_item(({"malt","vine","vines"}),"pick","@@pick_malt");
    
    add_exit(ROOM + "street7","southwest",0,1);
    
    reset_room();
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
}



find_worm()
{
    if (can_dig)
    {
        say(QCTNAME(TP) + " picks something off the ground.\n");
        write("You find a little earthworm in the grass and pick it up.\n");
        clone_object(OBJ + "worm")->move(TP);
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
        clone_object(OBJ + "hop")->move(TP);
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
        clone_object(OBJ + "malt")->move(TP);
        has_malt--;
        return 1;
    }
    else
    {
        write("It seems there are no more grains left to pick here!\n");
        return 1;
    }
}

