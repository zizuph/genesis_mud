/*
 *      /w/vencar/caravan/npc/leachim.c
 *
 *      Leahcim Draagslag ,
 *      inspired by Ordheus in vingaard
 *
 *      Created by Vencar 22/09/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      09/2003
 */

#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

#define DEBUG_WIZ       "vencar"
#define DEBUG_MSG(x)   find_player(DEBUG_WIZ)->catch_msg("Debug msg: " + x + ".\n");

inherit "/std/act/action";
inherit VSTD + "knight_base";
inherit AUTO_TEAM

int sublevel, level;
string subtitle, title;
object attacker;
int justcharged = 5;

string
query_race_name()
{
    return(calling_function() == "query_presentation" ? "Solamnian" :
      "human");
}

string
set_my_title()
{
    level = 4;
    sublevel = 9;
    subtitle = SWORD_TITLES[sublevel];
    return "Knight of the Crown";
}

string
long_desc()
{
    string str;

    str = "This confident Knight of Solamnia stands with a dignity " +
      "that shows his dedication clearly. He has a lengthy white " +
      "moustache, and it is a source of pride. He is scanning the " +
      "surroundings watching the security of the wagons. " +
      "He is a "+subtitle+".\n";

    return str;
}


void
get_me_soul()
{
    object horse;

    ::get_me_soul();

    /* and here is the ability to ride */
    horse = clone_object(STEED);
    horse->set_short("spirited steel-grey warhorse");
    horse->move(E(TO));
    TO->command("mount horse");

    setuid();
    seteuid(getuid());
    clone_object(KOBJ + "cavalry_npc_shadow")->shadow_me(TO);

}

public void
create_knight_npc()
{
    int i;

    set_name("leahcim");
    add_name("_krynn_knight_");
    set_living_name("leahcim");
    set_adj("confident");
    set_title("Draagslag of Palanthas, the Lord of Swords");
    add_name("gLeahcim");
    set_gender(0);
    set_introduce(1);
    set_long(long_desc);
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 140 + random(30));
    set_all_hitloc_unarmed(50);

    set_knight_prestige(-8);
    set_alignment(1200);

    set_skill(SS_KATTACK, 150);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 120);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);

    set_skill(SS_ANI_HANDL, 80);
    set_skill(SS_RIDING, 100);
    set_skill(SS_MOUNTED_COMBAT, 100);

    set_pick_up_team(({"_krynn_knight_"}));
    set_act_time(20);
    add_act("emote smooths his white moustache with care.");
    add_act("emote gazes deep into your eyes.");
    add_act("emote solemnly declares: Est Sularus oth Mithas!");
    add_act("hcalm");
    add_act("hrub");
    add_act("hrear");
    add_act("hsnap");
    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'caravan'", "say The caravan shall " +
      "never fall while I guard it!",1);
    add_ask(" [about] 'task' / 'quest'", "say I have no tasks " +
      "for you, seek elsewhere.",1);
    add_ask(" [about] 'oath'", "say My Honour is My Life.",1);
    add_ask(" [about] 'knight' / 'knights'", "say The " +
      "Knights of Solamnia are a body of warriors, bound " +
      "together in holy unity with the purpose of defending " +
      "the weak and impoverished and those in need, fighting " +
      "injustice and stemming the tide of evil. Several times "+
      "in our history, members of the Knights have been " +
      "called on to defend the world.", 1);

}

int
special_attack(object enemy)
{
    int ret = 0;

    DEBUG_MSG("in special attack " + TO->short() );
    if (justcharged < 5)
    {
        DEBUG_MSG ("in special attack sp:" + justcharged);
        justcharged++;
        ret = TO->command("sp "+enemy->query_real_name());
        DEBUG_MSG  ("in special attack sp:" + ret + enemy->query_real_name());
    }
    else
    {
        DEBUG_MSG  ("in special attack charge:" + justcharged);
        ret = TO->charge_special(enemy);
        DEBUG_MSG  ("in special attack charge: " + ret + " " + enemy->query_real_name());
        justcharged = 0;
    }

    return ret;
}


/* Due to this is an npc, I cannot get the set_bit to work,
 * Instead I override the test_bit function. Vencar 20-09-2003
 */
public int
test_bit(string dom, int group, int bit)
{
    if ( (dom == "Krynn") && (group == GUILD_GROUP) && (bit == MEMBER_BIT) )
        return 1;

    return 0;

}

public void
init_living()
{
    init_team_pickup();
    ::init_living();
}
