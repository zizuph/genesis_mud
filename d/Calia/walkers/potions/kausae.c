
/*
 * /d/Calia/walkers/potions/kausae.c
 *
 * modified from Karath's cerebal.c potion, by Jaacar November 1997
 */

#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>
#include <macros.h>
#include "defs.h"

public void
create_potion()
{
    set_potion_name("kausae");
    set_short("dark green potion");
    set_pshort("dark green potions");
    set_adj("dark");
    add_adj("green");

    /* Set the long description if identified. */
    set_id_long("This dark green potion appears to have some small bits of "+
        "green leaves floating around in it.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This dark green potion appears to have some type of green "+
        "plant leaves floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has a strong alcohol mixed with some type "+
        "green sea grass, some slimy green alga, salt, and ash.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol, soot, salt, "+
        "and has some sort of green leaves floating in it.\n");

    /* Set the smell if identified. */
    set_id_smell("This potion smells of strong alcohol mixed with ash "+
        "and salt.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of alcohol and soot with a bit of "+
        "salt.\n");

    /* How hard is it to identify? */
    set_id_diff(60);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(1200);

    /* Set the effect. */
    set_effect(HERB_SPECIAL, "", 0);
}

string
query_recover()
{
    return MASTER;
}

void
special_effect()
{
    object kausaeeffect;
    if (present("_kausae_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    kausaeeffect = clone_object(KAUSAE_POTION_OBJECT);
    kausaeeffect->set_remove_time(KAUSAE_TIME);
    kausaeeffect->move(this_player());
}

