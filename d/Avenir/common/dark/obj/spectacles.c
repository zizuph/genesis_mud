// -*-C++-*-
// Josen's spectacles, for dark/mon/archaelogist
// Made by Boriska Feb 10 1995

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
  set_name("spectacles");
  set_pname("spectacles");
  set_short ("golden-rimmed spectacles");
  set_pshort ("golden-rimmed spectacles");
  add_adj (({"golden-rimmed", "golden"}));
  set_long ("The spectacles are made of thick golden wire connecting\n" +
	    "two strong lenses.\n" );
  set_ac (5);
  set_at (A_HEAD);
  add_prop (OBJ_I_WEIGHT, 100);
  add_prop (OBJ_I_VOLUME, 50);
  add_prop (OBJ_I_VALUE, 300);
}

public string
wear_how(int location)
{
  if (this_player() == wearer)
    return " over your nose";
  else
    return " over " + wearer->query_possessive() + " nose";
}
  

