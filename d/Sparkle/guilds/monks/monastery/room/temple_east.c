/*******************************************************************\
| TEMPLE_EAST.C                                                     |
\*******************************************************************/

/*
 * 98/04/25 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("eastern end of temple");
  set_long ("Dominating this vast temple is a statue of " +
            "a great bronze dragon against the far western " +
            "wall. Flickering candles stand in tall holders " +
            "along the east and west wall, their faint " +
            "light passing through the thin wisps and curls of " +
            "sweet smoke. The floor of this hall is made " +
            "from smooth stone tiles, precisely laid. Directly " +
            "overhead, a balcony ledge extends out just beneath " +
            "the high vaulted ceiling.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_lower_south", "east");
  add_exit ("temple_west", "west");

  dg_add_entrance ("east", "You enter the vast temple.");
  dg_add_entrance ("west", "You pass silently along the smooth stone floor of the temple.");

  add_item (({ "dragon", "status", "bronze dragon" }),
            "The statue of the dragon rises to the high ceiling " +
            "of this vast place. Its bronze wings spread " +
            "glittering out across the width of the temple, " +
            "refracting the candlelight through the smokey " +
            "air. Its foreclaws rest on the ground, between " +
            "which lies a simple altar of white sandstone. The " +
            "great head of the dragon looks peacefully down, " +
            "seemingly directly at you. Its onyx eyes hold no " +
            "light.\n");
  add_item (({ "altar", "sandstone", "sandstone altar" }),
            "You can make out no details from here.\n");
  add_item (({ "candle", "candles", "light" }),
            "Dozens of tall candles, spaced evenly along the " +
            "north and south walls, provide light for this " +
            "vast temple, into which no windows look. The " +
            "light from the candles rafracts dully off the " +
            "bronze wings on the dragon, and their smoke " +
            "obscures your vision, smells of hazelwood and old " +
            "incense.\n");
  add_item (({ "tile", "tiles", "floor", "ground" }),
            "The floor is made from evenly laid tiles of very " +
            "smooth, dark stone. Footfalls make no noise upon " +
            "the floor.\n");
  add_item (({ "balcony" }),
            "The balcony extends out over the temple, directly " +
            "overhead.\n");

  add_cmd_item (({ "candle", "candles", "light" }),
                ({"extinguish"}),
                "The moment you extinguish one of the candles, it " +
                "lights itself up again, of its own accord.\n" +
                dg_embed_action ("tries to extinguish one of the candles, but it lights up on its own a moment after it goes out."));
  add_cmd_item (({ "air", "smoke", "candle", "candles" }),
                ({ "smell", "sniff" }),
                "The air smells faintly of incense and hazelwood.\n" +
                dg_embed_action ("smells the smokey air of the temple."));
}

//-------------------------------------------------------------------

