/*
 * Base inside room for the Toron minotaur village with
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
inherit R_FILE
                        
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

public void
add_walls()
{
    add_item(({"tent", "wall", "walls", "hide", "hides"}),
               "The walls are made from different kinds of animal " +
               "hides, some have been sewn together, others are " +
               "just overlapping each other. \n");
}

public void
add_hut_walls()
{
    add_item(({"hut", "wall", "walls", "poles", "heavy logs",
               "rope", "strong ropes"}),
               "Two long poles every two meters stand straight up " +
               "and between them are heavy logs stacked on top of " +
               "each other. The logs are tied together with strong " +
               "ropes and make out the walls of the hut. You notice " +
               "the roof is made in a similar manner. \n");
}

public void
add_hut_roof()
{
    add_item("roof",
             "The roof is made of huge logs tied together. It is " +
             "leaning on a long pole standing straight up in the " +
             "middle of the room. A hole has been made to let the " +
             "smoke from the fire out. \n");
}

public void
add_pole()
{
    add_item(({"pole", "long pole"}),
               "It seems like this pole is the only thing that is " +
               "keeping the roof from caving in. Luckily it looks " +
               "very sturdy. \n");
}

public void
add_furs()
{
    add_item(({"fur", "furs", "smelly furs"}),
               "They are dark brown, long-haired and very dirty. \n");
}

public void
add_smoke()
{
    add_item("smoke",
             "It makes the air hard to breathe. \n");
}

public void
add_fire()
{
    add_item(({"fire", "camp fire", "center"}),
               "A fire burns in the middle of the tent. Considering " +
               "the amount of smoke here you guess the fire is never " +
               "put out. \n");
}

public void
add_hut_fire()
{
    add_item(({"fire", "large fire", "hole", "hole in roof"}),
               "A fire burns in the middle of the hut. Above it a " +
               "hole has been made in the roof to let the smoke out. " +
               "Considering the amount of smoke in here you wonder " + 
               "if they not made the hole too small. \n");
}

public void
add_hut_flames()
{
    add_item(({"flame", "flames"}),
               "They dance around randomly. \n");
}

public void
add_tent_light()
{
    add_item("light",
             "The fire is the only lightsource. \n");
}

public void
add_hut_shadows()
{
    add_item(({"shadow", "shadows"}),
               "They move with the flames. \n");
}

public void
add_twigs_straw()
{
    add_item(({"twig", "twigs", "straw", "straws"}),
               "Pieces of twigs and straw cover the ground. \n");
}

public void
add_logs()
{
    add_item(({"chair", "chairs", "log", "logs", "rock", "rocks", 
               "big rock", "big rocks", "huge log", "huge logs"}),
               "Calling this a chair is probably a disgrace for real " +
               "chairs, however it does seem like an effort has " +
               "been made to find logs and rocks that are at " +
               "least remotely comfortable. \n");
}

public void
add_furniture()
{
    add_item(({"chair", "chairs", "log", "logs", "rock", "rocks", 
               "furniture", "big rock", "big rocks", "huge log", 
               "huge logs", "table", "tables"}),
               "A large flat rock must be the dinner table since " +
               "its surrounded by smaller rocks and logs that clearly " +
               "are supposed to be chairs. \n");
}

public void
add_ground()
{
    add_item(({"ground", "dirt", "floor"}),
               "The ground is a mix of dirt, mud, twigs and straw. " +
               "It does not look very comfortable to sleep on but " +
               "as you see nothing resembling beds anywhere you guess " +
               "the sleeping takes place here. \n");
}

public void
add_hut_ground()
{
    add_item(({"ground", "dirt", "floor", "bed", "beds"}),
               "The ground is a mix of dirt, mud, twigs and straws. " +
               "Near the walls it has been tightly packed and covered " +
               "with large animal furs creating simple beds. They do " +
               "not look very comfortable. \n");
}

public void
add_opening()
{
    add_item(({"opening", "exit"}),
               "The opening leads back to where you came from. \n");
}

/*
 * Function name: long_desc
 * Description  : Long room descriptions based on location and
 *                time of day.
 */
 
public string
long_desc()
{
   string desc;

   desc = gStart_desc;
    
   if(location == "TENT")
   { 
        switch (GET_TIMEOFDAY)
        {
            case TOD_NIGHT:
                desc += "It is quite obvious the inhabitans have not " +
                        "lived here for long as the interior is quite " +
                        "spartan. The ground is made of hard packed dirt " +
                        "with a small fire in the center. The dancing " +
                        "flames are the only source of light casting " +
                        "strange shadows on the walls. Around the fire a " +
                        "couple of huge logs and big rocks have been placed " +
                        "serving as crude chairs. The air is difficult to " +
                        "breathe and thick with smoke but you can still " +
                        "smell the typical odor coming from large " +
                        "furry creatures. ";
                break;

            default:
                desc += "It is quite obvious the inhabitans have not " +
                        "lived here for long as the interior is quite " +
                        "spartan. The ground is made of hard packed dirt " +
                        "with a small fire in the center. Around the " +
                        "fire a couple of huge logs and big rocks have " +
                        "been placed serving as crude chairs. The air is " +
                        "difficult to breathe and thick with smoke but " +
                        "you can still smell the typical odor coming " +
                        "from large furry creatures. ";
        }
    }

    else if(location == "HUT")
    {
        switch (GET_TIMEOFDAY)
        {
            case TOD_NIGHT:
                desc += "It has been made of heavy logs and long poles " +
                        "tied together with strong ropes. Although " +
                        "slighly better than a tent this still appears to " +
                        "be a temporary home as it is very sparsely " +
                        "furnitured. Logs and rocks serve as chairs " +
                        "and tables while tightly packed dirt covered " +
                        "with smelly furs must be the beds. The only " +
                        "other noticable feature is the large fire burning " +
                        "in the middle of the room making the air very " +
                        "difficult to breathe. As it is night the restless " +
                        "flames from the fire casts strange shadows " +
                        "on the walls. ";
                break;

            default:
                desc += "It has been made of heavy logs and long poles " +
                        "tied together with strong ropes. Although slighly " +
                        "better than a tent this still appears to " +
                        "be a temporary home as it is very sparsely " +
                        "furnitured. Logs and rocks serve as chairs and " +
                        "tables while tightly packed dirt covered with " +
                        "smelly furs must be the beds. The only other " +
                        "noticable feature is the large fire burning " +
                        "in the middle of the room making the air very " +
                        "difficult to breathe. ";
        }
    }
    desc += gLong_desc;

    return desc + "\n";  
}

public void create_toron_room()
{
}

nomask public void 
create_krynn_room()
{    
    set_long(long_desc);
    
    create_toron_room();
}

public void reset_toron_room()
{
}

nomask public void
reset_krynn_room()
{
    reset_toron_room();
}
