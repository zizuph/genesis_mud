/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("tanecetum vulgare");
    add_name("flowers");
    set_herb_name("tansy");
    add_adj("button-like");
    set_short("bunch of button-like flowers");   
    set_id_long("This cluster of yellow button-like flower heads comes "+
          "from the tansy plant. The flowering part of this plant with "+
          "fern-like leaves produces a golden yellow dye.\n");
    set_unid_long("A cluster of button-like flowers from a plant you "+
          "do not know.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
