
/*
 * /d/Calia/walkers/potions/optasia.c
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
    set_potion_name("optasia");
    set_short("green-flecked grey potion");
    set_pshort("green-flecked grey potions");
    set_adj("green-flecked");
    add_adj("grey");

    /* Set the long description if identified. */
    set_id_long("This potion appears to have small green flecks floating "+
        "in a light grey liquid.\n");

    /* Set the long description if unidentified. */
    set_unid_long("This light grey liquid has some sort of green flecks "+
        "floating in it.\n");

    /* Set the taste if identified. */
    set_id_taste("This potion tastes of sooty water.  The green flecks "+
        "taste like some type of lettuce.\n");

    /* Set the taste if unidentified. */
    set_unid_taste("This potion tastes of sooty water with chewy green "+
        "leaves floating in it.\n");

    /* Set the smell if identified. */
    set_id_smell("The potion smells of ash.\n");

    /* Set the smell for those who can't identify it. */
    set_unid_smell("The potion smells sooty.\n");

    /* How hard is it to identify? */
    set_id_diff(35);

    /* What is the amount of liquid in mL? */
    set_soft_amount(30);

    /* How much alcohol in the potion? */
    set_alco_amount(0);

    //* How much is the potion worth? (5 gold) */
    set_potion_value(675);

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
    object optasiaeffect;
    if (present("_optasia_potion_object_",this_player()))
    {
        write("You feel no effect.\n");
        return;
    }
    seteuid(getuid());
    optasiaeffect = clone_object(OPTASIA_POTION_OBJECT);
    optasiaeffect->set_remove_time(OPTASIA_TIME);
    optasiaeffect->move(this_player());
}

