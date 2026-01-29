/*
 *    This silence object is to mute emotes that allow free text
 *    such as ponder, wonder, mumble and think. Feel free to add
 *    any emote commands that you feel are inappropriate for the
 *    tranquility of the church.
 *
 *                         - Arman, 4 November 2017.
 */
inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

public int no_command();

/*
 * Function name:   remove_church_silence_object
 * Description:     Remove the church silence
 * Arguments:       None
 * Returns:         Nothing
 */
public int
remove_church_silence_object()
{
    remove_object();
} /* remove_church_silence_object */

void
create_object() 
{
    seteuid(getuid());
    set_name("sparkle_church_no_talk_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

init()
{
    ::init();
    add_action("do_all_commands", "", 1);
}

public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"mumble","ponder","wonder","think"});

    if (this_player()->query_wiz_level())
	return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
	return 0;
    else
	return no_command();

    return 1;
}

int
no_command()
{
    write("The local church is a place of tranquility and solitude, and "
        + "you should not break it through idle talk.\n");
    return 1;
}