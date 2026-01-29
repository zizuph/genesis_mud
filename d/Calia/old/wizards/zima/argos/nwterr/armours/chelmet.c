/*
** a common helmet
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 10/15/96   Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"
 
void create_armour() {
    set_name("helmet");
    set_adj(({"taberded","leather"}));
    set_short("taberded leather helmet");
    set_long("It is a taberded leather helmet, decorated with links of "+
             "chainmail around the top.\n");
    set_ac(10);
    set_at(A_HEAD);
}
