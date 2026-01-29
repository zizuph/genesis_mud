/* Manor's Garden white rose
 * Coded by Marisol (10/29/97)
 * This flower if smells it will clear your mind..
 * For use in the Manor's Garden in Re Albi
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flowers");
    add_name("bunch of white flowers");
    add_pname("bunches of white flowers");
    add_adj("bunch of white");
    set_herb_name("snowy angels");
    set_short("bunch of white flowers");
    set_pshort("bunch of white flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A sweet-smelling bunch of white roses "+
      "from a rosebush.\n");
    set_id_long("A bunch of Snowy Angels. These small roses are "+
      "famous for their magical properties. Their sweet aroma "+
      "clears the tired mind and uplifts the soul. "+
      "It is rumoured that these roses are only found in "+
      "the Manor's garden in Re Albi these days.\n");

    set_ingest_verb("sniff");
    set_find_diff(5);
    set_id_diff(10);
    set_effect(HERB_HEALING, "mana", 15);
    set_herb_value(506);
    set_decay_time(5000);
    set_dryable();
}

string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
}
void
int_recover(string arg)

{
    init_herb_recover(arg);
}
