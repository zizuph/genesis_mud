/* A ruined version of Leech for the quest, the power (and jewel) have
 * been stripped from this blade by a player questing (or just
 * feeling mean).
 * 16 July, 1994  Mayhem
 */
inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h" 

void create_weapon()
{
  set_name("leech");
  add_name(({"sword","scimitar"}));
  add_name("_shire_magebane");
  set_adj(({"sharp","black","blackened","jagged","wavy"}));
  set_short("jagged black scimitar");
  set_long("A sharp, blackened scimitar with a jagged, wavy blade "+
    "and hide-wrapped hilt. The blade is forged of an unknown "+
    "steel alloy, blackened to eliminate all reflections. The hide "+
    "wrap on the hilt is still covered with numerous bristles from "+
    "the boar it came from. An empty setting in the hilt seems "+
    "to yearn darkly for its component.\n");
  set_default_weapon(25,15,W_SWORD,W_SLASH|W_IMPALE,W_NONE,TO);
  set_pm(({-2,2,0}));
  set_likely_dull(1);
  set_likely_corr(2);
  set_likely_break(1);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(15,W_SWORD)+random(501));
  add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,15)-random(51));
}


string jewel_desc()
{
  if((MENT_STATS(TP)-(TP->query_intoxicated()/2))<275+random(26))
  {
/*
    TP->eat_food(-(query_stuffed()/2));
*/
    say(QCTNAME(TP)+" wrenches "+HIS_HER(TP)+" eyes away from "+
      "whatever "+HE_SHE(TP)+" was looking at, "+
      "and proceeds to lose part of "+HIS_HER(TP)+" dinner.\n");
    return "The pulsing, shifting jewel seems to draw part of "+
      "your very soul into its inner depths.  With a start, "+
      "you wrench your gaze away, but not before "+
      "becoming so nauseated you lose some of your "+
      "dinner.\n";
  }
  return "The dark red jewel appears to be quite valuable, but "+
    "also an integral part of the weapon, with no gaps or weaknesses "+
    "visible in its setting.  The jewel pulses and shifts within "+
    "the hilt, and for just a second, you can almost feel "+
    "it calling to you.\n";
}


int wield()
{
  WRITEN("You wrap your hand around the hilt of the "+short()+".");
  SAY(" wields the "+short()+".");
  return 1;
}

int unwield()
{
  object wielder = query_wielded();
  wielder->catch_msg("You release your grip upon the "+short()+".\n");
  say(QCTNAME(wielder)+" unwields the "+short()+".\n");
  return 1;
}


