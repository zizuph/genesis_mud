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
inherit "/lib/keep";

create_object()
{
    seteuid(getuid());

    set_name("crown");
    set_pname("crowns");

    set_short("dented crown");
    add_adj(({"golden", "dented"}));

    set_long("This large golden crown. It has a massive dent in it where " +
        "a blunt weapon slammed into it, making it unwearable.\n");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
