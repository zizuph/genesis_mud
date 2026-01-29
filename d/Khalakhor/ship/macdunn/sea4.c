/* File:          /d/Khalakhor/ship/macdunn/sea4.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       The sea4 is a room that all Khalakhor ships
 *                originating from Port Macdunn pass through.
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
    set_short("On Cuan Siorruidh");
    set_long("   This is the eternal ocean, Cuan Siorruidh. It " +
      "surrounds the land of Khalakhor. At its most distant "+
      "reaches, foreign lands can be found.\n");

    add_exit(MACDUNN_DIR + "sea3","northwest",0,0,1);
    add_exit(MACDUNN_DIR + "sea_faerie","faerie",0,0,1);
    add_exit(MACDUNN_DIR + "sea_gelan","gelan",0,0,1);
    add_exit(MACDUNN_DIR + "sea_greyhavens","greyhavens",0,0,1);
    add_exit(MACDUNN_DIR + "sea_kalaman","kalaman",0,0,1);
    add_exit(MACDUNN_DIR + "sea_sparkle","sparkle",0,0,1);
}
