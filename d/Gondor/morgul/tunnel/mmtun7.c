inherit "/d/Gondor/morgul/tunnel/std_tunnel";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "tunnel_door.h"

#define OTHER_ROOM  (MORGUL_DIR + "tunnel/mmtun8")

/* f_door = 0: door closed; f_door = 1: door open */
int f_door;
int f_door_alarm;

int set_f_door(int i);

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun6", "up", 0, 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun8", "southwest", "@@check_door@@", 4);

    make_the_room("@@extra_desc@@");

    remove_item("wall");
    add_item(({"gate","door","wall","metal wall","metal plate","plate"}), VBFC_ME("exa_door"));
    remove_item("ceiling");
    remove_item("roof");
    add_item(({"ceiling","roof"}), VBFC_ME("exa_ceiling"));
}

string extra_desc()
{
  string desc;
  desc = "To the northeast, the tunnel leads steeply upwards, ";

  if(f_door)
    desc += "while in the other direction the floor levels out. Just " +
      "under the ceiling you can see a thick metal plate protruding. ";
  else
    desc += "while in the other direction a metal wall blocks your " +
     "progress. ";

  return "You seem to have reached the deepest part of this tunnel.\n" +
    BS(desc);
}

int check_door()
{
  object partner;

  if(f_door)
  {
    if(partner = HATCH1_ROOM->query_wheel_user())
    {
      if(partner->query_prop(MORGUL_ENTRY_HATCH) == 2)
        partner->change_prop(MORGUL_ENTRY_HATCH,3);
    }
    if(partner = HATCH2_ROOM->query_wheel_user())
    {
      if(partner->query_prop(MORGUL_ENTRY_HATCH) == 2)
        partner->change_prop(MORGUL_ENTRY_HATCH,3);
    }
    return 0;
  }
  else
  {
    write("The metal wall blocks your progress.\n");
    return 1;
  }
  write("\nBUG!\n\n");
  return 1;
}

void open_msg(int j)
{
  mixed *exits;
  int i;

  tell_room(TO, BSN("Suddenly, there is a horrible noise like metal " +
    "scratching over rock coming from " +
    "the metal plate blocking the passage to the southwest.") +
    "\nSSSSKKKKKKKRRREEEEEEEEEEEEEEE!\n\n" +
    BSN("Then you notice that the metal plate is slowly moving upwards, " +
    "disappearing into the tunnel roof.")  );

  exits = query_exit();
  for(i = 0; i < sizeof(exits); i+=3)
  {
    if(exits[i] != OTHER_ROOM)
      tell_room(exits[i], 
        "Suddenly there is a terrible noise like metal " +
        "scratching over rock coming from somewhere:\n"+
        "\nSSSSKKKKKKKRRREEEEEEEEEEEEEEE!\n\n");
    else
      tell_room(exits[i],
        BSN("Suddenly, there is a horrible noise like metal scratching over " +
        "rock coming from the metal plate blocking the passage to the " +
        "northeast.") +
        "\nSSSSKKKKKKKRRREEEEEEEEEEEEEEE!\n\n" +
        BSN("Then you notice that the metal plate is slowly moving upwards, " +
        "disappearing into the tunnel roof.")  );
  }
  if(j == 1 && !get_alarm(f_door_alarm))
    f_door_alarm = set_alarm(0.0, 0.0, &set_f_door(0));
}

void close_msg()
{
  mixed exits;
  int i;

  tell_room(TO, "Suddenly, there is a tremendously loud bang.\n"+
    "\n BAAAANNG!!!! \n\n" + 
    BSN("When you recover from the shock, you notice that the metal " +
    "plate now blocks the passage southwest. It must have fallen " +
    "down from its position in the ceiling. "));

  exits = query_exit();
  for(i = 0; i < sizeof(exits); i+=3)
  {
    if(exits[i] != OTHER_ROOM)
      tell_room(exits[i],
        "Suddenly there is a tremendously loud bang coming from somewhere.\n"+
        "\n BAAAANNG!!!! \n\n");
    else
      tell_room(exits[i],
        "Suddenly, there is a tremendously loud bang.\n"+
        "\n BAAAANNG!!!! \n\n" +
        BSN("When you recover from the shock, you notice that the metal " +
        "plate now blocks the passage northeast. It must have fallen " +
        "down from its position in the ceiling. "));
  }
}

int set_f_door(int i)
{
  if(i != 0 && i != 1 && i != -1)
    return 0;
  if(f_door == 0 && i != 0)
    open_msg(i);
  else if(f_door == 1 && i == 0)
    close_msg();
  f_door = ABS(i);
  return 1;
}

int query_f_door()
{
  return f_door;
}

string exa_door()
{
  if(f_door)
    return BSN("You can see the lower end of a thick metal plate protruding " +
      "from the ceiling. The upper end of the plate is hidden in the ceiling. " +
      "There are grooves carved into the rock just where the plate meets the " +
      "walls and the floor. The plate probably can be lowered into these " +
      "grooves, thereby blocking the passage southwest, but there is no " +
      "mechanism for closing the door visible in this room. ");
  else
    return BSN("The metal plate blocks the passage to the southwest. It is " +
      "made of thick dark metal. Where it meets the walls, the floor and the " +
      "ceiling, it does not end but disappears into the rock. There must be " +
      "a way to open it, but you cannot see any mechanism or lock. ");
}

string exa_ceiling()
{
  if(f_door)
    return BSN("The lower end of a thick metal plate is protruding from the " +
      "ceiling southwest of here. ");
  else
    return "The ceiling is too high for you to reach. \n";
}

init()
{
    ::init();
    add_action("do_push","push");
    add_action("do_push","press");
    add_action("do_open","open");
    add_action("do_open","move");
}

int do_push(string str)
{
    string  vb      = query_verb();

    NF(CAP(vb) + " what?\n");
    if(!str || (str != "gate" && str != "door" && str != "wall" &&
        str != "metal wall" && str != "metal plate" && str != "plate") )
        return 0;

    write("You " + vb + " the metal wall. \n");
    SAY(" " + vb + "es the metal wall.\n");
    tell_room(TO,"Nothing happens.\n");
    return 1;
}

int do_open(string str)
{
    string  vb      = query_verb();
 
    NF(CAP(vb) + " what?\n");
    if(!str || (str != "gate" && str != "door" && str != "wall" &&
        str != "metal wall" && str != "metal plate" && str != "plate") )
        return 0;

    write("You try to " + vb + " the gate, but you find no way to achieve this. \n");
    SAY(" tries to "+ vb +" the gate, but finds no way to achieve this.\n");
    return 1;
}
    

  
