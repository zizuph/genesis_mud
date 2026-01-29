/*******************************************************************\
| MIRROR.C                                                          |
\*******************************************************************/

/*
 * 01/02/07 Manat 	Created
 * 01/12/17 Arandir     Fixed a typo
 * 03/05/18 Arandir	Ported to new area and bugfixed
 * 03/07/23 Arandir     Fixed so that even invis people see it
 *
 */

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/object";

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

object *aoWatchers = ({ });

//-------------------------------------------------------------------

int m_near_player (object oHim)
{
  object oEnv = environment ();

  // Check whether we are held by the player or in the same room

  return (objectp (oHim) &&
          ((oEnv == oHim) ||
           (oEnv == environment (oHim))));
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions to mimic /std/living/description                        |
\*******************************************************************/

int query_met (mixed name) { return (0); }

string query_real_name () { return (lower_case (::query_name ())); }
string query_name () { return (capitalize (::query_name ())); }
string query_met_name () { return (query_name ()); }
string query_nonmet_name () { return (::short()); }
string query_Met_name () { return (capitalize (query_met_name ())); }

varargs string query_art_name (object pobj) { return (LANG_ADDART (query_nonmet_name ())); }
varargs string query_Art_name (object pobj) { return (capitalize (query_art_name (pobj))); }
varargs string query_art_possessive_name (object pobj) { return (LANG_POSS (query_art_name (pobj))); }
varargs string query_Art_possessive_name (object pobj) { return (LANG_POSS (query_Art_name (pobj))); }
varargs string query_the_name (object pobj) { if  (!objectp (pobj)) pobj = previous_object (-1); return ("the " + query_nonmet_name ()); }
varargs string query_The_name (object pobj) { return (capitalize (query_the_name (pobj))); }
varargs string query_the_possessive_name (object pobj) { return (LANG_POSS (query_the_name (pobj))); }
varargs string query_The_possessive_name (object pobj) { return (LANG_POSS (query_The_name (pobj))); }

//-------------------------------------------------------------------

int can_see_in_room () { return (TRUE); }

int check_seen (object for_obj) { return (TRUE); }

int query_humanoid ()
{
  object tp = this_player ();
  if (m_near_player (tp))
    return (tp->query_humanoid ());
  return (FALSE);
}

object query_combat_object ()
{
  object tp = this_player ();
  if (m_near_player (tp))
    return (tp->query_combat_object ());
  return (FALSE);
}

mixed query_armour (int which)
{
  object tp = this_player ();
  if (m_near_player (tp))
    return (tp->query_armour (which));
  return (FALSE);
}

int query_hp ()
{
  object tp = this_player ();
  if (m_near_player (tp))
    return (tp->query_hp ());
  return (500);
}

int query_max_hp ()
{
  object tp = this_player ();
  if (m_near_player (tp))
    return (tp->query_max_hp ());
  return (500);
}

//-------------------------------------------------------------------

/*
 * Function name : long
 * Description   : Returns long description of the mirror
 *
 */

varargs string long (mixed oFor)
{
  string sDesc;
  object oHim;

  oHim = objectp (oFor) ? oFor : this_player ();

  sDesc = "The ornamented mirror is heavy, made from a strange " +
          "material that only mirrors things when looked straight in.";

  if (m_near_player (oHim) && m_is_monk (oHim))
  {
    sDesc += " Perhaps you can try to appraise it.";
  }

  sDesc += "\n";
  return (sDesc);
}

/*
 * Function name : show_visible_contents
 * Description   : Returns the contents of the mirror
 *
 */

void show_visible_contents (object oFor)
{
  object oHim = this_player ();
  string sDesc;

  if (m_near_player (oHim))
  {
    sDesc = "Contained within the mirror is ";
    if (oHim == oFor) sDesc += "your";
                 else sDesc += XPNAME (oHim, oFor);
    sDesc += " image:\n";
    sDesc += oHim->long (oFor);
    oFor->catch_tell (sDesc);
  }
  else
  {
    oFor->catch_tell ("Nothing is visible in the mirror.\n");
  }
}

//-------------------------------------------------------------------

/*
 * Function name : create_object
 *
 */

void create_object ()
{
    set_name ("mirror");
    set_short ("ornamented mirror");
    set_adj (({ "ornamented", "monk" }));

    add_prop (OBJ_I_VALUE, 50000);
    add_prop (OBJ_I_WEIGHT, 100000);
    add_prop (OBJ_I_VOLUME, 123000);
    add_prop (OBJ_M_NO_ATTACK, "The ornamented mirror is not alive.\n");
    add_prop (OBJ_M_NO_MAGIC_ATTACK, "The ornamented mirror is not alive.\n");
    add_prop (OBJ_M_NO_GET, TRUE);
    add_prop (OBJ_M_NO_INS, TRUE);
    add_prop (OBJ_M_NO_SELL, TRUE);
    add_prop (OBJ_M_NO_GIVE, TRUE);
    add_prop (OBJ_M_NO_STEAL, TRUE);
    add_prop (CONT_I_IN, TRUE);

    set_no_show_composite (TRUE);

    enable_commands ();
}

//-------------------------------------------------------------------

