/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("spirea ulmaria");
    add_name("root");
    set_herb_name("meadowsweet");
    add_adj("pink");
    set_short("pink root");   
    set_id_long("This pinkish-red,aromatic root comes from the "+
          "meadowsweet plant. The plant itself is distinguishable by "+
          "its large clusters of cream colored flowers with an almond "+
          "scent. The root is used to produce a black dye.\n");
    set_unid_long("This aromatic pinkish root comes from a plant you don't "+
          "recognize.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
