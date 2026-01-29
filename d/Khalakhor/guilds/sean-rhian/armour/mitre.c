/*
** Mitre - head gear of head haunchos
** Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/5/97   Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
 
string color="purple";  /* default color purple */
 
void set_color(string col) {
    color=col;
    set_adj(color);
    set_short(color+" mitre");
    set_long("It is a "+color+" mitre, a religious headress consisting "+
             "of two arched pieces rounded and connected together at the "+
             "bottom to form a band. It is embroidered with three "+
             "interlocking circles on the front, while two "+color+
             " bands hang down from the back.\n");
}
 
void create_armour() {
    set_name("mitre");
    set_color(color);
    set_ac(5);
    set_at(A_HEAD);
}
