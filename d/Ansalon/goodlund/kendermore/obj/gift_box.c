/* Gift box for Kendermore. Gwyneth May-June, 1999 */

#pragma save_binary

inherit "/lib/keep";
inherit "/d/Genesis/std/pack";
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

private string colour = "uncoloured";

void
create_gbox()
{
    return;
}

void
create_pack()
{
    set_name("box");
    add_name("present");
    set_pname("boxes");
    add_pname("presents");
    set_adj(colour);
    add_adj("gift");
    set_short(colour + " gift box");
    set_pshort("@@query_colour@@ gift boxes");
    set_long("This is a lovely gift box wrapped in @@query_colour@@ " +
        "wrapping paper. @@open_closed@@\n");
    add_cmd_item(({"gift", "box", "present"}), "wrap", "@@wrap_gift");
    add_cmd_item(({"gift", "box", "present"}), "unwrap", "@@unwrap_gift");
    set_mass_storage(0);
    set_keep(1);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_WEIGHT, 1750);
    add_prop(CONT_I_MAX_VOLUME, 75000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(OBJ_I_VALUE, 250);
    set_alarm(0.1, 0.0, "make_me_box");
    create_gbox();
}

void
make_me_box()
{
    remove_name("pack");
    remove_pname("packs");
}

set_colour(string new_colour)
{
    remove_adj(colour);
    colour = new_colour;
    set_short(0);
    set_adj(colour);
}

string
query_colour()
{
    return colour;
}

string
open_closed()
{
    if (query_prop(CONT_I_CLOSED))
    {
        return "It could hold many different things. Unwrap it and find out!";
    }
    else
    {
        return "This is a great box to wrap a present in!";
    }
}

string
wrap_gift()
{
    if (query_prop(CONT_I_CLOSED))
    {
        write("It's already wrapped!\n");
    }
    else   
    {
        write("You gently place the lid onto the gift " + 
            "box.\n");
        add_prop(CONT_I_CLOSED, 1); 
    }
    return "";
}

string
unwrap_gift()
{
    if (query_prop(CONT_I_CLOSED))
    {
        write("You gently remove the lid of the gift " +
            "box.\n");
        add_prop(CONT_I_CLOSED, 0);
    }
    else
    {
        write("It's already unwrapped. Look inside!\n");
    }
    return "";
}
