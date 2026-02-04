/*
 * std_ogre.c
 * Ogre for the Elderwood forest.
 * Tomas -- May 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define ARM_DIR  MOUNTAIN_DIR + "elderwood/armour/"
#define WEP_DIR  MOUNTAIN_DIR + "elderwood/weapon/"
#define GEM_DIR "/d/Genesis/gems/obj/"

int power;
int stats;
string adj();
string adj2();
void dress_me();
mixed benice();

string *rgems = ({"alexandrite","beryl_red","diamond","emerald","ruby"}),
       *mgems = ({"sapphire","jade","pearl","spinel_blue","aquamarine","bloodstone"}),
       *cgems = ({"moonstone","onyx","topaz","chrysoprase","garnet","turquoise","coral","agate"});


/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}


void
create_monster()
{
    power = 50+random(30);
    set_race_name("ogre");
    set_adj(adj());
    set_adj(adj2());
    set_long("The ogre is massive in size. Its " +
       "large torso and arms are covered in a thick layer " +
       "of hair matted with blood and bile. The ogre's forehead " +
       "slopes downward revealing its burnous colored red eyes. " +
       "The jaw of the ogre protrudes outward showing wicked yellow " +
       "looking sharp teeth.\n");

    set_stats(({150+random(100), 
                100+random(25), 
                150+random(100), 
                25+random(50), 
                25+random(50), 
                130+random(20)}));

    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_CLUB, power);
    set_skill(SS_WEP_POLEARM, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, power);
    set_skill(SS_AWARENESS, power);
    set_skill(SS_2H_COMBAT, power);

    set_alignment(-500 - random(700));
    set_aggressive("@@benice");
    set_gender(MALE);  
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(NPC_I_NO_FEAR, 1);

    dress_me();

    // Actions the Ogre would do.
    set_act_time(10 + random(20)); 
    add_act("emote curls his lip outward revealing " +
       "its jagged yellow teeth.");
    add_act("emote groans hungrily.");
    add_act("emote whines something about being hungry.");
    add_act("emote groans while rubbing his stomach.");
    add_act("fart");
    add_act("emote scratches behind his ear.");
    add_act("emote scratches under his armour.");


    // Things the Ogre would say when not in combat
    set_chat_time(30 + random(20));  
    add_chat("I hungry!");
    add_chat("When we eat?!?");
    add_chat("I want more pretties!");
    add_chat("Silly little people need more horses. I'm still hungry!");    
 
    set_cchat_time(random(30));
    add_cchat("Dinner! I like when dinner comes to me.");
    add_cchat("Enough! You get in mouth now! Feed my poor stomach.");
    add_cchat("I like my meat tender.. Me gonna pound on you for " +
              "a little while first. Then me eat!");
    add_cchat("Why you put up this fight?!? Me eat you anyways.");
    add_cchat("Yum!");
    add_cchat("You being silly. Hurry up and die. I'm hungry.");
    add_cchat("OooooH! You bring dinner?!? You ARE dinner!");


}

void
dress_me()
{
    seteuid(getuid(this_object()));     

//    clone_unique(TEREL_DIR + "weapon/ddagger",5,TEREL_DIR + "weapon/short")->move(TO);

    switch(random(3)) 
    {
        case 0 :  clone_object(ARM_DIR + "ogre_necklace")->move(TO);
                  clone_object(ARM_DIR + "ogre_boots")->move(TO);
                  clone_object(ARM_DIR + "ogre_breastplate")->move(TO);
                  clone_object(ARM_DIR + "ogre_fur_robe")->move(TO);
                  clone_object(ARM_DIR + "ogre_helmet")->move(TO);
                  clone_object(WEP_DIR + "ogre_axe")->move(TO);
                  clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
                      break;
        case 1 :  clone_object(ARM_DIR + "ogre_sandals")->move(TO);
                  clone_object(ARM_DIR + "ogre_horse_cloak")->move(TO);
                  clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
                  clone_object(ARM_DIR + "ogre_breastplate")->move(TO);
                  clone_object(ARM_DIR + "ogre_cuirasse")->move(TO);
                  clone_object(ARM_DIR + "ogre_shield")->move(TO);
                  clone_object(WEP_DIR + "ogre_axe")->move(TO);
                      break;
        case 2 :  clone_object(ARM_DIR + "ogre_helmet")->move(TO);
                  clone_object(ARM_DIR + "ogre_breastplate")->move(TO);
                  clone_object(ARM_DIR + "ogre_belt")->move(TO);
                  clone_object(ARM_DIR + "ogre_shield")->move(TO);
                  clone_object(WEP_DIR + "ogre_axe")->move(TO);
                  clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
                  clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
                      break;
    }

    command("wield weapons");
    command("wear all");

}


mixed
benice()
{

    if (TP->query_wiz_level())
    {
        return 0;
    }
    
    if(TP->query_average_stat() <= 90)
    { 
      return 0;
    }

    set_alarm(itof(random(1) + 1), 0.0, "command",
                  "emote growls in a deep guttural tone");
    return 1; 
}
     
  


string adj()
{
    string *adj;
    adj = ({"black-haired","green-skinned","red-eyed",
               "thick-armed","scarred","green-haired", "black-haired",
               "red-haired", "pock-marked", "dark"});
    return adj[random(sizeof(adj))];
}

string adj2()
{
    string *adj2;
    adj2 = ({"angry", "horrible", "nasty",
            "muscular","dirty","wicked",
            "tanned","filthy","huge","massive"});
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
}



void
notify_ob_attacked_me(object friend, object attacker)
   {
   if (query_attack())
      return;
   
   set_alarmv(1.0, -1.0, "help_friend", ({attacker}));
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
   
    if (ob && !query_attack() && present(ob, environment())) {
        command("kill " + lower_case(ob->query_real_name()));
        command("kill " + lower_case(ob->query_real_name()));      
    }
}    


int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt, i;

    me = TO;

    if(random(11) > 8) 
    {
        hurt = F_PENMOD(20,20);

        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " swings at " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " swings at you!\n" +
            "You feel " + how + ".\n");

        if (enemy->query_hp() <= 0)
        {
            command("rsay Dis one dead! Now me eat!");
            enemy->do_die(me);
            command("get all from corpse");
        }
        return 1;
    }

    return 0;
}


