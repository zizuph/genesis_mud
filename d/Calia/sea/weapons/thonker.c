/*  file:  /d/Calia/sea/weapons/thonker.c
 *  description:  A thonker (club) made from a stalagtite
 *  like a warhammer--
 *  for the xlarge water krougs
 *  in the sea area
 *  coder:  Tigerlily
 *  date:   2002-06-
*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("thonker");
    add_name("club");
    set_adj(({"massive", "malachite"}));
    set_short("massive malachite thonker"); 
    set_pshort("massive malachite thonkers");
    set_long("A powerful looking weapon used by large water krougs."+
      " The club has a rough handle on one end and a sharp"+
      " beaklike thonker on the other. It is made from"+
      " malachite and resembles a stalactite that may"+
      " have been ripped from the ceiling of a cave.\n");
    set_hit(25);
    set_pen(34);
    set_wt(W_CLUB);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 7500);
}
