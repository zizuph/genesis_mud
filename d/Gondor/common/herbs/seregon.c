 /*
  * seregon.c
  *
  * modified from tuo.c by Elessar
  * Olorin, April 1793
  * from tuo.c zephram November 1793
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("flowers");
    add_name(({"bunch", "flower", "spice","_spice"}));
    set_adj(({"hardy", "bunch","of","small","pointed",
              "blood-red","red","small"}));
    set_herb_name("seregon");
    set_short("bunch of small hardy blood-red flowers");
    set_pshort("bunches of small hardy blood-red flowers");
    set_ingest_verb("chew");
    set_unid_long("This is a bunch of small hardy blood-red creeping flowers.\n");
    set_id_long(BSN("This is a bunch of blood-red seregon flowers. "
      + "Seregon is said to have grown at the summit of the old dwarven "
      + "delving-hill Amon Rudh. The dwarves believed that chewing the "
      + "leaves and flowers of seregon would protect them against sorcery. "
      + "The scent of the flower carries from far off the fragrance of "
      + "Beleriand during the Elder Days before it foundered beneath the waves."));

    set_effect(HERB_ENHANCING, "magic", 10);

    set_id_diff(40);
    set_find_diff(7);
    set_decay_time(6000);
    set_herb_value(888);
    set_dryable();
}

