/*******************************************************************\
| MZENSKA.C                                                         |
\*******************************************************************/

/*
 * 20181119 Ckrik Increase min stats, added fire breathing and reduced hunger
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 03/09/16 Arandir     Fixed path for saving state
 * 03/05/16 Arandir     Fixed so that food does not get wasted
 *                      when the lizard does not eat it all
 * 03/05/10 Arandir     Polished up
 * 02/05/02 Arandir	Ported to new area without rewrite
 * 01/01/26 Manat	Added the possibility of an amulet quest
 * 01/01/18 Manat	Added an amulet to the description
 * 00/12/28 Manat	Changed the feed command to process numbers
 *			better. Also changed devout to use tell room
 *			instead of say.
 * 00/12/26 Manat	Fixed a typo
 * 99/08/15 Cirion	Created
 *
 */

#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <alignment.h>
#include <state_desc.h>

#include "../defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit DG_OBJ_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

private static string *asReactEmotions = ({ });
private static string *asReactCommands = ({ });
private static int    *aiReactPlayers  = ({ });

public int iCounter = 0;

#define M_STATS_MIN     180
#define M_STATS_MAX     (SD_STATLEVEL_SUP * 2)

#define M_HUNGER_MIN    0
#define M_HUNGER_MAX    1000

#define M_SUSTENANCE    100

#define M_GUARDIAN_BREATH_BASE_PEN 800
#define M_GUARDIAN_BREATH_RANDOM_ADD_PEN 400
#define M_GUARDIAN_BREATH_DELAY 8

#define M_FOOD_AMOUNT_FACTOR 2

//-------------------------------------------------------------------

/*
 * Function name : m_filename
 * Function name : m_save_object
 * Function name : m_restore_object
 * Description   : Functions to save and restore the object.
 *
 */

string m_filename ()
{
  return (M_PATH_VAR_NPC + "/" + dg_base_name ());
}

void m_save_object ()
{
  DG_FIXUID;
  save_object (m_filename ());
}

void m_restore_object ()
{
  DG_FIXUID;
  restore_object (m_filename ());
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for reacting to actions                                   |
\*******************************************************************/

/*
 * Function name : m_add_reaction
 *
 */

void m_add_reaction (mixed mEmotion, string sCommand, int iPlayer)
{
  int iEmotion;

  if (pointerp (mEmotion))
  {
    for (iEmotion = 0 ; iEmotion < sizeof (mEmotion) ; iEmotion ++)
    {
      m_add_reaction (mEmotion [iEmotion], sCommand, iPlayer);
    }
  }
  else
  {
    asReactEmotions += ({ mEmotion });
    asReactCommands += ({ sCommand });
    aiReactPlayers += ({ iPlayer });
  }
}


/*
 * Function name : emote_hook
 * Description   : Reacts to the emotes performed in the room or
 *                 on the lizard directly.
 *
 */

varargs void emote_hook (string sEmote, object oActor, string sAdverb = NULL, object *aoTargets = NULL, int iAttributes = 0, int iTarget = FALSE)
{
  int iIndex;

  iIndex = member_array (sEmote, asReactEmotions);

  if (iIndex != -1)
  {
    if (aiReactPlayers [iIndex])
    {
      command (asReactCommands [iIndex] + " " + OB_NAME (oActor));
    }
    else
    {
      command (asReactCommands [iIndex]);
    }
  }
}

// We max eat_max() to break and infinte loop
int eat_max()
{
  return 100 + M_STATS_MAX * 30;
}

int m_query_pct_stuffed()
{
  int iResult;

  iResult = (query_stuffed() * 100) / eat_max();

  return iResult;
}

//-------------------------------------------------------------------

/*
 * Function name : query_base_stat
 * Description   : Returns stats based on hunger
 *
 */

int query_base_stat (int iStat)
{
  int iResult;

  // Stats are exponentially proportional stuffed

  iResult = (m_query_pct_stuffed() + 20) * M_STATS_MAX / 100;
  iResult = MAX (M_STATS_MIN, iResult);
  iResult = MIN (M_STATS_MAX, iResult);

  return (iResult);
}

//-------------------------------------------------------------------

/*
 * Function name : m_hunger_desc_short
 *
 */

string m_hunger_desc_short ()
{
  int iHunger = m_query_pct_stuffed();
  switch (iHunger)
  {
    case 0..20:      return ("starving");
    case 21..30:     return ("emaciated");
    case 31..40:     return ("very hungry");
    case 41..50:     return ("frail");
    case 51..60:     return ("lean");
    case 61..70:     return ("fierce");
    case 71..80:     return ("terrifying");
    case 81..90:     return ("majestic");
    case 91..100:    return ("invincible");
    default:         return ("hungry");
  }
}

/*
 * Function name : m_hunger_desc_long
 *
 */

string m_hunger_desc_long ()
{
  int iHunger = m_query_pct_stuffed();
  switch (iHunger)
  {
    case 0..20:      return ("He is looking on the verge of death from hunger.");
    case 21..30:     return ("He is looking so emaciated that he can hardly get up.");
    case 31..40:     return ("He is looking like he could eat a lot more.");
    case 41..50:     return ("He is looking rather frail from the lack of food.");
    case 51..60:     return ("He is looking rather lean.");
    case 61..70:     return ("He is looking strong and fierce, although he looks as though he could eat a bit more.");
    case 71..80:     return ("He is looking fierce and terrible, like he could tear your limbs off just by looking at them. He seems as though he might want to eat a bit more ...");
    case 81..90:     return ("He is looking majestic and fierce.");
    case 91..100:    return ("He is looking as if nothing could stop him. He also seems very well fed.");
    default:         return ("He looks like he could eat a bit more.");
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_is_food
 * Description   : Determines whether this is something we can eat
 *
 */

int m_is_food (object oItem)
{
  return ((function_exists ("create_food", oItem)) &&
          (oItem->query_amount () > 0));
}

/*
 * Function name : m_pinch_heap
 * Description   : Pinches a bit off a heap.
 *
 */

object m_pinch_heap (object oHeap, int iAmount)
{
  object oRemnant;
  int    iSize;

  iSize = oHeap->num_heap ();
  oHeap->split_heap (iSize - iAmount);
  oRemnant = oHeap->make_leftover_heap ();

  return (oRemnant);
}

/*
 * Function name : m_devour
 * Description   : Devours a single food object
 *   oFood         : What to devour
 * Returns       : True if everything was devoured, false if
 *                 some food was left because we are full
 *
 */

int m_devour (object oFood)
{
  object oMe = this_object ();
  int iAmountAvailable, iAmountPossible;
  int iAmountEaten;
  int iCountAvailable;
  int iCountEaten;
  float fPercentHP;

  // First, we have to calculate how much we can actually eat.
  // We presume that all food comes in heaps, same as in the
  // standard eat command in the MudLib.

  iAmountAvailable = oFood->query_amount () * M_FOOD_AMOUNT_FACTOR;
  iAmountPossible = eat_max() - query_stuffed();
  iCountAvailable = oFood->num_heap ();

  if (iAmountAvailable * iCountAvailable > iAmountPossible)
  {
    iCountEaten = iAmountPossible / iAmountAvailable;
    oFood = m_pinch_heap (oFood, iCountEaten);
  }
  else
  {
    iCountEaten = iCountAvailable;
  }

  iAmountEaten = iCountEaten * iAmountAvailable;

  if (iAmountEaten > 0)
  {
    // The message has to be printed before devouring the food
    // because otherwise we loose the short description.

    tell_room (environment (oMe), QCTNAME (oMe) + " devours " +
               LANG_ASHORT (oFood) + ".\n", oMe, oMe);

    // Feeding raises the stats, we need to raise the
    // hit points to preserve the current percentage.

    fPercentHP = itof (query_hp ()) / itof (query_max_hp ());
    
    set_hp (ftoi (itof (query_max_hp ()) / fPercentHP));

    eat_food (iAmountEaten, FALSE);
    oFood->remove_food ();
  }

  return (iCountEaten == iCountAvailable);
}

/*
 * Function name : m_action_feed
 * Description   : Feeds the lizard
 *
 */

int m_action_feed (string sArgs)
{
  object oHim = this_player ();
  object oMe = this_object ();
  mixed  *axItems;
  int    iCount;
  int    iIndex, iTotal;

  // Just in case we fail ...

  notify_fail ("Feed lizard with what ?\n");

  if (!parse_command (sArgs, all_inventory (oHim), "'lizard' / 'mzenska' [with] %i", axItems))
    return (FALSE);

  if (sizeof (axItems) < 1) return (FALSE);

  iTotal = axItems [0];
  iIndex = 1;

  if (iTotal < 0)
  {
    // The player used specification such as "first", we
    // need to find which item this really is ...

    for ( ; iIndex < sizeof (axItems) ; iIndex ++)
    {
      iTotal += MAX (1, axItems [iIndex]->num_heap ());
      if (iTotal >= 0) break;
    }

    if (iTotal < 0) return (FALSE);

    iTotal = 1;
  }
  else if (iTotal == 0)
  {
    // The player used specification such as "all" ...

    iTotal = MAXINT;
  }

  // We just eat what we were told to now ...

  for ( ; (iIndex < sizeof (axItems)) && (iTotal > 0) ; iIndex ++)
  {
    if (m_is_food (axItems [iIndex]))
    {
      iCount = MAX (1, axItems [iIndex]->num_heap ());
      if (iCount > iTotal)
      {
        iCount = iTotal;
        axItems [iIndex] = m_pinch_heap (axItems [iIndex], iCount);
      }
      oHim->catch_msg ("You feed " + LANG_THESHORT (axItems [iIndex]) + " to " + QTNAME (oMe) + ".\n" );
      say (QCTNAME (oHim) + " feeds " + LANG_THESHORT (axItems [iIndex]) + " to " + QTNAME (oMe) + ".\n");
      if (!m_devour (axItems [iIndex]))
      {
        write (XCTNAME (oHim, oMe) + " does not want more food right now, " +
               "but knowing " + XPOS (oMe) + " appetite, you can always " +
               "leave a few tidbits just in case " + XPNOUN (oMe) + " gets " +
               "hungry later.\n");
        break;
      }
    }
    else
    {
      write (XCTNAME (oHim, oMe) + " does not want " + LANG_THESHORT (axItems [iIndex]) + ".\n");
    }

    iTotal -= iCount;
  }

  m_save_object ();
  return (TRUE);
}

//-------------------------------------------------------------------

void init_living ()
{
    ::init_living ();

    add_action (m_action_feed, "feed");
}

//-------------------------------------------------------------------

void default_config_npc (int iStats)
{
  int iIndex;

  for (iIndex = 0 ; iIndex < SS_NO_STATS ; iIndex ++)
  {
    set_base_stat (iIndex, iStats);
  }
}

//-------------------------------------------------------------------

/*
 * Function name : reset_npc
 * Description   : Called periodically to make the lizard grow hungry.
 *
 */

void reset_npc ()
{
  object oMe = this_object ();
  object oRoom = environment ();
  object *aoFood;
  int    iIndex;

  // We attempt to eat all the food that is present.
  aoFood = filter (all_inventory (oRoom), &m_is_food ());
  for (iIndex = 0 ; iIndex < sizeof (aoFood) ; iIndex ++)
  {
    m_devour (aoFood [iIndex]);
  }

  m_save_object ();
}

//-------------------------------------------------------------------

string m_short ()
{
  return (m_hunger_desc_short () + " fire lizard");
}


string m_long ()
{
  object oHim = this_player ();
  string sDesc;

  sDesc = "Long and sinuous, this fire lizard has ruby-red " +
          "eyes and long, sharp irridescent scales. He lies curled " +
          "at the base of the stairs, peering around intently. ";

  if (dg_is_invisible (oHim))
    sDesc += "His eyes rest on you, even in your invisible state. ";
  else if (dg_is_hidden (oHim))
    sDesc += "He stares at you with disdain, despite " +
             "your efforts to hide. ";

  sDesc += m_hunger_desc_long () + "\n";

  return (sDesc);
}


void create_creature ()
{
  set_name ("mzenska");
  add_name ("lizard");
  add_adj ("fire");
  add_adj ("sinuous");

  // Note that due to bugs in MudLib it is not OK to use
  // function pointer in calls to set_short even though
  // the documentation states it should work.

  set_short (VBFC_ME ("m_short"));
  set_long (&m_long ());

  set_race_name ("dragon");

  set_alignment (ALIGN_GOOD);
  default_config_npc (SD_STATLEVEL_SUP);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (SS_DEFENCE, 100);
  set_skill (SS_BLIND_COMBAT, 100);

  add_prop (LIVE_I_SEE_INVIS, TRUE);
  add_prop (LIVE_I_NEVERKNOWN, TRUE);

  set_attack_unarmed (0,  100, 100, W_IMPALE, 50, "jaws");
  set_attack_unarmed (1, 100, 100, W_BLUDGEON, 50, "tail");
  set_hitloc_unarmed (0, ({ 150 }), 10, "head");
  set_hitloc_unarmed (1, ({ 150 }), 80, "body");
  set_hitloc_unarmed (2, ({ 150 }), 10, "tail");
  add_prop(LIVE_I_QUICKNESS, 150);

  set_exp_factor(200);

  m_add_reaction (({ "pet", "hug", "cuddle", "pat", "ruffle" }), "purr", FALSE);
  m_add_reaction (({ "snuggle", "smile" }), "emote chirps happily.", FALSE);
  m_add_reaction ("grin", "leer mischievously", TRUE);

  m_add_reaction (({ "growl", "scowl", "snarl" }), "snarl", TRUE);
  m_add_reaction ("tackle", "blink", FALSE);
  m_add_reaction (({ "fart", "burp", "puke" }), "stare disgustedly", TRUE);

  m_add_reaction ("ack", "jump", FALSE);
  m_add_reaction ("agree", "nod sagely", TRUE);
  m_add_reaction ("applaud", "bow clumsily", FALSE);
  m_add_reaction ("admire", "blush", FALSE);
  m_add_reaction ("apologize", "emote chirps happily.", FALSE);
  m_add_reaction ("avert", "avert", TRUE);
  m_add_reaction ("back", "snarl mischievously", TRUE);
  m_add_reaction ("beg", "shake", TRUE);
  m_add_reaction ("blank", "blank", FALSE);
  m_add_reaction ("blush", "sigh .", FALSE);
  m_add_reaction ("bow", "stare .", TRUE);
  m_add_reaction (({ "bat", "blow", "caress", "gesture", "grope",
                     "fawn", "fondle", "french", "puke", "nuzzle",
                     "nibble" }), "back", TRUE);
  m_add_reaction ("bite", "emote snaps its jaws.", FALSE);
  m_add_reaction ("blink", "blink .", FALSE);
  m_add_reaction ("boggle", "bounce", FALSE);
  m_add_reaction ("brighten", "emote chirps merrily.", FALSE);
  m_add_reaction ("beckon", "back", TRUE);
  m_add_reaction ("blanch", "emote chirps with concern.", FALSE);
  m_add_reaction ("bounce", "bounce", FALSE);

  // Set variables based on the saved hunger ...

  m_restore_object ();
  set_hp (query_max_hp ());
  set_fatigue (query_max_fatigue ());

  // The alarm makes us grow hungry ...

  set_alarm (1800.0, 5400.0, &reset_npc ());
}

//-------------------------------------------------------------------

int
special_attack(object enemy)
{
  string damage_lvl;
  mixed damage;
  int pen, target_pen;
  int i;
  object* targets;
  object me;

  me = this_object();
  
  if (++iCounter >= M_GUARDIAN_BREATH_DELAY + random(2))
  {
    targets = query_enemy(-1);
    pen = M_GUARDIAN_BREATH_BASE_PEN + random(M_GUARDIAN_BREATH_RANDOM_ADD_PEN);
    targets[i]->catch_msg(QCTNAME(me) + " inhales deeply and breathes out a torrent of fire.\n");
    for (i = 0; i < sizeof(targets); i++)
    {
      target_pen = pen - pen * targets[i]->query_magic_res(MAGIC_I_RES_FIRE) / 100;
      damage = targets[i]->hit_me(target_pen, MAGIC_DT, me, -1);
      if (damage[0] <= 0) {
        damage_lvl = "unharmed";
      } else if (damage[0] < 10) {
        damage_lvl = "slightly singed";
      } else if (damage[0] < 30) {
        damage_lvl = "moderately burned";
      } else if (damage[0] < 60) {
        damage_lvl = "horribly charred";
      } else {
        damage_lvl = "torched beyond recognition";
      }
      targets[i]->catch_msg("You are " + damage_lvl + " by the fire.\n");
      tell_watcher(QCTNAME(targets[i]) + " looks " + damage_lvl + " by the fire.\n", targets[i]);
    }

    return 1;
  }

  return 0;
}