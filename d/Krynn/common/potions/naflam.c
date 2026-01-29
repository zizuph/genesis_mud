/*
 * /d/Krynn/common/potions/naflam.c
 *
 * modified from Olorin's ipotion.c, by Teth Jan 1997
 */
#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

public void
create_potion()
{
    set_potion_name("naflam");
    set_id_long("This potion is an opaque purple. It seems that " +
        "the potion is a mixture of a soapy herb and a purple " +
        "herb, making for a potion that has synergistic effects, " +
        "of greater effect than the herbs taken alone.\n");
    set_unid_long("This potion is an opaque purple. You are not " +
        "absolutely sure what it does.\n");
    set_id_taste("The potion tastes of hot soap!\n");
    set_unid_taste("The potion tastes of hot alkali!\n");
    set_id_smell("The potion smells like fireweed.\n");
    set_unid_smell("The potion smells sweet, like a flower blossom.\n");
    set_id_diff(34);
    set_soft_amount(20);
    set_alco_amount(10);
    set_potion_value(213);

    set_effect(HERB_ENHANCING, "fire", 40);
    add_effect(HERB_ENHANCING, "acid", 40);
}
