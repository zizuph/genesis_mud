/*
 * coded by Amelia 4/12/97
 *  for use in Roke Ten Alders area 
 *  herb with possible medicinal uses
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>

public void
create_herb()
{
    set_name("leaf");
    add_name(({"spinach leaf", "spinach"}));
    set_pname("leaves");
    add_adj(({"dark", "dark green", "green", "spinach"}));
    set_herb_name("spinach");
    set_short("dark green leaf");
    set_pshort("dark green leaves");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A dark green wrinkled leaf. It comes " +
        "from a small bush that grows in the ground.\n");
    set_id_long("A spinach leaf. It is a highly " +
        "nutricious plant, or Spinacia oleracea, " +
        "which is rumoured to increase one's " +
        "strength if eaten regularly.\n");
    set_id_diff(20);
    set_find_diff(3);
    set_effect(HERB_ENHANCING, "str", 20);
    set_ingest_verb("eat");
    set_herb_value((5 * 20) + (20 * 20)/4);
    set_decay_time(3000);
    set_dryable();
}
