/*                         
 * Random object for citadel
 * Finwe, April 2008
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

create_object()
{
    seteuid(getuid());

    set_name("robe");
    set_pname("robes");

    set_short("tattered robe");
    add_adj(({"tattered", "old"}));

    set_long("This is a tattered robe. It looks like it was once worn by royalty. Now it is shredded and tattered, and looks worthless.\n");

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE,  500);
    add_prop(OBJ_I_VOLUME, 50);

    set_slots(A_TORSO);
    set_layers(0);
    set_looseness(0);

}
