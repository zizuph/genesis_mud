/* Shield of a kretan sentry
**
** HISTORY
** Date       Coder      Action
** ---------- ---------- ----------------------------------
** 1/25/96    Zima       Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum shield");
    set_long("It is a large round shield with a chainmail face, charred "+
             "black and emblazoned with a seven-headed hydra in red.\n");
    set_ac(15);
    set_at(A_SHIELD);
    set_am( ({0,0,0}));
}
