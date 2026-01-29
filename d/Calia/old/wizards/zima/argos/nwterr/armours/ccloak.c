/*  a common cloak
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           10/15/96 Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#define COLOR ({"red","brown","black","white","green","blue","yellow"})
 
void create_armour() {
    string color=COLOR[(random(sizeof(COLOR)))];
    set_name("cloak");
    set_adj(({"long",color}));
    set_short("long "+color+" cloak");
    set_long("It is a common cloak made of "+color+" wool. It looks warm.\n");
    set_ac(9);
    set_at(TS_ROBE);
}
