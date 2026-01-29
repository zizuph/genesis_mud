/* an herb coded by Elizabeth Cook/Mouse, April 1997 */
inherit "/std/herb";
#include <herb.h>
#include "../mouse.h"       

void create_herb()  {
    set_name("foeniculum vulgare");
    add_name(({"root","plant"}));
    set_herb_name("fennel");
    add_adj(({"aromatic","bulbous"}));
    set_short("aromatic, bulbous root");   
    set_id_long("Fennel is a highly aromatic plant with small yellow "+
          "flowers, fine leaves, and a bulb-like root. Fennel is known "+
          "to reduce the effects of alcohol on the body.\n");
    set_unid_long("This is the bulbous root of an aromatic plant. You have "+
          "no clue what its uses are.\n");
    set_herb_value(500);
    set_decay_time(2400);
    set_find_diff(5);
    set_id_diff(60);
    set_effect(HERB_SPECIAL,0,0);

  }
 
void special_effect()
{
    int intoxicated = TP->query_intoxicated();
    int detox= TP->intoxicated_max()/5;     
    if(intoxicated < detox)
        TP->set_intoxicated(0);     
    else
        TP->set_intoxicated(intoxicated-detox);
    tell_object(TP,"You feel less intoxicated.\n");   
}
