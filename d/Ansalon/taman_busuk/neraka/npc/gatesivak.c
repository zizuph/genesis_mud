#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define KSIVAK  NNPC + "sivak"

inherit KSIVAK;

int
check_for_attack()
{
    return ATTACKERS_ADMIN->query_auto_attack(TO,TP);
}

void
create_sivak()
{
    ::create_sivak();

    set_aggressive("@@check_for_attack@@");
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    ATTACKERS_ADMIN->add_reputation(attacker,CRIME_ATTACK);
    if (E(TO))
        E(TO)->sound_alarm();
    TO->command("shout Attack! Enemies at the gate!");
}

void
do_die(object killer)
{
    ATTACKERS_ADMIN->add_reputation(killer,CRIME_MURDER);
    ::do_die(killer);
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
void
attack_object(object ob)
{
    object *arr;
    int i;

    ::attack_object(ob);

    if (E(TO))
        E(TO)->sound_alarm();

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);    
}

/*
 * Function name: aggressive_attack
 * Description:   We are aggressive, let us attack
 * Arguments:         ob - the object to attack
 */
public void
aggressive_attack(object ob)
{
    if (!objectp(ob) || !present(ob, environment(this_object())))
        return;

    command("say You're as good as dead, " + ob->query_race_name() + "!");
    command("kill " + ob->query_real_name());
}

/*
 * Function name: help_friend
 * Description:   Help a teammate in trouble by attacking someone
 * Arguments:     ob - the object to attack
 */
public void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("shout For Takhisis!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
