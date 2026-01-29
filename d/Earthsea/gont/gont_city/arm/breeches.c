#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

#define COLOURS (({"red", "black", "purple-striped", "orange", \
    "green", "blue" \
}))

public void
create_earthsea_wearable_item()
{
    string colour = COLOURS[random(sizeof(COLOURS))];
    set_name("breeches");
    add_name("pair of " + colour + " breeches");
    add_name("pair of breeches");
    add_name("pair");
    set_adj("colour");
    add_pname("pairs");
    set_short("pair of " + colour + " breeches");
    set_pname("pairs of breeches");
    set_pshort("pairs of " + colour + " breeches");
    set_long("A pair of " + colour + " breeches, "+
        "which are typically worn by sailors or pirates. A small length of rope " +
        "is used to tie the " +short()+ " in place.\n");
    set_layers(100);
    set_looseness(10);
    set_slots(A_LEGS);    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 5);
}
