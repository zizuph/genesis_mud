inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
 
void
create_object()
{
    ::create_object();
    set_name("token");
    set_adj("wooden");
    set_short("wooden token");
    set_long("This is a wooden token giving to those who "
	+"help the master.\n");
    add_prop(OBJ_I_VALUE,3000);
    add_prop(OBJ_I_LIGHT,-2);
}


