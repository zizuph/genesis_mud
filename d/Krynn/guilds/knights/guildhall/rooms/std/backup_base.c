/* The normal guards by Percy. */
/* base file to inherit for all knight npc's by Aridor, 09/94 */
/* modified by Teth and Morrigan, 01/97 */
    
#include "../../../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit M_FILE

#include "../../npcs/std/killer.h"

int level, soul_id;
void create_knight_npc();
void get_me_soul();

void
set_level(int lev)
{
    level = lev;
    create_knight_npc();
}

int
query_level()
{
    return level;
}

string
set_my_title()
{
    if (!level)
    {
        level = random(9) + 1;
    }
    
    if (level == 10)
    {
        return "Order of the Rose";
    }
    if (level == 8 || level == 9)
    {
        return "Order of the Sword";
    }
    if (level < 8 && level > 3)
    {
        return "Order of the Crown";
    }
    return "Knighthood";
}

string
query_guild_name_occ()
{
    return "Solamnian Knights";
}

int
query_knight_level()
{
    switch(level)
    {
        case 10:
          return 5;
        case 8..9:
            return 4;
        case 4..7:
            return 3;
        case 1..3:
            return 2;
    }
}

void
create_knight_npc()
{
    set_my_title();
}

void
create_krynn_monster()
{
    int i, gender;
    string race, genstr, title;
    
    for (i = 0; i < 6; i++)
    {
        set_base_stat(i, 100 + random(20));
    }

    set_base_stat(5, 130+ random(20));

    create_knight_npc();

    if (TO->query_knight_level() == 2)
    {
        title = "squire";
    }
    else
    {
        title = "knight";
    }

    gender = (random(100) > 90 ? 1 : 0);
    genstr = (gender == 0 ? "male " : "female ");
    race = ((random(100) + 1) < 90 ? "human" :
        (random(10) + 1) > 5 ? "half-elf" : "dwarf");
    
    set_name(title);
    set_race_name(race);
    set_gender(gender);

    if (race == "dwarf")
    {
        switch(random(5) + 1)
        {
            case 5:
                set_adj(({"stocky", "bearded"}));
                set_short("stocky bearded "+genstr+title);
                break;
            case 4:
                set_adj(({"stout", "dark-haired"}));
                set_short("stout dark-haired "+genstr+title);
                break;
            case 3:
                set_adj(({"barrel-chested", "thick-bearded"}));
                set_short("barrel-chested thick-bearded "+genstr+title);
                break;
            case 2:
                set_adj(({"short", "stocky"}));
                set_short("short stocky "+genstr+title);
                break;
            case 1:
                set_adj(({"tall", "grey-bearded"}));
                set_short("tall grey-bearded "+genstr+title);
                break;
            default:
                set_adj("deformed");
                set_short("deformed "+genstr+title);
                break;
        }
    }
    if (race == "human" || race == "half-elf" && gender == 1)
    {
        switch(random(5) + 1)
        {
            case 5:
                set_adj(({"stern", "blue-eyed"}));
                set_short("stern blue-eyed female "+title);
                break;
            case 4:
                set_adj(({"light-skinned", "solemn"}));
                set_short("light-skinned solemn female "+title);
                break;
            case 3:
                set_adj(({race == "half-elf" ? "pointy-eared" : "dark-eyed",
                         "slender"}));
                set_short(race == "half-elf" ? "pointy-eared slender female "+
                          title : "dark-eyed slender female "+title);
                break;
            case 2:
                set_adj(({"tall", "stone-faced"}));
                set_short("tall stone-faced female "+title);
                break;
            case 1:
                set_adj(({"bright-eyed", "short"}));
                set_short("short bright-eyed female "+title);
                break;
            default:
                set_adj(({"deformed"}));
                set_short("deformed female "+title);
                break;
        }
    }

    if (race == "half-elf" || race == "human" && gender == 0)
    {
        switch(random(9) + 1)
        {
            case 10:
                set_adj(({"tall", "muscular"}));
                set_short("tall muscular male "+title);
                break;
            case 9:
                set_adj(({"stern", "proud"}));
                set_short("proud stern male "+title);
                break;
            case 8:
                set_adj(({"pale", race == "half-elf" ? "calm" : "moustachioed"}));
                set_short(race == "half-elf" ? "pale calm male "+title :
                         "pale moustachioed male "+title);
                break;
            case 7:
                set_adj(({"young", "dark-eyed"}));
                set_short("young dark-eyed male "+title);
                break;
            case 6:
                set_adj(({"stone-faced", "blue-eyed"}));
                set_short("stone-faced blue-eyed male "+title);
                break;
            case 5:
                set_adj(({"cold", "haughty"}));
                set_short("cold haughty male "+title);
                break;
            case 4:
                set_adj(({"long-haired", "dark-eyed"}));
                set_short("long-haired dark-eyed male "+title);
                break;
            case 3:
                set_adj(({"blue-eyed", race == "human" ? "stocky" : "slender"}));
                set_short(race == "human" ? "stocky blue-eyed male "+title :
                         "slender blue-eyed male "+title);
                break;
            case 2:
                set_adj(({"dark-haired", "cautious"}));
                set_short("cautious dark-haired male "+title);
                break;
            case 1:
                set_adj(({"solemn", "light-haired"}));
                set_short("solemn light-haired male "+title);
               break;
            default:
                set_adj("deformed");
                set_short("deformed male "+title);
                break;
        }
    }
    
    set_extra_long(gender == 1 ? "Her tunic is decorated with the symbol of "+
        "the "+set_my_title()+".\n" : "His tunic is decorated with the symbol "+
        "of the "+set_my_title()+".\n");
    
    set_skill(SS_BLOCK, 70 + random(30));
    set_skill(SS_KATTACK, 70 + random(30));
    set_skill(SS_WEP_SWORD, 60 + random(40));
    set_skill(SS_PARRY, 60 + random(30));
    set_skill(SS_DEFENCE, 50 + random(25));
    set_skill(SS_2H_COMBAT, 60);
    set_skill(SS_AWARENESS, 50 + random(15));
    set_skill(SS_WEP_POLEARM, 60 + random(15));
    set_skill(SS_WEP_CLUB, 60 + random(10));
    set_act_time(random(5) + 5);
    add_act(level > 3 ? "kbow" : "kaspire");
    add_act("pledge");
    add_act("kdeclare");
    add_act("kswear");
    add_act("kdanger");
    add_act(race == "half-elf" ? "ksmooth h" : "ksmooth");
    add_act(level > 3 ? "ksomber" : "kcrown");
    add_act("kstudy");
    add_act("tend weapons");
    set_cact_time(random(2) + 1);
    add_cact("@@do_rescue");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop("_knight_npc", 1);
    set_alignment(500);
    set_knight_prestige(-2);
    set_aggressive(VBFC_ME("check_if_aggressive"));
    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alarm(1.0,0.0,"arm_me");
}

void
get_me_soul()
{
    TO->add_cmdsoul(KOBJ + "solamnian_soul");
    TO->add_cmdsoul(VOBJ + "kattack_special");
    TO->update_hooks();
    remove_alarm(soul_id);
}

void
arm_me()
{
    seteuid(geteuid(TO));
    
    clone_object(VARM+"s_helm")->move(TO);
    clone_object(VARM+"s_gauntlets")->move(TO);
    
    if (level > 6 && random(2))
    {
        clone_object(VARM+"full_armour")->move(TO);
    }
    else
    {
        clone_object(VARM + "s_armour")->move(TO);
    }
    
    switch(random(20) + 1)
    {
        case 1..5:
            clone_object(VARM+"s_shield")->move(TO);
            clone_object(VWEP + "s_sword")->move(TO);
            break;
        case 6..7:
            clone_object(VWEP+"s_mace")->move(TO);
            clone_object(VARM+"s_shield")->move(TO);
            break;
        case 8:
            clone_object(VWEP+"s_shortsword")->move(TO);
            clone_object(VARM+"s_shield")->move(TO);
            break;
        case 9..12:
            clone_object(VWEP+"two_handed_sword")->move(TO);
            break;
        case 13..15:
            clone_object(VWEP+"s_halberd")->move(TO);
            break;
        case 16..17:
            clone_object(VWEP+"s_sword")->move(TO);
            clone_object(VWEP+"s_shortsword")->move(TO);
            break;
        case 18:
            clone_object(VWEP+"s_sword")->move(TO);
            clone_object(VWEP+"s_mace")->move(TO);
            break;
        case 19:
            clone_object(VWEP+"s_shortsword")->move(TO);
            clone_object(VWEP+"s_mace")->move(TO);
            break;
        case 20:
            clone_object(VWEP+"s_shortsword")->move(TO);
            clone_object(VWEP+"s_shortsword")->move(TO);
            break;
        default:
            clone_object(VWEP+"s_sword")->move(TO);
            clone_object(VARM+"s_shield")->move(TO);
    }
    
    command("wear all");
    command("wield all");
}

int
check_if_aggressive()
{
    return TP->query_prop("_i_attacked_in_vingaard");
}

void
attacked_by(object ob)
{
    switch(random(6))
    {
        case 5:
            TO->command("kwep "+ob->query_real_name());
            break;
        case 4:
            TO->command("kc2 death");
            break;
        case 3:
            TO->command("kc2");
            break;
        case 2:
            TO->command("kc1");
            break;
        case 1:
            TO->command("kfirm");
            break;
        default:
            TO->command("kamused");
            break;
    }
    
    if (ob->query_race_name() != "draconian")
    {
        TO->do_rescue();
    }
    ::attacked_by(ob);
}

string
do_rescue()
{
    /* rescue a fellow knight who is currently under attack */
    object *who = FILTER_LIVE(all_inventory(E(TO)));
    object *ene, *good = ({ }), *bad = ({ });
    object person;
    int i;
    who -= ({ TO, 0 });

    ene = who->query_attack();

    for(i = 0; i < sizeof(ene); i++)
    {
        if (who[i] != TO  && (who[i]->id("knight") ||
            who[i]->query_guild_name_occ() == "Solamnian Knights")
            && ene[i] && !ene[i]->id("knight") &&
            ene[i]->query_guild_name_occ() != "Solamnian Knights")
        {
            good += ({ who[i] });
            bad += ({ ene[i] });
        }
    } 

    if (!good || !sizeof(good))
    {
        return "";
    }

    i = random(sizeof(bad));
    if (!good[i]->id("knight") || random(5))
    {
        if (good[i]->query_hp() < query_hp())
        {
            attack_object(bad[i]);
            bad[i]->attack_object(TO);
            tell_room(E(TO),"The human knight heroically rescues " +
                QTNAME(good[i]) + ".\n");
        }
    }
    else
    {
        if (E(TO)->not_called_for_help_yet() &&
            (bad[i])->query_race_name() != "draconian")
        {
            E(TO)->call_for_help(TO,good[i],bad[i]);
        }
    }
    return "";
}

int
do_sp(object enemy)
{
    TO->command("sp "+enemy->query_name());
}

int
special_attack(object enemy)
{
    do_sp(enemy);
    return 1;
}

