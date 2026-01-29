/*  Spear of a Kretan Sentry
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/25/96  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("spear");
    set_adj(({"Kretan","long","kretan","black-shafted","black"}));
    set_short("long black-shafted spear");
    set_long(
       "It is a long spear with a sharp steel point set on a black "+
       "orichalcum shaft.\n");
    set_hit(22); set_pen(16);
    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_POLEARM);
}
