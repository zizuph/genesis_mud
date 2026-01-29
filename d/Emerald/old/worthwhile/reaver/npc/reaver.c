inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/magic/resist";

#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <options.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>

public int gaze_attack(object enemy);
public int poison_attack(object enemy);

/* Ideas on this guy...he's going to have an axe of silver, which */
/* will show the reflection of the wielder, but as a withering */

/*corpse. The axe will be two handed, with a long shaft. He will */
/*also have matte black armour - breastplate, greaves, bracers - */
/* and perhaps heavy leather gloves and boots, that will be */
/* resistant to blades, and can only be damaged by blunt weapons. */
/*I'll have to figure a way to tone down this capacity when it's */
/*worn by a PC. If he is disarmed, he will be able to use his */
/*claws, which will be poisonous. I'm also planning on giving him */
/*some kind of CON drain, which will be done in some way through */
/*his eyes. */
public void
create_emerald_monster()
{
    set_name("reaver");
    set_living_name("black_reaver");
    set_race_name("reaver");
    set_adj("black");

    set_long("A black reaver, undead humanoid of " +
    	"overbearing stature, shrouded in impenetrable darkness. It " +
    	"stands three meters tall, with an armspan that dwarfs any " +
    	"long limbed troll's. It boasts no discernible features, save " +
    	"its eyes - depthless twin pools of magma sparked by " +
    	"intelligence, that seem to drain the essense of its " +
    	"challengers' souls.\n");

    set_stats(({ 250, 300, 250, 250, 225, 300 }));

    set_all_hitloc_unarmed(100);
    set_all_attack_unarmed(100, 100);

    set_gender(G_NEUTER);
    set_alignment(-1200);

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 90);
    set_skill(SS_PARRY, 95);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_ABJURATION, 80);
    set_skill(SS_ELEMENT_EARTH, 80);
    set_skill(SS_ELEMENT_AIR, 80);
    set_skill(SS_ELEMENT_WATER, 80);

    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't accept gifts from mortals.\n");
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(NPC_I_NO_LOOKS, 1);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_FIRE, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_EARTH, 65);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_DEATH, 95);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ELECTRICITY, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_WATER, 20);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ILLUSION, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 100);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ACID, 70);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_MAGIC, 50);

    set_act_time(12);
    add_act("emote watches you closely.");
    add_act("emote tests the edge of its weapon, never " +
        "letting its eyes leave you.");

    add_equipment(({
        MONASTERY_DIR + "wep/reaver_" + (random(2) ? "axe" : "scythe"),
        MONASTERY_DIR + "arm/reaver_plate", }));


    log_my_deaths(MONASTERY_DIR + "log/reaver_deaths.log");
    log_my_kills(MONASTERY_DIR + "log/reaver_kills.log");

    set_special_attack_percent(3);
    add_special_attack(gaze_attack, 50, "gaze");
    add_special_attack(poison_attack, 50, "poison");

    set_exp_factor(130);

/*A few changes to the above ideas, and some additions. Instead */
    /*of an axe, let's give him a scythe, or let it randomly choose */
    /*either weapon, as Shiva suggested. Just to make him a bit */
    /*more challenging, let's give him a hook that lets */
    /*him recover and rewield his weapon if he's disarmed. When */
    /*the player finally figures out how to write a trigger to */
    /*grab the weapon, _then_ he can use his claws. The two */
    /*responses - */
    /*Recovery - "emote emits a soft chuckle, apparently amused */
    /*by your antics."*/
    /*No recovery - "As the reaver is disarmed, it seems to sneer, */
    /*and clicks its long curved nails together." */
    /*We're also going to take away any possibility of his wearing */
    /*gloves or cloak - the gloved would get in the way of the */
    /*claws, and the cloak might inhibit his dexterity. */
}

public int
gaze_attack(object enemy)
{
    int amnt, res;

    enemy->catch_tell("The black reaver gazes at you intensely--its red eyes " +
        "corruscating with demonic power--and your chest tightens as you feel " +
        "its wicked stare draining the life from you.\n");
    tell_watcher(QCTNAME(this_object()) + " gazes at " + QTNAME(enemy) +
        "intensely--its red eyes corruscating with demonic power.\n", enemy);

    res = spell_resist(this_object(), enemy, SS_ELEMENT_DEATH, TASK_DIFFICULT);

    enemy->add_tmp_stat(SS_CON, -random(15) * res / 100, 20);

    amnt = -random(200) * res / 100;
    enemy->heal_hp(amnt);
    heal_hp(-amnt);

    amnt = -random(50) * res / 100;
    enemy->add_mana(amnt);
    add_mana(-amnt);

    amnt = -random(30) * res / 100;
    enemy->add_fatigue(amnt);
    add_fatigue(-amnt);

    amnt = random(20) * res / 100;
    enemy->add_panic(amnt);
    add_panic(-amnt);

    return 1;
}
 
public int
poison_attack(object enemy)
{
    object poison;

    if (query_weapon(-1) && (random(20)))
    {
        return 0;
    }

    if (query_combat_object()->cb_tohit(W_RIGHT, 90, enemy))
    {
        enemy->catch_tell("The black reaver swipes at you with its jagged " +
            "claws, leaving a series of deep gashes in your body.\n");
        tell_watcher(QCTNAME(this_object()) + " swipes at " + QTNAME(enemy) +
            "with its jagged claws, leaving a series of deep gashes in " +
            enemy->query_possessive() + " body.\n", enemy);

        enemy->hit_me(300, W_SLASH, this_object(), W_RIGHT);

        if (enemy->query_hp() <= 0)
	{
            enemy->do_die(this_object());
            return 1;
	}

        if (random(4))
	{
            return 1;
	}

        setuid();
        seteuid(getuid());

        poison = clone_object(MONASTERY_DIR + "obj/reaver_poison");
        poison->move(enemy, 1);
        poison->start_poison();

        return 1;
    }

    enemy->catch_tell("The black reaver swipes at your with its jagged " +
        "claws, but misses completely.\n");
    tell_watcher(QCTNAME(this_object()) + " swipes at " + QTNAME(enemy) +
         "with its jagged claws, but misses " + enemy->query_objective() +
         "completely.\n", enemy);

    return 1;
}

public void
weaken_me()
{
    set_stats(({ 160, 200, 160, 160, 160, 200 }));

    set_all_hitloc_unarmed(50);
    set_all_attack_unarmed(40, 40);
}

int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}

mixed *
hit_me(int wcpen, int dt, object attacker, int attack_id, int hitloc = -1)
{
    object wep;


    if (attack_id == -1)
    {
        /* Nonstandard attack...do normal damage */
        return ::hit_me(wcpen, dt, attacker, attack_id, hitloc);
    }

    if (wep = attacker->query_weapon(attack_id))
    {
        if (wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	{
	    /* Attacks with magical weapons do full damage */
            return ::hit_me(wcpen, dt, attacker, attack_id, hitloc);
	}

        /* Attacks with non-magical weapons do no damage */
        return ::hit_me(0, dt, attacker, attack_id, hitloc);
    }

    /* Unarmed attacks do half damage */
    return ::hit_me(wcpen / 2, dt, attacker, attack_id, hitloc);
}

/* Don't even bother calculating fatigue healing:  it is always
 * at max.
 */
void
calculate_fatigue()
{
    set_fatigue(query_max_fatigue());
}
