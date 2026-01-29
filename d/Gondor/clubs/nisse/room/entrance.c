/*
 *  /d/Gondor/clubs/nisse/room/entrance.c
 *
 *  The entrance to the Nisse Ohtar camp.
 *
 *  Deagol, March 2003
 *  Tigerlily, tweaked descriptions April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

inherit NISSE_LIB_DIR + "nisse_funcs";

mapping guards_defeaters = ([]);

/*
 *  Global variables
 */
int     s_revealed;     /* is a pathway to the south visible? */

/*
 *  Prototypes
 */
int     test_exit_south();
int     test_exit();
void    long_desc();

void
create_gondor()
{
    ::create_gondor();

    set_short("A clearing surrounded by a dense hawthorn hedge");
    set_long(&long_desc());

    sky_add_items();
    add_camp_tells();

    add_item(({"hedge", "hawthorn", "wall", "dense hawthorn hedge",
        "dense hedge", "dense hawthorn", "hawthorn hedge"}),
        "There is a dense, impenetrable wild hawthorn hedge that " +
        "surrounds this area. With sharp thorns and dark green leaves, " +
        "it forms a natural wall that protects the area from unwanted " +
        "visitors and provides a hiding place for birds and other small " +
        "creatures.\n");
    add_item(({"path", "covered path", "partially covered path"}),
        "The narrow path leads south through the foliage. You lean down to " +
        "examine crushed grass and mud on the path and notice footprints.\n");
    add_item(({"footprints", "footprint"}),
        "You see footprints that appear to have been made by smaller feet, " +
        "perhaps women's feet.\n");
    add_item(({"birds", "small creatures", "creatures"}),
        "Normally a place such as this would be full of birds and small " +
        "animals. While you sense they may be around, it is curiously " +
        "quiet.\n");
    add_item(({"clearing", "center"}),
        "It looks as though someone has tried to clear the central area of " +
        "trees and bushes, however, nature has taken its due with new " +
        "growth to the south.\n");
    add_item(({"scrub oaks", "ash trees", "oak", "trees", "tree", "ash"}),
        "Many seedling trees and tangled bracken seem to spring up around " +
        "the rotting tree stumps where someone tried to clear the area.\n");
    add_item(({"stumps", "tree stumps"}),
        "There are some stumps where larger oaks and ash trees have been " +
        "cut away to clear the area. This must have been a while ago, " +
        "since they are now rotting and covered in moss and fungus.\n");
    add_item(({"foliage", "undergrowth", "bracken", "brush"}),
        "The ground is covered in fern bracken and undergrowth. Dense " +
        "foliage blocks the view to the south.\n");

    add_exit(NISSE_ROOM_DIR + "path1", "south", test_exit_south, 0,
        test_exit);
    add_exit(LEB_DIR + "sroad/sr5", "east", 0, 0, 0);

    clone_object(NISSE_NPC_DIR + "guard")->move(TO);

    enable_reset(200);
}

/*
 *  Function name: long_desc
 *  Description  : Gives a long description of this room. It depends on
 *                 fact if a player is the Nisse member or not, or if
 *                 he/she defeated the guard before.
 */
string
long_desc()
{
    string text = "A dense hawthorn hedge encircles this area to the " +
        "north and east and serves as a wall to keep out prying eyes " +
        "and potential invaders." + sky_desc() + " With rumours of an " +
        "outlaw camp nearby, there is a wary feeling about the place, and " +
        "even the birds and small creatures seem subdued and quiet. It " +
        "looks as though someone has tried to raze a clearing in the " +
        "center, although there is a thick growth of scrub oak and ash " +
        "trees as well as other foliage growing defiantly. ";

    if (TP->query_nisse_level() || TP->query_wiz_level())
    {
        return text + "Your sharp hawklike eyes make out a partially " +
            "covered path through the brush leading to the south.\n";
    }

    if (!s_revealed)
    {
        return text + "The path to the south is blocked.\n";
    }

    return text + "A secret narrow pathway leads to the south.\n";
}

/*
 *  Function name: reset_room
 *  Description  : Keeps a guard on her place.
 */
void
reset_room()
{
    if (!present(NISSE_GUARD_ID, TO))
    {
        clone_object(NISSE_NPC_DIR + "guard")->move(TO);
    }

    return;
}

/*
 *  Function name: text_exit_south
 *  Description  : Tests if a player can enter the camp.
 *  Returns      : 0/1
 */
int
test_exit_south()
{
    object      player = TP;
    string      name = player->query_real_name();

    if (player->query_nisse_level() || player->query_wiz_level())
    {
        return 0;
    }

    guards_defeaters = restore_map(NISSE_LOG_DIR + "guards_defeaters");
    if (!mappingp(guards_defeaters))
    {
        guards_defeaters = ([]);
    }

    if (!guards_defeaters[name])
    {
        player->catch_msg("There is no obvious exit south.\n");
        return 1;
    }

    s_revealed = 1;
    return 0;
}

/*
 *  Function name: text_exit
 *  Description  : Tests if a player can see the entrance to the camp.
 *  Returns      : 0/1
 */
int
test_exit()
{
    object      player = TP;
    string      name = player->query_real_name();

    if (player->query_nisse_level() || player->query_wiz_level())
    {
        return 0;
    }

    guards_defeaters = restore_map(NISSE_LOG_DIR + "guards_defeaters");
    if (!mappingp(guards_defeaters))
    {
        guards_defeaters = ([]);
    }

    if (!guards_defeaters[name])
    {
        return 1;
    }

    s_revealed = 1;
    return 0;
}

/*
 *  Function name: enter_inv
 *  Description  : It's here just to keep the sky description up to date.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}
