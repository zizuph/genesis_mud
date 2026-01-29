
/*
 * /d/Calia/walkers/potions/pichno.c
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
    set_potion_name("pichno");
    set_short("cold brown potion");
    set_pshort("cold brown potions");
    set_adj("cold");
    add_adj("brown");

    /* Set the long description if identified. */
    set_id_long("A cold brown potion, this is a mixture of water, an ice "+
        "crystal and fucus.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This cold brown potion appears to have small particles "+
        "of ice floating amoungst a greenish-brown water.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has the unmistakenable taste of salt water.  " +
        "Judging by the greenish-brown alga particles and the temperature " +
        "of the water, you concluded it is a mixture of water, and ice "+
        "crystal and fucus.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes slightly of salt water.\n");

    /* Set the smell if identified. */
    set_id_smell("The smell of salt water is faint in this potion.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells slightly of salt water.\n");

    /* How hard is it to identify? */
    set_id_diff(25);

    /* What is the amount of liquid in mL? */
    set_soft_amount(30);

    /* How much alcohol in the potion? */
    set_alco_amount(0);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(740);

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
    object pichnoeffect;
    if (present("_pichno_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    pichnoeffect = clone_object(PICHNO_POTION_OBJECT);
    pichnoeffect->set_remove_time(PICHNO_TIME);
    pichnoeffect->move(this_player());
}

