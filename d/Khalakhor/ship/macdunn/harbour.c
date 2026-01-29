/* File:          /d/Khalakhor/ship/macdunn/harbour.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       The harbour is the first sea room outbound for any
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
    set_short("In the harbour of Port Macdunn, Cala Fasgadh");
    set_long("This is the harbour of Port Macdunn, Cala Fasgadh. It " +
      "is useful as it provides shelter to ships, especially during " +
      "storms on Cuan Siorruidh.\n");
    add_item("sky","The sky is somewhat cloudy, lending the day a " +
      "grim feeling.\n");

    add_exit(MACDUNN_DIR + "sea1","southwest",0,0,1);
}

