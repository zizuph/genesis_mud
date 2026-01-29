/*  Cloak worn by Deuterian Kretan Commanders
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
    set_adj(({"long","silver","kretan"}));
    set_short("long silver cloak");
    set_long("It is a long silver cloak with ranking military insignias "+
             "sewn into its border, and a seven-headed hydra embroidered "+
             "on the back. It is worn around the neck with a clip that "+
             "holds it in place.\n");
    set_ac(13);
    set_at(A_NECK);
}
