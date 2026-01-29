/*
 * File Name        : parrot.c
 * By               : Elmore.
 * Inspiration from : A parrot by Ashlar.
 * Date             : Nov. 2000.
 * Description      : This is the free parrot that the
 *                    pirates can collect at the guild.
 *                    But only once each login.
 *
 */

/* Ashlar, 26 May 97 - a parrot! */

/* Navarre July 11: Commented out triggers and alarms for now.
   They caused a problem with lag in the game. 
   I will change this parrot when I get time, to make it say stuff
   again, but not with an endless alarm and not with triggers.
 */



#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/lib/keep";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include <files.h>

#define PARROTSUBLOC    "_ansalon_parrot_subloc"
#define PARROTNAME      "_ansalon_parrot"

#define A_BEAK 0
#define A_CLAWS 1
#define H_HEAD 0
#define H_BODY 1
#define H_WINGS 2
#define MAXLINES    100
#define DELAY   itof(45 + random(45))

string *colours = ({ "green", "yellow", "blue-green",
  "deep blue", "dark green" });
string *lines = ({ });

int false_drop;

void add_line(string l);
varargs void do_random_say(int not_again);

void
create_creature()
{
    string c;	

    if (!IS_CLONE)
	return;

    set_name("parrot");
    add_name("bird");
    add_name(PARROTNAME);
    add_name("animal");

    set_race_name("parrot");
    c = colours[random(sizeof(colours))];

    set_adj(explode(c," "));

    set_long("The parrot is " + c + ", with carefully preened feathers.\n");

    set_gender(2);
    set_appearance_offset(-25-random(20)); // It's a lovely parrot. :)

    default_config_mobile(4);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS,40);

    add_prop(LIVE_I_NEVERKNOWN,1);
    change_prop(OBJ_M_NO_GET,"@@take_parrot");
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_HEIGHT, 30);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL, 1);

    set_attack_unarmed(A_BEAK,5,10,W_SLASH,40,"sharp beak");
    set_attack_unarmed(A_CLAWS,10,7,W_SLASH,60,"claws");
    set_hitloc_unarmed(H_HEAD,7,20,"head");
    set_hitloc_unarmed(H_BODY,10,55,"body");
    set_hitloc_unarmed(H_WINGS,8,25,"wings");

//    trig_new("%s 'says:' %s", "hear_something");
//    trig_new("%s 'shouts:' %s", "hear_something");

#define BASIC_LINES 5
    add_line("Arr!");
    add_line("Where's me grog?");
    add_line("Ahoy, landlubbers!");
    add_line("Where did you hide the gold?");
    add_line("He's drunk again!");

//    set_alarm(DELAY,0.0,&do_random_say());

    catch(PARROT_ADMIN->register_parrot(TO));
}

void
attacked_by(object enemy)
{
    if ((enemy->id("weasel")) && (query_panic() < 1000))
	add_panic(1000);
    ::attacked_by(enemy);
}

mixed
take_parrot()
{
    if (objectp(TP) && interactive(TP) && present(PARROTNAME,TP))
    {
	return "Two parrots rarely get along, so you decide not to " +
	"take another.\n";
    }
    else
	return 0;
}

string *
query_lines()
{
    return lines;
}

void
add_line(string l)
{
    int p;	

    if ((p = member_array(l, lines))==-1)
    {
	lines += ({ l });
	if (sizeof(lines) > (MAXLINES + BASIC_LINES))
	    lines -= ({ lines[BASIC_LINES] });
    }
}

int
hear_something(string speaker, string spoken)
{
    int chance;
    chance = 50 - (strlen(spoken)/4);
    if (chance > 33)
	chance = 33;

    spoken = explode(spoken,"\n")[0];

    if (random(100) < chance)
    {
	add_line(spoken);
    }
    return 1;
}

void
do_say(string to_say)
{
    switch(random(3))
    {
    case 0:
	to_say = "Waark! " + to_say;
	break;
    case 1:
	to_say = to_say + " Waark!";
	break;
    case 2:
	to_say = "Waark! " + to_say + " Waark!";
    }

    if (E(TO) && E(TO)->query_prop(LIVE_I_IS))
    {
	tell_room(E(E(TO)),
	  "The parrot perched on " + QTNAME(E(TO)) + 
	  "'s shoulder squawks: " + to_say + "\n", E(TO));
	if (interactive(E(TO)))
	    E(TO)->catch_msg("The parrot perched on your shoulder " +
	      "squawks: " + to_say + "\n");
    }
    else
    {
	if (CAN_SEE_IN_ROOM(TO))
	    TO->command("say " + to_say);
    }
}

varargs void
do_random_say(int not_again)
{
    do_say(lines[random(sizeof(lines))]);

    if (!not_again){
	//set_alarm(DELAY,0.0,&do_random_say());
    }
}

int
is_parrot(object ob)
{
    if (ob->id(PARROTNAME))
	return 1;
    else
	return 0;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if(env->query_prop(LIVE_I_IS))
    {
	object *t;
	t = filter(deep_inventory(env),is_parrot) - ({ TO });

	if (sizeof(t))
	{
	    env->catch_msg("Two parrots rarely get along, so you put the " +
	      short() + " down on the ground.\n");
	    tell_room(E(env), QCTNAME(env) + " warily eyes " + HIS(env) +
	      " second parrot, and after a brief pause " + HE(env) +
	      " puts the " + short() + " down on the ground.\n", env);
	    set_alarm(0.0,0.0,&move(E(env)));
	    false_drop = 1;
	}
	else
	{
	    env->catch_msg("The " + short() + " climbs up on your " +
	      "shoulder.\n");
	    env->add_subloc(PARROTSUBLOC,TO);
	    set_alarm(1.0,0.0,&set_no_show_composite(1));
	}
    }

}

void leave_env(object from, object to)
{
    ::leave_env(from,to);
    if(!false_drop && from->query_prop(LIVE_I_IS))
    {
	from->remove_subloc(PARROTSUBLOC);
	set_no_show_composite(0);
	from->catch_msg("You convince the parrot to leave your shoulder.\n");
    }
    false_drop = 0;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != PARROTSUBLOC)
        return ::show_subloc(subloc, me, for_obj);
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You have a parrot perched on your shoulder.\n";

    if (for_obj == me)
	return "You have a " + short() + " perched upon your shoulder.\n";
    else
	return C(PRONOUN(me)) + " has a " + short() + " perched upon " +
	POSSESSIVE(me) + " shoulder.\n";
}

void
emote_hook(string emote,object actor,string adverb = 0)
{
    if((emote=="nudge") || (emote=="pet"))
    {
	//set_alarm(3.0,0.0,&do_random_say(1));
    }
}

void
do_die(object killer)
{
    killer->add_prop(NERAKA_I_KILLED_PARROT, time());
    ::do_die(killer);
}
