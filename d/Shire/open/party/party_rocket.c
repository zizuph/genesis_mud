/*
 *  party_rocket.c
 *  Cloned by the party_room.c when someone buy a rocket.
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Shire/open/randomize.h"
#include "party.h"

void describe_explosion();

object rocketroom;
string nameMET, nameNONMET;

void
create_object()
{
    set_name("rocket");
    set_pname("rockets");
    set_adj("fine");
    set_short("fine rocket");
    set_pshort("fine rockets");
    set_long("There is a fuse at the end of the rocket.\n");
    add_item("fuse", "Take a wild guess what you're suppose to do with it...\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 50);
}

void
init()
{
    ::init();

    if (this_player() != environment())
	return;

    add_action("do_fire", "fire");
    add_action("do_fire", "shoot");
    add_action("do_light", "light");
}

int
do_fire(string str, int nocheck)
{
    object *obs;
    string txt;

    if (!nocheck)
    {
	notify_fail(query_verb() + " what?\n");

	if (!str)
	    return 0;

	obs = FIND_STR_IN_OBJECT(str, this_player());

	if (!obs || !sizeof(obs) || obs[0] != this_object())
	    return 0;
    }
    rocketroom = environment(this_player());
    nameMET    = METNAME;
    nameNONMET = "the " + this_player()->query_nonmet_name();
    write("You light the rocket which takes off with an incredible speed.\n");
    txt = " shoots away a rocket which goes up to the sky.\n";
    say(({break_string(METNAME + txt, 70), break_string(TART_NONMETNAME + txt,
	70) }));
    set_alarm(itof(5 + random(5)), 0.0, &describe_explosion());
    return 1;
}

int
do_light(string str)
{
    if (str == "fuse")
	return do_fire(0, 1);

    return do_fire(str, 0);
}

void
describe_explosion()
{
    string txt1, txt2;

    if (!rocketroom)
	return;

    switch (random(5))
    {
    case 0:
	tell_room(rocketroom, "The sky is lit up in " + random_colour()
		+ " by a wonderful rocket.\n");
	break;
    case 1:
	tell_room(rocketroom, "A rocket explodes into millions of small "
		+ random_colour() + "lights.\n");
	break;
    case 2:
	tell_room(rocketroom, break_string("Millions and millions of demons "
	 + "spread over the world as the rocket explodes in the sky.\n", 70));
	break;
    case 3:
	tell_room(rocketroom, break_string("Everyone gasps in astonishment as "
	+"they see the rocket explode in a multi-colored bolt of fire.\n", 70));
	break;
    case 4:
	txt1 = "The rocket comes down from the sky again. You duck in an "
            +"attempt to evade it. With a big BANG it finally explodes on the "
            +"other side of the room. You better be more careful next time ";
	txt2 = " decides to light another rocket!\n";
	tell_room(rocketroom, ({break_string(txt1 + nameMET + txt2, 70),
		  break_string(txt1 + nameNONMET + txt2, 70)}));
	break;
    }
    remove_object();
    return;
}
