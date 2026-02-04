inherit "/std/shadow";

#include <wa_types.h>

public mixed
query_nonmet_name()
{
    string func = calling_function();

    if(func == "do_die" || func == "set_name")
    {
        return shadow_who->query_nonmet_name();
    }

    return "knuckle-walking " + shadow_who->query_nonmet_name();
}

query_m_in()
{ 
   return "walks in on the knuckles"; 
}

query_m_out()
{
   return "walks on the knuckles";
}
