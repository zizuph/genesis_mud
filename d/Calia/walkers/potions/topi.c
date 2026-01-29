
/*
 * /d/Calia/walkers/potions/topi.c
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
    set_potion_name("topi");
    set_short("redish-brown potion");
    set_pshort("redish-brown potions");
    set_adj("redish-brown");

    /* Set the long description if identified. */
    set_id_long("A redish-brown potion, this is a mixture of a strong "+
        "alcohol and a coarsly ground redish-brown alga.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This redish-brown potion appears to have small coarse "+
        "redkish-brown particles of alga floating throughout it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has a strong alcohol mixed with some type "+
        "of redkish-brown alga giving it a gritty taste.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol with "+
        "some type of gritty substance.\n");

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
    set_potion_value(950);

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
    object topieffect;
    if (present("_topi_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    topieffect = clone_object(TOPI_POTION_OBJECT);
    topieffect->set_remove_time(TOPI_TIME);
    topieffect->move(this_player());
}

