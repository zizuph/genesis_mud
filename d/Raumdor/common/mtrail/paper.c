/* 2017-05-24 Malus: Making this a sheet, since it's obtained from a book */
/* 2017-10-22 Malus: Adding glpyh and tracing elements */

#include "defs.h"
#define RAUMDOR_TRACED_GLYPH "_raumdor_traced_glyph"
inherit "/std/object";

void
create_object()
{
    set_name("paper");
    add_name("sheet");
    set_adj("folded");
    set_short("folded sheet of paper");
    set_pshort("folded sheets of paper");
    set_long("It looks like a simple hand-written letter.\n");
    add_cmd_item(({"paper", "sheet of paper", "folded sheet of paper",
                "letter"}), "read",
    "Master Shafla,\n\n"+
    "I have stolen that ancient tome of the foolish Drakmereians!\n" +
    "They will never find it now, Master, for I have hidden it\n" +
    "deep within the mountain, and placed undying guardians there.\n" +
    "They would have to pass through the terrors of the forest, and\n" +
    "then discover the passage behind the waterfall, which I have\n" +
    "protected with an enchantment. Should you wish to inspect the\n" +
    "tome or my protections, you may trace the glyph below at the\n" +
    "the entrance to enter unimpeded.\n\n" +
    "         *\n" +
    "          *******\n" +
    "   *           *\n" +
    "    * **      *\n" +
    "     *        * **\n" +
    "     ****     *   *\n" +
    "    *    *     ***\n" +
    "    *   *     *\n" +
    "    *    *****\n" +
    "    *       *\n" +
    "     *       *\n" +
    "      *       ****\n" +
    "        *         **\n" +
    "           *        *\n\n" +
    "Soon we will be able to take over that fetid city!\n\n"+
    "In Darkness,\n"+
    "Penthalus, of the Khiraa\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,5);
    add_prop(OBJ_I_VALUE,1);
}

void
glyph_traced(object player, object room)
{
    if (find_object(FOREST_DIR + "wforest42") != room)
    {
        player->catch_msg("Nothing happens.\n");
        return;
    }
    if (player->query_prop(RAUMDOR_TRACED_GLYPH))
    {
        player->catch_msg("The door-shaped outline at the edge of the " +
            "waterfall intensifies momentarily.\n");
        return;
    }
    player->add_prop(RAUMDOR_TRACED_GLYPH, 1);
    player->catch_msg("A door-shaped outline appears at the edge of " +
        "the waterfall!\n");
}

int
do_trace(string str)
{
    notify_fail("Trace what?\n");
    if (!str)
        return 0;

    notify_fail("Trace what? The glyph?\n"); 
    if (!parse_command(str, ({}), " [the] 'glyph' "))
        return 0;

    if (!check_seen(TP) || !TP->can_see_in_room())
    {
        write("You can't see the glyph!\n");
        return 1;
    }

    TELL_SEEN(TP, QCTNAME(TP) + " traces " + HIS(TP) +
        " finger on a sheet of paper.\n");
    write("You trace the glyph with your finger...\n");
    set_alarm(2.0, 0.0, &glyph_traced(TP, E(TP)));
    return 1;
}

void
init()
{
    ::init();
    add_action(do_trace, "trace");
}
