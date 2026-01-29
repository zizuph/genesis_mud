/*
 * anthurium flower
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
 
    set_name("anthurium");
    set_short("flower");
    set_short("anthurium");
    set_pname("anthuriums");
    set_fragrance(0);
    set_adj("heart-shaped");
    set_long("A large heart-shaped anthurium. This magnificent flower " +
        "is wax-like yet is very durable. A yellow tail grows from " +
        "center of the flower. The flower is a brilliant red with a " +
	"yellow tail.\n");
    set_wilt_time(2500);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
