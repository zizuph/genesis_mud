#include "defs.h"

inherit "/std/armour";
inherit "/d/Shire/common/lib/tell";

#include <wa_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>

#define RISE	  10

int visor_closed;
int visor_vision;
object wearer;

create_armour()
{
    set_name("helmet");
    add_name(({"helmet's visors","helmet visors",
	       "visors on helmet","visors of helmet"}));
    add_pname("helmets");
    set_adj("visored", "metal");
    set_short("@@my_short@@");
    set_pshort("visored metal helmets");
    set_long("@@my_long@@");
    add_item(({"visors","visor"}), "@@exa_visor@@");

    set_at(A_HEAD);
    set_af(this_object());

    add_prop(OBJ_I_WEIGHT, 2*1000);
    add_prop(OBJ_I_VOLUME, 420);
    add_prop(OBJ_I_VALUE,  200);

    visor_closed = 0;
    visor_vision = 0;
}

init()
{
    ::init();
    add_action("do_open","open");
    add_action("do_close", "close");
}

void
vision_rise(int up)
{
    if(!wearer)
	return;

    ADD_SKILL(wearer, SS_AWARENESS, up*RISE);
    visor_vision += up;

    call_out("inform_vision", 0);
}

inform_vision()
{
    switch(visor_vision) {
	case 0: wearer->catch_msg(
	    "You notice that you are completely aware now and complete vision.\n");
	    break;
	case -1: wearer->catch_msg(
	    "You notice that you have a poor sideview.\n");
	    break;
	case -3: wearer->catch_msg(
	    "You can almost see nothing now, since your visors are down.\n");
	    break;
	default:
	    wearer->catch_msg("This should not happen.\n");
    }
}


mixed
wear(object to)
{
    wearer = this_player();

    if(visor_closed)
	vision_rise(-3);
    else
	vision_rise(-1);
    return 0;
}

mixed
remove(object to)
{
    if(visor_closed)
	vision_rise(3);
    else
	vision_rise(1);

    wearer = 0;
    return 0;
}


int query_is_visored() { return 1; }

int
filter_is_visored(object which)
{
    return which->query_is_visored();
}

int can_open() { return visor_closed = 1; }

int
filter_can_open(object which)
{
    return which->can_open();
}

int
filter_can_close(object which)
{
    return !which->can_open();
}

void
open_visors()
{
    visor_closed = 0;
    if (query_worn())
    {
	vision_rise(2);
	query_worn()->query_combat_object()->cb_update_armour(TO);
    }
}

void
close_visors()
{
    visor_closed = 1;
    if (query_worn())
    {
	vision_rise(-2);
	query_worn()->query_combat_object()->cb_update_armour(TO);
    }
}

int
do_open(string arg)
{
    object *obs;

    arg = replace_strings(arg,
	      ({ "visors", "visor" }), ({ "helmets", "helmet" }));

    if (index(arg, "helm") != -1)
	return notify_fail("Open what? The visors?\n");

    obs = FIND_STR_IN_OBJECT(arg, TP);
    obs = filter(obs, "is_visored_helmet", TO);
    obs = filter(obs, "can_open", TO);

    if (sizeof(obs))
    {
	write("You open the visors of your " + COMPOSITE_DEAD(obs) + ".\n");
	say(QCTNAME(TP) + " opens the visors of " + HIS_HER(TP) +
	    QCOMPDEAD + ".\n");

	obs -> open_visors();
	return 1;
    }
    return 0;
}



do_close(string arg)
{
    object *obs;

    arg = replace_strings(arg,
	      ({ "visors", "visor" }), ({ "helmets", "helmet" }));

    if (index(arg, "helm") != -1)
	return notify_fail("Open what? The visors?\n");

    obs = FIND_STR_IN_OBJECT(arg, TP);
    obs = filter(obs, "is_visored_helmet", TO);
    obs = filter(obs, "can_open", TO);

    if(sizeof(obs))
    {
	write( "You close the visors of your " + COMPOSITE_DEAD(obs) + ".\n");
	say( QCTNAME(TP) + " closes the visors of " + HIS_HER(TP) +
	     QCOMPDEAD + ".\n" );

	obs -> close_visors();
	return 1;
    }
    return 0;
}


string
my_short()
{
    if(visor_closed)
	return "closed visored metal helmet";
    else
	return "opened visored metal helmet";
}

string
my_long()
{
    string str =
	"This is a metal helmet which covers all your head. It also "+
	"has a visor over the face which you can open or close. ";

    if(visor_closed)
	return str + "The visors are now closed, thereby increasing the "
		   + "protection against face hits.\n";
    else
	return str + "The visors are open so you can see better, but they "
		   + "give no protection against face hits.\n";
}

string
exa_visor()
{
    if(visor_closed) return
	"The visors of the metal helmet are closed.";
    else return
	"The visors of the metal helmet are opened.";
}

int
query_ac()
{
    if(visor_closed)
	return 40;
    else
	return 22;
}

int *
query_am(int hid)
{
    if(visor_closed)
	return ({ 0, 0, 0 });
    else
	return ({ -2, 0, 2 });
}
