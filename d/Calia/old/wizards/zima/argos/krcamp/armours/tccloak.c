/*  Cloak worn by Triterian Kretan Commanders
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/25/96  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("cloak");
    set_adj(({"short","gray","kretan"}));
    set_short("short gray cloak");
    set_long("It is a short gray cloak bordered with black-threaded "+
             "designs. A clip holds it around the neck and a seven-headed "+
             "hydra is embroidered on the back in black.\n");
    set_ac(10);
    set_at(A_NECK);
}
