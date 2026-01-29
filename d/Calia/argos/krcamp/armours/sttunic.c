/*  Tunic worn by kretan stratarchs
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("tunic");
    set_adj(({"long","silver","kretan"}));
    set_short("long silver tunic");
    set_long("It is a long silver tunic made of silk. Its hem is trimmed "+
             "with military insignias and a small seven headed hydra is "+
             "embroidered on the front.\n");
    set_ac(5);
    set_at(A_ROBE);
}
