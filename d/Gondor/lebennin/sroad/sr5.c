/*
 *
 *  Deagol, March 2003
 *  Tigerlily, added a few descriptions April, 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/clubs/nisse/lib/nisse_funcs.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/nisse/nisse_defs.h"

string  long_desc();

mapping camp_enter = ([]);
int     test_west_exit();
int	test_exit();

void
create_gondor()
{
    ::create_gondor();

    set_short("Path through a field in Lebennin");
    set_long(&long_desc());

    add_item("path", &long());
    add_item(({"field", "oats", "barley", "crops", "crop"}),
        "Oats and barley grow abundantly on either side " +
        "of the path.\n");
    add_item(({"hedge", "tall hedge"}),
        "A tall dark-green hedge marks the boundary of " +
        "the field to the west. It is formed from " +
        "closely interlocked hawthorn trees.\n");
    add_item(({"hawthorn", "hawthorn trees", "trees"}),
        "The hawthorn trees stand tall and dense and are " +
        "covered in sharp thorns.\n");
    add_item(({"road", "paved road"}),
        "The path intersects with a ancient paved road to " +
        "the southeast from here.\n");
    add_item(({"pelargir", "Pelargir"}),
        "The great walled city lies farther to the " +
        "east at the mouth of the river Anduin.\n");
    add_item(({"river", "Anduin"}),
        "The Anduin is close to its end here " +
        "and several miles wide. Not far from here, " +
        "it will reach the Mouths of the Anduin, or " +
        "the Ethir Anduin, where it divides into " +
        "many smaller river courses before it finally " +
        "reaches the Sea in the Bay of Belfalas.\n");

    add_exit(LEB_DIR + "sroad/sr4", "northeast", 0, 0);
    add_exit("/d/Gondor/clubs/nisse/room/entrance", "west", test_exit, 0,
        test_west_exit);
    add_exit("/d/Gondor/lebennin/sroad/sr5", "southwest", "@@block_exit", 2);

    add_prop(OBJ_S_SEARCH_FUN, "reveal_camp");
    add_prop(OBJ_I_SEARCH_TIME, 1);
}

/*
 *  Function name: long_desc
 *  Description  : Gives a long description of this room. It depends on
 *                 fact if a player is the Nisse member or not.
 */
string
long_desc()
{
    string text = "A path across a field in the southern " +
        "parts of Lebennin in Gondor." + sky_desc() +
        " To the west a tall dark green hedge " +
        "marks the boundary of the field. Some distance " +
        "to the east stand the walls of " +
        "Pelargir on the river Anduin. An abundant " +
        "crop of oats and barley grows on either " +
        "side of the path that continues to " +
        "the southwest.\n";

    return text;
}

int
test_west_exit()
{
    if (!camp_enter[TP->query_real_name()] && !TP->query_wiz_level())
    {
//        TP->catch_msg("There is no obvious exit west.\n");
        return 1;
    }

    return 0;
}

int
test_exit()
{
    if (!camp_enter[TP->query_real_name()] && !TP->query_wiz_level())
    {
        TP->catch_msg("There is no obvious exit west.\n");
        return 1;
    }

    return 0;
}

string
reveal_camp(object tp, string str)
{
    object player = this_player();

    if (str == "hedge" || str == "tall dark green hedge" ||
        str == "green hedge" || str == "dark hedge" || str == "tall hedge")
    {
        camp_enter[TP->query_real_name()] = 1;
        return "You find a hidden exit that leads to the west.\n";
    }

    return 0;
}

int
block_exit()
{
   if (TP->query_wiz_level())
   {
      write("The road south is still closed for mortals!\n\n");
      return 0;
   }

   write("The road southwest is closed by order of the Steward of Gondor.\n");
   return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}
