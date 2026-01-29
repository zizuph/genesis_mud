/*
 * pHarm
 */
 
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

public void
pharm_message(object caster, object enemy, mixed hr)
{
    string *how;
	
    DEBUG(sprintf("PHARM: hitresult =  %d proc_hurt, %d phit, %d dam\n",
        hr[0], hr[2], hr[3]));

    if (hr[0] <= 0)
        how = ({ "without harming " + HIM(enemy),
        	 "without harming you" });
    else if (hr[0] < 5)
        how = ({ "hurting " + HIM(enemy) + " slightly",
        	 "hurting you slightly" });
    else if (hr[0] < 12)
        how = ({ "hurting " + HIM(enemy),
        	 "hurting you" });
    else if (hr[0] < 26)
        how = ({ "hurting " + HIM(enemy) + " severely",
        	"hurting you severely" });
    else if (hr[0] < 55)
        how = ({ "leaving " + HIM(enemy) + " on the verge of collapse",
        	"leaving you on the verge of collapse" });
    else if (hr[0] < 100)
        how = ({ "almost killing " + HIM(enemy),
        	"almost killing you" });
    else
        how = ({ "taking all of " + HIS(enemy) + " life force",
        	"taking all of your life force" });

    caster->catch_msg("You reach out towards " +
    enemy->query_the_name(caster) + " with your hands, draining " +
    HIS(enemy) + " health, " + how[0] + ".\n");

    enemy->catch_msg(caster->query_The_name(enemy) + " reaches out towards " +
    "you with " + HIS(caster) + " hands, draining your health, " + how[1] +
    ".\n");

    generalbb(QCTNAME(caster) + " reaches out towards " + QTNAME(enemy) +
    ", draining " + HIS(enemy) + " health, " + how[0] + ".",
    all_inventory(E(caster)) - ({ caster, enemy }));
}

public int
pharm_damage(object caster, object target, int result)
{
    int t;

    t = 50 + result / 3 + caster->query_priest_level() * 15;
    t -= target->query_stat(SS_CON) / 4 + target->query_stat(SS_DIS) / 5;

    if (t > 200)
        t = 200;

    DEBUG("PHARM: result = " + result + ", PEN = " + t);

    return t;
}

public int
pharm_resist(object target)
{
    int i;
    i = target->query_magic_res(MAGIC_I_RES_MAGIC) +
        target->query_magic_res(MAGIC_I_RES_LIFE);
    return (i > 100 ? 100 : i);
}

public int
create_spell_pharm(string arg)
{
    string whom, what;
    object *tar;

    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);

    set_spell_time(2);
    set_spell_mana(55);

    set_spell_attack();
    set_damage_type(MAGIC_DT);

    set_spell_task(TASK_SIMPLE+150);
    set_spell_stationary(0);
    set_find_target(find_one_living_target);
    set_spell_message(pharm_message);
    set_spell_resist(pharm_resist);
    set_spell_damage(pharm_damage);
}

public int
do_pharm(string str)
{
    return cast_spell();
}


