// file name:        /d/Avenir/common/dark/obj/dark_treas_pmodule
// creator(s):       Denis and Lilith, Oct - Nov 1996
// purpose:          This object is the placer module for 
//                   treasure in the Utterdark.
#pragma strict_types
#include "/d/Avenir/smis/smis.h"

inherit SMIS_MODULE_PLACER;

void
create_placer()
{
    set_module_id("dark_treas");
    set_module_description("Utterdark treasure placer.");
//L2
    set_location_object("/d/Avenir/common/dark/l2/w8",
			"/d/Avenir/common/dark/smis/food_crate");
    set_location_object("/d/Avenir/common/dark/l2/w5",
			"/d/Avenir/common/dark/smis/tools_crate");
    set_location_object("/d/Avenir/common/dark/l2/n10",
                        "/d/Avenir/common/dark/smis/mixed_crate");
    set_location_object("/d/Avenir/common/dark/l2/n4",
                        "/d/Avenir/common/dark/smis/torch_crate");
    set_location_object("/d/Avenir/common/dark/l2/e11",
                        "/d/Avenir/common/dark/smis/torch_crate");
//L3
    set_location_object("/d/Avenir/common/dark/l3/s5_l2",
                        "/d/Avenir/common/dark/smis/mixed_crate");
    set_location_object("/d/Avenir/common/dark/l3/ec3",
                        "/d/Avenir/common/dark/smis/food_crate");
    set_location_object("/d/Avenir/common/dark/l3/center",
                        "/d/Avenir/common/dark/smis/torch_crate");

//L4
    set_location_object("/d/Avenir/common/dark/l4/n13",
                        "/d/Avenir/common/dark/smis/food_crate");
    set_location_object("/d/Avenir/common/dark/l4/w15",
                        "/d/Avenir/common/dark/smis/torch_crate");
    set_location_object("/d/Avenir/common/dark/l4/e1",
                        "/d/Avenir/common/dark/smis/torch_crate");
#if 0
//L5
    set_location_object("/d/Avenir/common/dark/l5/n15",
                        "/d/Avenir/common/dark/smis/torch_crate");
    set_location_object("/d/Avenir/common/dark/l5/w17",
                        "/d/Avenir/common/dark/smis/mixed_crate");
    set_location_object("/d/Avenir/common/dark/l5/w1",
                        "/d/Avenir/common/dark/smis/tools_crate");
    set_location_object("/d/Avenir/common/dark/l5/e10",
                        "/d/Avenir/common/dark/smis/torch_crate");
#endif
}
