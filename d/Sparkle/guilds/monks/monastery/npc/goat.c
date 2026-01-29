/*******************************************************************\
| GOAT.C                                                            |
\*******************************************************************/

/*
 * 11/07/12 Lavellan    Gave some combat skills
 * 07/05/26 Arandir     Gave the goat a decent climb skill
 * 03/08/05 Arandir     Replaced DG_RANDARR with one_of_list
 * 02/07/27 Arandir	Remade into a goat that is more thematic
 * 02/07/21 Arandir     Removed the obsolete usage of add_action
 * 02/01/23 Arandir	Ported to new area
 * 99/03/06 Cirion	Created
 *
 */

#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#include "../defs.h"

inherit "/std/act/action";
inherit "/d/Genesis/steed/steed";
inherit "/d/Genesis/steed/feeding";

//-------------------------------------------------------------------

// This code defines the fill, empty, drape, remove, close and
// open commands related to the saddlebags that the animal can
// carry.

#define ENV(o)	environment (o)

#include "/d/Terel/calathin/npc/terel_horse_saddlebag.c"

//-------------------------------------------------------------------

string act_twitch ()
{
  object *aoCargo;

  aoCargo = FILTER_DEAD (all_inventory (this_object ()));

  if (sizeof (aoCargo))
  {
    return ("emote twitches its shoulder, shifting " +
            COMPOSITE_DEAD (aoCargo) + " draped over its withers.");
  }
  else
  {
    return ("emote twitches its shoulder.");
  };
}

string act_nibble ()
{
  object oRoom = environment ();

  if (wildmatch ("* grass*", oRoom->long ()))
  {
    return ("emote nibbles at the grass.");
  }
  else
  {
    return ("");
  };
}

//-------------------------------------------------------------------

int can_lead (object oLiving)
{
  return (TRUE);
}

//-------------------------------------------------------------------

void create_steed ()
{
  string *asColors = ({ "black", "brown", "white", "grey", "spotted" });
  string *asDescs = ({ "swift", "old", "lean", "hairy" });

  string sColor = one_of_list (asColors);
  string sDesc = one_of_list (asDescs);

  set_name ("goat");
  set_short (sDesc + " " + sColor + " goat");
  set_long ("It is a " + sColor + " goat, partially domesticated. " +
            "It looks to be both well-fed and well-groomed. If it " +
            "likes you, you might be able to drape a pack over its " +
            "gleaming " + sColor + " withers.\n");
  if (random(2))
  {
    set_gender (G_MALE);
    set_stats (({ 100, 45, 92, 5, 100, 60 }));
  }
    else
  {
    set_gender (G_FEMALE);
    set_stats (({ 80, 65, 82, 5, 80, 60 }));
  };

  set_skill (SS_CLIMB, 100);
  set_skill (SS_DEFENSE, 30);
  set_skill (SS_UNARM_COMBAT, 50);

  
  set_race_name ("goat");
  set_adj (({ sColor, sDesc }));

  set_act_time (10);
  add_act (VBFC_ME ("act_twitch"));
  add_act (VBFC_ME ("act_nibble"));

  set_allowed_food (({ "hay", "oats", "barley", "sugar", "grass",
                       "fruit", "apple", "herb", "vegetable" }));
}

void init_living ()
{
  ::init_living ();

  add_action (do_fill, "fill");
  add_action (do_empty,"empty");
  add_action (do_drape, "drape");
  add_action (do_remove,"remove");
  add_action (do_close, "close");
  add_action (do_open, "open");
}

//-------------------------------------------------------------------

void emote_hook (string sEmote, object oActor, string sAdverb = 0)
{
  switch (sEmote)
  {
    case "pet":
    case "cuddle":
    case "ruffle":
    case "pat":
    case "kiss":
    case "lick":
    case "fondle":
      command ("emote meeks " +
               one_of_list (({ "happily", "contentedly", "merrily", "joyfully" })) +
               ".");
      break;

    case "poke":
    case "kick":
    case "swear":
    case "spit":
      command ("emote stomps " +
               one_of_list (({ "angrily", "ill-temperedly", "unhappily", "menacingly" })) +
               ".");
      break;

    case "chastise":
    case "scold":
      command ("emote hangs its head in shame.");
      break;
  };
}

//-------------------------------------------------------------------

