inherit "/d/Rhovanion/lib/mapserver";

#include <ss_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"

#ifndef ROOM_I_NO_ME_SUN
#define ROOM_I_NO_ME_SUN "_room_i_no_me_sun"
#endif

#define CLOCK "/d/Gondor/elessar/lib/clock"
#define TIME (string)CLOCK->query_time_of_day()

#define COBWEBS "The nastiest things you see are cobwebs: dark and dense "+ \
                "with extraordinarily thick threads, often stretched from "+ \
                "tree to tree, or tangled in the lower branches."

#define SOUNDS "You can hear grunts, scufflings, and moans in the undergrowth."

#define EYES   "You also see many eyes around you in forest. Some of them "+ \
               "look like eyes of insects, but they are bigger."

#define TREES  "Menacing gloomy trees, with black leaves, loom everywhere "+ \
               "around you."

#define SPIDER     		NPC_DIR+"spider"
#define	MAX_SPIDERS_UP		10
#define	MAX_SPIDERS_DOWN	35

/*
 * Function name: query_file_with_map
 * Description:	  This function is necessary to redefine
 * Returns:	  Should return string or object that defines function
 *                string *map()  (actual map of the area)
 */
mixed
query_file_with_map()
{
  return "/d/Rhovanion/common/mirkwood/mirk_map";
}

int
this_is_room(string arg)
{
  if(arg == "m") return 0;
  return ::this_is_room(arg);
}

/*
 * Function name: query_paths
 * Returns:	  Should return array of letters representing paths on map
 */
string *
query_paths()
{
  return ({"p","P"});
}

string
path_desc_start(string where)
{
  if(where == "p")
    return "There is a small path here. It continues ";
  if(where == "P")
    return "The path continues to the ";
  return ::path_desc_start(where);
}

string
path_desc_end(string where)
{
  if(where == "p")
    return " from here";
  if(where == "P")
    return "";
  return ::path_desc_end(where);
}

string *query_show()
{
  return ({ "m","T","P","p","m" });
}

string
neighbour_desc_start(string from, string to)
{
  if(to == "m")
    return "Huge peaks of some mountains are ";
  if(to == "p")
    return "You spot small path ";
  if(to == "P")
    return "The unused path is to ";
  if(to == "T")
    return "There is some cave to ";
  if(to == "M")
    return "Some old wide road is ";
  return ::neighbour_desc_start(from, to);
}

string
neighbour_desc_end(string from, string to)
{
  if(to == "m")
    return " from here";
  if(to == "p")
    return " from here";
  return ::neighbour_desc_end(from, to);
}

int
player_see_surrounding(object who, string from, string to)
{
  if(to == "p")
    if((who->query_skill(SS_AWARENESS) < 30) && (from != "p"))
      return 0;
  if(to == "P")
    if((who->query_skill(SS_AWARENESS) < 20) && (from != "P"))
      return 0;
  if(to == "T")
    if((who->query_skill(SS_AWARENESS) < 20) && (from != "T"))
      return 0;
  if(to == "M")
    if((who->query_skill(SS_AWARENESS) < 20) && (from != "M"))
      return 0;
  return ::player_see_surrounding(who, from, to);
}

/*
 * Function name: query_no_spiders
 * Returns:	  Should return array of letters on map where we dont 
 *                want spiders
 */
string *
query_no_spiders()
{
  return ({"p","P","T","E","W","S","N"});
}

void
reset_map_room(string where)
{
  string name;

  if((query_room_letter() == "x") &&
     !random(10))
  {
    object spider;
    name = "_spider_u_" + random(MAX_SPIDERS_UP) + "_";
    if(find_living(name))
      return;

    spider = clone_object(SPIDER);
    spider->move_living("into a room", this_object());
    spider->set_living_name(name);
  }
/* commented out for now
  if((query_room_letter() == "X") &&
     !random(10))
  {
    object spider;
    name = "_spider_d_" + random(MAX_SPIDERS_DOWN) + "_";
    if(find_living(name))
      return;

    spider = clone_object(SPIDER);
    spider->move_living("into a room", this_object());
    spider->set_living_name(name);
  }
end of commented out */
}

/*
 * Function name: set_up_room
 * Description:	  Called when room from map is created
 * Argument:	  where - letter from the map corresponding to this room
 * Usage:         Here you should set things like descriprions, items,
 *                properties etc for your room.
 */
void
set_up_room(string str)
{
  switch (str)
  {
    case "x":
	set_short("Mirkwood forest");
	set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");

	add_prop(ROOM_I_LIGHT, 0);
	add_prop(ROOM_I_NO_ME_SUN, 1);
	break;
    case "p":
	set_short("Tiny path in forest");
	set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");

	add_prop(ROOM_I_LIGHT, 0);
	add_prop(ROOM_I_NO_ME_SUN, 1);
	break;
    case "N":
    case "E":
    case "S":
    case "W":
	set_short("Mirkwood forest");
	set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");
	add_exits();
	break;
    case "G":
	set_short("Dol Guldur");
	set_long("Someone hasn't coded Dol Guldur yet, so it's "+
		 "not here.\n");
	add_exits();
	break;
    case "T":
	set_short("Thraduil's Caverns");
	set_long("Someone forgot to put in Thranduil's Cavern "+
			     "here.\n");
	add_exits();
	break;
    case "M":
	set_short("Men-i-Naugrim");
	set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");
	add_exits();
	break;
    case "m":
	set_short("Mountains of Mirkwood");
	set_long("You are on the mountains of Mirkwood. All "+
		 "around you you can see treetops.\n");
	add_exits();
	break;
    case "P":
        set_short("Unused path through Mirkwood");
        set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");

        add_item(({ "tree", "trees" }),
        "This hideous, twisted ancient tree has cobwebs draped over it.\n ");

        add_item(({"cobweb", "cobwebs" }),
        "It looks like it was made by an enormous spider!\n");

	add_exits();
	add_prop(ROOM_I_LIGHT, 0);
	add_prop(ROOM_I_NO_ME_SUN, 1);
	break;
  }
  reset_room();
}

string
path_desc_start(string where)
{
  if(where == "p")
    return "There is a small path here. It continues ";
  if(where == "P")
    return "The path continues to the ";
  return ::path_desc_start(where);
}

string
path_desc_end(string where)
{
  if(where == "p")
    return " from here";
  if(where == "P")
    return "";
  return ::path_desc_end(where);
}

/*
 * Function name: player_is_lost
 * Description:	  Test if player lost directions
 * Argument:	  who - object living
 * Returns:	  1 if lost,  0 if knows directions
 */
int
player_is_lost(object who, string where)
{
  if(where == "x")
    if(who->query_skill(SS_LOC_SENSE) < random(51))
      return 1;
  return 0;
}



string
query_rivername(string arg)
{
  return "";
}

string
my_long(string arg)
{
  string river, text = "";

    switch (arg) {
        case "N":
        case "E":
        case "S":
        case "W":
                  text = " The forest seems to be little thinner here.";
        case "p":
        case "x":
            switch(TIME) {
                case "early morning":
                case "night":
                case "evening":
                    text = "You are somewhere in the Mirkwood. It is "+
                      TIME+" now and you can hardly see your hands. "+
                      TREES+" "+SOUNDS+" "+EYES + text;
                    break;
                case "morning":
                case "noon":
                case "afternoon":
                    text = "You are somewhere in the Mirkwood. "+TREES+
                      " You guess it is "+TIME+" now, although you can't "+
                      "see the sky "+
                      "because of the the trees. "+SOUNDS+" "+COBWEBS+                   	      "The air here is quite hot and stuffy." + text;
                    break;
            }
            break;
        case "P":
            switch(TIME) {
                case "morning":
                case "noon":
                case "afternoon":
                  text = "You are deep on a dark path through Mirkwood "+
                      "forest. Although it is "+TIME+", it is very dark "+
                      "here. "+TREES+" "+SOUNDS+" "+COBWEBS+" No cobwebs "+
                      "stretch across the path, but whether some magic keeps "+
                      "the path clear, or it is clear for some other "+
                      "reason you cannot guess.";
                    break;
                case "early morning":
                case "night":
                case "evening":
                  text = "You are deep on a dark path through Mirkwood "+
                      "forest. "+TREES+" "+SOUNDS+" "+EYES+" "+
                      COBWEBS+" No cobwebs stretch "+
                      "across the path, but whether some magic keeps "+
                      "the path clear, or it is clear for some other "+
                      "reason you cannot guess.";
                    break;
            }
            break;
        case "M":
            switch(TIME) {
                case "early morning":
                case "night":
                case "evening":
                  text = "You are on a wide ancient road that goes straight "+
                      "in east-west direction. Rumours tell about the "+
                      "firstborn elves using it on their way to the land of "+
                      "Bliss. During Durin's realm in Khazad-dum it was well "+
                      "maintained and since then it is called Men-i-Naugrim. "+
                      "But now only fools use is on their way to the death. "+
                      TREES+" "+SOUNDS+" "+EYES+" "+COBWEBS;
                    break;
                case "morning":
                case "noon":
                case "afternoon":
                  text = "You are on a wide ancient road that goes straight "+
                      "in east-west direction. Rumours tell about the "+
                      "firstborn elves using it on their way to the land of "+
                      "Bliss. During Durin's realm in Khazad-dum it was well "+
                      "maintained and since then it is called Men-i-Naugrim. "+
                      "But now only fools use is on their way to the death. "+
                      TREES+" "+SOUNDS+" "+COBWEBS;
                    break;
            }
            break;
        case "c":
            switch(TIME) {
                case "early morning":
                case "morning":
                    text = "You are on a clearing in the Mirkwood. Between " +
                      "the trees you can catch glimpses of the sky. It is " +
                      TIME + " now. The darkness is still quite deep.";
                    break;
                case "noon":
                case "afternoon":
                    text = "You are on a clearing in the Mirkwood. The sun " +
                      "is shining, but the light can hardly penetrate the " +
                      "thick layer of leaves.";
                    break;
                case "evening":
                case "night":
                    text = "You are on a clearing in the Mirkwood. It is " +
                      "very dark here. The air has a bit more fresh scent " +
                      "here than in the forest.";
                    break;
            }
            break;
        case "r":
            switch(TIME) {
                case "early morning":
                case "morning":
                    river = query_rivername(arg);
                    text = "You are by the river " + (river == "" ?
                      "" : river + " ") + "in the Mirkwood. You can hardly " +
                      "see the other riverbank.";
                    break;
                case "noon":
                case "afternoon":
                    text = "You are by the river " + (river == "" ?
                      "" : river + " ") + "in the Mirkwood. It is quite " +
                      "dim here, although it is " + TIME + " now.";
                    break;
                case "evening":
                case "night":
                    text = "You are by a river in the Mirkwood. It is very " +
                      "dark here, and the other riverbank is out of sight " +
                      "in the darkness.";
                    break;
            }
            break;
        default: text = "You are wandering around in Mirkwood forest.";

    }
    return text+"\n";
}

