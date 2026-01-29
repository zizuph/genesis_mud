/*
 * red pepper, also known as cayenne pepper
 *
 * By Arren, August 94
 */
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
    set_name("fruits");
    add_name(({ "fruit", "narusse_ingr1", "spice", }));
    set_adj("handful");
    add_adj(({ "of", "red" }));
    set_herb_name("pepper");
    set_short("handful of small red fruits");
    set_pshort("handfuls of small red fruits");
    set_ingest_verb("eat");
    set_unid_long(
        "This is a handful of small red fruits.\n");
    set_id_long(BSN(
        "This is a handful of red pepper. It's the ripe fruit of the plant "+
        "of genus Capsicum. The fruit is usually dried and then powdered. "+
        "The powder is then used to flavour dishes. The spice is known "+
        "for its hot taste. "));

    set_effect(HERB_SPECIAL, "pepper", 50);
    add_effect(HERB_POISONING, "pepper", 25);
    set_poison_damage(({POISON_FATIGUE, 1, POISON_HP, 5, POISON_STAT, SS_CON,
                        POISON_STAT, SS_STR}));

    set_id_diff(14);
    set_find_diff(5);

    set_decay_time(5400);
    set_herb_value(72);
    set_dryable();
}

void
special_effect()
{
    if (effects[1] != "pepper")
    {
        write("You don't feel any effect.\n");
        return;
    }

    write("Your throat starts to burn, your eyes start to water.\n");
    TP->set_soaked(TP->query_soaked() - (500 * effects[2]) / 100);
}

