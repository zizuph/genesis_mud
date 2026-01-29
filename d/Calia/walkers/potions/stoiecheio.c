
/*
 * /d/Calia/walkers/potions/stoiecheio.c
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
    set_potion_name("stoiecheio");
    set_short("purple-speckled grey potion");
    set_pshort("purple-speckled grey potions");
    set_adj("purple-speckled");
    add_adj("grey");

    /* Set the long description if identified. */
    set_id_long("A purple-speckled grey potion, this appears to be a mixture "+
        "of ash, some type of strong alcohol, and purple flower petals.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This grey potion appears to have some type of finely "+
        "ground purple flower petals floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has a strong alcohol mixed with some type "+
        "of purple flower petals and ash.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol with "+
        "some type of sooty material and purple flower petals.\n");

    /* Set the smell if identified. */
    set_id_smell("This potion smells of strong alcohol mixed with ash.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of alcohol and soot.\n");

    /* How hard is it to identify? */
    set_id_diff(55);

    /* What is the amount of liquid in mL? */
    set_soft_amount(70);

    /* How much alcohol in the potion? */
    set_alco_amount(50);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(1100);

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
    object stoiecheioeffect;
    if (present("_stoiecheio_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    stoiecheioeffect = clone_object(STOIECHEIO_POTION_OBJECT);
    stoiecheioeffect->set_remove_time(STOIECHEIO_TIME);
    stoiecheioeffect->move(this_player());
}

