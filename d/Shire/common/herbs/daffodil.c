/*
 * Daffodil
 * Finwe, March 2003
 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

void
create_herb()
{
    set_name("daffodil");
    add_name("bulb");
    set_adj(({"large","scaly"}));
    set_short("large scaly bulb");
    set_herb_name("daffodil");
    set_id_long("This is the bulb of a daffodil plant. The bulb is large " +
        "and scaly, with anoff white color. The bulb produces tall " +
        "slender grass-like leaves with trumpet shaped flowers. The bulb " +
        "is rumoured to be poisonous, and grows in moist soil.\n");
    set_unid_long("This is a large scaly bulb.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(3);
    set_effect(HERB_POISONING, "daffodil", 15);
    set_poison_damage(({POISON_HP, 25, POISON_FATIGUE, 15, POISON_MANA, 20,
      POISON_STAT, SS_CON}));
    set_decay_time(2500);
    set_herb_value(450);
    set_dryable();

}
