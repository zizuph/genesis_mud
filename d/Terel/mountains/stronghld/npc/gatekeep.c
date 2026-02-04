/*
 *   Stronghold Gatekeeper
 *   Tomas   -- Jan 2000
 */

#include "/d/Terel/include/Terel.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <formulas.h>
#include <stdproperties.h>

inherit STDMONSTER;
void close_gate();
int berzerked = 0;

#define GATE MOUNTAIN_DIR + "stronghld/fielde"

public string
open_gate()
{
    if(TP->query_prop("_stonehld_attacked")) 
    {
       command("say I'll let you out, but you aint getting back " +
          "in ya bastard!\n");
       (GATE)->open_gate();
       set_alarm(8.0, -1.0, "close_gate");
       return "";  
    }
    else
    {
       command("nod ack");
       (GATE)->open_gate();
       set_alarm(8.0, -1.0, "close_gate");
       return "";
    }
    return "";
}

void
close_gate()
{
    (GATE)->close_gate();
    return;
}


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
        return;

    set_name("golan");
    set_living_name("Terel:golan");
    add_name("gatekeeper");
    set_race_name("dwarf");
    set_adj(({"burly","long-bearded"}));
    set_title("Gate Keeper");
   set_long("The burly gatekeeper operates the metal gate " +
      "before you. Perhaps, if you ask him he'd open it for you.\n");

   default_config_npc(160);
   set_skill(SS_DEFENCE, 85);
   set_skill(SS_UNARM_COMBAT, 100);
   set_skill(SS_PARRY, 80);
   set_all_hitloc_unarmed(75);
   add_ask(({"open metal gate","open gate","open"}), open_gate, 1);
   set_act_time(10);
   add_act("smile");
   add_act("grumble");
   add_act("shiver");

    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
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
    add_prop(LIVE_I_QUICKNESS,100 + random(20)); 
 
    
    command("emote mumbles something under his breath.");
    tell_room(environment(TO), "The dwarven warriors eyes glow a second " +
       "as he continues to mumble what sounds like a prayer.\n");
    command("emote roars showing renewed strength as he throws " +
            "himself into battle!");
}

    
    

