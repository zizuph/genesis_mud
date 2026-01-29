/*
 * g0.c
 * Main Gates of Avular
 * This room serves as the master controller for gate opening
 * and closing as well as querying gate status.
 * - Alaron JAN 2000
 */
#include "defs.h"
#include "/d/Emerald/sys/faction.h"

#define GATE_OPEN 1
#define GATE_SHUT 0

#define GARGS_STONE 0
#define GARGS_LIVE  1

#define INSIDE_GATE_ROOM AVMAIN + "av1"

inherit AVULAR_ROOM;

private int gatestatus;
private int garg_status;

private object guard1;
private object guard2;

private object garg1;
private object garg2;

private int gatealarm;

void open_gate();
void close_gate();
string query_gate_status();
void reset_room();
int check_gates();

void
create_avular_room()
{
    gatestatus = GATE_SHUT;

    set_short("The Gates of Avular");
    set_em_long("The strange, partial path ends its westward travel at the "+
                "foot of a massive, gray stone wall. The wall towers high, and "+
                "its surface is eerily smooth. Secured deep within the "+
                "barrier is an enormous black iron gate. A chill wind blows "+
                "out of the suffocating blackness to the south and continues "+
                "along the wall, disappearing to the northeast.\n");

    add_item( ({"gate", "gates", "door", "door in gate", "small door",
                "iron gate", "black iron gate", "black gate"}),
             "The huge iron gate looms before you. It stands nearly five "+
             "times the height of the tallest elf. Etched into the black surface "+
             "of the cold iron are dozens of small symbols whose meaning you can't "+
             "make out. The top of the iron gate has been shaved and bent, making "+
             "it seem almost wave-shaped. Almost completely hidden within the "+
             "side of the gate is a very small iron door to allow people to "+
             "pass through. It is currently @@query_gate_status@@.\n");

    add_item( ({"door", "small door", "iron door", "small iron door"}),
             "The small iron door is currently @@query_gate_status@@.\n");

    add_item( ({"symbols", "symbol", "small symbol", "small symbols", "lines"}),
             "The symbols have been carved flawlessly into the surface of "+
             "the cold, black iron gate. The precision of the cuts makes you "+
             "wonder about what kind of tool was used to make the symbols. They "+
             "are all strangely shaped, with crossing and intersecting lines, none "+
             "of them seeming to have any discernable pattern.\n");

    add_item( ({"wall", "large wall", "giant wall"}),
             "The towering gray stone wall recedes into the suffocating blackness "+
             "to the north and south. Its surface is eerily smooth, while the top "+
             "of the wall is strangely shaped. At seemingly random intervals, the "+
             "wall either raises or lowers in height, then at another seemingly "+
             "random distance, returns to normal. Directly before you, secured "+
             "deep within the stone wall is a huge, black iron gate.\n");

    add_exit(AVMAIN+"g1", "northeast");
    add_exit(AVMAIN+"av1", "west", check_gates);
    add_exit(AVMAIN+"g3", "south");

    reset_room();
}

int
check_gates()
{
    if (gatestatus == GATE_SHUT)
    {
        write("The door within the gate is shut, you cannot go that way now.\n");
        return 1;
    }
    else return 0;
}

string
query_gate_status()
{
    if (gatestatus == GATE_OPEN)
        return "open";
    else
        return "closed";
}

void
reset_room()
{
    if (!guard1)
    {
        guard1 = clone_object(AV_NPC+"gguard");
        guard1->move(this_object());
    }
    if (!guard2)
    {
        guard2 = clone_object(AV_NPC+"gguard");
        guard2->move(this_object());
    }
}

int
knock_gate(string str)
{
    if ( member_array(str, ({"gate", "gates", "on gate", "on gates",
                             "door", "on door"})) == -1)
    {
        notify_fail("Knock on what?\n");
        return 0;
    }

    if (gatestatus == GATE_OPEN)
    {
        write("The gates are already open, you don't need to knock on them.\n");
        return 1;
    }
    else
    {
        open_gate();
        return 1;
    }
}

void
open_gate()
{
    int pfac;

    if (!guard1)
    {
        guard1 = clone_object(AV_NPC+"gguard");
        guard1->move(this_object());
    }

    pfac = QUERY_FACTION(this_player(), FG_AVULAR_GUARDS);

    if ( pfac < FACRANK_COMPLAIN )
    {
        guard1->command("say to " + this_player()->query_real_name() +
               " I'll not open the gates for the likes of you.");
        return;
    }

    if ( pfac <  FACRANK_QUESTALLOW )
    {
        guard1->command("say to " + this_player()->query_real_name() +
               " I'll let you in, but you had better not cause any trouble.");
    }
    if ( pfac >= FACRANK_FRIENDLY )
    {
        guard1->command("say to " + this_player()->query_real_name() +
               " Welcome back to Avular, friend.");
    }

    guard1->command("emote unlatches the small door in the side of the gate " +
                    "and pushes it open.");
    tell_room(INSIDE_GATE_ROOM,
              "The small door within the giant iron gate slides open " +
              "smoothly.\n");
    gatestatus = GATE_OPEN;
    gatealarm = set_alarm(10.0,0.0,close_gate);
}

void
close_gate()
{
    if (!guard1)
    {
        guard1 = clone_object(AV_NPC+"gguard");
        guard1->move(this_object());
    }

    guard1->command("emote pulls the door in the side of the giant gate shut " +
            "with a metallic clang.");
    tell_room(INSIDE_GATE_ROOM,
              "The door within the giant gate slams shut with a loud metallic clang.\n");
    gatestatus = GATE_SHUT;
}

int
tryopen_gate(string str)
{
    if (member_array(str, ({"gate", "iron gate", "black iron gate", "black gate"}))==-1)
    {
        notify_fail("Open what?\n");
        return 0;
    }

    if (gatestatus == GATE_OPEN)
    {
        write("The gate is already open.\n");
        return 1;
    }
    else
    {
        write("The gate looks securely locked to you.\n");
        return 1;
    }
}

void
init()
{
    ::init();

    add_action(knock_gate, "knock", 0);
    add_action(knock_gate, "bang", 0);
    add_action(tryopen_gate, "open", 0);
}

