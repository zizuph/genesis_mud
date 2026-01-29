/*
 *  /d/Gondor/clubs/nisse/obj/miruvor.c
 *
 *  The flask of Miruvor. The drink from Imladris.
 *
 *  Deagol, March 2003
 */

inherit "/std/drink";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_drink()
{
    ::create_drink();

    set_name("miruvor");
    add_name("flask");
    set_adj("small");
    set_pname("miruvors");
    add_pname("flasks");
    set_short("small flask of miruvor");
    set_pshort("small flasks of miruvor");
    set_long("This rich delicious cordial from Imladris has restorative " +
        "properties, making it refreshing and cool on your throat. The " +
        "cordial is made from flowers in the valley of Imladris, but you " +
        "cannot seem to detect what the exact ingredients might be.\n");

    add_prop(OBJ_I_VALUE, 75);
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 180);

    set_soft_amount(160);
    set_alco_amount(18);
    
    setuid();
    seteuid(getuid());
}
