#include "defs.h"
#pragma save_binary

inherit "/d/Calia/sea/objects/rack";

#define ANUM 4

void
create_rack()
{
    object *arm=allocate(ANUM);
    int i;

	set_adj("armour");
	set_long(
            "This rack has many attachments for holding all sorts of armour." +
            "\n");
    for (i=0; i < ANUM; i++)
    {
        seteuid(getuid());
        arm[i]=clone_object(SEA_ARMOURS+"helmet");
        arm[i]->move(TO);
    }
}

int 
fits(object ob)
{
        return member("armour", ob->query_names());
}