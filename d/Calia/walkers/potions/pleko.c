
/*
 * /d/Calia/walkers/potions/pleko.c
 *
 * modified from Olorin's cerebal.c potion, which was modified by Teth, 
 * which was then found by Jaacar in Karath's directory - November 1997
 *
 */

#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>
#include <macros.h>
#include "defs.h"

public void
create_potion()
{
    set_potion_name("pleko");
    set_short("green-leafy clear potion");
    set_pshort("green-leafy clear potions");
    set_adj("green-leafy");
    add_adj("clear");

    /* Set the long description if identified. */
    set_id_long("A green-leafy clear potion, this is a mixture of a strong "+
        "alcohol and a finely ground green leaf.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This clear potion appears to have some type of finely "+
        "ground green plant floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has a strong alcohol mixed with some type "+
        "of green sea leaf.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol with "+
        "some type of green leaf.\n");

    /* Set the smell if identified. */
    set_id_smell("This potion smells of a strong alcohol.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of alcohol.\n");

    /* How hard is it to identify? */
    set_id_diff(45);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(925);

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
    object plekoeffect;
    if (present("_pleko_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    plekoeffect = clone_object(PLEKO_POTION_OBJECT);
    plekoeffect->set_remove_time(PLEKO_TIME);
    plekoeffect->move(this_player());
}

