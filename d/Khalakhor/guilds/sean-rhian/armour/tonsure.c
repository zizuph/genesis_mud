/*
** Tonsure - skull cap
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
    set_short(color+" tonsure");
    set_long("It is a small round "+color+" skull cap.\n");
}
 
void create_armour() {
    set_name("tonsure");
    set_color(color);
    set_ac(5);
    set_at(A_HEAD);
}
