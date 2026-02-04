/* a log can be used as a club */
/* Janus 920707 */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("log");
    set_short("small log");
    set_long("A normal looking brown log.\n");
    set_adj("brown");
    set_hit(5);
    set_pen(10);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,4000);
    set_wt(W_CLUB); 
    set_dt(W_BLUDGEON); 
    set_hands(W_ANYH); 
}
