/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("ocimum basilicum");
    add_name(({"leaves","plant"}));
    set_herb_name("basil");
    add_adj(({"bright","green"}));
    set_short("bunch of bright green leaves");   
    set_id_long("This plant is basil. It has bright green leaves that "+
          "are large and toothed, oval shaped, but pointed. The stem "+ 
          "is square and hairy. Basil is known for bringing mild mental "+
          "refreshment, as well as being a tasty addition to food.\n");
    set_unid_long("A plant with ovalish shaped, bright green leaves. "+
          "You aren't sure if it has any use.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(3);
    set_id_diff(40);
    set_effect(HERB_HEALING,"mana",5);  
}
 

