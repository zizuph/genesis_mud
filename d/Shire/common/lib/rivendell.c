#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/common/lib/rom";

create_rom() {
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    this_object()->create_rivendell_room();
    my_exit_desc_mode = 1;
}

reset_rom() {
    this_object()->reset_rivendell_room();
}
