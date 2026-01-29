/*
  Pax Tharkas, Low level, entrance into the fortress cellar.

  rubbles2.c
  ----------

  Coded ........: 95/01/03
  By ...........: Jeremiah

  Latest update : 95/05/06
  By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

int    light_intens;
string ret_str;


reset_pax_room()
{
    if(light_intens)
        tell_room(TO, "The torch goes out.\n");
   
    light_intens = 0;
    add_prop(ROOM_I_LIGHT, light_intens);
}


create_pax_room()
{
    reset_pax_room();

    set_short("Cellar room filled with rubble");
    set_long("@@long_descr");

    INSIDE;

    add_item("crates", "These are large wooden crates. Some of them are " +
        "labelled SOLACE and others are labelled GATEWAY. They are " +
        "all very effectively sealed, you can't open them.\n");

    add_item(({"rubble", "rubbles"}), "These are rubble of different sizes, " +
        "most of them are rather large. A tunnel has been cleared into " +
        "the heap of rubble.\n");

    add_item("door", "It is an old wooden door. By the hinges you can see, " +
        "that it is some kind of a swing door. There's no lock " +
        "visible, so you can probably walk through it unhindered.\n");

    add_item(({"torch", "large torch"}), "@@torch_descr");

    set_tell_time(90);
    add_tell("@@do_flicker@@");
   
    add_exit(LOW_LEVEL + "rubbles1", "north", 0);
    add_exit(LOW_LEVEL + "guard_room", "west", 0);
    add_exit(LOW_LEVEL + "rubbles_entr", "northeast", 0);
}


void
init()
{
    ::init();
    add_action("light_torch", "light");
    add_action("ext_torch", "extinguish");
}


string
long_descr()
{
    ret_str = "You are standing in a large room. The east part of the " +
        "room is covered by a huge heap of large rubble. A " +
        "small path has been cleared through the rubble, leading " +
        "to a tunnel going northeast. Stacks of wooden crates have " +
        "been placed randomly all over the room. There's an old " +
        "wooden door in the western wall. A large opening leads " +
        "north into another part of the cellar.\n"; 

    if (light_intens == 1)
    {
        ret_str = ret_str + "The room is lit up by a large torch mounted " +
            "in a torch holder on the wall.\n";
    }
    else
    {
        ret_str = ret_str + "A large unlit torch is mounted in a " +
            "torch holder on the wall.\n";
    }
    return ret_str;   
}


string
torch_descr()
{
    if (light_intens == 0)
    {
        write("This is a large unlit torch. It has been placed in an " +
            "iron holder on the wall.\n");
    }
    else
    {
        write("This is a large lit torch. It has been placed in an " +
            "iron holder on the wall. Flames are dancing from the " +
            "head of the torch.\n");
    }
    return "";
} 


int
light_torch(string what)
{
    if (what == "torch")
    {
        if (light_intens == 0)
        {
            light_intens = 1;
            write("You light the large torch.\n");
            say(QCTNAME(TP) + " lights the large torch.\n");
            add_prop(ROOM_I_LIGHT,light_intens);
        }
        else
        {
            write("but .. It's already lit.\n");
        }
        return 1;
    }
    else
    {
        NF("light what?\n");
        return 0;
    }
}


int
ext_torch(string what)
{
    if (what == "torch")
    {
        if (light_intens == 1)
        {
            light_intens = 0;
            write("You extinguish the large torch.\n");
            say(QCTNAME(TP) + " extinguishes the large torch.\n");
            add_prop(ROOM_I_LIGHT,light_intens);
        }
        else
        {
            write("but .. The torch isn't lit.\n");
        }
        return 1;
    }
    else
    {
        NF("extinguish what?\n");
        return 0;
    }
}


string
do_flicker()
{
    if (light_intens == 1)
    {
        return "The light from the torch flickers, strange shadows " +
            "dance across the room.\n";
    }
    return "";
}

