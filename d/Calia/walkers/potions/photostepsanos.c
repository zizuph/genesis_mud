
/*
 * /d/Calia/walkers/potions/photostepsanos.c
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
    set_potion_name("photostepsanos");
    set_short("cloudy yellow potion");
    set_pshort("cloudy yellow potions");
    set_adj("cloudy");
    add_adj("yellow");

    /* Set the long description if identified. */
    set_id_long("This cloudy yellow potion appears to be a mixture of "+
        "strong alcohol and some type of yellow alga.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This cloudy yellow potion has some type of alga floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has a strong alcohol mixed with some type "+
        "of yellow sea alga.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol with "+
        "some type of yellow alga.\n");

    /* Set the smell if identified. */
    set_id_smell("This potion smells of a strong alcohol.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of alcohol.\n");

    /* How hard is it to identify? */
    set_id_diff(50);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(1000);

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
    object photostepsanoseffect;
    if (present("_photostepsanos_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    photostepsanoseffect = clone_object(PHOTOSTEPSANOS_POTION_OBJECT);
    photostepsanoseffect->set_remove_time(PHOTOSTEPSANOS_TIME);
    photostepsanoseffect->move(this_player());
}

