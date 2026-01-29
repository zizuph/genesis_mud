/* small jeweled speckled bell
 * Created by Damaris 02/01
 */

inherit "/std/object.c";
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

void
create_object()
{
    set_name("bell");
    set_adj("small");
    add_adj("jeweled speckled");
    set_short("jeweled speckled bell");
    set_long("It looks like it might have a nice sounding ring to it.\n");

    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  500);
}

