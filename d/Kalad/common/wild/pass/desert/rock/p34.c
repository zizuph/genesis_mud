/* by Antharanos */
#include "/d/Kalad/defs.h"

#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define KALAD_FOUND_ROCK_EXIT "_kalad_found_rock_exit"

inherit "/d/Kalad/std/room";

object ob1;

public void
create_kalad_room()
{
   add_prop(ROOM_NO_TIME_DESC,1);
   add_prop(OBJ_S_SEARCH_FUN,"search_ground");
   set_short("A spring within the rock plains");
   set_long("You are within a field covered with innumerable rocks, "+
      "a fair number of which are the size of boulders and some as "+
      "massive as a small cottage. "+
      "An eerie-sounding wind whistles among the rocks, producing a tone "+
      "that grates on one's nerves. "+
      "A bubbling spring of pure water is here, turning the normally "+
      "barren terrain into an area teeming with life, as its water seeps "+
      "into the ground around it. Lush grasses and even a "+
      "few tall palm trees surround the life-giving water.\n");
   add_item(({"field","rugged terrain","terrain"}),
      "A vast expanse of rocks of many shapes and sizes.\n");
   add_item(({"innumerable rocks","rocks","rock","boulders","boulder"}),
      "The many rocks around you appear in nearly every conceivable shape and "+
      "size, created as they were by the combination of heat and wind and "+
      "erosion.\n");
   add_item(({"kaladian sun","sun"}),
      "It hangs in the sky like the bloated carcass of some unfortunate "+
      "animal.\n");
   add_item(({"bubbling spring","spring"}),"A wide, constantly flowing "+
      "fountain of water.\n");
   add_item(({"lush grasses","grasses"}),"Tall, waist-high plants that "+
      "whip back and forth in the wind.\n");
   add_item(({"tall palm trees","tall trees","palm trees","trees","tree"}),
      "Their giant leaves form a canopy over the waters of the spring, "+
      "providing a welcome relief from the heat of the desert.\n");
   add_item(({"water","life-giving water","waters"}),"Crystal clear and "+
      "the source of life here in this harsh clime, its value is beyond "+
      "estimate.\n");
   add_item(({"ground"}),
      "The previously parched and sun-cracked ground around the spring is "+
      "now moist and supports many lush grasses.\n");
   add_exit(CPASS(desert/rock/p28),"west",0,4);
   add_exit(CPASS(desert/rock/p29),"north",0,4);
   add_exit(CPASS(desert/rock/p30),"east",0,4);
   add_exit(CPASS(desert/rock/p31),"southeast",0,4);
   add_exit(CPASS(desert/rock/p33),"south",0,4);
   add_exit(CPASS(desert/rock/p27),"southwest",0,4);
   add_exit(CPASS(desert/rock/l1), "down", "@@exit_down", 1, 1);
   set_alarm(1.0,0.0,"reset_room");
}

reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/d_falcon));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The screech of a desert falcon from above alerts you to its presence.\n");
   }
}

int
exit_down()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_ROCK_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_ROCK_EXIT))
            {
                witness->add_prop(KALAD_FOUND_ROCK_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a passage hidden in the ground!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit down.\n");
    return 1;
}


public string
search_ground(object me, string arg)
{
   if(arg != "ground")
      return "";

   if(TP->query_skill(SS_AWARENESS) < 30)
      return "";
   
   TP->add_prop(KALAD_FOUND_ROCK_EXIT, 1);
   return "You search carefully and discover a way down!\n";
}

void
init()
{
   ::init();
   AA(drink,drink);
}
int
drink(string str)
{
   if(!str || str != "water")
      {
      NF("You can't drink '" + str + "'.\n");
      return 0;
   }
   write("You take a sip of the refreshing water.\n");
   say(QCTNAME(TP) + " takes a sip of the refreshing water.\n");
   return 1;
}
