/*
* This is the standard room inherited by all outside rooms in
* Kendermore.
*
* Created on Dec 11/95 by Erine.
* seasonal_tod_mess()
*
* some short desc added by Kishpa and few changes in seasonal mess 15/05/96
*
* tod_short_desc()
* tod_street_desc()
*
* - functions for adding and removing houses
*
* add_left_house()
* add_right_house()
* query_left_house()
* query_right_house()
* remove_left_house()
* remove_right_house()
*/

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/kendermore/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

inherit AOR_FILE


#define OBJ_S_HOUSE_LEFT         "_obj_s_house_left"
#define OBJ_S_HOUSE_RIGHT        "_obj_s_house_right"
#define OBJ_I_NO_RIGHT_HOUSE     "_obj_i_no_right_house"
#define OBJ_I_NO_LEFT_HOUSE      "_obj_i_no_left_house"

/* PROTOTYPES */
varargs void add_left_house(string path = AVOID);
varargs void add_right_house(string path = AVOID);


public void
create_kendermore_room()
{
}

public void
reset_kendermore_room()
{
   enable_reset(0);
}

nomask public void
create_krynn_room()
{
    ::create_krynn_room();

 /* 4 adds to avoid some errors in adding houses- path is leading to void
  */
   add_left_house();
   add_right_house();

   add_prop(OBJ_I_NO_LEFT_HOUSE, 0);
   add_prop(OBJ_I_NO_RIGHT_HOUSE, 0);

   create_kendermore_room();
}

nomask public void
reset_krynn_room()
{
   reset_kendermore_room();
}


string
season_name()
{
   string name_of_season;

   switch(GET_SEASON)
   {
    case SPRING :
                  name_of_season = "spring ";
    break;
    case SUMMER :
                  name_of_season = "summer ";
    break;
    case AUTUMN :
                  name_of_season = "autumn ";
    break;
    case WINTER :
                  name_of_season = "winter ";
    break;
   }

   return (name_of_season);
}


public string
tod_street_desc()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "Now the street is occupied only by rats and shadows. ";
        break;
        case TOD_DAWN:
            str = "You can see a few sleepy citizens walking along "+
                  "the street. ";
        break;
        case TOD_DAY:
            str = "You almost can drown in this sea of little fellows that "+
                  "crowd the street looking for new excitements. ";
        break;
        case TOD_TWILIGHT:
            str = "Just when first shadows starts to crawl from under the "+
                  "stones, happy and thirsty explorers burst out from "+
                  "their homes and start a desperate search for a mug of "+
                  "ale in any nice Inn nearby. ";
        break;
    }

    return str;
}
public string
tod_short_desc()
{
    string str, season;


    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "It is a peaceful "+ season_name() + "night in the "+
                  "city of Kendermore. ";
        break;
        case TOD_DAWN:
            str = "It is "+ season_name() +"morning in the city "+
                  "of Kendermore.";
        break;
        case TOD_DAY:
            str = "It is "+ season_name() +"day in the city "+
                  "of Kendermore.";
        break;
        case TOD_TWILIGHT:
            str = "It is "+ season_name() +"evening in the city "+
                  "of Kendermore.";
        break;
    }

    return str;
}

public string
seasonal_tod_mess()
{

   string str;


      switch(GET_TIME_STRING)
      {
         case MIDNIGHT:
         switch(GET_SEASON)
         {
            case SPRING:
            str = "The clean crisp midnight air brings "
            + "your soul alive with beautiful visions "
            + "of what the comming summer will produce. ";
            break;
            case SUMMER:
            str = "Kendermore seems peacefull on this calm "
            + "summer night. All seems calm in the mid of night. ";
            break;
            case AUTUMN:
            str = "At this time of night you can hear very "
            + "little, except for the sounds of summer leaving. ";
            break;
            case WINTER:
            str = "Even in the dead on night on this cold "
            + "winter day, the warm cheery spirit of "
            + "Kendermore warms your soul. ";
            break;
            }
         break;
      case NIGHT:
      switch (GET_SEASON)
      {
         case SPRING:
         str = "It is unusually silent for a calm Spring night "+
               "in Kendermore. ";
         break;
         case SUMMER:
         str = "It is a peaceful and warm night. After a hot day "+
               "the cool air is like a belssing. ";
         break;
         case AUTUMN:
         str = "It is a cool autumn night and you can feel winter coming. ";
         break;
         case WINTER:
         str = "Even on this cold winter night, the "
         + "happy welcoming spirit of Kendermore warms "
         + "your soul. ";
         break;
          }
      break;
      case EARLY_MORNING:
      switch (GET_SEASON)
      {
         case SPRING:
         str = "The smells of hearths burning, and food "
         + "cooking fill the early spring morning. ";
         break;
         case SUMMER:
         str = "You hear the sounds of kender waking and getting "
         + "ready to greet this fine summer morning. ";
         break;
         case AUTUMN:
         str = "As the sun slowly spreads its autumn light "
         + "accross the lands, Kendermore is getting ready "
         + "to take on another day. ";
         break;
         case WINTER:
         str = "The sun dawns on the land bringing light "
         + "to this cool wintery day. ";
         break;
         }
      break;
      case MORNING:
      switch(GET_SEASON)
      {
         case SPRING:
        str = "On this spring day just as anyother spring day. "
         + "citizens of Kendermore are in a frenzy attempting "
         + "get a productive day moving. ";
         break;
         case SUMMER:
         str = "Between it being summer and a glorious "
         + "morning here in Kendermore. The citizens of "
         + "Kendermore cheerfully leave thier homes to have "
         + "fun and most likely interesting day. ";
         break;
         case AUTUMN:
         str = "The morning autumn light shines brightly "
         + "accross a allready bustling Kendermore. ";
         break;
         case WINTER:
         str = "The warming sunlight of winter shines on "
         + " the happy citizens of Kendermore. ";
         break;
         }
         break;
      case NOON:
      switch (GET_SEASON)
      {
         case SPRING:
         str = "It is mid-day in Kendermore. Citizens are busy "
         + "scouring the city of interesting things that the "
         + "winter left behind. ";
         break;
         case SUMMER:
         str = "It is only mid-day and you see many citizens "
         + "wandering aimlessly through the streets of Kendermore. "
         + "Summer must bring out the wanderlust in kender you "
         + "think to yourself. ";
         break;
         case AUTUMN:
         str = "Autumn leaves blow through the busy streets of "
         + "Kendermore as it happy citizens check out the mid-day "
         + "specials in the local shops. ";
         break;
         case WINTER:
         str = "Even in this cold brisk winter day. The citizens "
         + "of Kendermore are out wandering aimlessly. ";
         break;
         }
         break;
      case AFTERNOON:
      switch (GET_SEASON)
      {
         case SPRING:
         str = "As the sun starts to set on the spring sky, "
         + "the citizens of Kendermore wander aimlessly about "
         + "the streets of thier fine city. ";
         break;
         case SUMMER:
         str = "As the sun starts to set accross the hills "
         + "srounding Kendermore. Kenderfolk display found "
         + "treasures to each other, some claiming these "
         + "treasures to be thiers before they lost them. ";
         break;
         case AUTUMN:
         str = "As the sun sets the day gets cooler giving "
         + "those tell-tail signs that winter is surely on its "
         + "way. Kender display treasures to each other, "
         + "where these treasures actually came from you can "
         + "only guess that it was someone elses pouches. ";
         break;
         case WINTER:
         str = "As the sun makes its decent accross the sky, "
         + "kender swap stories of adventure that this wintery "
         + "day has blessed them with. ";
         break;
         }
         break;
      case EVENING:
      switch (GET_SEASON)
      {
         case SPRING:
         str = "A warm glow shines accross the horizion from "
         + "the setting sun. Kenderfolk make thier way home, "
         + "to rest up for another spring day that will surely "
         + "bring many stories and treasures to thier lives. ";
         break;
         case SUMMER:
         str = "A red glow shines brilliantly from the setting "
         + "sun as it vanishes in the horizion. Kenderfolk "
         + "make thier way home holding their treasures and "
         + "adventures that the summer day has produced close "
         + "to thier hearts. ";
         break;
         case AUTUMN:
         str = "The sun has set accross the horizion cooling "
         + "the autumn air. Kenderfolk make thier way home "
         +"dreaming of what tommorow shall bring. ";
         break;
         case WINTER:
         str = "The light of the warming sun no-longer "
         + "shines apoun Kendermore. Kenderfolk make thier "
         + "way though the winter streets to find thier homes "
         + "and a nice warm bed to dream thier most impossible "
         + "dreams. ";
         break;
         }
         break;
   }
   return str;
}

void
init()
{
    ::init();

    add_action("enter_house", "enter");

}

int
enter_house(string full_command)
{
    string side;

    NF("Enter what?\n");
    if (!full_command)
     return 0;

 /*  we didn't want the house to be there so we cannot enter it */
    if (TO->query_prop(OBJ_I_NO_RIGHT_HOUSE) > 0) return 0;
    if(TO->query_prop(OBJ_I_NO_LEFT_HOUSE) > 0) return 0;
dump_array(parse_command(full_command, ({}), "[a] / [the] 'house' 'on' [a] / [the] %w [side]", side));

    if(parse_command(full_command, ({TP}), "[a] / [the] 'house' 'on' [a] / [the] %s [side]", side))
    {

        if (side == "left")
        {
            TP->move_living("into the house on the left.\n",
                TO->query_left_house());
            return 1;                          /* right command */
        }
        else if (side == "right")
        {
            TP->move_living("into the house on the right.\n",
                TO->query_right_house());
            return 1;                          /* right command */
        }
        NF("Enter house on the left or the right side?\n");
         return 0;                             /* not a right command */


    }

    NF("last RETURN.\n");
    return 0;   /* he didn't mean to enter house at all */

}

string
query_left_house()
{
   return TO->query_prop(OBJ_S_HOUSE_LEFT);
}

string
query_right_house()
{

   return TO->query_prop(OBJ_S_HOUSE_RIGHT);
}

varargs void
add_left_house(string path= AVOID)
{
    /* check if we really want the house here, return if if we don't */

    if (TO->query_prop(OBJ_I_NO_RIGHT_HOUSE))
     return;

    if(!TO->query_prop(OBJ_S_HOUSE_LEFT))
     TO->add_prop(OBJ_S_HOUSE_LEFT, path);

    TO->change_prop(OBJ_S_HOUSE_LEFT, path);
}

varargs void
add_right_house(string path = AVOID)
{
    /* check if we really want the house here return if we don't */

    if (TO->query_prop(OBJ_I_NO_RIGHT_HOUSE))
     return;

    if(!TO->query_prop(OBJ_S_HOUSE_RIGHT))
     TO->add_prop(OBJ_S_HOUSE_RIGHT, path);

    TO->change_prop(OBJ_S_HOUSE_RIGHT, path);
}

void
remove_left_house(int num)
{
    if (!num)
     return;

    TO->change_prop(OBJ_I_NO_LEFT_HOUSE, num);
}
void
remove_right_house(int num)
{
    if (!num)
     return;

    TO->change_prop(OBJ_I_NO_RIGHT_HOUSE, num);
}

