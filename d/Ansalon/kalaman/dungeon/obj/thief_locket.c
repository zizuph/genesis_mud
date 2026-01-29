/*
 * Thief Locket
 *
 * Quest Item
 *
 * Quest: This is for the first part of the love/hate quest of Kalaman.
 *        This locket is needed to gain entrance to the inner prison 
 *        cells of the dungeon.
 *        This is the locket that the old thief in the outer prison cells
 *        want to have, when he is given this locket he will give back
 *        the key to the inner cells.
 *
 * Lunatari of Krynn
 * 2008-02-10: Created (based on the handkerchief.c)
 */
inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

string open_locket();

void
create_object()
{
    set_name(({"locket","_kalaman_thief_locket_"}));
    set_adj(({"antique", "silver"}));
    set_short("antique silver locket");
    set_long("This is an " + query_short() + " attached to a thin " +
      "and beautifully crafted silver chain. The locket itself is " +
      "richly decorated with small dolphins. It seems like one " +
      "could be able to open it.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 500);

    add_cmd_item("locket", "open", open_locket);
}

string
open_locket()
{
    write("You flip the " + query_short() + " open and see a picture " +
      "of a beautiful red-haired slender female human, she looks " +
      "stunning and extremely happy. After studying the picture, you " +
      "gently close the locket again.\n");
    say(QCTNAME(TP) + " opens a " + query_short() + " and study the " +
      "content for a while and then closes it again.\n");
    return "";
}
