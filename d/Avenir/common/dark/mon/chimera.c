/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith Nov 2021: Updated after white-hits boost, hit/pen was too high. Modified
 *                    some actions and loot.
 * Lilith Feb 2022: Removed magic res since the combat system now autocalcs
 *                    it based on AC.
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include "/d/Avenir/smis/sys/statserv.h"
#include <tasks.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <poison_types.h>
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4
#define A_SBITE 5

#define H_HEAD 0
#define H_BODY 1

#define TP this_player()
#define TO this_object()
#define EN environment


public void
create_creature(void)
{
    setuid();
    seteuid(getuid());

    set_race_name("chimera");
    set_short("sleeping winged chimera");
    set_adj(({"sleeping", "winged", "restless"}));
    set_long("A hideous and terrifying creature, born of the deepest " +
      "part of the utterdark. Its body is that of a great lion, dark and "+
      "golden. It has three heads--one being a lion with fiery eyes, "+
      "the second being serpentine, and the third, that of a black-eyed "+
      "goat. Bat-like wings adorn its back.\n");

    default_config_creature(170);
    set_skill(SS_ACROBAT,      100); 
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_alignment(0);
    set_gender(G_NEUTER);

    set_act_time(13);
    add_act("emote rustles its wings.");
    add_act("emote twitches a muscle, sending a ripple across its skin.");


    set_cact_time(2);
    add_cact("@@flames");
    add_cact("@@hypn");
    add_cact("@@heal");
    add_cact("emote bangs you up against the tunnel wall.");
    add_cact("emote flails its barbed tail toward you.");
    add_cact("emote looks at you intently with its black goat eyes.");
    add_act("@@growls");
    add_act("@@hiss");
    add_act("@@flap");

    set_attack_unarmed(A_BITE,  30, 40, W_IMPALE,   20, "lion's jaws");
    set_attack_unarmed(A_LCLAW, 70, 30, W_SLASH,    30, "left claw");
    set_attack_unarmed(A_RCLAW, 70, 30, W_SLASH,    30, "right claw");
    set_attack_unarmed(A_TAIL,  10, 75, W_BLUDGEON, 30, "barbed tail");
    set_attack_unarmed(A_HORN,  40, 50, W_IMPALE,   20, "goat's horns");
    set_attack_unarmed(A_SBITE, 10, 60, W_IMPALE,   20, "serpent's fangs");

    set_hitloc_unarmed(H_HEAD, ({ 85 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 75 }), 80, "body");
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    add_leftover("/d/Avenir/inherit/leftover", "skull",3, "", 1,1);
    add_leftover("/d/Avenir/inherit/leftover", "bat wing",2, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "barbed tail",1, "", 1,1);
    add_leftover("/d/Avenir/inherit/leftover", "goat eye",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "lion tongue", 1,"",0,0);
    clone_object("/d/Genesis/gems/obj/agate_fire")->move(TO);

}

private void
poisoned(object who)
{
    if (living(who) && (who->query_stat(SS_DEX) < random(150)))
    {
	who->catch_msg("You fail to escape the cloud of poison!\n");

	object ob = clone_object("/std/poison_effect");
	ob->move(who);
	ob->start_poison();
    }
}

public string
hiss(void)
{
    tell_room(environment(this_object()),
      "The chimera's serpent head hisses violently.\n");
    return "";
}

public string
growls(void)
{
    tell_room(environment(this_object()),
      "The chimera's lion head growls loudly.\n");
    return "";
}

public string
flap(void)
{
    tell_room(environment(this_object()),
      "The chimera flaps its wings wildly.\n");
    return "";
}

public string
flames(void)
{
    tell_room(environment(this_object()),
      "The chimera's serpent head spews forth a cloud of poison.\n");
    map(all_inventory(EN(TO)), poisoned);
    return "";
}

public string
heal(void)
{
    this_object()->heal_hp(300);
    tell_room(environment(this_object()),
      "The chimera's serpent head hisses arcane words.\n" +
      "The chimera is surrounded by a purple glow.\n");
}

public string
hypn(void)
{
    object target = TO->query_attack();
    int res = resolve_task(TASK_ROUTINE, 0,
      target, ({ TS_DIS, TS_WIS }));

    target->catch_tell("The chimera's lion head looks at you.\n");

    if (res)
    {
	tell_room(environment(this_object()),
	  "The chimera's eyes glare at you!\n");
	tell_room(environment(this_object()),
	  "The chimera's goat head laughs hideously while the lion's eyes bewitch you.\n");

	target->command("$drop weapon");
    }

    return "";
}

public int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
  int phit, int dam, int hid)
{
    if (aid == A_SBITE)
    {
	tell_object(enemy,
	  "The chimera's serpentine fangs inject you with deadly venom!\n");

	object poison = clone_object("/std/poison_effect");

	if (poison)
	{
	    poison->set_strength(25);
	    poison->set_poison_type(POISON_HP);
	    poison->set_damage(({ POISON_HP, 50, POISON_STAT, SS_CON }));

	    poison->move(enemy);
	    poison->start_poison();
	}
    }
    return 0;
}

public int
special_attack(object enemy)
{
    if (random(3))
	return 0;

    mixed *hitresult = do_stat_based_attack(TO, enemy, MAGIC_DT);

    // The attack was evaded
    if (intp(hitresult))
	return 1;

    string how = " misses";

    if (hitresult[0] > 0)
	how = " singes";
    if (hitresult[0] > 25)
	how = " burns";
    if (hitresult[0] > 40)
	how = " engulfs";

    enemy->catch_msg(QCTNAME(TO) + how +
      " you with a fiery burst from its lion's mouth.\n");
    tell_watcher(QCTNAME(TO) +
      " breathes fire from its lion's mouth and" +
      how + " " + QTNAME(enemy) + ".\n", enemy);

    if (enemy->query_hp() <= 0)
	enemy->do_die(TO);

    return 1;
}


/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
    int s, t;

    ::attacked_by(ob);


    set_short("restless winged chimera");

}



void
do_die(object killer)
{
    object treasure;

    if (query_hp() > 0)
	return;
    // one gem type for each "head"
    treasure = clone_object("/d/Genesis/gems/obj/opal_fire");
    treasure->set_heap_size(3);
    treasure->move(TO);
    treasure = clone_object("/d/Genesis/gems/obj/pearl_black");
    treasure->set_heap_size(3);
    treasure->move(TO);
    treasure = clone_object("/d/Genesis/gems/obj/ruby");	
    treasure->set_heap_size(3);
    treasure->move(TO);
    STATSERV_LOG_EVENT("Utterdark", "Chimera killed");

    ::do_die(killer);

}
