inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("portrait of om");

    set_short("portrait of the Honourable Om Baggins");
   set_long("This is a portrait of Om Baggins, former wizard of Terel.  " +
    "Never\nshould any Terel wizard forget his gifts to this domain.\n" +
    "His contributions include, but are not limited to, the following:\n\n" +
    "     The dark caves deep within the forest maze\n" +
    "     Various NPC's throughout Terel\n");

    add_prop(OBJ_I_NO_GET, 1);

    add_name("om");
}
