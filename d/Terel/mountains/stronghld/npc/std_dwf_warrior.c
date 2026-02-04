/*
 * std_dwf_warrior.c
 * Dwarven Warrior for mountains/stronghld 
 * Tomas -- Nov. 1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;


#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#define ARM_DIR  MOUNTAIN_DIR + "stronghld/armour/"
#define WEP_DIR  MOUNTAIN_DIR + "stronghld/weapon/"

int power;
int stat;
int berzerked = 0;
string adj();
string adj2();
void dress_me();

/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}


void
create_monster()
{
    power = 70+random(30);
    stat = 70+random(50);

    set_name("warrior");
    set_pname("dwarves");
    set_race_name("dwarf");
    set_adj(adj());
    set_adj(adj2());
    set_long("A dwarven warrior assigned to Stonehold.\n");
    default_config_npc(stat);
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_CLUB, power);
    set_skill(SS_WEP_POLEARM, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, power);
    set_skill(SS_AWARENESS, power);
    set_skill(SS_2H_COMBAT, power);
    set_alignment(500 + random(700));
    set_gender(MALE);  
    set_aggressive("@@benice");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(500));
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_SEE_INVIS, 3);
    add_prop(NPC_I_NO_FEAR, 1);

    dress_me();

    set_act_time(5 + random(20)); 
    add_act("emote adjusts his armour.");
    add_act("stare confident");
    add_act("say Is there something I can do for you?");


    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
   
}

void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(ARM_DIR + "dwarf_plate")->move(TO);
    clone_object(ARM_DIR + "dwarf_robe")->move(TO);
    clone_object(ARM_DIR + "dwarf_boots")->move(TO);    
    clone_object(ARM_DIR + "dwarf_helmet")->move(TO);  
  
    switch(random(4)) 
    {
        case 0 :  clone_object(WEP_DIR + "shortsword")->move(TO);
                  clone_object(WEP_DIR + "dwarf_battleaxe")->move(TO);   
                      break;
        case 1 :  clone_object(WEP_DIR + "arbir")->move(TO);
                      break;
        case 2 :  clone_object(WEP_DIR + "dwarf_battleaxe")->move(TO);
                  clone_object(ARM_DIR + "dwarf_shield")->move(TO);
                      break;
        case 3 :  clone_object(ARM_DIR + "dwarf_shield")->move(TO);
                  clone_object(WEP_DIR + "shortsword")->move(TO);
                      break; 
    }
    command("wield weapons");
    command("wear armours");
}


mixed
benice()
{
       
    if((TP->query_prop("_stonehld_attacked")) || TP->query_race() == "goblin" && TP->query_alignment() < 910)
    { 
       set_alarm(itof(random(1) + 1), 0.0, "command",
                  "emote shouts We are under attack!!");
       return 1; 
    }    
    return 0;    
}



string adj()
{
    string *adj;
    adj = ({"black-haired","bald","long-bearded", "black-bearded",
               "thick-armed","scarred","dark-haired", "brown-haired",
               "grey-haired", "wild-eyed", "brown-bearded"});
    return adj[random(sizeof(adj))];
}

string adj2()
{
    string *adj2;
    adj2 = ({"confident", "muscular", "massive", "brown-skinned",
            "dark-eyed","impressive","stern","old",
            "blue-eyed","green-eyed","light-skinned","grey-eyed"});
    return adj2[random(sizeof(adj2))];
}




void
attacked_by(object ob)
{
   object *arr;
   int i;
   
   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
       arr[i]->notify_ob_attacked_me(this_object(), ob);
   ob->add_prop("_stonehld_attacked",1);
}



void
notify_ob_attacked_me(object friend, object attacker)
   {
   if (query_attack())
      return;
   
   set_alarmv(1.0, -1.0, "help_friend", ({attacker}));
   }


void
help_friend(object ob)
{
    string msg;

    switch (random(5)) {
     case 0:
        msg = "We are under attack!!";
        break;
     case 1:
        msg = "How dare you attack us!";
        break;
     case 2:
        msg = "Time to die!";
        break;
     case 3:
        msg = "Guards, Guards!!";
        break;
     case 4:
        msg = "Roars, as he throws himself into battle!";
        break;
    }
    
    if (ob && !query_attack() && present(ob, environment())) {
        command("say " + msg);
        command("kill " + lower_case(ob->query_real_name()));
        command("kill " + lower_case(ob->query_real_name()));      
    }
}


react_attacked(s,ss)
{
  set_alarmv(1.0, 5.0, "att",({TP}));
  return 1;

}


att(s,ss)
{
  int qryhp;
  qryhp = (TO->query_max_hp() / 2);

  if(berzerked == 1)
  return 0;

  if(TO->query_hp() <= qryhp)
  {
   set_alarm(1.0, 0.0, "go_berzerk",({TP}));
   return 1;
  }
   return 0; 
}


public void
go_berzerk()
{
    int base_stat;
    int i;
    berzerked = 1;

    for (i = 0; i < 6; i++)
        set_base_stat(i, query_stat(i) + random(30));

    set_hp(query_max_hp());
    set_fatigue(query_max_fatigue());
    add_prop(LIVE_I_QUICKNESS,10 + random(20)); 
 
    
    command("emote mumbles something under his breath.");
    tell_room(environment(TO), "The dwarven warriors eyes glow a second " +
       "as he continues to mumble what sounds like a prayer.\n");
    command("emote roars showing renewed strength as he throws " +
            "himself into battle!");

}

    
    
