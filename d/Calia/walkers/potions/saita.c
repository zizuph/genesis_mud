
/*
 * /d/Calia/walkers/potions/saita.c
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
    set_potion_name("saita");
    set_short("smelly yellowish potion");
    set_pshort("smelly yellowish potions");
    set_adj("smelly");
    add_adj("yellowish");

    /* Set the long description if identified. */
    set_id_long("A smelly yellowish potion, this is a mixture of a strong "+
        "alcohol, a fine yellow powder and white crystals.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This smelly yellowish potion appears to have small "+
        "particles of yellow powder as well as white crystals floating "+
        "throughout the yellowish liquid.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion has the unmistakenable taste of sulphur "+
        "mixed with some type of strong alcohol and a bit of salt.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("The potion tastes of a strong alcohol with "+
        "a bit of salt mixed in.\n");

    /* Set the smell if identified. */
    set_id_smell("The strong smell of sulphur is apparent as well as a hint "+
        "of salt water.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells of rotten eggs, strong alcohol, "+
        "and a bit of salt.\n");

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
    object saitaeffect;
    if (present("_saita_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    saitaeffect = clone_object(SAITA_POTION_OBJECT);
    saitaeffect->set_remove_time(SAITA_TIME);
    saitaeffect->move(this_player());
}

