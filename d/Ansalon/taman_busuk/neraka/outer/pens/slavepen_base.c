/* Ashlar, 24 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

object *slaves = ({ });
private int slavemax=0,slavetype=0;

void set_slavemax(int sm);
int query_slavemax();
void set_slavetype(int st);
int query_slavetype();

void
reset_neraka_room()
{
	object s;
    slaves -= ({ 0 });

	while (sizeof(slaves) < slavemax)
    {
    	s = this_object()->clone_npc(NNPC + "slave");
        s->set_gender(slavetype);
        slaves += ({ s });
    }
}

void
set_slavemax(int sm)
{
	slavemax = sm;
}

int
query_slavemax()
{
	return slavemax;
}

void
set_slavetype(int st)
{
	slavetype = st;
}

int
query_slavetype()
{
	return slavetype;
}

int
leave_pen()
{
	if (member_array(TP,slaves)!=-1)
    {
    	say(QCTNAME(TP) + " tries to climb out of the pit, but is too weak.\n");
        return 1;
    }
    else
    {
    	write("You climb out of the pit and breathe fresh air again.\n");
        return 0;
    }
}

