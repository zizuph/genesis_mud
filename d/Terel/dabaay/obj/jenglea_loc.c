#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#define JENGLEA_LOG  DABAAY_DIR + "log/jenglea.loc"

string gLocation = "";
string *gLocales = ({"s2","n16","e1","bwalk_6","bwalk_3","square2_3","square1_3"});
int query_locale(string name);

void
create_object()
{
    FIX_EUID;
    set_name("jenglea_loc");
    gLocation = gLocales[random(sizeof(gLocales))];    
    write_file (JENGLEA_LOG, gLocation + "(" +ctime(time()) +")\n");
}

int
query_locale(string name)
{
    if(name == gLocation)
        return 1;
    return 0;
}
