#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;


void
create_icewall_room()
{
    set_short("At the bottom of the icy slope");
    set_long("@@long_descr");

    add_item(({"slope","icy slope"}),"Aye, its a slope, and its " +
     "made out of ice! Who knows where it leads...\n");
    add_item(({"slit","slits","archers' slits","narrow slits"}), "" +
     "Shaped like horizontal trapezoids with the shorter base " +
     "directed outward, the archers' slits allow " +
     "easy loosening of missiles on targets outside the castle, " +
     "while at the same time present " +
     "a minimal profile for enemy fire. You could squeeze back " +
     "into the castle through it.\n");

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
  "You stand upon an ice flow, extending from the glacier-covered " +
  "mountain to the north all the way to the castle. Closely to the " +
  "south, the ice is pushing against the battlement, and an " +
  "archer's slit opens just a foot over the surface of the ice. " +
  "To the east, the ice is much higher, already flowing over " +
  "the battlement.\n");

}


int
do_climb(string str)
{
    if(str == "north")
      {
        write("You climb the slope to the north, but quickly " +
         "run out of handholds! Clinging desperately to the smooth " +
         "ice, you try to steady yourself...\n");
        say(QCTNAME(TP) + " tries to climb the slope to the " +
         "north, but runs out of handholds! Suddenly slipping, " +
         QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
        set_alarm(2.0,0.0,"slide_down1");
        return 1;
      }

    if(str == "east")
      {

        if(TP->query_fatigue() < 20)
          {
            write("You are too tired to climb in that direction\n");
            say(QCTNAME(TP) + " tries to climb west, but is too " +
               "tired to do it.\n");
            return 1;
          }

        if((TP->query_skill(104)) < 30)
          {
            say(QCTNAME(TP) + " tries to climb the slope to the " +
             "east, but runs out of handholds! Suddenly slipping, " +
             QTNAME(TP) + " loses " + HIS(TP) + " balance and...\n");
            write("You climb the slope to the east, but quickly " +
             "run out of handholds! Clinging desperately to the smooth " +
             "ice, you try to steady yourself...\n");
             set_alarm(2.0,0.0,"slide_down1");
            return 1;
          }

        write("Though the cold ice numbs your fingers, you manage to find " +
          "your way up the east side of the glacier's finger.\n");
        say("Though the cold ice must numb " + HIS(TP) + " fingers " + 
          QTNAME(TP) + " finds his way up the east side of the glacier's " +
          "finger.\n");
        tell_room(ROOMSK + "glacier1", QCTNAME(TP) + 
          " climbs up the ice from down the western slope.\n");
      
        TP->move_living("climbing up the icy slope", ROOMSK + "glacier1",1,0);
        TP->add_fatigue(-20);

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
    "of the battlement!\n" + QCTNAME(TP) + " appears relatively unharmed.\n");
   TP->heal_hp(-100);
   return 1;
}

int
do_squeeze(string str)
{
    if(str == "through slit")
      {

        if (TP->query_race_name() == "kender" || TP->query_race_name() == "hobbit")
          {
            write("Turning sideways, you smartly slip through the " +
              "narrow archers' slit back into the castle.\n");
            say("Turning sideways, " + QTNAME(TP) + " smartly slips " +
              "back into the castle.\n");
            tell_room(ROOMSK + "battlement5", "With the ease of a small folk, " +
              QTNAME(TP) + " slips out from the north archers' slit.\n");
            
            TP->move_living("through the archers' slit", ROOMSK + "battlement5",1,0);
            return 1;
          }

      write("Sucking in your proverbial gut, you twist and push " +
       "and scrape and groan and curse and finally manage to plop " +
       "back into the castle through the archers' slit.\n");
      say("Sucking in his proverbial gut, " + QTNAME(TP) + " twists " +
       "and pushes and scrapes and groans and curses but finally " +
       "manages to plop back into the castle.\n");
     tell_room(ROOMSK + "battlement5", "Twisting, pushing, scraping and " +
      "groaning, " + QTNAME(TP) + " plops out from the north " +
      "archers' slit.\n");
      
     TP->move_living("through the archers' slit", ROOMSK + "battlement5",1,0);
      return 1;
      }

    write("Squeeze through what?\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(do_squeeze, "squeeze");
    add_action(do_climb, "climb");
}              