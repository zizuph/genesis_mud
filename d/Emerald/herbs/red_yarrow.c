/* A yarrow. This herb will enhance the constitution
 * of anyone that eat it. It is found all over Earthsea.
 * Coded by Marisol (11/15/97)
 * Modified by Marisol (08/10/98) it will enhance cold resistance
 * It is found all over Emerald.
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_adj("red");
    set_herb_name("red yarrow");
    set_short("red flower");
    set_pshort("red flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A pleasant smelling red flower.\n");
    set_id_long("A Red Beauty yarrow. A very pretty and useful herb "+
        "found in medicinal garden. It is both use for the sick and "+
        "for cooking. The foliage is feathery green with a pleasant "+
        "smell when crushed. Red flowers are clustered in bunch of "+
        "flat heads. It is really good against cold weather.\n");

    set_ingest_verb("eat");
    set_find_diff(8);
    set_id_diff(50);
    set_effect(HERB_ENHANCING, "cold", 30);
    set_herb_value(940);
    set_decay_time(4000);
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
