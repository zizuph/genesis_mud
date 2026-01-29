/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("monarda didyma");
    add_name(({"bergamot","blossoms","plant"}));
    set_herb_name("bee balm");
    add_adj(({"shaggy","red"}));
    set_short("bunch of shaggy red blossoms");   
    set_id_long("This plant is known as bee balm, or bergamot. It has "+
          "shaggy, vibrant red blossoms and toothed, lanceolate leaves. "+
          "Bee balm has been known to mildly reduce fatigue.\n");
    set_unid_long("A plant with shaggy red blossoms. "+
          "You aren't sure if it has any use.\n");
    set_herb_value(100);
    set_decay_time(2400);
    set_find_diff(3);
    set_id_diff(40);
    set_effect(HERB_HEALING,"fatigue",5);  
}
 
