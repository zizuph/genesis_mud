/*
 * Holiday food from Bree
 * Finwe, December 2002
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("gingerbread");
    add_name("gingerbread man");
    add_name("gingerbread cookie");
    add_pname("gingerbread cookies");
    add_pname("gingerbread man cookies");
    set_adj("brown");
    set_short("gingerbread man cookie");
    set_pshort("gingerbread man cookies");
    set_long("This is a cookie in the shape of a person. It is dark " +
       "brown and outlined with white frosting. Red candies mark the " +
       "eyes, nose, and upturned face. It looks tasty as it is made " +
       "from ginger and is a popular holiday cookie.\n");
    set_amount(9); 
}
