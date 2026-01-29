
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("On a steep stairway");
  set_long("You precariously stand upon a high, shallow step. The "+
     "dark stairway runs under an arched ceiling parallel with the "+
     "steps. A large wooden gate used to stop passage here leans "+
     "heavily against the northern wall, the lower half broken from "+
     "its hinge. A small hole can be seen in the southern wall "+
     "opposite the gates hinges. The dry, thin air is becoming "+
     "increasingly harder to breath. The stairway runs upwards "+
     "to the west and downwards to the east.\n");

  add_item(({ "staircase", "stairway" }),
     "Certainly one of the steeper ones you've seen. One slip "+
     "could send you tumbling all the way down to your death.\n");
  add_item(({ "steps", "step", "stairs", "stair" }),
     "They are each two feet high by one foot deep.\n");
  add_item(({ "wall", "walls" }),
     "These dark stone walls are fairly smooth. A few cracks "+
     "can be seen marring its surface.\n");
  add_item("ceiling",
     "It is arched in the form of a semi-circle.\n");
  add_item(({ "gate", "wooden gate", "large gate", "large wooden "+
     "gate", "broken gate", "north wall", "northern wall" }),
     "Leaning heavily against the northern wall this thick door "+
     "is barely attached to its upper bronze hinge. Its lower hinge "+
     "has broken free of the wall which supports it. While blackened "+
     "by fire and marred by blades of intruders this sturdy door "+
     "could probably still serve its purpose if its hinges were "+
     "repaired. Three thick bronze bands encircling the door at its "+
     "top, middle, and lower portions remain unbroken adding strength "+
     "to the thick wood. The locking mechanism, a heavy iron bolt, "+
     "remains intact on the backside of the door. The image of a "+
     "large circular shield has been carved into the center of "+
     "the door above its middle band.\n");
  add_item(({ "hinge", "hinges", "bronze hinges" }),
     "These large bronze hinges appear to be very strong. The "+
     "lower one however has been snapped from the wall while "+
     "the upper one strains to hold the heavy door in place. "+
     "Eventually it will break too due to the obvious strain "+
     "placed upon it.\n");
  add_item(({ "band", "bands", "bronze bands" }),
     "These bronze bands are a foot wide and run around the door at "+
     "its top, middle and bottom. Although the rest of the door "+
     "show signs of battle and fire these bands are free of any "+
     "nicks, dents, or stains.\n");
  add_item(({ "shield", "image", "carving" }), "@@shield_image@@");
  add_item(({ "lock", "mechanism", "bolt", "rod" }),
     "Located on the backside of the door below the middle band "+
     "this iron rod is roughly six inches in diameter and looks "+
     "very heavy. It appears to slide across its mountings into "+
     "a hole in the southern wall.\n");
  add_item("hole",
     "A simple hole in the wall roughly six inches in diameter.\n");
 
  add_exit("/d/Shire/khazad/west/wd2","up",0,5);
  add_exit("/d/Shire/khazad/west/wd4","down",0,5);
}
 
int
do_close(string str)
{
  if (str != "gate")
  {
    notify_fail("Close what?\n");
    return 0;
  }
 
  else
  {
    write("You try and close the heavy gate but it wont budge. "+
       "Fixing the hinges might help.\n");
  }
    return 1;
}
 
int
do_slide(string str)
{
  if (str != "bolt into hole")
  {
    notify_fail("Slide what into where?\n");
    return 0;
  }
 
  else
  {
    write("The large bolt barely budges an inch.\n");
    return 1;
  }
}
 
void
init()
{
  ::init();
  add_action(do_close, "close");
  add_action(do_slide, "slide");
}

string
shield_image()
{
  TP->add_prop("_i_have_examined_shield_image",1);
  return "A simple yet finely crafted work of art. You wonder "+
         "who or what crafted it and what it represents.\n";
}
 
public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/wd2")
  {
    ob->catch_msg("You laboriously make your way down the "+
      "treacherous steps.\n");
  }
 
  else if (file_name(from) == "/d/Shire/khazad/west/wd4")
    ob->catch_msg("You laboriously climb the treacherous stairs.\n");
}
