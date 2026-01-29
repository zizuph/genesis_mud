/*
 * daisy flower
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
 
    set_name("daisy");
    set_short("flower");
    set_short("beautiful daisy");
    set_pname("beautiful daisies");
    set_fragrance(0);
    set_adj("large");
    set_long("It is a large daisy with brilliant white petals. The " +
        "center is a golden yellow and contrasts with the blossom.\n");
    set_wilt_time(2500);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
