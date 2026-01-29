// cook at knights spur
// gives exp for wood quest
// grace

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <macros.h>
#include <money.h>

#define WOODEXP 50

inherit M_FILE

string give_job();
string what_me();
string water_me();

create_krynn_monster()
{
   
   set_name("Mrs. Waybill");
   set_title("Head Cook of the Knights' Spur Kitchen");
   add_name(({"woman", "old woman", "human", "waybill", "cook"}));
   set_adj("jowly");
   set_adj("thick-waisted");
   set_race_name("human");
   set_gender(1);
   set_long(
      "This dumpy old woman looks a bit dangerous waving that kitchen " +
      "utensil in the air.  She has a fierce frown on her round, red face.\n");
   set_stats(({60,60,60,40,40,50}));
   set_gender(1);
   set_alignment(200);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   set_all_hitloc_unarmed(5);
   set_all_attack_unarmed(20, 11);
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_WEP_CLUB, 50);
   set_skill(SS_AWARENESS, 20);
   set_skill(SS_UNARM_COMBAT, 20);
   set_skill(SS_ELEMENT_LIFE, 100);
   set_knight_prestige(-2);
   set_default_answer(VBFC_ME("what_me"));
   
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   add_prop(NPC_I_NO_LOOKS,1);
   
   set_act_time(3);
   add_act(({"say I need more help in this kitchen.",
            "emote grumbles angrily."}));
   add_act(({"say Where is that ninny Willa?",
            "emote mumbles: Prolly flirtin' wi' some flashy Knight."}));
   add_act(({"sigh .", "emote scratches herself absentmindedly."}));
   add_act(({"say To the abyss with 'em all!",
            "say I'll be cookin' no more til I get me some fuel fer the ovens."}));
   add_act(({"say They'll all come a-runnin' t'elp when they find "+
            "there's no supper for 'em.",
            "say Bah!"}));
   
   add_ask("food", "say Willa serves you, not me!", 1);
   add_ask(({"draconian", "prisoner", "draconian prisoner"}),
      "say I dunno much 'bout him save he's ugly as sin and eats "+
      "enuf to feed three Knights!", 1);
   add_ask(({"help", "task", "job", "errand"}), VBFC_ME("give_job"), 1);
   add_ask(({"for water", "about water", "water"}), VBFC_ME("water_me"), 1);
   add_ask(({"about wood","about log", "wood", "log"}), 
      VBFC_ME("give_job"), 1);
   
   seteuid(getuid(TO));
   
   if (IS_CLONE)
      set_alarm(0.0, 0.0,"dress_me");
}

string
what_me()
{
   command("grumble .");
   command("say I'm not paid to answer questions. Ask Willa.");
   return "";
}

void
add_introduced(string who)
{
      command("introduce myself");
      command("say Away with you now! Can't you see I'm busy?");

}

string
give_job()
{
   if(TP->test_bit("Krynn", 3, 3))
      {
      command("smile " + TP->query_name());
      command("say Ye've done enough fer me already. I've got "+
         " nuthin' left fer you ta do.");
      command("say Thank ye fer askin' tho.");
      return "";
   }
   
   else
      {
      command("say I need more wood fer me ovens!");
      command("scratch");
      command("say Thar's wood 'round here somewheres.");
      command("say Bring me a nice big piece an' I might give ye "+
         "sumthin fer yer trouble.");
      return "";
   }
}

void 
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   
   if(from)
      set_alarm(1.0,0.0,"reward_me",ob,from);
}

void
reward_me(object ob, object from)
{
    object cake, pitcher;
   if(ob->id("_quest_wooden_log"))
      {
      if(interactive(from))
         {
         if(from->test_bit("Krynn", 3, 3))
            {
            command("smile .");
            command("say Ye already bought me a piece, " +
               "remember?");
            command("say If ye thought I'd reward ye agin fer doin' "+
               "sumthin' ye already done, yer twice the fool "+
               "ye were thinkin' I wuz.");
            command("say But since ye went and worked up a sweat "+
               "over it, ye might as well have this.");
            clone_object(SOBJ + "pitcher")->move(TO);
            command("give pitcher to " + (from->query_real_name()));
            set_alarm(20.0,0.0,"remove_it",ob);
            return;
         }
         else
            {
            command("say It is about time sum'n brought " +
               "me some wood!");
            command("thank " + from->query_name());
            pitcher=clone_object(SOBJ + "pitcher")->move(TO); 
            cake=clone_object(SOBJ + "cake")->move(TO);
            command("say Here's a little sumthin fer ya.");
            command("give cake to " + (from->query_real_name()));
            command("say And here's sumthin' to warsh it down wi'.");
            command("give pitcher to " + (from->query_real_name()));
	    
	    K_QUEST_LOG("quest", "Spur Wood quest", from, WOODEXP);

            from->add_exp(WOODEXP);
            from->set_bit(3, 3);
            from->catch_msg("You feel a bit more experienced.\n");
            
            set_alarm(20.0,0.0,"remove_it",ob);
            return;
         }
      }
   }
}

string
water_me()    
{
   if(TP->test_bit("Krynn", 3, 3))
      {
      command("frown ");
      command("say Water? Why should I...?");
      command("say Ah! I r'member! Yer that nice person who "+
         "brought me wood");
      command("say Sure, you kin 'ave yerself some water.");
      clone_object(SOBJ + "pitcher")->move(TO);
      command("give pitcher to " + (TP->query_real_name()));
      return"";
   }
   
   else
      {
      command("say I need more wood fer me ovens!");
      command("scratch");
      command("say Thar's wood 'round here somewheres.");
      command("say Bring me a nice big piece an' I might give ye "+
         "sum water fer yer trouble.");
      return"";
   }
}

// I am hoping that this will remove the object from inventory....
void
remove_it(object ob)
{
   //    if (sizeof((all_inventory(TO)->id(ob->query_name())) - ({ 0 })) > 1)
   ob->remove_object();
}

void
dress_me()
{
   object wep, club, dress;
   
   seteuid(getuid(this_object()));
   
   wep = clone_object(SOBJ + "utensil");
   wep->move(this_object(), 1);
   club = clone_object(SOBJ + "utensil2");
   club->move(this_object(), 1);
   dress = clone_object(SOBJ + "dress");
   dress->move(this_object(), 1);
   command("wear all");
   command("wield all");
}
