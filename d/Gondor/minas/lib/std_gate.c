#pragma strict_types

#include <macros.h>

#include "/d/Gondor/defs.h"

#define GUARD_FILE  MINAS_DIR + "npc/cguard"

public string  set_other_side(string str = 0);

static int     Gate_Open = 0;
static object *Guard = allocate(3);
static string  Other_Side;

public int
query_gate_open()
{
    return Gate_Open;
}

public int
close_gate()
{
    if (Gate_Open)
    {
        Gate_Open = 0;
        tell_room(TO, "The gates slowly swing shut again.\n");
        if (!strlen(Other_Side))
            set_other_side();
        tell_room(Other_Side, "The gates are closed again.\n");
        return 1;
    }
    return 0;
}

public int
open_gate(int delay = 2)
{
    if (Gate_Open)
        return 0;

    Gate_Open = 1;
    tell_room(TO, "The gates open slowly.\n");
    if (!strlen(Other_Side))
        set_other_side();
    tell_room(Other_Side, "The gates open slowly.\n");
    set_alarm(itof(delay), 0.0, close_gate);
    return 1;
}

public string
exa_gate()
{
    string  desc = ("This is the "+TO->query_circle()+" Gate that guards the City. ");
    if (Gate_Open)
        desc += "Presently it is open.";
    else
        desc += "The gates are closed, and you will not get through without a password.";

    return (BSN(desc));
}

public int
gate_closed()
{
    switch (TO->tod())
    {
        case "evening":
        case "night":
        case "early morning":
            write("A guard says: The gate is usually closed at night, but...ok.\n");
            write("He opens the gates a little, enough for you to slip out.\n");
            break;
        default:
            break;
    }
    return 0;
}

public void
reset_room()
{
    TO->clone_npcs(Guard, GUARD_FILE, -1.0);
}

public string
set_other_side(string str = 0)
{
    int     i;
    mixed  *exits;

    if (strlen(str))
        Other_Side = str;
    else if ((i = (member_array("@@pass_gate@@",
        (exits = TO->query_exit())))) >= 0)
        Other_Side = exits[i-2];

    return Other_Side;
}

public string
query_other_side()
{
    if (!strlen(Other_Side))
	set_other_side();
    return Other_Side;
}

public int
pass_gate()
{
    if (gate_closed())
        return 1;

    open_gate();
    return 0;
}
