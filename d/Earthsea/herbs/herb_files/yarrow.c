/*
 * A yarrow. This herb will enhance the constitution
 * of anyone that eat it. It is found all over Earthsea.
 * Coded by Marisol (11/15/97)
 * Copyright (c) Marisol Ramos 1997
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>

public void
create_herb()
{
    set_name("flower");
    add_adj("pinkish");
    add_pname("flowers");
    set_herb_name("yarrow");
    set_short("pinkish flower");
    set_pshort("pinkish flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A strong smelling pink flower.\n");
    set_id_long("A yarrow! This is one of the jewels in any village " +
        "witch's kitchen. This beautiful, aromatic and also tasty " +
        "herb is famous for its medicinal uses for strengthening the " +
        "sick and weak of body.\n");
    set_ingest_verb("eat");
    set_find_diff(8);
    set_id_diff(50);
    set_effect(HERB_ENHANCING, "con", 30);
    set_herb_value(940);
    set_decay_time(4000);
    set_dryable();
}
