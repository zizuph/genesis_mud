// Torus spinning on its end, acting as a portal through which 
// Mascarvin reaches the dying in Sybarus.

inherit "/std/object";
#include "../dead.h"

void
create_object()
{
    set_name("_portal_torus");
    add_name(({"portal", "torus",}));
	add_adj(({"spinning"}));
    set_short("spinning torus");
    set_long("This is a torus that seems to rotate on itself along the inside "
	    +"even as it is spinning on its outer edge. "
	    +"It seems to be made of a dark metal and a reddish stone "
		+"of some kind, perhaps jasper or carnelian. "
		+"In the center of the toroid various images of other places "
		+"flash into view in rapid succession. "
        +"Perhaps this a portal?\n");
	add_item(({"carelian", "reddish stone", "jasper"}),
	    "The stone of the torus is opaque and red, likely jasper or carnelian.\n");
	add_item(({"images", "center of the torus", "location"}),
	    "The torus rotates rapidly and every turn reveals a new location "
		+"in Sybarus.\n");
	add_item(({"skulls", "domes"}), "Creamy white with a pearlescent lustre, "
	    +"some of these skulls are from creatures you do not "
		+"recognize.\n");
		add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 99906);
    add_prop(OBJ_M_NO_GET, "It is far too heavy to move, and besides "
	    +"you'd be a fool to even attempt touching it.\n");

    set_no_show_composite(1);

}
