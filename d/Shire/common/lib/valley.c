#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/common/lib/rom";

static object clock;

create_rom() {
    clock = find_object("/d/Gondor/common/obj/clock");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    ITEM(({"sky","moon","sun","stars","heaven"}),"@@do_sky@@\n");
    this_object()->create_valley();
    my_exit_desc_mode = 1;
}

reset_rom() {
    this_object()->reset_valley();
}

/*
   - early morning - from 04.00 to 08.00
   - morning       - from 08.00 to 11.00
   - noon          - from 11.00 to 14.00
   - afternoon     - from 14.00 to 18.00
   - evening       - from 18.00 to 22.00
   - night         - from 22.00 to 04.00
*/

#define EARLY_NIGHT     22..24
#define LATE_NIGHT      0..3
#define EARLY_MORNING   4..7
#define MORNING         8..10
#define NOON            11..13
#define AFTERNOON       14..17
#define EVENING         18..21

do_sky() 
{
  int time = clock -> query_hour();
  switch(time) 
  {
    case LATE_NIGHT:
    case EARLY_NIGHT:
      return "It is a dark sky, only stars twinkle above you. ";
    case EARLY_MORNING:
      return "It is now starting to get brighter in the east as the day comes. ";
    case MORNING:
      return "The sun rises above the top of the mountains, yielding a splendid view. ";
    case NOON:
      return "The sun is now due south now, as it is around noon. ";
    case AFTERNOON:
      return "The sun is lower now than at its zenith, emerging slowly to the east. ";
    case EVENING:
      return("The sun is setting below the horizon, and Darkness sneaks upon the land. ");
  }
}

/*
string
add_extra_time()
{
  switch(clock->query_hour()) {
  case LATE_NIGHT:
    if(clock->query_moon())
      return
	"Upon the hills there shines coldly in blue as the Moon "+
        "gently climbs over some dense clouds of the Misty Mountains. ";
    else
      return
	"Utterly darkness unfolds upon this hostile area as the clouds "+
        "over the Misty Mountains shelters the Stars and the Moon from "+
        "the face of earth. ";
  case EARLY_MORNING:
    return
      "The eastern sky slowly brightens up as a new day starts. Still "+
      "the Sun can not be seen emerging over the immense Misty Mountains. ";
  case MORNING:
    return
      "The view of the immensly large peaks in the east is spectacular "+
      "in beauty as the Sun rays upon the white spots of the mountain range. ";
  case NOON:
  case AFTERNOON:
    return
      "Still at high, the Sun shines, though heating only your soul, as she "+
      "is not strong enough at these altitudes to bring the temperature up. ";
  case EVENING:
    return
      "Getting chillier, you sadly understand that the warmth of the Sun, "+
      "will soon cease as she walks below the horizon and the cold night "+
      "begins. ";
  case EARLY_NIGHT:
    if(clock->query_moon())
      return
	"Still not long since the Sun set, the coldness under the Misty Mountains "+
        "upsets you. A sneaky gust from the higher regions chills and the "+
	"Moon and the Stars can not warm you, they only give blue rays of "+
        "everlasting sorrow. ";
    else
      return
	"A dense cold darkness surrounds you as no light from Stars nor Moon "+
        "can permeate the thick layer of hostile clouds over the Misty Mountains. ";
  }
}

string
query_extra()
{
    return add_extra_time();
}

*/
