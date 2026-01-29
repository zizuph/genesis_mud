/* /d/Emerald/thief_lair/wep/ewams_club.c

   Ewam, the bandit shopkeeper's nasty spiked club.
   - Casimir, 1999.
*/

inherit "std/weapon.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("club");
    set_short("massive spiked club");
    add_adj( ({"massive", "spiked"}) );
    set_long("A heavy piece of stout oak through which crude iron spikes "+
	     "have been driven.\n");

    set_hit(30);
    set_pen(34);
    likely_dull = 15;
    likely_break = 5;
    likely_corr = 4;

    set_wt(W_CLUB);
    set_dt(W_IMPALE|W_BLUDGEON); 
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 14400);
    add_prop(OBJ_I_VOLUME, 22000);    
}

