/*
 *  IGARD_WALL + "closed_gate.c"
 *
 *  Broken southern gate of Isengard.
 *
 *  Last modified by Alto, 03 January 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();
public string      long_desc();
public int         check_huorn();

object             actor;
static object      *Ent   = allocate(2);

public void
create_gondor()
{
    set_short("The broken rubble of the southern gate of Isengard");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();

    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_item(({"door", "doors", "gate", "gates", "entrance",
        "great gate", "great southern gate"}), "The formerly mighty "
        + "doors of iron now lay broken and shattered upon the rubble "
        + "of the Ring Wall.\n");
    add_item(({"wall", "ring wall", "ringed wall", "rubble",
        "heap of rubble"}), "The great wall "
        + "of Isengard once stood at least one hundred feet tall and "
        + "curved away to the west and east as far as the eye could "
        + "see. Now it is nothing but an impassible heap of rubble.\n");
    add_item(({"landscape", "natural landscape", "terrain"}), "Here at "
        + "the foot of the Misty Mountains, the landscape is partly flat "
        + "but also has many sudden projections of black rock. The wall "
        + "before you is made from a combination of these natural "
        + "outcroppings as well as quarried stone worked by the hands "
        + "of Men.\n");
    add_item(({"rock", "black rock"}), "The great ring wall was made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men. It now is nothing more than an impassible heap of "
        + "rubble.\n");
    add_item(({"street", "wide street"}), "A wide street leads south "
        + "from the great gate. It is made from great flat stones, "
        + "squared and laid with great skill. No blade of grass can "
        + "be seen in any joint.\n");
    add_item(({"stones", "flat stones", "great flat stones"}), "The "
        + "flat and squared stones are made from the same black rock "
        + "used in the construction of the ring wall.\n");
    add_item(({"isengard", "fortification"}), "The fortification of "
        + "Isengard stands "
        + "directly north from here. It is now a wrecked and wretched "
        + "ruin of its former glory. Only the tower Orthanc seems to "
        + "remain intact.\n");
    add_item(({"tower", "mighty tower", "orthanc", "peak", "isle"}), 
        "Beyond the crumbled Ring Wall there stands a tower of marvellous "
        + "shape. It was fashioned "
        + "by the builders of old, who smoothed the Ring of Isengard, and "
        + "yet it seems a thing not made by the craft of men, but riven "
        + "from the bones of the earth in the ancient torment of the hills. "
        + "This is Orthanc, a peak and isle of rock, black and gleaming "
        + "hard. Four mighty piers of many-sided stone are welded into "
        + "one, but near the summit they open into gaping horns, their "
        + "pinnacles sharp as the points of spears, keen-edged as knives.\n");
    add_item(({"pier", "piers"}), "The tower Orthanc is made from "
        + "four mighty piers of many-sided stone, welded into one.\n");
    add_item(({"horn", "horns"}), "Four gaping horns open atop the mighty "
        + "tower, their pinnacles sharp as the points of spears, keen-edged "
        + "as knives.\n");
    add_item(({"pinnacle", "pinnacles"}), "The pinnacles of the gaping "
        + "horns are sharp as the points of spears, keen-edged as knives.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(IGARD_EXTERIOR + "status_room.c", "south", check_huorn, 2, 1);

    reset_room();
}


public void
reset_room()
{
    clone_npcs(Ent,  IGARD_NPC + "igard_ent",  -1.0);
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}


string
long_desc()
{
    return "You stand before a massive heap of rubble that is the wrecked "
      + "and wretched remains of the once mighty ring wall of Isengard." 
      + sky_desc() 
      + " A tremendous calamity has befallen this place, but whether it was "
      + "leveled by some great engine of war, some mighty feat of sorcery, "
      + "or perhaps a power far older and more subtle, is not apparent. "
      + "A street leads south and away from the devastation of the massive "
      + "ring wall.\n";
}


public int
knock_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("What is it that you are trying to knock on?\n");
       return 0;
    }

    write("The gates are smashed beyond function. You cannot pass.\n");
    tell_room(environment(actor), "You notice " 
        + QTNAME(actor) + " foolishly trying to knock on the smashed "
        + "gates.\n", ({actor}));
    return 1;

}


public int
push_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("What would you like to push on?\n");
       return 0;
    }

    write("The gates are smashed beyond function. You cannot pass.\n");
    tell_room(environment(actor), "You notice " 
        + QTNAME(actor) + " foolishly trying to push on the smashed "
        + "gates.\n", ({actor}));
    return 1;

}


public void
init() 
{
    ::init();

    add_action(knock_gate,      "knock");
    add_action(push_gate,       "push");
}


public int
check_huorn()
{

    switch (TP->query_race())
    {
    case "huorn":
        return 1;
	       break;
    case "ent":
        return 1;
        break;
    default:
	       break;
    }

    if (!TP->query_enemy() || !TP->query_attack())
    {
	       write("Feeling rather shaken, you leave the devastation of Isengard "
            + "behind.\n");
	       return 0;
    }

	   write("You dare not turn your back on the enemy!\n");
	   return 1;
    
}


