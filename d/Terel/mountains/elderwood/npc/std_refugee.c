/*
 *
 * std_refugee.c for use with the fields of Elderwood forest  -- Tomas June 2000
 *
 */


#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#define ARM_DIR  MOUNTAIN_DIR + "elderwood/armour/"
#define WEP_DIR  MOUNTAIN_DIR + "elderwood/weapon/"


int power;
string adj();
string adj2();
void dress_me();

public string
reply_pathfinders()
{
    command("say Those Pathfinders come and go all the time. Always scouting " +
            "around the forests looking for danger. God bless em! They " +
            "really came through for us this time.\n");
    return "";
}


public string
reply_goblins()
{
    command("say Where?!? Oh.. you wanna know about em.\n");
    command("say Whats there to say. One day, everything was peaceful " +
            "as could be. Then the drums came. Sounded like thunder " +
            "at first. Some of those Pathfinders came into town, appeared " +
            "outta nowhere just like usual.. Told us we had to burn " +
            "everything, poison the wells, etc. Cause an army of " +
            "goblins and ogres were a closing in on the vale.\n");
    command("say Well.. We grabbed what we could, put a torch to whatever " +
            "would burn, then made for the pass. The forest was " +
            "all quiet n' all coming down. Gave me the willies..\n");
    return "";
}

public string
reply_vale()
{
    command("say Ahh.. The Vale..\n");
    command("sigh wist");
    command("say The Vale is our home. We call it Trelliswood. Trelliswood " +
            "is beautiful. Not sure what it looks like now though.. " +
            "The last thing I saw from fair Trelliswood was it burning " +
            "to the ground.\n");
    command("sniff");
    return "";
}


public string
reply_line()
{
    command("say Not long after we arrived, the entire vale, forest everything " +
            "was overrun right down to the mouth of the northern pass. " +
            "Thats where the men of Stonehold have em held. I sure hope " +
            "the southerners can bring help fast. No telling how much " +
            "longer we can hold em.\n");
    return "";
}


public string
reply_stonehold()
{
    command("say Stonehold is a massive fortress up in the pass. " +
            "Dwarven miners carved the fort out of solid rock they did!  "+
            "Those walls are huge, thick as an Ogre is tall.. " +
            "If anything can hold the Goblins, it can!");
    return "";
}


void
create_monster()
{
    power = 30+random(70);

    set_name("refugee");
    set_pname("refugees");
    set_gender(random(2));
    set_race_name("dwarf");
    set_adj(adj());
    set_adj(adj2());
    default_config_npc(power);
    set_alignment(random(500));
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, power);
    set_skill(SS_AWARENESS, power/2);
    set_skill(SS_2H_COMBAT, power);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));

    set_chat_time(100 + random(100));
    add_chat("Hello, welcome stranger.");
    add_chat("We dont have much, but its better than being eaten " +
       "by those goblins.");
    add_chat("The Pathfinders got us out just in the nick of time!");
    add_chat("We could hear the horrible sound of their beating drums " +
       "all the way to the pass.");
    add_chat("We lost everything but what we carry upon our backs.");
    add_chat("The hardest thing we had to do was burn our homes to " +
       "the ground.");
    add_chat("If you plan on heading up there, dont drink from " +
       "our wells. We poisoned em so those horrible creatures " +
       "wouldn't use em.");
    add_chat("The Pathfinders told us that those goblins and ogres " +
       "are eating everything the moves.. Even the stuff that aint " +
       "moving no more! I hope they choke on a bone!");
    add_chat("Without Stonehold in the way, no telling how far those " +
       "gobbos would be by now.");
    add_chat("Our boys are holding the line but just barely.");
    add_chat("Bundle up, its cold out there.");

    set_act_time(75 + random(200));
    add_act("emote rubs their nose.");
    add_act("cough");
    add_act("sneeze");

    add_ask(({"goblins", "ogres", "creatures"}), reply_goblins, 1);
    add_ask(({"pathfinders", "Pathfinders"}), reply_pathfinders, 1);
    add_ask(({"vale", "trelliswood", "Trelliswood", "Vale"}), 
              reply_vale, 1);
    add_ask(({"line", "boys"}), reply_line, 1);
    add_ask(({"Stonehold", "stonehold"}), reply_stonehold, 1);
    
    dress_me();

}


void
dress_me()
{
    seteuid(getuid(this_object()));     

//    clone_unique(TEREL_DIR + "weapon/ddagger",5,TEREL_DIR + "weapon/short")->move(TO);

    switch(random(6)) 
    {
        case 0 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_axe")->move(TO);
                      break;
        case 1 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_knife")->move(TO);
                  clone_object(WEP_DIR + "refugee_knife")->move(TO);
 //                 clone_object(CALATHIN_DIR + "obj/backpack")->move(TO);
                      break;
        case 2 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
 //                 clone_object(CALATHIN_DIR + "obj/backpack")->move(TO);
                  clone_object(WEP_DIR + "refugee_pickaxe")->move(TO);
                      break;
        case 3 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_hoe")->move(TO);
                      break;
        case 4 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_shovel")->move(TO);
                      break;
        case 5 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_polearm")->move(TO);
 //                 clone_object(CALATHIN_DIR + "obj/backpack")->move(TO);
                      break;
    }

    command("wield weapons");
    command("wear all");
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
            "stern","slim","stern",
            "barrel-chested","fat","ancient","young"});
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


