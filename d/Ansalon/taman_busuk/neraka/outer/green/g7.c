#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

object guard1,guard2;
object gate;
void reset_neraka_room();

void
create_neraka_room()
{
	set_short("Outside the Green Dragonarmy gatehouse");
    set_extra_long("You are at the Green Dragonarmy gates that lead into " +
        "the inner city of Neraka. The dirt road you stand upon leads " +
        "west back to the camp, or east into the city. There are " +
        "wooden sidewalks along the roads here, since the roads are " +
        "often used for wagons and horses. The inner city walls soar " +
        "into the air here, and the gatehouse is dark and forboding. " +
        "There is a doorway to the northeast leading into the gatehouse " +
        "proper. A road leads north from here, towards the White Quarter.");
	set_quarter(GREEN);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item("doorway","It is a small doorway leading into the gatehouse.\n");
    add_item(({"walls","city walls","inner city walls","inner walls"}),
        "They are giant walls that surround the inner part of Neraka, " +
        "where only the elite officers of the Dragonarmies are allowed " +
        "to enter. The walls are made of old, grey stone, and there are " +
        "a few slitted windows along them. The gatehouse that the Green " +
        "Dragonarmy is assigned to protect lies in the center.\n");
    add_item("gatehouse","The gatehouse consists of two towers placed " +
        "on the city walls, with a giant, iron gate in between them. It " +
        "looks like it is heavily protected.\n");
    add_item(({"gate","iron gate"}),"The gate efficiently closes " +
        "off all access to the inner city.\n");
    add_item(({"city","inner city"}),
        "You can only see the inner city walls from here.\n");
    add_item("camp","The Green Dragonarmy camp lies westwards of here.\n");

    add_exit(NOUTER+"green/gatehouse","northeast","@@enter_gatehouse", 1, 1);
    add_exit(NOUTER+"green/g6","west",0,0,0);
	add_exit(NOUTER+"green/g23","north",0,0,0);

	gate = clone_object(NOUTER+"green/out_gate.c");
    gate->move(TO);
    reset_neraka_room();
}
int
enter_gatehouse()
{
    object drac;
    drac = present("draconian",TO);

    if (!(NERAKA_ADMIN)->query_may_enter_city(TP,drac,1))
    {
        write("The " + drac->short() + " blocks you from entering the " +
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
        guard1 = clone_npc(NNPC+"gatesivak.c","green");
    if(!guard2)
        guard2 = clone_npc(NNPC+"gatesivak.c","green");
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
    (NERAKA_ADMIN)->attack_on_gate("green");
}
