/*  Tunic worn by apprentices of the Thespian Guild
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/25/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("robe");
    set_adj(({"long","maroon"}));
    set_short("long maroon robe");
    set_long("It is a long maroon robe with a wide black strip from "+
             "the neck to the hem. An actor's mask is embroidered on "+
             "it.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  800);
}
