#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berries");
    add_name("handful");
    add_name( ({ "sulambar_ingr1" }) );
    set_adj(({"green", "of", "handful"}));
    set_herb_name("hemlock");
    set_short("handful of green berries");
    set_pshort("handful of green berries");
    set_ingest_verb("eat");
    set_unid_long("This is a handful of green berries.\n");
    set_id_long(BSN("This is a handful of green berries of the hemlock plant. " +
      "Hemlock (Conium maculatum) is a poisonous biennial herb of the " +
      "parsley family. It has a hollow, many-branched stem, purple spotted, finely " +
      "divided leaves, and clusters of white flowers. A sufficient dose of the green " +
      "fruits will paralyze the circulatory system."));

    set_effect(HERB_POISONING, "paralyze", 30 + random(21));
    set_poison_file(HERB_DIR + "hemlock_effect");
    set_poison_damage(({POISON_HP,300, POISON_STAT,SS_STR,POISON_STAT,SS_STR,
        POISON_STAT,SS_DEX,POISON_STAT,SS_DEX,POISON_STAT, SS_CON,
        POISON_STAT,SS_DIS,POISON_FATIGUE,100,}));
    set_id_diff(35);
    set_find_diff(5);
    set_decay_time(5400);
    set_herb_value(120);
}

