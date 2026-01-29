#pragma strict_types

inherit "/std/object";
inherit "/d/Gondor/common/lib/tell_funcs.c";

/* Inherit /lib/help to enable the help functionality. */
inherit "/lib/help";

#include "guild.h"

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("horn");
    set_short("silver-plated horn");
    add_name(GUILD_EMBLEM_ID);
 
    add_adj( ({ "silver", "plated", "silver-plated" }) );
    set_long("This silver-plated horn is the item that designates you as"
      + " an official member of the " + GUILD_NAME + ". You sense that you"
      + " could use the command <help patrol> to learn more about the"
      + " guild. It is also possible to <blow> this horn to signal an"
      + " alarm if danger should threaten the lands.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME,  500);

    remove_prop(OBJ_I_VALUE);

    /* We add help in a folder, and we add a category "patrol".
     * The folder contains two help files:
     *     history.help and levels.help
     *
     * This offers the following commands:
     *     help patrol  --> lists the topics: history and levels.
     *     help [patrol] levels
     *     help [patrol] history
     */
    
    /* Give the directory in which the help files are located. Using a
     * directory requires us to also set a category. */
    set_help_dir("/d/Sparkle/area/tutorial/guild/help");

    /* Set the category for this help. It is mandatory when using a
     * directory of help files. This routine takes a single string, or
     * an array of string, e.g. ({ "demoguild", "dg" }) would have
     * worked too. Just make sure that the categories are UNIQUE in
     * the realms, or otherwise they wouldn't work as category :-) */
    set_help_category("patrol");
}


public int
blow_horn(string str)
{
    string  his;

    if ((!str) || (str != "horn"))
    {
        notify_fail(capitalize(query_verb())+" what?\n");
        return 0;
    }

    his = this_player()->query_possessive();

    write("You breathe deeply, and blow the horn.\n"
        + "You produce a deep and mighty, bellowing sound!\n");
    say(QCTNAME(this_player())
      + " blows into "+his+" horn, and produces a mighty sound!\n",
        this_player());

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
        return 1;

    tell_players_in_same_subdir(this_player(),
        "The sound of a patrol horn echoes through the area.\n", 0);
    tell_next_room_with_dir(environment(this_player()),
        "You hear the sound of a mighty horn from");
    return 1;
}



/*
 * Function name: hook_display_help_topics
 * Description  : Display the available topics for a given category. It makes
 *                a little table based on the screen width of the player.
 * Arguments    : string category - the category.
 *                string *topics - the topics within that category.
 */
public void
hook_display_help_topics(string category, string *topics)
{
    write("Here are the topics you can get help on. Simply type:\n\n"
      + "\t<help patrol history>    - a history of the guild\n"
      + "\t<help patrol levels>     - the levels achievable in the guild\n"
      + "\t<help patrol commands>   - the commands you can use in the guild\n");
} /* hook_display_help_topics */


public void
init()
{
    ::init();
    add_action(blow_horn, "blow");
    add_action(blow_horn, "play");
}