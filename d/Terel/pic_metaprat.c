inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("portrait of metaprat");

    set_short("portrait of the Honourable Metaprat");
    set_long("This is a portrait of Metaprat, former wizard of Terel.  " +
    "Never\nshould any Terel wizard forget his gifts to this domain.\n" +
    "His contributions include, but are not limited to, the following:\n\n" +
    "     Much of the city of Calathin\n" +
    "     Many of the first roads andd paths\n" +
    "     Most of the first NPC's of the domain\n\n" +
    "Lack of access denied this saint from ever seeing Terel open " +
    "to the public.\n");

    add_prop(OBJ_I_NO_GET, 1);

    add_name("om");
}
