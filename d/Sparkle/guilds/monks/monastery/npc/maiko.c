/*******************************************************************\
| MAIKO.C                                                           |
\*******************************************************************/

/*
 * 04/11/20 Arandir     Removed the tough food regime
 * 04/10/08 Arandir     Better hint for listing prices
 * 04/02/07 Arandir     Added the tough food regime
 * 03/12/11 Arandir     Added the punishment support
 * 03/08/05 Arandir     Fixed heap coalescing
 * 03/05/09 Arandir     Polished up and bugfixed
 * 02/05/02 Arandir	Ported to new area without rewrite
 * 00/12/26 Manat	Fixed a typo
 * 98/10/22 Cirion	Created
 *
 */

#include <const.h>
#include <macros.h>
#include <formulas.h>
#include <language.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

inherit "/lib/pub";
inherit "/lib/trade";

//-------------------------------------------------------------------

// Determines what food and drinks are served.

#undef  M_SERVE_STRICT
#define M_SERVE_NORMAL
#undef  M_SERVE_RICHER

// This definition is based on man values because there
// seems to be no equivalent definition in formulas.h ...

#define M_VALUE_FOOD(iAmount)   (5 + (iAmount * iAmount / 600))

//-------------------------------------------------------------------

void m_setup_food ()
{
  int iRandomizer = random (20, time () / 3600);

#ifdef M_SERVE_STRICT
  add_food (({ "bread", "loaf" }), ({ "bread", "loaf" }), ({ "cold", "hard", "stale" }),
            10, M_VALUE_FOOD (10) + iRandomizer,
            "loaf of bread", "loaves of bread",
            "It is a hard loaf of bread.\n");
#endif

#ifdef M_SERVE_NORMAL
  add_food (({ "bread", "loaf" }), ({ "bread", "loaf" }), ({ "warm", "hot" }),
            100, M_VALUE_FOOD (100) + iRandomizer,
            "loaf of bread", "loaves of bread",
            "It is a piping hot loaf of freshly-made bread.\n");
  add_food (({ "soup", "bowl", "broth" }), ({ "broth", "soup", "bowl" }), ({ "warm", "hot", "vegetable" }),
            193, M_VALUE_FOOD (193) + iRandomizer,
            "bowl of hot vegetable broth", "bowls of hot vegetable broth",
            "It is a large, thick leaf formed cleverly into a bowl, " +
            "which is filled with warm, rich-smelling vegetable broth.\n");
#endif
}


void m_setup_drinks ()
{
  int iRandomizer = random (50, time () / 3600);

#ifdef M_SERVE_STRICT
  add_drink ("water", "water", ({ "tepid", "lukewarm" }),
             10, 0, 5,
             "glass of water", "glasses of water",
             "It is simply a glass of tepid water.\n",0);
#endif

#ifdef M_SERVE_NORMAL
  add_drink ("water", "water", "fresh",
             90, 0, 10,
             "glass of water", "glasses of water",
             "It is simply water, sparkling fresh and clear.\n",0);
  add_drink ("wine", "wine", "red",
             70, 40, F_VALUE_ALCO (40) + iRandomizer,
             "glass of red wine", "glasses of red wine",
             "The sparkling rosy tint of this wine comes from " +
             "the ripened grapes that were harvested from the " +
             "vinyards near the monastery.\n", 0);
  add_drink ("mead", "mead", "foul smelling",
             10, 70, F_VALUE_ALCO(70) + iRandomizer,
             "mug of thick mead", "mugs of thick mead",
             "Foul smelling vapors rise from this thick, dark brown " +
             "liquid. You feel dizzy even inhaling the fumes.\n",0);
#endif
}

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("maiko");
  set_gender (G_MALE);
  set_race_name ("human");
  set_adj (({ "elderly", "wrinkled" }));
  set_long ("This bald monk stands tall with an air of ease and " +
            "grace that defies his many years. He now serves " +
            "out his remaining years as the steward of the " +
            "dining hall, taking orders for food and drink. " +
            "He can also list the prices for you.\n");

  m_init ();
  m_equip (({ 20 + random (15) }));
  m_stature (185, 70);

  set_act_time (30);
  add_act ("mk control");
  add_act ("mk inspired");
  add_act ("mk dedicate");
  add_act ("mk relax");

  // Setup functions to see food and drink

  config_default_trade ();
  set_money_give_max (2000);
  set_money_give_out (({ 2000, 700, 50, 4 }));
  set_money_give_reduce (({ 1, 1, 1, 1 }));

  m_setup_food ();
  m_setup_drinks ();
}

//-------------------------------------------------------------------

int m_action_list (string sWhat)
{
  mixed  mItems;
  string sName;
  string sCost;
  int    iItem;
  int    iTimer = 0;

  // Make sure the player wants to list prices ...

  if (sWhat == "prices")
  {
    // First, list the available drinks ...

    mItems = query_drinks ();

    if (pointerp (mItems) && sizeof (mItems))
    {
      m_say ("For drinks I can sell you the following:", iTimer ++);

      for (iItem = 0 ; iItem < sizeof (mItems) ; iItem ++)
      {
         sName = LANG_ADDART (mItems [iItem] [5]);
         sCost = LANG_WNUM (mItems [iItem] [4]);

         m_say (capitalize (sName) + " for " + sCost + " coppers.", iTimer ++);
      }
    }

    // Next, list the available food ...

    mItems = query_food ();

    if (pointerp (mItems) && sizeof (mItems))
    {
      m_say ("For food I can sell you the following:", iTimer ++);

      for (iItem = 0 ; iItem < sizeof (mItems) ; iItem ++)
      {
         sName = LANG_ADDART (mItems [iItem] [4]);
         sCost = LANG_WNUM (mItems [iItem] [3]);

         m_say (capitalize (sName) + " for " + sCost + " coppers.", iTimer ++);
      }
    }

    return (TRUE);
  }

  return (FALSE);
}

//-------------------------------------------------------------------

void init_living ()
{
  ::init_living ();

  init_pub ();

  add_action (&m_action_list (), "list");
}

//-------------------------------------------------------------------

/*
 * Function name : m_move_to_table
 * Description   : Here the order gets placed on the table
 *
 */

void m_move_to_table (object oWhat, object oWhere)
{
  oWhat->set_no_merge (FALSE);
  oWhat->move (oWhere, MOVE_SUBLOC_ALWAYS);
}


/*
 * Function name : pay_hook_player_buys
 * Description   : Here the order gets placed on the table
 *
 */

void pub_hook_player_buys (object oItem, int iPrice)
{
  object oMe = this_object ();
  object oHim = this_player ();
  object oRoom = environment (oMe);
  object oTable = oRoom->m_get_table ();;

  write ("You pay " + iPrice + " coppers for " + LANG_THESHORT (oItem) + ".\n");
  say (QCTNAME (oHim) + " orders " + LANG_ASHORT (oItem) + ".\n");

  if (present (oTable, oRoom))
  {
    tell_room (oRoom, QCTNAME (oMe) + " places " + LANG_THESHORT (oItem) +
               " on " + LANG_THESHORT (oTable) + ".\n");

    // The move has to happen in an alarm because the item
    // is moved to the player after we return. We need to
    // prevent heap merging too ..

    oItem->set_no_merge (TRUE);
    set_alarm (0.0, 0.0, &m_move_to_table (oItem, oTable));
  }
}

//-------------------------------------------------------------------

/*
 * Function name : order
 * Description   : Blocks ordering for punished players
 *
 */

int order (string sArgs)
{
  object oWho = this_player ();

  if (m_is_punished (oWho, M_PUNISH_NOBUY))
  {
    notify_fail ("You are forbidden to order by the council.\n");
    return (FALSE);
  }
  else
  {
    return (::order (sArgs));
  }
}

//-------------------------------------------------------------------

