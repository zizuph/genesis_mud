/*
 * camellia flower
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
 
    set_name("camellia");
    set_short("flower");
    set_short("camellia");
    set_pname("camellias");
    set_fragrance(0);
    set_adj("perfect");
    set_long("A large showy camillia. The flower is beautiful and " +
       "quite large. It is a perfect white and long lasting.\n");
    set_wilt_time(2700);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
