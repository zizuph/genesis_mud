inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_weapon()
{
    set_name("knife");
    set_adj(({ "dark-laen", "laen", "dark" }));
    set_short("dark-laen knife");

    set_long("A simple knife in every fashion except for the " +
        "blade, which is forged from a dark, smokey, glass-like " +
        "substance.\n");

    add_item("blade", "It is fashioned from a dark, smokey, glass-like " +
        "substance which you recognize as the rare dark-laen.\n");
  
    set_wt(W_KNIFE);
    set_hit(45);
    set_pen(35);
    set_dt(W_IMPALE | W_SLASH);
    set_likely_break(1);
    set_hands(W_LEFT);

    set_keep(1);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 20 }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "You sense that the weapon was enchanted with a very " +
        "specific purpose, namely to be used in acts of thievery.\n", 15,
        "It has the potential to deliver powerful strikes to " +
        "unsuspecting opponents.\n", 45,
        "This is only possible when the attacker is unseen by the " +
        "target, however.\n" }));
    add_prop(OBJ_S_WIZINFO, "This knife does extra MAGIC_DT " +
        "damage when used against an opponent who is unable to see " +
        "the attacker.\n");

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE,  2 * 12 * 12 * 12);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 500);
}

public void
give_msg(string hdesc, object attacker, object enemy, int dam)
{
    if (dam < 175)
    {
	attacker->catch_tell("You follow through with your attack, " +
	    "driving the " + short(attacker) + " deeper into " + 
	    LANG_POSS(enemy->query_the_name(attacker)) +
	    " " + hdesc + ".\n");
    }
    else
    {
	attacker->catch_tell("You follow through with your attack, " +
  	   "driving the " + short(attacker) + " deeper into " +
	    LANG_POSS(enemy->query_the_name(attacker)) +
	    " " + hdesc + ", viciously twisting the blade.\n");
    }

    if (interactive(enemy))
    {
        enemy->catch_tell("You nearly cry out in pain as " +
            attacker->query_the_name(enemy) + " drives the weapon " +
            "deeper into your " + hdesc + ".\n");
    }
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
		int dt, int phit, int dam)
{
    mixed *hr;
    object attacker = query_wielded();
	
    if ((phurt < 0) || (CAN_SEE_IN_ROOM(enemy) && 
        CAN_SEE(enemy, attacker) || random(10)))
    {
	return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    hr = enemy->hit_me(350 + attacker->query_skill(SS_BACKSTAB),
        MAGIC_DT, attacker, aid);
    set_alarm(0.0, 0.0, &give_msg(hdesc, query_wielded(),
        enemy, hr[3]));

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
