/* Ashlar, 19 Jul 97 */
/* Navarre July 3rd 2006, fixed typo, was dirt leads north, lacked the road */
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit OUTER_OUT;

object guard1,guard2;
object gate;

void
create_neraka_room()
{
	set_short("Outside the main gates of Neraka");
    set_extra_long("You stand outside the main gates of Neraka. A dirt " +
        "road leads north away from the gate, into the mountains in the " +
        "distance. "+
        "The inner city walls soar " +
        "into the air here, and the gatehouse is dark and forboding. " +
        "There is a doorway to the southeast leading into the gatehouse " +
        "proper.");

    add_item_dirtroad();
    add_item("doorway","It is a small doorway leading into the gatehouse.\n");
    add_item(({"walls","city walls","inner city walls","inner walls"}),
        "They are giant walls that surround the inner part of Neraka, " +
        "where only the elite officers of the Dragonarmies are allowed " +
        "to enter. The walls are made of old, grey stone, and there are " +
        "a few slitted windows along them.\n");
    add_item("gatehouse","The gatehouse consists of two towers placed " +
        "on the city walls, with a giant, iron gate in between them. It " +
        "looks like it is heavily protected.\n");
    add_item(({"gate","iron gate"}),"The gate efficiently closes " +
        "off all access to the inner city.\n");
    add_item(({"city","inner city"}),
        "You can only see the inner city walls from here.\n");

    add_exit(NOUTER+"main/gh1","southeast","@@enter_gatehouse", 1, 1);
    add_exit(NOUTER+"main/r2","north");

	gate = clone_object(NOUTER+"main/out_gate.c");
    gate->move(TO);
    reset_room();
}

int
enter_gatehouse()
{
    object g;
    g = present("guard",TO);

    if (!(NERAKA_ADMIN)->query_may_enter_city(TP,g,1))
    {
        write("The " + g->short() + " blocks you from entering the " +
            "gatehouse.\n");
        return 1;
    }
    else
    {
        write("You enter the gatehouse.\n");
        return 0;
    }
}

void
reset_neraka_room()
{
    if(!guard1)
    {
        guard1 = clone_npc(NNPC+"gateguard.c");
        guard1->add_name("gate_guard");
    }
    if(!guard2)
    {
        guard2 = clone_npc(NNPC+"gateguard.c");
        guard2->add_name("gate_guard");
    } 
}

int
query_attack_going_on()
{
    if (guard1->query_attack() || guard2->query_attack())
        return 1;
    else
        return 0;
}

int
query_defenders_left()
{
    if (objectp(guard1) || objectp(guard2))
        return 1;
    else
        return 0;
}

object
query_gate()
{
    return gate;
}

/* called by the guards */
void
sound_alarm()
{
    (NERAKA_ADMIN)->attack_on_gate("main");
}

/* called by admin object */
void
raise_portcullis()
{
    object g;
    g = P("guard",TO);
    if (g)
        g->command("open gate");
}

void
lower_portcullis()
{
    object g;
    g = P("guard",TO);
    if (g)
        g->command("close gate");
}
