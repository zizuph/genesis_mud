
/* 
   Standard moorland in the mid-western regions of Calia. 
   Template based on std_tunnel.c in Gondor.

   Coded by Maniac 1/3/95
   Modified 27/4/95.
   18/3/96   herbs added from Krynn            Maniac
   20/6/16   adjusted herb rates               Jaacar
*/

#pragma save_binary

#define KRYNN_HERBS "/d/Krynn/common/herbs/"
#define KALAD_HERBS "/d/Kalad/common/herbs/"

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/herbsearch.h" 

string 
*random_desc_add 
      = ({"The wind whistles eerily as it blows across the landscape.",
          "The sky above is a dreary, cloudy grey, the sunlight dim.",
          "A light cold rain is falling, making this area seem " +
          "even less inviting.",
          "A cold gust of wind chills you as you observe the " +
          "surroundings.",
          "You hear the howling of a wolf in the far distance." });


void
reset_herb_room()
{
    set_searched(0);
}


void
reset_room()
{
    reset_herb_room();
}


/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long, int type, int sub_type)
{
    string s, l, l2;

    if (!extra_long) { extra_long = ""; }
    if (!type) type = 0;
    if (!sub_type) sub_type = 0;

    switch (type) { 
       case 0: /* road room */ 
               s = "Road through Calian west moorland";
               l = "You are on a cobbled road through bleak " +
                    "moorland in the mid-western regions of " + 
                    "Calia.";
               l2 = "";
               add_item(({"road", "cobbled road"}), 
                 "A simple road through the surrounding moorland, " +
                 "its surface made of smallish grey stones that are " +
                 "closely cobbled together. It might create a " +
                 "slightly bumpy ride for carriages.\n"); 
               break;
      case 1: /* stone room */
              s = "An obelisk in Calian west moorland";
              l = "You have reached a mysterious place in the moorland. " +
                "Here a tall obelisk, some ten feet high, " +
                "stands upright, at the centre of a level circle " +
                "of ground on which the grass does not grow, a strange " + 
                "contrast with the surrounding moorland.";
              l2 = "";
              add_item(({"stone", "obelisk", "tall obelisk"}),
                "This four-sided stone column, standing some ten feet " +
                "high, tapers to a pyramid at the top. The stone that the " +
                "column is made of is a deep grey colour, and has a smooth " +
                "surface. " +
                "There is an impression in the stone about four feet " +
                "up from the base.\n");
              add_item(({"impression"}), "The impression in the stone " +
                "seems to be large and roughly hand-shaped.\n");
              add_item(({"circle", "level circle", "circle of ground", 
                         "level circle of ground"}), 
                         "The circle is very precise, so " +
                         "precise that you get the impression that " +
                         "there is some kind of magic involved. No " +
                         "grass grows on it at all.\n");
              break;
      default: /* regular moorland room */
              s = "Calian west moorland"; 
              l = "You are off the road, on open moorland in the " +
                  "mid-western regions of Calia.";
              if (!sub_type)
                  l2 = "The faded green lands " +
                   "stretch into the distance, short pale grass forming a " +
                   "blanket over a landscape that dips gently into " +
                   "shallow hollows and rises gradually into small " +
                   "hillocks, crudely adorned with the red or rusty " +
                   "coloured heathers.";
              else
                  l2 = "The faded green lands stretch out into the distance " +
                       "to the north, but you are now near the beginning " +
                       "of the northwestern foothills of Mount Kyrus."; 
              /* Herbs may go in the ordinary moorland rooms. */ 
              set_search_places(({"here", "grass", "heather"}));  
              add_prop(OBJ_I_SEARCH_TIME, 2); 
              add_prop(OBJ_S_SEARCH_FUN, "herb_search");
                if (random(100) > 60) add_herb_file(KRYNN_HERBS+"cladina");
                if (random(100) > 50) add_herb_file(KRYNN_HERBS+"cranberry");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"horsetail");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"bkd_sedge");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"blk_currant");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"raspberry");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"crocus");
                if (random(100) > 60) add_herb_file(KRYNN_HERBS+"fireweed");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"sm_camas");
                if (random(100) > 50) add_herb_file(KRYNN_HERBS+"chicory");
                if (random(100) > 50) add_herb_file(KRYNN_HERBS+"grey_willow");
                if (random(100) > 20) add_herb_file(KRYNN_HERBS+"saskatoon");
                if (random(100) > 60) add_herb_file(KALAD_HERBS+"kuko");
                if (random(100) > 60) add_herb_file(KALAD_HERBS+"lore");
                if (random(100) > 60) add_herb_file(KALAD_HERBS+"blade");
                if (random(100) > 60) add_herb_file(KALAD_HERBS+"mandrake");
                if (random(100) > 60) add_herb_file(KALAD_HERBS+"glowshroom");
                if (random(100) > 20) add_herb_file(KALAD_HERBS+"bloodweed");
                if (random(100) > 20) add_herb_file(KALAD_HERBS+"drudgeworth");
                if (random(100) > 20) add_herb_file(KALAD_HERBS+"nightshade");
                if (random(100) > 20) add_herb_file(KALAD_HERBS+"mindleech");
                if (random(100) > 60) add_herb_file(KALAD_HERBS+"flameroot");
              reset_herb_room();
              break;
    }

    set_short(s);
    set_long(l + " " + l2 + ((l2 == "") ? "" : " ") + 
             ((sub_type == 0) ? "" : ("To the southeast you notice that " +
             "the terrain is markedly more hilly. ")) +
             random_desc_add[random(sizeof(random_desc_add))] + " " +
             extra_long); 

    add_item(({"grass", "short grass", "short pale grass", "pale grass"}), 
        "The grass is short and pale, it appears that the soil here is " +
        "not suitable for grass to grow long.\n");
    add_item(({"heather", "heathers", "red heathers", 
               "rusty coloured heathers"}),
       "The heather is the most prominent form of plant life growing " +
       "on the moors, red or rusty coloured shrubs with small bell " +
       "shaped flowers.\n");
    add_item(({"moor", "moorland", "land", "lands"}), 
       "The open uncultivated moorland stretches out over quite a wide " +
       "area in the mid-west of Calia.\n");
    add_item(({"wind"}), "How can you see wind?\n"); 
    add_prop(ROOM_I_INSIDE, 0);

}
