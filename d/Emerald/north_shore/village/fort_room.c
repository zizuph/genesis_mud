/*
 *  /d/Emerald/north_shore/village/fort_room.c
 *
 *  This is a room where some of the local elven children have taken
 *  to building and playing in the woods. There is a tree fort here.
 *  How unfortunate that they have selected a location so close to the
 *  Ogres of the Mountains!
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include "/d/Emerald/common/guild/aod/defs.h"
#include <macros.h>

/* Definitions */
#define            RIPPED_TREE   "_emerald_i_ripped_tree"

/* Prototypes */
public void        create_emerald_room();
public string      describe(string what);
public int         rip_tree(string arg);
public void        init();
public int         climb_fort(string arg);
public int         check_ogre();
public int         kick_tree(string arg);


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("in an oak grove where a small tree fort has been built");
    set_em_long("@@describe|room@@");

    add_item( ({ "grove", "groves", "oak grove", "grove of oak",
                 "grove of oak trees" }), &describe("grove"));
    add_item( ({ "sizes" }), &describe("oaksize"));
    add_item( ({ "oaks", "oak trees", "trees" }), &describe("oaks"));
    add_item( ({ "little oak", "little oaks", "small oak", "small oaks",
                 "little tree", "little trees", "small tree",
                 "small trees", "smaller tree", "smaller oak",
                 "smaller oaks", "little one", "little ones" }),
             &describe("small"));
    add_item( ({ "wood", "woods", "dark wood", "dark woods",
                 "darker wood", "darker woods", "northwest",
                 "dark forest" }),
        "The forest to the northwest looks rather forboding. There"
      + " is a darkness that hangs over the trees, and you get the"
      + " feeling that something lives beyond that border that would"
      + " be terrifying to meet.\n");
    add_item( ({ "dark", "darkness" }),
        "The darkness to the northwest is almost palpable.\n");
    add_item( ({ "trail", "bit of a trail", "path", "soil", "ground",
                 "down", "earth", "floor", "soil" }),
        "A trail runs northwest to southeast here, apparently having"
      + " been made by whoever built the tree fort. It grows rather"
      + " obscure as it approaches the woods. Apparently people don't"
      + " go that way much.\n");
    add_item( ({ "trunk", "trunks" }),
        "The trunks of the trees are covered in bark and shaggy"
      + " moss.\n");
    add_item( ({ "bark" }),
        "It is greyish-brown and covered with shaggy green moss.\n");
    add_item( ({ "moss", "shaggy moss", "green moss",
                 "shaggy green moss", "green shaggy moss" }),
        "You've seen this type of moss growing on oak trees before. It"
      + " is thick and spongy to the touch.\n");
    add_item( ({ "oak", "tree", "large oak", "large tree",
                 "particularly large oak", "particularly large tree",
                 "ancient oak", "ancient oaks", "ancient tree",
                 "ancient trees", "oak tree", "large oak tree" }),
          &describe("big tree"));
    add_item( ({ "fort", "tree fort", "large fort", "large tree fort" }),
          &describe("fort"));
    add_item( ({ "up", "sky", "blue sky" }),
        "The blue sky peeks now and again from between the leaves of"
      + " the oak trees high above.\n");
    add_item( ({ "leaf", "leaves" }),
        "Where there be oaks, there be leaves. Here, there be both!\n");
    add_item( ({ "limbs", "limb", "branch", "branches" }),
        "Trees tend to have branches. No exceptions here.\n");
    add_item( ({ "low limb", "low limbs", "lower limb", "lower limbs",
                 "lowest limb", "lowest limbs" }),
        "The lowest limbs of the large oak tree support the tree"
      + " fort. Whoever built this structure chose carefully where to"
      + " place it.\n");
    add_item( ({ "individual oak", "individual oaks" }),
        "Yes ... it is important to treat each oak as an individual."
      + " They get their feelings hurt otherwise.\n");
    add_item( ({ "structure" }),
        "Such a proud structure. Ahh ... youth.\n");
    add_item( ({ "proud structure" }),
        "Proud ... very proud.\n");
    add_item( ({ "village", "nearby village" }),
        "Though nearby, it isn't visible from here in the grove.\n");
    add_item( ({ "plank", "planks", "wooden plank", "wooden planks",
                 "wood plank", "wood planks" }),
        "Wooden planks have been nailed to the tree, making it"
      + " possible for people to climb up to the tree fort.\n");

    add_exit("in_fort", "up", check_ogre, 1, 1);

    setuid();
    seteuid(getuid());
} /* create_emerald_room */


/*
 * Function name:        describe
 * Description  :        provide some variable descriptions for
 *                       various things in the room
 * Arguments    :        string what - the thing we want to describe
 * Returns      :        string - the description
 */
public string
describe(string what)
{
    string  ogre_text = "";
    int     ogre = IS_OGRE(this_player());

    switch(what)
    {
        case "room":
            if (ogre)
            {
                ogre_text = "Hmmm ... your ogre brain seems to think that"
                  + " this tree looks perfectly kickable.";
            }

            return "You stand in a grove of oak trees on the outskirts"
              + " of a forest which grows more dark and dense to the"
              + " northwest. A bit of a trail has been beaten in the"
              + " soil here, leading beside a particularly large oak"
              + " which houses a small tree fort that has been built"
              + " in its lowest limbs. " + ogre_text + "Southeast,"
              + " the trail grows wider, leading out of the trees."
              + " It also leads into the darker woods northwest, though"
              + " there is a very ominous feeling that way.\n";
            break;
        case "grove":
            if (ogre)
            {
                ogre_text = "Oooo ... the little ones look like they might"
                  + " make nice weapons!";
            }

            return "This grove of oak trees extends out from the darker"
              + " woods which loom to the northwest. The individual"
              + " oaks grow spread out from one another in all"
              + " assortment of sizes. " + ogre_text + "\n";
            break;
        case "oaksize":
            if (ogre)
            {
                ogre_text = "Oooo ... the little ones look like they might"
                  + " make nice weapons!";
            }

            return "The oaks grow both large and small. " + ogre_text
              + "\n";
            break;
        case "oaks":
            if (ogre)
            {
                ogre_text = "It wouldn't be hard at all to tear these"
                  + " little ones out of the ground, I bet!";
            }

            return "Oaks grow all around you here. Some are ancient,"
              + " with trunks up to five feet across. Most are more"
              + " moderate in size. There are also quite a few little"
              + " ones that grow straight and thin from the ground. "
              + ogre_text + "\n";
            break;
        case "small":
            if (ogre)
            {
                ogre_text = "Ho ho ho ... these look perfect for smashing"
                  + " faces with! Maybe you could tear one out of"
                  + " the ground.";
            }

            return "The smaller oaks are typically six inches to a foot"
              + " across at the base, and fairly straight. "
              + ogre_text + "\n";
            break;
        case "big tree":
            if (ogre)
            {
                ogre_text = "You wonder what would happen if you gave this"
                  + " tree a good kick!";
            }

            return "One particularly large oak tree stands apart from"
              + " the others. The path seems to run right up beside it"
              + " and for good reason - it houses a large tree fort!"
              + " This must be where the local boys from the nearby"
              + " village come to play in their idle time. "
              + ogre_text + "\n";
            break;
        case "fort":
            if (ogre)
            {
                ogre_text = "Hmmm ... maybe there are some young elflings"
                  + " up there to smash! A good kick to the tree"
                  + " would probably get 'em down here if so.";
            }

            return "Ahh ... the joy of any young lad! This fort has been"
              + " expertly constructed in the lowest limbs of a large"
              + " oak tree which stands at the side of the path. Surely"
              + " there was adult supervision in the construction of"
              + " this proud structure. Planks have been nailed to the"
              + " trunk of the tree, leading up to the fort. "
              + ogre_text + "\n";
            break;
    }

    return "";
} /* describe */


/*
 * Function name:        rip_tree
 * Description  :        allow ogres to rip trees out of the ground
 *                       here.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success
 *                           0 - failure
 */
public int
rip_tree(string arg)
{
    int     ripped_prop = this_player()->query_prop(RIPPED_TREE);
    object  tree;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [out] [the] [small] [smaller] [oak] 'tree' / 'trees'"
      + " [up] [out] [of] [from] [the] [ground]") &&
        !parse_command(arg, ({}),
        "[up] [out] [the] [small] [smaller] 'oak' / 'oaks' [tree]"
      + " [trees] [up] [out] [of] [from] [the] [ground]"))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (!IS_OGRE(this_player()))
    {
        write("Who do you think you are, an ogre?\n");
        return 1;
    }

    if (ripped_prop > 1)
    {
        write("You've probably ripped enough trees out of the ground"
          + " for now.\n");
        return 1;
    }

    write("Grasping one of the smaller oaks by the trunk, you heave"
      + " upward with your massive shoulders and tear it out of the"
      + " ground, roots and all!\n");
    tell_room(this_object(), QCTNAME(this_player()) + " grasps one"
      + " of the smaller oaks by the trunk and heaves upward with "
      + this_player()->query_possessive() + " mighty shoulders, tearing"
      + " it out of the ground, roots and all!\n", this_player());

    tree = clone_object("/d/Emerald/north_shore/village/wep/tree");
//  this_player()->add_prop(RIPPED_TREE, (ripped_prop + 1));

    if (!tree->move(this_player()))
    {
        return 1;
    }

    /* move to player failed, so we drop it at their feet with an
     * appropriate message */
    write("Ooof! You are carrying too much. You fumble the tree and"
      + " it falls to the ground.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " fumbles the"
      + " tree and it falls to the earth.\n", this_player());
    tree->move(this_object());

    return 1;
} /* rip_tree */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(rip_tree, "rip");
    add_action(rip_tree, "tear");
    add_action(climb_fort, "climb");
    add_action(kick_tree, "kick");
} /* init */


/*
 * Function name:        climb_fort
 * Description  :        allow people to try to climb up to the tree
 *                       fort
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
climb_fort(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [in] [to] [into] [the] 'tree' / 'oak'") &&
        !parse_command(arg, ({}),
        "[up] [in] [to] [into] [the] [oak] 'tree'") &&
        !parse_command(arg, ({}),
        "[up] [in] [to] [into] [the] [tree] 'fort' / 'tree-fort'"))
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would just move you up here using command()."
          + " Since you are a wizard, that won't work. Just type <up>"
          + " yourself, please.\n");
        return 1;
    }

    this_player()->command("up");
    return 1;
} /* climb_fort */


/*
 * Function name:        check_ogre
 * Description  :        ogres cannot climb the tree. Allow others.
 * Returns      :        int 0 - allow passage
 *                       int 1 - don't allow
 */
public int
check_ogre()
{
    if (!IS_OGRE(this_player()))
    {
        return 0;
    }

    write("You are much to big to get up there. You could probably"
      + " just kick the tree and see what falls out.\n");
    return 1;
} /* check_ogre */


/*
 * Function name:        kick_tree
 * Description  :        Allow people to kick the tree. If an Ogre does
 *                       it, anyone in the fort comes crashing to
 *                       the ground.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success,
 *                           0 - failure
 */
public int
kick_tree(string arg)
{
    object    fort = find_object("/d/Emerald/north_shore/village/in_fort");

    if (!strlen(arg))
    {
        return 0; /* the mudlib can handle kick */
    }

    if (!parse_command(arg, ({}),
        "[the] [particularly] [large] [ancient] 'tree' / 'oak'") &&
        !parse_command(arg, ({}),
        "[the] [particularly] [large] [ancient] [oak] 'tree'"))
    {
        return 0; /* mudlib */
    }

    if (!IS_OGRE(this_player()))
    {
        write("You haul off and kick the tree. Aaargh! Your toes"
          + " feel the pain!\n");
        tell_room(this_object(), QCTNAME(this_player()) + " gives"
          + " the large oak tree a swift kick, and then winces"
          + " in pain!\n", this_player());

        return 1;
    }

    write("You haul off and boot the tree with your mighty foot! The"
      + " entire trunk quivers and you hear things rattling around"
      + " in the tree fort.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " hauls off"
      + " and kicks the large oak tree with a mighty foot! The entire"
      + " trunk quivers and you hear things rattling around in the"
      + " tree fort above.\n", this_player());

    fort->get_kicked();
    return 1;
} /* kick_tree */
