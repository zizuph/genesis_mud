/*
* Watchtower---Vingaard Keep
* Grace        15 April 1994
* update:      19 Sept   1995
*
* Modified to be the battlement base file by Morrigan
   */

#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <macros.h>

inherit OUT_BASE;

#define SDIR  "/d/Krynn/solamn/splains/room/"
#define PLAINS \
({  \
	SDIR + "plain1", \
	SDIR + "plain2", \
	SDIR + "plain3", \
	SDIR + "plain4", \
	SDIR + "plain5", \
	SDIR + "plain10", \
	SDIR + "plain11", \
	SDIR + "plain12", \
	SDIR + "plain13", \
	SDIR + "plain14", \
	SDIR + "plain15", \
	SDIR + "plain20", \
	SDIR + "plain21", \
	SDIR + "plain22", \
	SDIR + "plain23", \
	SDIR + "plain24", \
	SDIR + "plain25", \
	SDIR + "plain30", \
	SDIR + "plain31", \
	SDIR + "plain32", \
	SDIR + "plain33", \
	SDIR + "plain34", \
	SDIR + "plain35", \
	})
#define ROAD \
({  \
	SDIR + "bridge", \
	SDIR + "road1", \
	SDIR + "road3", \
	SDIR + "road4", \
	SDIR + "road5", \
	SDIR + "road6", \
	SDIR + "road7", \
	SDIR + "road8", \
	})
#define SOUTH \
({  \
	VROOM + "outkeep", \
	VROOM + "bridge", \
	SDIR + "xroad", \
	SDIR + "road9", \
	SDIR + "pier", \
	SDIR + "ferry", \
	"/d/Krynn/newsea/newsea16", \
	})
#define RIVER \
({  \
	SDIR + "river2", \
	SDIR + "river3", \
	SDIR + "river4", \
	SDIR + "river5", \
	SDIR + "river6", \
	SDIR + "river7", \
	})
#define KEEP \
({  \
	VROOM + "inner_court", \
	VROOM + "train2", \
	VROOM + "train1", \
	VROOM +"west_train1", \
	VROOM + "east_train2", \
	VROOM + "ss1", \
	VROOM + "ss2", \
	VROOM + "ss3", \
	VROOM + "ss4", \
	VROOM + "ss5", \
	VROOM + "ss6", \
	VROOM + "es1", \
	VROOM + "es2", \
	VROOM + "es3", \
	VROOM + "es4", \
	VROOM + "es5", \
	VROOM + "ws1", \
	VROOM + "ws2", \
	VROOM + "ws3", \
	VROOM + "ws4", \
	VROOM + "ws5", \
	VROOM + "courtyard", \
	VROOM + "garden", \
	})
#define BATTLE \
({  \
	VROOM + "swtowerup", \
	VROOM + "sb1", \
	VROOM + "sb2", \
	VROOM + "sb3", \
	VROOM + "setowerup", \
	VROOM + "eb1", \
	VROOM + "eb2", \
	VROOM + "eb3", \
	VROOM + "netowerup", \
	VROOM + "nb1", \
	VROOM + "nb2", \
	VROOM + "nb3", \
	VROOM + "nwtowerup", \
	VROOM + "wb1", \
	VROOM + "wb2", \
	VROOM + "wb3", \
	VROOM + "balcony", \
	})


string batt_desc() { return ""; }

void reset_vin_room() { }

void create_battlement() { }

void
create_vin_room()
{
    set_short("Battlement of Vingaard Keep");
    set_long("@@long_desc");
    AI(({"battlement","battlements"}), "@@battle_desc");
    AI("plains", "@@plains_desc");
    AI("south", "@@south_desc");
    ACI("south","look","@@south_desc");
    AI("road", "@@road_desc");
    AI("keep", "@@keep_desc");
    AI("river", "@@river_desc");
    AI("west", "Perhaps you should examine the road or plains?\n");
    AI("east", "In the distance you can see the Dargaard Mountains.\n");
    AI("north", "The Vingaard River flows through the plains toward " +
       "Kalaman in the northeast.\n");
    AI("northeast","You can see the Vingaard River meandering " +
       "toward Kalaman and the mountains of Dargaard, with its " +
       "brooding, haunted Keep.\n");
    AI("southeast", "Far across the plains you can see the Southern "+
       "Darkwoods and the land of Throt.\n");
    AI("northwest", "The Vingaard Mountains rise from the plains, " +
       "and the High Clerist Tower guards the pass to Palanthus.\n");
    AI("southwest", "Solanthus lies in the foothills of the " +
       "Garnet Mountains rising from the plains. Thelgaard " +
       "Keep lies just beyond.\n");
    AI(({"mountains","dargaard","dargaard mountains",
	 "garnet mountains"}),"They rise, purple-black, from the " +
       "desolation of the plains.\n");
    AI(({"thelgaard","solanthus","thelgaard keep","tower","newsea",
	 "throt","darkwoods",}),"It is difficult to see from this " +
       "distance.\n");
    AI("wall","It is sturdy and looks capable of keeping out even " +
       "the Dragonqueen herself!\n");
    AI("walls","They are sturdy and look capable of keeping out even "+
       "the Dragonqueen herself!\n");

    set_tell_time(120);
    add_tell("A gust of wind rolls over you.\n");
    add_tell("You hear the song of a bird in the distance.\n");
    add_tell("You hear muffled voices echoing from below.\n");
    add_tell("The sounds of footsteps drift upwards.\n");
    add_tell("A cloud passes slowly by in the sky above.\n");
    add_tell("The sound of music can be heard from the Bronze " +
	     "Dragon Inn.\n");
    create_battlement();
    reset_vin_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
      start_room_tells();
}

string
battle_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;

    roomfiles = BATTLE;
    roomfiles -= ({ E(TP) });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	live -= ({ TP });
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  return ("On the battlements, you can see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  return ("On the battlements, you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	/*    else if (sizeof(dead) > 0)
	   return ("Inside the Keep's walls, you can see " +
	   COMPOSITE_DEAD(dead) + ".\n");
	*/
    }
    return ("The battlements look grim and empty, a disturbing sign.\n");
}

string
keep_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;

    roomfiles = KEEP;
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  return ("Inside the Keep's walls, you can see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  return ("Inside the Keep's walls, you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	/*    else if (sizeof(dead) > 0)
	   return ("Inside the Keep's walls, you can see " +
	   COMPOSITE_DEAD(dead) + ".\n");
	*/
    }
    return ("The Keep itself looks secure. You might want to examine the " +
      "road and look at the plains and the river, though.\n");
}

string
ledge_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;

    roomfiles = ({ VROOM + "ledge", });
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  return ("On the ledge you see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  return ("On the ledge you see " +
		  COMPOSITE_LIVE(live) + ".\n");
	/*    else if (sizeof(dead) > 0)
	   return ("Inside the Keep's walls, you can see " +
	   COMPOSITE_DEAD(dead) + ".\n");
	*/
    }
    return ("A small piece of land at the bottom of the wall.\n");
}

string
plains_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;

    roomfiles = PLAINS;
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	/*
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	   return ("Looking over the plains, you can see " +
	   COMPOSITE_LIVE(live) + ", as well as " +
	   COMPOSITE_DEAD(dead) + ".\n");

	else */
	if (sizeof(live) > 0)
	  return ("Looking over the plains, you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	/*   else if (sizeof(dead) > 0)
	     return ("Looking over the plains, you see " +
	     COMPOSITE_DEAD(dead) + ".\n");
	     */
    }
    return ("From here the plains seem both empty and endless. " +
	    "Perhaps you should examine the road and the river.\n");
}

string
river_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;
    
    roomfiles = RIVER;
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  return ("Squinting your eyes against the glare, you can see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  return ("Squinting your eyes against the glare, you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	else if (sizeof(dead) > 0)
	  return ("Squinting your eyes against the glare, you can see " +
		  COMPOSITE_DEAD(dead) + ".\n");
    }
    return ("From here the river seems secure. Try looking south, " +
	    "or examine the plains and the road.\n");
}

string
road_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;

    roomfiles = ROAD;
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  return ("On the west road to Palanthas, you can see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  return ("On the west road to Palanthas, you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	else if (sizeof(dead) > 0)
	  return ("On the west road to Palanthas, you can see " +
		  COMPOSITE_DEAD(dead) + ".\n");
    }
    return ("From here the road looks untravelled. Try looking south, " +
	    "or examine the plains and the river.\n");
}


string
south_desc()
{
    string *roomfiles;
    object *inv, *live, *dead, room;
    int i;
    
    roomfiles = SOUTH;
    inv = ({});
    for (i = 0; i < sizeof(roomfiles); i++)
    {
	if ((room = find_object(roomfiles[i])) != 0)
	  inv += all_inventory(room);
    }
    
    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	  return ("Looking south from the Keep toward Solanthus and Newsea, "+
		  "you can see " +
		  COMPOSITE_LIVE(live) + ", as well as " +
		  COMPOSITE_DEAD(dead) + ".\n");
	else if (sizeof(live) > 0)
	  return ("Looking south from the Keep toward Solanthus and Newsea, "+
		  "you can see " +
		  COMPOSITE_LIVE(live) + ".\n");
	else if (sizeof(dead) > 0)
	  return ("Looking south from the Keep toward Solanthus and Newsea, "+
		  "you can see " +
		  COMPOSITE_DEAD(dead) + ".\n");
    }
    return ("From here the area south of the Keep looks deserted. Try checking "+
	    "the road, or examine the plains and the river.\n");
}

string
long_desc()
{
    return (season()+batt_desc()+"To the north, the Vingaard River " +
	    "converges with a smaller tributary. The vast plains of " +
	    "Solamnia stretch out around you, and you can see quite " +
	    "a distance in all directions.\n");
}

