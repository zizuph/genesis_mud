/*
 * gardenia flower
 * Coded by Finwe
 * August 1996   
 */ 
 
inherit "/d/Emerald/telseron/flowers/flowers.c";
#include "/sys/language.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
public void
create_flower()
{
 
    set_name("gardenia");
    set_short("flower");
    set_short("gardenia");
    set_pname("gardenias");
    set_fragrance(1);
    set_adj("large");
    set_long("This flower is pure white and very fragrant. The petals " +
        "are radiant and compact.\n");
    set_wilt_time(2500);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
