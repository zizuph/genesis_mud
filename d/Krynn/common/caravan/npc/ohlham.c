/* Ohlham Ochre of Solanthus,  */
/* inspired by Ordheus in vingaard */
/*

Rhyn mumbles:  if (environment(victim)->query_prop(ROOM_I_TYPE) ==;ROOM_UNDER_WATER ||;Rhyn mumbles:       environment(victim)->query_prop(ROOM_I_TYPE) ==;ROOM_IN_WATER ||;Rhyn mumbles:       environment(victim)->terrain_includes_any(TERRAIN_UNDERWATER))
*/

#include "../local.h"
#undef PARENT
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit VSTD + "knight_base";
inherit AUTO_TEAM


#define DEBUG_WIZ       "vencar"
#define DEBUG_MSG(x)   find_player(DEBUG_WIZ)->catch_msg("Debug msg: " + x + ".\n");


#include "../lib/hunt.h"

int sublevel, level;
string subtitle, title;
object attacker;
int justcharged = 5;
int kdied = 0;

string
query_race_name()
{
    return(calling_function() == "query_presentation" ? "Solamnian" :
      "human");
}

string
set_my_title()
{
    level = 5;
    sublevel = 9;
    subtitle = ROSE_TITLES[sublevel];
    return "Knight of the Rose";
}

string
long_desc()
{
    string str;

    str = "This contemplating Knight of Solamnia takes his duties very " +
      "seriously, by the looks of it. He has a lengthy flowing " +
      "moustache, and it is a source of pride. Every move he makes " +
      "is conservatively measured, scanning the area for trouble only " +
      "when it is necessary, so that all his energies are " +
      "saved for a dangerous situation. He is a "+subtitle+".\n";

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

    set_name("ohlham");
    add_name("_krynn_knight_");
    set_living_name("ohlham");
    set_adj("contemplating");
    set_title("Ochre of Solanthus, the Lord of Roses");
    add_name("gOhlham");
    set_gender(0);
    set_introduce(1);
    set_long(long_desc);
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 150 + random(30));
    set_all_hitloc_unarmed(60);

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

    set_act_time(10);
    add_act("emote smooths his grand moustache with care.");
    add_act("say Ah, to be home in Solanthus, during spring dawning.");
    add_act("say The Knights of Solamnia are a noble organization!");
    add_act("emote gazes deep into your eyes.");
    add_act("emote unruffles his tunic.");
    add_act("emote solemnly declares: Est Sularus oth Mithas!");
    add_act("say The Knights of Solamnia are the finest body of justice and " +
      "honour throughout the land.");
    add_act("emote sighs and wistfully utters: How I wish I could go back " +
      "to Solanthus and visit my family. Alas, it's not to " +
      "be.");
    add_act("emote shuffles his body slightly.");
    add_act("emote steadies his body, and stands tall.");
    add_act("hcalm");
    add_act("hrub");
    add_act("hrear");
    add_act("hsnap");
    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'vingaard'", "say Vingaard Keep " +
      "shall never fall while I stand guard!",1);
    add_ask(" [about] 'caravan'", "say The caravan shall " +
      "never fall while I guard it!",1);
    add_ask(" [about] 'task' / 'quest'", "say I have no tasks " +
      "for you, seek elsewhere.",1);
    add_ask(" [about] 'oath'", "say My Honour is My Life.",1);
    add_ask(" [about] 'ordheus'", "say My cousin Ordheus, " +
      "protects Vingaard Keep while We travel.",1);
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

    set_hunting_name(enemy->query_real_name(), TO);
    if (justcharged < 5)
    {
        justcharged++;
        ret = TO->command("sp "+enemy->query_real_name());
//        DEBUG_MSG  ("in special attack sp:" + ret + enemy->query_real_name());
    }
    else
    {
        if (TO->query_steed())
        {
            ret = TO->charge_special(enemy);
//            DEBUG_MSG  ("in special attack charge: " + ret + " " + enemy->query_real_name());
            justcharged = 0;
        }
    }

    return ret;
}

void
do_hunt_special(object ob, object attacker)
{
//    DEBUG_MSG("hp before:" + ob->query_hp() + " attacker: " + attacker->short() +
//              "attacked: " + ob->short());
    if (E(ob) == E(attacker))
    {
        ob->catch_msg(QCTNAME(attacker) + " strikes you with a heavy blow in " +
                      "the back as " + HE(attacker) + " catches up to you.\n");
        attacker->tell_watcher(QCTNAME(attacker) + " strikes " + QTNAME(ob) +
                  " with a heavy blow in the back as " + HE(attacker) + " catches " +
                  "up to " + HIM(ob) + ".\n", ob);
        ob->hit_me(250,W_SLASH,attacker,-1 );
//        DEBUG_MSG("hp after:" + ob->query_hp());
    }

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

void
arm_me()
{
    seteuid(geteuid(TO));
    clone_object(VARM + "s_armour")->move(TO);
    clone_object(VARM+"s_helm")->move(TO);
    clone_object(VARM+"s_shield")->move(TO);
    clone_object(WEP + "w_lance")->move(TO);
    command("wield weapon");
    command("wear armours");
}


int
query_knight_level()
{
    return 5;
}


public void
do_die(object killer)
{

//    DEBUG_MSG("KNIGHT LEVEL: " + TO->query_knight_level());
    object room = E(TO);

    if(!kdied)
    {
       command("kdie true");
       command("kdie true");
       TO->command("mount horse");
       kdied = 1;

       return;
    }

    ::do_die(killer);
}




