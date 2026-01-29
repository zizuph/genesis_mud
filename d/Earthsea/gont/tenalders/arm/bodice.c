#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_earthsea_wearable_item()
{
    set_name("bodice");
    set_pname("bodices");
    set_adj(({"white", "lacey", "low-cut"}));
    set_short("lacey white low-cut bodice");
    set_pshort("lacey white low-cut bodices");
    set_long("This is a tight-fitting low-cut "+
        "lacey bodice, which is made to hug a woman's figure, showing "+
        "it to best advantage.\n");
    set_layers(10);
    set_looseness(5);
    set_slots(A_TORSO);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 70);   
    add_prop(OBJ_I_VALUE, 300);
}
