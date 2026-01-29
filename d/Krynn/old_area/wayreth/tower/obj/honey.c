/* 
 * Some honey
 * -Karath 970430
 */

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_food()
{
    set_name("honey");
    add_name("dab");
    set_pname("honey");
    add_pname("dabs");
    set_adj("sticky");
    set_short("dab of sweet honey");
    set_pshort("dabs of sweet honey");
    set_long("A fairly normal looking dab of honey. It smells strongly "+
	"of clover and you can only imagine the beautiful fields that "+
	"it must have come from.\n");
    set_amount(15);
}
