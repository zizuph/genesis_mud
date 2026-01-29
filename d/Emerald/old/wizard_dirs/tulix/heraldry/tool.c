/* An engraving tool. This item is part of the Heraldry quest in Emerald. */
/* It is needed to engrave the plaques. Coded by Tulix, 18/4/1993 */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Emerald/tulix/heraldry/heraldry_defs.h"

void
create_object()
{
    set_name("tool");
    set_adj("engraving");
    set_short("engraving tool");
    set_long(break_string("It is a small, pen sized engraving tool. " +
        "The tip of the tool has a small diamond inset into it, which " +
        "it can be used to engrave metal quite easily.\n ",78));

    add_prop(OBJ_I_WEIGHT, 50);     /* weighs 50g      */
    add_prop(OBJ_I_VOLUME, 10);     /* takes up 10ml   */
    add_prop(OBJ_I_VALUE, 200);     /* Quite expensive */
}

void
init()
{
    ::init();
    add_action("do_engrave", "engrave");
}

int
do_engrave(string str)
{
    int size;
    *string engraving;

    notify_fail("Engrave what?\n");
    
    if (!str)
        return 0;

    engraving = explode(str , " ");  /* Chop str into little bits */
    size = sizeof(engraving);

    if ( member_array("plaque", engraving) == -1 )
    {
        write("You decide that the object was not suitable for engraving");
        return 1;
    }
    return 1;
}


