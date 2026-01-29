
/*
 * /d/Calia/walkers/potions/nero.c
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
    set_potion_name("nero");
    set_short("watery green potion");
    set_pshort("watery green potions");
    set_adj("watery");
    add_adj("green");

    /* Set the long description if identified. */
    set_id_long("A watery green potion, this is a mixture of water "+
        "and poison ivy.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This watery green potion appears to have finely "+
        "ground leaves floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("The potion tastes of poison ivy mixed " +
        "with water.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes like watery, leafy tea.\n");

    /* Set the smell if identified. */
    set_id_smell("The potion smells of poison ivy.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of wet leaves.\n");

    /* How hard is it to identify? */
    set_id_diff(25);

    /* What is the amount of liquid in mL? */
    set_soft_amount(30);

    /* How much alcohol in the potion? */
    set_alco_amount(0);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(720);

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
    object pyroeffect;
    if (present("_nero_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    pyroeffect = clone_object(NERO_POTION_OBJECT);
    pyroeffect->set_remove_time(NERO_TIME);
    pyroeffect->move(this_player());
}

