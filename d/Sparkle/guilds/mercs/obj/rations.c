inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("ration of meat and potatoes");
    set_pshort("rations of meat and potatoes");
    set_name("meat");
    set_pname("meats");
    add_name("ration");
    add_pname("rations");
    set_adj("meat");
    set_long("The rations are not the most lovely food around "+
	"but they are good for travelling.\n");
    set_amount(351);
}

