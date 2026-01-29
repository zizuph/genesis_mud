#include "../guild.h"
#include <files.h>

#define IDEA_FILE VAMP_LOG_DIR + "ideas"

void write_msg(string str)
{
    write_file(IDEA_FILE, sprintf("\n%-13s (%s)\n%s\n", 
        capitalize(this_player()->query_real_name()), ctime(time()), str));

    write("Ok.\n");
}
       
int videa(string str)
{
    if (strlen(str))
    {
       write_msg(str);
       return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("done", "");
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
        
