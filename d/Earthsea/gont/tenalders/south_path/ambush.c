inherit "/d/Earthsea/std/room";
#include "defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"


int ambush();
void
create_earthsea_room()
{

    set_short("blah blah");
    set_long("blah blah blah.\n");
}

int
ambush()
{
    int x = 4;
    object *kargs = allocate(4);

    setuid();
    seteuid(getuid(TO));
    if (!present("karg", TO))
    {
	while (x--)
	{
	    kargs[x] = clone_object(KARGS[random(sizeof(KARGS))]);
	    kargs[x]->move(TO);
	}
	(kargs[3])->command("shout ATTACK!!");
	tell_room(TO, "A band of kargs comes running in, screaming "+
	  "warcries!\n", ({}));
	tell_room(TO, "AMBUSH!!\n", ({}));
	return 1;
    }
    return 0;
}
