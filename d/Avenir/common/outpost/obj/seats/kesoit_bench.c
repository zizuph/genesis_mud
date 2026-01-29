#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"kesoit","wooden","ornate", "carved", "elegant"}));
    set_short("ornate kesoit bench");
    set_long("A beautiful bench made from the blood-red wood of a kesoit "+
    "tree. It has been ornately carved with trefoils and spirals. It looks "+
    "sturdy enough to seat two.\n");

    set_seat_names(({"bench", "kesoit bench"}));

    set_seat_id("_kesoit_bench");

    set_max_seat(3);
    set_lay_num(1);

    set_shift_seat(1);
    set_allow_kinky(1);
}
