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
      3*TP->query_skill(SS_CLIMB)) / 5;  /* This is the new way for climb 30 */
    //  2*TP->query_skill(SS_CLIMB)) / 5;    /* This is the old way for 50 climb skill */
}

make_the_room()
{
    set_long("@@long_desc");
    set_short("@@short_desc");
    add_item(({ "wall", "mountain wall" }), BS("The wall is rather steep, "
	+ "but it's rough enough so that an experienced climber might be able "
	+ "to climb it.\n"));
    add_item(({ "rock", "projecting rock" }), "You can't see what's on it " +
      "from here.\n");
    seteuid(getuid());
    if(down_room) down_room->load_me();
    if(up_room) up_room->load_me();
}

init()
{
    ::init();
    add_action("climb", "climb");
}

long_desc()
{
    string text;
    text = "You are climbing " + where + " in the " + area + ". ";
    text += "It is a very uncomfortable place, cold and windy. High above you can see a projecting rock. ";
    if (extraline)
	text += extraline;

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
	if(down_room != find_object(THIS_DIR + "base"))
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
    skillvalue = TP->query_skill(SS_CLIMB);
    if (skillvalue < 10)
    {
	write(BS("You examine the wall closely and realize that you are not sufficiently " +
	    "skilled in climbing, so you dare not to try it.\n"));
	return 1;
    }
    rnd = random(20);
    if (skillvalue + rnd > 35)
    {
	write("You skillfully climb up.\n");
	say(QCTNAME(TP) + " climbs up.\n", TP);
	TP->move_living("M", up_room, 1);
	TP->add_fatigue((rnd+skillvalue)/6 - 25);
	say(QCTNAME(TP) + " arrives climbing up from below.\n", TP);
	return 1;
    }
    if (skillvalue + rnd > 30)
    {
	write("You try to climb higher, but you lose your grip!\n\n" +
	  "Fortunately you don't fall much.\n");
	say(QCTNAME(TP) + " begins to climb higher, but " +
	  TP->query_pronoun() + " loses " + TP->query_possessive() +
	  " grip and slides back.\n");
	TP->heal_hp(-random(40) - 30);
	TP->add_fatigue((rnd+skillvalue)/10 - 15);
	return 1;
    }
    write("You try to climb higher, but you lose your grip!\n");
    say(QCTNAME(TP) + " begins to climb higher, but "+
      TP->query_pronoun() + " loses " +
      TP->query_possessive() + " grip and falls down!\n", TP);
    do_fall(TP,0);
    return 1;
}

int
climb_down()
{
    int skillvalue, rnd;
    skillvalue = TP->query_skill(SS_CLIMB);
    if (skillvalue < 10)
    {
	write("You look down and realize that you are not adequately skilled " +
	  "in climbing, so you dare not to try it.\n");
	return 1;
    }
    rnd = random(20);
    if (skillvalue + rnd > 20)
    {
	write("You skillfully climb down.\n");
	say(QCTNAME(TP) + " begins to climb down.\n", TP);
	TP->move_living("M", down_room, 1);
	TP->add_fatigue((rnd+skillvalue)/10 - 15);
	say(QCTNAME(TP) + " arrives climbing down from above.\n", TP);
	return 1;
    }
    if (skillvalue + rnd > 15)
    {
	write("You begin to climb down, but you lose your grip!\n\n" +
	  "Fortunately you don't fall much.\n");
	say(QCTNAME(TP) + " begins to climb down.\n"
	  + CAP(TP->query_pronoun()) + " loses " +
	  TP->query_possessive() + " grip!\n", TP);
	TP->heal_hp(-random(40) - 30);
	TP->move_living("M", down_room, 1);
	TP->add_fatigue((rnd+skillvalue)/12 - 12);
	say(QCTNAME(TP) + " loses " + TP->query_possessive() +
	  " grip while climbing down,\n" +
	  "but fortunately doesn't fall much.\n", TP);
	return 1;
    }
    write("You begin to climb down, but you lose your grip!\n");
    say(QCTNAME(TP) + " begins to climb down the wall.\n"
      + CAP(TP->query_pronoun()) + " loses " +
      TP->query_possessive() + " grip!\n", TP);
    do_fall(TP,1);
    return 1;
}

int
climb(string str)
{
    NF("Climb what?\n");
    if (str == "up" || str == "wall")
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
