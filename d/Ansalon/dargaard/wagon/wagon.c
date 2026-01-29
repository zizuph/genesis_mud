#include "/d/Ansalon/common/defs.h"
#include "path.h"
#include "caravan.h"

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define SECSTEP 5
object gWagonbed;
int gMoveAlarm = 0;
int gPosition;
int gTimeAtPos;

mixed *gPath = DARGAARD_TO_NIGHTLUND + NIGHTLUND_TO_DARGAARD;
string *gMessage = DARGAARD_TO_NIGHTLUND_MESSAGES + NIGHTLUND_TO_DARGAARD_MESSAGES;

void
create_object()
{
    if (!IS_CLONE)
        return;

	set_name("chariot");
	set_adj("massive");
	add_adj("black");
        set_short("massive black chariot");
	set_long("This is a massive black chariot. Looking at it, you have "+
        "a sense that it has a soul of its own. Teeth from former "+
        "riders rest on the wheels making a horrid noise that sends "+
        "a chill down your spine. Two horses of midnight black are "+
        "pulling it. A driver sits on a high seat just behind the horses, " +
	"holding the reins.\n");

	add_item(({"horses","pair of horses"}),
	"The horses are wearing white masks made of human bone. They are very skeletal, "+
        "and there eyes have a piercing glow.\n");
	add_item("driver","The driver sits on the front " +
	"of the chariot, keeping an eye on it and " +
	"the horses. His face is covered with a black shroud making "+
        "it impossible for you to see his face.\n");
        add_item(({"remounts","string of remounts","string"}),
        "A line of horses tied together with ropes trail after the wagon.\n");
	add_prop(OBJ_I_WEIGHT, 950000);
	add_prop(OBJ_I_VOLUME, 760000);
	add_prop(OBJ_M_NO_GET, 1);

	setuid();
	seteuid(getuid());

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
    tell_room(E(TO),"The charioteer shouts: Passengers may now enter the chariot!\n");
    return "The charioteer shouts: Passengers may now enter the chariot!\n";
}

string
set_wagon_full()
{
    string cargo;
    cargo = CARGO_TYPES[random(sizeof(CARGO_TYPES))];
    gWagonbed->set_cargo(cargo);
    tell_room(E(TO),"The charioteer shouts: Passengers may now enter the chariot!\n");
    return "The charioteer shouts: Passengers may now enter the chariot!\n";
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
			tell_wagon("The charioteer pulls the reins and the horses stop. You have reached your " +
				"destination.\n");
		}
		else if(oldr && is_wagonstop(oldr))
		{
			tell_wagon("The charioteer shouts a loud command at the horses and the " +
			"chariot starts moving.\n");
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
    
	NF("Enter what? The chariot perhaps?\n");
	if ((!stringp(arg)) || !((arg == "chariot") ||
		(arg == "the chariot")))
	{ return 0; }

	NF("The charioteer prevents you from entering the chariot. Perhaps he wants " +
	    "some sort of financial recompense...\n");
	if (!TP->query_prop(DARGAARD_PLAYER_I_BRIBED_DRIVER))
		return 0;

    TP->remove_prop(DARGAARD_LIVE_O_WAGON_STEED);
    if ((steed = TP->query_prop(LIVE_O_STEED)) && (!TP->query_wiz_level()))
    {
        TP->command("$dismount");
        TP->catch_msg("You tie your " + steed->short() + " to a line of " +
            "remounts following the chariot, so you can fetch it when you " +
            "leave the wagon.\n\n");
        tell_room(E(TP), QCTNAME(TP) + " ties " + HIS(TP) + " " +
            steed->short() + " to a line of remounts following the chariot.\n",
            ({ TP }));
        TP->add_prop(DARGAARD_LIVE_O_WAGON_STEED, steed);
        steed->move_living("M",AVOID);
        
    }
    write("You enter the black chariot.\n");
	if (!TP->move_living("entering the black chariot",gWagonbed,1))
		TP->add_prop(DARGAARD_PLAYER_I_BRIBED_DRIVER,
		    TP->query_prop(DARGAARD_PLAYER_I_BRIBED_DRIVER) - 1);
    else if (steed = TP->query_prop(DARGAARD_LIVE_O_WAGON_STEED))
    {
        write("As you failed to enter the black chariot, you retrieve your horse.\n");
        steed->move_living("M",E(TP));
        TP->remove_prop(DARGAARD_LIVE_O_WAGON_STEED);
    }
        
	return 1;
}

int
do_bribe(string arg)
{
	int *c;
	int pay;
	NF(C(query_verb()) + " whom? The charioteer perhaps?\n");
	if ((!stringp(arg)) || !((arg == "charioteer") ||
		(arg == "the charioteer")))
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
		NF("The charioteer looks at what you have to offer, and " +
			"shakes his head at you.\n");
		return 0;
	}

	MONEY_ADD(TP,-pay);
	TP->add_prop(DARGAARD_PLAYER_I_BRIBED_DRIVER,
	    TP->query_prop(DARGAARD_PLAYER_I_BRIBED_DRIVER) + 1);
	write("You hand the charioteer " + MONEY_TEXT_SPLIT(pay) +
		", and he nods at you, indicating that the chariot has a seat for you.\n");
	say(QCTNAME(TP) + " hands some coins to the charioteer.\n");
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
