 //   watch             (/d/Avenir/common/port/uw_watch.c)
 // creator(s):       Glinda june -95
 // last update:
 // purpose:          A watch that can be repaired.
 //                   Originially meant as noise but turned into a
 //                   small quest.
 // note:
 // bug(s):
 // to-do:void

inherit "/std/object";
inherit "/d/Avenir/inherit/quest";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define QLOG "/d/Avenir/log/quest/fix_watch"

// #define ME       "/d/Gondor/common/lib/time"->qstime()

#define ME       "/d/Gondor/elessar/lib/clock"->query_24_hour()
#define KALAD    "/d/Kalad/clock"->query_time()
#define KRYNN    "/d/Krynn/common/clock/clock"->query_hour()

#define TP this_player()

int i = 5;
int open = 0;
int source = 0;
int fixed = 0;
int alarm_id;

create_object()
{
   set_short("golden watch");
   set_pshort("golden watches");
   set_name("watch");
   set_pname("watches");
   add_adj(({"gold","golden"}));
   set_long("A golden watch, meant to keep in your pocket. Attached to " +
      "it is a golden chain. It seems to have some kind of odd scale, " +
      "not like any other watch you have seen. Instead of numbers are " +
      "small symbols. @@watch_long@@\n");
   add_item(({"symbols","scale"}), "The symbols that make out the hours " +
      "look like nothing you have seen before.\n");
   add_item(({"chain"}), "A gold chain is attached to the watch.\n");

   add_prop( OBJ_I_VOLUME, 97);
   add_prop( OBJ_I_WEIGHT, 240);
   add_prop( OBJ_I_VALUE, "@@value");
   add_prop( OBJ_S_SEARCH_FUN, "do_search");
   add_prop( OBJ_I_SEARCH_TIME, 20 );

   seteuid(getuid());
}

int check_time(object who)
{
   string place;

   place = lower_case(environment(who)->query_domain());

   switch(place)
    {
      case "krynn":
      case "ansalon":
        return KRYNN;
        break;

      case "gondor":
      case "mordor":
      case "shire":
      case "rhovanion":
        return ME;
        break;

      case "kalad":
        return KALAD;
        break;

      default:
        return -1;
        break;
     }
}

void
init()
{
    add_action("do_listen","listen");
    add_action("do_insert","put");
    add_action("do_insert","insert");
    add_action("do_insert","place");
    add_action("do_wind","wind");
    add_action("do_open","open");
    add_action("do_close","close");
    ::init();
}

my_id(object ob)
{
   if( ob->id("source"))
      return 1;
   return 0;
}

do_close(string str)
{
   if(str != "hatch")
      return 0;
   if(!open)
   {
      notify_fail("The hatch is closed already.\n");
      return 0;
   }
   open = 0;
   if(fixed || !source)
   {
      write("You close the hatch again.\n");
      return 1;
   }
   fixed = 1;
   if(TP->test_bit("Avenir", 0, 16)) 
   {
      write("The watch starts ticking slowly.\n");
      return 1;
   }
   write_file(QLOG, TP->query_name() + " fixed the watch and got 2000 xp "
              + ctime(time()) + "\n");
   write("Congratulations! You fixed the watch!\n");
   reward_quest("Fix Watch", TP, 0, 16, 2000);
   write("The watch starts ticking slowly.\n");
   return 1;
}

do_insert(string str)
{
   object ob, *obs;

   if(str != "source in hatch" && str != "crystal in hatch" &&
      str != "source into hatch" && str != "crystal into hatch" )
      return 0;
   if(fixed)
   {
      notify_fail("The watch has been repaired already.\n");
      return 0;
   }
   if(source)
   {
      notify_fail("There is already some source in the hatch.\n");
      return 0;
   }
   if(!open)
   {
      notify_fail("But the hatch is closed.\n");
      return 0;
   }

   if( present("source",TP) )
   {
      obs=filter(all_inventory(TP), my_id);
      ob=obs[0];
      ob->remove_object();
      write("You place the piece of source into the hatch. It melts stuck.\n");
      source = 1;
      return 1;
   }
   return 0;
}

do_listen(string str)
{
   notify_fail("Listen to what?\n");
   if(str != "to watch" && str != "watch")
      return 0;
   if(fixed)
      alarm_id = set_alarm(0.5, 1.5, "do_tick", TP );
   else
      write("You hear nothing.\n");
   say(QCTNAME(TP) + " holds a golden watch to " + TP->query_possessive()
          + " ear.\n");
   return 1;
}

do_tick(object who)
{
   if(i)
      who->catch_msg("TICK\n");
   else
   {
      remove_alarm(alarm_id);
      i=6;
      who->catch_msg("You stop listening to the watch.\n");
   }
   i--;
}

do_wind(string str)
{
   if(str != "watch")
      notify_fail("Wind what?\n");
   if(str == "watch")
      notify_fail("You cant find any knob to wind the watch with.\n");
   return 0;
}


do_open(string str)
{
   if( str != "hatch")
      return 0;
   write("You open the small hatch on the back of the watch.\n");
   open = 1;
   return 1;
}

do_search(object searcher, string str)
{
   if(TP->query_skill(SS_AWARENESS) < 37)
      return 0;
   if(str != "watch" )
      return 0;
   add_item(({"hatch","hollow"}), "A small hollow in the back of the " +
      "watch. @@hatch_state@@\n");
   return "There is a small hatch on the back side of the watch.\n";
}

string
watch_long()
{
   if(fixed)
      return "The arms are moving slowly around the scale.";
   else
      return "The arms are fixed motionless in a sharp angle.";
}

string
hatch_state()
{
   if(!open)
      return "The hatch is closed.";
   if(source)
      return "A piece of glowing material has been inserted into the " +
             "hatch, and has melted stuck.";
   else
      return "The hatch has been opened. It is empty.";
}

int
value()
{
   if(fixed)
      return 3500;
   else
      return 350;
}

