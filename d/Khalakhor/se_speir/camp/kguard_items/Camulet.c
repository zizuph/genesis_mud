inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>

#define ADJ ({"heavy", "sharp", "malicious", "cruel", "blunted"})
#define ADJ2 ({"silver-coated", "gold-coated", "platinum-coated", "copper-coated"})

void
create_weapon()
{
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2);
   
    set_name(({"axe"})); 
    add_name(({"axe"}));
    set_short(adj+" "+adj2+" "+wep); 
    set_long("This "+adj+" "+wep+" "+"has been given" +
            " a "+adj2+" edging, giving its blade an elegant shine."+
            " Deep within the shines of the "+adj2+", "+
            "you see a small inscription labeled 'Stark Industries'.\n");
    set_adj(({"adj"}));
    add_adj(({"adj2"}));
    set_wt(W_AXE);           
    set_dt(W_SLASH | W_IMPALE); 
    set_hands(W_ANYH);
    set_hit(35);
    set_pen(35);
}