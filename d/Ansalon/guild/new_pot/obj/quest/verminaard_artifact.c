/* Ashlar, 29 Oct 97
        The artifact that Verminaard wants delivered.
*/

inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"

void
create_object()
{
    set_name("artifact");
    add_name("verminaard_artifact");
    add_name("box");
    set_adj("small");
    add_adj("golden");
    set_short("small golden box");
    set_long("It is a small golden box. There seems to be a lid, but you " +
    "cannot find any way to open it, which would perhaps not be such a good " +
    "idea anyway. You better take this to the temple right away.\n");
    
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}


