#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>
inherit ICEINROOM;

object wroc;

int    frozen_hand_found = 0; /* 0 : frozen_hand NOT found */
object frozen_hand;

public void
reset_icewall_room()
{
    set_searched(random(2));
    {
        object *inv, *live;

        inv = ({});
        inv = all_inventory(TO);
        live = FILTER_LIVE(inv);

        if(sizeof(live))
            return;

       frozen_hand_found = 0;
       frozen_hand->remove_object();
    }

    if (!wroc)
    {
	wroc = clone_object(NPCK + "young_roc.c");
	wroc->move_living("xx", TO);
    }

}

void
create_icewall_room()
{
    set_short("On the ice, very high above the battlement");
    set_long("@@long_descr");

    add_item(({"slope","icy slope"}),"Aye, its a slope, and its " +
     "made out of ice! Who knows where it leads...\n");
    add_item("plateau","@@plateau_desc");

    set_tell_time(800);

    add_tell("It is snowing hard... And white flakes begin " +
     "cover you from head to toe.\n");
    add_tell("Wind picks up quite suddenly, scattering " +
     "snow and chilling you to the bone.\n");
    add_tell("You think you have just heard a strange shriek " +
     "carried here by the everpresent freezing wind.\n");
    add_tell("Your hands feel numb. You " +
     "feel you shouldn't stay up here for too long, or you " +
     "might not be able to climb down again.\n");

    seteuid(getuid(TO));

    remove_prop(ROOM_I_INSIDE);

    enable_reset(200);
    reset_icewall_room();
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
  "You have climbed onto a small, flat plateau high above Icewall " +
  "Castle. The wind howls here, but the view is quite nice. " +
  "Looking down, you feel the glacier's power as it flows against " +
  "the battlements, spelling their destruction. " +
  "Far down, and slightly to the west a lower part of the glacier's " +
  "finger reaches under an archer's " +
  "slit. North, the glacier becomes too steep to climb.\n");

}

string
plateau_desc()
{
    if(frozen_hand_found)
       {
       tell_room(TO, QCTNAME(TP) + " glances around the small plateau, " +
         "but finds nothing particularly interesting.\n", TP);
       return "This is simply a small ledge on the flowing slope. " +
         "A big chunk of ice must have broken out and left this space " +
         "behind it. You glance around the icy place, but find nothing " +
         "particularly interesting.\n";
       }

    frozen_hand_found = 1;
       tell_room(TO, QCTNAME(TP) + " glances around the small plateau, " +
         "and finds a black frozen arm sticking out of the ice!\n", TP);
       frozen_hand = clone_object(OBJK + "frozen_hand.c");
       frozen_hand->move(TO);
       return "This is simply a small ledge on the flowing slope. " +
     "A big chunk of ice must have broken out and left this space " +
     "behind it. You glance around the icy place, and much to your " +
     "suprise find a black frozen arm sticking out of the ice!\n";
}

int
do_climb(string str)
{
    if(str == "north")
      {
            say(QCTNAME(TP) + " tries to climb up the vertical slope to the " +
             "north, but fails and gives up.\n");
            write("You try to climb up the vertical slope to the north, but " +
             "fail and decide to give up.\n");
            return 1;
      }

    if(str == "south")
      {

        if(TP->query_fatigue() < 50)
          {
            write("You are too tired to climb in that direction\n");
            say(QCTNAME(TP) + " tries to climb south, but is too " +
               "tired to do it.\n");
            return 1;
          }

        if(TP->query_stat(1) < random(200))
          {
            say(QCTNAME(TP) + " tries to climb down the slope to the " +
             "south, but suddenly slips on the ice! Failing to grab a " +
             "handhold, " + QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
            write("You climb down the slope to the south, but suddenly " +
             "slip on the ice! Desperately, you reach out to grab " +
             "a handhold, but fail...\n");
             set_alarm(2.0,0.0,"slide_down4");
           return 1;
          }

        write("Though the cold ice numbs your fingers, you manage to find " +
          "your way down south.\n");
        say("Though the cold ice must numb " + HIS(TP) + " fingers " + 
          QTNAME(TP) + " finds his way down south.\n");
        tell_room(ROOMSK + "glacier3", QCTNAME(TP) + 
          " climbs down the ice from the north.\n");
      
        TP->move_living("climbing down the slope", ROOMSK + "glacier3",1,0);
        TP->add_fatigue(-50);

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


void
init()
{
    ::init();

    add_action(do_climb, "climb");
}              
