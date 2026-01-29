/*
 * A box for players' suggestions in smoke room in gentleman's club
 * Created by Valen, 20011211
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include <macros.h>
#include <std.h>
#include "guild.h"

nomask void
create_board()
{
    remove_name(query_name());
    remove_pname(query_pname());
    add_name(OB_NAME(this_object()), 1);
    set_name("box");
    set_short("suggestion box");
    set_long("A large box placed here by owners of the club. There is " +
        "a notice placed above the mantle where you can read more about " +
        "the purpose of this box. " +
        "Your gentleman's behaviour does not allow you to peek on notes " +
        "posted by other members, however you can read your own notes.\n");
    set_board_name(LOG + "suggestions");
    set_num_notes(100);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("Sorry, only a Lord may remove the notes.\n");
    set_no_report(0);
    set_keep_discarded(1);
}

nomask int
query_prevent_shadow()
{
    return 1;
}

/* only wizards can read other people's notes */

nomask int
block_reader(int note = 0)
{
    if(this_player()->query_wizard_level())
    {
        return 0;
    }

    return 1;
}

/* replacement of that 'gnome securing' message */

nomask void
reset_board()
{
    if (!random(5))
    {
        tell_room(environment(),
            "A small gnome appears and makes sure all notes are securely " +
            "placed in the " + short() + ".\nThe gnome then leaves again.\n");
    }
}
