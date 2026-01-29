/* skeletal buckler by percy */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/d/Krynn/solace/graves/local.h"


int times;

void
create_armour()
{
    times = 10;
    set_name("shield");
    add_adj("bone");
    set_short("bone shield");
    set_long("It is a sturdy buckler made of bone.\n");
    set_ac(5);
    set_at(A_SHIELD);
}

int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    if (ph > 0)
	times--;

    if (times < 0)

    {
	query_worn()->catch_msg("Your shield breaks!\n");
	tell_room(environment(query_worn()), "The shield of " +
	  QTNAME(query_worn()) + " breaks!.\n", query_worn());
	set_alarm(0.0, 0.0, remove_object);
    }

    return 0;
}

string
query_recover()
{
    return OBJ + "skel_shield.c:" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
