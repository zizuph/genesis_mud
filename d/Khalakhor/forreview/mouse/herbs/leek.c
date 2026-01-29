/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>
#include "../mouse.h"

void create_herb()  {
    set_name("allium porrum");
    add_name(({"bulb","plant"}));
    add_adj("white");
    set_herb_name("leek");
    set_short("white bulb");   
    set_id_long("This is a leek plant. It has a whitish colored bulb "+
          "and three smooth, green, broad leaves. The entire plant "+
          "has an odor of onion. Leek has long been known to protect "+
          "men in battle.\n");
    set_unid_long("A white bulb with three smooth leaves. This plant "+
          "has a strong, horrible odor. The thought of eating it disgusts "+
          "you.\n");
    set_herb_value(500);
    set_decay_time(2400);
    set_find_diff(4);
    set_id_diff(50);
    set_effect(HERB_SPECIAL,0,0);
  
}
 
void special_effect()
{
    object arm;
    reset_euid();
    arm = clone_object(ROOT+"herbs/armour.c");
    arm->move(ENV(TO));
}
