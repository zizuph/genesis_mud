/*
 * 2021-01-03 - Cotillion
 * - Added clone_unique to gold platemail
 */
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/npc/basic_karg";
inherit "/lib/unique";

#define BASE_PATH ("/d/Earthsea/gont/tenalders/")

#include <macros.h>
#include <language.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

private int last_attack = time(), preparing = 0;

public int 
query_disallow_mercy(object ob)
{
   if(ob->query_merciful())
   {
      write_file("/d/Earthsea/log/npc_logs/kargcapt_mercy",
          this_player()->query_name() + " " + ctime(time()) + "\n");
      return 1;
   }

   return 0;
}

public void
create_karg()
{
    object to = this_object();
    set_living_name("_mr_karg_6_");
    set_levels(6);
    set_random_move(10);
    set_short(query_short() + " " + "captain");
    add_name("captain");
    set_skill(SS_WEP_POLEARM, 100);
    set_stats(({180, 190, 175, 100, 100, 145 }));
    set_title("captain");
    set_act_time(45);
    add_act("swing halberd");
    add_act("laugh all");
    add_act("cackle");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop("_ranger_m_no_disarm_drop", 1);
    equip(({
        "/d/Earthsea/gont/tenalders/arm/spike_boots",
        "/d/Earthsea/gont/tenalders/arm/arm_bands",
        clone_unique(BASE_PATH + "arm/gold_plate", 20, BASE_PATH + "arm/bronze_plate"),
        "/d/Earthsea/gont/tenalders/arm/sash",
        "/d/Earthsea/gont/tenalders/arm/dragon_helm" }));
    (MONEY_MAKE_PC(random(4)))->move(to, 1);
    clone_unique("/d/Earthsea/gont/tenalders/wep/unholy_halberd", 2,
        "/d/Earthsea/gont/tenalders/wep/lance")->move(to, 1);
    command("wield all");
    set_vip_importance(5);
}

public int
special_attack(object victim)
{
    object polearm, to = this_object();
    int pen;
    mixed hitres;
    string adjective, how, toposs = to->query_possessive();

    if(time() < last_attack + 20)
        return 0;

    if(!preparing)
    {
        preparing = 1;
        return 0;
    } else {
        preparing = 0;
    }

    // Make sure we are wielding everything
    command("wield all");
    polearm = query_weapon(W_BOTH);

    if(!objectp(polearm) || polearm->query_wt() != W_POLEARM)
        return 0;

    last_attack = time();

    if(query_combat_object()->cb_tohit(-1, 100, victim) != 1)
    {
        pen = -1;
    } else {
        pen = (polearm->query_pen() + query_stat(SS_STR)) / 2; 
        pen = F_PENMOD(pen, query_skill(SS_WEP_POLEARM));
    }

    hitres = victim->hit_me(pen, W_SLASH, to, -1);

    if(victim->query_wiz_level())
        victim->catch_tell("Attack pen: " + pen +
            "\nAttack Damage: " + hitres[3] + "\n");

    switch(hitres[4])
    {
        case A_LEGS:
            adjective = "crouches low and ";
        break;
        case A_HEAD:
            adjective = "aims high and ";
        break;
        case A_TORSO:
            adjective = "follows through and ";
        break;
        default:
            adjective = "";
    }

    switch(hitres[0])
    {
        case -1:
        case 0:
            how = "unharmed";
        break;
        case 1..10:
            how = "barely scratched";
        break;
        case 11..20:
            how = "scratched";
        break;
        case 21..35:
            how = "slightly injured";
        break;
        case 36..50:
            how = "injured";
        break;
        case 51..70:
            how = "badly slashed";
        break;
        case 71..90:
            how = "horribly slashed";
        break;
        default:
            how = "utterly massacred";
        break;
    }

    victim->catch_tell(query_The_name(victim) + " " + adjective +
        "slashes at your " + hitres[1] + " with " + toposs + " " +
        polearm->short() + ", leaving you feeling " + how + " from " +
        toposs + " attack.\n");
    tell_watcher(query_The_name(victim) + " " + adjective + "slashes at " +
        QTNAME(victim) + "'s " + hitres[1] + " with " + toposs + " " +
        polearm->short() + ", leaving " + QTNAME(victim) + " feeling " +
        how + " from " + LANG_POSS(QTNAME(to)) + " attack.\n", victim);

    return 1;
}

