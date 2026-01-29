/* 
 * Calian Events Log Handler
 *
 * This handler takes care of events such as joining, promotions, and leaving.
 * It allows the guild to keep an accurate history of the dates that events
 * occurred. It is mainly called from the recruiter_code.
 *
 * Created by Petros, March 2009
 */

#pragma save_binary
#pragma no_clone

inherit "/std/object";

#include <std.h>
#include "defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define EVENTS_DIR       "/d/Calia/guilds/calians/texts/events/"

public void
create_object()
{
    setuid();
    seteuid(getuid());
}

public void
add_event_item(object player, string text)
{
    string player_file;
    mapping contents;
    
    player_file = EVENTS_DIR + player->query_real_name();
    if (!mappingp(contents = restore_map(player_file)))
    {
        return;
    }
    
    contents["" + time()] = text;
    save_map(contents, player_file);
}

private string
convert_display_text(string text)
{
    switch (text)
    {
    case "leaving":
        return "Left Calian Warrior's Guild.";
    
    case "promise trust":
        return "Became Calian Trainee.";
    
    case "join follower":
        return "Became Calian Follower.";
    
    case "accept full warrior":
        return "Became Full Calian Warrior.";     
    }
    
    return text;
}

public string
query_events(string name)
{
    string player_file, result;
    mapping contents;

    result = "";
    player_file = EVENTS_DIR + name;
    if (file_size(player_file + ".o") < 0)
    {
        send_debug_message("events_handler", "Could not get content for "
            + player_file + ".o.");
        return result;
    }
    
    if (!mappingp(contents = restore_map(player_file)))
    {
        send_debug_message("events_handler", "Could not get content for "
            + player_file + ".o.");
        return result;
    }
    
    foreach (string timestampstr : sort_array(m_indices(contents)))
    {
        result += ctime(atoi(timestampstr))[4..10] 
            + ctime(atoi(timestampstr))[-4..] + ": " 
            + convert_display_text(contents[timestampstr]) + "\n";
    }
    
    return result;
}
