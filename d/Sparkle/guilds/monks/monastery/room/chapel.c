/*******************************************************************\
| CHAPEL.C                                                          |
\*******************************************************************/

/*
 * 08/02/16 Mercade     Use CMDPARSE_PARALYZE_CMD_IS_ALLOWED
 * 06/08/16 Arandir     Removed the ability to sacrifice
 * 04/11/14 Arandir     Guild masters on member list
 * 04/08/15 Arandir     Added the missing inside property
 * 03/12/23 Arandir     Empty pray string resulted in runtime
 * 03/05/08 Arandir     Use CMDPARSE_PARALYZE_ALOWED when praying
 * 03/04/25 Arandir     Polished up and bugfixed the defunct
 *                      limit on the maximum number of discs
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 01/06/11 Manat	Added karma check for sacrifice
 * 00/12/22 Manat	Fixed sacrificing
 * 98/06/14 Cirion	Created
 *
 */

#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit "/lib/guild_support";

inherit DG_OBJ_LIBS;
inherit M_OBJ_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

#define M_PRAYER_MANA_COST      10
#define M_PROP_TMP_I_PRAYING    "_monk_tmp_i_praying"

private object oTable;

//-------------------------------------------------------------------

void create_room ()
{
  oTable = dg_clone_here (M_PATH_OBJ + "/chapel_altar");

  set_short ("chapel");
  set_long ("This small chapel serves as a place of meditation " +
            "and rest. " +
            VBFC ("dg_get_description:" + file_name (oTable)) + " " +
            "The rest of the floor is covered with parquet wooden " +
            "tiles staggered together. A large copper and silver lamp " +
            "hanging from the ceiling provides the only light for the " +
            "room.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_top", "east");

  dg_add_entrance ("east", "You walk through the doorway into a small temple.");

  add_item (({ "dais" }),
            "It is a low, semicircular dais, made from white " +
            "marble. Sitting atop the dais is a simple altar " +
            "of dark wood.\n");
  add_item (({ "image", "images", "bird", "birds", "dragon", "dragons" }),
            "The images on the altar are intricate and " +
            "intertwining. They depict long, sinuous dragons " +
            "and graceful birds.\n");
  add_item (({ "floor", "ground", "tile", "tiles" }),
            "The floor is made from hard wooden tiles, fitted " +
            "together neatly.\n");
  add_item (({ "lamp", "copper lamp", "silver lamp" }),
            "It is made from copper and silver, beaten together " +
            "in an ornate pattern. The light from within the " +
            "lamp casts irregular beams of light out along the " +
            "chapel.\n");
  add_item (({ "light", "beam", "beams" }),
            "The copper and silver lamp casts out thin beams of " +
            "light through the small holes in its surface. The " +
            "light shimmers along the walls in irregular patterns.\n");
  add_item (({ "wall", "walls" }),
            "The walls of the chapel are made from large blocks " +
            "of grey stone.\n");
  add_item (({ "ceiling" }),
            "The ceiling of the chapel is high above. From the " +
            "illumination offered by the lamp, you can make " +
            "out the painted image of a long, sinuous grey " +
            "dragon.\n");

  add_cmd_item (({ "lamp", "copper lamp", "silver lamp" }),
                ({"light"}),
                "It is already lit.\n");
  add_cmd_item (({ "lamp", "copper lamp", "silver lamp" }),
                ({ "extinguish" }),
                "You can find no way of opening it, and thus no way " +
                "to extinguish it.\n");
  add_cmd_item (({ "altar", "words", "inscription" }),
                ({ "read" }),
                "Pray for Voice, and thou shalt be granted speech.\n" +
                "Pray for Brotherhood, and thy brethren ye shalt see.\n");

  // This makes it possible to meditate here.

  create_guild_support ();
}

//-------------------------------------------------------------------

/*
 * Function name : m_action_block
 * Description   : A command hook to stop players from
 *                 executing commands while in prayer.
 *
 */

int m_action_block (string sArgs)
{
  object oMe = this_player ();

  // Some commands are always allowed ...

  if (CMDPARSE_PARALYZE_CMD_IS_ALLOWED (query_verb ())) return (FALSE);

  // We must really be in prayer ...

  if (!oMe->query_prop (M_PROP_TMP_I_PRAYING)) return (FALSE);

  write ("But you are currently in prayer.\n");
  return (TRUE);
}


int m_pray_filter (object oWho)
{
  return ((m_is_monk (oWho) || m_is_guild_wizard (oWho))
          && !dg_is_invisible (oWho)
          && !dg_is_junior (oWho));
}


/*
 * Function name : m_prayer_finished
 * Description   : Takes care of the result of a finished prayer.
 *
 */

void m_prayer_finished (object oWho, string sWhat)
{
  object *aoPeople;
  object oDisc;
  int    iGuildStat;

  if (oWho->query_mana () < M_PRAYER_MANA_COST)
  {
    oWho->catch_tell ("You find that your mind is too weak to concentrate now.\n");
  }
  else
  {
    oWho->add_mana (-M_PRAYER_MANA_COST);

    switch (sWhat)
    {
      // Show a list of what monks are on ...

      case "brotherhood":
      case "sisterhood":
      case "friends":
      case "friendship":
      case "knowledge":

        aoPeople = filter (users (), &m_pray_filter ()) - ({ oWho });

        if (sizeof (aoPeople) > 0)
        {
          write ("You can see a vision of " +
                 COMPOSITE_WORDS (aoPeople->query_name ()) +
                 " all around you.\n");
        }
        else
        {
          write ("Your vision comes, but it is empty.\n");
        }

        break;

      // Try to gain a speaking disc ...

      case "voice":

        // This used to limit the number of discs a player could
        // get in a specific period of time, but the mechanism
        // was flawed and it was the consumption of mana
        // rather than this limit that actually hit.

        // Now, the difficulty of getting the disc depends
        // on the intelligence and the guild stat, which is better
        // and ultimately does what the previous mechanism should have.

        if (m_is_monk (oWho, SS_OCCUP)) iGuildStat = TS_OCC;
                                   else iGuildStat = TS_LAYMAN;

        if (oWho->resolve_task (TASK_DIFFICULT, ({ TS_INT, iGuildStat })))
        {
          oWho->catch_tell ("You offer up your prayers for voice.\n");

          DG_FIXUID;
          oDisc = clone_object (M_PATH_OBJ + "/disc");
          oDisc->move (oTable, MOVE_SUBLOC_ALWAYS);

          tell_room (this_object (),
                     "A small iron disc forms from a thin cloud " +
                     "of dust and smoke upon the altar.\n");
        }
        else
        {
          oWho->catch_tell ("Your prayers fail.\n");
        }

        break;

      default:

        oWho->catch_tell ("Your prayers go unheard.\n");
    }
  }

  tell_room (this_object (),
             QCTNAME (oWho) + " rises from prayer.\n",
             oWho);

  oWho->remove_prop (M_PROP_TMP_I_PRAYING);
}


/*
 * Function name : m_action_pray
 * Description   : A command that allows a monk in good standing
 *                 to start praying for something.
 *
 */

int m_action_pray (string sArgs)
{
  object oMe = this_player ();
  string sWhat = "";

  if (m_is_monk (oMe))
  {
    if (m_is_punished (oMe, M_PUNISH_DISGRACE))
    {
      write ("It is futile to pray while disgraced.\n");
      say (QCTNAME (oMe) + " tries with futility to pray.\n");
      oMe->command ("$cry");
    }
    else
    {
      if (strlen (sArgs)) sscanf (sArgs, "for %s", sWhat);
      set_alarm (10.0, 0.0, &m_prayer_finished (oMe, sWhat));
      oMe->add_prop (M_PROP_TMP_I_PRAYING, TRUE);

      write ("You sit crosslegged on the floor and offer " +
             "up your prayers.\n");
      say (QCTNAME (oMe) + " sits cross-legged on the floor " +
           "before the altar and prays silently.\n");
    }
  }
  else
  {
    write ("You lower your head in prayer.\n");
    say (QCTNAME (oMe) + " prays.\n");
  }

  return (TRUE);
}

//-------------------------------------------------------------------

/*
 * Function name : gs_hook_start_meditate
 * Description   : Gives a nice description when someone starts to meditate.
 *
 */

void gs_hook_start_meditate ()
{
  object oMe = this_player ();
  write ("You kneel before the altar and concentrate all your focus inwards.\n");
  say (QCTNAME (oMe) + " kneels down before the altar.\n");
}


/*
 * Function name : gs_hook_rise
 * Description   : Gives a nice description when someone is done meditating.
 *
 */

void gs_hook_rise ()
{
  object oMe = this_player ();
  write ("You rise from the floor and open your eyes.\n");
  say (QCTNAME (oMe)+" rises from the floor and opens " + QPOS (oMe) + " eyes.\n");
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();

  init_guild_support ();

  add_action (m_action_pray, "pray");

  add_action (m_action_block, "", ACTION_PARTIAL);
}

//-------------------------------------------------------------------

