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
	set_adj("weapon");
	set_long(
            "This rack has many attachments for holding all sorts of weapons." +
            "\n");
}

int
fits(object ob)
{
	return member("weapon", ob->query_names());
}
