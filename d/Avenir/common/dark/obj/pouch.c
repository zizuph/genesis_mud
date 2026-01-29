// Pouch containing stones for magic square quest.
// Made by Boriska@Genesus, Nov 1994

inherit "/std/receptacle";

#include <stdproperties.h>

create_receptacle ()
{
  set_name ("pouch");
  set_pname ("pouches");
  add_prop (CONT_I_WEIGHT, 100);
  add_prop (CONT_I_VOLUME, 1000);
  add_prop (OBJ_I_VALUE,  50);
  add_prop (CONT_I_MAX_WEIGHT, 2000);
  add_prop (CONT_I_MAX_VOLUME, 2000);
}

void
set_color (string cl)
{
  set_short (cl + " pouch");
  set_pshort (cl + " pouches");
  set_long ("Small pouch made from " + cl + " leather.\n");
  add_adj (cl);
}
