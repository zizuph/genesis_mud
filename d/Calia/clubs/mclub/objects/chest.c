/* MClub - chest to hold club objects                 (7/25/95) */
/* Found in the sacristry (rooms/shconsac)                     */
inherit "/std/receptacle";
#include <macros.h>
#include "defs.h"
#include "/sys/stdproperties.h";
 
void create_receptacle() {
    set_name("chest");
    set_adj("cedar");
    set_long(
       "It is a a long chest made of cedar, its aromatic wood "+
       "perfuming the chamber.\n");
 
    add_prop(CONT_I_WEIGHT,      20000);
    add_prop(CONT_I_MAX_WEIGHT, 700000);
    add_prop(CONT_I_VOLUME,      12000);
    add_prop(CONT_I_MAX_VOLUME, 700000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_I_NO_GET,1);
}
