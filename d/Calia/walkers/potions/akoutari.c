
/*
 * /d/Calia/walkers/potions/akoutari.c
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
    set_potion_name("akoutari");
    set_short("smelly brown potion");
    set_pshort("smelly brown potions");
    set_adj("smelly");
    add_adj("brown");

    /* Set the long description if identified. */
    set_id_long("A smelly brown potion, this is a mixture of water, sulphur "+
        "and fucus.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This smelly brown potion appears to have small particles "+
        "of yellow powder floating amoungst a greenish-brown water.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has the unmistakenable taste of sulphur, with "+
        "a hint of salt water mixed in.  Judging by the greenish-brown "+
        "alga particles, you concluded it is a mixture of water, sulphur "+
        "and fucus.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes slightly of salt water.\n");

    /* Set the smell if identified. */
    set_id_smell("The strong smell of sulphur is apparent as well as a hint "+
        "of salt water.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of rotten eggs and salt water.\n");

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
    object akoutarieffect;
    if (present("_akoutari_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    akoutarieffect = clone_object(AKOUTARI_POTION_OBJECT);
    akoutarieffect->set_remove_time(AKOUTARI_TIME);
    akoutarieffect->move(this_player());
}

