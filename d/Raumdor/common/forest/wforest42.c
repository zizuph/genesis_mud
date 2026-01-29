/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typos)
 */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#define RAUMDOR_TRACED_GLYPH "_raumdor_traced_glyph"
#include "defs.h"
inherit WFOREST_ROOM;

object outline;

void
create_room()
{
    string climb = "You scramble up the steep mountainside, " +
            "only to slide back down again.\n";
    forest_details = " To the south a steep mountainside rises high " +
        "above you. A waterfall flows from above, emerging into a stream " +
        "that continues north into the forest.";
    ::create_room();
    add_item("waterfall","@@waterfall@@");
    add_item(({"stream"}), "It looks clear and clean enough to drink from.\n");
    add_item(({"mountain","mountains","mountainside"}),
            "Mountains rise from the forest, blocking passage south.\n");
    add_cmd_item(({"mountain","mountains","mountainside"}), "climb", climb);
    set_no_exit_msg("south", "That would take you right into a waterfall!\n");
    set_no_exit_msg(({"southwest","southeast"}), climb);
    add_exit(FOREST_DIR + "wforest56","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest57","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest43","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest41","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest55","northwest",0,FOREST_FATIGUE);

    outline = clone_object(COMMON_OBJ_DIR + "outline");
    outline->move(TO, 1);
}

string
waterfall()
{
    string desc = "The water cascades over smooth rocks into a " +
    "stream that flows north.";
    if (TP->query_prop(RAUMDOR_TRACED_GLYPH))
        desc += " You can see a door-shaped outline near its edge. "
           + "Perhaps you could enter it."; 
    desc += "\n";
    return desc;
}

void
init()
{
    ::init();
    add_action("drink", "drink");
    add_action("enter", "enter");
}

int
enter(string str)
{
    notify_fail("Enter what?\n");
    if (!str)
        return 0;

    notify_fail("Enter what? The waterfall?\n");
    if (!parse_command(str, ({}), " [the] 'waterfall' / 'outline' "))
        return 0;

    if (!TP->can_see_in_room())
    {
        write("You cannot see well enough to do that!\n");
        return 1;
    }

    if (!TP->query_prop(RAUMDOR_TRACED_GLYPH))
    {
        write("You approach the waterfall, but you do not see " +
            "any way to enter it.\n");
        return 1;
    }

    write("You enter the waterfall...\n");
    say(QCTNAME(TP)+ " disappears behind the waterfall!\n");
    TP->move_living("M",FOREST_DIR + "crypt1");
    return 1;
}

int
drink(string str)
{
    object obj = TP;
    if (str == "from stream" || str == "from the stream")
    {
        write("Ahh! Refreshing!\n");
        say(QCTNAME(obj) + " drinks from the stream.\n",obj);
        obj->drink_soft(300);
        return 1;
    }
    notify_fail("Drink from what? The stream?\n");
    return 0;
}
