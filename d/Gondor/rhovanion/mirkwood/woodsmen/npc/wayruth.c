/*
 * Herbalist in Gairent
 * Varian - August 2015
 * Code borrowed from Daisy in the Shire
 * /d/Shire/eastroad/npc/herbalist.c
 */

#pragma save_binary

#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

inherit "/d/Shire/lib/herbalist.c";
inherit "/std/monster.c";

#define HERB_SAVE   WOODSMEN_DIR + "herb_save.o"

void

introduce_me();
arm_me();

int intro_id;

void
create_monster()
{
   
    set_name("wayruth");
    add_adj(({"slender","brown-haired"}));
    set_long("This appears to be the local herbalist in Gairent. She is " +
        "rather tall for a woman yet still quite slender and her long, " +
        "brown hair seems to be sprinkled with a little grey.\n");
    set_race_name("human");
    set_gender(1);
   
    add_act("smile all");
    add_act("emote carefully examines a small, green leaf.");
    add_act("emote gently stores a handful of yellow berries in a jar.");
    add_act("emote expertly ties some herbs on a string to be properly " +
        "dried and preserved.");
    add_act("greet all");
    add_act("say Welcome traveller! Do you know what herbs you are " +
        "looking for?");

    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));

    set_act_time(10);
   
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_HERBALISM, 68);

    set_stats(({ 120, 140, 120, 110, 110, 130}), 10);
   
    set_alignment(350);
   
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");

    set_max_herbs_kept(250);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);
}

arm_me()
{
   object dress;

   FIXEUID;

   dress = clone_object(WOODSMEN_DIR + "arm/wayruth_dress.c");

   dress->move(TO);   

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
    str +="-Lord Jaypeg-\n";
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
        "a nice young hobbit named Daisy who was quite knowledgable, and " +
        "she introduced me to an old man named Lothmir who taught me " +
        "even more! The day you stop learning is the day you stop living! " +
        "That's what I say.");
    return "";
}

default_answer()
{
    command("say I don't know much about that!");
    return "";
}