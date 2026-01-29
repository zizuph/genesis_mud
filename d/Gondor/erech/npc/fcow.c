/* This is /d/Gondor/common/npc/wrabbit.c
 * A white rabbit
 * Dunstable, Septembet 1993
 */
inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

/*
 * Define some attack and hitloc id's
 */
#define A_HORNS 0
#define A_LFOOT 1
#define A_RFOOT 2

#define H_HEAD 0
#define H_BODY 1
#define H_PRIV 2

/* Prototypes */
int   milk(string arg);
void  wave_tail();

void
create_creature()
{
    set_name("cow");
    set_short("large spotted cow");
    set_long("A spotted cow ready to be milked. \n");

    add_adj("spotted");
    add_adj("large");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(9);
    add_act("emote moos.");
    add_act(&wave_tail());
    add_act(&wave_tail());
    add_act(&wave_tail());
    add_act("emote chews on something.");
    add_act("emote chews on something.");
    add_act("emote chews on something.");
    add_act("emote chews on something.");

    set_skill(SS_DEFENCE, 5);
    set_skill(SS_UNARM_COMBAT, 5);

    set_attack_unarmed(A_HORNS, 15, 15, W_IMPALE, 90, "horns");
    set_attack_unarmed(A_LFOOT, 5, 5, W_BLUDGEON, 5, "left foot");
    set_attack_unarmed(A_RFOOT, 5, 5, W_BLUDGEON, 5, "right foot");

    set_hitloc_unarmed(H_HEAD, ({30, 10, 15}), 30, "head");
    set_hitloc_unarmed(H_BODY, ({5, 5, 5}), 65, "body");
    set_hitloc_unarmed(H_PRIV, ({1, 1, 50}), 5, "udders");
}

void
init_living()
{
    ::init_living();
    add_action(milk, "milk");
}

int
milk(string arg)
{
    object milker, bucket;

    milker = this_player();
    bucket = present("Erech_farm_bucket", milker);

    if (arg == "cow")
    {
        if (!bucket)
	{
	    write("You need a bucket to milk the cow.\n");
	    return 1;
	}
        if (milker->query_skill(SS_ANI_HANDL) < 15)
	{
	    write("You don't feal that you are not able to handle this cow " +
		  "yet.\n");
	    return 1;
	}
        if (bucket->query_filled() == 0)
	{
            write("You manages to get some milk from the cows udders " +
                  "and into the bucket.\n");
            say(QCTNAME(milker) + " swears and courses as " +
                milker->query_pronoun() + " fumbles with the cow's udders.\n");
            bucket->set_filled("milk");
            return 1;
	}
	if (bucket->query_content() != "milk")
	{
	    write("There are allready some " + bucket->query_content() + 
		  " in the bucket.\n");
	    return 1;
	}
	if (bucket->query_content() == "milk" && bucket->query_filled() < 3)
	{
	    write("You manages to get some milk from the cows udders " +
		  "and into the bucket.\n");
	    say(QCTNAME(milker) + " swears and courses as " + 
		milker->query_pronoun() + " fumbles with the cow's udders.\n");
	    bucket->set_filled("milk");
	    return 1;
	}
	else if (bucket->query_filled() == 3)
	{
	    write("The bucket is full of " + bucket->query_content() + ".\n");
	    return 1;
	}
	write("Might be an error, please report this by mailing Skippern.\n");
	return 1;
    }
    return 0;
}

void
wave_tail()
{
    object *apresent, victim;
    int    i, n;

    apresent = all_inventory(environment(this_object()));
    apresent = FILTER_PRESENT_LIVE(apresent);

    n = sizeof(apresent);
    i = random(n);

    switch (random(10))
      {
      case 0:
	victim = apresent[i];
	if (victim == this_object())
	  return;
	victim->catch_tell("The large spotted cow waves her tail in your " +
	    "face.\n");
	say("The large spotted cow waves her tail in " +
	    QTPNAME(victim) + " face.\n", ({ victim, this_object() }) );
	break;
      default:
	command("emote waves her tail.");
	break;
      }
    return;
}
