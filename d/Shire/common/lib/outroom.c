#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/common/lib/rom";

static object clock, watcher;
static int life;
string *life_list;

create_rom() {
    clock = find_object(CLOCK);
    add_prop(ROOM_I_INSIDE, 0);
    ITEM(({"sky","moon","sun","stars","heaven"}),"@@do_sky@@\n");
    ITEM(({"mountains","Misty Mountains","misty mountains","tops"}),
        "These high unclimbable mountains divide the whole Middle Earth\n"+
        "in two. They rise up into the white cloads which brings cold and\n"+
        "ice to the tops of the mountains. You surely cannot cross east\n"+
        "over these mountains. If there is a way over east, it must be\n"+
        "through under the mountains. It is said that there used to be\n"+
        "a vast kingdom of dwarves here, but where is the entrance?\n");
    this_object()->create_outroom();
    life_list =
      ({
	"scream,creature,crow",
	  "The crow, or whatever it was, yelled from a distance.",
	"whine,gust,wind",
	  "The chilling wind came from the mountains.",
	"wolves, sounds",
          "The wolves shouts from a distance. Let's hope they don't get the scent of you.",
	"threat",
	  "You shiver to the bones in the overwhelming threat of the Misty Mountains.",
	"echo",
	  "It can not be looked at, only heard."
      });
    my_exit_desc_mode = 1;
}


reset_rom() {
    this_object()->reset_outroom();
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

#define CRAW     0
#define GUST     1
#define WOLVES   2
#define THREAT   3
#define ECHO     4

int
night()
{
    int time = clock->query_hour();
    if(time<4 || time > 17)
	return 1;
    else
	return 0;
}

int
is_it_sun()
{
    int time = clock->query_hour();
    if(time>3 && time <18)
	return 1;
    else
	return 0;
}

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

string
add_extra_time()
{
  switch(clock->query_hour()) {
  case LATE_NIGHT:
    if(clock->query_moon())
      return
	" Upon the hills there shines coldly in blue as the Moon "+
        "gently climbs over some dense clouds of the Misty Mountains.\n";
    else
      return
	" Utterly darkness unfolds upon this hostile area as the clouds "+
        "over the Misty Mountains shelters the Stars and the Moon from "+
        "the face of earth.\n";
  case EARLY_MORNING:
    return
      " The eastern sky slowly brightens up as a new day starts. Still "+
      "the Sun can not be seen emerging over the immense Misty Mountains.\n";
  case MORNING:
    return
      " The view of the immensly large peaks in the east is spectacular "+
      "in beauty as the Sun rays upon the white spots of the mountain range.\n";
  case NOON:
  case AFTERNOON:
    return
      " Still at high, the Sun shines, though heating only your soul, as she "+
      "is not strong enough at these altitudes to bring the temperature up.\n";
  case EVENING:
    return
      " Getting chillier, you sadly understand that the warmth of the Sun, "+
      "will soon cease as she walks below the horizon and the cold night "+
      "begins.\n";
  case EARLY_NIGHT:
    if(clock->query_moon())
      return
	" Still not long since the Sun set, the coldness under the Misty Mountains "+
        "upsets you. A sneaky gust from the higher regions chills and the "+
	"Moon and the Stars can not warm you, they only give blue rays of "+
        "everlasting sorrow.\n";
    else
      return
	" A dense cold darkness surrounds you as no light from Stars nor Moon "+
        "can permeate the thick layer of hostile clouds over the Misty Mountains.\n";
  }
}

static string *name;
  
string
add_extra_life()
{
    life = random(5);
    if(name && sizeof(name))
	remove_item(name[0]);
    name = explode(life_list[2*life],",");
    add_item(name, life_list[2*life+1]+"\n");
  
    switch(life)
    {
      case 0:
	return
	  "A ghostly scream echoes as a creature, a crow perhaps, yells into "+
          "the mountains. ";
      case 1:
	return
	  "A whine of gust chills your bones as wind from above yawns into the lowlands. ";
      case 2:
        return
	  "From a distance you hear the frightening sounds of wolves echoing in the mountains. ";
      case 3:
        return
            "Standing there, you feel the intense overwhelming threat of the "
	  + "Misty Mountains. They look almost as teeth; hostile, barren, and untamed... ";
      case 4:
        return
            "You surely thought you could hear someone! A large frightening creature, "+
            "perhaps? Or was it just an echo of yourself from the mountains? ";
    }
}

string
query_extra()
{
    string extra;
    extra = add_extra_time();
    if(random(3)==2)
        extra += add_extra_life();
    return extra;
}
