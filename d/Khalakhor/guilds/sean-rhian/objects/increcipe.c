/*
** A piece of parchment containing the recipe for making incense
*/
inherit "/std/scroll";
#include "defs.h"
#include <stdproperties.h>
 
void create_scroll() {
    set_name("parchment");
    add_name(({"piece of parchment","recipe"}));
    set_short("piece of parchment");
    set_long("It is a piece of parchment with a recipe for incense "+
             "written on it.\n");
 
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 75);
 
    set_file(SR_OBJ+"increcipe.txt");
}
