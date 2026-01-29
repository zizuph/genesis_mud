/* File:          /d/Khalakhor/ship/macdunn/sea1.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       The sea1 is a room that all Khalakhor ships
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
    set_short("On Lean Mir");
    set_long("   This is the calm sea, Lean Mir. It is located " +
      "between the southwest and southeast speirs of the " +
      "continent of Khalakhor.\n");

    add_exit(MACDUNN_DIR + "harbour","northeast",0,0,1);
    add_exit(MACDUNN_DIR + "sea2","southeast",0,0,1);
}

