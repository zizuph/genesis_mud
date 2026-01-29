/* an herb coded by Elizabeth Cook/Mouse, December 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("verbascum thapsis");
    add_name(({"leaves","plant"}));
    set_herb_name("mullein");
    add_adj(({"large","woolly"}));
    set_short("plant with large, woolly leaves");   
    set_id_long("This plant is mullein. It has fuzzy grayish colored "+
          "leaves on a stalky stem, which terminates in a spike of yellow "+
          "blossoms. The leaves offer some protection from the effects of "+
          "magic spells.\n");
    set_unid_long("A plant with grayish, fuzzy leaves. It has a stalky "+
          "stem topped by a spike of yellow flowers. It looks interesting, "+
          "but you have no idea if it is very useful.\n");
    set_herb_value(300);
    set_decay_time(3600);
    set_find_diff(3);
    set_id_diff(50);
    set_effect(HERB_ENHANCING,"magic",40);
 
  }
 
