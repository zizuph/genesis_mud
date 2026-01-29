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

    set_short("At the winding path");
    set_long("@@long_descr");


    add_exit("east_path4","south");
    add_exit("east_path6","west","@@west",30);
    add_exit("snow_plain1","east",0,1,1);
    
    add_cmd_item("cliff","climb","Impossible! The cliff is much too " +
     "steep here. You can find no handholds whatsoever. The only " +
     "way up is by following the winding path.\n");
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
    add_item(({"main gate","gate"}),"To the west, high up the cliff, " +
     "a dark gate has been set in the castle's wall. The gate is " +
     "barred, and doesnt look inviting at all. Snow has heaped high " +
     "beside it, and it appears unused in quite some time.\n");
    add_item(({"sled marks","marks"}),"The sharp, frozen " +
      "surface of the fresh snow is cut deep by twin parallel " +
      "marks of a sled being pulled towards, or from the castle. " +
      "Judging by the vastness of the snow field surrounding you, " +
      "it would be suicide to try and find a way on your own. " +
      "If you must venture out on the snow fields, better to " +
      "follow the sled, wherever it went, and hope it " +
      "and its owners didnt fall into a bottomless ravine or fell " +
      "to one of the myriad of horrible deaths readily available " +
      "in the frozen land. The sled marks lead east from here. " + 
      "To the west, they simply vanish on harder-packed snow.\n");
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
  "into the air and a winding path makes its way up the cliff, all " +
  "the way to the castle's main gate. High, snow-capped mountains rise " +
  "some way to the north, and behind the castle to the west. " +
  "Far to your southeast, a solid wall of the frozen forest raises from " +
  "the snow, and barren snow fields stretch as far as you can see " +
  "to the north, northeast and east. You can follow the " +
  "steep path to the west, or follow the castle's wall to the south. " +
  "The way north is blocked by ogre-high mounds of snow. Journey east, " +
  "out in the snow plains, could very well be suicidal... But wait! " +
  "Suddenly, you notice sled marks cutting into the snow there.\n");

}
int
west()
{
   write("Fighting your way through the mounds of snow, you slowly " +
    "make your way up the steep path. Its an exhausting, and time " +
    "consuming experience.\n");
   say(QCTNAME(TP) + " fights his way through the mounds on snow, " +
    "climbing the steep path to the west. It takes his time.\n");
   return 0;
}
           