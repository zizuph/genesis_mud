/*  Sash  worn by an imperial guard
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/96  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("sash");
    set_adj(({"black","silk","kretan"}));
    set_short("black silk sash");
    set_long("It is a long black sash made of silk, ornately embroidered "+
             "with military ensignias along its length.\n");
    set_ac(5);
    set_at(A_WAIST);
}
