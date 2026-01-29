/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/n_cave.c
 *
 *  A corridor rounds a bend here, travelling to the south and northwest
 *  deep within a cliffside along the western shores of Del Rimmon
 *  in the Blackwall Mountains of Emerald.
 *
 *  Copyright (c) September 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void           create_del_rimmon();
public void    init();
public int     do_listen(string arg);
public string  do_hear();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
void
create_del_rimmon()
{
    set_short("within a dark passageway which rounds a bend to the"
            + " northwest");
    set_long(BSN("A heavy silence hangs in this passageway, which"
               + " extends into darkness in both directions. To the"
               + " northwest, the corridor rounds a bend before"
               + " travelling onward. The way to the south is"
               + " straight."));

    add_item( ({"silence", "heavy silence"}), BSN(do_hear()) );
    add_item( ({"here", "passageway", "passageways", "corridor",
                "corridors"}), BSN(
        "Careful strokes mark the walls where this passageway has"
      + " been carved from the stone within the cliffs. Shadows"
      + " encroach to the south, where the corridor follows a"
      + " straight path, and to the northwest, as it"
      + " disappears around a bend."));
    add_item( ({"stroke", "strokes", "careful stroke",
                "careful strokes"}), BSN(
        "These strokes show the toil which was undertaken to craft"
      + " these passageways. They show much skill, but little"
      + " artistry."));
    add_item( ({"stone", "stones"}), BSN(
        "The stone which makes up the walls of this passageway are"
      + " scored with many careful strokes, which bear testimony to"
      + " those who created this place."));
    add_item( ({"wall", "walls", "walls of this passageway"}), BSN(
        "The walls of this corridor are flat and level, having been"
      + " hewn from the stone of the cliffs many ages ago by"
      + " skilled hands."));
    add_item( ({"darkness", "shadow", "shadows", "dark"}), BSN(
        "Shadows crowd in to the northwest and south, where the"
      + " corridor continues in both directions."));
    add_item( ({"northwest", "bend"}), BSN(
        "The corridor turns a bend to the northwest, disappearing"
      + " into darkness."));
    add_item( ({"south", "way to the south", "straight path"}), BSN(
        "The corridor runs directly to the south in a straight path"
      + " which disappears into the shadows there."));
    add_item( ({"cliffs", "cliff"}), BSN(
        "The cliffs themselves are not visible from here."));
    add_item( ({"sun", "moon", "star", "stars", "sky"}), BSN(
        "The sky is not visible from here, deep within the side"
      + " of the cliffs."));
    add_item( ({"ceiling", "roof", "up"}), BSN(
        "The roof of this corridor appears to be gradually sloping"
      + " downward the farther one travels north."));
    add_item( ({"floor", "ground", "down"}), BSN(
        "The ground is covered with quite a bit of dust and debris"
      + " which has evidently collected over many centuries."));
    add_item( ({"dust"}), BSN(
        "Dust lays heavily upon the floor of this corridor, where"
      + " it looks to have collected over a very long period of time."
      + " Footprints have made their way through the dust."));
    add_item( ({"footprint", "footprints", "print"}), BSN(
        "The footprints are confused and muddled, seemingly having"
      + " been made from both directions. It is not clear who or"
      + " what may have made these, but they do indeed look fresh."));
    add_item( ({"debris"}), BSN(
        "The floor of this corridor is layered lightly with small"
      + " bits of stone and crumbled fragments which must have"
      + " collected here over time."));
    add_item( ({"stone", "bits", "bits of stone", "bit of stone",
                "stones", "small bits", "small bits of stone",
                "fragment", "fragments", "crumbled fragment",
                "crumbled fragments"}), BSN(
        "Crumbled fragments lay scattered about the floor. It looks"
      + " as if they may have fallen from the walls or ceiling."));


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/dead_end", "northwest");
    add_exit(DELRIMMON_DIR + "lakeside/caves/cave_fork", "south");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "southwest", "west" }),
        "You are blocked by the corridor walls.\n");
} /* create_del_rimmon */

/*
 * Function name:        init
 * Description  :        add actions to the player (listen)
 */
public void
init()
{
    ::init();

    add_action(do_listen, "listen");
} /* init */

/*
 * Function name:        do_listen
 * Description  :        handles attempts to listen
 * Arguments    :        arg -- what the player typed
 * Returns      :        1 -- success, 0 -- failure
 */
public int
do_listen(string arg)
{
    if (!strlen(arg))       /* no arg */
    {
        WRITE(do_hear());
        return 1;
    }

    if (!strlen(arg) || !parse_command(arg, ({}),
        "[to] [the] [heavy] 'silence' / 'corridor' / 'passageway'"))
    {
        notify_fail;      /* the mudlib takes care of this already */
        return 0;
    }

    WRITE(do_hear());
    return 1;
} /* do_listen */

/*
 * Function name:        do_hear
 * Description  :        print the text for what the player hears
 */
public string
do_hear()
{
    return "Deep within this cliffside, you notice not so much noise, as"
         + " the complete absence of sound - normal outdoor noises"
         + " which are so often taken for granted.";
} /* do_hear */
