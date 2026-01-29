// file name:        /d/Avenir/common/dead/obj/scepter_wand.c
// creator(s):       Lilith, July 2021
// revision history: 
// purpose:          Quest obj for Hegemon Ghost Quest
// bug(s):           
// to-do:
inherit "/d/Avenir/inherit/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "../dead.h"

void
create_weapon()
{
    set_name("_Hegemon_Scepter_Wand");
    add_name(({"scepter", "wand",}));
    add_adj(({"skull-tipped", "hegemon's", "kesoit" }));
    set_short("skull-tipped kesoit wand");
    set_long("This is a wand made of silky smooth reddish wood. "
	    +"The top ends in a jagged break, while the bottom ends "
		+"in a grinning skull draped in vines and leaves. It has "
		+"a distinctive smell, reminscent of ginger and cedar, "
		+"with a hint of musk.\n");
    add_item(({"top"}), 
	    "The top of the wand is jagged and splintered.\n");
	add_cmd_item("wood", "smell", "It smells pleasantly of spice and musk.\n");
    add_item(({"tip", "skull", "skull-tip", "bottom", "vines", "leaves"}),
	    "The bottom end of the kesoit wand is ornately carved with a grinning skull. "
	    +"Vines and leaves twine down the shaft and cradle the skull.\n"); 		
	
	add_prop(OBJ_I_BROKEN, 1);
    set_hit(20 + random(5));
    set_pen(20 + random(5));
    add_prop(OBJ_I_VALUE, 1000);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}

