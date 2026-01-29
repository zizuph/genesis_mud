#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit (ZIGG + "lib/seating");

public void
create_seating(void)
{
    set_name(({"desk","chair"}), 1);
    set_short("carved wooden desk");
    set_long("");

    set_seat_names(({"desk","chair"}));

    set_seat_id("__union_library_desk");

    set_max_seat(1);
    set_no_show();
}

public void
ss_seated(int state)
{
    write("You take a seat at the "+ short() +".\n");
    say(QCTNAME(TP) +" takes a seat at the "+ short() +".\n");
}

public string
sit_text(void)		{ return "seated at"; }
