/*
 * other/gates/v-15.c
 *
 * By Skippern 20(c)01
 *
 * A Gate.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";
inherit DOL_LIB + "gates.c";
inherit "/lib/unique";

/* Globale variables */
string text;

/* Prototypes */
string east_gate();
string north_gate();
string west_gate();
string last_vbfc(int i);

void
delay()
{
    clone_object(DOL_NPC + "citizen1")->move(DOL_HILLS + "streets/o-13");
}

public void
create_dol_amroth()
{
    set_short("a room within the walls");
    set_extralines("High walls surrounds this place.");
    set_lastline("There are some niches in along the walls, probably used " +
		 "by guards, but for some reason they are empty now.");
    set_vbfc_last(&last_vbfc(0));
    set_no_of_lamps(4);
    set_alarm(5.0, 0.0, &delay());
    reset_room();

    add_item( ({ "wall", "walls" }), "The walls are high and made from " +
	      "granite. Those building the wall have done a superior job " +
	      "and the wall is so tight that you could not press the " +
	      "tiniest knife blade into the largest openings in it. " +
	      "You guess it would survive a catapult attack.\n");
    add_item( ({ "gate", "gates" }), &last_vbfc(1));
    add_item( ({ "west gate", "large iron gate", "iron gate" }), &west_gate());
    add_item( ({ "north gate", "large wooden gate", "wooden gate" }),
	      &north_gate());
    add_item( ({ "east gate", "iron plated gate", "plated gate" }),
	      &east_gate());

    set_sound_detail("From time to time the wind makes an almost silent " +
		     "sound of whining as it blows through the gates.");

    add_exit(DOL_TRADE + "streets/v-14", "north", &inner_gate(), 1, 
	     &inner_visible());
    add_exit(DOL_OTHER + "gates/w-15", "east", &outher_gate(), 1, 
	     &outher_visible());
    add_exit(DOL_OTHER + "closed", "west", &closed_gate(), 1, 
	     &closed_visible());
}

void
reset_room()
{
    object ob;
    ::reset_room();
    ob = clone_unique(DOL_NPC + "citizen1", 10);
    ob->move(this_object());
    ob = clone_unique(DOL_NPC + "citizen2", 3);
    ob->move(this_object());
    ob = clone_unique(DOL_NPC + "citizen3", 3);
    ob->move(this_object());
}

string
east_gate()
{
    text = "This iron plated gate leads east, connecting, or if you " +
        "like shields Dol Amroth from the rest of the world. It is " +
        "made out of huge wooden beams, with large iron plates nailed " +
        "on them as a shield. ";

    if  (outher_gate() == 1)
        text += "The iron plated gate is closed. ";
    else
        text += "The iron plated gate to is open. ";

    text += "A small hatch is made in one of the doors enabeling guards " +
        "to check what goes on outside the gate when it is closed.\n";

    return text;
}

string
west_gate()
{
    text = "This large iron gate leads west. It is made out of " +
        "huge blocks or plates who are welded together. Some of the " +
        "squares on the gate have lighter and some have darker colours. ";
/*
    if  (closed_gate() == 1)
        text += "The large iron gate is closed and barred. ";
    else
        text += "The large iron gate is open. ";
*/
        text += "The large iron gate is closed and barred. ";

		text += "It looks like it's in prime condition. It would most " +
        "likely resist the hammering of a ram.\n";

    return text;
}

string
north_gate()
{
    text = "This large wooden gate leads north into the city of " +
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
last_vbfc(int i)
{
    text = "Three huge gates are placed here, making this the entrance " +
		"to the city. The gates seems to be opened and closed from " +
		"somewhere else. The gates seems so sturdy that knocking on " +
		"them wouldn't attract attention of anybody on the other side. ";

//    if  (closed_gate() == 1)
        text += "To the west a large iron gate is closed and barred. ";
/*    else
        text += "A large iron gate leads west. "; */
    if  (inner_gate() == 1)
        text += "The large wooden gate to the north is closed with an " +
	    "iron beam. ";
    else 
        text += "The large wooden gate to the north leads to the city. ";
    if  (outher_gate() == 1)
        text += "An iron plated gate closes the way to the east. ";
    else
        text += "The iron plated gate to the east is open. ";

    if (i == 1)
        text += "\n";

    return text;
}

