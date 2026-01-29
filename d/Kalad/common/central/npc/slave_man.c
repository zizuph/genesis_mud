/*
 * Cotillion - 2017-10-01
 * - Fixed cloning of key into void and cleanup.
 */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"

/* by Antharanos */
/* modified by Korat */
void
create_monster()
{
    setuid();
    seteuid(getuid());

    ::create_monster();
    set_name("scrough");
    set_race_name("human");
    set_adj("cruel");
    add_adj("bulky");
    set_long("A balding, chubby individual that peers around as if he "+
            "owned everything here, including the people. Perhaps it is because "+
            "he does own the people here! At least the slaves, that is.\n");
    set_stats(({80,60,75,50,50,60}));
    set_alignment(-750);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_2H_COMBAT,50);
    set_skill(SS_UNARM_COMBAT,25);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,50);
    set_act_time(6);
    add_act("shout Keep it moving you miserable curs!");
    add_act("spit slave");
    add_act("kick slave");
    add_act("crack");
    add_act("crack");
    add_act("crack");
    set_cact_time(3);
    add_cact("grin mer all");
    add_cact("say I'll beat you just like I do my slaves.");
    set_title("the Slave Guard");
    add_speak("Whadda you want?!?\n");
    set_knight_prestige(750);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    equip(({ 
        "/d/Kalad/common/caravan/arm/sovest", "/d/Kalad/common/caravan/arm/sogloves", 
        "/d/Kalad/common/caravan/arm/soboots", "/d/Kalad/common/caravan/obj/ikey",
        "/d/Kalad/common/caravan/wep/sowhip"
    }));

    MONEY_MAKE_SC(random(30))->move(this_object(), 1);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("fume");
      command("say I will kill you now!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}   

void
do_die(object killer)
{
    int i;
    object *ob;
    if (query_hp()>0) return;
    if (present("slave",environment()))
    {
        tell_room(environment(),"Suddenly the slaves realize that they have been "+
                "freed from their slavery!\n");
        ob = FILTER_LIVE(all_inventory(environment()));
        for (i=0;i<sizeof(ob);i++)
        {
            if (ob[i]->query_real_name()=="slave" && ob[i]->query_npc())
            {
                ob[i]->command("thank "+lower_case(killer->query_real_name()));
                ob[i]->command("emote runs away.");
                ob[i]->remove_object();
            }
        }
    }
    ::do_die(killer);
}
