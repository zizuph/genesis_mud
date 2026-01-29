/* created by Aridor, 09/14/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>
#include <macros.h>

object my_guard;

void
equip_me()
{
    seteuid(getuid(TO));
/*    clone_object(OBJ + "dress")->move(TO);
    clone_object(OBJ + "sandals")->move(TO);
    my_guard = clone_object(LIV + "bodygepuard");
    my_guard->move(E(TO));
    my_guard->set_follow(TO);
    command("wear all");
    MONEY_MAKE_GC(random(5))->move(TO);*/
}

void
create_citizen()
{
    set_name("malynda");
    add_name("malynda_branchala");
    add_name("lady");
    set_race_name("human");
    set_introduce(", Lady of the noble House of Branchala");
    set_gender(1);
    set_adj("proud");
    add_adj("noble");
    set_long("@@my_long@@She is very elegantly dressed and appears to be " +
	     "of noble family.@@body_guard@@\n");
    default_config_npc(random(10) + 20);
    add_prop("_live_m_attack_thief","alarm_body_guard");
    set_random_move(40);
    set_restrain_path(TDIR);
    set_act_time(50);
    add_act("smile coquetishly");
}

void
alarm_body_guard(object thief, object victim, object what)
{
    if (!my_guard)
      return;
    my_guard->attack_object(thief);
    thief->attack_object(my_guard);
}

string
body_guard()
{
    if (!my_guard)
        return "";
    return " She has a body guard with her for protection.";
}

void
attacked_by(object ob)
{
    if (my_guard)
        set_alarm(1.0,0.0,"bodyguard_rescues",ob);
    else
        ::attacked_by(ob);
}

void
bodyguard_rescues(object who)
{
    if (E(my_guard) != E(who))
        return;
    tell_room(E(TO),"Valiantly, " + QTNAME(my_guard) +
        " jumps in to rescue " + QTNAME(TO) + ".\n");
    my_guard->attack_object(who);
    who->attack_object(my_guard);
    who->stop_fight(TO);
    TO->stop_fight(who);
}
