
/*
 * paper.c
 * Used in the 'missing' dead ferrets quest.
 * 
 * Ares, 2004
 *
 */

inherit "/std/object";

#include <stdproperties.h>

string fname;

void
create_object()
{
    set_name("paper");
    add_name("_quest_paper_");
    set_adj("official-looking");

    set_short("official-looking paper");
    set_pshort("official-looking papers");
    set_long("This paper is titled 'Rodent Death Certificate' and lists the "+
       "name as @@query_ferret_name@@ \n");

    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}

void
set_ferret_name(string str)
{
    fname = str;
}


query_ferret_name()
{
    return fname;
}

