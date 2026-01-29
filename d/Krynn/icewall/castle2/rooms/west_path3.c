#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;


void
create_icewall_room()
{
    set_short("At the mouth of an arctic canyon");
    set_long("@@long_descr");


    add_exit("west_path2","north");
    add_exit("/d/Krynn/icewall/outside/bottom_of_ice","southeast");

    add_item(({"cliff","cliffs"}),"Here, they begin to rise from the " +
     "ground, but are yet to little to impress any mountaneer.\n");
    add_item("canyon","The canyon is nothing but a deep fissure " +
     "in the snow, further limited by the high cliffs on the east " +
     "and west sides. You ponder why snow doesnt cover this place, and " +
     "reach a conclusion that avalanches on a regular bases must " +
     "bear the snow away, further into the south flatlands.\n");
    add_item("mountains","High and heavy with snow, they appear devoid " +
     "of any living inhabitants. Most of them are covered with the great " +
     "Icewall glacier.\n");
    add_item(({"glacier","icewall glacier"}),"The glacier starts high in " +
     "mountains to the north, but over the ages the twinkling icy " +
     "carpet flowed south, into the flatlands.\n");

    set_tell_time(800);

    add_tell("It is snowing hard... And white flakes begin to " +
     "cover you from head to toe.\n");
    add_tell("With a rustle, more snow slides down the cliff to "+
     "rest at its base!\n");
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
  "You stand at the mouth of an arctic canyon, which opens to the " +
  "north. The ground rises visibly, yet the cliffs on both sides " +
  "of the canyon shoot into the sky much faster. " +
  "High, snow-capped mountains rise some way to the north and west. " +
  "You can follow the canyon north or turn back to the icy " +
  "staircase to the southeast.\n");

}
           