#pragma save_binary
/*
 *  /d/Gondor/guilds/rangers/north/great_hall.c
 *
 * Revision history:
 *  10-Dec-1997, Gnadnar: general clean up and add working fireplace
 * 15-July-2001, Alto: revised to fit new rangers theme
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "../rangers.h"

inherit RANGERS_NOR_DIR + "north_funcs.c";
inherit RANGERS_DIR + "member_vote.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/common/lib/clock.h"
#include "check_exit.c"

static object  gMaster;
static int     gRqStageStored = rq_stage();

public string  fire_desc(string arg);


/*
 * Function name: create_gondor
 * Description  : set up the room
 */
public void
create_gondor()
{
    set_short("the great hall");
    set_long(&fire_desc());

    north_add_items();
    create_votes("north");

    set_parse_pattern("[the] [deep] [stone] 'fireplace'");

    add_item( ({ "deep fireplace", "stone fireplace",
        "deep stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item( ({ "flames", "flame", "fire" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */
    add_item( ({ "wood", "firewood", "wood in fireplace",
        "firewood in fireplace" }), &fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in fireplace", "ashes in fireplace" }),
        &fire_desc("ashes"));

    add_item(({"mantle", "mantlepiece"}), "A mantlepiece of carved oak "
        + "stretches the width of the fireplace.\n");
    add_item(({"banner"}), "The banner displays a White Tree surrounded "
        + "by seven stars.\n");
    add_item(({"tapestry", "tapestries"}), "The tapestries show Elendil, "
        + "the first king of Arnor, and his two sons, Isildur and Anarion. "
        + "The most prominent tapestry portrays Elendil and his ships as "
        + "they are washed ashore at Lindon. Later, he travelled up the "
        + "river Lhun and established the realm of Arnor.\n");
    add_item(({"stone pillars", "stone pillar", "large stone pillars",
        "large stone pillar", "large pillars", "large pillar",
        "pillars", "pillar"}), "Large stone pillars, sculpted to resemble "
        + "slender trees, support the ceiling.\n");
    add_item( ({ "graceful archway", "graceful archways", "archway",
        "archways", "corridor", "corridors" }), "Sweeping up towards the "
        + "vaulted ceiling, the sculpted archways open onto corridors "
        + "leading in all directions.\n");
    add_item(({ "room", "great hall" }), &fire_desc());

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(RANGERS_NOR_DIR+"s_corridor","west");
    add_exit(RANGERS_NOR_DIR+"e_corridor","north");
    add_exit(RANGERS_NOR_DIR+"o_corridor","south");
    add_exit(RANGERS_NOR_DIR+"t_corridor","east");

    reset_room();
}


/*
 * Function name: reset_room
 * Description  : Restores master ranger and fire.
 */
public void
reset_room()
{
    if ( !objectp(gMaster) )
    {
        if (gRqStageStored < RQ_LEFT_HOBBITON)
            gMaster = clone_object(RANGERS_NPC + "aragorn");
        else
            gMaster = clone_object(RANGERS_NPC + "halbarad");
        gMaster->move(TO, 1);
    }

    set_wood(-1);
    if ( query_fire_state() != FIRE_BURNING && ENV(gMaster) == TO )
    {
        gMaster->command("emote places some wood in the fireplace.");
        gMaster->command("emote lights the wood.");
        set_fire_state(FIRE_BURNING);
    }
    check_member_end_vote();
}

/*
 * Function name: init
 * Description  : Adds verbs for the fire.
 */
public void
init()
{
    ::init();
    init_fire();
    init_member_vote();
}


/*
 * Function name: fire_desc
 * Descripiton  : VBFC for room and items that vary with the fire.
 * Arguments    : string arg -- what we're looking at
 * Returns      : string description
 */
public varargs string
fire_desc(string arg = "")
{
    int fire_state = query_fire_state();
    string tmpstr;

    switch ( arg )
    {
    case "fireplace":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The fireplace is built of the same dark gray stone "
                + "as the walls; the gold and silver flecks in the stone "
                + "sparkle in the light of the fire.\n";
        case FIRE_UNLIT_WOOD:
            return "The fireplace is built of the same dark gray stone "
                + "as the walls. Wood is stacked in the fireplace, ready "
                + "to be lit.\n";
        default:
            return "The fireplace is built of the same dark gray "
                + "stone as the walls.\n";
        }

    case "fire":
        if ( fire_state == FIRE_BURNING )
        {
            return one_of_list(({ "The flickering gold and red flames "
                + "are mesmerizing.\n", "The fire casts a warm light "
                + "over the great hall.\n", "The fire burns brightly, "
                + "imparting a warm glow to the surrounding stone.\n" }));
        }

        return "You find no fire.\n";

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The wood in the fireplace burns brightly, emiting "
                + "a pleasant warmth.\n";
        case FIRE_UNLIT_WOOD:
            return "Unlit wood is piled in the fireplace.\n";
        default:
            return "You find no firewood.\n";
        }

    case "ashes":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, ashes cover "
                + "the bottom of the fireplace.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the wood, ashes cover the bottom of the "
                + "fireplace.\n";
        default:
            return "Ashes cover the bottom of the fireplace.\n";
        }

    default:
        if ( fire_state == FIRE_BURNING )
            tmpstr = ", where a flickering fire casts a warm glow "
                + "over the room. ";
        else
            tmpstr = ". ";

        return "The great hall of the northern headquarters is warm and "
            + "commodious. Two rows of large stone pillars support the high "
            + "ceiling, rich tapestries cover the walls, and a grand banner "
            + "hangs above a deep fireplace" + tmpstr + "Graceful archways "
            + "lead out of the hall.\n";
    }
}
