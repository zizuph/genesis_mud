#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#define KILL_LOG  LAST_DIR+"log/gwailin_kill"

string *gNames = ({});
int query_killer(string name);

void
create_object()
{
    FIX_EUID;
    set_name("kill_logger");
    restore_object(KILL_LOG);
}

void
add_killer(string name)
{
    if(query_killer(name))
        return;
    gNames += ({ name });
    save_object(KILL_LOG);
}

void
remove_killer(string name)
{
    gNames -= ({ name });
    save_object(KILL_LOG);
}
int
query_killer(string name)
{
    if(member_array(name, gNames) > -1)
        return 1;
    return 0;
}
