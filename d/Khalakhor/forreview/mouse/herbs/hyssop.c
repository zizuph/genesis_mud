/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("hyssopus officinalis");
    add_name(({"leaves","plant"}));
    set_herb_name("hyssop");
    add_adj(({"aromatic","lanceolate"}));
    set_short("plant with aromatic, lanceolate leaves");   
    set_id_long("This plant is hyssop. It is a small, bushy plant "+
          "with narrow, pointed and aromatic leaves and purple flowers. "+
          "It is useful in healing injuries and restoring health.\n");
    set_unid_long("A small, bushy plant with narrow, pointed and "+
          "aromatic leaves and purple flowers. You doubt it has much "+
          "usefulness.\n");
    set_herb_value(300);
    set_decay_time(3600);
    set_find_diff(3);
    set_id_diff(40);
    set_effect(HERB_HEALING,"hp",20);
  }
 
