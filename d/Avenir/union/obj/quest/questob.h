#include "../../lib/bits.h"

public void
enter_env(object to, object from)
{
   ::enter_env(to, from);

   if(from || !interactive(to))
    return;

   seteuid(getuid());

   write_file("/d/Avenir/union/log/quest",
    ctime(time()) + " " + to->query_name() + " (#"
   + QNUM(to)+") got the " + short() + " (#"
   + this_object()->query_prop(QUEST_OB) + ") at\n          " 
   + file_name(environment(to))+"\n");
}

