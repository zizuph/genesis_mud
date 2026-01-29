/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("juglans regia");
    add_name("nut");
    set_herb_name("walnut");
    add_adj(({"green","husked"}));
    set_short("green husked nut");   
    set_id_long("This nut with the green husk comes from a walnut "+
          "tree. The husk and shells make a brown dye.\n");
    set_unid_long("This is some sort of nut with a green husk.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
