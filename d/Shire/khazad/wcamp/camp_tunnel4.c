inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("An empty corridor");
  set_long("An empty corridor with a smooth cut ceiling, floor, and "+
     "walls. A narrow shaft in the ceiling lets most of the moist air "+
     "escape thereby keeping this a relatively dry area. By the eastern "+
     "wall is a winch attached to a chain which runs into the ceiling "+
     "above the gate north of you. To the south two large double doors "+
     "stand closed.\n");
/*
  add_item(({ "ceiling", "roof" }),
  add_item(({ "wall", "walls", "eastern wall", "east wall" }),
  add_item(({ "ground", "floor" }),
  add_item(({ "light", "flickering light" }),
  add_item("gate",
  add_item("corridor",
  add_item(({ "doors", "double doors" }),
  add_item(({ "chain", "chains" }),
     "The narrow chain connected to the winch runs upwards into the "+
     "ceiling above the gate.\n");
  add_item("winch",
     "A wheel with a handle on its side. A narrow chain is connected "+
     "to it.\n");
  add_item(({ "shadow", "shadows" }),
     "Cast by the flickering light they dance off the "+
     "ceiling as if possessed by a joyful spirit.\n");
*/
  add_prop(ROOM_I_LIGHT,1);
 
  clone_object("/d/Shire/khazad/obj/cave_gate_b")->move(TO);
  clone_object("/d/Shire/khazad/obj/cave_door_a")->move(TO);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  switch (random(6))
  {
    case 0:
        tell_room(TO, "Shadows dance along the walls.\n");
        break;
    case 1:
        tell_room(TO, "Shadows dance upon the ceiling.\n");
        break;
  }
}            
