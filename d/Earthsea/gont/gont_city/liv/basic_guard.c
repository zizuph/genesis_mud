/*
 * Changes:
 * 2021-08-26 - Cotillion
 * - Cut down on chat spam
 */
#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Krynn/open/auto_teaming";
inherit "/d/Earthsea/lib/width_height";

#include "basic_guard.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

public void create_guard() { }

public nomask void
create_earthsea_monster()
{
    string adj1 = DESC1[random(sizeof(DESC1))],
        adj2 = DESC2[random(sizeof(DESC2))];

    set_name("guard");
    set_pname("guards");
    set_adj(adj1);
    add_adj(adj2);
    set_gender(random(1));
    set_race_name("human");
    set_height("tall");
    set_width("lean");
    add_name("guard");
    add_name("__es_gont_guard__");
    set_short(adj1 + " " + adj2 + " guard");
    set_pshort(adj1 + " " + adj2 + " guards");
    set_long(capitalize(LANG_ASHORT(this_object())) + ". "+
        "This is one of the mercenary guards hired by "+
        "the Lord of Gont to keep law and order in the city. "+
        capitalize(query_pronoun()) + " looks confident"+
        " and is probably a tough opponent.\n");
    set_act_time(50);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_pick_up_team("__es_gont_guard__");
    create_guard();
}

public void
set_levels(int level)
{
    int skill, i = 6;

    while(i--)
    {
        set_base_stat(i, levels[level] - 10 + random(
            (i == 5 ? 70 : 30)));
    }

    set_hp(query_max_hp());
    set_all_hitloc_unarmed(1);

    set_skill(SS_DEFENCE, (levels[level] / 3 ) * 2 + random(20));
    set_skill(SS_WEP_AXE, (levels[level] / 3 ) * 2 + random(20));
    set_skill(SS_WEP_CLUB, (levels[level] / 3 ) * 2 + random(20));
    set_skill(SS_PARRY, (levels[level] / 3 ) * 2 + random(20));
    set_skill(SS_BLIND_COMBAT, (levels[level] / 3 ) * 2 + random(20));
    set_skill(SS_WEP_SWORD, (levels[level] / 3 ) * 2 + random(20));
    set_skill(SS_WEP_POLEARM, (levels[level] / 3 ) * 2 + random(20));
}

public int
attacked_by(object player)
{
    ::attacked_by(player);

    object *bored = filter(query_team_others(), &not() @ &->query_attack());

    if (sizeof(bored)) 
    {
        command("shout Invaders!! Sound the alarm!");
        bored->command("kill " + OB_NAME(player));
    } else {
        switch(random(10)) {
        case 0:
            command("say That was one big mistake!");
            command("grumble angri");
        break;
        case 1:
            command("emote gets a grim expression in " +
                query_possessive() + " face.\n");
            command("say Die then!");
        break;
        case 2:
            command("shout Guards! Guards! To me!");
            command("smile conf");
        break;
        case 3:
            command("say A brave but dumb decision.");
            command("say I am going to kill you!");
        break;
        case 4:
            command("emote raises " + query_possessive() + " weapons"+
                " in defence confidently.");
        break;
        default:
            command("say This troublemaker will die for that!");
            command("cackle confi");
        }
    }

    return 1;
}

public void
init_living()
{
    ::init_living();
    init_team_pickup();
}
