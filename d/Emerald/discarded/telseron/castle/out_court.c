/*
 * The outer court of the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
void reset_room();
 
 
void
create_room()
{
    object gate;
    reset_room();
    set_short("The outer court");
    set_long("   You stand in the outer court of the castle of " +
        "Telseron. The courtyard is large and made of white " +
        "marble. Running down the center is a wide avenue of " +
        "red marble leading to the steps of the portico. Standing " +
        "in the outer court, the castle overwhelms you. Its sheer " +
        "size and glory is something you have never beheld before. " +
        "The building seems perfect, rising from the earth on a " +
        "platform of perfectly carved white marble. The castle is " +
        "faced with mother of pearl and glistens in the sun like a " +
        "jewel. Gracing the front is the portico. It stands at the " +
        "top of some stairs, as if guarding the castle. Behind the " +
        "pediment you see a large dome.\n\n");
 
    add_item(({"floor", "ground", "down"}),
        "The ground is constructed of white marble. It is polished " +
        "to an incredible sheen from the number feet which tread " +
        "across it. Running from the gate to the stone steps is " +
        "an avenue of red marble for royalty. The stones don't show " +
        "any sign of traffic.\n");
    add_item("portico",
        "This large open columned porch marks the entrance to the " +
        "castle of Telseron. Standing on top of the portico are " +
        "marble elven statues, proudly overlooking the grounds. \n");
    add_item("pediment",
        "This low triangular shaped stone sits on top of the outer " +
        "pillars and defines the entrance to the castle. In its center " +
        "are relief statues of elven warriors defending the city.\n");
    add_item(({"stair", "stairs", "staircase"}),
        "Great marble stairs, faced with mother of pearl, ascend to " +
        "the portico.\n");
    add_item("statues",
        "They are sculpted from white marble and stand guard, " +
        "overlooking the outer courtyard.\n");
    add_item("dome",
        "The dome is large and onion shaped. It is shines from " +
        "the light that reflects from its mother of pearl surface.\n");
 
    add_exit( TCASTLE_DIR + "portico", "up", "@@upstairs@@");

    gate = clone_object( TOWNSHIP_DIR + "doors/gate_castle_out");
    gate->move(this_object());
} 
 
 
int upstairs()
{
    write ("You ascend the stairs to the portico.\n");
 
    say(QCTNAME(TP) + " ascends the stairs to the portico.\n");
}
 
void
reset_room()
{
}
