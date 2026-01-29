/*
 * Herbalist in Haven
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

inherit "/d/Shire/lib/herbalist.c";

inherit M_FILE

#define HERB_SAVE   "/d/Krynn/haven/town/npc/herbalist_herbs.o"

void
introduce_me();
arm_me();

int intro_id;

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("lemuel");
   add_name("herbalist");
   set_race_name("human");
   set_living_name("lemuel");
   set_title("the Hedge Wizard and Herbalist");
   set_adj("short");
   add_adj("balding");
   set_long("This short balding human is the owner of the Mageware shop " +
      "in Haven. Clad in faded red robes covered with dirt at the knees, it " +
      "seems he is accostomed to spending a lot of his time in his garden " +
      "tending his herbs.\n");
   set_gender(G_MALE);
   set_stats(({ 70, 55, 60, 99, 98, 55 }));
   set_introduce(1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_LOOKS,1);

   add_prop(CONT_I_WEIGHT,60000);
   add_prop(CONT_I_HEIGHT,172);
   
   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);

   set_alignment(200);
   set_knight_prestige(-50);
   
   set_act_time(10);
   add_act("say Par-Salian never allowed me to sit the Test. He said it " +
       "would be tantamount to murder.");
   add_act("say My father was an archmage, a war wizard. When the Conclave " +
       "refused to let me sit the Test, he left home and never returned.");
   add_act("say There isn't much need for a Mageware shop in Haven. Would " +
       "have been better to set up in Palanthas, but I would really miss " +
       "my herb garden.");
   add_act("say If you have an unknown herb, I might be able to identify " +
           "it.");
   add_act("say I sell items of use to those who dabble in spellcraft. " +
           "I even have a few spell scrolls I can sell for the right price.");
   add_act("emote searches the shelves for dried herbs.");
   add_act("emote takes an herb to his nose and smells it.");
      
    set_alignment(350);
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");
    set_max_herbs_kept(250);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herb lore"}), VBFC_ME("ask_lore"));
}



//equip function

arm_me()
{
    clone_object(KRARMOUR + "herb_gloves")->move(TO);
    command("wear all");
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

void
enter_inv(object herb, object from)
{
    ::enter_inv(herb, from);
    init_herbalist_identify(herb,from);
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

string
ask_herbs()
{
    command("say Herbs? Well, I have lots of herbs available right " +
        "here in my store! Would you like to buy some? Or perhaps you " +
        "have some you would like to sell? I might even be able to " +
        "identify a herb for you if you are not sure what you have!"); 
    return "";
}

string
ask_lore()
{
    command("say Well, I am very knowledgable about herbs if I do say " +
        "so myself, but there is still so much to learn! I once met " +
        "a young aspirant named Raistlin who was quite knowledgable, " +
        "even the White Mage Antimodes passes through here occasionally " +
        "and we shared what we knew of herblore.");
    return "";
}

default_answer()
{
    command("say I don't know much about that!");
    return "";
} 