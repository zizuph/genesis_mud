#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h"
#define IDEA_FILE SINDAR_RACE_DIR + "ideas"

#include <files.h>

 /*
 * routine to save ideas
 */
void write_msg(string str)
{
    setuid();
    seteuid(getuid());
    write_file("/d/Shire/guild/sindar_racial/ideas", sprintf("\n%-13s (%s)\n%s\n", 
        capitalize(this_player()->query_real_name()), ctime(time()), str));

    write("Ok.\n");
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

/*
 *command to submit ideas
 */
int noidea(string str)
{
    if (strlen(str))
    {
       if (str == "")
       {
           write("siidea [<message>]\n");
           return 1;
       }

       &write_msg(str);
       return 1;
    }

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("done", "");
    return 1;
}
