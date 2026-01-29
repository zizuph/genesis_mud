/* -*- Mode: C -*-
 *
 * trade/streets/v-14.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";
inherit DOL_LIB + "gates.c";

string last_vbfc();
string gate_item();
 
public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("To the south a high wall towers up.");
    set_lastline("An empty guard post is here, abandoned for some " +
		 "strange reason.");
    set_vbfc_last(&last_vbfc());

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_item( ({ "gate", "large wooden gate", "wooden gate" }),
	      &gate_item());

    set_sound_detail("From time to time the wind makes an almost silent " +
                     "sound of whining as it blows through the gates.");

    add_exit(DOL_OTHER + "gates/v-15", "south", &inner_gate(), 1, 
	     &inner_visible());
    add_exit(DOL_TRADE + "streets/v-13", "north", 0, 1);
    add_exit(DOL_TRADE + "streets/u-14", "west", 0, 1);
}

string
gate_item()
{
    string text;

    text = "This large wooden gate leads south out of the city of " +
        "Dol Amroth. It is made of oaken beams nailed together with " +
        "pinewood crossbeams. ";

    if  (inner_gate() == 1)
        text += "The large wooden gate is closed with an iron beam. ";
    else
        text += "The large wooden gate is open. ";

    text += "The gate is seldom moved, so the hinches looks kind of " +
        "rusty.\n";

    return text;

}

string
last_vbfc()
{
    string text;

    text = "Place information about the gates here. ";
    if(inner_gate() == 1)
        text += "The large wooden gate to the south is closed with an " +
	    "iron beam. ";
    else
        text += "The large wooden gate to the south leads out of the city. ";

    return text;
}
