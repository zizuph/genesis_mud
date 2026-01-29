/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("arctostaphylos uva-ursi");
    add_name("leaves");
    set_herb_name("bearberry");
    add_adj("paddle-shaped");
    set_short("bunch of paddle-shaped leaves");   
    set_id_long("These small paddle-shaped leaves are from a "+
         "low-growing, trailing shrub with small white, bell-shaped "+
         "flowers. The leaves of the bearberry plant are useful in "+
         "creating a dye of a violet-gray hue.\n");
    set_unid_long("Small paddle-shaped leaves from a low-growing shrub. "+
         "You have no idea what plant it is.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
