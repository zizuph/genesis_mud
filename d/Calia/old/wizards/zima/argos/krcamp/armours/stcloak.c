/*  Cloak worn by a Kretan Stratarch
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/96  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("cloak");
    set_adj(({"long","red","kretan"}));
    set_short("long red cloak");
    set_long("It is a long red cloak made of silk, ornately embroidered "+
             "with military ensignias along its border with the emblem "+
             "of a seven-headed hydry sewn with gold thread on the back. "+
             "A gold clip holds it around the neck where it is worn.\n");
    set_ac(15);
    set_at(A_NECK);
}
