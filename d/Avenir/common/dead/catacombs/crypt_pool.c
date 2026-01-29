/*
 *  Pool player jumps into and washes up randomly on the
 *  Shore of the the Necronisi.
 *  Commands to get here are located in crypt_placer.c
 *     Lilith Aug 2021
 *
 * updated: Lilith Oct 2021 added inside and indoors props
 *          Lilith Jan 2022 added +1 to random on move_living
 *                 because there is no shore.c or shore0.c room.
 *                 also added move_along() just in case player gets
 *                 stuck again.
 * 
 */
inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"
#include <macros.h>
#include <stdproperties.h>

public object *diving = ({ });

void
create_crypt_room()
{
    set_short("diving into darkness");
    set_long("Diving in darkness down a pool filled with water and shadows.\n");
    add_prop(ROOM_S_DARK_LONG, "Diving in darkness down a pool filled "+
      "with water and shadows.\n");
    add_prop(ROOM_I_LIGHT, -100);
	add_prop(ROOM_M_NO_ATTACK, 1);
	add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
	add_prop(ROOM_M_NO_SCRY, 1);

    IN;     // inside room
	IN_IN;  // indoors: no source tells and no steeds.
}

/* Shouldn't be needed, but just in case */
void
move_along(object tp)
{
	// Check to make sure they're still here.
	if (!present(tp)) return;
	
	write("You wash ashore, gasping for breath.\n");
    tp->move_living("M", PATH +"shore"+(random(30) +1));
	say(QCTNAME(tp) +" washes up on the shore.\n");
 
}	


private void
diving_down(object ob, int count)
{
    string str;

    if (!ob)
	return;

    if (environment(ob) != this_object())
    {
	    diving -= ({ ob });
	    return;
    }

    if (count > 3)
    {
	    write("You wash ashore, gasping for breath.\n");
	    ob->move_living("M", PATH +"shore"+(random(30) +1));
	    say(QCTNAME(ob) +" washes up on the shore.\n");
	    diving -= ({ ob });
		set_alarm(1.0, 0.0, &move_along(ob));
	    return;
    }

    switch (count)
    {
        case 0: str = "Your heart pounds in your ears.\n";
	      break;
        case 1: str = "Something brushes up against you under the water.\n";
	      break;
        case 2: str = "Your lungs ache and burn. You long for air!\n";
		  break;
        case 3: str = "You feel yourself being tugged up and rolled.\n"
		    +"Water churns and froths around you.\n";
	      break;
    }

    if (query_interactive(ob))
	ob->catch_msg(str + "\n\n");

    set_alarm(2.0, 0.0, &diving_down(ob, ++count));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    diving = filter(diving, objectp);
    if (member_array(ob, diving) == -1)
    {
	    diving += ({ ob });
	    set_alarm(1.5, 0.0, &diving_down(ob, 0));
    }
	
	
}
