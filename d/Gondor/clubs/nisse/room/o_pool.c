/*
 *  /d/Gondor/clubs/nisse/room/o_pool.c
 *
 *  The ceremony pool in the camp of the Nisse Ohtar.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

inherit NISSE_LIB_DIR + "nisse_funcs";

/*
 *  Prototypes
 */
int	climb_willow(string str);
int	take_stone(object tp, string str);
int	test_exit_hollow();
int	test_exit();
string	exa_willow();

void
create_gondor()
{
    ::create_gondor();

    set_short("A pool in the Nisse Ohtar camp");
    set_long("On the shore of a tranquil pool. Fresh, green rye grass " +
        "grows upon the shores. On the left shore of the pool a large " +
        "willow tree flourishes. On the shore near you there is a painted " +
        "tent.@@sky_desc@@ There are two dusty paths leading away " +
        "from here, back toward the rest of the encampment. The northeast " +
        "path fades into some dark green bushes while the other winds off " +
        "toward the northwest. On the other side of a tranquil pool stands " +
        "a huge painted tent.\n");

    sky_add_items();
    add_pool_tells();
    add_tent_tells();
        
    add_item(({"pool", "tranquil pool"}),
        "You look closer at the tranquil pool. The pool is an irregular " +
        "shape with sparkling, crystal clear water. The surface of the " +
        "water is calm and perfectly flat as the light glitters " +
        "across it.\n");
    add_item(({"water"}),
        "You look closer at the tranquil pool. The pool has an irregular " +
        "shape and the water is sparkling and crystal clear. The surface " +
        "of the water is calm, perfectly flat and glittering.\n");
    add_item(({"willow", "willow tree", "willow-tree", "tree", "large willow",
	"large willow tree", "large willow-tree"}), &exa_willow());
    add_item(({"root", "roots"}),
        "The roots are strong and healthy. The roots you can see are " +
        "exposed as they reach to the pool for nourishment.\n");
    add_item(({"path", "paths", "pathway", "pathways"}),
        "You lean down and smell the ground briefly. Examining the path " +
        "you find many footprints, and this fact makes you certain that " +
        "it is used quite often.\n");
    add_item(({"ground"}),
        "The ground is dusty and covered in footprints.\n");
    add_item(({"footprint", "footprints"}),
        "You notice a variety of footprints, but most of them seem to be " +
        "made by smaller feet.\n");
    add_item(({"northeast path", "northeast pathway"}),
        "The northeast pathway fades off into some bushes and is covered " +
        "in footprints.\n");
    add_item(({"northwest path", "northwest pathway"}),
        "The northwest pathway winds off toward the distance and is " +
        "covered in footprints.\n");
    add_item(({"grass", "rye grass", "green grass", "green rye grass"}),
        "You look closer at the green rye grass growing wild around this " +
        "area. It flanks the tranquil pool and it gets its vibrant green " +
        "colour probably because of the moisture from the pool. The grass " +
        "is so tall your feet seem to vanish within it.\n");
    add_item(({"bush", "dark bush", "green bush", "dark green bush",
        "bushes", "dark bushes", "green bushes", "dark green bushes"}),
        "The dark green bushes arch over the pathway that goes to the " +
        "northeast. The lush colour and leaves of the bushes are probably " +
        "the result of their proximity to clean water.\n");
    add_item(({"shore", "left shore"}), "You are standing on the shore " +
        "of the pond which is covered in green rye grass. On the left " +
        "shore of the pool stands a large willow tree.\n");
    add_item(({"tent", "painted tent", "huge painted tent"}),
        "You look closer at the painted tent. The tent before you, though " +
        "obviously worn, is in perfect condition. The painted hawks on the " +
        "sides of the tent are engaged in some type of combat. This looks " +
        "like the tent of a warrior. A round hide flap is draped over the " +
        "entrance to the tent.\n");
    add_item(({"hawks"}),
        "The hawks are engaged in some type of combat. One of the hawks " +
        "is light brown while the other is a deep copper colour.\n");
    add_item(({"entrance"}),
        "The entrance to this tent is well trodden like the pathways " +
        "around the camp.\n");

    add_prop(OBJ_S_SEARCH_FUN, "take_stone");
    add_prop(OBJ_I_SEARCH_TIME, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    add_exit(NISSE_ROOM_DIR + "path3", "northwest", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "path4", "northeast", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "neit_tent", "north", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "hollow", "hollow", test_exit_hollow, 0,
        test_exit);

    set_drink_from(({"water", "pool", "tranquil pool"}));
}

/*
 *  Function name: exa_willow
 *  Description  : Gives a different description of a willow. It depends
 *                 on if a player is a Nisse or not.
 *  Returns      : the willow tree description
 */
string
exa_willow()
{
    string text =
        "You decide to examine the large willow tree. Its roots go down " +
        "to the pool which would explain why it looks so healthy and lush. " +
        "The tree seems to be climbable.";

    if (TP->query_nisse_level() == 0 && TP->query_wiz_level() == 0)
    {
        return text + "\n";
    }

    return text + " There is a hollow that seems to be enterable.\n";
}

/*
 *  Function name: climb_willow
 *  Description  : This routine is called when the player climbs a tree.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 1 if success, 0 if not
 */
int
climb_willow(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "[a] [the] [large] [willow] [tree]"))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    /* only two persons can be on the tree at once */
    if ((NISSE_ROOM_DIR + "willow")->query_livings() == 2)
    {
        notify_fail("You failed to climb the willow. Somebody is there " +
            "already.\n");
        return 0; 
    }

    write("You climb the large willow tree skillfully.\n");
    say(QCTNAME(TP) + " climbs the large willow tree skillfully.\n");
    tell_room(NISSE_ROOM_DIR + "willow", QCNAME(TP) + " comes climbing " +
        "the tree.\n");
    TP->move_living("M", NISSE_ROOM_DIR + "willow", 1, 0);
    return 1;
}

/*
 *  Function name: enter_pool
 *  Description  : This function is called when a player tries to enter
 *                 the pool. It's not possible and this possibility is
 *                 here just to keep an atmosphere.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0 or 1
 */
int
enter_pool(string str)
{
    if (!strlen(str) || str != "pool" && str != "tranquil pool")
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    write("How you dare to enter the ceremony pool? The Nisse Ohtar use " +
        "it for their ceremonies and it is sacred.\n");
    say(QCTNAME(TP) + " tries to enter the tranquil pool, but backs away " +
        "immediately. " + CAP(PRONOUN(TP)) + " seems to be scared by " +
        "something.\n");
    return 1;
}

/*
 *  Function name: take_stone
 *  Description  : This routine is called when a player takes a stone. It
 *                 clones an object (a small stone) into the inventory of
 *                 this player.
 *  Arguments    : object tp, string str - as entered by the player
 *  Returns      : 0 if not success, a string if success
 */
string
take_stone(object tp, string str)
{
    object player = this_player();

    if (str == "grass" || str == "bent-grass")
    {
	if (tp->query_nisse_level() != 0)
	{
            return 0;
	}

        clone_object(NISSE_OBJ_DIR + "stone")->move(tp, 1);
        say(QCTNAME(tp) + " finds something.\n");
        return "You find a small black stone.\n";
    }

    return 0;
}

/*
 *  Function name: test_exit_hollow
 *  Description  : Tests if a player can enter the hollow. Only the Nisse
 *                 members and the wizard are able to do so.
 *  Returns      : 0/1
 */
int
test_exit_hollow()
{
    object      player = TP;

    if (player->query_nisse_level() || player->query_wiz_level())
    {
        tell_room(NISSE_ROOM_DIR + "hollow", QCTNAME(player) + " enters " +
            "through the hollow.\n");
        player->move_living("M", NISSE_ROOM_DIR + "hollow", 1, 0);
        tell_room(NISSE_ROOM_DIR + "o_pool", QCTNAME(player) + " comes " +
            "near the willow tree and disappears suddenly.\n");
        return 1;
    }

    /* We don't want others to know here is an exit 'hollow' */
    player->catch_msg("What ?\n");
    return 1;
}

/*
 *  Function name: test_exit
 *  Description  : Tests if a player can see the hollow. Only the Nisse
 *                 members and the wizard are able to see it as an obvisous
 *                 exit.
 *  Returns      : 0/1
 */
int
test_exit()
{
    object      player = TP;

    if (player->query_nisse_level() || player->query_wiz_level())
    {
        return 0;
    }

    return 1;
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

void
init()
{
    ::init();

    init_drink();
    add_action(climb_willow, "climb");
    add_action(enter_pool, "enter");
}
