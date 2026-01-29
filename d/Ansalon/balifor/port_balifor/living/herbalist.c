/*
 * Herbalist in Port Balifor
 * Based on Herbalist in Haven that was...
 * Based on Herbalist in Gairent by Varian - August 2015
 *
 */
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/sohm/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>

inherit "/d/Krynn/haven/town/npc/herbalist_base";

inherit M_FILE

#define HERB_SAVE   "/d/Ansalon/balifor/port_balifor/room/herbalist_herbs"

void
introduce_me();
arm_me();

int intro_id;

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("el-Serinda");
   add_name("herbalist");
   add_name("serinda");
   set_race_name("half-elf");
   set_living_name("el-serinda");
   set_title("the Herbalist and Merchant of the Exotic");
   set_adj("lithe");
   add_adj("raven-haired");
   set_long("This lithe half-elf is the local merchant of Port Balifor " +
      "who specialises in the sale of herbs and mageware equipment.\n");
   set_gender(G_FEMALE);
   set_stats(({ 70, 55, 60, 99, 98, 55 }));
   set_introduce(1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_LOOKS,1);

   add_prop(CONT_I_WEIGHT,60000);
   add_prop(CONT_I_HEIGHT,172);

   add_prop(OBJ_M_NO_ATTACK,"She is protected " +
      "by powerful runes of magic, keeping her safe from harm.\n");
   
   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);

   set_alignment(200);
   set_knight_prestige(-50);
   
   set_act_time(10);
   add_act("say If you have an unknown herb, I might be able to identify " +
           "it.");
   add_act("emote searches the shelves for dried herbs.");

      
    set_alignment(350);
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");
    set_max_herbs_kept(250);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);

    set_default_answer(VBFC_ME("default_answer"));

    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
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
    command("say Herbs? Well, I have lots of herbs available right " +
        "here in my store! Would you like to buy some? Or perhaps you " +
        "have some you would like to sell? I might even be able to " +
        "identify a herb for you if you are not sure what you have!"); 
    return "";
}


default_answer()
{
    command("say I don't know much about that!");
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
    command("say Thank you, but I have no use for that.");
    command("say Here, take it back friend.");
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
