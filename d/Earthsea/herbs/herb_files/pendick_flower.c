/*A Pendick-flower. This flower when sniffs will
 *enhance your wisdom. It is found all over Earthsea.
 *Coded by Marisol (11/17/97)
 *Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_adj("red");
    add_pname("flowers");
    set_herb_name("pendick-flower");
    set_short("red flower");
    set_pshort("red flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A beautiful red flower.\n");
    set_id_long("A red flower from a Pendick tree. The flower of "+
      "this tree is rumored to enhance the memory of forgotten "+
      "days, bringing bliss and sometimes wisdom.\n");

    set_ingest_verb("sniff");
    set_find_diff(3);
    set_id_diff(6);
    set_effect(HERB_ENHANCING, "wis", 10);
    set_herb_value(38);
    set_decay_time(2000);
    set_dryable();
}
