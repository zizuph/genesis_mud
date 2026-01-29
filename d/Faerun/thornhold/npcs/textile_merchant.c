/*
* Carolenne Ostever Textile Merchant by Twire June, 2016
*/
inherit "std/monster";

#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

//   Protoypes
int return_smile(string who);
void return_introduce();
void greet(object ob);

public void
init_size()
{
    set_size_descs("tall", "lean");
}

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("carolenne");
   add_name(({"ostever", "textile", "seamstress", "Carolenne", "merchant"}));
   set_living_name("carolenne");
   set_title("Ostever of Longsaddle, Textile Merchant");
   set_race_name("human"); 
   set_gender(G_FEMALE);
   set_adj(({"slender","dark-haired"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 80);
   set_base_stat(SS_STR, 80);
   set_base_stat(SS_DEX, 100);
   set_base_stat(SS_INT, 80);
   set_base_stat(SS_WIS, 90);
   
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,80);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
   remove_prop(LIVE_M_NO_ACCEPT_GIVE);

   set_act_time(40);
   set_chat_time(40);
   add_act("smile kindly");
   add_act("emote carefully folds a length of fabric.");
   add_act("emote swiftly counts her bolts.");
   add_act("emote pulls a bolt of burlap into the provisons shop.");
   add_act("emote retreats a moment into the provisions shop to resupply.");
   add_chat("A fine dressmaker in Waterdeep oft purchases my best silks.");
   add_chat("In addition to wool and fabric, I also bring mutton to the " +
            "taverns of the region, including the Thornhold Alehouse.");
   add_chat("If you've ever purchased clothing anywhere on the Sword Coast " +
            "there's a good chance you've encountered my textiles.");
   add_chat("Kala Stoneshaft always makes sure I have the most comfortable " +
            "bedding when I stop at Thornhold for the night.");
   add_chat("If you're ever in Longsaddle, be sure to visit the Ivy " +
            "Mansion if you're looking for an interesting time!"); 
   set_alarm(0.0, 0.0, init_size);
   
   add_ask( ({ "problem", "quest", "job", "task", "missing", "item" }), VBFC_ME("explain_problem"));
   add_ask( ({ "magpie", "nest" }), VBFC_ME("explain_magpie"));
   add_ask( ({ "thimble", "thimbles" }), VBFC_ME("explain_thimble"));
   add_ask( ({ "ivy", "mansion" }), VBFC_ME("explain_ivymansion"));
}

init_living() 
{
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;

    if (obj->id("_thq_thimble"))
    {
        if(!QUEST_MASTER->check_thimble(from))
        {
            command("say Oh! You found my thimble! Thank you so much!");
            command("emote tucks the thimble into one of her pockets.");
            command("say Keep an eye out for those magpies! Winged thieves!");
            QUEST_MASTER->award_thimble(from);
        }
        else
        {
            command("say Another thimble! Thanks!");
        }
        obj->remove_object();
    }
    else
    {
        command("say Hmm Not sure what I'd do with that.");
        obj->move(from);
    }
}

explain_problem()
{
   if (interactive(this_player()))
   {
       if (QUEST_MASTER->check_thimble(this_player()))
       {
             command("say Thank you for helping me earlier. I am in your debt!");
       }
       else
       {
            command("say You'll never believe this, but as I arrived in Thornhold, " +
                    "a magpie swept out of nowhere and stole my best thimble!");
       }
   }
}

explain_magpie()
{
    command("say Those little black and white birds are a nuisance! They " +
            "take shiny objects and hide them away in their nests.");
}

explain_thimble()
{
    command("say My thimbles prevent needle pricks while sewing tears in " +
            "my stock. My favorite one fits my thumb perfectly!");
}

explain_ivymansion()
{
    command("say Ivy Mansion is inhabited by a family of eccentric " +
            "wizards. Just pay them a visit if your path ever brings " +
            "you through Longsaddle.");
    command("emote winks meaningfully.");
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say It is so very nice to meet you " + 
   ob->query_nonmet_name() + "!");
}

my_long() 
{
   if (notmet_me(this_player())) this_player()->add_introduced("carolenne");
   return "This is a slender, dark-haired female human. \n" +
          "She is a textile merchant. \n";
          "She is wearing a green wool travelling dress. \n";
}

int
return_smile(string who)
{
	object ob;
   
	ob = present(who, environment());
   
	if (!ob) 
		return 0;
	   
	switch (random(4))
	{
	case 0: 
		command("smile"); 
		return 1;
	case 1: 
		command("smile " + who); 
		return 1;
	case 2: 
		if (notmet_me(ob)) 
		{
			command("introduce myself to " + who);
			return 1; 
		}
		break;
	default:
		break;
	}
	
	return 0;
}

int
add_introduced(string who)
{
   object ob;
   
   if (!who) return 0;
   who = lower_case(who);
   ob = present(who, environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), ob)) return 0;
   if (!notmet_me(ob)) return 0;
   if (!random(20)) return 0;
   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}

void
return_introduce()
{
   command("introduce myself");
}

void
emote_hook(string emote,object actor,string averb = 0)
{
   string name = actor->query_real_name();
   
   switch(emote)
   {
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}
