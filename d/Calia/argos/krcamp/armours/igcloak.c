/*  Cloak worn by an Imperial guard
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
    set_adj(({"long","black","kretan"}));
    set_short("long black cloak");
    set_long("It is a long black cloak made of silk, ornately embroidered "+
             "with military ensignias along its border with the emblem "+
             "of a seven-headed hydra sewn with silver thread on the back. "+
             "A silver clip holds it around the neck where it is worn.\n");
    set_ac(15);
    set_at(A_NECK);
}
