/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge7.c
 *
 *  The ledge along the western cliffs in the Blackwall Mountains
 *  has begun to wind slightly to the northeast here. The ledge is
 *  broken by the chimney from the waterfall here. A player can
 *  jump to cross the gap.
 *
 *  Copyright (c) August 1997, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master.c";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_ledge();
public int     ledge_gap();
public int     ledge_jump(string arg);
public void    init();


/*
 * Function name: create_ledge
 * Description  : allows us to create the room with area presets
 */
public void
create_ledge()
{
    set_show_area_desc();

    set_extraline("The ledge winds further along the cliffs here,"
      + " turning slightly east as it travels north. High above,"
      + " a large finger of stone rises from the cliff face. The"
      + " progress of the ledge is halted by a wide gap which"
      + " has cut through the rock to the northeast.");

    add_item( ({ "gap", "wide gap", "gap in the ledge",
                 "chimney" }), BSN(
        "A chimney perhaps three feet in width has been bored out"
      + " of the cliffside here. It has cut through the ledge to"
      + " the northeast."));
    add_item(({"finger","fingers","finger of stone",
               "fingers of stone"}), BSN(
        "A tall spire of stone rises from the cliffs above, casting"
      + " a long forbidding shadow across the weathered faces of"
      + " rock."));
    add_item(({"shadow","shadows"}), BSN(
        "The shadow cast by the towering stone spire is long and"
      + " narrow, almost as a finger of darkness pointing to some"
      + " unknown purpose.")); /* ha ha! Red Herring, you suckers! */

    set_cliff_base(DELRIMMON_DIR + "lakeside/w_cliff5");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge8", "northeast",
             ledge_gap, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge6","south");

    set_no_exit_msg( ({ "east", "southeast" }),
        "A sheer drop lies in that direction.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest", "north" }),
        "The walls of the cliffs rise imposingly in that direction,"
      + " preventing your movement.\n");
} /* create_ledge */


/*
 * function name:        ledge_jump
 * description  :        let the player try to jump over the ledge
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
ledge_jump(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[over] [across] [the] [large] [wide] "
      + "'gap' / 'chimney' / 'northeast' / 'ne' [in] [the] [ledge]"))
    {
        return 0;
    }

    WRITE("Taking a running jump, you leap across the gap in the"
        + " ledge to land on the opposite side.");
    say(QCTNAME(TP) + " takes a running jump and leaps across the"
        + " gap in the ledge to land on the other side.\n");

    TP->add_fatigue(-(30 + random(10)) );
    TP->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/ledge8", 1);
    say(QCTNAME(TP) + " arrives, sailing over the gap in the ledge from"
                    + " the southwest to land on this side.\n");
    return 1;
} /* ledge_jump */


/*
 * Function name: ledge_gap
 * Description  : sends a message to the player telling them that they
 *                cannot simply walk over thin air, preventing the
 *                success of the move from add_exit
 * Returns      : string -- message that the player cannot walk that dir
 */
public int   
ledge_gap()
{
    WRITE("A large section of the ledge has been carved away by"
        + " the same process which must have carved the chimney"
        + " in the side of the cliff. You cannot simply walk"
        + " in that direction.");

    return 1;
} /* ledge_gap */

/*
 * function name:        init
 * description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(ledge_jump, "jump");
    add_action(ledge_jump, "leap");
} /* init */
