/* 
 * A piece of paper, found behind a boulder
 *
 * 950501 by Rastlin
 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("paper");
    set_adj("old");
    set_short("old piece of paper");
    set_long("It is an old bloodstained piece of paper, there is some " +
	"writing on it.\n");

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 2);

    add_cmd_item(({"paper", "writting", "text"}), "read",
	"\n" +
	"     My life is coming to an end, I just want to\n" +
	"     warn you of the hidden door. DON'T open it!\n" +
	"     There is something terrible behind it, I can't\n" +
	"     put the feeling into words. But if you value your\n" +
	"     life don't open it. I will tie a key to this paper,\n" +
	"     that key should open the final door. I'm not sure though.\n" +
	"\n" +
	"                                 Eben Shatterstone\n");
}
