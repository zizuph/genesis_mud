inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/d/Gondor/defs.h"
#include "dirdefs.h"

object up_room, down_room;
string where, area, extraline;

void drop_item(object ob);

int
calc_cap()
{
    return (TP->query_stat(SS_STR) +
      TP->query_stat(SS_DEX) +
      TP->query_stat(SS_CON) +
      TP->query_fatigue() +
      3*TP->query_skill(SS_CLIMB)) / 6;  /* For new climb of 30 */
    //  2*TP->query_skill(SS_CLIMB)) / 6;  /* For old climb of 50 */
}

make_the_room()
{
    set_long("@@long_desc");
    set_short("@@short_desc");
    add_item(({ "walls", "wall", "rock walls" }), BS("The walls are rather steep, "
	+ "but an experienced climber might be able to climb up in the chimney.\n"));
    add_item(({ "rock", "projecting rock" }), "You can't see what's on it " +
      "from here.\n");
    add_item("chimney", BS(
	"This is a narrow chimney, going straight up between the rock walls.\n"));
    seteuid(getuid());
    if(down_room) down_room->load_me();
    if(up_room) up_room->load_me();
}

void init()
{
    ::init();
    add_action("climb", "climb");
}

long_desc()
{
    string text, dir;
    text = "You are climbing " + where + " in the " + area + ". ";
    text += "It's a very uncomfortable place. High above you can see a projecting rock. ";
    if (extraline)
	text += extraline;

    dir = "";
    if(up_room)
	dir = "up";
    if(down_room)
    {
	if(dir != "")
	    dir += " or down";
	else
	    dir = "down";
    }
    if(dir != "")
	text = text + "You might be able to climb " + dir + ".";

    return BS(text + "\n");
}

short_desc()
{
    return CAP(where) + " in the " + area;
}

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!living(ob))
	set_alarm(1.0, 0.0, &drop_item(ob));
}

void
drop_item(object ob)
{
    if (ob && present(ob))
    {
	tell_room(TO, "The " + ob->query_name() + " falls down.\n");
	ob->move(down_room);
	tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from above.\n");
	if(down_room != find_object(THIS_DIR + "chimney1"))
	    down_room->drop_item(ob);
    }
}

do_fall(object player, int height)
{
    if(!height)
	write("AAARRRRGGGHHH!!! You fall.\n\n");
    else
	write("\nYou continue to fall down.\n\n");

    height = height + 1;

    tell_room(down_room, "You hear a terrible scream as someone falls down from above.\n");
    player->move_living("M", down_room, 1);
    down_room->do_fall(player, height);
    return;
}

int
climb_up()
{
    int skillvalue, rnd;
    skillvalue = calc_cap();
    if (skillvalue < 25)
    {
	write(BS("You examine the wall closely and realize that you are not sufficiently " +
	    "skilled in climbing, or perhaps you are too weak and too exhausted, but you dare not to try it.\n"));
	return 1;
    }
    rnd = random(20);
    if (skillvalue + rnd > 55)
    {
	write("You skillfully climb up.\n");
	say(QCTNAME(TP) + " climbs up.\n", TP);
	TP->move_living("M", up_room, 1);
	TP->add_fatigue((rnd+skillvalue)/5 - 30);
	say(QCTNAME(TP) + " arrives climbing up from below.\n", TP);
    }
    else if (skillvalue + rnd > 45)
    {
	write("You try to climb higher, but you lose your grip!\n\n" +
	  "Fortunately you don't fall much.\n");
	say(QCTNAME(TP) + " begins to climb higher, but " +
	  TP->query_pronoun() + " loses " + TP->query_possessive() +
	  " grip and slides back.\n");
	TP->heal_hp(-random(40) - 30);
	TP->add_fatigue((rnd+skillvalue)/10 - 25);
    }
    else
    {
	write("You try to climb higher, but you lose your grip!\n");
	say(QCTNAME(TP) + " begins to climb higher, but "+
	  TP->query_pronoun() + " loses " +
	  TP->query_possessive() + " grip and falls down!\n", TP);
	do_fall(TP,0);
    }
    if(TP->query_fatigue() < TP->query_max_fatigue()/2)
	write("Climbing up the chimney has exhausted you.\n" +
	  "Perhaps you should rest before continuing.\n" +
	  "It might be dangerous to climb, as tired as you are.\n");
    return 1;
}

int
climb_down()
{
    int skillvalue, rnd;
    skillvalue = calc_cap();
    if (skillvalue < 20)
    {
	write("You look down and realize that you are not adequately skilled " +
	  "in climbing, so you dare not to try it.\n");
	return 1;
    }
    rnd = random(20);
    if (skillvalue + rnd > 45)
    {
	write("You skillfully climb down.\n");
	say(QCTNAME(TP) + " begins to climb down.\n", TP);
	TP->move_living("M", down_room, 1);
	TP->add_fatigue((rnd+skillvalue)/10 - 25);
	say(QCTNAME(TP) + " arrives climbing down from above.\n", TP);
    }
    else if (skillvalue + rnd > 35)
    {
	write("You begin to climb down, but you lose your grip!\n\n" +
	  "Fortunately you don't fall much.\n");
	say(QCTNAME(TP) + " begins to climb down.\n"
	  + CAP(TP->query_pronoun()) + " loses " +
	  TP->query_possessive() + " grip!\n", TP);
	TP->heal_hp(-random(40) - 30);
	TP->move_living("M", down_room, 1);
	TP->add_fatigue((rnd+skillvalue)/12 - 15);
	say(QCTNAME(TP) + " loses " + TP->query_possessive() +
	  " grip while climbing down,\n" +
	  "but fortunately doesn't fall much.\n", TP);
    }
    else
    {
	write("You begin to climb down, but you lose your grip!\n");
	say(QCTNAME(TP) + " begins to climb down wall.\n"
	  + CAP(TP->query_pronoun()) + " loses " +
	  TP->query_possessive() + " grip!\n", TP);
	do_fall(TP,1);
    }
    if(TP->query_fatigue() < TP->query_max_fatigue()/2)
	write("Climbing down the chimney has exhausted you.\n" +
	  "Perhaps you should rest before continuing.\n" +
	  "It might be dangerous to climb as tired as you are.\n");
    return 1;
}

int
climb(string str)
{
    NF("Climb what?\n");
    if (str == "up")
    {
	if(up_room)
	    return climb_up();
	else
	{
	    write("You cannot climb up here.\n");
	    return 1;
	}
    }
    if (str == "down")
    {
	if(down_room)
	    return climb_down();
	else
	{
	    write("You cannot climb down here.\n");
	    return 1;
	}
    }
    return 0;
}
