/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("rubia tinctorum");
    add_name("root");
    set_herb_name("madder");
    add_adj("reddish-brown");
    set_short("reddish-brown root");   
    set_id_long("This thick, fleshy, reddish-brown root comes from "+
         "the madder plant. It is a climbing plant with prickly leaves "+
         "and stem and small yellowish-green flowers. The root is used "+
         "to create a red dye.\n");
    set_unid_long("A reddish-brown root from a plant you seem unable "+
         "to identify.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
