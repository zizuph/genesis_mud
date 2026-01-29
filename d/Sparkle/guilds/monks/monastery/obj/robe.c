/*******************************************************************\
| ROBE.C                                                            |
\*******************************************************************/

/*
 * 99/02/?? Lilith	Created
 * 03/04/04 Arandir	Ported to new area and bugfixed
 * 03/12/23 Arandir     Made the robe color saving
 * 04/01/02 Arandir     Made multiword colors work
 * 04/03/06 Arandir     The robe was both recovering and autoloading
 *
 */

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_OBJ_CLOTHES_ARMOUR_BASE;

//-------------------------------------------------------------------

string m_robe_long ();
string m_robe_short ();

private string sRobeColor = "";

// Colors based on Calia eye colors by Maniac, extended somewhat.

string *asColors = ({
  "amber", "almond brown", "albino white", "amethyst",
  "amber brown", "aquamarine", "ashen", "black",
  "blue", "blood red", "brown", "bright blue",
  "bright green", "bright purple", "bright red", "bright yellow",
  "calico", "cerulean blue", "chestnut brown", "cinnamon",
  "cinder red", "coal black", "cloud grey", "crystal clear",
  "crimson red", "dark blue", "dark green", "dark",
  "dark brown", "dark grey", "dark yellow", "deep blue",
  "deep brown", "deep green", "deep purple", "ebony",
  "emerald green", "ember red", "forest green", "fiery red",
  "golden yellow", "green", "grey", "hazel green",
  "icy blue", "indigo", "ivory", "jet black",
  "light brown", "mahogany", "midnight black", "magenta",
  "ocean blue", "olive green", "pearly", "pink",
  "purple", "rainbow-hued", "red", "royal blue",
  "ruby red", "sapphire blue", "scarlet", "sienna",
  "silvery grey", "sky blue", "smoke grey", "snow white",
  "sorrel", "steel grey", "turquoise", "vermilion",
  "violet", "velvet black", "white", "walnut brown",
  "yellow", "light green" });

//-------------------------------------------------------------------

int m_set_adjective (string sAdjective)
{
  sRobeColor = sAdjective;
  remove_adj (query_adjs ());
  set_adj (({ "soft", "light" }) + explode (sAdjective, " "));
  return (member_array (sAdjective, asColors) >= 0);
}


void m_random_adjective ()
{
  m_set_adjective (asColors [random (sizeof (asColors))]);
}


string *m_get_adjectives ()
{
  return (sort_array (asColors));
}

//-------------------------------------------------------------------

string m_robe_long ()
{
  return ("It is a soft robe made from some light fabric.\n");
}

string m_robe_short ()
{
  return ((sRobeColor == "") ? ("robe") : (sRobeColor + " robe"));
}

//-------------------------------------------------------------------

void create_armour ()
{
  ::create_armour ();

  set_name  ("robe");

  set_short (&m_robe_short ());
  set_long  (&m_robe_long ());

  set_ac (random (3) + 1);
  set_af (this_object ());
  set_at (A_ROBE);

  add_prop (OBJ_I_VALUE, 250);
  add_prop (OBJ_I_WEIGHT, 1200);
  add_prop (OBJ_I_VOLUME, 650);
}

//-------------------------------------------------------------------

void init_recover (string sArgs)
{
  string sOriginal;
  string sAdjective;
  sscanf (sArgs, "%s:MONK:%s", sOriginal, sAdjective);
  ::init_recover (sOriginal);
  m_set_adjective (sAdjective);
}


string query_recover ()
{
  return (::query_recover () + ":MONK:" + sRobeColor);
}

//-------------------------------------------------------------------

