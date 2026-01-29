/*
 * conner.c
 *
 * Shopkeeper for the village shop Tabor Sogh.
 *
 * Khail - April 1/97
 * Zima  - March 15/98
 * Refactored
 * Tapakah, 07/2021
 */

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"
 
inherit BASE_NPC;
inherit "/d/Khalakhor/se_speir/common/shopkeeper.c";

void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_wool",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_tabor" });
  ::arm_me();
}
 
/*
 * lad_lass
 */
string
lad_lass (object tp)
{
  return tp->query_gender() ? "lassie" : "laddie";
}
 
/*
 * ask_suit - player asked me about a beekeeper's suit
 */
string
ask_suit ()
{
  object suit, srm;
  string srpath  = ((ENV(TO))->query_store_room());
 
  if (!stringp(srpath))
    return ("say I do no ha' one with me, "+lad_lass(TP)+".");
  srm=((srpath)->pointer_me());
 
  if (objectp(present(BEE_KEEPER_SUIT,srm)))
    return ("say Aye, "+lad_lass(TP)+", I have one for sale.");
 
  suit=clone_object(ARM+"bk_suit");
  if (objectp(suit)) {
    command("say Aye, "+lad_lass(TP)+", I ha' one!");
    command("say No one's asked for one in a while.");
    command("emote takes something from behind a shelf and puts it up "+
            "for sale.");
    suit->move(srm);
    command("say 'O the finest quality too!");
    return ("smile greedily");
  }
 
  return "say Someone must'a stole it, "+lad_lass(TP)+"! It's gone!";
}
 
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a shopkeeper.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  explicit_name = "conner";
  ::create_khalakhor_human();
  add_name("shopkeeper");
  add_name("man");
  set_adj("fat");
  add_adj("red-bearded");
  set_long("The man appears to have seen little, in any, " +
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
  set_exp_factor(50);
 
  set_act_time(15);
  add_act("emote chuckles softly to himself.");
  add_act("say All these ships from different lands has been " +
          "great for business!");
  add_act("say Have you ever seen a shadow that looked like " +
          "it was moving around? I did once, far to the north.");
  add_act("say Rumour has it the Clans will go to war " +
          "soon, I wonder which ones.");
  add_act("ponder");
 
  add_cact("say Oh, so it's a fight you want, is it?");
  add_cact("emote growls.");
 
  add_ask(({"ossean","Ossean","beekeeper","honey","honeycomb","beeswax",
            "wax"}),
          "say Ossean is a local beekeeper, his place is north of town, "+
          "but he's never home, the lazy scrapper!",1);
  add_ask(({"bee","bees","honeybee","honeybees"}),
          "say Aye, the bees in these parts can be mighty fierce. Wouldn't "+
          "go near 'em wi'out a suit.\n",1);
  add_ask(({"suit","beekeeper suit","bee suit","beekeeper's suit",
            "for suit","for beekeeper suit","for beekeeper's suit"}),
          "@@ask_suit",1);
 
  remembered = ([]);
 
  set_size_descs("short", "plump");
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
  command("say I remember you, thug, what do you want this " +
          "time?");
}

void 
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say My memory might be short, " + capitalize(str) +
          ", but I still remember you from your last vist. What " +
          "can I do for you?");
}
