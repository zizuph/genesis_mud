/*  file:  /d/Calia/sea/weapons/great_thonker.c
 *  description:  great obsidian thonker (club)
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
    set_adj(({"great", "obsidian"}));
    set_short("great obsidian thonker");
    set_pshort("great obsidian thonkers");
    set_long("A massive weapon wielded only by the most"+
      " elite water krougs. The club has a rough handle on one"+
      " end and a sharp beaklike thonker on the other. It is"+
      " made from glasslike black obsidian and resembles a"+
      " stalactite that may have been ripped from the"+
      " ceiling of a cave.\n");
    set_hit(50);
    set_pen(50);
    set_wt(W_CLUB);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 7500);
}
