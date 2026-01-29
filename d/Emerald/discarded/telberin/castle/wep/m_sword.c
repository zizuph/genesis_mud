/* Sword made for the militia men in Telberin.
 * Average stats since they are one of the lowest swords around, but
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

    set_name("sword");
    set_short("short sword");
    set_long("This sturdy short sword is made of a fine metal found "+
             "mostly in and around the city of Telberin. "+
             "There is very little decoration on the short blade, but it "+
             "looks like a very durable and useful weapon.\n");
    set_adj("short");

    set_hit(10);
    set_pen(12);

    set_wt(W_SWORD);
    set_dt(W_IMPALE);

    set_hands(W_ANYH);


    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,12) + random(90) - 45);
}

string
query_recover()
{
    return "/d/Emerald/obj/general/m_sword" + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
