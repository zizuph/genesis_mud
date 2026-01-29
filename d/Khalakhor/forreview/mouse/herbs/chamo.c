/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("chamaemelum nobile");
    add_name(({"flowers","plant"}));
    set_herb_name("chamomile");
    add_adj("white-petalled");
    set_short("bunch of white-petalled flowers with golden centers");   
    set_id_long("This plant is chamomile. Its flowers have white petals "+
          "extended from golden centers. It has bright green, feathery "+ 
          "leaves that have an apple-like scent. The flowers of this plant "+
          "are endowed with very mild healing properties.\n");
    set_unid_long("This plant has flowers with white petals that radiate "+
          "from golden centers. You aren't sure if it has any use.\n");
    set_herb_value(200);
    set_decay_time(2400);
    set_find_diff(3);
    set_id_diff(40);
    set_effect(HERB_HEALING,"hp",20);
  }
 
