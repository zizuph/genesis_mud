/* File:          /d/Khalakhor/ship/macdunn/sea_gelan.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the sea room used near Gelan for the
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
    set_short("An ocean near the land of Calia");
    set_long("   This is an ocean near the land of Calia. The " +
      "water of the ocean rolls in large waves.\n");
    add_item("waves","The waves are ever-moving.\n");
    add_item("water","The water is azure blue in colour.\n");
    add_item("sky","The sky is fair and cloudless.\n");

    add_exit(MACDUNN_DIR + "sea4","khalakhor",0,0,1);
    add_exit(GELAN_PIER,"gelan",0,0,1);
}
