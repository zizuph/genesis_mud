#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object ob, pole;

void
create_icewall_room()
{
    pole = clone_object(OBJK + "pole_nasty.c");
    pole->move(TO);       

    set_short("Under the east wall of the castle");
    set_long("@@long_descr");


    add_exit("east_path3","south");
    add_exit("east_path5","north");

    
    add_cmd_item("cliff","climb","Impossible! The cliff is much too " +
     "steep here. You can find no handholds whatsoever.\n");
    add_item(({"steep path","path"}),"It cuts through the steep cliff, " +
     "working its way up, towards the main gate of the castle. " +
     "Winding as it does, it prevents anyone from simply charging " +
     "the gate with a ram. It also gives the garrison ample time " +
     "to shoot anyone making its way up. The path appears unused, " +
     "and is covered high by white snow.\n");
    add_item(({"cliff","cliffs"}),"The snowy cliff makes the Icewall " +
     "castle easily defended from this flank.\n");
    add_item("mountains","High and heavy with snow, they appear devoid " +
     "of any living inhabitants. Most of them are covered with the great " +
     "Icewall glacier.\n");
    add_item(({"glacier","icewall glacier"}),"The glacier starts high in " +
     "mountains to the north, but over the ages the twinkling icy " +
     "carpet flowed south, into the flatlands.\n");
    add_item("castle","High above you to the west raises the " +
     "Icewall castle. Due to the sharp angle, you cannot see much " +
     "of it, just the tall, dark walls blocking the sky.\n");
    add_item("plains","Stretching as far as you can see, the plains " +
     "are white, and devoid of life.\n");
    add_item(({"forest","ice forest"}), "To the southeast, a frozen " +
     "forest raises from the snow. A scary sight... Who knows what " +
     "dwells in it.\n");

    set_tell_time(800);

    add_tell("It is snowing hard... And white flakes begin to " +
     "cover you from head to toe.\n");
    add_tell("Wind picks up quite suddenly, scattering " +
     "snow and chilling you to the bone. You can " +
     "feel the first jabs of frostbite on your face. " +
     "This is definitely not a friendly land.\n");
    add_tell("You think you have just heard a strange shriek " +
     "carried here by the everpresent freezing wind.\n");
    add_tell("Snow whirls about you, creating myriad of patterns... " +
     "There is a strange beauty in them...\n\n\n" +
     "You shiver and slap your face. It must be the cold.\n");

}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()

{ return ("" +
  "You stand under the east wall of " +
  "the Icewall Castle. Here, the snow-covered, rocky cliff raises " +
  "into the air. High, snow-capped mountains rise " +
  "some way to the north, and behind the castle to the west. " +
  "To your southeast, a solid wall of the frozen forest raises from " +
  "the snow, and barren snow fields stretch as far as you can see " +
  "to the east and northeast. You can follow the cliff wall to the " +
  "north, where a steep path winds up the cliff to the castle's " +
  "main gate, or to the south.\n");

}
           