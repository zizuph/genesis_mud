// file name:        /d/Avenir/common/dead/obj/scepter_top.c
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
    set_name("_Hegemon_Scepter_Top");
    add_name(({"scepter", "top", "head"}));
    add_adj(({"trefoil", "hegemon's", "kesoit", "ornate"}));
    set_short("ornate kesoit scepter");
    set_long("This is the scepter of office of one of the former "
	    +"Hegemons of Sybarus. The ornate head has been carved from a "
        +"three-sided block of the fragrant, reddish black wood of the "
		+"kesoit tree. The very top of it is flat, with a trefoil knot "
		+"carved in bas relief, while each of the three sides is ornately " 
		+"carved filigree embellished with precious metals and gems. "
        +"There is a pleasant scent, both musky and somewhat spicy, "
	    +"emanating from the wood itself. A few inches of glossy smooth " 
		+"wood is extending from the base of the scepter's head, "
		+"ending in a jagged break.\n");
    add_item(({"head", "top", "knot", "trefoil"}), 
	    "The top of the scepter is has a trefoil "
	    +"knot carved into the kesoit wood. The trefoil is a symbol of "
		+"Sybarus.\n");
	add_item(({"filigree"}), "It is very ornate, so much so that it looks "
	    +"like it is made of lace and not wood.\n");
	add_cmd_item("wood", "smell", "It smells pleasantly of spice and musk.\n");
    add_item(({"break", "jagged end"}),
	    "A few inches of beautifully polished wood marred by a jagged break. "
       +"It looks like someone intentionally broke the wand off the scepter.\n"); 		
	
	add_prop(OBJ_I_BROKEN, 1);
    set_hit(20 + random(5));
    set_pen(20 + random(5));
    add_prop(OBJ_I_VALUE, 1000);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}

