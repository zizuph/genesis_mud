/*
 * Wooden club coded by Lord Rastlin
 */

inherit "/std/weapon";

#include "/sys/formulas.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

nomask
create_weapon() 
{
    set_name("club");
    set_adj("wooden");
    set_short("wooden club");
    set_long("A normal wooden club. Good to have when you\n"
	     + "want to hit someone on the head.\n");
    set_hit(10);
    set_pen(12);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,12));
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2700);
}
