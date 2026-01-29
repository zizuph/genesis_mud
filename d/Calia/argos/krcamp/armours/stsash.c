/*  Sash  worn by a Kretan Stratarch
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
    set_adj(({"red","silk","kretan"}));
    set_short("red silk sash");
    set_long("It is a long red sash made of silk, ornately embroidered "+
             "with military ensignias along its length.\n");
    set_ac(5);
    set_at(A_WAIST);
}
