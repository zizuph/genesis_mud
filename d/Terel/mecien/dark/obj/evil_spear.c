inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <comb_mag.h>
#include <ss_types.h>
#include "/sys/wa_types.h"

#define TP this_player()


create_weapon(){
   set_name("spear");
   set_adj("black");
   set_short("black spear");
   set_long("A wicked halberd, fashioned of a black alloy.\n");
   set_hit(40);
   set_pen(38);
   set_wf(this_object());
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   /*    add_prop(OBJ_I_VALUE, comp_value(30)); */
   
}


public int
wield(object wep)
{
   if (this_player()->query_alignment() > 40)
      {
      write("The spears glows bright red and burns you.\n");
      TP->heal_hp(-5);
      return -1;
   }
   return 0;
   
}
