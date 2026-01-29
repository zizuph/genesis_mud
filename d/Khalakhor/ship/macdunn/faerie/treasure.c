/* File:          /d/Khalakhor/ship/macdunn/faerie/treasure.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Modifications:
 * Purpose:       The treasure found in the trunk.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/ship/macdunn/faerie/trunk.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

public void
create_object()
{
    set_name("figurine");
    add_name(({"figure","statue","carving"}));
    set_adj("ivory");
    add_adj(({"delicate","detailed","white","carved"}));
    set_short("ivory figurine");
    set_pshort("ivory figurines");
    set_long("This figurine is carved from the finest ivory. " +
      "It is obviously the work of a master artisan. " +
      "The carving is of a man with a bearded face, " +
      "wearing a robe. The edges of the robe on the figurine " +
      "are plated with gold. In the man's hand, he holds a " +
      "staff.\n");
    add_item("staff on figurine","The staff on the figurine " +
      "is made of some type of burled wood.\n");
    add_prop(OBJ_I_VALUE, 4545);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 165);
}
