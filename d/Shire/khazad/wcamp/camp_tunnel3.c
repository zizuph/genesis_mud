inherit "/d/Shire/khazad/moria_room_drip";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("Within a spacious cave");
  set_long("You comfortably stand within a roughly hewn, spacious cave. "+
     "The cave has a high ceiling that curves downwards and eventually "+
     "meets the floor. The bare stone ground is rather slick due to moss "+
     "that thrives here in this humid environment. Faint trickles of "+
     "water occasionally streak down the sides of this dome-shaped cave. "+
     "In the center of the cave torch stands shed a soft flickering light. "+
     "At the base of the eastern wall a small metal grate can be seen. "+
     "A small tunnel continues off to the west while to the south a large "+ 
     "gate is recessed in the wall.\n");     

  add_item("tunnel",
     "It's a cramped humid tunnel heading to the west.\n");
  add_item(({ "ceiling", "roof" }),
     "It's high and roughly cut from the hard stone. It is dome-shaped "+
     "and moist in some areas due to the strange humidity in this place.\n");
  add_item(({ "wall", "walls", "eastern wall", "east wall" }),
     "They are actually part of the ceiling as it gradually slopes "+
     "downwards.\n");
  add_item(({ "ground", "floor" }),
     "The uneven stone floor is covered in some areas by moss and an "+
     "occasional puddle.\n");
  add_item("moss",
     "It has a translucent greenish color and appears to be common "+
     "around these parts.\n");
  add_item(({ "water", "puddle", "streak", "streaks" }),
     "The water is clear but rather warm. Occasionally it runs down "+
     "from the ceiling and either forms tiny puddles or is drained "+
     "away through a hole at the base of the western wall.\n");
  add_item(({ "light", "flickering light" }),
     "Three torchstands holding large torches seem to be the source "+
     "of it.\n");
  add_item(({ "torchstand", "torchstands", "stand", "stands" }),
     "About five feet in height these brass stands have three "+
     "legs which bends outwards supporting the stand itself. "+
     "Each hold large wooden torches which are seated "+
     "in small metal rings.\n");
  add_item("gate",
     "Recessed in the southern wall its vertical bars appear to "+
     "be made of iron. It blocks passage into a long corridor.\n");
  add_item("corridor",
     "Looking through the bars of the gate you see an empty rectangular"+
     "corridor that leads south to a set of large double door. A few "+
     "feet beyond the gate you notice a winch connected to a chain that "+
     "runs up into the ceiling above the gate.\n");
  add_item(({ "doors", "double doors" }),
     "They are too far from here to make out in detail.\n");
  add_item(({ "chain", "chains" }),
     "The narrow chain connected to the winch runs upwards into the "+
     "ceiling above the gate.\n");
  add_item("winch",
     "A wheel with a handle on its side. A narrow chain is connected "+
     "to it.\n");
  add_item("grate",
     "It consists of a few metal rods placed into the ground at the base "+
     "of the eastern wall. Hot air can be felt flowing out of this "+
     "grate.\n");
  add_item(({ "shadow", "shadows" }),
     "Cast by the flickering light they dance off the "+
     "ceiling as if possessed by a joyful spirit.\n");
  
  add_prop(ROOM_I_LIGHT,1);
 
  clone_object("/d/Shire/khazad/obj/cave_gate_a")->move(TO);
 
  add_exit("/d/Shire/khazad/wcamp/camp_tunnel2","west",0,1);
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
        tell_room(TO, "Warm torch light casts shadows about the room.\n");
        break;
    case 2:
        tell_room(TO, "Shadows dance upon the ceiling.\n");
        break;
  }
}            
