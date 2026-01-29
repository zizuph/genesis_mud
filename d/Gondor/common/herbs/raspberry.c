#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
  set_name("berry");
  set_short("little red berry");
  set_pshort("little red berries");
  set_adj(({"little", "red", "translucent", "glistening", }));
  set_herb_name("red raspberry");
  set_id_long(BSN("This red raspberry is a member of the genus Rubus. "+
    "The berry is glistening and translucent, with many small seeds and tangy flavour. "+
    "The red raspberry has a mild nutrative and restorative effect."));
  set_unid_long("This red berry looks like an ordinary berry. You don't know "+
    "what it's for.\n");
  set_ingest_verb("eat");

  set_effect(HERB_HEALING, "panic", 2);

  set_id_diff(4);
  set_find_diff(3);

  set_decay_time(3600);

  set_herb_value(18);

  set_amount(5);
  add_prop(OBJ_I_WEIGHT, 5);
  add_prop(OBJ_I_VOLUME, 5);
}

