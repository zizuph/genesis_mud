/**********************************************************************
 * - dshears.c                                                      - *
 * - Carried by dress shop owner in SaMorgan.                       - *
 * - /d/Khalakhor/sw_speir/samorgan/npc/arinia.c                    - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/

inherit "/d/Khalakhor/std/weapon.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
 
void 
create_khalakhor_weapon() 
{
    set_name("shears");
    set_adj(({"brass","dress"}));
    set_short("pair of brass dress shears");
    set_pshort("pairs of dresssheep shears");
    set_long("It is a pair of brass sheep shears, two sharp blades "+
             "hinged together near one end with handles. The brasswork "+
             "on these is high quality, something any dressmaker "+
             "would be proud to own.\n");
 
    set_hit(10);
    set_pen(5);
 
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);

    add_prop("mystic_weapon",1);
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  500);
}