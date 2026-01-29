
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void
reset_room()
{
  if(!present("_ledge_guru_"))
    {
      object herm;
      seteuid(getuid(TO));
      herm = clone_object(RHUN_DIR + "npc/hill_hermit");
      herm->add_name("_ledge_guru_");
      herm->move(TO,1);
    }
}

create_room()
{
    set_short("Ledge");
    set_long("You are standing atop a narrow ledge in the mountains just west of the Sea of Rhun."
	     + " The view from here is magnificient, and you can see for many miles in every"
	     + " direction. It appears that someone has made this place into a home. There is a simple"
	     + " straw bed dangerously close to the edge, and some cooking utensils are strewn across"
	     + " a small mat.\n");
    add_item("ledge", "The ledge is very narrow, but it is still habitable as there is a sheltering"
	     + " outcropping a couple of yards above.\n");
    add_item("outcropping", "It seems to shelter the ledge from rain and snow.\n");
    add_item(({"bed", "straw bed"}), "The bed is made of straw stuffed into a piece of cloth sewn together"
	     + " along the sides. The bed is very close to the edge and you wonder how anyone could sleep"
	     + " there without falling off.\n");
    add_item(({"cooking utensils", "utensils"}), "The utensils seem clean. You wonder where the owner gets"
	     + " water to dish them with.\n");
    add_item("edge", "As you peer closely at the edge, you almost fall off it!\n");
    add_item("straw", "The straw looks a bit moldy.\n");
    add_item("mat", "The mat is simple and unadorned.\n");
    add_item("view", "@@view_from_ledge");
    add_exit(RHUN_DIR + "hills/p3", "down");

    reset_room();
}

string
view_from_ledge()
{
  string str, ti;
  ti = ctime(time());
  if((ti == "evening") || (ti == "night")) return "The view from here would be truly magnificient, if it wasn't night.\n";
  str = "The view from here is truly magnificient. You can see for leagues in all directions. Looking east, you see the"
    + " plains of the Easterlings spread out, a rugged but beautiful wilderness. Slightly to the north of the plains "
    + "a large glittering body is visible; the Sea of Rhun. Beyond that is a green mass that must be the forest Taur Romen,"
    +" a remnant of the once vast forest that covered large parts of Middle Earth. To your north you can see the towns and"
    + " small settlements that line the valley of the river Celduin. Tracing the line of the Celduin north you imagine seeing"
    + " Esgaroth, with the Lonely Mountain towering above it. West of you you see plains, beyond which lies the famed Mirkwood,"
    + " although it escapes your view. Much closer you see a castle perched on the hills below you to your west.\n"
    + "The mountain is covering your view to the south.\n";
  return str;
}   


