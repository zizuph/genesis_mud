/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("cedronella canariensis");
    add_name(({"plant","balm"}));
    set_herb_name("balm of gilead");
    add_adj("musky");
    set_short("musky plant");   
    set_id_long("A plant with delicate pink flower clusters and a "+
          "prickly stem. Its leaves are three-lobed and toothy. It has "+
          "a distinctly musky odor. This is the Balm of Gilead, a plant "+
          "endowed with great powers of healing and purifying.\n");
    set_unid_long("A plant with delicate pink flower clusters and a "+
          "prickly stem. Its leaves are three-lobed and toothy. This "+ 
          "plant smells musky. You wonder if it has any use.\n");
    set_herb_value(900);
    set_decay_time(2400);
    set_find_diff(7);
    set_id_diff(80);
    set_effect(HERB_HEALING,"hp",80);;
    add_effect(HERB_ENHANCING,"con",2);
    add_effect(HERB_CURING,"all",100);
  }
 
