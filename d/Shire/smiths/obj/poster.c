/*
 * Help poster for the Smiths in the forge.
 * -- Finwe, June 2001
 */
 
inherit "/std/scroll";

#include <stdproperties.h>

void
create_scroll()
{
    set_name("poster");
    set_adj("metal");
    set_long("It is a piece of brass, hammered thing with " +
        "some writing engraved on its surface. At the top of " +
        "the sign, it reads 'The Forge of Bree'.\n");

    add_prop(OBJ_I_VALUE, 678);
    add_prop(OBJ_I_WEIGHT, 40000000);
    add_prop(OBJ_I_VOLUME, 254);

    setuid();
    seteuid(getuid());
    set_file("/w/finwe/poster");
}
