/*
* Durana Stoneshaft of Thornhold, by Twire June, 2016
*/
inherit "std/monster";

#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

//   Protoypes
int return_yawn(string who);
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("durana");
   add_name(({"stoneshaft", "lady", "woman", "matron", "Durana"}));
   set_living_name("durana");
   set_title("Stoneshaft the High Matron of Thornhold");
   set_race_name("dwarf"); 
   set_size_descs("tall", "lean");
   set_gender(G_FEMALE);
   set_adj(({"tempered","hawk-eyed"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 150);
   set_base_stat(SS_STR, 150);
   set_base_stat(SS_DEX, 150);
   set_base_stat(SS_INT, 150);
   set_base_stat(SS_WIS, 150);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
   set_act_time(25);
   set_chat_time(25);
   add_act("smile relaxed");
   add_act("emote peers down onto the road at an approaching caravan.");
   add_act("emote nods in acknowledgement at a patrolling dwarven guard.");
   add_act("emote scans her environs hawkishly, looking for signs of " +
           "signs of anything untoward.");
   add_act("emote inspects the battlement for signs of damage.");
   add_act ("shout All hail Clan Stoneshaft, Keepers of Thornhold!");
   add_chat("If you have time, I could use your help with a small problem.");
   add_chat("Durlar can restock your provisions, should you have need.");
   add_chat("I know of Thornhold's history, if you'd care to ask.");
   add_chat("Visit our bunkhouse if you need to rest here for the night.");
   add_chat("If you are travelling by steed, you'll find everything your " +
            "your mount requires in the Thornhold stables.");

   add_ask( ({ "problem", "quest", "job", "task" }),
            VBFC_ME("explain_problem"));
   
   add_ask( ({ "durlar", "provisions", "provisioner", "Durlar" }),
            VBFC_ME("explain_durlar"));
    
   add_ask( ({ "stoneshaft", "Stoneshaft", "clan", "dwarves" }),
            VBFC_ME("explain_stoneshaft"));
    
   add_ask( ({ "thornhold", "Thornhold", "history" }), 
            VBFC_ME("explain_thornhold"));
   
   add_ask( ({ "Zhentarim", "zhentarim" }), 
            VBFC_ME("explain_zhentarim"));

   add_ask( ({ "samular", "Samular", "knights" }), 
            VBFC_ME("explain_samular"));
   
   add_ask( ({ "Tyr", "tyr" }), 
            VBFC_ME("explain_tyr"));
   
   add_ask( ({ "merchant", "merchants", "textile", "spice", "arms",
               "tinkerer", "gem", "trader", "dealer", "Carolenne",
               "Wilhem", "Theadric", "Searlyn"}), 
             VBFC_ME("explain_merchants"));
   
   add_ask( ({ "tin", "snuff", "box" }), VBFC_ME("explain_tin"));
   add_ask( ({ "something", "glint" }), VBFC_ME("explain_glint"));
}


init_living() {
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}


explain_problem()
{
    string *incomp = ({""});
    string thischoice = "";
    object qp = this_player();
    
    if (interactive(qp))
    {
        if (QUEST_MASTER->check_done(qp))
        {
            command("say Thank you again for helping our visiting " +
                    "merchants! The caravans must roll smoothly " +
                    "if Thornhold is to remain propserous!");
        }
        else if (QUEST_MASTER->check_full(qp))
        {
            command("say So it seems you've helped every merchant on the " +
                    "schedule! You're a true friend and ally of Clan " + 
                    "Stoneshaft!");
            return("As Durana offers you a broad smile, you suddenly feel " +
                   "more experienced!");
            QUEST_MASTER->award_full(qp);
        }
        else if (QUEST_MASTER->check_none(qp))
        {
            command("say Our visiting merchants are usually troubled by " +
                    "one thing or another. If you could assist them, I " +
                    "appreciate it. Visiting merchants are the " +
                    "lifeblood of Thornhold.");
        }
        else
        {
            if (!QUEST_MASTER->check_thimble(qp) )
                incomp = incomp + ({"thimble"});
            if (!QUEST_MASTER->check_ingot(qp) )
                incomp = incomp + ({"ingot"});
            if (!QUEST_MASTER->check_gear(qp) )
                incomp = incomp + ({"gear"});
            if (!QUEST_MASTER->check_loupe(qp) )
                incomp = incomp + ({"loupe"});
            if (!QUEST_MASTER->check_spice(qp) )
                incomp = incomp + ({"spice"});

            //    thischoice = one_of_list(  ({"thimble", "spice", "ingot", ""}) );
            thischoice = one_of_list(incomp);
            switch(thischoice)
            {
                case "thimble":
                    command("say Carolenne, the cloth merchant that " +
                            "frequents Thornhold, has been complaining " +
                            "about some kind of pest in Thornhold. " +
                            "Maybe you can look into that?");
                    break;
                case "ingot":
                    command("say Wilhem always seems to be searching " +
                            "for materials to fulfill his weapon orders. " +
                            "Maybe you can see if he needs anything?");
                    break;
                case "gear":
                    command("say Theadric is a mess of a tinkerer " +
                            "and is always losing this or that. Check " +
                            "and see if he needs any help.");
                    break;
                case "loupe":
                    command("say I heard Brigid bragging that she won a " +
                            "prize gem in a match of noughts and crosses. " +
                            "You might want to see if the gem merchant " + 
                            "lost anything substantial to that wily girl.");
                    break;
                case "spice":
                    command("say I haven't spoken to Searlyn, the spice " +
                            "merchant in a while. Can you check in with " + 
                            "her to make sure business is running smoothly?");
                    break;
                default:
                    command("say It seems every merchant that visits " +
                            "Thornhold has a problem sooner or later. " +
                            "Always ask them if they need any tasks done!");
                    break;
            }
        }
    }
}

explain_merchants()
{
    command("say We have a new merchant come through every other day " +
            "to do business in Thornhold. You can check the schedule " +
            "in the north courtyard to see who's coming next." );
}

explain_durlar()
{
    command("say Durlar is a competent provisoner and should be able to " +
            "provide you with any basic adventuring supply you might " +
            "require.");
}
explain_stoneshaft()
{
    command("say Our clan are the designated caretakers of Thornhold. " +
            "We are a proud and noble clan, specializing in trade.");
}

explain_thornhold()
{
    command("say Originally, Thornhold was the fortress of Brynyundar " +
            "Margaster, a local warlord, until he was overthrown by " +
            "Samular Carradoon shortly after the end of the Second " +
            "Troll War. ");
    command("say Samular had a deed of ownership written so that it " +
            "would belong to his family but it actually functioned as " +
            "a chapterhouse for the Knights of Samular.");  
    command("say In 1368 DR, the fortress was briefly seized by the " +
            "Zhentarim after Samular's heir, Hronrulf Caradoon died."); 
    command("say Fortunately, Hronrulf's daughter, Bronwyn, recaptured " +
            "Thornhold, and entrusted it to our Clan's capable hands. " +
            "It's served as a caravan stop ever since.");
}

explain_zhentarim()
{
    command("say The Zhentarim are a mercenary company. They are a " +
            "shadow of their former glory, and trouble the Sword Coast " +
            "little these days.");
}

explain_samular()
{
    command("say The Knights of Samular are a holy order of paladins " +
            "in service to Tyr.");
    command("say By the time Bronwyn recaptured Thornhold, the order " +
            "established new headquarters at a placed called Summit Hall, "  +
            "a fortified abbey in the Slumber Hills.");
}

explain_tyr()
{
    command("say Yegads, you don't even know of the Maimed God? You best " +
            "visit the temples of Waterdeep if you care for theology " +
            "lessons. I've a fortress to run!");
}

explain_tin()
{
    command("say Oh, you mean my tobacco box? Durlar gave that to me and " +
            "it was perfect for my pipe tobacco! It belongs to Saerlyn?");
    command("say Unfortunately, I lost it! I'm afraid I've a bad habit of " +
            "taking it out of my pocket during my pipe break in the west " +
            "tower. Maybe if you look there you'll find it?");
}

explain_glint()
{
    command("say Interesting... my tobacco must have fallen from the tower " +
            "to the cliff below. I have no idea how to get down there. If " +
            "you find a way, please retrieve the spice tin and return it " +
            "it to Saerlyn.");    
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Welcome to Thornhold " + ob->query_nonmet_name() + "!");
}

my_long() {
   if (notmet_me(this_player())) this_player()->add_introduced("durana");
   return "Durana Stoneshaft is the High Matron of Thornhold. " +
      "She is older and more distinguished-looking than most of the " +
      "dwarves of Thornhold, suggesting that she may be of noble " +
      "birth. She is dressed in full armor and a tunic embroidered " +
      "with a faceted gem, the symbol of Clan Stoneshaft.\n";
}

int
return_smile(string who) {
   object ob;
   
   ob = present(who, environment());
   if (!ob) return 0;
   switch (random(4)) {
      case 0: command("smile"); return 1;
      case 1: command("smile " + who); return 1;
      case 2: if (notmet_me(ob)) {
         command("introduce myself to " + who);
         return 1; 
          }
      break;
   }
   return 0;
}

int
return_yawn(string who)
{
   if (!who) return 0;
   who = lower_case(who);
   if (random(3)) return 0;
   command("say You may wish to retire to the bunkhouse if you need sleep.");
   return 1;
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
      case "yawn":
      set_alarm(3.0,0.0,&return_yawn(name));
      break;
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}
