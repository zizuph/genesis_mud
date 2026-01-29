/* A paramol fruit. This fruit when eat it will
 * make you feel less tired. Found only in Gont.
 * Coded by Marisol (11/20/97)
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("fruit");
    set_pname(({"fruits", "paramols"}));
    add_adj("yellow");
    set_herb_name("paramol");
    set_short("yellow fruit");
    set_pshort("yellow fruits");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A yellow and fragant fruit from a tree.\n");
    set_id_long("A paramol! This fruit, from the tree of the same "+
      "name, grown in the high hills of Gont. Goats are very fond "+
      "of this fruit, and goat herders need to watch them not to "+
      "eat too many or they will be all night frolicking in the "+
      "pastures.\n");

    set_ingest_verb("eat");
    set_find_diff(5);
    set_id_diff(10);
    set_effect(HERB_HEALING, "fatigue", 20);
    set_herb_value(125);
    set_decay_time(5000);
}
