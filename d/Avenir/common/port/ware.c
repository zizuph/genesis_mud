// file name:        /d/Avenir/common/port/ware.c
// creator(s):       Ilyian
// revision history: Boriska, Aug 95 added thug NPC
//		     Denis, Sep'96: Changes due to the port inheritance recode.
//		     Zielia July 09: Updated descriptions.
// purpose:
// note:
// bug(s):
// to-do:  

#include "port.h"
inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";

public void
create_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("inside the port warehouse");
    set_long("You are inside a dingy warehouse that serves the " +
	     "port. It is of rickety construction, and you can feel " +
	     "the entire structure shake from the winds that howl " +
	     "outside. The north part of the warehouse seems to sag " +
	     "down a bit, and the doorway out is to the east. Crates and " +
	     "boxes lie scattered around the floor, and stacked up on " +
	     "the east wall.\n");
  
    add_item(({ "wall", "walls" }),
	     "The walls of the warehouse are made from sturdy wood, " +
             "although the construction is generally poor " +
             "and seems to have been hurried. The east wall is nearly "+
             "hidden behind the many crates piled against it.\n");

    add_item(({ "east wall"}),
	     "Crates and boxes are stacked all along the east wall, " +
             "nearly hiding it from view. The crates are mostly all " +
             "new imports from all over the Outlands, though a few "+
             "dusty forgotten crates are also viewable, scattered "+
             "amongst the new arrivals.\n");             
               
    add_item(({ "crate", "crates", "box", "boxes" }),
	     "Many crates are strewn about or piled near the east wall. " +
	     "They are for the most part empty. The crates have various " +
             "stamps written on them in many languages.\n");
             
    add_item(({"forgotten crates", "dusty crates" }),
	     "Barely viewable amongst the many other crates piled along "+
	     "the east wall, are several crates that look like they "+
	     "have been sitting here a long time. They are covered with "+
             "a thick layer of dust. Like the other crates, they look "+
             "large and extremely heavy. They are secured with iron "+
             "bands and locks.\n");
  
    add_item(({"stamp", "stamps" }),
	     "Most are in languages you don't " +
             "know, but many bear the makings of distant lands like " +
             "Sparkle, Minas Tirith, Minas Morgul, Re Albi, Gelan, and " +
             "many other distant cities.\n");

    set_tell_time(110);
    add_tell("The whole warehouse shakes from a furious gust " +
	     "of wind that strikes it.\n");
    add_tell("The wind howls through the doorway, making a " +
	     "ghostly noise, and stirring up some dust.\n");
    add_tell("You hear the distant sound of a foghorn.\n");

    IN; LIGHT;

    add_exit(PORT+"port6","east");

    add_object(PORT + "obj/std_crate", 8 + random(8));
    add_object(PORT + "obj/crate", 1);

    add_npc(PORT + "mon/thug", 1);
    add_npc(PORT + "mon/ware_worker", 1);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
        start_room_tells();
}
