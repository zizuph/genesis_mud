// Apron worn by ogre mommies
// Made by Boriska@Genesis Oct 1994

#include <wa_types.h>
#include <stdproperties.h>
#include <money.h>

inherit "/std/armour";

create_armour()
{
  set_name ("apron");
  set_short ("leather apron");
  add_adj ("leather");
  set_long ("Smelly apron which definetely needs some cleaning.\n");

  set_ac(13);
  set_at(A_WAIST);
}
