#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;


void
create_icewall_room()
{
    set_short("In an arctic canyon");
    set_long("@@long_descr");


    add_exit("west_path1","north");
    add_exit("west_path3","south");

    add_item("canyon","The canyon is nothing but a deep fissure " +
     "in the snow, further limited by the high cliffs on the east " +
     "and west sides. You ponder why snow doesn't cover this place, and " +
     "reach a conclusion that avalanches on a regular bases must " +
     "bear the snow away, further into the south flatlands.\n");
    add_item(({"cliff","snowy cliff","high cliff"}),"Heavy with " +
     "snow, it looks quite dangerous. You hush, realizing that " +
     "any louder shout might bring down an avalanche!\n");
    add_item(({"castle","dark castle","icewall castle"}),"All you " +
     "can see is the high western wall of the castle. No battlements " +
     "are visible in the open, but narrow archers' slits cut the upper " +
     "part of the wall.\n");
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
  "You are within the arctic canyon. High above you, standing " +
  "on the cliff to the east, looms the dark Icewall Castle. " +
  "High, snow-capped mountains rise some way to the north and west. " +
  "You can follow the canyon north or south.\n");

}

int
do_shout(string str)
{
      if (!strlen(str))
    {
      return 0;
    }

set_alarm(1.5,0.0,"do_avalanche");
return 0;
}

int
do_avalanche()
{
    write("\nAs you shout, the cliffs above you shake and rumble! " +
          "Frozen, you catch your breath as snow cascades down on " +
          "you!\nHowever, before you panic, the rumble stops, and " +
          "the cliffs quiet down. The avalanche bids it time.\n\n");
    say("As " + QTNAME(TP) + " shouts, the cliffs above you " +
          "shake and rumble! Frozen, you catch your breath as " +
          "snow cascades down on you!\nHowever, before you panic, " +
          "the rumble stops, and the cliffs quiet down. The avalanche " +
          "bids it time.\n\n");
    return 0;
}

void
init()
{
    ::init();

    add_action(do_shout, "shout");
}                  