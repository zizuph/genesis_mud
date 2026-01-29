/*
 * This file is /d/Gondor/ithilien/npc/haradstd.c
 *
 * Last mod: Olorin, August 1994
 */
inherit "/std/monster";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/evilkill.h"

string  lookadj();
void    help_friend(object ob);

void
create_monster()
{
   set_name("haradrim warrior");
   add_name(({"warrior","southron","haradrim","man"}));
   set_pname("warriors");
   add_pname("men");
   add_pname("southrons");
   add_pname("haradrim");
   set_short("haradrim warrior");
   set_pshort("haradrim warriors");
   set_race_name("human"); 
   set_adj("dark-skinned");
   set_adj(lookadj());
   set_long(BSN("This is a tall and dark-skinned haradrim warrior, clad in a " +
         "scarlet robe and with black plaits of hair braided with gold."));
   set_alignment(-200-random(200));

   default_config_npc(63+random(10));    
   set_base_stat(SS_CON, 75+random(10));
   set_base_stat(SS_DIS, 85+random(10));
   set_skill(SS_WEP_SWORD,   70+random(10));
   set_skill(SS_PARRY,        85+random(5));
   set_skill(SS_DEFENCE,      85+random(5));
   set_skill(SS_AWARENESS,    25+random(5));
   set_skill(SS_UNARM_COMBAT, 45+random(5));
   add_prop(CONT_I_HEIGHT,   180+random(20));
   add_prop(CONT_I_WEIGHT, 75000+random(10000));
   add_prop(CONT_I_VOLUME, 70000+random(20000));    
   add_prop(LIVE_I_NEVERKNOWN, 1);
   
   set_chat_time(10+random(10));
   add_chat("Where are these ridiculous dunedain? Did they all flee?");
   add_chat("Why don't we attack Minas Tirith now? I hate this waiting!");
   add_chat("When does the dance start? I don't wanna miss the fun!");
   add_chat("Think of all the girls waiting in Minas Tirith just for me!");
   
   set_cchat_time(5+random(5));
   add_cchat("Take this, you worm!");
   add_cchat("Stand still and fight, you coward!"); 
   add_cchat("Let me kill you quickly, it won't hurt!");
   
   set_act_time(15+random(15));
   add_act("burp");
   add_act("hiss");
   add_act("grin");
   
   set_cact_time(5+random(5));
   add_cact("scream"); 
   add_cact("cry"); 
   add_cact("shout Die, you stinking spy!");
   
}

void
get_money()
{
   MONEY_MAKE_CC(10 + random(5))->move(TO);
   MONEY_MAKE_SC(     random(5))->move(TO);
}

void
arm_me()
{
   FIX_EUID
   
   clone_object(WEP_DIR + "haradscim")->move(TO);
   command("wield scimitar");
   
   clone_object(ARM_DIR + "haradcloak")->move(TO);
   command("wear cloak");
   
   clone_object(ARM_DIR + "haradshield")->move(TO);
   command("wear shield");
   
   clone_object(ARM_DIR + "corslet")->move(TO);
   command("wear corslet");
   
   get_money();
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
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

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
   if (query_attack())
      return;
   
   if (random(10))
      set_alarm(rnd()*5.0, 0.0, &help_friend(attacker));
}

int query_show_list(object x) { return !(x->query_no_show()); }

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
   object *loot_list;

   if (ob && !query_attack() && present(ob, ENV(TO)))
   {
      loot_list = all_inventory(ob);
      loot_list = filter(loot_list,"query_show_list", TO);
      command("say I'll kill it, I want to have its " 
         + (string)loot_list[random(sizeof(loot_list))]->short() + "!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}

string
lookadj() 
{
   string *lookadjs;
   lookadjs = ({"grim", "tall", "angry", "beastly", "mean", "dirty", "foul", 
         "brutal", "battered", "sinister","wicked","savage", "ugly"});
   return lookadjs[random(sizeof(lookadjs))];
}

int query_knight_prestige() { return 130; }
