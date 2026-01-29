/*
 * File:    temple_e
 * Creator: Cirion, 1998.04.25
 * Purpose: The temple of the monks.
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>

inherit ROOMBASE;

void
create_room ()
{
    set_short("eastern end of temple");
    set_long("Dominating this vast temple is a statue of "
        + "a great bronze dragon against the far western "
        + "wall. Flickering candles stand in tall holders "
        + "along the east and west wall, their faint "
        + "light passing through the thin wisps and curls of "
        + "sweet smoke. The floor of this hall is made "
        + "from smooth stone tiles, precisely laid. Directly "
        + "overhead, a balcony ledge extends out just beneath "
        + "the high vaulted ceiling.\n");
    add_item(({"dragon","status","bronze dragon"}),
        "The statue of the dragon rises to the high ceiling "
        + "of this vast place. Its bronze wings spread "
        + "glittering out across the width of the temple, "
        + "refracting the candlelight through the smokey "
        + "air. Its foreclaws rest on the ground, between "
        + "which lies a simple altar of white sandstone. The "
        + "great head of the dragon looks peacefully down, "
        + "seemingly directly at you. Its onyx eyes hold no "
        + "light.\n");
    add_item(({"altar","sandstone","sandstone altar"}),
        "You can make out no details from here.\n");
    add_item(({"candle","candles","light"}),
        "Dozens of tall candles, spaced evenly along the "
        + "north and south walls, provide light for this "
        + "vast temple, into which no windows look. The "
        + "light from the candles rafracts dully off the "
        + "bronze wings on the dragon, and their smoke "
        + "obscures your vision, smells of hazelwood and old "
        + "insence.\n");
    add_item(({"tile","tiles","floor","ground"}),
        "The floor is made from evenly laid tiles of very "
        + "smooth, dark stone. Footfalls make no noise upon "
        + "the floor.\n");
    add_item("balcony",
        "The balcony extends out over the temple, directly "
        + "overhead.\n");
    add_cmd_item(({"candle","candles","light"}), ({"extinguish"}),
        "The moment you extinguish one of the candles, it "
        + "light up again itself, of its own accord.\n"
        + VBFC_SAY("tries to extinguish one of the candles, but it "
        + "light up on its own a moment after it goes out.\n"));
    add_cmd_item(({"air","smoke","candle","candles","the air"}), ({"smell","sniff"}),
        "The air smells fainly of insence and hazelwood.\n"
        + VBFC_SAY("smells the smokey air of the temple.\n"));


    // where, command
    add_exit("temple_w", "west");
    add_exit("hall_lower_south", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You enter the vast temple.\n");
    ENTRANCE_MSG("west", "You pass silently along the smooth stone "
        + "floor of the temple.\n");
}

