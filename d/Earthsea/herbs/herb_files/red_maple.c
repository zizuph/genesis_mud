/*
 * Coded by Ckrik June 1998
 *  for decoration in Oranea, quest, and possible magical value.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

public void
create_herb()
{
    set_name("leaf");
    set_pname("leaves");
    add_name("herb");
    add_pname("herbs");
    add_name("maple leaf");
    add_pname("maple leaves");
    add_adj("red");
    set_short("red seven-pointed leaf");
    set_pshort("red seven-pointed leaves");
    set_herb_name("red maple leaf");
    set_unid_long("A red seven-pointed leaf. It is very beautiful.\n");
    set_id_long("This is the leaf of a red maple tree. " +
        "The leaves of such a tree stays " +
        "red even during spring and summer and " +
        "falls in autumn. People often collect " +
        "these leaves just for its beauty.\n");
    set_id_diff(5);
    set_find_diff(0);
    set_ingest_verb("eat");
    set_herb_value((5 * 10) + (10 * 10)/4);
    set_decay_time(3000);
}
