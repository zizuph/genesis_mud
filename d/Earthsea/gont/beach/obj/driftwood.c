#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

#define CARVE_OBJECT_ID "_travellers_carving_object"

public void
create_object()
{
    set_name("driftwood");
    add_name("wood");
    add_name(CARVE_OBJECT_ID);
    add_adj("brown");
    set_short("piece of brown driftwood");
    set_pshort("pieces of brown driftwood");
    set_long("This is a piece of wood that has been " +
        "carved by sea and sand into an interesting shape. " +
        "It might be possible for someone with special skill in " +
        "carving to create a sculpture from it.\n");
    add_item((({"shape", "interesting shape"})),
        "The driftwood is shaped almost like a seahorse or " +
        "perhaps a dolphin ... it is up to you what you see " +
        "in it.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, random(25));
}
