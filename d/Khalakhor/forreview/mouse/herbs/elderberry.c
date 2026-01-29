/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("sambucus berries");
    add_name("berries");
    set_herb_name("elder berries");
    add_adj("dark");
    set_short("cluster of dark berries");   
    set_id_long("This cluster of small, deep purple berries is the fruit "+
         "of the elder shrub. They make an excellent purple dye.\n");
    set_unid_long("A cluster of dark berries from a shrub with which you "+
         "are not familiar.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
