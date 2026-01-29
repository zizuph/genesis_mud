#pragma strict_types

inherit "/d/Gondor/common/lib/sky.c";

#include <macros.h>
#include <std.h>

#include "/d/Gondor/defs.h"

public int     gates_closed();
public int     do_knock(string str);
public string  gate_desc();

public void
init()
{
    ::init();
    add_action(do_knock,"knock");
}

void
create_room()
{
    set_short("outside Edoras");
    extraline = "You are standing just outside the gates of Edoras. "
      + "The city walls are stretching out to the southeast and "
      + "southwest. As far as your eyes can see the green plains "
      + "continue north. South are the city gates.";

    add_exit(EDORAS_DIR + "gate",      "south",     gates_closed);
    add_exit(ROH_DIR + "road/graves",  "north",     0);
    add_exit(EDORAS_DIR + "by_stream", "southwest", 0);
    add_item(({"gates","gate","town gates"}), gate_desc);

    make_the_room();
}

public int
gates_closed()
{
   string  time;

//   if (SECURITY->query_wiz_dom(TP->query_real_name()) == "Gondor")
    if (this_player()->query_wiz_level())
   {
        write("Welcome, Wizard!\n");
        return 0;
   }

   time = tod();
   if (time == "night" || time == "evening")
   {
       write("The gates of Edoras are closed at night.\n"
	     + "They will open again in the morning.\n");
       return 1;
   }
   else
   {
       write("You pass through the gates into the city.\n");
       return 0;
   }  
}

public string
gate_desc()
{
   string  desc = "These are the city gates of Edoras. "
                + "They are made of wrought iron and can withstand "
                + "all but the fiercest attacks. ",
           time;

   time = tod();
   if ((time == "night") || (time == "evening") )
   {
       desc +=  "They are closed since it is " + time + ".";
   }
   else
   {
       desc += "They are open since it is " + time + ".";
   }
   return BSN(desc);
}

void
gate_reaction()
{
    tell_room(TO,
        "A guard shouts: Go away! Come back in the morning!\n" +
        "A guard shouts: We do not open the gates to the town during the night!\n");
}

public int
do_knock(string str)
{
    string  time;

    NF(CAP(query_verb()) + " on what?\n");
    if(!str || (str != "gate" && str != "on gate"))
        return 0;

    time = find_object(CLOCK)->query_time_of_day();
    if (time == "evening" || time == "night")
    {
        write("You knock on the gate.\n");
        say(QCTNAME(TP) + " knocks on the gate.\n");
        set_alarm(itof(2 + random(5)), 0.0, gate_reaction);
    }
    else
    {
        write("You knock on the open gates. Stupid, isn't it?\n");
        say(QCTNAME(TP) + " knocks on the open gates. Stupid, isn't it?\n");
    }
    return 1;
}

public void
hook_wagon_depart(object wagon, string where)
{
    if (where != "south")
	return;

    switch (tod())
    {
    case "evening":
    case "night":
	tell_room(TO, "The gates open to let the "+wagon->short()+
		  " into the city.\n");
	tell_room(EDORAS_DIR + "gate", "The gates open.\n");
	break;
    default:
	break;
    }
}

public void
hook_wagon_arrive(object wagon, string from)
{
    if (from != "north")
	return;

    switch (tod())
    {
    case "evening":
    case "night":
	tell_room(TO, "The gates close again behind the "+wagon->short()+".\n");
	tell_room(EDORAS_DIR + "gate", "The gates close again behind the "+wagon->short()+".\n");
	break;
    default:
	break;
    }
}
