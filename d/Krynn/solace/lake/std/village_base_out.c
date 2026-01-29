/*
 * Base outside room for the Toron minotaur village with
 * path leading to it.
 *
 * by Cherek Jan 2007.
 */
 
#pragma strict_types

#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include <composite.h>
#include <filter_funs.h>

/* Inherit the Krynn room */
inherit OR_FILE

int room_alarm = 0;

string gLong_desc, gStart_desc, location;

public void
set_location(string str)
{
    location = str;
}

public void
set_start_desc(string str)
{
    gStart_desc = str;
}

public void
set_long_desc(string str)
{
    gLong_desc = str;
}

/*
 * Function name: add_path_items
 * Description  : Adds items to the path leading to the village, based
 *                on time and season.
 */
 
public void
add_path_items()
{
    
    switch (GET_SEASON)
    {
        case WINTER:
            add_item(({"snow", "layer of snow"}),
                       "The snow appears to be around five inches deep. " +
                       "Every second more and more snowflakes quietly " +
                       "lands on the ground. \n");

            add_item(({"sky", "clouds", "gray clouds"}),
                       "Here and there you spot the blue sky hiding " +
                       "behind the gray clouds. \n");        
            break;
        
        case SPRING:
            add_item("waves",
                     "The clear water is rippled by small waves caused by " +
                     "the wind. \n");    
            break;
        
        case SUMMER:
            add_item(({"landscape", "majestic landscape", "nature"}),
                       "Green blossoming trees, a crystal clear lake, " +
                       "and great mountains. The nature around " +
                       "you looks just like a classic summer painting. \n");
            break;
        
        case AUTUMN:
            add_item(({"rain", "raindrops"}),
                       "It is cold and wet. \n");
            
            add_item(({"sky", "clouds", "cloudy sky"}),
                       "Heavy dark clouds covers the sky. It does not look " +
                       "like it will stop raining anytime soon. \n");
            break;
    }

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN: 

            add_item(({"horizon", "haze"}),
                       "It is hard to see very far since a light haze " +
                       "covers the lands. \n"); 
            break;
               
        case TOD_TWILIGHT:
    
            add_item(({"shadow", "shadows"}),
                       "They seem to engulf the ground in darkness. \n");
            break;
        
        case TOD_NIGHT:
            add_item(({"light", "pale light"}),
                       "It is pale and does not give much light. \n");
                       
            add_item(({"shadow", "shadows"}),
                       "They seem to engulf the ground in darkness. \n");                       
            break;
    }

    if (GET_SEASON == WINTER)
    {
        add_item(({"path", "track", "road"}),
                   "This very narrow track does not look very " +
                   "well used. It is covered by a layer of snow. \n");

        add_item(({"ground", "snow", "layer of snow", "layer"}),
                 "The snow is about five inches deep. \n");

        add_item(({"tree", "trees", "forest"}),
                   "You spot many different trees, from tall pines to " +
                   "great Vallenwood trees common in the area. A layer of " +
                   "snow covers the trees as well as the ground. \n");	 

        add_item(({"lake", "water", "waters"}),
                   "You are walking on the shores of the great Crystalmir " +
                   "Lake. The water looks cold but is only frozen near the " +
                   "shores. \n");  

        add_item(({"lakeshore", "shore"}),
                   "The water is frozen near the shores of the lake. \n"); 

        add_item(({"pines", "tall pines"}),
                   "Snow-covered pines are one of the most common trees " +
                   "in this mixed forest. \n");

        add_item(({"vallenwood", "vallenwood trees"}),
                   "Standing over two hundred feet tall these mighty " +
                   "trees dominate the forest. The naked branches are " +
                   "frosty from the cold air. \n");

    }

    else
    {    
        add_item(({"path", "track", "road"}),
                   "This very narrow track does not look very well used. " +
                   "Grass and straw cover the ground, making it hard to " +
                   "see the path. \n");

        add_item(({"straw", "straws"}),
                   "Small straws of dead grass covers the ground. \n");

        add_item("grass",
                 "Grass from the surrounding forest hangs over the " +
                 "track. \n");	  

        add_item(({"ground", "dirt", "rock", "rocks"}),
                   "The ground is made from dirt and small rocks. \n");

        add_item(({"tree", "trees", "forest"}),
                   "You spot many different trees, from tall pines to " +
                   "great Vallenwood trees common in the area. \n");

        add_item(({"lake", "water", "waters"}),
                   "You are walking on the shores of the great Crystalmir " +
                   "Lake. You can barely make out the other side. \n");

        add_item(({"lakeshore", "shore"}),
                   "This seem to be the eastern shores of the lake. \n"); 
        
        add_item(({"pines", "tall pines"}),
                   "One of the most common trees in this mixed forest. \n");

        add_item(({"vallenwood", "vallenwood trees"}),
                   "Standing over two hundred feet tall these mighty " +
                   "trees dominate the forest. \n");
    }

}

/*
 * Function name: add_road_items
 * Description  : Adds items to the outside rooms in the village 
 *                (the roads). Based on time and season.
 */
 
public void
add_road_items()
{

    switch (GET_SEASON)
    {
        case WINTER:
            add_item("landscape",
                     "Snow covers the lands. \n");

            add_item(({"snow", "light snow"}),
                       "Snowflakes silently fall all around you. \n");
            break;
        
        case AUTUMN:
            add_item(({"rain", "raindrops"}),
                       "It is cold and wet. \n");
            
            add_item(({"sky", "clouds", "cloudy sky"}),
                       "Heavy dark clouds covers the sky. It does not look " +
                       "like it will stop raining anytime soon. \n");
            break;
    }

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            add_item(({"sun", "horizon"}),
                       "The sun has a pale orange color. \n"); 
            
            add_item(({"horizon", "haze"}),
                       "It is hard to see very far since a light haze " +
                       "covers the lands. \n"); 
            break;
        
        case TOD_DAY:
        
            add_item("sun",
                     "The sun has a clear yellow color. \n"); 
            break;
        
        case TOD_TWILIGHT:
            add_item("sun",
                     "The sun has a deep red color. \n"); 

            add_item("glow",
                     "It is clear another day will soon come to " +
                     "an end. \n");
            break;
        
        case TOD_NIGHT:
            add_item(({"light", "pale light"}),
                       "It is pale and does not give much light. \n");

            add_item("flames",
                     "They seem to have their own life, flickering " +
                     "back and forth in a random pattern. \n");

            add_item(({"pattern", "random pattern"}),
                       "It is truly random. \n");                      
                     
            break;
    }
}

/*
 * More items that can be added to induvidual rooms.
 */
 
public void
add_village()
{
    add_item(({"village", "huts", "tents", "camp", "area"}),
               "You count about fifteen tents and huts in the " +
               "village. It seems like most of them have been " +
               "raised or built recently. In the northern part " +
               "you spot a large wooden structure that " +
               "seems to be the only actual building in the " +
               "entire village. \n");
}

public void
add_trees()
{
    add_item(({"tree", "trees"}),
               "You spot many different trees, from tall pines " +
               "to great Vallenwood trees common in the area. " +
               "Some trees have been chopped down and turned into " +
               "building material for the village. Between the trees " +
               "you spot a glimpse of the great Crystalmir Lake. \n");	 
}

public void
add_path()
{
    add_item(({"path", "road", "dirt road"}),
               "The road is very narrow and made of dirt " +
               "and mud. \n"); 
}

public void
add_dirt_mud()
{
    add_item(({"dirt", "mud"}),
               "There is nothing special about it. \n"); 
}

public void
add_smoke()
{
    add_item("smoke",
             "It makes the air hard to breathe. \n");
}

public void
add_fires()
{
    add_item(({"fire", "fires", "campfire", "campfires"}),
               "Simple campfires are placed in front of almost every tent " +
               "or hut. Some have cooking pots hanging over them. \n");
}

public void
add_pots()
{
    add_item(({"pot", "pots", "cooking pot", "cooking pots"}),
               "They are made from iron and look battered and " +
               "well-used. \n");
}

public void
add_lake()
{
    add_item("lake",
             "This is the eastern shore of the great " +
             "Crystalmir Lake.\n");
}

public void
add_tent_entrance()
{
    add_item("entrance",
             "A simple tent flap marks the entrance. \n");
}

public void
add_hut_entrance()
{
    add_item("entrance",
             "There is no door. \n");
}

public void
add_hides()
{
    add_item(({"hides", "animal hides"}),
               "The hides are gray or brown in color, some have been " +
               "sewn together, others are just overlapping each other \n");

}

public void
add_structure()
{
    add_item(({ "structure", "wooden structure", "fortress" }),
                "It looks a like some kind of small fortress " +
                "made from wooden poles and logs. It is by " +
                "far the largest structure in the village. \n");
}

public void
add_poles_logs()
{
    add_item(({ "poles", "logs" }),
                "The wood is still very fresh. \n");

}

public void
add_tent()
{
    add_item(({"tent", "large tent"}),
               "A simple tent made of animal hides. It serves " +
               "as a temporary home for some of the minotaurs " +
               "in the village. \n");
}


public void
add_entrance()
{
    add_item("entrance",
             "The only way to tell the village ends or begins here " +
             "is the lack of tents and huts to the south. \n");
}
public void
add_hut()
{
    add_item(({"hut", "wooden hut"}),
               "A simple hut made of wooden logs. It looks like " +
               "it has been built in a hurry and there is still " +
               "much work to be done, yet it serves as good " +
               "shelter for some of the minotaurs living in the " +
               "village. \n");
}

/*
 * Function name: long_desc
 * Description  : Long room descriptions based on time and season.
 */
 
public string
long_desc()
{
    string desc;

    desc = gStart_desc;

    if(location == "ROAD")
    {
        switch (GET_TIMEOFDAY)
        {
            case TOD_DAWN:
                desc += "The sun is rising above the horizon and the camp " +
                        "is bustling with activity. Smoke is rising from " +
                        "the numerous fires scattered throughout the area. ";
                break;
            
            case TOD_DAY:
                desc += "The sun is shining down on you and the camp " +
                        "is bustling with activity. Smoke is rising from " +
                        "the numerous fires scattered throughout the area. ";
                break;
            
            case TOD_TWILIGHT:
                desc += "The sun is slowly sinking, bathing the entire " +
                        "camp in a pale reddish glow. Smoke is rising " +
                        "from a number of fires scattered throughout the " +
                        "area. ";
                break;
            
            case TOD_NIGHT:
                desc += "The pale light from the two moons gives the " +
                        "entire camp a serene and almost ghostly feel. " +
                        "Flames from numerous fires scattered throughout " +
                        "the area dance around you. ";
                break;
        }

        switch (GET_SEASON)
        {
            case WINTER:
                desc += "The air is cold and crisp and the entire " +
                        "landscape surrounding the camp is frozen. " +
                        "A light snow is falling from the partly " + 
                        "clouded sky. ";
                break;
            
            case SPRING:
                desc += "Spring is in the air and the great trees " +
                        "surrounding the camp are blossoming. ";
                break;
            
            case SUMMER:
                desc += "The air feels warm and the great trees " +
                        "surrounding the camp are vibrant and green. ";
                break;
            
            case AUTUMN:
                desc += "The air is chill and the great trees " +
                        "surrounding the camp are colored by autumn. " + 
                        "You feel a light rain falling down from the " +
                        "cloudy sky. ";
                break;
        }
    }

    else if(location == "PATH")
    { 
        switch (GET_TIMEOFDAY)
        {
            case TOD_DAWN:
                desc += "The sun is slowly rising above the horizon, " +
                        "highlighting the mighty forest surrounding you. ";
                break;
            
            case TOD_DAY:
                desc += "The sun is shining down on you, filtering through " +
                        "the many trees in the surrounding forest. ";
                break;
            
            case TOD_TWILIGHT:
                desc += "The sun is sinking behind the trees, making " +
                        "the mighty forest surrounding you cast long " +
                        "shadows on the ground. ";
                break;
            
            case TOD_NIGHT:
                desc += "The pale light from the two moons makes the " +
                        "many trees surrounding you cast strange shadows " +
                        "on the ground. ";
                break;
        }
    
        switch (GET_SEASON)
        {
            case WINTER:
                desc += "Winter is in the air and a thin layer of snow " +
                        "covers the lands. A light snow is falling from " +
                        "the partly clouded sky. ";
                break;
            
            case SPRING:
                desc += "Spring is in the air, yet a cold breeze blows " +
                        "from the north causing small waves to appear " +
                        "on the lake. ";
                break;
            
            case SUMMER:
                desc += "Summer is in the air and the water of the great " +
                        "lake reflects the majestic landscape. ";
                break;
            
            case AUTUMN:
                desc += "Autumn is in the air and the water of the great " +
                        "lake is rippled by raindrops falling from the " +
                        "cloudy sky. ";
                break;
        }        
    }      
    desc += gLong_desc;

    return desc + "\n";
}

public void create_toron_room()
{
}

/*
 * Function name: room_actions
 * Description  : Adds random events to the room, based on
 *                location.
 *                NOTE: Called using an alarm.
 */
 
void
room_actions()
{    
    string *road_action = 
    ({ 
      "Your eyes start to water as you are hit by a gust of smoke.",
      "A cold breeze clears the smoke for a brief moment.",
      "A raven quietly lands on the ground and starts hacking on an " +
      "animal carcass.", 
      "A lone dog barks in the distance.",
      "The smell of dead animal penetrates the thick smoke-filled air."
    });
      
    string *path_action = 
    ({ 
      "The mighty trees sway slightly in the wind.",  
      "You hear a splash as a fish jumps in the nearby lake.",
      "A small squirrel suddenly darts across the path in front of you.",
      "A cold wind blows through the surrounding trees.",
      "You catch a few ravens circling high above you."
    }); 

    if (location == "ROAD")
    {
        tell_room(this_object(), 
                  road_action[random(sizeof(road_action))] + "\n");
    }

    else if (location == "PATH")
    {
        tell_room(this_object(), 
                  path_action[random(sizeof(path_action))] + "\n");
    }
}

nomask public void 
create_krynn_room()
{   

    set_long(long_desc);    
    create_toron_room();  
    
}

/*
 * Function name: enter_inv
 * Description  : Checks if a player enters and turns on
 *                the alarm so random "events" can happen.
 */
 
void
enter_inv(object ob, object from)
{    
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        if (!room_alarm)
        {
            room_alarm = set_alarm(itof(random(20)+10), 
            itof(random(200)+100),
            &room_actions(this_object()));       
        }
    }
}

/*
 * Function name: leave_inv
 * Description  : Checks if there is still a player in the
 *                rooms. If not it removes the alarms from
 *                the room so no "events" happen if nobody
 *                is in the room.
 */
 
void
leave_inv(object ob, object to)
{    
    ::leave_inv(ob, to);

    int players = 0;
    
    if (interactive(ob))
    {        
        object *livings = all_inventory(this_object());
    
        for(int i = 0; i < sizeof(livings); i++)
        {
            if (interactive(livings[i]))
            {
                players = players + 1;
            }
        }
    }

    if (players == 0)
    {
        remove_alarm(room_alarm);
        room_alarm = 0;
    }
}

public void reset_toron_room()
{
}

nomask public void
reset_krynn_room()
{
    reset_toron_room();
}


