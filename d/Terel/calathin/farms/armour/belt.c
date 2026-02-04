// belt.c
// Tomas Feb 2000

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("belt");
  set_short("thick leather belt");
  add_adj(({"thick", "leather"}));
  set_long ("A thick leather belt.\n");
  set_ac (10);
  set_am(({ 0, 0, 0}));
  set_at (A_WAIST);
}