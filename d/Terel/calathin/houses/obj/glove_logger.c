#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#define GLOVE_LOG CALATHIN_DIR+"log/glov_log"

string *gNames = ({});
int query_finder(string name);


void
create_object()
{
    FIX_EUID;
    set_name("glove_logger");
}

void
add_finder(string name)
{
    if(query_finder(name))
        return;
    gNames += ({ name });
    save_object(GLOVE_LOG);
}

void
remove_finder(string name)
{
    gNames -= ({ name });
    save_object(GLOVE_LOG);
}
int
query_finder(string name)
{
    if(member_array(name, gNames) > -1)
        return 1;
    return 0;
}

