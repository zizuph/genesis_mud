
/*
    A warhammer used by Xorfin, the Cadets' guildmaster.

    Coder(s) : Maniac

*/

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
    set_name("warhammer");
    set_adj(({ "huge", "steel" }));
    set_short("huge steel warhammer"); 
    set_pshort("huge steel warhammers"); 
    set_long("A huge steel warhammer.\n"); 
    set_hit(40);
    set_pen(40);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 10000);
}

