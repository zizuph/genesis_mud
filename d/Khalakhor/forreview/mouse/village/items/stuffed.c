/* a stuffed animal coded by Elizabeth Cook/Mouse, November 1996 */
 
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void create_weapon()  {
	set_name("bear");
        set_adj("stuffed");
	set_short("stuffed bear");
	set_long("A severely bedraggled stuffed bear. His left ear is "+
			"torn and a small bit of fluffy stuffing is popping out from the "+
			"seam in his right arm. Only one pearly white button eye peers "+
			"out of his face at you. A small piece of black pompon is left "+
			"where his little nose use to be and a little red felt tongue "+
			"sticks out where his mouth would be. His cocoa brown fur is "+
			"matted in the places he hasn't gone bald. His arms sag downward "+
			"from being hugged around his tummy so much. He has a nubble of "+
			"tail on his behind.\n");
	set_hit(3);
        set_pen(1);
        set_wt(W_CLUB);
        set_dt(W_BLUDGEON);
        set_hands(W_ANYH);

        add_prop(OBJ_I_WEIGHT, 250);
        add_prop(OBJ_I_VOLUME, 250);
       
}

void init()
{
     ::init();
     add_action("do_hug","hug");
}

int do_hug(string str)
{
	if((str == "bear")||(str == "stuffed bear"))
	{
		write("You hug your bear.\n");
		say(this_player()->query_cap_name()+" hugs the bear.\n");
		return 1;
	}
	return 0;
}
