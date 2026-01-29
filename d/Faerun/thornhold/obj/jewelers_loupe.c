/* jewelers loupe by Twire, June 14, 2016
 * Item for the Thornhold merchants quest.
*/

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>


public void
create_object()
{
    set_name("loupe");
    set_adj("jewelers");
    set_short("jewelers loupe");
    set_long("This jewelers loupe is a lens encased in a cylinder. It's " +
             "used for examining gems.\n");
    add_cmd_item("loupe","use","@@do_use@@");
}


public int
do_use()
{
    write("You peer through the jewelers loupe. It magnifies everything. " +
      "It might be useful to an experienced jeweler or appraiser.\n");
    return 1;
}
