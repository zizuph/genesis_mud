/*
 * Herbalist in Wayreth
 * Based on Herbalist in Gairent by Varian - August 2015
 *
 */
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>

inherit "/d/Krynn/haven/town/npc/herbalist_base";

inherit M_FILE

#define HERB_SAVE   "/d/Krynn/wayreth/npc/herbalist_herbs"

void
introduce_me();
arm_me();

int intro_id;

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("lawsuel");
   add_name("herbalist");
   set_race_name("gnome");
   set_living_name("lawsuel");
   set_title("Lesser White Wizard and Tower Herbalist");
   set_adj("white");
   add_adj("robed");
   set_long("This white robed gnome is the herbalist of the Tower " +
      "of Wayreth.\n");
   set_gender(G_MALE);
   set_stats(({ 70, 55, 60, 99, 98, 55 }));
   set_introduce(1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_LOOKS,1);

   add_prop(CONT_I_WEIGHT,60000);
   add_prop(CONT_I_HEIGHT,172);

   add_prop(OBJ_M_NO_ATTACK,"He is protected " +
      "by powerful runes of magic, keeping him safe from harm.\n");
   
   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);

   set_alignment(200);
   set_knight_prestige(-50);
   
   set_act_time(10);
   add_act("say IfYouHaveAnUnknownHerb,IMightBeAbleToIdentifyIt.");
   add_act("emote searches the shelves for dried herbs.");
   add_act("emote takes an herb to his nose and smells it.");
      
    set_alignment(350);
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");
    set_max_herbs_kept(10000);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));

    seteuid(getuid());
}



//equip function

arm_me()
{
  //anything added here you'll need to exclude in the enter_env function
}

void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("bow polite");
   command("introduce me"); 
   set_alarm(15.0, 0.0, allow_introductions);
}

void
init_living()
{
    init_herbalist();
    ::init_living();
}

string
wizinfo()
{
    string str;
    str = "This Herbalist stores up to "+query_herbs_max_kept()+
    " herbs of same type at one time.\n\n";
    if (!query_herb_list_size())
    {
    str += "The herbalist has no herbs for sale now.\n";
    return str;
    }
    str += "The herbalist has these herbs for sale:\n";
    str += query_herb_list();
    str +="-Lord Arman-\n";
    return str;
}


// ask responses

string
ask_herbs()
{
    command("say Herbs?Well,IHaveLotsOfHerbsAvailableRight" +
        "HereInTheTower!WouldYouLikeToBuySome?OrPerhapsYou" +
        "HaveSomeYouWouldLikeToSell?IMightEvenBeAbleTo" +
        "IdentifyAHerbForYouIfYouAreNotSureWhatYouHave!"); 
    return "";
}


default_answer()
{
    command("say IDon'tKnowMuchAboutThat!");
    return "";
} 

void
give_it_back(object ob, object from)
{
    string what,
    who;
    what = L(ob->query_short());
    who = from->query_real_name();
    command("emote looks closely at the " + what + ".");
    command("say ThankYou,ButIHaveNoUseForThat.");

    command("give " + what + " to " + who);
    command("drop " +what);
}

void
herbalist_not_herb_hook(object ob, object player)
{
    command("ponder");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    init_herbalist_identify(ob,from);

    if(ob->id("herb"))
    {
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}
