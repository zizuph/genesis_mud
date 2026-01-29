
/*
 * Elementalists rack log reader
 * Originally coded by Zima
 * Modified slightly by Jaacar for Elementalists Guilds use
 */

#include <stdproperties.h>
#include <macros.h>
#include <exec.h>

inherit "/std/object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "defs.h"

#define     LOG_READ_SIZE       24576
#define     LAST_ARMAGEDON      (file_time("/GAME_START.3011"))

// Forward function declarations
mapping parse_line(string line);
mapping *parse_log(string file);

/*
 * Function name: create_object
 * Description  : transparent flexible scroll
 */
void
create_object()
{
    set_name("scroll");
    add_name("_elementalist_transparent_scroll_");
    set_pname("scrolls");
    set_adj("transparent");
    add_adj("flexible");
    set_short("transparent flexible scroll");
    set_pshort("transparent scrolls");

    set_long( "The scroll is oddly transparent. There is something magical "
            + "about it. It reads: 'Use me to <observe> a rack, "
            + "chest or shelf. Once you are done with me, you "
            + "can use the command <return scroll> to return me "
            + "to the council chambers.'\n");

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 180);
    add_prop(OBJ_I_VALUE, 1728);
    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_M_NO_STEAL,1);
}

public int
usage()
{
    write("Letters on the transparent scroll glow brightly:\n\n "
        + "'Observe a rack, chest or shelf through me'. Once you "
        + "are done with me, you can use the command 'return "
        + "scroll' to return me to the council chambers.\n");
}

public int
observe_rack(string rack)
{
    object tp = this_player();
    object room = environment(tp);

    if (rack == 0)
    {
        usage();
        return 1;
    }

    tell_room(room, QCTNAME(tp)
            + " raises a magical transparent scroll and starts "
            + "reading from it.\n", tp);

    object env = environment(this_player());
    object rack_obj = present(rack, env);

    if (rack_obj == 0) 
    {
        write("You do not see " + rack + ".\n");
        return 1;
    }

    string log_file = rack_obj->query_rack_log_file();
    
    if (log_file == 0)
    {
        write("The scroll glows brightly, its surface changing vivid colors "
            + "for few moments only to return to its transparent state. "
            + "Magic of the scroll fails to divine anything about this "
            + "item.\n");
        return 1;
    }

    send_debug_message("DEBUG", "Using log file: " + log_file);

    mapping *entries = parse_log(log_file);

    if (entries == 0)
    {
        write("The transparent scroll sparkles a bit and goes dormant.\n");
        return 1;
    }

    if (sizeof(entries) == 0)
    {
        write("The transparent scroll shows on activity on this container.\n");
        return 1;
    }

    send_debug_message("DEBUG", "Retrieved " + sizeof(entries) 
                     + " records from log.");

    write("Letters on the transparent scroll fade away and quickly they are "
        + "replaced with following lines of text: \n\n");

    foreach(mapping entry : entries)
    {
        string action = "";

        if (entry["action"] == "enter")
            action = " added by ";
        else if (entry["action"] == "leave")
            action = " removed by ";

        write(ctime(entry["timestamp"]) + " " 
                + capitalize(entry["what"])
                + action + capitalize(entry["who"]) + ".\n");

    }

    write("\nText fades away turning the scroll transparent and empty again.\n");

    return 1;
}

public int
return_scroll(string str)
{
	if (!str)
	{
		NF("Return what?\n");
		return 0;
	}
	
	if (str != "scroll")
	{
		NF("Return what?\n");
		return 0;
	}
	
	write("As you utter the command, the scroll disappears.\n");
	TO->remove_object();
	return 1;
}

public void
init()
{
    ::init();
    add_action(observe_rack, "observe");
    add_action(return_scroll, "return");
}

private mapping
parse_line(string line)
{
    string ts, who, what, action;

    sscanf(line, "timestamp_%s ({\"%s\",\"%s\",\"%s\",})", ts, who, what, action); 
    if (ts == 0) return 0;
    
    return ([ 
            "timestamp": atoi(ts), 
            "who": who, 
            "what": what, 
            "action": action 
    ]);
}

private mapping*
parse_log(string file)
{
    setuid();
    seteuid(getuid());

    int arma_time = LAST_ARMAGEDON;

    int read_size = min(LOG_READ_SIZE, file_size(file));

    send_debug_message("DEBUG", "Using read size: " + read_size);

    if (read_size == 0) return 0;

    string data = read_bytes(file, -read_size, read_size);

    send_debug_message("DEBUG", "Amount of read data: " + strlen(data));

    if (data == 0) return 0;

    string *lines = explode(data, "\n");

    function no_errors = &operator(!=)(0,);
    function timestamp = &operator([])(,"timestamp");
    function after_arma = &operator(<)(arma_time,);

    mapping* entries = map(lines, parse_line);
    entries = filter(entries, no_errors);
    entries = filter(entries, after_arma @ timestamp);

    return entries;
}

