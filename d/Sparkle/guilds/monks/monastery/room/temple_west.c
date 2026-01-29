/*******************************************************************\
| TEMPLE_WEST.C                                                     |
\*******************************************************************/

/*
 * 98/04/25 Cirion	Created
 * 01/01/30 Manat	Added west wall
 * 02/02/23 Arandir	Changed sign to omit tax info
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up
 * 03/07/17 Arandir     Added items describing the joining commands
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit M_JOINING_LIBS;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("western end of temple");
  set_long ("Looming high overhead against the west wall is " +
            "a massive, serpentine statue of a bronze dragon, wise " +
            "and serene. Its wings spread out, spanning the " +
            "width of this temple and refracting the light from " +
            "many candles with a dull, sparkling splendor. Seated between " +
            "its great foreclaws, resting upon the ground, is a " +
            "simple altar of white sandstone. High above to the " +
            "west, a balcony extends out over the temple, and " +
            "the temple base continues to the east.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit("temple_east", "east");

  dg_add_entrance ("east",
                   "You walk noiselessly down the vast temple hall " +
                   "and come to the base of the great statue of a " +
                   "bronze dragon.");

  add_item (({ "west wall" }),
            "Against the west wall is a massive, serpentine statue of a " +
            "bronze dragon. Resting upon the ground, between the statues " +
            "foreclaws, is a simple altar of white sandstone.\n");
  add_item (({ "dragon", "statue", "bronze dragon" }),
            "The statue of the dragon rises to the high ceiling " +
            "of this vast place. Its bronze wings spread " +
            "glittering out across the width of the temple, " +
            "refracting the candlelight through the smokey " +
            "air. Its foreclaws rest on the ground, between " +
            "which lies a simple altar of white sandstone. The " +
            "great head of the dragon looks peacefully down, " +
            "seeming to gaze directly at you. Its onyx eyes hold " +
            "no light.\n");
  add_item (({ "claw", "claws", "foreclaws" }),
            "The enormous foreclaws of the dragon rest upon the " +
            "ground, between which sits a sandstone altar. The " +
            "talons of the claws are made from a dull white " +
            "wood, very old.\n");
  add_item (({ "wood", "talons", "white wood" }),
            "The wooden talons of the dragon are made from some " +
            "unknown wood, aged and soft.\n" +
            dg_embed_action ("looks carefully at the claws of the dragon statue."));
  add_item (({ "altar", "sandstone", "sandstone altar" }),
            "The simple altar is made from soft, white " +
            "sandstone. Scripted on the top of the altar are " +
            "words in the common tongue. You also notice a tiny " +
            "addendum below.\n");
  add_item (({ "words", "scripted words", "scribbled words" }),
            "The words are in the common tongue and scripted " +
            "upon the altar. Perhaps you can read them.\n");
  add_item (({ "addendum", "small addendum", "tiny addendum" }),
            "The addendum is in a tiny script, but definitely readable.\n");
  add_item (({ "candle", "candles", "light" }),
            "Dozens of tall candles, spaced evenly along the " +
            "north and south walls, provide light for this " +
            "vast temple, into which no windows look. The " +
            "light from the candles rafracts dully off the " +
            "bronze wings on the dragon. Their smoke " +
            "obscures your vision, and smells of hazelwood and " +
            "old incense.\n");
  add_item (({ "tile", "tiles", "floor", "ground" }),
            "The floor is made from evenly laid tiles of very " +
            "smooth, dark stone. Footfalls make no noise upon " +
            "the floor.\n");
  add_item (({ "balcony" }),
            "A narrow balcony extends out over the eastern end " +
            "of the temple, just below the high vaulted " +
            "ceiling.\n");
  add_item (({ "ceiling" }),
            "It spreads out high above, veiled in the scented " +
            "tendrils of smoke and haze.\n");
  add_item (({ "wing", "wings" }),
            "They are of beaten bronze with raised winds " +
            "running along to their narrow claws.\n");
  add_item (({ "candlestick", "candlesticks", "candlelight", "light" }),
            "The light cast from the candles is swallowed by " +
            "the smokey haze. The candlesticks themselves " +
            "shimmer with individual stars that dance and play " +
            "in the slow moving air.\n");
  add_item (({ "head" }),
            "The head of the dragon rises high above, looking " +
            "down in solemn majesty.\n");
  add_item (({ "eyes", "eye", "onyx" }),
            "The onyx eyes of the dragon glitter with a light " +
            "of their own.\n");

  add_cmd_item (({ "", "altar", "before the altar", "down", "on floor" }),
                ({ "pray", "kneel" }),
                "You kneel before the altar in serene meditation, " +
                "and a feeling of peace washes over you.\n" +
                dg_embed_action ("kneels before the altar in serene meditation."));
  add_cmd_item (({ "candle", "candles", "light" }),
                ({"extinguish"}),
                "The moment you extinguish one of the candles, it " +
                "lights itself up again, of its own accord.\n" +
                dg_embed_action ("tries to extinguish one of the candles, but it lights up on its own a moment after it goes out."));
  add_cmd_item (({ "altar", "word", "words", "scripted words", "scribbled words" }),
                ({ "read" }),
                "The words inscribed on the altar read: " +
                "Ye who would dedicate thyself to the Order, " +
                "steel thy Heart and Mind with patience, " +
                "for the Way is long beyond measure. " +
                "Ye who would forsake the search of the Way, " +
                "remember that there is but one Failure, " +
                "and that is to cease trying.\n" +
                dg_embed_action ("reads the words inscribed on the sandstone altar."));
  add_cmd_item (({ "addendum", "small addendum", "tiny addendum" }),
                ({ "read" }),
                "You can <apply> for membership and <check> the " +
                "status of your application here. Once your application " +
                "is accepted, you can <dedicate> yourself to the Order. As " +
                "a member, you can <transfer> to a different branch here, or " +
                "<forsake> the Order altogether.\n" +
                dg_embed_action ("reads the addendum inscribed on the sandstone altar."));
  add_cmd_item (({ "air", "smoke", "candle", "candles" }),
                ({ "smell", "sniff" }),
                "The air smells faintly of incense and hazelwood.\n" +
                dg_embed_action ("smells the smokey air of the temple."));
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();
  m_joining_hook_init ();
}

//-------------------------------------------------------------------

