/*
 *  /d/Genesis/start/human/obj/mapbox.c
 *
 *  This box provides maps of Sparkle for people who want them.
 *
 *  Created October 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>


/* Prototypes */
public void        create_object();


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("_sparkle_map_dispenser");
    add_name( ({ "dispenser" }) );
    add_adj( ({ "wooden", "map" }) );

    set_short("map dispenser");
    set_long("A map dispenser has been placed here in the middle of town."
     + " In it, you see many old crumpled maps. Perhaps you should <get>"
     + " one?\n");

    add_item( ({ "post", "sturdy post" }),
        "Quite sturdy. Its not going anywhere.\n");
    add_item( ({ "map", "maps", "crumpled map", "crumpled maps",
                 "old map", "old maps", "old crumpled map",
                 "old crumpled maps" }),
        "They are inside the dispenser. Perhaps you could <get> one?\n");

    setuid();
    seteuid(getuid());

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_M_NO_GET, "The dispenser is mounted on a sturdy post,"
     + " and cannot be taken.\n");
} /* create_object */


/*
 * Function name:        get_map
 * Description  :        allow players to take a map from the box
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
get_map(string arg)
{
    object map;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle it */
    }

    if (!parse_command(arg, ({}),
        "[the] [old] [paper] 'map' / 'maps' 'from' [the] [map]"
      + " 'dispenser'"))
    {
        if (parse_command(arg, ({}),
        "[the] [old] [paper] 'map' / 'maps'"))
        {
            write("The maps are inside the dispenser. You'll need to"
              + " <get map from dispenser> to take one.\n");
            return 1;
        }

        return 0; /* let the mudlib handle it */
    }

    if (present("_sparkle_map", this_player()))
    {
        write("You've already taken a copy. Type <i> to see a list of your"
          + " inventory. You can <exa map> to look at the map.\n");
        return 1;
    }

    map = clone_object(OBJ_DIR + "sparkle_map")->move(this_player());
    write("You take a map from the dispenser. You can examine it by"
      + " typing <exa map>.\n");

    return 1;
} /* get_map */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_map, "take");
    add_action(get_map, "get");
} /* init */