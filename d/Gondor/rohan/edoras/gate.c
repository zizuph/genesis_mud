/*
 * Revisions : 7 Feb. 2000 adapted to Genesis gem system by Stern
 */
#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"
public int     gates_closed();
public string  gate_desc(); 
       string  read_plaque();
       void    reset_room();

public void
create_gondor()
{
   set_short("inside the gates");
   set_long(BSN("You stand under the gatetower of Edoras. The walls "
     + "are made of big solid stones, which were hewn by the dwarves "
     + "who helped the Rohirrim when they came to these parts of the "
     + "world. Above you is a great arch with an ironbar gate in it. "
     + "You see a golden plaque on the western wall, probably "
     + "containing some valuable information. You'd better give "
     + "yourself the time to read it. To the west and east are "
     + "doorways, leading to guard rooms for the city guard. "
     + "South is the town and if you go north you will be out of "
     + "the city in no time."));
   add_exit(EDORAS_DIR + "city_entr", "north", gates_closed);
   add_exit(EDORAS_DIR + "guard_w",   "west",  0);
   add_exit(EDORAS_DIR + "guard_e",   "east",  0);
   add_exit(EDORAS_DIR + "ingate",    "south", 0);

   add_item(({"plaque", "golden plaque"}), read_plaque());
   add_cmd_item(({"plaque", "golden plaque"}), "read", read_plaque());

   add_item(({"gates","gate","town gates"}), gate_desc);

   clone_object(GEM_DIR + "amber")->move(TO);
   reset_room();
}

public string
read_plaque()
{
    return break_string(
       "\nThis is a two by one foot sign made of gold. "
     + "It is engraved with lovely ceremonious letters.\n",50)
     + "\nIt states:\n" + break_string(
       "Welcome journeyman, to Edoras, capital of Rohan. "
     + "You may rest here and get healed, if you are wounded. "
     + "But beware, evil creatures will not get far into this city.\n\n",50)
     + "       Sir Hamurabbi - Architect and Constructor\n\n";
}

void
add_monster() 
{
    object g;
   int n;
   for (n = 0; n <= 2; n++)
    {
        g = clone_object(EDORAS_DIR + "npc/rguard");
        g->arm_me();
        g->move_living("away", TO);
    }
}    

void
reset_room() 
{
   if (!present("guard",TO)) 
      add_monster();
}

public int
gates_closed()
{
   object  clock = find_object(CLOCK);
   string  time = clock->query_time_of_day();

   if(time == "night" || time == "evening")
   {
      write("The gateguard looks out through a small hatch "
        + "before letting you out.\n");
      return 0;
   }
   write("You pass through the gates out of the city.\n");
   return 0;
}

public string
gate_desc()
{
   object  clock = find_object(CLOCK);
   string  desc,
           time = clock->query_time_of_day();

   desc = "These are the city gates of Edoras. They are made of "
     + "wrought iron and can withstand all but the fiercest attacks. ";
   if (time == "night" || time == "evening")
      desc +=  "They are closed since it is " + time + ".";
   else
      desc += "They are open since it is " + time + ".";
   return BSN(desc);
}

public void
hook_wagon_depart(object wagon, string where)
{
    if (where != "north")
	return;

    switch (tod())
    {
    case "evening":
    case "night":
	tell_room(TO, "The gates open to let the "+wagon->short()+
		  " out of the city.\n");
	tell_room(EDORAS_DIR + "city_entr", "The gates open.\n");
	break;
    default:
	break;
    }
}

public void
hook_wagon_arrive(object wagon, string from)
{
    if (from != "south")
	return;

    switch (tod())
    {
    case "evening":
    case "night":
	tell_room(TO, "The gates close again behind the "+wagon->short()+".\n");
	tell_room(EDORAS_DIR + "city_entr", "The gates close again behind the "+wagon->short()+".\n");
	break;
    default:
	break;
    }
}
