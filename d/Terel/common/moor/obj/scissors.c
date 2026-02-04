/*
    Modified: 6 May 2003, by Bleys
        - added a short desc to dodge the "unwielded" problem
*/

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
  set_name("scissors");
  set_long("A pair of small scissors, used to prune "+
    "the plants in the garden. In a pinch it could "+
    "probably be used as a weapon.\n");
  set_short("small pair of scissors");
  set_adj(({"a pair of","small"}));
  set_hit(5);
  set_pen(5);

  set_wt(W_KNIFE); 
  set_dt(W_IMPALE); 

  /* Last, how shall it be wielded? */
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 500);
}
