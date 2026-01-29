inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

object  attendant, rack;
string  logfile;
int     removed;

public void
set_attendant(object who)
{
    attendant = who;
}

public void
return_book()
{
    set_alarm(0.0, 0.0, "remove_object");
}

public int
query_rack_log()
{
    return 1;
}

public string *
get_array(string str)
{
    string *array, hum, bug;
    int     i, num;
    
    if (sscanf(str, "%s ({\"%s\",})", hum, bug) != 2)
        return ({});
    
    array = ({ hum });
    
    num = sizeof(explode(bug, ","));
    for (i = 0; i < num; i++)
    {
        if (sscanf(bug, "%s\",\"", hum))
        {
            array += ({ hum });
            bug = extract(bug, (strlen(hum) + 3), strlen(bug));
        }
        else
        {
            array += ({ bug });
        }
    }
    
    return array;
}

public void
set_rack(object obj)
{
    int     value, i;
    string  rack_log, *humbug, *dummy;
    
    if (!stringp(rack_log = obj->query_rack_log_file()))
        return;
    
    /* Tried using restore map, but didnt work as suggested in the inherited
       standard file, using hum-bug code to fix this. */
    
    logfile = "";
    rack    = obj;
    
    for (i = 0; i < sizeof(humbug = explode(read_file(rack_log), "\n")); i++)
    {
        dummy = get_array(humbug[i]);
        
        if (!sizeof(dummy))
            continue;
        
        if (sscanf(dummy[0], "timestamp_%d", value) && 
            (time() - value) < 2592000)
        {
            logfile += sprintf("%26-s: %10-s %8-s ", ctime(value),
            capitalize(dummy[1]), (dummy[4] == "enter" ? "stored" : "withdrew"))
            + " [" + dummy[2] + "] " + LANG_ADDART(dummy[3]) + "\n";
        }
    }
}

void
create_object()
{
    set_name("logbook");
    add_name(({"book", "log"}));
    set_adj(({ "worn", "leather-bound" }));
    set_short("worn leather-bound logbook");
    set_long("This is a logbook issued by the Dragonarmy, detailing the usage "
    + "of the armoury. You may read it to get a recent history of rack usage, "
    + "or use more to get a full list. Once finished, you can 'return' it to "
    + "the attendant.\nMore usage: <more - num book> / <more book>\n");
    
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, 500);
}

public status
do_read(string str)
{
    string *lines;
    int     tail;
    
    if (!strlen(str) || (!parse_command(str, ({}),
        "[the] [worn] [leather-bound] 'book' / 'logbook'") &&
        !parse_command(str, ({}),
        "'-' %d [the] [worn] [leather-bound] 'book' / 'logbook'", tail)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (!this_player()->query_guild_leader_occ() &&
        !sizeof(filter(all_inventory(environment(this_player())),
        &->query_guild_leader_occ())))
    {
        if (objectp(attendant))
            attendant->command("say to " + this_player()->short() + " You do "
            + "not have permission to read the armoury logs.");
            
        this_player()->catch_msg((objectp(attendant) ? QCTNAME(attendant) :
        "The attendant") + " retrieves the " + short() + " from you.\n");
        this_player()->tell_watcher((objectp(attendant) ? QCTNAME(attendant) :
        "The attendant") + " retrieves the " + short() + " from "
        + QTNAME(this_player()) + ".\n");
        
        return_book();
        return 1;
    }
    
    if (!strlen(logfile))
    {
        this_player()->catch_msg("The equipment log is empty.\n");
        return 1;
    }
    
    lines = explode(logfile, "\n");
    
    if (query_verb() == "more")
    {
        this_player()->more(implode(lines[(tail ? (sizeof(lines) - tail) : 1)..],
        "\n"));
        return 1;
    }
    
    this_player()->more(implode(lines[(sizeof(lines) - 30)..], "\n"));
    return 1;
}

public status
do_return(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "[the] [worn] [leather-bound] 'book' / 'logbook'"))
    {
        notify_fail("Return what?\n");
        return 0;
    }
    
    this_player()->catch_msg("You return the " + short() + " to the "
    + (objectp(attendant) ? attendant->short() : "attendant") + ".\n");
    this_player()->tell_watcher(QCTNAME(this_player()) + " gives "
    + LANG_ADDART(short()) + " to the " + (objectp(attendant) ?
    attendant->short() : "attendant") + ".\n");
    return_book();
    return 1;
    
}

public void
init()
{
    ::init();
    add_action(do_read,     "read");
    add_action(do_read,     "more");
    add_action(do_return,   "return");
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (objectp(to) && (!living(to) || to == attendant))
    {
        if (!living(to))
            attendant->tell_watcher(QCTNAME(attendant) + " retrieves the "
            + short() + ".\n");
        
        remove_object();
    }
}