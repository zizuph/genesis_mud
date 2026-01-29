
/*
 *rock.c
 *Used in a ferret quest to find the 'missing' dead ferrets.
 *
 *Ares July 2004
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("rock");
    add_name("_quest_rock_");
    set_adj("gravestone");

    set_short("gravestone rock");
    set_pshort("gravestone rocks");
    set_long("A small rock that once served as a gravestone. It reads 'GEORGE "+
        "2 YEARS OLD'.  \n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);

}

