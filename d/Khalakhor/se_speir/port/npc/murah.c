/*
 * murah.c
 *
 * Landlord for the village pub in Port MacDunn.
 * 
 * Khail - April 4/97
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

object pub;
string kitchen;

public void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_cloth",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_macdunn" });
  ::arm_me();
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a landlord.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name("landlord");
  add_name("man");
  set_adj("thin");
  add_adj("cheerful");
  set_long("For a man whose entire life revolves around " +
           "food, he seems to fit into rather small clothes. He's " +
           "thin as a reed! The broken blood vessels in his nose, " +
           "however, tend to indicate his indulgences lie more " +
           "within the liquid portion of his menu.\n");

  default_config_npc(40);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_SWORD, 35);

  set_alignment(400);
  set_exp_factor(50);
  set_size_descs("tall", "skinny");
  remembered = ([]);
  add_ask(({"eil-galaith"}),
          "say Hmm. Well I'm not sure. Sounds like something that might "+
          "be on the isle of Galaith.", 1);
  add_ask(({"galaith", "isle of galaith", "galaith isle"}),
          "say Oh yes, the isle of Galaith is near the southwestern speir. "+
          "I've heard there is a tower that suddenly appeared there. I do "+
          "not travel much myself to know for sure. You might try around "+
          "the docks.", 1);
  add_ask(({"dining room", "private dining", "dining"}),
          "say I gave Barley Mae that room to the west. He calls it a "+
          "private dining room. He has put in some nice tables and chairs. "+
          "So go ahead and take a look if you like that sort of thing.",1);
  add_ask(({"barley", "barley mae"}),
          "say Barley Mae is my distant cousin. He's a great chef, but "+
          "thats about it.",1);
    
}

/*
 * Function name: set_pub
 * Description  : Sets landlord's pub object pointer, to make
 *                it easier to see if he's where he's supposed
 *                to be.
 * Arguments    : ob - Object pointer to set as his pub.
 * Returns      : n/a
 */
void
set_pub (object ob)
{
  if (!pub)
    pub = ob;
}

/* Function name: set_kitchen
 * Description  : Sets landlord's kitchen pointer, to make it easier
 *                dealing with him running and hiding from attackers.
 * Arguments    : str - String with the path name to the kitchen.
 * Returns      : n/a
 */
void
set_kitchen (string str)
{
  if (!kitchen)
    kitchen = str;
}

int
hook_return_intro_new (string str)
{
  command("say Good day, " + capitalize(str) +
          "! I'm " + query_name() + ", " + query_name() + " " +
          query_title() + ", and welcome " +
          "to The Wild Rover. What can I get for you?");
  command("bow " + str);
}

int
hook_return_intro_bad (string str)
{
  command("growl");
  command("say I know who you are, you bully. Now buy " +
          "something and leave!");
}

int
hook_return_intro_good (string str)
{
  command("grin misch");
  command("say I may have a few blank spots in my memory, " +
          capitalize(str) + ", but I remember you. What'll it " +
          "be this time?");
  command("smile bright");
  return 1;
}
