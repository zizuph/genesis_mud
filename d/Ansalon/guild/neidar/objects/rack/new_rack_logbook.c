inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/guild/neidar/guild.h"

object  attendant, rack;
string *logfile;
mapping rack_log;

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

public void
set_rack(object obj)
{
    int     val, i;
    string *list, *item;
    
    setuid();
    seteuid(getuid());

    // AK_DEBUG("set_rack called in logbook");
    
    if (!mappingp(rack_log = obj->query_rack_log()) || !m_sizeof(rack_log))
        return;
    
    list = sort_array(m_indexes(rack_log));
    
    for (i = (sizeof(list) - 1); i > -1; i--)
    {
        if (!pointerp(logfile))
            logfile = ({});
        
        if (sizeof(item = rack_log[list[i]]) <= 3)
            continue;
    
        if (sscanf(list[i], "timestamp_%d_", val) && (time() - val) < 2592000)
        {
            // logfile += ({ sprintf("%26-s: %10-s %8-s ", ctime(val),
            logfile += ({ sprintf("%26-s: %10-O %8-s ", ctime(val),
            capitalize(item[0]), (item[3] == "enter" ? "stored" : "withdrew"))
            + " [" + item[1] + "] " + LANG_ADDART(item[2]) });
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
    set_long("This is a logbook which details the usage of the dwarven armoury "
    + "in Iron Delving. You may read it to get a recent history of rack usage. "
    + "Once finished, you can 'return' it to the attendant.\n");
    
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, 500);
}

public status
do_read(string str)
{
    int     tail;
    
    if (!strlen(str) || (!parse_command(str, ({}),
        "[the] [worn] [leather-bound] 'book' / 'logbook'") &&
        !parse_command(str, ({}),
        "'-' %d [the] [worn] [leather-bound] 'book' / 'logbook'", tail)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (!this_player()->query_wiz_level() &&
        (!this_player()->query_guild_leader_occ() &&
        !sizeof(filter(all_inventory(environment(this_player())),
        &->query_guild_leader_occ()))))
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
    
    if (!sizeof(logfile))
    {
        this_player()->catch_msg("The equipment log is empty.\n");
        return 1;
    }
    
    if (tail > (sizeof(logfile) - 1))
        tail = 0;
    
    this_player()->more(logfile[0..(tail ? tail : sizeof(logfile) - 1)]);
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

public varargs void
remove_logbook_object(object dest)
{
    if (!living(dest))
        attendant->tell_watcher(QCTNAME(attendant) + " retrieves the "
        + short() + ".\n");
    
    remove_object();
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
        set_alarm(0.0, 0.0, &remove_logbook_object(to));
} /* enter_env */