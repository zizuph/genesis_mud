#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;


void
create_icewall_room()
{
    set_short("On the ice, above the battlement");
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
  "You stand upon an ice flow, extending from the glacier-covered " +
  "mountain to the north all the way to the castle. Closely to the " +
  "south, the ice already flows over the battlement, and to " +
  "the west a lower part of the glacier reaches under an archer's " +
  "slit.\n");

}


int
do_climb(string str)
{
    if(str == "north")
      {

        if(TP->query_fatigue() < 30)
          {
            write("You are too tired to climb in that direction\n");
            say(QCTNAME(TP) + " tries to climb north, but is too " +
               "tired to do it.\n");
            return 1;
          }

        if(TP->query_stat(1) < random(136))
          {
            say(QCTNAME(TP) + " tries to climb up the slope to the " +
             "north, but suddenly slips on the ice! Failing to grab a " +
             "handhold, " + QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
            write("You climb up the slope to the north, but suddenly " +
             "slip on the ice! Desperately, you reach out to grab " +
             "a handhold, but fail...\n");
             set_alarm(2.0,0.0,"slide_down2");
            return 1;
          }

        write("Though the cold ice numbs your fingers, you manage to find " +
          "your way up the north side of the glacier's finger. The " +
          "way gets harder, though!\n");
        say("Though the cold ice must numb " + HIS(TP) + " fingers " + 
          QTNAME(TP) + " finds his way up the north side of the glacier's " +
          "finger.\n");
        tell_room(ROOMSK + "glacier2", QCTNAME(TP) + 
          " climbs up from the southern slope.\n");
      
        TP->move_living("climbing up the icy slope", ROOMSK + "glacier2",1,0);
        TP->add_fatigue(-30);

        return 1;
      }
      
     if(str == "west")
      {
        if(TP->query_fatigue() < 20)
          {
            write("You are too tired to climb in that direction\n");
            say(QCTNAME(TP) + " tries to climb west, but is too " +
               "tired to do it.\n");
            return 1;
          }

        if(TP->query_stat(1) < random(136))
          {
            say(QCTNAME(TP) + " tries to climb down the slope to the " +
             "west, but suddenly slips on the ice! Failing to grab a " +
             "handhold, " + QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
            write("You climb down the slope to the west, but suddenly " +
             "slip on the ice! Desperately, you reach out to grab " +
             "a handhold, but fail...\n");
             set_alarm(2.0,0.0,"slide_down1");
           return 1;
          }

        write("Though the cold ice numbs your fingers, you manage to find " +
          "your way down the west side of the glacier's finger.\n");
        say("Though the cold ice must numb " + HIS(TP) + " fingers " + 
          QTNAME(TP) + " finds his way down the west side of the glacier's " +
          "finger.\n");
        tell_room(ROOMSK + "slope_bottom", QCTNAME(TP) + 
          " climbs down the ice on the eastern slope.\n");
      
        TP->move_living("climbing down the slope", ROOMSK + "slope_bottom",1,0);
        TP->add_fatigue(-20);

        return 1;
      }

     if(str == "south")
      {
        write("You think the slope is too smooth that way. You " +
         "could slip and slide all the way over the roof of the " +
         "battlement to your death on the Castle's courtyard.\n");
        say(QCTNAME(TP) + " looks briefly south, but abandons the " +
         "idea.\n");
        return 1;
      }
    notify_fail("Climb which way?\n");
    return 0;
}

int
slide_down1()
{
   write("But slide down the ice! Before you manage to gain much speed, " +
    "you collide with the dark stone of the battlement, adding a " +
    "small bruise to your adventurous collection.\n");
   say("Slides down the ice! Before " + HE(TP) + " manages to gain " +
    "much speed though, " + QTNAME(TP) + " barrels into the dark stone " +
    "of the battlement!\n");
   TP->heal_hp(-100);
   TP->move_living("sliding down", ROOMSK + "slope_bottom",1,0);
   tell_room(ROOMSK + "slope_bottom", QCTNAME(TP) + " slides down " +
    "from the slope and barrels into the dark stone of the " +
    "battlement!\n" +
    QCTNAME(TP) + " appears relatively unharmed.\n",TP);

   return 1;
}

int
slide_down2()
{
   write("And slide down the ice! Your ride takes you south at first, " +
    "but then a change in slope drops you sharply to the west! " +
    "Traveling with a solid speed, you " +
    "collide with the dark stone of the battlement, adding a " +
    "large bruise to your adventurous collection.\n");
   say("Slides down the ice, going south, before a change in slope " +
    "drops him to the west! Travelling with a solid speed, " + 
    QTNAME(TP) + " collides with the dark stone of the battlement!\n");
   TP->heal_hp(-300);
   TP->move_living("sliding down", ROOMSK + "slope_bottom",1,0);
   tell_room(ROOMSK + "slope_bottom", QCTNAME(TP) + " slides down " +
    "from the slope and collides with the dark stone of the " +
    "battlement!\n" +
    QCTNAME(TP) + " appears bruised from the impact.\n",TP);

   return 1;
}



void
init()
{
    ::init();

    add_action(do_climb, "climb");
}              
