/*
 * Coordinates the list of available tags and which files are sending them.
 * Allows debugger objects to subscribe to tags and files.
 */
#include <macros.h>

public void purge();

static mapping listeners = ([ ]);
static mapping tags = ([ ]);

void
create() 
{
    set_alarm(600.0, 600.0, &purge());
}

void
start_listening(object ob, string tag)
{
    if (!listeners[tag])
        listeners[tag] = ({ });
    listeners[tag] |= ({ ob });
}

void
stop_listening(object ob, string tag)
{
    if (!listeners[tag])
        return;

    listeners[tag] -= ({ ob, 0 });
}

public string *
query_tags()
{
    return m_indexes(tags);
}

public string *
query_files(string tag)
{
    if (!tags[tag])
        return ({ });
    return m_indexes(tags[tag]);
}

public varargs void
send_debug_message(object source, string tag, string message)
{
    string file = file_name(source);
    if (!mappingp(tags[tag]))
        tags[tag] = ([ ]);

    if (!tags[tag][file]) 
        tags[tag][file] = 1;

    object *tag_listeners = listeners[tag] || ({ });
    object *file_listeners = listeners[file] || ({ });
    object *master_listeners = listeners[MASTER_OB(source)] || ({ });

    object *list = tag_listeners | file_listeners | master_listeners;
    list->process_message(message);
}

public void
purge()
{
    foreach (string tag, mapping map: tags)
    {
        foreach (string file, int v: map)
        {
            if (!find_object(file))
                m_delkey(map, file);
        }
    }
}
