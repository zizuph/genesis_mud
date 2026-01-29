//
// shopkeeper.c
//
// Shopkeeper for the village shop, copied from Tabor Sogh
//
// Khail - April 1/97
// Zima  - June 10/98 (copied)

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
inherit "/d/Khalakhor/se_speir/common/landlord";
inherit BASE_ASHLAGH;

void
arm_me()
{
  armours = ({ COM_ARM+"shirt_wool",
               COM_ARM+"belt",
               COM_KILTS+"kilt_tabor" });

  ::arm_me();
}
 
void
create_khalakhor_human ()
{
  explicit_name = "lyrr";
  ::create_khalakhor_human();
  set_race_name("dwarf");
  add_name("shopkeeper");
  add_name("man");
  set_adj("fat");
  add_adj("red-bearded");
  set_long("The dwarf appears to have seen little, in any, " +
           "exercise in years. You notice as he moves " +
           "around the rippling of muscle beneath a layer of fat, " +
           "and suspect a few years ago his build might have been " +
           "quite different.\n");
 
  default_config_npc(40);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_SWORD, 35);
  
  set_alignment(400);

  add_prop(ATTACK_TEAM,ATEAM);
 
  set_act_time(15);
    add_act("emote chuckles softly to himself.");
    add_act("say All these visitors from different lands have been " +
        "great for business!");
    add_act("say Have you ever seen a shadow that looked like " +
        "it was moving around? I did once, far to the north.");
    add_act("say Rumour has it the Clans will go to war " +
        "soon, I wonder which ones.");
    add_act("say The gobbo's been bad for business these days.");
    add_act("ponder");
 
    add_cact("say Oh, so it's a fight you want, is it?");
    add_cact("say Ye'll not get a penny of me money, varmit!");
    add_cact("say The guards'll rip yer head off!");
    add_cact("emote growls.");
 
    remembered = ([]);
 
    set_size_descs("short", "plump");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}
 
int
query_no_deals (object ob)
{
    string name;
 
    name = ob->query_real_name();
    if (!remembered[name])
        return 0;
    if (remembered[name] == "bad")
        return 1;
    return 0;
}
 
void
hook_return_intro_new (string str)
{
  command("say Ahh, pleased to meet you, " + capitalize(str) +
          ", " + query_name() + " " + query_title() +
          ", at your service.");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("growl");
  command("say I remember you, thug, what do you want this time?");
}

void
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say My memory might be short, " + capitalize(str) +
          ", but I still remember you from your last vist. What " +
          "can I do for you?");
}
