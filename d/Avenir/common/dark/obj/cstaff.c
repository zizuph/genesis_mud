//file name:        /d/Avenir/common/dark/obj/cstaff.c
//creator(s):       Casca, 12/04/99
//revisions:        
//purpose:          
//note:             
//bug(s):           
//to-do:            


inherit "/d/Avenir/inherit/weapon";
#include "../dark.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("polearm");
    add_name(({"staff", "weapon"}));
    set_adj(({"crystal-headed", "long"}));    
    set_short("long crystal-headed staff");
    set_pshort("long crystal-headed staffs");
    set_long("While this may be rather crude in construction, there is no "+
        "arguing about its sheer power. The shaft is made from a long springy "+
        "ash pole, at each end is a large piece of unworked quartz crystal."+
        "\n");           


    set_hit(33);
    set_pen(36);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

}
