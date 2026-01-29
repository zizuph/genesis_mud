/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("isatis tinctoria");
    add_name("leaves");
    set_herb_name("woad");
    set_short("bunch of lanceolate leaves");   
    set_id_long("These thin, toothless leaves come from the woad plant. "+
         "This plant is distinguished by the cluster of small yellow "+
         "blossoms atop its leafy stem. The leaves of the woad plant "+
         "are used to create a blue dye.\n");
    set_unid_long("A plant with thin, toothless leaves. You have no "+
         "idea of its uses.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(1);
    set_id_diff(10);  

}
 
