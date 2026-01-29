#include "../stddefs.h"
#include <stdproperties.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "fir_forest.h"

#pragma save_binary

inherit ELFROOM;

#define WEST    ROOMDIR + "trade_road_1"
#define TP      this_player()
#define PORTAL_CLOSED 1 // 1 = open, 0 = closed

/*
#define MAGESTONE "/d/Genesis/obj/wizquest/mage_stone"
*/

#define SHORT  "In a small clearing in the forest"

#define NAT_LONG \
  "Here is a small clearing in the forest. The vegetation is low and " + \
  "yellowish dry, and here and there the limestone bedrock is visible " +\
  "between bushes and tufts of grass. The air is warm, and a smell of " +\
  "dry grass lingers in the air. In the center of the clearing is a "+\
  "circle of roughly carved stones.\n"
#define FOR_LONG \
  "You are standing in a small clearing in the dark fir forest. There are " +\
  "low bushes and some grass here.\n"

#define BUSH_ITEM  ({"bush", "bushes"})
#define BUSH_FDESC "Oh, its just some kind of low bushes.\n"
#define BUSH_NDESC \
  "Whenever the fall comes, these bushes will be filled with sloes.\n"

#define ROCK_ITEM ({"rock", "bedrock", "bed-rock", "ground", "limestone"})
#define ROCK_DESC \
  "The bedrock that is visible in patches has the characteristic gray, " + \
  "brittle, pockmarked surface that limestone exposed to sun and rain " + \
  "gets, but the yellowish white of the untouched stone still shines in " + \
  "scratches and newly eroded places. Cracks and holes in the rock " + \
  "provide a footing for the bushes and grass that grows here.\n" 

#define GRASS_ITEM ({"grass", "tuft", "tufts"})
#define GRASS_DESC \
  "The grass is short, dry, and covered with limestone dust, giving it " +\
  "a pale greyish-yellow colour. Many of the straws carry small seeds. " +\
  "Inside the circle of stones is a area of green grass with sparkles " +\
  "of light dancing across the top.\n"
  
create_room()
{
  set_short(SHORT);
  set_long(N_KNOW(WRAP(NAT_LONG), WRAP(FOR_LONG)));
  
  FIR_FOREST_STD_ITEMS;
  add_item( BUSH_ITEM, N_KNOW(WRAP(BUSH_NDESC), WRAP(BUSH_FDESC)));
  add_item( ROCK_ITEM, WRAP(ROCK_DESC));
  add_item(GRASS_ITEM, WRAP(GRASS_DESC));
    add_item(({"portal", "huge portal", "circle", "circle of stones"}),
        "The circle of stones is set in the center of the clearing. " +
        "They look like they are growing out of the ground. Tufts " +
        "of grass grow at the base of each stone. Inside the center "+
        "of the circle of stones, and contrasting with the rest of " +
        "the clearing, is lush, green grass.\n");
   add_item(({"stones", "roughly carved stones", "carved stones"}),
        "The roughly carved stones are tall, and weather-worn. " +
        "They seem to grow out of the ground and surround a " +
        "circle of lush, green grass.\n");
   add_item(({"lush green grass", "lush grass", "green grass"}),
        "The grass is ankle deep and very lush looking. It contrasts " +
        "with the rest of the clearing. An unseen breeze blows " +
        "across the grass, scattering minute sparkles of dancing light.\n");
    add_item(({"sparkles of light", "minute sparkles of light", "sparkles"}),
        "The sparkles dance randomly across the top of the grass, " +
        "weaving inside and out of each other, in mesmerizing " +
        "patterns. Occasionally they rise and form a faint outline " +
        "of an archway, then fall to the ground in a shower of " +
        "light and dance about.\n");
    add_item(({"dust", "limestone dust"}),
        "The grey dust covers everything except for the green, " +
        "lush grass.\n");
    add_item(({"seeds"}),
        "The grass seeds are brown and dried looking. Probably " +
        "not good for much.\n");
    add_item(({"straws"}),
        "These are golden yellow and dried grass stalks. Seeds " +
        "still hang from them.\n");
    add_item(({"grass stalks", "stalks", "dried grass stalks"}),
        "They are golden yellow with some seeds still hanging " +
        "from them.\n");
    add_item(({"center", "center of circle of stones", 
            "center of the circle of stones"}),
        "In the center of the circle of stones is lush, green " +
        "grass. Dancing across the surface of the green grass " +
        "are sparkles of light.\n");
    add_item(({"cracks", "holes", "cracks and holes", 
            "holes and cracks"}),
        "The cracks and holes in the limestone rock are from the " +
        "weather. They provide a footing for bushes and grassses " +
        "that grow here.\n");
    add_item(({"vegetation"}),
        "Bushes and grasses grow here. Oddly enough, inside the " +
        "circle of stones is a circle of lush, green grass, " +
        "contrasting with the area.\n");
    add_item(({"clearing", "small clearing"}),
        "It is small, inside a forest, low vegetation grows " +
        "everywhere. In the center of the clearing is a circle of " +
        "stones.\n");
    
   add_cmd_item( ({"circle",
                   "circle of stones", 
                   "portal", 
                   "archway", 
                   "through portal", 
                   "sparkles", 
                   "light"}), 
                   ({"enter", "go"}), "@@transport@@");


  add_exit(WEST, "west", 0);
  tie_to_map(CENTER_SQUARE, 186, 6, 554, 5);

/*
  stock();
*/
}

void
init()
{   
    ::init();
    add_action("transport", "enter");
    add_action("transport", "go");
}



/*
stock()
{
  object obj;
  if (!present("stone", this_object()) &&
      (obj = clone_object(MAGESTONE)) != 0)
    obj->move(this_object());
}
*/

string transport()
{

        write("You enter the circle of stones. The sparkles swirl up " +
        "and surround you. They blind you as they envelope you " +
        "completely.\n");
        say(QCTNAME(TP)+ " enters the circle of stones and disappears " +
        "in a swirl of sparkles.\n");
        TP->move_living("M", "/d/Shire/cypress/thalandrone/rooms/glen/glen",1);
        say(QCTNAME(TP) + " arrives in the circle of trees and steps out.\n");
        return "";
}
