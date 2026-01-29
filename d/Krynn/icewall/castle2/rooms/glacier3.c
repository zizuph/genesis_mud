#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;


void
create_icewall_room()
{
    set_short("On the ice, very high above the battlement");
    set_long("@@long_descr");

    add_item(({"slope","icy slope"}),"Aye, its a slope, and its " +
     "made out of ice! Who knows where it leads...\n");

    set_tell_time(800);

    add_tell("It is snowing hard... And white flakes begin " +
     "cover your back.\n");
    add_tell("Wind picks up quite suddenly, scattering " +
     "snow and chilling you to the bone. You cling " +
     "closer to the icy slope, hoping to keep your hold upon it.\n");
    add_tell("You think you have just heard a strange shriek " +
     "carried here by the everpresent freezing wind.\n");
    add_tell("Your hands feel numb from grasping at the ice. You " +
     "feel you shouldn't stay up here for too long.\n");
    remove_prop(ROOM_I_INSIDE);
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
  "You precariously to a steep ice flow, extending from the glacier-covered " +
  "mountain to the north all the way to the castle. Way down to the " +
  "south, the ice already flows over the battlement, and " +
  "far down and a bit to the west a lower part of the glacier reaches under an archer's " +
  "slit. Directly north, the glacier becomes extremely steep. " + 
  "Only an expert climber could safely continue up from here.\n");

}


int
do_climb(string str)
{
    if(str == "north")
      {

        if(TP->query_fatigue() < 50)
          {
            write("You are too tired to climb in that direction\n");
            say(QCTNAME(TP) + " tries to climb north, but is too " +
               "tired to do it.\n");
            return 1;
          }

        if(TP->query_stat(1) < random(220))
          {
            say(QCTNAME(TP) + " tries to climb up the extremely steep slope to the " +
             "north, but suddenly slips on the ice! Failing to grab a " +
             "handhold, " + QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
            write("You climb up the extremely steep slope to the north, but suddenly " +
             "slip on the ice! Desperately, you reach out to grab " +
             "a handhold, but fail...\n");
             set_alarm(2.0,0.0,"slide_down4");
            return 1;
          }

        write("Though the cold ice numbs your fingers, you manage to find " +
          "your way up the extremely steep north side of the glacier's finger. The " +
          "climb is badly exhausting!\n");
        say("Though the cold ice must numb " + HIS(TP) + " fingers " + 
          QTNAME(TP) + " finds his way up the extremely steep north side of the glacier's " +
          "finger.\n");
        tell_room(ROOMSK + "glacier4", QCTNAME(TP) + 
          " climbs up from the south slope.\n");
      
        TP->move_living("climbing up the icy slope", ROOMSK + "glacier4",1,0);
        TP->add_fatigue(-50);

        return 1;
      }
      
     if(str == "south")
      {

        if(TP->query_fatigue() < 40)
          {
            write("You are too tired to climb in that direction\n");
            say(QCTNAME(TP) + " tries to climb west, but is too " +
               "tired to do it.\n");
            return 1;
          }

        if(TP->query_stat(1) < random(180))
          {
            say(QCTNAME(TP) + " tries to climb down the slope to the " +
             "south, but suddenly slips on the ice! Failing to grab a " +
             "handhold, " + QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
            write("You climb down the slope to the south, but suddenly " +
             "slip on the ice! Desperately, you reach out to grab " +
             "a handhold, but fail...\n");
             set_alarm(2.0,0.0,"slide_down3");
           return 1;
          }

        write("Though the cold ice numbs your fingers, you manage to find " +
          "your way down south.\n");
        say("Though the cold ice must numb " + HIS(TP) + " fingers " + 
          QTNAME(TP) + " finds his way down south.\n");
        tell_room(ROOMSK + "glacier2", QCTNAME(TP) + 
          " climbs down the ice from the north.\n");
      
        TP->move_living("climbing down the slope", ROOMSK + "glacier2",1,0);
        TP->add_fatigue(-40);

        return 1;
      }

    notify_fail("Climb which way?\n");
    return 0;
}

int
slide_down4()
{
   write("And slide down the ice! Your ride takes you south at first, " +
    "but then a change in slope drops you sharply to the west! " +
    "Traveling with a sick speed, you " +
    "hammers into the dark stone of the battlement, adding a " +
    "bloody bruise to your adventurous collection.\n");
   say("Slides down the ice, going south, before a change in slope " +
    "drops him to the west! Travelling with a sick speed, " + 
    QTNAME(TP) + " hammers into dark stone of the battlement!\n");
   TP->heal_hp(-800);
   TP->move_living("sliding down", ROOMSK + "slope_bottom",1,0);
   tell_room(ROOMSK + "slope_bottom", QCTNAME(TP) + " slides down " +
    "from the slope and hammers into the dark stone of the " +
    "battlement!\n" +
    QCTNAME(TP) + " appears badly hurt from the impact.\n",TP);


   return 1;
}

int
slide_down3()
{
   write("And slide down the ice! Your ride takes you south at first, " +
    "but then a change in slope drops you sharply to the west! " +
    "Traveling with a great speed, you " +
    "smash into the dark stone of the battlement, adding a " +
    "huge bruise to your adventurous collection.\n");
   say("Slides down the ice, going south, before a change in slope " +
    "drops him to the west! Travelling with a great speed, " + 
    QTNAME(TP) + " smashes into the dark stone of the battlement!\n");
   TP->heal_hp(-500);
   TP->move_living("sliding down", ROOMSK + "slope_bottom",1,0);
   tell_room(ROOMSK + "slope_bottom", QCTNAME(TP) + " slides down " +
    "from the slope and smashes into the dark stone of the " +
    "battlement!\n" +
    QCTNAME(TP) + " appears hurt from the impact.\n",TP);

   return 1;
}



void
init()
{
    ::init();

    add_action(do_climb, "climb");
}              
