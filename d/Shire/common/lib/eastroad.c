#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/common/lib/rom";

create_rom() {
    add_prop(ROOM_I_INSIDE, 0);
    /*
	  add_item(({"sky","moon","sun","stars","heaven"}),"@@do_sky@@\n");
    */
    my_exit_desc_mode = 1;
    this_object()->create_eastroad();
}

reset_rom() { TO->reset_eastroad(); }
