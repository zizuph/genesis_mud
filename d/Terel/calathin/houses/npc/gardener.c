/*
 * house4 Gardner.c
 * Modification of: Std Calathin Citizen
 *
 * Tomas 11-17-1999
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;


#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define ARM_DIR  CALATHIN_DIR + "armour/"
#define WEP_DIR  CALATHIN_DIR + "weapon/"
#define QUEST_GLOVES_GROUP 1
#define QUEST_GLOVES_BIT 12
#define QUEST_GLOVES_EXP 750


int power;
string adj();
string adj2();
string races();


public string
reply_gloves()
{
   if (TP -> test_bit("Terel", QUEST_GLOVES_GROUP, QUEST_GLOVES_BIT))
   {
     return "You have done this once! Don't you remember?\n";
   }

   if(TP->query_prop("_terel_gardener_quest"))
   {
      command("say I told you. I lost my gloves and I need them in order " +
              "to grow certain medicines. I'll understand if you are " +
              "unable to find them.");
      return "";
   }

   command("say I lost my prized herbing gloves. I took them " +
      "off for just a second in order to handle some delicate flora, " +
      "then they were gone! I need those gloves in order to grow certain " +
      "medicines in order to heal some sick children in Calathin. " +
      "I'm offering a reward to the person who returns the gloves to me.");

   TP->add_prop("_terel_gardener_quest", 1);

   return "";
}

void
create_monster()
{
    power = 30+random(70);

    set_name("gardener");
    set_pname("gardeners");
    set_gender(random(1));
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_long("The gardener.\n");
    default_config_npc(power);
    set_alignment(random(500));
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_AWARENESS, power/2);
    set_skill(SS_2H_COMBAT, power);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(1);
    add_act("close door");
    add_act("emote tends to one of the plants.");
    add_act("emote mutters something about bugs.");

    add_ask(({"quest","gloves","task","herbing gloves"}), reply_gloves, 1);


}


public void
wrong_msg()
{
    command("ponder");
    command("say Uhm.. These aren't the right gloves. Nice try however..");
    command("drop gloves");
}


public void
right_msg(object me)
{
    string name;

    if (!me || ETO != environment(me)) return;

    name = me->query_real_name();
    command("wear gloves");
    command("smile " + name);
    if (me -> test_bit("Terel", QUEST_GLOVES_GROUP, QUEST_GLOVES_BIT)) {
        tell_object(me, "You have done this once! " +
                        "Don't you remember?\n");
    } else {
        if (me->query_exp() <= QUEST_GLOVES_EXP ) {
            me->add_exp(me->query_exp(), 0);
        } else {
            me->add_exp(QUEST_GLOVES_EXP, 0);
        }
        me->set_bit(QUEST_GLOVES_GROUP, QUEST_GLOVES_BIT);
        me->catch_msg("You suddenly feel more experienced.\n");
        tell_room(ETO, QCTNAME(me) +
             " has become more experienced.\n", me);
        seteuid(getuid());
        write_file(QUEST_LOG, capitalize(name) +
           " solved the missing gardener gloves quest (" + ctime(time()) + ")\n");
    }
}


void
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from);

    if ((interactive(from)) && ob->query_prop("_Terel_Gardener_Gloves"))
    {

        if (TP->query_prop("_terel_gardener_found") && TP->query_prop("_terel_gardener_quest"))
        {
            TP->remove_prop("_terel_gardener_found");
            TP->remove_prop("_terel_gardener_quest");
            set_alarm(2.0, -1.0, &right_msg(TP));
        }
        else
        {
            set_alarm(2.0, -1.0, wrong_msg);
        }
    }


}

public void
item_give(string s1, string s2)
{
    object gloves = present("_Terel_Gardener_Gloves", TO);

    if (gloves)
    {
        if (TP->query_prop("_terel_gardener_found") && TP->query_prop("_terel_gardener_quest"))
        {
            TP->remove_prop("_terel_gardener_found");
            TP->remove_prop("_terel_gardener_quest");
            set_alarm(2.0, -1.0, &right_msg(TP));
        }
        else
        {
            set_alarm(2.0, -1.0, wrong_msg);
        }
    }
}


string races()
{
    string *races;
    races = ({"elf","half-elf","human"});
    return races[random(sizeof(races))];
}

string adj()
{
    string *adj;
    adj = ({"black-haired","blond-haired","muscular", "swarthy",
               "thick-armed","long-haired","short-haired", "silver-haired",
               "red-haired", "brown-haired", "grey-haired"});
    return adj[random(sizeof(adj))];
}

string adj2()
{
    string *adj2;
    adj2 = ({"blue-eyed", "hazel-eyed", "black-eyed", "brown-eyed",
            "green-eyed","olive-skinned","brown-skinned",
            "tanned","dark-skinned","light-skinned","grey-eyed"});
    return adj2[random(sizeof(adj2))];
}

