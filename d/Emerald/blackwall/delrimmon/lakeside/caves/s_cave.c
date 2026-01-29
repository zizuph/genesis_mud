/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/s_cave.c
 * 
 *  This is the southern fork of a cave deep within the cliffs of the
 *  Blackwall Mountains in Emerald. These passageways were carved by the
 *  Elves of Telberin in ages long past.
 *
 *  Copyright (c) November 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";

#include <filter_funs.h>     /* for FILTER_LIVE */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    ORC_ROOM        (DELRIMMON_DIR + "lakeside/caves/barracks")

/* global variables */
public object  Orc_Room;      /* room to check for orcs */

/* prototypes */
void           create_del_rimmon();
public string  describe();
public string  glow_desc();
public int     orcs_present();
public void    init();
public int     random_noise();
public int     fire_present();
public string  my_dark_msg();

/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
void
create_del_rimmon()
{
    set_short("a corridor deep within the cliffs of the Blackwall Mountains");
    set_long(describe);

    add_item( ({"sky", "sun", "star", "stars", "moon"}), BSN(
        "The sky is not visible from these dark tunnels, deep within"
      + " the cliffs."));
    add_item( ({"cliff", "cliffs"}), BSN(
        "Though within them, you are not able to view the cliffs from"
      + " here, merely the stone which comprises their foundations."));
    add_item( ({"wall", "walls", "rough wall", "rough walls",
                "roughly hewn wall", "roughly hewl walls"}), BSN(
        "The walls of this passage, while rough, are extremely flat."
      + " Many grooves along their surfaces bear testimony to the"
      + " hands and tools that carved them from the stone."));
    add_item( ({"groove", "grooves"}), BSN(
        "The grooves in the walls remain unpolished, giving no"
      + " indication that any thought for beauty was in the minds"
      + " of those who carved this passage."));
    add_item( ({"hands", "hand", "tools", "tool",
                "hands and tools"}), BSN(
        "Surely this passage was carved in a bygone age. The tools"
      + " are lost, and the hands gone to dust."));
    add_item( ({"stone", "stone surface", "stone surfaces"}), BSN(
        "The stone is dark and rough, hewn many years ago to"
      + " create these passages."));
    add_item( ({"passage", "passages", "passageway", "passageways",
                "corridor", "corridors", "tunnel", "tunnels"}), BSN(
        "The passageway turns a corner here, running both to the"
      + " north and to the southwest."));
    add_item( ({"floor", "ground"}), BSN(
        "The floor of the passageway is flat, much like the walls"
      + " and ceiling. It, however, is covered by a good deal of"
      + " dust."));
    add_item( ({"dust", "print", "prints", "footprint", "footprints",
                "foot print", "foot prints"}), BSN(
        "The dust along the ground appears to be disturbed. Many"
      + " feet have travelled this way."));
    add_item( ({"feet", "foot", "footprint", "footsteps"}), BSN(
        "The footprints in the dust are many and confusing. There"
      + " are none which reveal much more than the fact that this"
      + " corridor has been heavily travelled very recently."));
    add_item( ({"ceiling", "roof", "up"}), BSN(
        "The ceiling runs level with the floor in both directions."));
    add_item( ({"direction", "directions"}), BSN(
        "The tunnel runs to the north and to the southwest from"
      + " here."));
    add_item( ({"turn", "bend"}), BSN(
        "The bend in the corridor is very angular, presenting a"
      + " marked edge in the walls of the corridor."));
    add_item( ({"edge", "marked edge"}), BSN(
        "The edge is very precise and sudden. It would seem that"
      + " the such accuracy of design would require a sophisticated"
      + " level of skill."));
    add_item( ({"glow", "dull glow"}), glow_desc);
    add_item( ({"path", "straight path"}), BSN(
        "The way to the north is straight, running into the shadows"
      + " in that direction. Footprints are visible in the dust"
      + " along the ground."));
    add_item( ({"shadow", "shadows", "dark", "darkness"}), BSN(
        "In these dark tunnels, shadows close in all around, making"
      + " it difficult to view great distances."));

    set_noise_interval(10, 15);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, my_dark_msg);

    add_exit(DELRIMMON_DIR + "lakeside/caves/cave_fork", "north");
    add_exit(DELRIMMON_DIR + "lakeside/caves/barracks", "southwest");

    set_no_exit_msg( ({ "northeast", "east", "southeast", "south",
                        "west", "northwest" }),
        "Hard stone walls block your movement.\n");
} /* create_del_rimmon */

/*
 * Function name:        describe
 * Description  :        provides a long description for the room,
 *                       varying dependent on whether the bonfire
 *                       in the room to the southwest is lit
 * Arguments    :        none
 * Returns      :        string -- the room description
 */
public string
describe()
{
    string  corridor_desc = "The roughly hewn walls of this corridor"
                          + " round a bend here, turning to the"
                          + " southwest";

    if (fire_present())
    {
        corridor_desc += " where a dull glow illuminates the stone"
                       + " surfaces.";
    }

    else
    {
        corridor_desc += " where the way is dark.";
    }

    corridor_desc += " To the north, the tunnel runs a straight"
                   + " path into the shadows.";

    return BSN(corridor_desc);
} /* describe */

/*
 * Function name:        glow_desc
 * Description  :        provide a description for the glow on the
 *                       walls
 * Returns      :        string - the glow description
 */
public string
glow_desc()
{
    string  glowtxt;

    if (fire_present())
    {
        glowtxt = "The stone surfaces of the walls to the southwest"
                + " flicker lightly with a dull glow.";
    }

    else
    {
        glowtxt = "You find no " + query_exa_arg() + ".";
    }

    return BSN(glowtxt);
} /* glow_desc */

/*
 * Function name:        orcs_present
 * Description  :        tells us whether or not adjascent rooms
 *                       have any orcs in them
 * Arguments    :        none
 * Returns      :        the number of orcs found
 */
public int
orcs_present()
{
    object  *orcs;

    if (!objectp(Orc_Room))
    {
        FIX_EUID
        ORC_ROOM->short();
        if (!objectp(Orc_Room = find_object(ORC_ROOM)))
        {
            /* oops. can't load the room. oh, well. */
            return 0;
        }
    }

    orcs = FILTER_LIVE(all_inventory(Orc_Room));
    return sizeof(filter(orcs, &->query_prop("_live_i_isengard_orc")));
} /* orcs_present */

/*
 * Function name:        init
 * Description  :        set up some random noises
 */
public void
init()
{
    ::init();
    init_random_noise();
} /* init */

/*
 * Function name: random_noise
 * Description  : the player can hear drips in the chamber
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    if (!orcs_present())
    {
        return 0;
    }

    tell_room(TO, BSN(        ({
        "Harsh voices echo through the corridor from the southwest.",
        "A cruel shout rings out from the southwest.",
        "Harsh and horrible laughter sounds out suddenly from the"
      + " southwest.",
        "Muffled laughter suddenly erupts to the southwest.",
        "What sounds like angry voices arguing comes suddenly"
      + " from the southwest.",
        })[random(5)] ) );

    return 1;
} /* random_noise */

/*
 * Function name:        fire_present
 * Description  :        checks the room to the southeast to see if
 *                       the bonfire there is lit
 * Returns      :        1 - fire is lit,
 *                       0 - fire is not lit
 */
public int
fire_present()
{
    if (ORC_ROOM->query_fire_state() == 2)
    {
        return 1;
    }

    return 0;
} /* fire_present */

/*
 * Function name:        my_dark_msg
 * Description  :        checks the room to the southwest to see if
 *                       the bonfire there is lit... if so, we have
 *                       a special dark msg for the room.
 * Returns      :        string - the dark msg
 */
public string
my_dark_msg()
{
    if (fire_present())
    {
        return "A dull glow to the southwest only barely illuminates"
             + " this dark room.\n";
    }

    return "A dark room.\n";
} /* my_dark_msg */
