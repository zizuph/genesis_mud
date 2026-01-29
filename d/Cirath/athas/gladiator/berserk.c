/**********************************************************************
 * - berserk.c                                                      - *
 * - Special attack for gladiators.                                 - *
 * - Removed this out of the soul for easier debugging purposes.    - *
 * - Created by Damaris@Genesis 10/2004                             - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver"; 
inherit "/d/Cirath/lib/commands";
inherit "/d/Genesis/lib/multi_alarm";
inherit "/d/Genesis/specials/calculations";

#include "defs.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <macros.h>

void
allow_berserk(object ob)
{
    if (!objectp(ob)) return;
    tell_object(ob, "\nYou can now enter a berserked state again.\n\n");
    ob->remove_prop(GLAD_I_IS_BERSERK);
}

void
expire_berserk(object ob, int str, int con, int dis)
{
    int burnout, old_hp, old_maxhp, new_hp, new_maxhp;

    if (!objectp(ob)) return;
    old_maxhp = ob->query_max_hp();
    old_hp = ob->query_hp();
    ob->set_stat_extra(SS_CON,ob->query_stat_extra(SS_CON)-con);
    ob->set_stat_extra(SS_STR,ob->query_stat_extra(SS_STR)-str);
    ob->set_stat_extra(SS_DIS,ob->query_stat_extra(SS_DIS)-dis);
    new_maxhp = ob->query_max_hp();
    new_hp = new_maxhp * old_hp / old_maxhp;
    ob->heal_hp(new_hp - old_hp);

    burnout = ((ob->query_base_stat(SS_CON))/6);
    if (burnout > (ob->query_fatigue())) (ob->set_fatigue(1));

    else (ob->add_fatigue(-burnout));

    set_alarm(itof(MAX(10, 25 - ob->query_skill(SS_BERSERK) / 5)), 0.0,
      &allow_berserk(ob));
    tell_object(ob, "You begin to calm down and return to a normal frame "+
      "of mind.\n");
    say(QCTNAME(ob) + " seems to have returned to a normal frame of "+
      "mind.\n");
}
void
do_berserk(object ob)
{
    int str, dis, con, skill, time, old_hp, old_maxhp, new_hp,
    max, new_maxhp;

    if (!objectp(ob)) return;
    skill = ob->query_skill(SS_BERSERK);
    time = 25 + skill/4;  /* between 25 and 50 seconds */
    
    // 6% CAID to str, as per tax doc.
    str = convert_caid_to_stat(ob, 15 * skill / 100, SS_STR);
    
    // 15% CAID to dis, as per tax doc.
    dis = convert_caid_to_stat(ob, 15 * skill / 100, SS_DIS);

    // 15% CAID to con, as per tax doc.
    con = convert_caid_to_stat(ob, 20 * skill / 100, SS_CON);

    ob->set_stat_extra(SS_STR,str+ob->query_stat_extra(SS_STR));
    ob->set_stat_extra(SS_DIS,dis+ob->query_stat_extra(SS_DIS));

    old_maxhp = ob->query_max_hp();
    old_hp = ob->query_hp();
    ob->set_stat_extra(SS_CON,con+ob->query_stat_extra(SS_CON));
    new_maxhp = ob->query_max_hp();
    new_hp = new_maxhp * old_hp / old_maxhp;
    ob->heal_hp(new_hp - old_hp);

    set_alarm(itof(time), 0.0, &expire_berserk(ob, str, con, dis));
    ob->catch_tell("You start slavering at the mouth.\n");
    say(QCTNAME(ob) + " works "+ob->query_objective()+"self"+
      " into a wild battle rage.\n", ob);
}

int
berserk()
{
    object glad = TP;

    if(!(glad->query_skill(SS_BERSERK)))
    {
    NF("Berserk is a skill, not just something you do.\n");
    return 0;
    }

    if (CHECK_PUNISHMENT(glad, PUN_SPEC))
    {
    write("Kalak has cursed you with the inability to berserk!\n"+
      "You shall need to find another way to defeat your enemies.\n");
    return 1;
    }

    if (glad->query_prop(GLAD_I_IS_BERSERK) == 1)
    {
    write("You are foaming at the mouth as it is.\n");
    }
    else if (((glad->query_base_stat(SS_CON))/5) > (glad->query_fatigue()))
    {
    write("You are too exhausted to go berserk.\n");
    }
    else
    {
    glad->add_prop(GLAD_I_IS_BERSERK, 1);
    set_alarm(5.0, 0.0, &do_berserk(glad));
    glad->catch_tell("Your breathing becomes heavier.\n");
    say(QCTNAME(glad)+" breaks out in a sweat as "+HIS_HER(glad)+
      " breathing becomes heavier.\n", glad);
    }
    return 1;
}




