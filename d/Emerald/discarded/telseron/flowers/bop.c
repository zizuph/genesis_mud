inherit "/d/Emerald/telseron/flowers/flowers.c";
#include "/sys/language.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
public void
create_flower()
{
 
    set_name("bird of paradise");
    set_short("flower");
    set_short("bird of paradise flower");
    set_pname("bird of paradise flowers");
    set_fragrance(0);
    set_adj("beautiful");
    set_long("This lovely flower is shaped like a tropical bird. " +
        "It has a colourful crown and a beak-like tip.\n");
    set_wilt_time(2500);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
