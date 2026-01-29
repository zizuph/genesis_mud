/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>
#include "../mouse.h"
#pragma strict_types

void create_herb()  {
    set_name("agrimonia eupatoria");
    add_name(({"flowers","plant"}));
    set_herb_name("agrimony");
    add_adj("yellow");
    set_short("spike of yellow flowers");   
    set_id_long("Agrimony is a hairy plant with a short rhizome and "+
          "solitary stem which supports a long spike of yellow flowers. "+
          "Agrimony is known to improve poor vision.\n");
    set_unid_long("A hairy plant with a long spike of yellow flowers. "+
          "Its uses are a mystery to you.\n");
    set_herb_value(1500);
    set_decay_time(2400);
    set_find_diff(6);
    set_id_diff(70);
    set_effect(HERB_SPECIAL,0,0); 
  
}
 
void special_effect()  
{
    object *ob_arr = all_inventory(ENV(TO));  
    int num = sizeof(ob_arr);
    int i;
    
    for(i=0;i<num;i++)
    {
        if(ob_arr[i]->query_poison_type() == "blindness")
        {
            ob_arr[i]->cure_poison(({"blindness"}),80);
            break;
        }
    }
}

