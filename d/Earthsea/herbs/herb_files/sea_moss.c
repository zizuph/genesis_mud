/* Coded by Ckrik June 1998. */

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>

public void
create_herb()
{
    set_name("moss");
    set_pname("mosses");
    add_name("herb");
    add_pname("herbs");
    add_name("sea moss");
    add_pname("sea mosses");
    set_adj("slippery");
    add_adj("brown");
    set_short("slippery brown moss");
    set_pshort("slippery brown moss");
    set_herb_name("sea moss");
    set_unid_long("A slippery brown vine.\n");
    set_id_long("This is sea moss, found growing only " +
        "in the sea. This moss must " +
        "have been washed up onto a beach " +
        "by the waves. It seems to be of " +
        "the variety that has some medicinal value.\n");
    set_effect(HERB_HEALING, "hp", 10);
    set_id_diff(45);
    set_find_diff(5);
    set_ingest_verb("eat");
    set_herb_value((5 * 10) + (10 * 10)/4);
    set_decay_time(3000);
    set_dryable();
}
