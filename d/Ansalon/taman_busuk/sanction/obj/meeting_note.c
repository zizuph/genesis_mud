inherit "/std/object";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

#define GARREN_NOTE "_garren_quest_note"
#define PARCHMENT_PROP "_garren_prop_read_note"

void
create_object()
{
    set_name("parchment");
    add_name("message");
    add_name("note");
    add_name(GARREN_NOTE);
    add_adj("yellow");
    set_short("yellow parchment");
    set_long("This is a piece of yellow parchment normally used to write on. " +
             "The parchment is something written on it.\n");

    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 20);
}

int
read_note(string args)
{
    if (args != "note" && args != "message" && args != "parchment" && args != "yellow parchment")
    {
        notify_fail("Read What? The note?\n");
        return 0;
    }
    TP->catch_tell("       ********************************\n" +
                   "       *                              *\n" +
                   "       * We are leaving tonight,      *\n" +
                   "       * meet us at the old warehouse *\n" +
                   "       * as usual. Bring the rest of  *\n" +
                   "       * the girls, and you will get  *\n" +
                   "       * your promised reward.        *\n" +
                   "       *                              *\n" +
                   "       * Don't let anyone see you, it *\n" +
                   "       * is imperative that we get to *\n" +
                   "       * leave unoticed or we will    *\n" +
                   "       * be forced to pay tribute to  *\n" +
                   "       * the accursed dragonarmy.     *\n" +
                   "       *                              *\n" +
                   "       * ~ K.                         *\n" +
                   "       *                              *\n" +
                   "       ********************************\n");
    TP->add_prop(PARCHMENT_PROP, 1);
    tell_room(environment(TP), QCTNAME(TP) + " looks at a yellow parchment.\n", TP);
    return 1;
}

public void init()
{
    ::init();
    add_action(read_note, "read");
}

