#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#define EXPELL_LOG   "/d/Terel/guilds/riders/log/rider_expelled"

string *gNames = ({});
int query_expelled(string name);

void
create_object()
{
    FIX_EUID;
    set_name("expell_logger");
    restore_object(EXPELL_LOG);
}

void
add_expelled(string name)
{
    if(query_expelled(name))
        return;
    gNames += ({ name });
    save_object(EXPELL_LOG);
}

void
remove_expelled(string name)
{
    gNames -= ({ name });
    save_object(EXPELL_LOG);
}
int
query_expelled(string name)
{
    if(member_array(name, gNames) > -1)
        return 1;
    return 0;
}
