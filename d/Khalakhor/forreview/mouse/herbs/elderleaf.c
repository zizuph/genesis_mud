/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("sambucus leaves");
    add_name("leaves");
    set_herb_name("elder leaves");
    add_adj("toothy");
    set_short("bunch of toothy leaves");   
    set_id_long("These toothed opposite compound leaves come from "+
         "a shrub known as the elder. These leaves are excellent for "+
         "creating a green dye.\n");
    set_unid_long("These are toothed leaves from some sort of shrub.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
