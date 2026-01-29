inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#define QUEST_BRACELET "_quest_bracelet_"
 
void
create_object()
{
    ::create_object();
    set_name("bracelet");
    set_adj("brilliant");
    add_adj("jeweled");
    set_short("brilliant jeweled bracelet");
    set_long("This is a beautiful crafted bracelet covered "
	+"in jewels. You notice it has an inscription on the "
	+"inside edge.\n");
    add_item("inscription","The inscription says:\n"
	+"To my lovely wife, love always,\n"
	+"Maximus.\n");
    add_prop(OBJ_I_VALUE,3000);
   add_prop(QUEST_BRACELET,1);
}


