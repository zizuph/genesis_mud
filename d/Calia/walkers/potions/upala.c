
/*
 * /d/Calia/walkers/potions/upala.c
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
    set_potion_name("upala");
    set_short("cold clear potion");
    set_pshort("cold clear potions");
    set_adj("cold");
    add_adj("clear");

    /* Set the long description if identified. */
    set_id_long("This cold clear potion is a mixture of a strong "+
        "alcohol and an ice crystal.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This cold clear potion appears to have small "+
        "ice crystals floating throughout the clear liquid.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has the unmistakenable taste of strong "+
        "alcohol.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol.\n");

    /* Set the smell if identified. */
    set_id_smell("There strong smell of alcohol.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of a strong alcohol.\n");

    /* How hard is it to identify? */
    set_id_diff(40);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(747);

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
    object upalaeffect;
    if (present("_upala_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    upalaeffect = clone_object(UPALA_POTION_OBJECT);
    upalaeffect->set_remove_time(UPALA_TIME);
    upalaeffect->move(this_player());
}

