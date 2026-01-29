#include "/d/Ansalon/common/defs.h"
#include "caravan.h"
#include "path.h"

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define SECSTEP 5
object gWagonbed;
int gMoveAlarm = 0;
int gPosition;
int gTimeAtPos;

mixed *gPath = NERAKA_TO_SANCTION + SANCTION_TO_NERAKA;
string *gMessage = NERAKA_TO_SANCTION_MESSAGES +
    SANCTION_TO_NERAKA_MESSAGES;

void
create_object()
{
    if (!IS_CLONE)
        return;

	set_name("wagon");
	set_adj("large");
	add_adj("covered");

	set_long("The large wagon is covered with " +
	"canvas, protecting the wagonbed. It is pulled by a pair of " +
	"horses. A driver sits on a high seat just behind the horses, " +
	"holding the reins.\n");

	add_item("wagonbed","The wagonbed is protected by an " +
	"arching roof of canvas. A flap at the rear makes it " +
	"possible to enter it.\n");
	add_item("canvas","An arching roof of canvas protects " +
	"the wagonbed.\n");
	add_item(({"horses","pair of horses"}),
	"A pair of brown working horses.\n");
	add_item("driver","The driver sits on the front " +
	"of the wagon, keeping an eye on the wagon and " +
	"the horses. As you approach him, he looks at you expectantly, " +
	"rubbing his thumb and forefinger together.\n");
    add_item(({"remounts","string of remounts","string"}),
    "A line of horses tied together with ropes trail after the wagon.\n");
	add_prop(OBJ_I_WEIGHT, 950000);
	add_prop(OBJ_I_VOLUME, 760000);
	add_prop(OBJ_M_NO_GET, 1);

	setuid();
	seteuid(getuid());
	if (LOAD_ERR(WAGONBED))
	{
	    (NERAKA_ADMIN)->adminlog("Could not load file: " + WAGONBED);
		set_alarm(1.0,0.0,remove_object);
	}
	gWagonbed = find_object(WAGONBED);
	if (gWagonbed)
		gWagonbed->set_wagon(TO);
}

public void
tell_wagon(string s)
{
	tell_room(gWagonbed, s);
}


public void
set_wagonbed(object wagonbed)
{ gWagonbed = wagonbed; }

public object
query_wagonbed()
{ return gWagonbed; }

string
set_wagon_empty()
{
    gWagonbed->set_cargo(0);
    tell_room(E(TO),"Some people rush out and begin unloading the wagon.\n");
    return "Some people start unloading the cargo.\n";
}

string
set_wagon_full()
{
    string cargo;
    cargo = CARGO_TYPES[random(sizeof(CARGO_TYPES))];
    gWagonbed->set_cargo(cargo);
    tell_room(E(TO),"Some people rush out and begin loading the wagon with " +
        cargo + ".\n");
    return "Some people begin loading the wagon with " + cargo + ".\n";
}   

int
is_wagonstop(object r)
{
    if (objectp(r) && member_array(file_name(r), WAGON_STOPS) != -1)
        return 1;
    else
        return 0;
}

public int
query_moving()
{
	if (E(TO) && is_wagonstop(E(TO)))
		return 0;
	else
		return 1;
}

void
do_a_move()
{
	string s;
	object r,oldr;
	if ((gPosition==-1) || (gTimeAtPos>=gPath[gPosition*2+1]))
	{
		gPosition++;
		if (gPosition >= (sizeof(gPath)/2))
			gPosition = 0;
		s = gPath[gPosition*2];
		LOAD_ERR(s);
		r = find_object(s);
		if (!objectp(r))
			tell_wagon("Fatal error, couldn't find path! " +
				"Contact a wizard to help you out.\n");

		oldr = E(TO);
		move(r);
		if (is_wagonstop(r))
		{
			tell_wagon("The wagon stops as you reach your " +
				"destination.\n");
		}
		else if(oldr && is_wagonstop(oldr))
		{
			tell_wagon("You bump against the side of the " +
			"wagon as it starts moving.\n");
		}
		if (gMessage[gPosition])
		    tell_wagon(check_call(gMessage[gPosition]));
		gTimeAtPos = 0;
	}
	else
		gTimeAtPos += SECSTEP;
}

void
start_moving()
{
	if (gMoveAlarm)
		return;
	gPosition = -1;
	gMoveAlarm = set_alarm(1.0, 5.0, do_a_move);
}

void
stop_moving()
{
	if (!gMoveAlarm)
		return;
	remove_alarm(gMoveAlarm);
	gMoveAlarm = 0;
}
void
leave_env(object env, object to)
{
	::leave_env(env, to);
	if (env && env->query_prop(ROOM_I_IS))
	{
		tell_room(env, "The " + short() + 
		" rumbles away, in a cloud of dust.\n");
	}
}

void
enter_env(object env, object from)
{
	::enter_env(env, from);
	if (env && env->query_prop(ROOM_I_IS))
	{
		tell_room(env, "A " + short() + 
		" rumbles in.\n");
	}
}

int
do_enter(string arg)
{
    object steed;
    
	NF("Enter what? The wagon perhaps?\n");
	if ((!stringp(arg)) || !((arg == "wagon") ||
		(arg == "the wagon")))
	{ return 0; }

	NF("The driver stops you from entering the wagon. Perhaps he wants " +
	    "some sort of financial recompense...\n");
	if (!TP->query_prop(NERAKA_PLAYER_I_BRIBED_DRIVER))
		return 0;

    TP->remove_prop(NERAKA_LIVE_O_WAGON_STEED);
    if ((steed = TP->query_prop(LIVE_O_STEED)) && (!TP->query_wiz_level()))
    {
        TP->command("$dismount");
        TP->catch_msg("You tie your " + steed->short() + " to a line of " +
            "remounts following the wagon, so you can fetch it when you " +
            "leave the wagon.\n\n");
        tell_room(E(TP), QCTNAME(TP) + " ties " + HIS(TP) + " " +
            steed->short() + " to a line of remounts following the wagon.\n",
            ({ TP }));
        TP->add_prop(NERAKA_LIVE_O_WAGON_STEED, steed);
        steed->move_living("M",AVOID);
        
    }
    write("You climb into the covered wagon.\n");
	if (!TP->move_living("entering the wagon",gWagonbed,1))
		TP->add_prop(NERAKA_PLAYER_I_BRIBED_DRIVER,
		    TP->query_prop(NERAKA_PLAYER_I_BRIBED_DRIVER) - 1);
    else if (steed = TP->query_prop(NERAKA_LIVE_O_WAGON_STEED))
    {
        write("As you failed to enter the wagon, you retrieve your horse.\n");
        steed->move_living("M",E(TP));
        TP->remove_prop(NERAKA_LIVE_O_WAGON_STEED);
    }
        
	return 1;
}

int
do_bribe(string arg)
{
	int *c;
	int pay;
	NF(C(query_verb()) + " whom? The driver perhaps?\n");
	if ((!stringp(arg)) || !((arg == "driver") ||
		(arg == "the driver")))
	{ return 0; }

	c = MONEY_COINS(TP);
	if (c[0] >= 6)
		pay = 6;
	else if (c[1] > 0)
		pay = 12;
	else if (c[2] > 0)
		pay = 144;
	else if (c[3] > 0)
		pay = 1728;
	else
	{
		NF("The driver looks at what you have to offer, and " +
			"laughs at you.\n");
		return 0;
	}

	MONEY_ADD(TP,-pay);
	TP->add_prop(NERAKA_PLAYER_I_BRIBED_DRIVER,
	    TP->query_prop(NERAKA_PLAYER_I_BRIBED_DRIVER) + 1);
	write("You hand the driver " + MONEY_TEXT_SPLIT(pay) +
		", and he nods at you, indicating that the wagon is, in a sense, " +
	    "all yours.\n");
	say(QCTNAME(TP) + " hands some coins to the driver.\n");
	return 1;
}

void
init()
{
	::init();
	add_action(do_enter,"enter");
   add_action(do_enter,"board");
	add_action(do_bribe,"bribe");
	add_action(do_bribe,"pay");
	add_action(do_bribe,"tip");
}
