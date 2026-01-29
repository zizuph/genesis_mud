/*
 * File:    temple_w
 * Creator: Cirion, 1998.04.25
 * Purpose: The temple of the monks. This is where a player
 *          can join.
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>

inherit ROOMBASE;

void
create_room ()
{
    set_short("western end of temple");
    set_long("Looming high overhead against the west wall is "
        + "a massive, serpentine statue of a bronze dragon, wise "
        + "and serene. Its wings spread out, spanning the "
        + "width of this temple and refracting the light from "
        + "many candles with a dull, sparkling splendor. Seated between "
        + "its great foreclaws, resting upon the ground, is a "
        + "simple altar of white sandstone. High above to the "
        + "west, a balcony extends out over the temple, and "
        + "the temple base continues to the east.\n");
    add_item(({"dragon","statue","bronze dragon"}),
        "The statue of the dragon rises to the high ceiling "
        + "of this vast place. Its bronze wings spread "
        + "glittering out across the width of the temple, "
        + "refracting the candlelight through the smokey "
        + "air. Its foreclaws rest on the ground, between "
        + "which lies a simple altar of white sandstone. The "
        + "great head of the dragon looks peacefully down, "
        + "seeming to gaze directly at you. Its onyx eyes hold "
        + "no light.\n");
    add_item(({"claw","claws","foreclaws"}),
        "The enormous foreclaws of the dragon rest upon the "
        + "ground, between which sits a sandstone altar. The "
        + "talons of the claws are made from a dull white "
        + "wood, very old.\n");
    add_item(({"wood","talons","wood","white wood"}),
        "The wooden talons of the dragon are made from some "
        + "unknown wood, aged and soft.\n"
        + VBFC_SAY("looks carefully at the claws of the dragon statue.\n"));
    add_item(({"altar","sandstone","sandstone altar"}),
        "The simple altar is made from soft, white "
        + "sandstone. Scripted on the top of the altar are "
        + "words in the common tongue.\n");
    add_item(({"candle","candles","light"}),
        "Dozens of tall candles, spaced evenly along the "
        + "north and south walls, provide light for this "
        + "vast temple, into which no windows look. The "
        + "light from the candles rafracts dully off the "
        + "bronze wings on the dragon. Their smoke "
        + "obscures your vision, and smells of hazelwood and  "
        + "old incense.\n");
    add_item(({"tile","tiles","floor","ground"}),
        "The floor is made from evenly laid tiles of very "
        + "smooth, dark stone. Footfalls make no noise upon "
        + "the floor.\n");
    add_item("balcony",
        "A narrow balcony extends out over the eastern end "
        + "of the temple, just below the high vaulted "
        + "ceiling.\n");
    add_item("ceiling",
        "It spreads out high above, veiled in the scented "
        + "tendrils of smoke and haze.\n");
    add_item(({"wing","wings"}),
        "They are of beaten bronze with raised winds "
        + "running along to their narrow claws.\n");
    add_item(({"candlestick","candlesticks","candlelight","light"}),
        "The light cast from the candles is swallowed by "
        + "the smokey haze. The candlesticks themselves "
        + "shimmer with individual stars that dance and play "
        + "in the slow moving air.\n");
    add_item("head",
        "The head of the dragon rises high above, looking "
        + "down in solemn majesty.\n");
    add_item(({"eyes","eye","onyx"}),
        "The onyx eyes of the dragon glitter with a light "
        + "all their own.\n");
    add_cmd_item(({"altar","","before the altar","down","on floor"}), ({"pray","kneel"}),
        "You kneel before the altar in serene meditation, "
        + "and a feeling of peace washes over you.\n"
        + VBFC_SAY("kneels before the altar in serene meditation.\n"));
    add_cmd_item(({"candle","candles","light"}), ({"extinguish"}),
        "The moment you extinguish one of the candles, it "
        + "light up again itself, of its own accord.\n"
        + VBFC_SAY("tries to extinguish one of the candles, but it "
        + "lights up on its own a moment after it goes out.\n"));
    add_cmd_item(({"altar","words","script","word"}), ({"read"}),
        "The words inscribed on the altar read:\n\tYe who would "
        + "dedicate thyself to the Order,"
        + "\n\tknow that the path to mastery of the Way of the Dragon is long.\n"
        + "\tMastery of the Way shall cost " + LANG_WNUM (MONK_OCC_TAX)
        + " percent of your experience \n\tfor occupational study, and "
        + LANG_WNUM (MONK_LAY_TAX) + " for layman study.\n"
        + "\n\tShould you later betray the Order, "
        + "\n\tone sixth of thy experience in combat will be forfeit.\n"
        + VBFC_SAY("reads the words inscribed on the sandstone altar.\n"));
    add_cmd_item(({"air","smoke","candle","candles","the air"}), ({"smell","sniff"}),
        "The air smells fainly of incense and hazelwood.\n"
        + VBFC_SAY("smells the smokey air of the temple.\n"));


    // where, command
    add_exit("temple_e", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You walk noiselessly down the vast "
        + "temple hall and come to the base of the great statue "
        + "of a bronze dragon.\n");
}

public int
check_monk ()
{
    if (this_player ()->m_query_monk ())
        return 0;

    if (m_is_old_member (this_player ()))
        return 0;

    write ("You cannot pass that way.\n");
    return 1;
}

void
init()
{
    ::init();

    m_join_init(); // initialize joining functions
}


