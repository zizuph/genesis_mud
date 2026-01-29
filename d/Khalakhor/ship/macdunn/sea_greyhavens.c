/* File:          /d/Khalakhor/ship/macdunn/sea_greyhavens.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the sea room used near Grey Havens for the
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
    set_short("In the sea west of Grey Havens");
    set_long("   This is the sea west of Grey Havens. The " +
      "crystal clear water sparkles in the sunlight.\n");
    add_item(({"waters","crystal waters","clear waters"}),
      "The water is pure and clean.\n");
    add_item("sky","The sky is lit with an all present amount of " +
      "sunshine.\n");

    add_exit(MACDUNN_DIR + "sea4","khalakhor",0,0,1);
    add_exit(GREYHVNS_PIER,"greyhavens",0,0,1);
}
