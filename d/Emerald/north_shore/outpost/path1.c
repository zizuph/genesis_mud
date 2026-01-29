/*
 *  /d/Emerald/north_shore/outpost/path1.c
 *
 *  This path leads through the woods from the outpost on the North
 *  Shore towards the mountains where Ogres live.
 * 
 *  Created April 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/blackwall/delrimmon/lib/herb_search";

#include "/d/Emerald/common/guild/aod/defs.h"
#include "defs.h"

/* prototypes */
#define  XHERB_DIR             ("/d/Gondor/common/herbs/")
#define DEL_RIMMON_HERBS ({ \
                                 (XHERB_DIR + "blueberry"),\
                                 (XHERB_DIR + "clove"),\
                                 (XHERB_DIR + "dill"),\
                                 (XHERB_DIR + "fennel"),\
                                 (XHERB_DIR + "foxglove"),\
                                 (XHERB_DIR + "garlic"),\
                                 (XHERB_DIR + "ginger"),\
                                 (XHERB_DIR + "hemlock"),\
                                 (XHERB_DIR + "holly"),\
                                 (XHERB_DIR + "mint"),\
                                 (XHERB_DIR + "oregano"),\
                                 (XHERB_DIR + "rosemary"),\
                                 (XHERB_DIR + "sage"),\
                                 (XHERB_DIR + "tarragon"),\
                                 (XHERB_DIR + "thyme"),\
                              })

/* prototypes */
public void        create_emerald_room();
public void        reset_room();
public void        clone_npc(int number);
public int         check_exit();


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("a path within the confines of a dark woods");
    set_em_long("A path winds its way into the confines of a dark"
      + " wood here, twisting between the torn and damaged trunks"
      + " of the evergreen trees. The way grows lighter to the south."
      + " To the northeast, however, the forest grows more dense and"
      + " more disturbing.\n");

    add_item( ({ "path", "way", "trail" }),
        "It looks well trod. You notice some VERY large footprints.\n");
    add_item( ({ "print", "prints", "footprints", "foot print",
                 "foot prints", "large footprint", "large footprints",
                 "very large footprint", "very large footprints" }),
        "Larger than an elephant would make! What could be the"
      + " cause of such a thing?\n");
    add_item( ({ "ogre print", "ogre prints", "ogre footprint",
                 "ogre footprints" }),
        "That is a very good and disturbing possibility.\n");
    add_item( ({ "wood", "forest", "woods" }),
        "Boy, this place is dark and spooky.\n");
    add_item( ({ "dark", "dark forest", "dark wood", "dark woods", }),
        "And spooky!\n");
    add_item( ({ "spooky", "spooky wood", "spooky forest",
                 "spooky woods" }),
        "Oooooo ... shivers!\n");
    add_item( ({ "tree", "trees" }),
        "They are everywhere. Something has done some serious damage"
      + " to quite a few of them.\n");
    add_item( ({ "pine", "pine tree", "pine trees" }),
        "Pine trees are nice, aren't they. Ahh ... smells good. Wait,"
      + " something has damaged these pretty trees!\n");
    add_item( ({ "damage", "damaged tree", "damaged trees" }),
        "A number of the trees have been uprooted and left to rot."
      + " Others have been twisted in half! What monstrosity could"
      + " accomplish such feats?\n");
    add_item( ({ "evergreen", "evergreens", "evergreen tree",
                 "evergreen trees" }),
        "They look to be pine.\n");
    add_item( ({ "light", "lighter way", "south" }),
        "Much lighter. Maybe that would be a good way to go.\n");
    add_item( ({ "way" }),
        "South or northeast. You choose.\n");
    add_item( ({ "dense way", "disturbing way", "northeast" }),
        "Dense. Disturbing. Hmmmm ....\n");
    add_item( ({ "ground", "down", "floor" }),
        "Whoa ... look at those footprints!\n");
    add_item( ({ "up", "sky", }),
        "Hard to see through the trees, isn't it?\n");

    add_exit(AOD_ROOM_DIR + "lower_ground", "northeast",
             check_exit, 1, 0);
    add_exit("/d/Emerald/north_shore/outpost/gate04", "south");

    set_no_exit_msg( ({ "north", "east", "southeast", "southwest",
                        "west", "northwest" }),
        "The trees are too dense in that direction to allow travel.\n");

    set_up_herbs( ({ one_of_list(DEL_RIMMON_HERBS),
                     one_of_list(DEL_RIMMON_HERBS),
                     one_of_list(DEL_RIMMON_HERBS) }),
                          ({ "ground", "bush", "tree",
                             "undergrowth", "trees", "forest",
                             "shrub", "shrubs", "bushes", }),
                  3 );

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        reset_room
 * Description  :        make sure the room has herbs from time to time
 */
public void
reset_room()
{
    clone_npc(1 + random(3));
} /* reset_room */


/*
 * Function name:        clone_npc
 * Description  :        bring the right amount of npcs into the room
 * Arguments    :        int number - the amount of clones we want
 */
public void
clone_npc(int number)
{
    int     i, n;
    string  filename = OUTPOST1_NPC + "woodcutter";
    object *guard = allocate(number);

    if (present("_elf_woodcutter", this_object()))
    {
        return;
    }

    for (i = 0, n = sizeof(guard); i < n; i++)
    {
        if (!objectp(guard[i]))
        {
            guard[i] = clone_object(filename);
            guard[i]->move_living("from the void", this_object());
        }
    }
    return;
} /* clone_npc */


public int
check_exit()
{
    if (!IS_OGRE(this_player()))
    {
        TELL_G("\n\n" + sprintf("%|80s", "--**-- "
          + capitalize(this_player()->query_real_name())
          + " approaches THE GUILD! -**-\n\n"));
    }

    return 0;
}