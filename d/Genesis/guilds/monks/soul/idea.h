#include "defs.h"
#include <files.h>

#define IDEA_FILE (MONK_LOG + "ideas")

void done(string str);

void write_msg(string str)
{
    setuid();
    seteuid(getuid());
    write_file(IDEA_FILE, sprintf("\n%-13s (%s)\n%s\n", 
        capitalize(this_player()->query_real_name()), ctime(time()), str));

    write("Ok.\n");
}

int
_idea(string str)
{
    if (strlen(str))
    {
       write_msg(str);
       return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit(done);
    return 1;
}

void done(string str)
{
    if (!strlen(str))
    {
        write("Aborted.\n");
        return;
    }

    write_msg(str);
}
