/*******************************************************************\
| TREE.C                                                            |
\*******************************************************************/

/*
 * 03/12/11 Arandir     Created
 * 03/12/12 Arandir     Slight change in dance syntax
 *          Arandir     Added the crystal spheres with dancers
 *
 */

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/object";

inherit DG_OBJ_LIBS;
inherit DG_PLAYER_LIBS;

//-------------------------------------------------------------------

public string *asDancers = ({ });
public string *asHuggers = ({ });

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
  return (M_PATH_VAR_OBJ + "/" + dg_base_name ());
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

string m_item_spheres ()
{
  if (sizeof (asDancers) > 1)
  {
    return ("There are " + LANG_WNUM (sizeof (asDancers)) + " " +
            "delicate crystal spheres decorating the tree, almost " +
            "transparent but filled with swirling clouds of mist. " +
            "Picking one sphere at random, you take a closer look " +
            "and realize that a tiny figure of " +
            LANG_ADDART (one_of_list (asDancers)) + " " +
            "dances merrily inside it.\n");
  }
  else return ("You should not look at the spheres yet.\n");
}

//-------------------------------------------------------------------

void create_object ()
{
  ::create_object ();

  set_name ("tree");
  set_adj (({ "decorated", "christmas", "live", "pine" }));
  set_short ("decorated pine tree");
  set_long ("Set in a large stone pot, a live pine tree grows right next " +
            "to you. The tree is tall and straight, with a dark brown bark " +
            "and dense green needles suggesting it is being well cared for. " +
            "Its branches are decorated with silvery chains and crystal " +
            "spheres that set a festive mood.\n");

  add_prop (OBJ_I_WEIGHT, 100000);
  add_prop (OBJ_I_VOLUME, 100000);
  add_prop (OBJ_I_VALUE, 1000);
  add_prop (OBJ_M_NO_GET, "The roots hold the tree firmly in the ground.\n");

  add_item (({ "pot", "stone pot", "large pot", "soil" }),
            "A stone pot is submerged into the floor so that its edge is " +
            "level with the surrounding tiles. Surprisingly thick roots " +
            "disappear into the soil, suggesting that the pot is quite " +
            "large.\n");

  add_item (({ "root", "roots", "thick root", "thick roots" }),
            "Thick and healthy roots support the tree.\n");

  add_item (({ "bark", "trunk" }),
            "The dark brown bark of the tree is a sign of perfect health.\n");

  add_item (({ "needle", "needles" }),
            "The needles are dense, green in color with a slight silvery " +
            "tint that makes the entire tree look as if it basked in " +
            "moonlight.\n");

  add_item (({ "branch", "branches", "pattern" }),
            "Silvery chains and crystal spheres decorate the branches " +
            "of the pine tree, in a marvellous pattern of soft green " +
            "and glittering silver.\n");

  add_item (({ "chain", "chains" }),
            "Silvery chains decorate the branches of the tree, spiraling " +
            "all the way from the ground to the tip of the tree.\n");

  add_item (({ "sphere", "spheres" }), &m_item_spheres ());

  m_restore_object ();
}

//-------------------------------------------------------------------

int m_tree_hug (string sArgs)
{
  object oWho = this_player ();
  string sDesc = dg_get_pretty_description (oWho);

  if (sArgs != "tree") return (FALSE);

  if (member_array (sDesc, asHuggers) < 0)
  {
    asHuggers += ({ sDesc });
    m_save_object ();
  }

  write ("You hug the pine tree in a protective gesture, careful " +
         "to avoid testing the sharpness of its needles. The tree " +
         "seems to shiver slightly in response.\n");
  say (QCTNAME (oWho) + " hugs the pine tree in a protective gesture.\n");

  return (TRUE);
}


int m_tree_climb (string sArgs)
{
  object oWho = this_player ();
  string sDesc = dg_get_pretty_description (oWho);

  string sCompanion;

  if (sArgs != "tree") return (FALSE);

  sCompanion = one_of_list (asHuggers);

  write ("Ducking as you thread your way between the branches, you " +
         "reach the trunk of the pine tree with the intent to " +
         "climb it.\n");

  if (stringp (sCompanion) &&
      (sDesc != sCompanion))
  {
    write ("When you touch the bark of the tree, a sudden flash of " +
           "silvery light blinds you momentarily, pushing you away. " +
           "You would swear you saw an apparition of " +
           LANG_ADDART (sCompanion) + " " +
           "hugging the tree protectively.\n");
    say (QCTNAME (oWho) + " attempts to climb the tree but is " +
         "stopped by an apparition of " +
         LANG_ADDART (sCompanion) + ".\n");

    asHuggers -= ({ sCompanion });
    m_save_object ();
  }
  else
  {
    write ("When you touch the bark of the tree, you feel a strong " +
           "sense of disagreement which makes you back away again.\n");
    say (QCTNAME (oWho) + " attempts to climb the tree.\n");
  }

  return (TRUE);
}


int m_tree_dance (string sArgs)
{
  object oWho = this_player ();
  string sDesc = dg_get_pretty_description (oWho);

  string sCompanionOne;
  string sCompanionTwo;

  if (strlen (sArgs) &&
      parse_command (sArgs, ({ }), "[around] [decorated] [pine] 'tree'"))
  {
    if (member_array (sDesc, asDancers) < 0)
    {
      asDancers += ({ sDesc });
      m_save_object ();
    }

    sCompanionOne = one_of_list (asDancers);
    sCompanionTwo = one_of_list (asDancers);

    write ("You dance around the tree, waving your arms merrily and laughing in joy.\n");

    if (!random (5) &&
        stringp (sCompanionOne) &&
        stringp (sCompanionTwo) &&
        (sDesc != sCompanionOne) &&
        (sDesc != sCompanionTwo) &&
        (sCompanionOne != sCompanionTwo))
    {
      write ("The tree shimmers with a silvery glow in response. All " +
             "of a sudden, the glow forms into silhouettes of " +
             LANG_ADDART (sCompanionOne) + " and " +
             LANG_ADDART (sCompanionTwo) + ". " +
             "The silhouettes accompany you in a joyful dance.\n");
      say (QCTNAME (oWho) + " dances joyfully around the tree, " +
           "accompanied by glowing silvery silhouettes of " +
             LANG_ADDART (sCompanionOne) + " and " +
             LANG_ADDART (sCompanionTwo) + ".\n");
    }
    else
    {
      say (QCTNAME (oWho) + " dances joyfully around the tree.\n");
    }

    return (TRUE);
  }

  return (FALSE);
}


/*
 * Function name : init
 * Description   : Called whenever somebody comes our way.
 *
 */

void init ()
{
  ::init ();

  add_action (&m_tree_hug (), "hug", FALSE);
  add_action (&m_tree_climb (), "climb", FALSE);
  add_action (&m_tree_dance (), "dance", FALSE);
}

//-------------------------------------------------------------------

