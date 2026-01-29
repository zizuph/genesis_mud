/*
 * Signet ring of Gavriel the Mystic Cantor 
 */
#include <stdproperties.h>
#include <wa_types.h>
#include <const.h>

inherit "/std/armour";

public void
create_armour()
{
   set_name("ring");
   add_name("signet");
   add_name("_mystic_signet");
 
   set_adj(({"arcane", "gold", "signet"}));
   set_at(A_ANY_FINGER);
   set_ac(5);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 20);
   add_prop(OBJ_I_VOLUME, 5);
   set_short("arcane gold signet ring");   
   set_long(
      "Golden and luminous, this arcane ring is a signet. Thus banded " +
      "with a mysterious seal. Upon the seal are seven stars, a serpent " +
      "and a few strange characters.\n");
}
