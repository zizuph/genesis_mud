/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";


create_object()
{
    seteuid(getuid());

    set_name("crown");
    set_pname("crowns");

    set_short("dented crown");
    add_adj(({"golden", "dented"}));

    set_long("This large golden crown. It has a massive dent in it where " +
        "a blunt weapon slammed into it. The massive dent makes the crown unwearable.\n");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
