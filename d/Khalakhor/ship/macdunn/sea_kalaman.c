/* File:          /d/Khalakhor/ship/macdunn/sea_kalaman.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the sea room used near Kalaman for the
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
    set_short("An ocean near Kalaman, on the continent of Ansalon");
    set_long("   This is an ocean near the city of Kalaman. The " +
      "pale green waters absorb the sun's rays.\n");
    add_item(({"waters","pale waters","green waters"}),
      "Although pale green, the water appears clean.\n");
    add_item("sky","The sky is somewhat cloudy.\n");

    add_exit(MACDUNN_DIR + "sea4","khalakhor",0,0,1);
    add_exit(KALAMAN_PIER,"kalaman",0,0,1);
}
