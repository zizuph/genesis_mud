#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,2);
    set_short("The Seagull Center");
    set_long("You are inside the Seagull Center, a haven for new "+
      "visitors in the Port District specifically, and Kabal in general. "+
      "Here, travellers can gain useful information on everything from "+
      "where a ship lands to what interesting places one should visit. This large "+
      "comfortably decorated room possesses several long couches where people "+
      "can sit down and rest. Elegant carpets cover the floor, giving you "+
      "the urge to walk barefoot. The walls of the room each have a "+
      "delightful painting upon them, and from the ceiling hangs a "+
      "golden chandelier. The far end of the room has a large oak desk and a "+
      "cushioned chair.\n");
    add_item(({"long couches","couches","couch"}),"They're covered in "+
      "the softest-looking pillows imaginable.\n");
    add_item(({"pillows","pillow"}),"Fluffy white pillows stuffed with "+
      "incredibly light goose feathers.\n");
    add_item(({"elegant carpets","carpets","carpet"}),"Decorated with "+
      "images of ships on a calm sea, with an equally beautiful sky, "+
      "the image gives you a feeling of serenity.\n");
    add_item(({"walls","wall"}),"The sides have all been white-washed "+
      "and decorated with paintings.\n");
    add_item(({"paintings","painting"}),"All four paintings depict "+
      "daily scenes commonly found here in the Port District, such as "+
      "the docking ships, people walking through the district's plaza and "+
      "customers shopping at the various stores and travelling on the "+
      "basket to the rest of the city.\n");
    add_item(({"ceiling"}),"The ceiling has been painted a brilliant "+
      "white color, which makes this room appear brighter than normal.\n");
    add_item(({"golden chandelier","chandelier"}),"A gold-colored "+
      "set of lights that lies just out of your reach. It provides a "+
      "more than adequate light-source for the area.\n");
    add_item(({"large oak desk","large desk","oak desk","desk"}),
      "A magnificently-crafted oak desk. From the quality and texture of "+
      "the wood's grain, it was probably fashioned from one of the many "+
      "trees growing in the Hespyre mountains. A small plaque rests atop "+
      "the desk.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_item(({"cushioned chair","chair"}),"A plush chair, lined with "+
      "soft cushions. It looks like someone has been sitting in it.\n");
    add_exit(PORT + "s61", "west");
    reset_room();
}

plaque()
{
    return "Jomo the Retired Sea Captain, and Master of Advice.\n";
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/jomo");
	ob1 -> move(TO);
    }

}

