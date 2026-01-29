 //   watch             (/d/Avenir/common/port/uw_watch.c)
 // creator(s):       Glinda june -95
 // last update:
 // purpose:          A watch that can be repaired.
 //                   Originially meant as noise but turned into a
 //                   small quest.
 //                  -Now made into a prototype for an interdomain
 //                   watch that can be used to check the time
 // note:
 // bug(s):
 // to-do:void

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

#define ME       "/d/Gondor/elessar/lib/clock"->query_24_hour()
#define KALAD    "/d/Kalad/clock"->query_time()
#define KRYNN    "/d/Krynn/common/clock/clock"->query_hour()

// Not in place yet:
// #define AVENIR   "/d/Avenir/lib/clock"->query_hour()

#define TP this_player()

string time();
int check_time(object who);

create_object()
{
   set_short("thin brass disk");
   set_pshort("thin brass disks");
   set_name("disk");
   set_pname("disks");
   add_adj(({"thin","brass"}));

   set_long("It is a thin disk, its burnished brass surface smooth "
           +"and shiny. Around the edges of the disk are twelve "
           +"tiny symbold etched lightly into the metal. @@time@@");

   add_item(({"symbols","symbol"}), "There are twelve symbols, delicatley "
           +"etched into the brass and evenly "
           +"spaced along the edge of the disk, making it look almost "
           +"like the face of a tiny clock.\n");

   add_item("first symbol", "It is a red hand within a tiny octagon.\n");
   add_item("second symbol", "It is a rat within a circle.\n");
   add_item("third symbol", "It is a skull inside a goblet.\n");
   add_item("fourth symbol", "It is the outline of an eye.\n");
   add_item("fifth symbol", "It is a stylus within a square within a circle.\n");
   add_item("sixth symbol", "It is a trident within a circle.\n");
   add_item("seventh symbol", "It is a knife within a crescent.\n");
   add_item("eighth symbol", "It is a pentagram within a circle.\n");
   add_item("ninth symbol", "It is two crossed rods.\n");
   add_item("tenth symbol", "It is two wavy lines on either side of a "
                           +"triangle.\n");
   add_item("eleventh symbol", "It is a teardrop and a serpent.\n");
   add_item("twelfth symbol", "It is two opposing triangles.\n");

   add_prop( OBJ_I_VOLUME, 97);
   add_prop( OBJ_I_WEIGHT, 80);
   add_prop( OBJ_I_VALUE, 853);
}

string time()
{
   int time, twelve_time;
   string color;
   string *number = (({"twelfth", "first", "second", "third",
                       "fourth", "fifth", "sixth",
                       "seventh", "eighth", "ninth",
                       "tenth", "eleventh", "twelfth"}));
   object who = TP;

   time = check_time(who);

   if(time<0 || time>24) time = -1;

   if(time > 12) 
     twelve_time = time - 12;
   else
     twelve_time = time;

   if(time == 0) time = 24;

   say(QCTNAME(who) + " looks closely at a " + short() + ".\n");

   switch(time)
     {
       case -1:
         return "The face of the disk is pale and lightless.\n";
         break;
       case 0:
         color = "a blue-black";
         break;
       case 1 .. 3:
         color = "a dark blue";
         break;
       case 4 .. 6:
         color = "a pale blue";
         break;
       case 7 .. 11:
         color = "a soft white";
         break;
       case 12:
         color = "a bright white";
         break;
       case 13 .. 17:
         color = "a pale white";
         break;
       case 18 .. 20:
         color = "a dim white";
         break;
       case 21 .. 23:
         color = "a dark blue";
         break;
       case 24:
         color = "a blue-black";
         break;
      }

   return "The "+number[twelve_time]+
          " symbol is aglow with "+color+" light.\n";
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

      case "avenir":
        // Let's cheat for now...
        return random(24);
        break;

      default:
        return -1;
        break;
     }
   return -1;
}

query_autoload() { return MASTER; }