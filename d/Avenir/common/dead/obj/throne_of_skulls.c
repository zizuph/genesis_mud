inherit "/std/object";
#include "../dead.h"

void
create_object()
{
    set_name("_throne_of_skulls");
    add_name(({"mascarvin's seat", "seat", "throne", "throne of skulls", 
	    "dais"}));
	add_adj(({"cushioned", "bone", "skull"}));
    set_short("throne of skulls");
    set_long("This is the seat of Mascarvin, a throne made of bones. "
	    +"Resting atop a dais of three concentric rings of skulls, nearly "
		+"twice as wide as it is deep, it is covered in a variety of cush"
		+"ions upon which the goddess lounges. The skulls have jewels for "
		+"eyes, and the domes gleam with a pearly white lustre. "
		+"Spectral figures flicker in and out of view, some kneeling, "
		+"some standing protectively, others laying prone in suppli"
		+"cation before the throne.\nArtfully made, this throne is "
		+"as beautiful as it is macabre."
        +"\n");
	add_item(({"cushion", "cushions"}),
	    "Cushions in a wide variety of shapes and sizes are strewn "
		+"upon the seat and against the back of the throne.\n");
	add_item(({"skull eyes", "skulls eyes", "gemstone eyes", "jewels",
	    "eyes", "jewel eyes", "eye sockets"}),
	    "Thousands of jewels glitter in the flickering rushlight. "
		+"They are round and multifaceted and fill the eye sockets "
		+"of each skull.\n");
	add_item(({"skulls", "domes"}), "Creamy white with a pearlescent lustre, "
	    +"some of these skulls are from creatures you do not "
		+"recognize.\n");
	add_item(({"figures", "spectral figures"}),
	    "Everywhere about the throne you can see figures fading "
		+"in and out of view, like visual echoes.\n");
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 99906);
    add_prop(OBJ_M_NO_GET, "It is far too heavy to move.\n");

    set_no_show_composite(1);

}
