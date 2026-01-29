// /d/Avenir/common/holm/obj/caltrop.c
// creator(s):   Lilith  06/06/97
// purpose:      Impede progress thru exits.
// note:         Particularly effective against steeds.
// bug(s):       Have had a problem with players getting the writes
//               from the get_check and test_exit functions. Added
//               a check for presence of this_player(). Hopefully
//               it shouldn't happen anymore. -- Lil, 2 Oct 97
/* Revisions:
 * 	Cirion, Mar 1999: Changed the gloves check from == A_HANDS so armour
 * 			  covering multiple body parts can be checked.
 * 	Lilith, Mar 1999: stat av < 35 may pass.
 * 	Lilith, Apr 1999: Too useful a p-fighting tool. Modified as follows:
 * 			  -No more than 3 caltrops blocking an exit.
 * 			  -25% chance caltrop will break when stepped on.
 * 			  -Weight and volume raised.
 * 			  -66% chance caltrop will not recover.
 * 			  -Will reduce number of clones.
 * 	Lucius, Oct 2017: More changes to prevent p-fighting abuses.
 * 			  -33% chance that caltrop can be taken without gloves.
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include "/d/Genesis/specials/defs.h"

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#define TO	this_object()
#define TP	this_player()
#define ENV	environment

#define HITP		(10 + random(10))
#define WOLF_PROP	"_wolf_i_riding"


public string blocked;
public object glove, boot, wolf, steed;

public string
set_exit_blocked(string s)	{ return blocked = s; }

public string
query_exit_blocked()		{ return blocked; }


public string
my_long(void)
{
    string str = "";

    if (strlen(blocked))
	str = "It is blocking the exit leading "+ blocked +".\n";

    return "This six-pronged caltrop resembles a very large "+
	"child's jack. Each prong is very sharp and as long "+
	"as your middle finger. You might want to be careful "+
	"when handling it, lest you hurt yourself. The caltrop "+
	"can be tossed on the ground near an exit, to impede "+
	"progress and possibly hurt whomever steps upon it.\n"+ str;
}

public void
create_object()
{
    set_name("caltrop");
    add_pname("caltrops");
    set_short("six-pronged caltrop");
    add_adj(({"pronged", "six-pronged"}));
    set_long(my_long);
    set_keep(1);

    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 30 + random(30));
    add_prop(OBJ_I_HIDE, 30);
    add_prop(OBJ_M_NO_GET, "@@get_check@@");
}


/* This function removes the block to the room exit.
 * It also tests if caltrop is broken and removes it.
 */
public void
reset_blocked(void)
{
    int b = ENV()->query_prop("caltrop_blocks_"+ blocked);

    if (b <= 1)
	ENV()->remove_prop("caltrop_blocks_"+ blocked);
    else
	ENV()->add_prop("caltrop_blocks_"+ blocked, b - 1);

    blocked = 0;

    if (query_prop(OBJ_I_BROKEN))
	set_alarm(3.0, 0.0, remove_object);
}

/* This provides a 25% chance the caltrop will be rendered
 * useless when stepped on.
 */
public void
test_break(void)
{
    if (random(4))
	return;

    add_prop(OBJ_I_BROKEN, 1);
    reset_blocked();
}

// Cirion 1999.03.28: changed the check from == A_HANDS so armour
// covering multiple body parts (including hands) can be checked.
public int
worn_glove(object ob)
{
    int at = ob->query_at();
    return ((at & A_R_HAND) || (at & A_L_HAND));
}

public int
worn_boot(object ob)
{
    int at = ob->query_at();
    if (ob->query_worn()) return ((at & A_R_FOOT) || (at & A_L_FOOT));
}

public int
get_check(string str)
{
    object *gloves;

    if (!objectp(ENV()))
	return 0;

    /* Something non-living may trigger this some way... */
    if (!living(TP))
	return 0;

    /* Been having problems with people getting messages for
       the caltrop even though they're elsewhere, so... */
    if (ENV(TO) == TP || !(ENV(TO) == ENV(TP)))
	return 0;

    if (TP->query_wiz_level())
    {
	write("You are so thick-skinned that the pricking "+
	  "of the "+ short() +" doesn't bother you at all :O\n");
	reset_blocked();
	return 0;
    }

    /* Not wearing gloves will cause a little bit of damage
     * but there is a 33% chance of still being able to pick it up.
     */
    gloves = TP->query_armour(-1) + TP->query_clothing(-1);
    if (!sizeof(filter(gloves, worn_glove)))
    {
	TP->heal_hp(-HITP);
	write("OUCH! You prick your fingers trying to get "+
	    "the "+ short() +".\n");

	if (!random(3))
	{
	    reset_blocked();
	    return 0;
	}
	return 1;
    }

    reset_blocked();
    return 0;
}

/*
 * This is the check for players who are riding steeds.
 */
public int
steed_check(object tp)
{
    steed = tp->query_prop(LIVE_O_STEED);

    write("Your "+ steed->short() +" steps on something sharp "+
	"and cries in pain as it tries to go "+ blocked +".\n");
    tell_room(ENV(TO), QCTPNAME(tp) +" "+ steed->short() +
	" screams with pain!\n", tp);

    steed->heal_hp(-(2 * HITP));
    return 1;
}

/*
 * Kalad doesn't use the LIVE_O_STEED prop,
 * so the Riders of the Red Fang get their own check.
 */
public int
wolf_check(object tp)
{
    object *wolves = filter(all_inventory(tp), &->id("wolf"));

    if (!sizeof(wolves))
	return 0;

    write("Your "+ wolves[0]->short() +" steps on something sharp "+
	"and howls in pain as it tries to go "+ blocked +".\n");
    tell_room(ENV(TO), QCTNAME(tp) +"'s "+ wolves[0]->short() +
	" howls in pain!\n", tp);

    wolves[0]->heal_hp(-(2 * HITP));
    return 1;
}

/*
 * This is the function called by the actions 'toss' and 'throw'
 */
public int
toss_it(string str)
{
    int i, b;

    if (ENV(TO) != TP)
    {
	notify_fail("You should get it, first.\n");
	return 0;
    }

    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
	    "[a] / [the] [six-pronged] 'caltrop' [to] [the] %s", str))
    {
	notify_fail(capitalize(query_verb()) +" the caltrop <exit>.\n");
	return 0;
    }

    /* If it is broken it won't work */
    if (query_prop(OBJ_I_BROKEN))
    {
	notify_fail("The prongs of the caltrop have been trod "+
	  "upon so many times that they are bent, rendering "+
	  "the caltrop useless.\n");
	return 0;
    }

    i = member_array(str, ENV(TP)->query_exit_cmds());
    if (i < 0)
    {
	notify_fail("You can't do that. Try <toss caltrop [exit]> "+
	  "to block the exit with the caltrop.\n");
	return 0;
    }

    /* There are too many caltrops blocking the exit */
    b = ENV(TP)->query_prop("caltrop_blocks_"+ str);
    if (b > 2)
    {
	write("Caltrops have been spread liberally there, "+
	  "perhaps you should try another exit?\n");
	return 1;
    }

    say(QCTNAME(TP) +" tosses a "+ short() +" near the exit leading "+
      str +".\n");
    write("You toss the "+ short() +" near the "+
      "exit leading "+ str +".\n");
    set_exit_blocked(str);
    ENV(TP)->add_prop("caltrop_blocks_"+ str, b + 1);
    move(ENV(TP), 1);
    return 1;
}

/*
 * This is the function called by trying to use the blocked exit.
 */
int
test_exit()
{
    object *boots;
    int pass_task, rnd;
    string name;

    /* If its just 'there' it won't do anything */
    if (!blocked)
	return 0;

    // If PVP blocking abilities are turned off.
    if (PVP_ABILITY_DISABLED)
      return 0;

    /* A non-living might test the exit for some strange reason */
    if (!living(TP))
	return 0;

    /* Been having problems with people getting messages for
     *  the caltrop even though they're elsewhere, so...
     */
    name = TP->query_real_name();
    if (ENV(TO) == TP || !present(name, ENV(TO)))
	return 0;

    /* Little people have little feet. They should be able to get by */
    if (TP->query_average_stat() < 35)
    {
	return 0;
    }

    /* Here we check for STEEDS */
    rnd = (random(4)); /* 4 feet, 25% chance all will miss */
    if (TP->query_prop(LIVE_O_STEED))
    {
	if (rnd == 0)
	    return 0;
	else
	{
	    steed_check(TP);
	    return 1;
	}
    }

    if (TP->query_prop(WOLF_PROP))
    {
	if (rnd == 0)
	    return 0;
	else
	{
	    wolf_check(TP);
	    return 1;
	}
    }

    /* Walking on own two feet */
    rnd = random(2);
    if (rnd == 0) /* Two feet, 50% chance both will miss */
	return 0;

    pass_task = TP->resolve_task(TASK_FORMIDABLE, ({ TS_DEX, SS_AWARENESS }));
    if ((pass_task > 0)|| TP->query_wiz_level())
    {
	write("Your superior awareness and agility permit you "+
	  "to negotiate passage around the "+ short() +
	  " without injury.\n");
	return 0;
    }


    if (sizeof(boots = filter(all_inventory(TP), "worn_boot", TO)))
    {
	boot = boots[0];
	if (boot->query_ac() < 10)
	{
	    write("OUCH! You step on something sharp that pushes "+
	      "through the sole of your "+boot->query_short() +".\n");
	    tell_room(ENV(TO), QCTNAME(TP) +" steps on something sharp "+
	      "and hurts "+ TP->query_object() +"self!\n", TP);
	    boot->remove_broken();
	    TP->heal_hp(-(HITP / 2));
	    return 1;
	}
	else
	{
	    write("You step on something sharp on your "+
	      "way "+ blocked +", but your "+ boot->query_short() +
	      " protect your feet.\n");
	    return 0;
	}
    }

    write("Ouch! Something stabbed you in the foot as you "+
      "tried to go "+ blocked +".\n");
    tell_room(ENV(TO), QCTNAME(TP) +" tries to go "+ blocked +", but "+
      "steps on something and hurts "+ TP->query_objective() +"self!\n", TP);
    TP->heal_hp(-HITP);

    /* Test if caltrop should break or not */
    test_break();
    return 1;
}

public void
init()
{
    ::init();

    add_action(toss_it, "toss");
    add_action(toss_it, "throw");

    if (blocked)
	add_action(test_exit,  query_exit_blocked());
}
