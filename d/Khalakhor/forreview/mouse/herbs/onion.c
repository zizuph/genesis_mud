/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("allium cepa");
    add_name("bulb");
    set_herb_name("onion");
    add_adj("odorous");
    set_short("odorous bulb");   
    set_id_long("This is a plant with long, tubular, green leaves and "+
         "a large root bulb, commonly known as an onion. Its powerful "+
         "odor brings tears to the eyes, but the skin of this bulb creates "+
         "a lovely orange dye.\n");
    set_unid_long("You don't know what plant this is, but the bulbous root "+
         "emits a terribly strong odor.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
