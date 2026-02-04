inherit "/std/shadow";

#include <wa_types.h>

public varargs mixed query_remembered(mixed name)
{
   if(stringp(name))
	return 0;
   else
	return ([]);
}

public varargs mixed query_introduced(mixed name)
{
   if(stringp(name))
	return 0;
   else
	return ([]);
}

public varargs mixed add_remembered(string str)
{
	write("You try to focus, remember...\n");
	return 0;
}

public int query_met(mixed name)
{
    if (objectp(name) && 
       name->query_real_name() == shadow_who->query_real_name())
    {
        return 1;
    }
    if (stringp(name) &&
       name == shadow_who->query_real_name())
    {
        return 1;
    }
	return 0;
}