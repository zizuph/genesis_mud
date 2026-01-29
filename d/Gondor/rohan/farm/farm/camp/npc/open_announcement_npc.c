/*
 * A one to two armageddon NPC used to announce the opening
 * of the Dunlending area.
 * --Raymundo
 * Summer 2021
  */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <living_desc.h>

#include "/d/Gondor/rohan/farm/farm/camp/defs.h"
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/bits.h"

#define ADJ1 ({ "disheveled", "injured", "ragged", "unkempt", "beaten", "bruised"})
#define ADJ2 ("rohirrim")


string adj1;
string adj2;


void
create_monster() 
{
    adj1 = one_of_list(ADJ1);
    adj2 = ADJ2;
    set_name(({"farmer", adj2}));
    set_gender(random(2));
    set_race_name("human");
    set_adj(({adj1, adj2}));
    set_short(adj1 + " " + adj2 + " farmer");
    set_long("This farmer looks very badly beaten. You can tell by "
    + "the dirt under " + HIS_HER(TO) + " finger nails that you're looking "
    + "at a rohirrim farmer.\n");
    default_config_npc(52);
    set_base_stat(SS_CON,95);
    set_base_stat(SS_STR,95);
    set_skill(SS_WEP_SWORD, random(10)+90);
    set_skill(SS_DEFENCE, random(10)+90);
    set_skill(SS_PARRY, random(10)+90);
    set_alignment(100+random(200));
    
    add_prop(LIVE_I_NEVERKNOWN, 1 );
    
    set_chat_time(12);
    add_chat("Someone must stop the Dunlendings!");
    add_chat("The Dunlendings have stolen everything!");
    add_chat("How will I ever recover from what they did to me?");
    add_chat("They even killed my dog!");
    add_chat("Can you help me?");
  
  
    add_ask( ({"dunlending", "dunlendings", "Dunlending", "Dunlendings", "they", "farm"}),
        "@@ask_dunlendings@@");
    add_ask( ({"help", "quest", "task"}), "@@ask_help@@");
    add_ask( ({"reward", "woman", "inn"}), "@@ask_reward@@");
    add_ask( ({"forest", "night", "mountains", "white mountains"}), "@@ask_mountains@@");
    add_ask( ({"burn", "burned", "stole", "steal", "stolen", "everything"}), "@@ask_steal@@");
    add_ask( ({"dog"}), "@@ask_dog@@" );
    set_default_answer("@@ask_default@@");
  

  
}

void
ask_default()
{
    command("say I'm not sure about that.");
    command("emote wails in despair.");
    command("say I just want my farm back.");
}

void
ask_dunlendings()
{
    command("say The Dunlendings came out of the forest by night and burned my farm!");
    command("say They stole what they could carry and burned the rest!");
}

void
ask_help()
{
    command("say I can't afford to pay you anything. I'm just a poor farmer.");
    command("sigh");
    command("say I hear there's a woman at the Inn in Edoras... Maybe she "
        + "can give you a reward.");
}

void
ask_reward()
{
    command("say I'm just a poor farmer. I can't afford to give you a reward.");
    command("think .");
    command("say I hear there's a woman at the Inn in Edoras... Maybe she "
        + "can give you a reward.");
}

void
ask_mountains()
{
    command("say The Dunlendings came out of the big pine forest near the "
        + "White Mountains.");
    command("say The one southeast of my farm.");
    command("cry");
}

void
ask_steal()
{
    command("say They're worse than monsters, these Dunlendings.");
    command("fume");
    command("say Could you please help get my farm back?");
}

void
ask_dog()
{
    command("emote sobs uncontrollably.");
    command("say Muh.. muh... muh dog!");
    command("wail");
    command("say Dead!");
}