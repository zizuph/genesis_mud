/*
 *  party_champagne.c
 *  Cloned by the party_room.c when someone buys some champagne.
 *  It is not really a drink, so it does not disturb the game balance.
 */
inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#include "/sys/macros.h"
#include "party.h"

int filled;

void
create_object()
{
    set_name(({"bottle", "champagne", "bottle of champagne"}));
    set_pname(({"bottles", "champagne", "bottles of champagne"}));
    set_short("@@my_short_desc");
    set_pshort("@@my_pshort_desc");
    set_long("@@my_long_desc");
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, "@@my_value");
    filled = 2;
}

string
my_short_desc()
{
    switch (filled)
    {
    case 2:
	return "full bottle of champagne";
    case 1:
	return "half-full bottle of champagne";
    case 0:
	return "empty bottle of champagne";
    }
}

string
my_pshort_desc()
{
    switch (filled)
    {
    case 2:
	return "full bottles of champagne";
    case 1:
	return "half-full bottles of champagne";
    case 0:
	return "empty bottles of champagne";
    }
}

string
my_long_desc()
{
    switch (filled)
    {
    case 2:
	return break_string("It seems to be a very good champagne. "
	+"It looks delicious and contains very very little alcohol.\n", 70);
    case 1:
	return break_string("It seems to be very good champagne. "
       +"It is very delicious but only half of it is left. The champagne "
       +"contains very very little alcohol.\n", 70);
    case 0:
	return break_string("It is an empty champagne-bottle. It is worthless. "
       +"You better give it to the butler.\n", 70);
    }
}

int
my_weight()
{
    switch (filled)
    {
    case 2:
	return 1000;
    case 1:
	return 600;
    case 0:
	return 200;
    }
}

int
my_value()
{
    switch (filled)
    {
    case 2:
	return 12;
    case 1:
	return 5;
    case 0:
	return 2;
    }
}

void
init()
{
    ::init();
    add_action("do_drink", "drink");
    add_action("do_cheer", "cheer");
    add_action("do_cheer", "cheers");
}

int
do_drink(string str, int nocheck)
{
    object *obs;

    if (!nocheck)
    {
	notify_fail("Drink what?\n");

	if (!str)
	    return 0;

	obs = FIND_STR_IN_OBJECT(str, this_player());

	if (!obs || !sizeof(obs) || obs[0] != this_object())
	    return 0;
    }

    switch (filled)
    {
    case 2:
	filled = 1;
	write("You drink some champagne from the bottle. It tastes very good "
	    + "and luckily there is still some left.\n");
	say(QCTNAME(this_player()) + " drinks some champagne and smiles "
	    + "happily.\n");
	return 1;
    case 1:
	filled = 0;
	write("You swing the rest of the bottle. It was very good this "
	    + "champagne.\n");
	say(QCTNAME(this_player()) + " finishes "
	+ this_player()->query_possessive() + " bottle of champagne and gives "
	+ "you a drunk look.\n");
	return 1;
    case 0:
	notify_fail("The bottle is empty.\n");
	return 0;
    }
}

int
do_cheer(string str)
{
    object *obs;
    string adj, qp;

    switch (filled)
    {
    case 2:
	adj = "filled";
	break;
    case 1:
	adj = "semi-filled";
	break;
    case 0:
	notify_fail("You cannot cheer with an empty bottle.\n");
	return 0;
    }

    qp = this_player()->query_possessive();
    if (!str || str == "to everyone" || str == "everyone" ||
	str == "to all" || str == "all")
    {
	write("You raise your " + adj + " bottle of champagne high in the air "
	    + "and cheer to everyone. ");
	say(QCTNAME(this_player()) + " raises " + qp + " " + adj +" bottle of "
	  + "champagne and yells: 'Cheers to you all'. ");
	do_drink(0, 1);
	return 1;
    }
    obs = FIND_STR_IN_OBJECT(str, environment(this_player()));

    if (!obs || !sizeof(obs) || !living(obs[0]))
    {
	notify_fail("Cheer who?\n");
	return 0;
    }

    if (present("bottle of champagne", obs[0]))
    {
	this_player()->catch_msg("You hold up your " + adj + " bottle of champagne "
	+ "and cling it with the one " + QTNAME(obs[0]) + " is carrying: "
	+ "Cheers!\n");
	obs[0]->catch_msg(QCTNAME(this_player()) + " holds up " + qp + " " + adj
	+ " bottle of champagne and clings it with yours: Cheers!\n");
	say(QCTNAME(this_player()) + " and " + QTNAME(obs[0]) + " cling their "
	+ "bottles of champagne together.\n", ({ this_player(), obs[0] }));
    }
    else
    {
	this_player()->catch_msg("You hold your " + adj + " bottle of champagne in"
	+ " front of " + QTNAME(obs[0]) + " and yell: CHEERS!\n");
	obs[0]->catch_msg(QCTNAME(this_player()) + " holds " + qp + " " + adj
	+ " bottle of champagne in front of you and yells: CHEERS!\n");
	say(QCTNAME(this_player()) + " holds " + qp + " " + adj + " bottle of "
	+ "champagne in front of " + QTNAME(obs[0]) + " and yells: CHEERS!\n",
	({ this_player(), obs[0]}));
    }
    return 1;
}
