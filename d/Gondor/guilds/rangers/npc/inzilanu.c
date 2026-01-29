/*
 * Herbalist in Gairent
 * Varian - August 2015
 * Code borrowed from Daisy in the Shire
 * /d/Shire/eastroad/npc/herbalist.c
 */

#pragma save_binary

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

inherit "/d/Shire/lib/herbalist.c";
inherit RANGERS_NPC + "random_npc_ranger.c";
inherit "/std/monster.c";

#define HERB_SAVE   NPC_DIR + "inzilanu_herbs.o"

void

introduce_me();
arm_me();

int intro_id;

void
create_monster()
{
   
    set_name("inzilani");
    add_adj(({"stoic","grey-eyed"}));
    set_title("the Herbalist of the North Company");
    set_long("This ranger has the rich aroma of herbs wafting around " +
        "her. You suspect that perhaps she might have some herbs to " +
        "sell, or even that she might be willing to purchase any " +
        "extra herbs you might have.\n");
    set_race_name("human");
    set_gender(1);
   
    add_act("smile all");
    add_act("emote carefully tightens the lid on a small wooden canister.");
    add_act("emote places some dark red berries in a tall glass jar.");
    add_act("emote arranges some of the containers on the wooden table in " +
        "an effort to make things more organized.");
    add_act("greet all");
    add_act("rhail");
    add_act("emote carefully examines a grey ceramic pot.");
    add_act("say Hello there! Do you have any herbs you might be interested " +
        "in selling?");

    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));

    set_act_time(10);
   
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_HERBALISM, 68);

    set_stats(({ 120, 140, 120, 110, 110, 130}), 10);
   
    set_alignment(950);
   
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");

    set_max_herbs_kept(750);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);
}

arm_me()
{
   object cloak;
   object pin;

   FIXEUID;

   cloak = clone_object(RANGERS_OBJ + "grey_cloak");
   pin = clone_object(RANGERS_OBJ + "ron_brooch");

   cloak->move(TO); 
   pin->move(TO);  

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
    command("say Yes, I do indeed sell my herbs here! In truth, I am also " +
        "willing to purchase any extra herbs you do not currently have a " +
        "use for.");
    return "";
}
string
ask_lore()
{
    command("say I have studied herb lore for many years now, having " +
        "first begun my training under master Lothmir.");
    return "";
}

default_answer()
{
    command("say I don't know much about that!");
    return "";
}