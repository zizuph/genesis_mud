/*
 * jasmine flower
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
 
    set_name("jasmine");
    set_short("flower");
    set_short("jasmine");
    set_pname("jasmines");
    set_fragrance(1);
    set_adj("white");
    set_long("This star shaped flower is very fragrant. Its perfume " +
        "fills the room with a rich fragrance. The flower is white and " +
        "very beautiful.\n");
    set_wilt_time(2500);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
