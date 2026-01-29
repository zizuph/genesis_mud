/* File:          /d/Khalakhor/ship/macdunn/sea_faerie.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications: Teth - added mermaids, Sept 07, 1997
 * Purpose:       This is the sea room used near Faerie for the
 *                Khalakhor ship that originates from Port Macdunn.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Genesis/start/elf/monster/simple_mermaid.c
 *                /d/Khalakhor/ship/macdunn/std/sea_base.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/ship/macdunn/std/sea_base";
#include "local.h"
#include <stdproperties.h>

#define MERMAID "/d/Genesis/start/elf/monster/simple_mermaid.c"

object mermaid1, mermaid2;

public void
create_sea()
{
    set_short("An ocean near the land of Faerie");
    set_long("   This is an ocean near the land of Faerie. The " +
      "crystal clear water sparkles in the sunlight.\n");
    add_item(({"waters","crystal waters","clear waters"}),
      "The water is pure and clean.\n");
    add_item("sky","The sky is lit with an all present amount of " +
      "sunshine.\n");

    add_exit(MACDUNN_DIR + "sea4","khalakhor",0,0,1);
    add_exit(FAERIE_PIER,"faerie",0,0,1);

    mermaid1 = clone_object(MERMAID);
    mermaid1->move(this_object());
    mermaid2 = clone_object(MERMAID);
    mermaid2->move(this_object());
}
