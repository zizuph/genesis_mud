#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

void boil(object ob);

CONSTRUCT_ROOM
{
    set_short("In boiling water");
    set_long("You are swimming in a hot boiling water!\n"
	   + "It seems to be possible to climb up a slippery "
	   + "slope to the east.");

    add_item(({"water"}),
	  "The water steams and you are rapidly scorned!\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_call(({"climb", "up"}), "[up] [the] [slope]", "do_climb");
    add_call("dive", "[into] [the] [water]", "do_dive");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->query_wiz_level())
    {
        return;
    }
    if (living(ob))
    {
        set_alarm(4.0, 0.0, &boil(ob));
    }
    else
    {
// tell_room(TO, "The " + ob->short() + " sinks into the water.\n", 0, ob);
        set_alarm(1.0, 0.0, &tell_room(TO,
            "The @@lang_the_short:/sys/global/language|" +
            file_name(ob) + "@@ sinks into the water.\n"));
        set_alarm(5.5, 0.0, &ob->remove_object());
    }
}

int
do_dive(string str)
{
    string how = query_verb() + (strlen(str)? " "+str : "");
    write("You would not like to " + how + " here!\n");
    write("You would scorch yourself too much.\n");
    return 1;
}

int
do_climb(string str)
{
    int succ;
    int diff;

    if(strlen(str) && (str != "slope" && str != "up"))
	return notify_fail(CAP(query_verb())+ " what?\n");

    diff = DIFF_HARD + 3 * TP->query_encumbrance_weight();

    succ = TP->resolve_task(diff, ({ SS_SWIM, SS_CLIMB }));

    if (succ <= 0)
    {
	if (random(TP->query_skill(SS_SWIM)) < random(TP->query_climb()))
	{
	    write("You try to swim towards the slope, but it is simply too "
		+ "difficult for you to get out of the water. ");
	}
	else
	{
	    write("You manage to get to the slope, but can't manage to climb "
		+ "up the slippery slope.\n");
	}
	if(TP->query_encumbrance_weight() > 20)
	    write("Perhaps you should drop some of your load first?\n");
	say(QCTNAME(TP) + " tried to climb the slope, but slides back into the water.\n");
	return 1;
    }
    else
    {
	write("You successfully manage to climb up the slippery slope!\n");
	TP->move_living("climbing up the slope", THIS_DIR + "shnarrw", 1);
	return 1;
    }
}

void
boil(object tp)
{
    int dam;
    string how;

    if (ENV(tp) != TO)
	return;

/*
    if (random(10))
	dam = 400 + 10 * random(60);
    else
	dam = 2000 + 20 * random(100); // Critical..
*/

    dam = 400 + 10 * random(60);
    dam -= dam * (TP->query_magic_res(MAGIC_I_RES_FIRE)/2 +
		  TP->query_magic_res(MAGIC_I_RES_WATER)/2) / 100;

    if (dam < 3)
	dam = 0;

    switch(dam / 10)
    {
	case 0 :
	    how = "You do not feal the heat.";
	    break;
	case 2..10 :
	    how = "You feel the heat of the steam.";
	    break;
	case 11..20:
	    how = "You are somewhat scorched by the boiling hot water.";
	    break;
	case 21..30:
	    how = "You sigh as the hot water scorches your skin!";
	    break;
	case 31..40:
	    how = "You scream out in pain as the water scorches you!";
	    break;
	case 41..50:
	    how = "You feel the intense hot water scorch your skin!";
	    break;
	case 51..60:
	    how = "You feel an intense pain as hot water scorches your skin!";
	    break;
	case 61..70:
	    how = "You almost faint as the hot water scorches you severely!!";
	    break;
	case 71..80:
	    how = "You scream out in pain as the hot water scorches you!!";
	    break;
	case 81..90:
	    how = "In a terrible pain you gasp for air as your whole body is covered with boiling water!!";
	    break;
	case 91..100:
	    how = "An agonizing pain penetrates you as your body is soaked with hot boiling water!";
	    break;
    }

    tp->catch_msg(how+"\n");
    if (dam > 31)
	say(QCTNAME(tp) + " screams in pain due to the hot water!\n", tp);

    tp->heal_hp(-dam);
    if(HP(tp) <= 0)
	tp->do_die(TO);
    else
        set_alarm(4.0,0.0,&boil(tp));
}
