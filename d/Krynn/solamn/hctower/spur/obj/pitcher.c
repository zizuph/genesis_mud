inherit "/std/drink";
#include "../local.h"

create_drink()
{
    set_soft_amount(500);
    set_alco_amount(0);
    set_name("water");
    add_name("pitcher");
    add_name("pitcher of water");
    add_name("_spur_pitcher");
    set_drink_msg("The water is wonderful! You splash some on your face in "+
        "your eagerness to drink it all.\n");
    set_short("pitcher of water");
    set_long("This pitcher contains a half-litre of clean, cool water pumped from "+
        "the Vingaard River.\n");
    add_prop(OBJ_I_CONTAIN_WATER, 1);
}
