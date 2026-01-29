#pragma strict_types

#include "zigg.h"
#include <stdproperties.h>

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name(({"blanket","cloth","seat"}));
    set_adj(({"red", "black", "gingham", "cloth", "picnic",}));
    set_short("red and black gingham blanket");

    set_seat_names(({"blanket","cloth"}));

    set_seat_id("__zigg_picnic_blanket");

    set_max_seat(4);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
    set_portable(1);

    set_no_show();
}
