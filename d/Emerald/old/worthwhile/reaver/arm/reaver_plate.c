inherit "/std/armour";
inherit "/d/Genesis/magic/resist";

#include "../defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <language.h>
#include <macros.h>
#include <formulas.h>


static int alarm_id;

void
create_armour()
{
    set_ac(40);
    set_at(A_TORSO | A_LEGS | A_ARMS);
    set_am(({ 0, 20, 0 }));

    set_name(({ "fullplate", "plate", "black_reaver_armour" }));
    set_short("black matte fullplate");
    set_adj(({ "black", "matte", "full" }));
    set_long("Coal black plate, with no metallic gleam at " +
        "all. Its matte surface seems to swallow the " +
        "light around it, helping its wearer blend into " +
        "the shadows. It looks to be made of velvet, yet it " +
        "is solid and deathly cold to the touch. \n");

    set_af(this_object());
    
    set_likely_break(1);
    set_likely_cond(1);
    
    add_prop(OBJ_M_NO_BUY, 1);
    
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(40) * 2);
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "It is a powerful magical item.\n", 10,
        "It is enchanted with death magic, and can be quite " +
        "dangerous to those unfamiliar with the mysteries " +
        "of the element.\n", 25,
        "It is strongly resistant to slashing attacks.\n", 45,
        "Those unable to resist its evil influence are drained " +
        "of health, and all but the most malevolent of wearers " +
        "will find their souls corrupted by it.\n", 60,
        "The armour will retaliate of its own will when the " +
        "wearer is attacked.\n", 65,
        "It also spreads a strange, magical disease.\n", 75,
        "Undead creatures are immune to the disease.  Those " +
        "unfortunate enough to catch the disease, though, can " +
        "suffer a painful death and possibly be transformed into " +
        "undead creatures.\n", 80 }));
    
    add_prop(MAGIC_AM_MAGIC, ({ 80, "death" }));
    add_prop(OBJ_S_WIZINFO, "The armour is enchanted with death magic. " +
      "It provides an extra 20 points of armour versus slashing " +
      "attacks.  In addition, it has a 1 in 15 chance of returning " +
      "damage when it is hit by an attack (hit_me() with a pen equal " +
      "to the damage done).  The armour lowers the alignenment of " +
      "the wearer, but no lower than -600.  Those who wear ther armour " +
      "risk contracting a disease (there is a small chance of getting " +
      "the disease by making a successful unarmed attack on the armour). " +
      "Also, those unable to resist a TASK_ROUTINE level spell " +
      "resistance check for death magic will be drained of health as " +
      "long as the armour is worn.\n");
}

static void
decay_align()
{
    float delay;
    int align, decay;

    if (!query_worn || !query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        if (alarm_id)
        {
            remove_alarm(alarm_id);
            alarm_id = 0;
        }

        return;
    }

    if (!alarm_id)
    {
        delay = itof(15 * 60 + random(10 * 60));
        alarm_id = set_alarm(delay, delay, decay_align);
        return;
    }

    if ((align = wearer->query_alignment()) < -600)
    {
        return;
    }

    decay = (1800 - (1200 - align)) / 200;
    decay *= decay;
    decay = max(decay, 1);

    wearer->set_alignment(align - decay);
}

public void
infect(object who)
{
#ifdef DISEASE_ACTIVE
    object disease;

    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return;
    }

    setuid();
    seteuid(getuid());
    disease = clone_object(MONASTERY_DIR + "obj/reaver_disease");
    if (!disease->infect(who, this_object()))
    {
        disease->remove_object();
    }
#endif
}

public void
drain()
{
    int dam;

    if (!query_worn() || !query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        alarm_id = 0;
        return;
    }

    dam = 200 * (100 - spell_resist(this_object(), wearer,
        SS_ELEMENT_DEATH, TASK_DIFFICULT)) / 100;

    if (dam)
    {
        wearer->catch_tell("Suddenly, you feel a strong pain...as if your " +
          "life energy were being drained away!\n");
        wearer->heal_hp(-dam);
    }

    alarm_id = set_alarm(rnd() * 10.0 + 2.0, 0.0, drain);
}

mixed
wear(object arm)
{
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return 0;
    }

    decay_align();
    infect(wearer);

    if (!wearer->query_prop(LIVE_I_UNDEAD) &&
      (random(100) >= spell_resist(this_object(), wearer, SS_ELEMENT_DEATH,
          TASK_ROUTINE)))
    {
        alarm_id = set_alarm(0.0, 0.0, drain);
    }

    return 0;
}

mixed
remove(object arm)
{
    if (alarm_id)
    {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }

    return 0;
}

public void
return_damage(object attacker, int dt, int dam)
{
    wearer->catch_tell("As " + LANG_POSS(attacker->query_the_name(wearer)) +
      "attack strikes you, a bolt of energy lances out from the point " +
      "the attack struck the " + short(wearer) + ", jolting " +
      attacker->query_the_name(wearer) + ".\n");

    attacker->catch_tell("As your attack strikes " + 
      wearer->query_the_name(attacker) + ", a bolt of energy lances out " +
      "from the point of contact with " + wearer->query_possessive() +
      short(attacker) + ", jolting you.\n");

    wearer->tell_watcher("As the attack strikes " + QTNAME(wearer) + 
      ", a bolt of energy lances out from the point of contact with " +
      wearer->query_possessive() + " " + QSHORT(this_object()) +
      ", jolting " + QTNAME(attacker) + ".\n", attacker);

    attacker->hit_me(dam, dt, wearer, -1);

    if (attacker->query_hp() <= 0)
    {
        attacker->do_die(wearer);
    }
}

public varargs int
got_hit(int hid, int phurt, object attacker, int aid, int dt, int dam)
{
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return ::got_hit(hid, phurt, attacker, aid, dt, dam);
    }

    if (!random(15) && (dam > 0))
    {
        set_alarm(0.0, 0.0, return_damage(attacker, dt, dam));
    }

    if ((phurt >= 0) && !random(100))
    {
        infect(attacker);
    }

    return ::got_hit(hid, phurt, attacker, aid, dt, dam);
}

public int
disenchant_object(object disenchanter)
{
    remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
    remove_prop(MAGIC_AM_MAGIC);
    remove_prop(OBJ_M_NO_BUY);

    add_prop(MAGIC_AM_ID_INFO,
      ({ "The armour once possessed powerful magic, " +
        "but it has been disenchanted.\n", 30 }));

    update_prop_settings();

    set_likely_break(4);
    set_likely_cond(4);

    set_am(({ 0, 0, 0 }));

    if (query_worn())
    {
        wearer->update_armour(this_object());
    }

    return 1;
}
