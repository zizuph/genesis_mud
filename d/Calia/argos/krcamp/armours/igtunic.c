/*  Tunic worn by an imperial guard
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
    set_adj(({"long","black","kretan"}));
    set_short("long black tunic");
    set_long("It is a long black tunic made of silk. Its hem is trimmed "+
             "with military insignias and a small seven headed hydra is "+
             "embroidered on the front.\n");
    set_ac(5);
    set_at(A_ROBE);
}
