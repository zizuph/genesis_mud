/* thirst.c created by Shiva@Genesis
 * This file contains the code for the "thirst" command
 * This file is a part of the vampire guild soul
 */

/* Description
 * -----------
 * This command simply gives a vampire an indication of his/her
 * thirst level.
 */

#include "../guild.h"

int
thirst(string str)
{
    int i;
    object *oblist;
    string msg;
  
    if (strlen(str))
    {
        if (!sizeof(oblist = parse_this(str, "[the] %l")))
        {
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
        }
  
        for (i = 0; i < sizeof(oblist); i++)
        {
            msg = oblist[i]->desc_vamp_thirst(this_player());
            if (!strlen(msg))
            {
                write("You can't seem to tell.\n");
                continue;
            }
            
            write(msg);
        }

        return 1;
    }

    msg = this_player()->desc_vamp_thirst();
    write((strlen(msg) ? msg : "You can't seem to tell.\n"));
    return 1;
}
