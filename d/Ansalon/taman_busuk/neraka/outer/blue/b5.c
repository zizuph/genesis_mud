#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 13 Jul 97 */

inherit OUTER_OUT;

object guard1,guard2;
object gate;

void
create_neraka_room()
{
    set_short("Intersection outside the Blue Army gatehouse");
    set_extra_long("You are at the Blue Army gates that lead into " +
        "the inner city of Neraka. The road intersects here, one " +
        "branch leading west through the gates into the city, while " +
        "the other two branches lead east and south. There are " +
        "wooden sidewalks along the roads here, since the roads are " +
        "often used for wagons and horses. The inner city walls soar " +
        "into the air here, and the gatehouse is dark and forboding. " +
        "There is a doorway to the southwest leading into the gatehouse " +
        "proper.");        
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item("doorway","It is a small doorway leading into the gatehouse.\n");
    add_item(({"walls","city walls","inner city walls","inner walls"}),
        "They are giant walls that surround the inner part of Neraka, " +
        "where only the elite officers of the Dragonarmies are allowed " +
        "to enter. The walls are made of old, grey stone, and there are " +
        "a few slitted windows along them. The gatehouse that the Blue " +
        "Dragon Army is assigned to protect lies in the center.\n");
    add_item("gatehouse","The gatehouse consists of two towers placed " +
        "on the city walls, with a giant, iron gate in between them. It " +
        "looks like it is heavily protected.\n");
    add_item(({"gate","iron gate"}),"The gate efficiently closes " +
        "off all access to the inner city.\n");
    add_item(({"city","inner city"}),
        "You can only see the inner city walls from here.\n");
    add_item("camp","The Blue Army camp is spread out east of here.\n");

    add_exit(NOUTER+"blue/b4","south");
    add_exit(NOUTER+"blue/b8","east");
    add_exit(NOUTER+"blue/gatehouse","southwest","@@enter_gatehouse", 1, 1);
    
    gate = clone_object(NOUTER+"blue/out_gate.c");
    gate->move(TO);

    reset_room();
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
    if(!objectp(guard1))
        guard1 = clone_npc(NNPC+"gatesivak.c","blue");
    if(!objectp(guard2))
        guard2 = clone_npc(NNPC+"gatesivak.c","blue");
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
    (NERAKA_ADMIN)->attack_on_gate("blue");
}
