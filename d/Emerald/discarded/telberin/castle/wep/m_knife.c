/* Knife made for the militia men in Telberin.
 * Average stats since they are one of the lowest knives around, but
 * they should help newbies out. Mylos.
 *
 */
inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"


void
create_weapon()
{

    if(!IS_CLONE)
        return;

    set_name("knife");
    set_short("short knife");
    set_long("This small weapon is very light and very maneuverable. It "+
             "would probably be very effective at close ranges for stabbing "+
             "and slashing. The hilt is very plain and undecorated.\n");

    set_adj("short");

    set_hit(5);
    set_pen(9);

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);

    set_hands(W_ANYH);


    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(5,9) + random(90) - 45);
}

string
query_recover()
{
    return "/d/Emerald/obj/general/m_knife" + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
