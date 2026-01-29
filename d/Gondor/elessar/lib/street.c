/*
 *	Please use /d/Gondor/minas/lib/street.c,
 *	_NOT_ this file!
 */
inherit "/d/Gondor/common/room";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string areaname,streettype,streetname,long_descf,circle,extraline;
int streetlight;                       /* 0 = none, 1 = not lit, 2 = lit */
int activity;                          /* 0 = low,  1 = normal,  2 = high */ 
int wealth;                            /* 0 = poor, 1 = average, 2 = rich */
int war;                               /* 0 = peace 1 = alert    2 = war  */

make_the_room()
{
  object clock;

  log_file("street", MASTER + " inherits /d/Gondor/elessar/lib/street.c.\n", -1);
  clock = find_object(CLOCK);
  war = clock->query_war();
    set_short(CAP(LANG_ADDART(streettype)) + " in Minas Tirith");
  if (extraline) extraline = extraline+"\n";
    set_long("@@describe");
    add_item(streettype,"The " + streettype + " is made of square stones.\n");
    if (wealth == 0) add_item(({"house","houses"}),
        "The houses on this " + streettype + " are in a poor condition.\n" +
        "Obviously the people in this part of the city aren't the most\n" +
        "wealthy.\n");
    else if (wealth == 1) add_item(({"house","houses"}),
        "The houses on this " + streettype + " are in good condition.\n" +
        "They are not fancy, but suitable for common housing.\n");
    else add_item(({"house","houses"}),
        "The houses on this " + streettype + " are big and expensive\n" +
        "looking.\n");
    if(streetlight > 0) add_item("street light",
        "The street lights are oil lamps hanging from the houses.\n");
}

describe(str) {
  string time;
  object clock;
  int coloum,i;
  if(str) return;
  clock = find_object(CLOCK);
  time = clock->query_time_of_day();
  long_descf = 
    streetname + " in the " + areaname +
      " parts of the "+
	circle + " circle of Minas Tirith. ";
  if (time=="night"||time=="evening"||time=="early morning")
    {
      /* Calc light at night*/
      long_descf = long_descf + "The " + streettype; 
      if(streetlight == 2) long_descf = long_descf +
	" is lit by a warm light from the lit street lights. ";
      else if(clock->query_moon()=="dark") {
	long_descf = long_descf + " lies in darkness, ";
	if(streetlight == 0) long_descf = long_descf +
	  "as there are no street lights in this part of city. ";
	else long_descf = long_descf +
	  "as the street lights haven't been lit yet. ";
      }
      else long_descf = long_descf +
	" looks gloomy in the silvery light from the "+clock->query_moon()+" moon. ";
    }
  /* Calc activity : Early morning, daytime, evening, night */
  if(time == "early morning")
    if(activity == 0) long_descf = long_descf +
      "There are nobody in the " + streettype + " but from the houses " +
	"you hear the sounds of rattling pans and people shouting. All " +
	  "unmistakable signs that the city is awakening to a new day. ";
    else if(activity == 1) long_descf = long_descf +
      "There are a few people in the " + streettype + ". They look a " +
	"little sleepy as they stumble from their homes in different " +
	  "directions. From the houses you hear the sound of people wakening " +
	    "to a new day. ";
    else long_descf = long_descf +
      "There are already quite a few people in the " + streettype + ". " +
	"Shopkeepers are getting ready to open their businesses, the " +
	  "bars and pubs are closing, throwing out the last drunks. The " +
	    "city is awakening to a new day. ";
  else if(time == "morning" || time == "noon" || time == "afternoon")
    if(activity == 0) long_descf = long_descf +
      "There are a few people in the " + streettype + ". There is not " +
	"much activity here. Just a few playing children and women " +
	  "going about their daily doings. ";
    else if(activity == 1) long_descf = long_descf +
      "There are some people in the " + streettype + ". People come and " +
	"go on their way to other parts of the city, or to visit the few " +
	  "shops here. Occasionally a horse carriage scrambles down the " +
	    streettype + " or a constable walks by. ";
    else long_descf = long_descf +
      "The " + streettype + " is full of people. Shops, inns and other " +
	"businesses are open, and everybody is busy with their own doings. "+
	  "Horse carriages and wagons pulled by oxen rumble through the center " +
	    "of the " + streettype + ", and city guards are busy watching out " +
	      "for pickpockets and the likes. ";
  else if(time == "evening")
    if(activity == 0) long_descf = long_descf +
      "People are returning to their homes, mothers are calling their " +
	"children in to dinner, so the " + streettype + " is slowly " +
	  "emptying. "; 
    else if(activity == 1) long_descf = long_descf +
      "There are a few people in the " + streettype + ". Most of them " +
	"are on their way home, while the few shops are closing up for " +
	  "the night. ";
    else long_descf = long_descf +
      "There are still many people in the " + streettype + ". Some " +
	"are finishing their shopping, but most of the shopkeepers are " +
	  "closing up for the night. The inns and pubs are still open, and you " +
	    "hear the sound of laughter and music echoing down the " +
	      streettype + ". ";
  else
    if(activity == 0) long_descf = long_descf +
      "The " + streettype + " lies empty. The houses are dark and " +
        "empty with no signs of life. ";
    else if(activity == 1) long_descf = long_descf +
      "The " + streettype + " is quiet with a few people coming and " +
        "going. The few shops are closed, and the houses are dark and " +
	  "quiet. ";
    else long_descf = long_descf +
      "There are still some people in the " + streettype + ". The " +
        "light shines from bars and taverns, and you hear laughter " +
	  "and song. Now and then a city guard walks by on his round. ";
  if (extraline) long_descf = long_descf+extraline;
  else long_descf = long_descf + "\n";
  return (break_string(long_descf, 75)); 
}

string
query_circle()
{
    return circle;
}
