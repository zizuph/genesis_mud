/*
 * AV1.c
 * Inside the Avular Main Gates
 * - Alaron JAN 2000
 */

#include "defs.h"
#include <stdproperties.h>
#include "/d/Emerald/sys/macros.h"

#define GATE_MASTER (AVMAIN + "g0")

inherit AVULAR_ROOM;

int knock_gate(string str);
int tryopen_gate(string str);
int check_gates();
void reset_room();
string query_gate_status();

private object guard1;

void
create_avular_room()
{
    set_short("The Gates of Avular");
    set_em_long("A huge, gray stone wall towers over the end of the cobblestoned "+
        "street. Its surface is smooth beyond comparison, not showing a single "+
        "sign of a chip or even any sign of wear or erosion. Secured deep within "+
        "the massive stone wall is a large, black iron gate. The narrow, stone "+
        "road leads away from the gate into the looming blackness.\n");

    add_item( ({"street", "road", "cobblestone road"}),
             "The narrow street is just barely wide enough to support a horse "+
             "and rider beside. It is made up of coal-dark stones. Each stone "+
             "appears to be uniquely cut, every stone having its own completely "+
             "distinct shape. Each of the stones fits snugly together, forming "+
             "a narrow, cobblestoned street.\n");

    add_item( ({"cobblestones", "cobblestone"}),
             "The cobblestones themselves are small, uniquely carved and crafted "+
             "stones, each one having its own distinct size and shape. Somehow, "+
             "despite the apparent randomness of the stones' shapes, they all fit "+
             "together snugly, forming a straight road.\n");


    add_item( ({"gate", "iron gate", "gates", "iron gates", "black gate", "black iron gate"}),
             "The huge iron gate towers before you in the darkness. It stands nearly five "+
             "times the height of the tallest elf. Carved into the black surface of the "+
             "iron gate are countless small symbols whose meaning or origin you can't "+
             "make out. The top of the iron gate has been shaved and bent, making it seem "+
             "almost wavelike. Almost completely hidden within the side of the gate is a "+
             "very small iron door to allow small parties through without opening the "+
             "massive gates. It is currently @@query_gate_status@@.\n");

    add_item( ({"wall", "giant wall", "gray wall", "stone wall",
                "giant stone wall"}),
              "The towering gray stone wall disappears into the thick darkness "+
              "to the north and south. The surface of the wall is eerily smooth, "+
              "without a single bump, chip or imperfection visible. At seemingly "+
              "random intervals, the wall's height raises or lowers, and then some "+
              "random distance from there returns to a median height. Secured deep "+
              "within the thick wall is a huge, black iron gate.\n");

    add_item( ({"door", "small door"}),
              "The small iron door is currently @@query_gate_status.\n");

    add_exit(AVMAIN+"av2", "west");
    add_exit(AVMAIN+"g0", "east", check_gates);


    reset_room();
}

void
reset_room()
{
    if (!guard1)
    {
        guard1 = clone_object(AV_NPC+"gguard");
        guard1->move(this_object());
    }
}

init()
{
    ::init();
    add_action(knock_gate, "knock", 0);
    add_action(knock_gate, "bang", 0);
    add_action(tryopen_gate, "open", 0);
}

int
check_gates()
{
    setuid(); seteuid(getuid());
    if (GATE_MASTER->query_gate_status() == "open")
    {
        return 0;
    }
    else
    {
        write("The door in the massive iron gate is currently closed.\n");
        return 1;
    }
}

int
knock_gate(string str)
{
    if (member_array(str, ({"gate","gates","door","iron gate","on gate",
                            "on gates", "on door"})) == -1)
    {
        notify_fail("Knock on what?\n");
        return 0;
    }

    setuid(); seteuid(getuid());
    if (GATE_MASTER->query_gate_status() == "open")
    {
        write("You don't need to knock on the door, it is open.\n");
        return 1;
    }

    write("A guard shouts to the watch on the other side of the gate for the "+
        "door to be opened.\n");
    GATE_MASTER->open_gate();
    return 1;
}

string
query_gate_status()
{
    setuid(); seteuid(getuid());
    return GATE_MASTER->query_gate_status();
}

int
tryopen_gate(string str)
{
    if (member_array(str, ({"gate", "gates", "door", "iron gate",
                            "small door", "iron gate"})) == -1)
    {
        notify_fail("Open what?\n");
        return 0;
    }

    setuid(); seteuid(getuid());
    if (GATE_MASTER->query_gate_status()=="open")
    {
        write("The door in the giant gate is already open.\n");
        return 1;
    }

    write("The door in the gate is sealed shut. Perhaps a guard can open "+
        "it for you?\n");
    return 1;
}