/*
 * /d/Gondor/common/herbs/handasse.c
 *
 * A herb that enhances intelligence (Quenya: handasse)
 *
 * Olorin, July 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("mushroom");
    add_name("nifarist_ingr1");
    set_adj(({"green-yellow", "small","green", "yellow"}));
    set_herb_name("handasse");
    set_short("small green-yellow mushroom");
    set_pshort("small green-yellow mushrooms");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a small green-yellow mushroom with a " +
        "narrow head on a dark stalk. It looks poisonous."));
    set_id_long(BSN("This is a small green-yellow mushroom with a " +
        "narrow head on a dark stalk, known as Handasse. Even though " +
        "it looks quite poisonous it can be eaten without any harm. " +
        "It is said that eating it can even make you more perceptive " +
        "and speed the processes of the mind. It has been found in " +
        "many places in Middle Earth, but it is most common in Gondor."));

    set_effect(HERB_ENHANCING, "int", 55);
    set_id_diff(56);
    set_find_diff(3);
    set_decay_time(5400);
    set_herb_value(864);
    set_dryable();
}

