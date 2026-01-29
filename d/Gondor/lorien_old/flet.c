/*
 * Meeting room for dicussions about Lorien.
 * Serif, June 2003.
 */
 
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anduin/lib/and_funcs.c";

#include "/d/Gondor/anduin/lib/and_defs.h"
#include "/d/Gondor/defs.h"

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

public string      long_desc();

static void create_board();

public void
create_gondor()
{
    object board;

    set_short("An airy flet high in a mallorn tree");

    set_long(&long_desc());

    sky_add_items();
    lorien_add_items();

    set_tell_time(200);

    set_no_exit_msg(({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"}), "Nothing but open air lies "
        + "in that direction.\n");
    set_no_exit_msg(({"up"}), "The branches above you don't seem as if "
        + "they would support your weight.\n");
    set_no_exit_msg(({"down"}), "You probably don't want to try that, "
        + "since it's a long way down.\n");

    add_item(({"room", "area", "surroundings", "place"}), long_desc);
    add_item(({"flet", "spacious flet", "airy flet", "platform"}), "You "
        + "stand upon a spacious flet high in the mallorn trees of "
        + "Lothlorien, bathed in serenity and peace.\n");

    create_board();

    add_exit("/d/Gondor/workroom", "office");

}

string
long_desc()
{
    return "On a spacious flet somewhere in the mallorn treetops of "
        + "Lothlorien. There is little here except for the flet, a board, "
        + "and the mallorn trees" + mallorn_desc() + ", making a serene "
        + "and ideal spot to discuss the surrounding terrain.\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
        lorien_add_items();
        remove_item("Golden Wood");
        remove_item("Lorien");
        remove_item("golden wood");
        remove_item("lorien");
        add_item(({"Lorien", "lorien", "Golden Wood", "golden wood", 
            "Lothlorien", "lothlorien", "terrain", "surrounding terrain"}), 
            "Lorien, the Golden Wood, lies all around and below you, "
            + "decked in the splendour of the mallorn trees.\n");
 
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name("/d/Gondor/lorien/" + "board");
        board->set_num_notes(75);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_rank(this_player()->query_wiz_level());
        board->set_remove_str("You may not do that.\n");
        board->move(TO);
    }
    return 0;
}
