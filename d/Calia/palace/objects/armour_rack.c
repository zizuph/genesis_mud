#include "defs.h"
#pragma save_binary

inherit RACK;


void
remove_object()
{
    if (living(previous_object()))
       log_file("rack", previous_object()->query_name() +
                       " destructed rack.\n");
    ::remove_object();
}


void
create_rack()
{
	set_adj("armour");
	set_long(
            "This rack has many attachments for holding all sorts of armour." +
            "\n");
}

int 
fits(object ob)
{
        return member("armour", ob->query_names());
}
