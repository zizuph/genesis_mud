#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <macros.h>
#include <herb.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/* 
 * This herb is made to look like the Frostheal herb which makes people
 * cold-resistant. The only real difference is that this one will poison
 * the player, decreasing his/her con-stat, maybe even to death.
 * It is deliberately made easier to find than the sought-for Frostheal. >:-)
 *    Elessar.
 */

void
create_herb()
{
    set_name("leaf");
    add_name("herb");
    set_adj(({"gray", "fuzzy"}));
    set_herb_name("madwort");
    set_short("gray fuzzy leaf");
    set_pname(({"leaves", "herbs"}));
    set_pshort("gray fuzzy leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a small, grayish fuzzy leaf from a "
      + "diminutive creeping plant. Its virtue is unknown."));
    set_id_long(BSN("This grayish fuzzy leaf comes from the Madwort plant, "
      + "a plant found at high elevations. When eaten it will decrease "
      + "your physical health, maybe even killing you!"));

    set_effect(HERB_POISONING, "madwort", 120);
    set_poison_damage(({POISON_HP, 50, POISON_FATIGUE, 40, POISON_MANA, 20,
      POISON_STAT, SS_CON}));
    set_id_diff(69);
    set_find_diff(3);
    set_decay_time(5400);
    set_herb_value(108);
    set_dryable();
}

