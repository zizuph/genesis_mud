inherit "/d/Emerald/ctower/npc/elemental";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

void
create_elemental()
{
    set_element("earth");
    set_opposing_element("air");

    set_long("A truly massive pile of rocks and dirt, formed into " +
        "a vaguely humanoid form.\n");

    set_skill(SS_ELEMENT_EARTH, 100);

    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_EARTH, 100);

    set_strong_stats(({ 220, 100, 220, 100, 100, 300 }));
    set_weak_stats(({ 110, 50, 120, 100, 100, 120 }));

    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(60);
}

int
breakable_armour(object arm)
{
    if (arm->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return 0;
    }

    return (random(100) < (arm->query_likely_break() * 20));
}

void
engulf_hit(object enemy)
{
    object *armours;
    int i;

    enemy->catch_tell(query_The_name(enemy) + " grabs you and " +
        "squeezes your body with a crushing grasp.\n");

    tell_watcher(QCTNAME(this_object()) + " grabs " + QTNAME(enemy) +
        " and squeezes " + enemy->query_possessive() + " body " +
        "with a crushing grasp.\n", enemy);

    if (!sizeof(armours = filter(enemy->query_armour(-1), breakable_armour)))
    {
        return;
    }
     
    armours[random(sizeof(armours))]->remove_broken();

    enemy->hit_me(400, W_BLUDGEON, this_object(), -1, A_BODY);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
}

int
invoke_air()
{
    weaken_elemental();
    return 1;
}

int
invoke_earth()
{
    strengthen_elemental();
    return 1;
}
