/*
 * File Name        : monkey.c
 * By               : Elmore.
 * Inspiration from : A parrot by Ashlar.
 * Date             : Nov. 2000.
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/lib/keep";
inherit "/std/act/action";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include <files.h>

#define PARROTSUBLOC    "_ansalon_monkey_subloc"
#define PARROTNAME      "_ansalon_monkey"

#define A_BEAK 0
#define A_CLAWS 1
#define H_HEAD 0
#define H_BODY 1
#define H_WINGS 2
#define MAXLINES    100
#define DELAY   itof(45 + random(45))

string *colours = ({ "brown", "black", "grey",
  "tiny", "tiny" });
string *lines = ({ });

int false_drop;

void
create_creature()
{
    string c;	

    if (!IS_CLONE)
	return;

    set_name("monkey");
    add_name(PARROTNAME);
    add_name("animal");

    set_race_name("monkey");
    c = colours[random(sizeof(colours))];

    set_adj(explode(c," "));

    set_long("The monkey is " + c + ", with a tiny hat on it's head.\n");

    set_gender(2);
    set_appearance_offset(-25-random(20));

    default_config_mobile(4);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS,40);

    add_prop(LIVE_I_NEVERKNOWN,1);
    change_prop(OBJ_M_NO_GET,"@@take_monkey");
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_HEIGHT, 30);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL, 1);

    set_attack_unarmed(A_BEAK,5,10,W_SLASH,40,"sharp teeth");
    set_attack_unarmed(A_CLAWS,10,7,W_SLASH,60,"claws");
    set_hitloc_unarmed(H_HEAD,7,20,"head");
    set_hitloc_unarmed(H_BODY,10,55,"body");
    set_hitloc_unarmed(H_WINGS,8,25,"arms");

    catch(PARROT_ADMIN->register_parrot(TO));

    set_act_time(6);
    add_act("emote restlessly shifts back and forth, looking at you suspiciously.");
    add_act("emote suddenly jumps up and turn around nervously.");
    add_act("emote scratches it's back and find a small flea, which it eats.");
    add_act("emote fiddles with its tiny hat.");
    add_act("emote starts to doze off, and just as it is about to fall off, it "+
            "opens its eyes frightenly and graps hold on the shoulders of his "+
            "owner.");
    add_act("emote looks to all sides, obviously bored, it lets out a small sigh.");
    add_act("emote gets a greedy look in its eye, as it looks at your equipment.");
    add_act("emote jumps up and down eagerly, while pointing to the east.");
    add_act("emote looks eagerly at the ground, probably searching for any valuables to steal.");
    add_act("emote starts to pick his nose, while staring up at the sky.");
}

void
attacked_by(object enemy)
{
    if ((enemy->id("wolf")) && (query_panic() < 1000))
	add_panic(1000);
    ::attacked_by(enemy);
}

mixed
take_parrot()
{
    if (objectp(TP) && interactive(TP) && present(PARROTNAME,TP))
    {
	return "Two of those rarely get along, so you decide not to " +
	"take another.\n";
    }
    else
	return 0;
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
	    env->catch_msg("Two of those rarely get along, so you put the " +
	      short() + " down on the ground.\n");
	    tell_room(E(env), QCTNAME(env) + " warily eyes " + HIS(env) +
	      " second monkey, and after a brief pause " + HE(env) +
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
	from->catch_msg("You convince the monkey to leave your shoulder.\n");
    }
    false_drop = 0;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != PARROTSUBLOC)
        return ::show_subloc(subloc, me, for_obj);
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You have a tiny monkey perched upon your shoulder.\n";

    if (for_obj == me)
	return "You have a " + short() + " perched upon your shoulder.\n";
    else
	return C(PRONOUN(me)) + " has a " + short() + " perched upon " +
	POSSESSIVE(me) + " shoulder.\n";
}
