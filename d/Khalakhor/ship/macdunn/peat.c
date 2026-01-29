/* File:          /d/Khalakhor/ship/macdunn/peat.c
 * Creator:       Teth
 * Date:          November 30, 1997
 * Modifications:
 * Purpose:       This bale of peat contains the herb sphagnum.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/pier12.c
 *                /d/Krynn/common/herbs/sphagnum.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

int herb;
object sphagnum;

public void
reset_object()
{
    seteuid(getuid());

    herb = 0;
}

public void
create_object()
{
    set_name("bale");
    add_name("peat");
    set_adj("peat");
    add_adj(({"mossy","large","dirty"}));
    set_short("peat bale");
    set_pshort("peat bales");
    set_long("This peat bale is large and dirty. It is immense, " +
        "an amount of peat that can heat the homes in a small " +
        "village for a month. Peat is compressed vegetable matter, " +
        "made of centuries of compacted moss, and extracted from " +
        "boggy areas. A few tufts of fresh moss protrude, useless " +
        "as a fuel, but a by-product of collecting the peat.\n");
    add_item(({"moss","fresh moss","tufts","tufts of moss",
        "tufts of fresh moss"}),"The tufts of fresh moss are long " +
        "strands of green, contrasting the dun brown of the peat.\n");
    add_prop(OBJ_I_VALUE, 20250);
    add_prop(OBJ_I_WEIGHT, 401298);
    add_prop(OBJ_I_VOLUME, 350658);

    enable_reset();

    add_cmd_item(({"herb","moss","fresh moss","tuft","tufts",
        "on herb","on moss","on fresh moss","on tuft","on tufts"}),
        ({"pull","yank","tear","rip","collect","tug"}),
        "@@get_moss");           
}

public int
get_moss()
{
    if (herb > 1)
    {
        write("There are no tufts of moss large enough to be of any " +
           "value.\n");
        say(QCTNAME(TP) + " attempts to collect a tuft of moss from " +
          "the bale, but there are none that " + HE + " is able to " +
          "get of any value.\n");
        return 1;
    }

    write("You are able to tear a tuft of moss from the bale!\n");
    say("With little effort, " + QCTNAME(TP) + " is able to tear " +
      "a tuft of moss from the bale!\n");
    sphagnum = clone_object("/d/Krynn/common/herbs/sphagnum");
    sphagnum->move(this_player(), 1);
    herb = herb + 1;
    return 1;
}

