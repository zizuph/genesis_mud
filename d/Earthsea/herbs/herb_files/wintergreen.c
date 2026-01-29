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
    add_name("wintergreen", "wintergreen leaf");
    set_adj("oval-shaped");
    add_adj(({"green", "evergreen"}));
    set_pname(({"leaves", "herbs", "wintergreens", "wintergreen leaves"}));
    set_herb_name("wintergreen leaf");
    set_short("oval-shaped leaf");
    set_pshort("oval-shaped leaves");
    add_name("herb");
    set_unid_long("A dark, evergreen oval-shaped leaf " +
        "with a long vinelike stem.\n");
    set_id_long("A wintergreen leaf, which grows on " +
        "a vinelike plant, the Gaultheria procumbens, " +
        "and is particularly common in mountain forests. " +
        "The oil from the fragrant leaf is known to " +
        "have medicinal properties.\n");
    set_id_diff(25);
    set_find_diff(3);
    set_effect(HERB_SPECIAL, "", 25);
    set_ingest_verb("eat");
    set_herb_value((5 * 25) + (25 * 25)/4);
    set_decay_time(3000);
}

public void
special_effect()
{
    write("As you eat the leaf, a cool refreshing feeling comes over you.\n" +
        "You feel healthier.\n");
    this_player()->heal_hp(25);
}
