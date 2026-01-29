/* A beer tent in Tantallon, coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit TANTALLON_INSIDE;


load_bartender()
{
    clone_object(MON + "bartender4")->move(TO);
    tell_room(TO, "A bartender appears behind the bar.\n");
}

load_guard()
{
    clone_object(MON + "beerguard4")->move(TO);
    tell_room(TO, "A drunk human arrives.\n" +
      "The drunk human cries: Give me a beer!\n");
}

reset_tantallon_room()
{
    if (!present("drunk"))
	set_alarm(1.0,0.0,"load_guard");
    if (!present("bartender"))
	set_alarm(1.0,0.0,"load_bartender");
}

create_tantallon_room()
{
    set_short("Inside the Guardians Pub");
    set_long(BS(
	"You are now inside the Guardians Pub. The pub itself is a small " +
	"tent and around you stand many guards drinking and singing. In " +
	"one corner there is a large bar where the beers are being served. " +
	"Going north would take you out but there is no reason for you " +
	"to leave now.", SL));

    add_item("tent",
      "It's a small tent filled with people.\n");
    add_item(({"people", "guards"}), BS(
	"They are all guards and like to drink and sing but apart from " +
	"that they don't seem to have much in common. But then again, " +
	"isn't that what life is all about?", SL));
    add_item("sign",
      "It's bolted to the bar. You can read it.\n");
    add_item("bar", BS(
	"It's a large wooden bar with a lot of spilled beer on it. There " +
	"is also a sign to read for you.", SL));

    add_cmd_item("sign", "read", "The sign reads: 12 " +
      "copper coins for a beer.\n");
    /* Macker changed this line from 12 cc to 12 copper coins
    since the bartender only accepts copper coins. (9/19/94) */

    add_exit(TDIR + "city21", "north", "@@let_go");
    reset_room();

    add_prop(ROOM_I_HIDE, 9);

    INSIDE;
}

sing(arg)
{
    object ob;
    if (!arg)
	arg = "Hell and gore, shung hop father Allan lannan lay";
    write("You start to sing:\n     " + arg + " . . . . . . . . .\n" +
      BS("Suddenly everyone stops singing and starts looking at you. " +
	"Then they shrug and start to sing again.", SL));
    say(QCTNAME(TP) + " starts to sing:\n     " + arg +
      "\nIt doesn't sound very nice.\n");

    /* For the tourist quest. */
    if ((ob = present("tour2", TP)) && present("drunk", TO))
    {
	write("The guard however liked the singing and smiled at you.\n");
	say("But however the drunk guard seemed to like it.\n");
	ob->set_arr("guard");
    }
    return 1;
}

let_go()
{
    object *ob, obj;
    int i;

    if (TP->query_invis() || TP->query_prop(OBJ_I_HIDE) ||
      !(obj = present("bartender", TO)) || !living(obj))
	return 0;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->id("guard_beer"))
	{
            if(TP->query_race_name() == "ogre")
            {
               write("The bartender moves to stop you from leaving without "+
                     "finishing the beer, but thinks twice about getting in "+
                     "the way of an ogre. He lets you pass without a word.\n");
               say("The bartender moves to stop " +QTNAME(TP)+ " from leaving "+
                     "with a beer, but decides against getting in the way of "+
                     "an ogre!\n");
               return 0;
            }

	    write(BS("The bartender sees you move for the door but won't let " +
		"you go away without finishing that beer.", SL));
	    say(QCTNAME(TP)+" tried to leave but the bartender saw there\n" +
	      "was some beer left to drink.\n");
	    return 1;
	}
    return 0;
}

hide()
{
    write("You hide behind the bar but then you realize you look foolish.\n");
    say(QCTNAME(TP) + " looks foolish trying to hide behind the bar.\n");
    return 1;
}

throw_object()
{
    if (!present("bartender", TO))
    {
	write("" +
	  "As you start to make the throwing motion you get scared you\n" +
	  "would break something and stop.\n");
	say("For a second it looked like " + QTNAME(TP) + " was going\n" +
	  "to throw something.\n");
	return 1;
    }

    write("" +
      "As you start to make the throwing motion the bartender catches\n" +
      "your arm. 'Stop that', he tells you.\n");
    say(QCTNAME(TP) + " tried to throw something but the bartender stopped " +
      TP->query_objective() + ".\n");
    return 1; 
}

dig()
{
    write("You try to dig but the ground is too hard.\n");
    say(QCTNAME(TP) + " tries to dig.\n");
    return 1; 
}

init()
{
    ::init();
    ADA("sing");
    ADA("hide");
    add_action(throw_object, "throw");
    ADA("dig");
}
