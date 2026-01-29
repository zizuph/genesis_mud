/* File:          /d/Khalakhor/ship/macdunn/sea_sparkle.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the sea room used near Sparkle for the
 *                Khalakhor ship that originates from Port Macdunn.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/sea_base.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/ship/macdunn/std/sea_base";
#include "local.h"
#include <stdproperties.h>

public void
create_sea()
{
    set_short("An ocean near the village of Sparkle");
    set_long("   This is an ocean near the village of Sparkle. The " +
      "murky water of the sea absorbs all sunlight.\n");
    add_item(({"water","murky water"}),"The water absorbs all " +
      "sunlight, giving it a dun brown colour.\n");
    add_item("sky","The sky is lit with an overbearing amount of " +
      "sunshine.\n");

    add_exit(MACDUNN_DIR + "sea4","khalakhor",0,0,1);
    add_exit(SPARKLE_PIER,"sparkle",0,0,1);
}
