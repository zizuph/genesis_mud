#include "defs.h"
#pragma save_binary

inherit "/d/Calia/sea/objects/rack";

#define WNUM 2

void
create_rack()
{
    object *wep=allocate(WNUM);
    int i;

	set_adj("weapon");
	set_long(
            "This rack has many attachments for holding all sorts of weapons." +
            "\n");
    for (i=0; i < WNUM; i++)
    {
        seteuid(getuid());
        wep[i]=clone_object(SEA_WEAPONS+"short_spear");
        wep[i]->move(TO);
    }
}

int
fits(object ob)
{
	return member("weapon", ob->query_names());
}