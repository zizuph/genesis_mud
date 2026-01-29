/* this is a dummy living who is only used to figure out
 * which rooms lies in a certain direction if the query_exit
 * doesn't produce the correct result.
 */
#include <stdproperties.h>

inherit "/std/monster";

void
create_monster()
{
    add_prop(OBJ_I_INVIS,100);
}
