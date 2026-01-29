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

    set_name("cane");
    add_name("candy cane");
    set_pname("puddings");
    add_pname("canes");
    add_pname("candy canes");
    set_adj("striped");
    set_short("striped candy cane");
    set_pshort("striped candy canes");
    set_long("This is a candy cane. It is white with a large red stripe " +
        "wrapping around it. The top of the candy cane is bent over, " +
        "resembling a shepherd's crook. It is mint flavored and a favorite " +
        "of the holidays.\n");
    set_amount(10); 
}
