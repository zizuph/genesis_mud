inherit "/std/object";
#include <stdproperties.h>
void
create_object()
{
    set_name("amulet");
	add_name("platinum_amulet");
	set_long("This is a small platinum amulet. It "
	 + "bears the symbol of Paladine.\n");
	set_adj("platinum");
}
