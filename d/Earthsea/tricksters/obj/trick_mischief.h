/*
 * Creator: Ged
 * Date: 01.07.01
 * File: /w/ged/tricksters/trick_emotions.h
 * Comments: This is tricksters soul mischief header file
 * Revision history:
 * 
 */

#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

mapping query_trick_mischief()
{
 return
   ([
     "itchpowder":"itchpowder",
     "laughgas":"laughgas",
     "smokebomb":"smokebomb",
     "sneezepowder":"sneezepowder",
     "stinksplash":"stinksplash"
   ]);
}

void add_mischief_to_armour(object arm,string kind);

// ========================= MISCHIEF ==============================


// ======================== SNEEZEPOWDER ===========================

int sneezepowder(string who)
{
 object *list,sneeze_obj,*arm,stick;
 string desc;

 setuid();
 seteuid(getuid());

 NF("But you don't have the stick!\nYou'd better go and recover it!!\n");
 stick=present(STICK_DESC,TP);
 if(!stick) return 0;

 NF("Who do you wish to make sneeze?\n");
 if(!who) return 0;

 NF("You have no sneezepowder to throw.\n");
 if(!(stick->get_contents())[0]) return 0;

 arm=FIND_STR_IN_OBJECT(who,TP);
 if(sizeof(arm)>0)
  {
   NF("Silly, you can only make one sneezing at a time!\n");
   if(sizeof(arm)>1) return 0;

   NF("You must place the sneezing powder on armours!\n");
   if(function_exists("create_object",arm[0]) != "/std/armour")
     return 0;

   NF("Puting sneezing powder in armour that doesn't go on one's head "+
      "seems rather pointless.\n");
   if(arm[0]->query_at()!=A_HEAD) return 0;   

   NF("Uhm... remove it first?\n");
   if(arm[0]->query_worn()) return 0;

   desc=arm[0]->short();
   NF("There seems to be a trick already being played on "+desc+".\n");
   if(arm[0]->query_prop_setting("_trick_i_mischief")) return 0;

   me("You lace "+desc+" with sneezing powder.");
   all(" does something to "+desc+"!");

   add_mischief_to_armour(arm[0],"sneezing powder");
   stick->used_sneeze();
   return 1;
  }

 list=parse_this(who,"%l");
 NF("There is no "+who+" here for you to throw that at!\n");
 if(!sizeof(list)) return 0;

 NF("Silly, you can only make one sneezing at a time!\n");
 if(sizeof(list)>1) return 0;

 actor("You tap your stick against your hand, emptying sneezing "+
       "powder into your hand...   As soon as you figure you have "+
       "enough powder, you throw it in the face of",list,".");
 target(" starts to tap "+POS(TP)+" large stick against "+POS(TP)+
        " hand. Then all of a sudden "+PRO(TP)+" jerks "+POS(TP)+
        " hand and throws some strange powder in your face!!",list);
 all2act(" starts to tap "+POS(TP)+" large stick against "+POS(TP)+
         " hand. Then all of a sudden "+PRO(TP)+" jerks "+POS(TP)+
         " hand and throws some strange powder in the face of",list,"!!");

 sneeze_obj=clone_object(TRICKSTERS+"obj/sneezepowder");
 sneeze_obj->move(list[0]);
 sneeze_obj->set_length(15);
 sneeze_obj->start();

 stick->used_sneeze();
 return 1;
}

// ======================== ITCHPOWDER ===========================

int itchpowder(string who)
{
 object *list,*arm,itch_obj,stick;
 string desc;

 setuid();
 seteuid(getuid());

 NF("But you don't have the stick!\nYou'd better go and recover it!!\n");
 stick=present(STICK_DESC,TP);
 if(!stick) return 0;

 NF("Who are you trying to make itchy?\n");
 if(!who) return 0;

 NF("You don't have any itching powder in your stick to use!\n"); 
 if(!(stick->get_contents())[1]) return 0;

 arm=FIND_STR_IN_OBJECT(who,TP);
 if(sizeof(arm)>0)
  {
   NF("Silly, you can only give make one thing itchy at a time!\n");
   if(sizeof(arm)>1) return 0;

   NF("You must place the itching powder on armours!\n");
   if(function_exists("create_object",arm[0]) != "/std/armour")
     return 0;

   NF("Uhm... remove it first?\n");
   if(arm[0]->query_worn()) return 0;

   desc=arm[0]->short();
   NF("There seems to be a trick already being played on "+desc+".\n");
   if(arm[0]->query_prop_setting("_trick_i_mischief")) return 0;

   me("You lace "+desc+" with itching powder.");
   all(" does something to "+desc+"!");

   add_mischief_to_armour(arm[0],"itching powder");
   stick->used_itch();
   return 1;
  }

 list=parse_this(who,"%l");
 NF("There is no "+who+" here to make all itchy!\n");
 if(!sizeof(list)) return 0;

 NF("Silly, you can only give make one thing itchy at a time!\n");
 if(sizeof(list)>1) return 0;

 actor("You bonk",list," on the head with your large stick in such a "+
       "way that it releases some itching powder on "+POS(list[0])+
       " scalp.");
 target(" bonks you on the head with "+POS(TP)+" large stick!\n"+
        "You feel a slight tingle as the large stick hits your head as "+
        "if something was left there.",list);

 all2act(" bonks",list," on the head with "+POS(TP)+" large stick!");

 itch_obj=clone_object(TRICKSTERS+"obj/itchpowder");
 itch_obj->move(list[0]);
 itch_obj->set_length(15);
 itch_obj->start();

 stick->used_itch();
 return 1;
}

// ============================= SMOKEBOMB =========================

void bomb_explode()
{
 object bomb_obj;

 setuid();
 seteuid(getuid());

 bomb_obj=clone_object(TRICKSTERS+"obj/smokebomb");
 bomb_obj->move(ENV(TP));
 bomb_obj->explode();
}

int smokebomb(string stam)
{
 object stick;

 NF("But you don't have the stick!\nYou'd better go and recover it!!\n");
 stick=present(STICK_DESC,TP);
 if(!stick) return 0;

 NF("You have no smoke bombs to toss!\n");
 if(!(stick->get_contents())[2]) return 0;

 me("You fiddle around with your stick until you pry a smoke bomb from "+
    "within a hole of your stick.\n"+
    "You promptly throw the smoke bomb to the ground so you can make a "+
    "hasty escape.");
 all(" starts fiddling with "+POS(TP)+" large stick and produces a "+
     "small glass bulb, which "+PRO(TP)+" then quickly throws to the "+
     "ground, where it breaks on impact!");

 set_alarm(1.0,0.0,&bomb_explode());
 stick->used_smoke();

 return 1;
}

// ========================== STINKSPLASH =========================

int stinksplash(string who)
{
 object *list,stinky_obj,*arm,stick;
 string desc;

 NF("But you don't have the stick!\nYou'd better go and recover it!!\n");
 stick=present(STICK_DESC,TP);
 if(!stick) return 0;

 setuid();
 seteuid(getuid());

 NF("Make who all stinky and smelly?\n");
 if(!who) return 0; 

 NF("Curse the luck!  You are all out of stinky liquid!\n");
 if(!(stick->get_contents())[3]) return 0;

 arm=FIND_STR_IN_OBJECT(who,TP);
 if(sizeof(arm)>0)
  {
   NF("Make them all stinky? Nah , that would be too much stench!\n");
   if(sizeof(arm)>1) return 0;

   NF("You must spread the smelly liquid on armours!\n");
   if(function_exists("create_object",arm[0]) != "/std/armour")
     return 0;

   NF("Uhm... remove it first?\n");
   if(arm[0]->query_worn()) return 0;

   desc=arm[0]->short();
   NF("There seems to be a trick already being played on "+desc+".\n");
   if(arm[0]->query_prop_setting("_trick_i_mischief")) return 0;

   me("You lace "+desc+" with stinking liquid.");
   all(" does something to "+desc+"!");

   add_mischief_to_armour(arm[0],"smelly liquid");
   stick->used_stink();
   return 1;
  }

 list=parse_this(who,"%l");
 NF("There is no "+who+" here for you to make all stinky!\n");
 if(!sizeof(list)) return 0;
 
 NF("Make them all stinky? Nah , that would be too much stench!\n");
 if(sizeof(list)>1) return 0;

 actor("You remove a cork from your stick, revealing a small hole "+
       "containing a foul-smelling liquid.\n"+
       "You then swing your stick at",list,", splashing "+POS(list[0])+
       " with the stinking liquid.");
 target(" removes something from "+POS(TP)+" large stick, then swings "+
        "the stick towards you!\n"+
        "A foul liquid is spewed forth from the stick and you are "+
        "covered from head to toe with it!",list);
 all2act(" removes something from "+POS(TP)+" large stick, then swings "+
         "the stick towards",list," which releases a strange liquid "+
         "which covers "+POS(list[0])+" from head to toe!");

 stinky_obj=clone_object(TRICKSTERS+"obj/stinksplash");
 stinky_obj->move(list[0]);
 stinky_obj->set_length(15);
 stinky_obj->start();

 stick->used_stink();
 return 1;
}

// ========================== LAUGHGAS ============================

int laughgas(string stam)
{
 object vial,stick;

 setuid();
 seteuid(getuid());

 NF("But you don't have the stick!\nYou'd better go and recover it!!\n");
 stick=present(STICK_DESC,TP);
 if(!stick) return 0;

 NF("You have no laughing gas equiped in your stick!\n");
 if(!(stick->get_contents())[4]) return 0;

 me("You fiddle around with your stick until you pry a glass vial "+
    "containing laughing gas from within a hole in your stick.\n"+
    "You toss it towards the ground, and you better run out of this "+
    "room before you are effected by the gas!");
 all(" starts tinkering with "+POS(TP)+" large stick and produces a "+
     "small glass vial from it. "+C(PRO(TP))+" grins mischievously as "+
     PRO(TP)+" throws it to the ground.");
 
 vial=clone_object(TRICKSTERS+"obj/vial");
 vial->move(ENV(TP));
 vial->arm();

 stick->used_laugh();
 return 1;
}

void add_mischief_to_armour(object arm,string kind)
{
 object shad;
 int res;

 shad=clone_object(TRICKSTERS+"obj/mis_shadow");
 res=shad->shadow_me(arm);
 arm->add_prop("_trick_i_old_search",
   arm->query_prop_setting(OBJ_S_SEARCH_FUN));
 arm->add_prop(OBJ_S_SEARCH_FUN,"find_mischief");
 arm->add_prop("_trick_i_mischief",kind);
 arm->add_prop("_trick_i_mischief_owner",TP);
 arm->set_long(arm->query_long()+INFESTED_ARM_DESC);
 if(!arm->query_wf()) arm->set_wf(arm);

 if(!res) find_player("ged")->catch_msg("Armour shadow failed.\n");
}

