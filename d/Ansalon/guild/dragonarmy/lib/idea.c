#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include <files.h>

#define IDEA_FILE (DRAGONARMY_LOG + "ideas")

private void
write_msg(string str)
{
    setuid();
    seteuid(getuid());
    write_file(IDEA_FILE, sprintf("\n%-13s (%s)\n%s\n%s\n", 
        C(TP->query_real_name()), ctime(time()), file_name(E(TP)), str));
    write("Ok.\n");
}

private void
done(string str)
{
    if (!strlen(str))
    {
        write("Aborted.\n");
        return;
    }
    write_msg(str);
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
