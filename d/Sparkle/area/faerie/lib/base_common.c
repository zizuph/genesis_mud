/*
 * This file contains all the common items for Faerie
 * like houses, buildings, gardens, roads, etc..
 * This way these routines aren't spread over several files, 
 * and makes maintaining these routines much easier.
 *
 * Thanks to Arandir for the time functions. He coded them for the 
 * Dragon Order guild.
 * By Finwe, August 2004
 *
 * Fixed (rudely, patch prettier later!) the change in login sequence
 * wherefrom random_noise was inherited.
 * TAPAKAH, February 18, 2006
 *
 * Corrected typo with time seen when indoors
 * Finwe, January 11, 2009
 * 
 * Forced always day to agree with Donut model and rest of Sparkle
 * Lavellan, 12 September 2010   
 */
 
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";

inherit S_LIB_CLOCK;
inherit HERB_SEARCH;
inherit "/d/Genesis/lib/random_noise";

#define MAX_NPCS    4

static object *npc = allocate(MAX_NPCS);

/*******************************************************************\
| Support for time.                                                 |
\*******************************************************************/

/*
 * Function name : s_action_time
 * Description   : Executed when somebody issues the time action.
 *
 */

int s_action_time ()
{
//  if ((query_prop (ROOM_I_INSIDE)) || s_is_night ())
    if ((query_prop (ROOM_I_INSIDE)))
  {
    write ("It's " +
           LANG_ADDART (s_get_stime_season ()) + " " +
           s_get_stime_period () + ", " +
           "but since you're indoors, you can't tell what time it is exactly.\n");
  }
  else
  {
    write ("It's " +
           s_get_stime_hour_of_period () + " o'clock on " +
           LANG_ADDART (s_get_stime_season ()) + " " +
           s_get_stime_period () + ".\n");
  }
  return (TRUE);
}



string s_desc_sky_outside_sky ()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
/*    if (s_is_winter ())
      sDesc = "The night sky is very dark, with heavy winter " +
              "clouds obscuring whatever stars would be visible.";
    else
      sDesc = "The night sky is dark, but as you gaze up, you " +
              "notice a few stars flickering at the edge of " +
              "your vision.";
*/
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "The night sky is a deep blue, with threads of white clouds " +
            "scattered across it. Stars twinkle between the clouds. ";
        break;
      case "summer":
        sDesc = "The night sky is a deep blue. Clouds move slowly across it. ";
        break;
      case "autumn":
        sDesc = "The night sky is a grey blue, with clouds growing " +
                "gradually every day. ";
        break;
      case "winter":
        sDesc = "The night sky is grey. Heavy winter clouds " +
                "hang low and obscure many stars. ";
        break;
    }

  }
  else // daytime
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "The day sky is a bright blue, with the remnants of " +
                "winter clouds still visible. ";
        break;
      case "summer":
        sDesc = "The day sky is a marvelously bright blue. Only a few bits " +
                "and threads of clouds remain, decorating the blue " +
                "background with often intriguing patterns. ";
        break;
      case "autumn":
        sDesc = "The day sky is a grey blue, with clouds growing " +
                "gradually every day. ";
        break;
      case "winter":
        sDesc = "The day sky is grey, with heavy winter clouds " +
                "hanging low and obscuring the weak rays of " +
                "the winter sun. ";
        break;
    }
  }

//  sDesc += "\n";
  return (sDesc);
}

string s_desc_sky_outside_sun ()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    sDesc = "It is dark, and the sunlight is gone for now.";
  }
  else
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "The sun still travels low on the horizon, but " +
                "even the weakest of its rays are a welcome " +
                "change after the cold winter.";
        break;
      case "summer":
        sDesc = "The sun is at its full strength, a blazing ball " +
                "of fire impossible to look at for long. Still, " +
                "its rays do not provide much warmth.";
        break;
      case "autumn":
        sDesc = "The sun is getting obscured by clouds more often " +
                "every day, a sure sign of coming winter.";
        break;
      case "winter":
        sDesc = "The sun is barely visible behind the heavy " +
                "cover of the clouds.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}

string s_desc_sky_outside_moon ()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    if (s_is_winter ())
    {
      sDesc = "The clouds are so heavy the moon is not visible at all.";
    }
    else
    {
      sDesc = "The moon covers everything with a surreal silvery light.";
    }
  }
  else
  {
    sDesc = "It takes a better sight than yours to see the moon at daytime.";
  }

  sDesc += "\n";
  return (sDesc);
}

string s_desc_sky_outside_clouds ()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    sDesc = "They're too far away to see in the dark.";
  }
  else
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "They are layered and cover most of the sky. The clouds look " +
            "like a blanket of cotton.";
        break;
      case "summer":
        sDesc = "They are large and puffy and look like large balls of " +
            "cotton. The clouds are tall and spread across the sky.";
        break;
      case "autumn":
        sDesc = "They look like small balls of cotton stacked on top of " +
            "each. The clouds are spread like a blanket across the sky.";
        break;
      case "winter":
        sDesc = "They are thin and wispy. The clouds are spread across the sky.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}

s_item_sky_outside ()
{
  add_item (({ "sky" }),
//    &s_desc_sky_outside_sky () + "\n");
    "@@s_desc_sky_outside_sky@@\n");
  add_item (({ "sun", "sun rays", "sunrays", "sun beams", "sunbeams", 
        "sun light", "sunlight" }),
    &s_desc_sky_outside_sun ());
  add_item (({ "moon", "moon rays", "moonrays", "moon beams", "moonbeams", 
        "moon light", "moonlight" }),
    &s_desc_sky_outside_moon ());
  add_item (({ "cloud", "clouds" }),
    &s_desc_sky_outside_clouds ());
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();

    add_action (s_action_time, "time");
    init_random_noise();
}

/* Add herbing abilities
 */
void 
add_herbs()
{
    int seed;

    seed = file_size(file_name(calling_object()) + ".c");
    add_std_herbs(0, seed);
}


/****************************************************************
 * Sub functions called by other functions
 ****************************************************************/

/*
 * Function name : set_add_pastures
 * Arguments     : str: none
 * Description   : adds pasture descr to country rooms
 */
void set_add_pastures()
{
    add_item(({"pastures"}),
        "They are large, fenced in plots of land that have grass growing " +
        "in them. Animals, like horses or cows, probably roam in the pastures, " +
        "eating the grass and getting fat.\n");
   
}

/*
 * Function name : set_add_fields
 * Arguments     : str: none
 * Description   : adds field descr to countryside
 */
void set_add_fields()
{
    add_item(({"fields"}),
        "The fields are square shaped and surrounded by fences. Some are " +
        "plowed with crops growing in them. Others lie fallow.\n");
    add_item(({"fallow fields"}),
        "The fallow fields are unkempt and unplowed. Farmers leave " +
        "them this way for a season. They are also surrounded by fences.\n");
}


/*
 * Function name : set_add_fences
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_fences()
{
    add_item(({"fences", "split rail fence", "fence", "split rail fences"}),
        "The fence is made from logs that have been split into several " +
        "long rails. The rails are attached to fence posts set into " +
        "the ground at intervals, and are weathered and rough looking.\n");
    add_item(({"fence post", "fence posts", "posts", "post"}),
        "The fence posts are sunk deep into the ground, " +
        "offering a secure foundation for the fence. The rails " +
        "are securely attached to the posts.\n");
    add_item(({"rails", "split rails"}),
        "They are made from trees that have been splint into quarters. " +
        "The rails are then secured to the fence post.\n");
}

/*
 * Function name : set_add_haystacks
 * Arguments     : str: none
 * Description   : adds descr for haystacks and oatstacks
 */
void set_add_haystacks()
{
    add_item(({"haystacks"}),
        "The haystacks are tall, golden piles of hay that have been " +
        "stacked in the past couple of days. The are scattered about " +
        "some of the fields or lined up in neat rows. The haystacks " +
        "are wide at the base and gradually come to a rounded point " +
        "at the top.\n");
    add_item(({"oatstacks"}),
        "The oatstacks are tall, narrow columns of bundled oats. They " +
        "are stacked around poles that stick out of their centers, and " +
        "left to dry. These columns are arranged in straight lines in " +
        "some of the fields, drying and waiting to be taken down and " +
        "fed to farm animals.\n");
}




/*
 * Function name : set_add_farms
 * Arguments     : str: none
 * Description   : adds standard farm items to country road.
 */
void set_add_farms()
{
    add_item(({"farms", "homesteads"}),
        "Large buildings stand in the distance in the center of the " +
        "farms. They are surrounded by fields and pastures. They are a " +
        "ways off, so it is difficult to make out much detail about them.\n");
    add_item(({"buildings", "large buildings"}),
        "From this distance, it is hard to make out what they are, but " +
        "they are all sizes and shapes.\n");
    set_add_pastures();
    set_add_fields();
    set_add_fences();


    
}



/*
 * Function name : set_add_mt_descr
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_mt_descr()
{
    add_item(({"peaks", "mountain peaks", "mountain tops"}),
        "They are jagged and broken, reaching up to the sky. The " +
        "taller peaks are covered with snow, and some even hidden " +
        "by clouds. The peaks are rough looking and look bare of any growth.\n");
    add_item(({"snow"}),
        "It is pure white, covering the tallest peaks of the mountains.\n");
}


/*
 * Function name : set_add_gardens
 * Arguments     : str: none
 * Description   : adds garden descr for town
 */
void set_add_gardens()
{
    add_item(({"gardens", "flower gardens"}),
        "The gardens surround the buildings and are full of plants and " +
        "flowers. The flowers are bright and in a multitude of colors " +
        "and sizes. The plants are a healthy green and look well " +
        "tended. Beneath the plants is a layer of shredded bark.\n");

    add_item(({"flowers", "bright flowers"}),
        "The flowers are bright and come in a multitude of shapes and " +
        "sizes. Some look like shooting stars, others appear to be in " +
        "the shape of upturned suns, and more look like fallen snow on " +
        "mountains. Some flowers are low to the ground while others are " +
        "on tall spikes. Their colors are as varied as the rainbow " +
        "and complement each other wonderfully.\n");

    add_item(({"plants"}),
        "The plants in the gardens are healthy looking and are a variety " +
        "of shapes and sizes. Some are flowers while others have flowers " +
        "on them. Some of the plants have fruits and berries on them. The " +
        "leaves of the plants are different shapes and sizes. Some are " +
        "large, while others are as small as a thumbnail. The leaves are " +
        "rounded, tear-shaped, serrated, or feathery in shape.\n");

    add_item(({"berries", "fruits"}),
        "Growing on some of the plants are various fruits and berries. " +
        "Most of them are small and white, red, blue, or green. They hang " +
        "on the plants like bright jewels.\n");

    add_item(({"shredded bark", "bark", "beauty bark"}),
        "The shredded bark is spread around the garden beneath the " +
        "plants and flowers. It acts as a covering hiding the ground and " +
        "acting as a background for the plants. It is free of any plant " +
        "debris.\n");
}



/*
 * Function name : set_add_circ_bldg
 * Arguments     : str: none
 * Description   : adds outside descr for bulletin board room
 */
void set_add_circ_bldg()
{
    add_item(({"round building", "circular building"}),
        "This round building sits at the south end of the Training Academy. " +
        "It is open on all sides with lattice walls extending halfway " +
        "up the building. The domed roof rests on pillars that connect " +
        "it with the walls.\n");

    add_item(({"walls"}),
        "They are made of wooden lattice. The walls extend halfway up " +
        "the building and connect to the roof with small pillars. " +
        "Twining flowers grow up the lattice walls.\n");

    add_item(({"wooden lattice", "lattice"}),
        "It is made of many wooden slats which are in a crisscross " +
        "pattern. The lattice is in good condition and covered with many " +
        "twining flowers.\n");

    add_item(({"twining flowers"}),
        "They grow up and over the lattice walls, creating a wall of " +
        "green with dots of blue. The flowers are large, blue trumpets " +
        "connected to delicate stems. Many of the flowers are open, " +
        "pointing in all directions.\n");

    add_item(({"domed roof", "dome"}),
        "The domed roof rises above the circular building. It rests " +
        "on top of several pillars that are connected to the building. " +
        "The roof is smooth and white without any decoration.\n");
}


/****************************************************************
 * End of sub-functions
 ****************************************************************/


/*
 * Function name : set_add_all_rooms
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_all_rooms()
{

}



/*
 * Function name : set_add_all_track
 * Arguments     : str: none
 * Description   : adds standard items to all track rooms.
 */
void set_add_all_track()
{
    add_item(({"road", "track", "path", "narrow track",
            "narrow road", "narrow path"}),
        "The track is made of packed dirt. Deep ruts in the " +
        "ground run down the center of it. They are from " +
        "countless wagons that have travelled this way. Sparse grasses " +
        "grow down the center of the road.\n");
    add_item(({"wagon ruts", "ruts"}),
        "The wagon ruts run down the center of the track. They are deep " +
        "grooves made by wagon wheels that have used the road countless " +
        "times.\n");
    add_item(({"grasses", "sparse grasses"}),
        "It grows alongside and down the center of the track " +
        "in patches. The grass is short and light green.\n");
}



/*
 * Function name : set_add_mt_town
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_mt_town()
{
    add_item(({"mountains", "mountain"}),
        "The mountains are in the distance, tall peaks topped with snow. " +
        "Some of the peaks are hidden by clouds that hide the taller " +
        "mountain tops.\n");
    set_add_mt_descr();
}


/*
 * Function name : set_mt_descr
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_mt_descr()
{
    add_item(({"mountain peaks", "peaks", "mountain tops", 
            "mountain top", "tops"}),
        "They rise in the distance. They are dark colored and jagged. " +
        "Some are snow capped while the taller ones are hidden in the " +
        "clouds.\n");
    add_item(({"clouds"}),
        "The clouds are light and fluffy looking. They move about the " +
        "sky in random patterns and shapes. Some hover about the tops " +
        "of the tallest mountain tops.\n");
}


/*
 * Function name : set_add_valley
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_valley()
{
    add_item(({"valley"}),
        "It is a large, bowl shaped area in the mountains. There are " +
        "trees along the edges of the valley, with a large town in " +
        "the center.\n");
}

/*
 * Function name : set_add_ceiling
 * Arguments     : str: additional description
 * Description   : adds standard items to indoor rooms.
 */
void set_add_ceiling(string str)
{
    add_item(({"ceiling"}),
        "The ceiling is flat with large wood beams running the width " +
        "of the room. Resting on top of the beams are large wooden " +
        "planks. " + str + "\n");
    add_item(({"wood beams", "beams", "large wood beams"}),
        "The large wood beams are squared and thick. They are polished " +
        "and run the width of the room. Laid across the beams are " +
        "large wooden planks\n");
    add_item(({"planks", "wooden planks", "large wooden planks"}),
        "The large wooden planks make up the ceiling. They are smooth " +
        "and polished to a deep colour. They are laid on top of the " +
        "wooden beams.\n");
}

/*
 * Function name : set_add_dark_stone
 * Arguments     : str: additional description
 * Description   : adds standard items to indoor rooms.
 */
void set_add_dark_stone()
{
    add_item(({"dark stone", "stone"}),
        "The dark stone is flat and irregular shaped. It is used in " +
        "the walls and floors. In the floor, looks worn in places. " +
        "Some of the stones have darker veins which streak through them.\n");
}

/*
 * Function name : set_add_stone_walls
 * Arguments     : str: additional description
 * Description   : adds standard items to indoor rooms.
 */
void set_add_stone_walls(string str)
{
    add_item(({"walls", "stone walls"}),
        "The walls are made up of dark stone. They are smooth to the " +
        "touch and look strong. " + str + "\n");
}

/*
 * Function name : set_add_stone_floor
 * Arguments     : str: additional description
 * Description   : adds standard items to indoor rooms.
 */
void set_add_stone_floor(string str)
{
    add_item(({"floor", "stone floor"}),
        "The floor is constructed of dark stone. It is polished and " +
        "gleams in the light. Some of the stones are worn from " +
        "constant traffic. " + str + ".\n");
}

/*
 * Function name : set_add_academy
 * Arguments     : str: none
 * Description   : adds decriptions to training academy
 */
void set_add_academy()
{
    add_item(({"academy", "training academy"}),
        "The Training Academy is a local place where townsfolk come to " +
        "learn to protect themselves and learn about the outside world. The " +
        "Academy is a large group of buildings surrounded by gardens. " +
        "In the center are three large buildings, a circular building, " +
        "a square building, and a rectangular building.\n");

    set_add_circ_bldg();
//    set_add_square_bldg();
//    set_add_rec_bldg();
    set_add_gardens();

}

/*
 * Function name : set_add_bldg
 * Arguments     : str: none
 * Description   : adds 
 */
void set_add_bldg()
{
}


/*
 * Function name : set_add_houses
 * Arguments     : str: none
 * Description   : adds 
 */
void set_add_houses()
{
    add_item("houses",
        "The houses are sturdy buildings, made of wood and stone. " +
        "They are mostly one story and are set back from the road. " +
        "Gardens surround the houses, forming living walls of privacy " +
        "for the homeowners.\n");
    add_item(({"roofs", "roof"}),
        "The roofs of the buildings are mostly peaked and covered " +
        "with thatching.\n");
    add_item("eaves",
        "The eaves extend from the roof by about an arm's length, " +
        "providing protection to anyone standing beneath them.\n");
    add_item(({"thatching", "thatch"}),
        "It is made of large bundles of rushes and used as roofing " +
        "material. The thatchings are in good repair and are a tan " +
        "color.\n"); 
    add_item(({"rushes", "bundles of rushes"}),
        "These are dried stems of plants. They are bundled together " +
        "into large groups and used as thatching for the roofs in " +
        "the town.\n");
    add_item(({"chimney", "chimnies"}),
        "The chimnies are made from stone and mortar. They " +
        "run up the side of some buildings. They are very wide " +
        "at the base and then become narrow about two thirds of " +
        "the way up the buildings.\n");
    set_add_gardens();
}

/*
 * Function name : set_add_square_bldg
 * Arguments     : str: none
 * Description   : adds outside descr for library
 */
void set_add_square_bldg()
{
    add_item(({"square building", "library"}),
        "The building is one of the largest in the Academy. It's square shaped " +
        "and surrounded by gardens.\n");
    set_add_gardens();
}

/*
 * Function name : set_add_country
 * Arguments     : str: none
 * Description   : adds countryside descrs
 */
void set_add_country()
{
    add_item(({"country", "countryside"}),
        "The countryside is a flat, green carpet of grass, punctuated " +
        "by plowed fields, pastures, and farms and homesteads. Sprinkled " +
        "across the countryside are small groves of trees and wildflowers " +
        "dotting the grass. Fences mark the edges of the fields and " +
        "pastures, and some even run along both sides of the road.\n");  
    add_item(({"path", "track", "road"}),
        "This is a dusty road that runs through the countryside. " +
        "Sparse grasses grow on the track, and flowers grow alongside " +
        "the track. Deep wagon ruts have been cut into the road.\n");
    add_item(({"ruts", "wagon ruts"}),
        "The wagon ruts are deep, narrow trenches that have been carved " + 
        "by countless wagons that travel this road. They run down the " +
        "middle of the road.\n");
    add_item(({"trees"}),
        "Tall, ancient trees grow in small groves away from the road. " +
        "It is hard to see exactly what they are, but the trees look " +
        "healthy with long branches and thick trunks.\n");
    add_item(({"sparse grasses", "grasses"}),
        "The sparse grass grows in clumps down the middle of the track. " +
        "It is gray and trampled, lying flat on the dirt.\n");
    add_item(({"flowers", "wildflowers"}),
        "They are bright wildflowers, growing alongside the track " +
        "and in the countryside. They are all sizes and colors.\n");
    add_item(({"green grass"}),
        "It is a velvet layer of green that covers the land and countryside. " +
        "It grows right up to the edge of the road, which meanders " +
        "through the countryside. The grass is dotted with wildflowers " +
        "of all colors, sizes, and shapes.\n");
    set_add_mt_descr();

}

/*
 * Function name : Reset_shire_room
 * Description   : If you want to reset a room in the Shire use this function.
 */
void
reset_faerie_room() {}

/*
 * Function name : Reset_room
 * Description   : Takes care of reseting certain things used in the Shire,
 *                 such as herbs and other searches
 * TODO          : Make this function nomask when I know that all the rooms
 *                 that inherit this file don't use reset_room.

 */
void
reset_room()
{
    if (sizeof(query_herb_files()))
	this_object()->reset_faerie_herbs();
    reset_faerie_room();
}

/*
 * Function name : tree_descr
 * Description   : adds descr of seasonal orchard
 */

string tree_descr()
{
    switch (s_get_stime_season ())
    {
      case "spring":
        return"The trees are full of blossoms with birds singing in " +
            "their branches and bees dancing from flower to flower. Soon, " +
            "the branches will be laden with fruit ready for picking. ";
        break;
      case "summer":
        return "The trees are heavy with fruit, ready to be picked. ";
        break;
      case "autumn":
        return "The fruit trees are picked clean. It has been a bountiful " +
            "season and the only fruit remaining will be picked by the birds. ";
        break;
      case "winter":
        return "The fruit trees stand bare, resting during the season. " +
            "During the spring, they will be laden with many blossoms. ";
        break;
    }
} 

string flower_descr()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    sDesc = "They're too far away to see in the dark.";
  }
  else
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "";
        break;
      default:
        sDesc = "They have faded away, and won't return until next year.";
        break;        
    }
  }

  sDesc += "\n";
  return (sDesc);
}


string bees_descr()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    sDesc = "It is night time, and they are not visible now.";
  }
  else
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "They are large, and hum loudly as they visit each " +
            "blossom in the orchard.";
        break;
      case "summer":
        sDesc = "They are large and buzz loudly in the orchard. They " +
            "fly from blossom to blossom in the orchard. ";
        break;
      default:
        sDesc = "They seem to have all gone away. They will appear next season.";
        break;
    }
  }
  sDesc += "\n";
  return (sDesc);

}

string bird_descr()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    sDesc = "They're too far away to see in the dark.";
  }
  else
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "They are large and multi-colored, and fly around the " +
            "fruit trees in the orchard.";
        break;
      case "summer":
        sDesc = "They hide in the branches of the fruit tree, and sing, " +
            "and occasionally fry from one tree to the next.";
        break;
      case "autumn":
        sDesc = "There are only a few of them in the fruit trees. A few " +
            "songs can be heard from them.";
        break;
      case "winter":
        sDesc = "You do not see or hear any birds from the orchard.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}


string fruit_descr()
{
  string sDesc;

//  if (s_is_night ())
  if (0)
  {
    sDesc = "It is too dark to see them.";
  }
  else
  {
    switch (s_get_stime_season ())
    {
      case "spring":
        sDesc = "It is growing on the fruit trees. Remnants of blossoms " +
            "hang from the fruits, but they should be ripe soon.";
        break;
      case "summer":
        sDesc = "It is plump and ready to pick";
        break;
      case "autumn":
        sDesc = "There is very little left hanging from the trees. What " +
            "is left looks wrinkled and fit only for birds and other " +
            "animals to have.";
        break;
      case "winter":
        sDesc = "There is no fruit on the fruit trees.";
        break;
    }
  }

  sDesc += "\n";
  return (sDesc);
}


/*
 * Function name : set_add_orchard
 * Description   : adds descr of orchard
 */
void set_add_orchard()
{
    add_item(({"orchard", "fruit trees"}),
        "The trees are tall and carefully pruned. They grow in straight " +
        "rows. " + tree_descr() + "\n");
    add_item(({"row", "rows", "row of trees", "row of fruit trees"}),
        "They are fruit trees planted in straight lines in the orchard. " +
        "The rows are spaced apart properly to ensure the trees are " +
        "healthy.\n");
    add_item(({"blossoms", "blossom"}),
        &flower_descr());
    add_item(({"bees", "honeybees", "honeybee", "bumblebees", "bumblebee"}),
        &bees_descr());
    add_item(({"birds", "bird"}),
        &bird_descr());
    add_item(({"fruit"}),
        &fruit_descr());
    

    
}

/*
 * Function name : set_add_plaza
 * Description   : adds descr of plaza
 */
void set_add_plaza()
{
    add_item(({"square", "plaza"}),
        "This is an open area in the town. It is semi-circle shaped " +
        "and lined with flagstones.\n");
}

/*
 * Function name : set_add_arch
 * Arguments     : str: additional appended to end of arch descr
 * Description   : adds standard arch descriptions to rooms
 */

void set_add_arch(string str)
{

    add_item(({"arch", "arched opening", "large arch", "archway", "opening"}),
        "It is a tall opening in a wall. It is crowned with a slightly " +
        "curved lintel. "+str+"\n");
    add_item(({"crown", "top of arch", "top of the arch"}),
        "The crown, which is the top of the arch, " +
        "is one long piece of grey stone. It extends " +
        "an arm's length on each side of the arch. Both the top " +
        "and the inside of the stone are curved upwards " +
        "slightly, giving the arch a graceful look and feel.\n");
    add_item(({"pillar", "pillars"}),
        "The pillars are made of stone, smooth to the " +
        "touch and squared. The pillars are about twice the " +
        "height of an elf and support a graceful lintel.\n");
    add_item(({"lintel"}),
        "This is a horizontal piece of stone. It stretches across the " +
        "two pillars on either side of the arch.\n");
}

/*
 * Function name : log_quest
 * Description   : logs quest
 */
nomask varargs int
log_quest(object player, string long_name, int quest_bit, int exp)
{
    string log_str;

    log_str = ctime(time()) + " "+ capitalize(player->query_real_name()) +
    " (" + player->query_average_stat() + ") completed the "+
    long_name +".\n";

    log_file("quest_log", log_str);
    return 1;
    
}

/* Create orc npcs for orc camp */
void create_orcs(int orc, int wander)
{
    int index, npc_count;
    string orc_name;

    setuid(); 
    seteuid(getuid());
    
    npc_count = random(MAX_NPCS);

    if(npc_count ==0)
        npc_count = 3;

    switch(orc)
    {
        case 0: orc_name = NPC_DIR + "orc_thrall"; break;
        case 1: orc_name = NPC_DIR + "orc_scout"; break;
        case 2: orc_name = NPC_DIR + "orc_soldier"; break;
        case 3: orc_name = NPC_DIR + "orc_guard"; break;
        case 4: orc_name = NPC_DIR + "orc_officer"; break;
    }
    
    for(index = 0; index < npc_count; index++)
    {
        if (!objectp(npc[index]))
        {
            npc[index] = clone_object(orc_name);
            if(wander == 1)
            {
                npc[index]->set_restrain_path(OC_DIR);
                npc[index]->set_random_move(3);
            }
            npc[index]->move(TO);
        }
    }
}
