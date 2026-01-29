/*
* The Rich Men's Club
*
* Coded by Conan Jan -95
*
*/

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>

#define PORTOB RICHCLUB + "portob"

mapping ports = ([ ]);
mapping players = ([ ]);
/*
* Portal to Solace in Krynn accepted by Rastlin   95-08-24
* Portal to Gelan in Calia accepted by Maniac     95-02-01
* Portal to Kabal in Kalad accepted by Antharanos 95-01-28
*/

string
plaque()
{
  return ".-------------------------. \n"+
         "|  North portal -> Gelan  |\n"+
         "|  South portal -> Kabal  |\n"+
         "| West portal  -> Ansalon |\n"+
         "`-------------------------' \n";
}

public void
create_room()
{
  set_short("Top floor of The Rich Men's Club");
  set_long(
    "You are on the top floor of the tower-like building where "+
    "the\nRich Men's Club has its quarters. The view from the "+
    "large\nwindow is incredible and the atmosphere in the room "+
    "makes\nyou relax. Three portals are placed in the north, "+
    "south and\nwest walls. A golden plaque is placed over the window. "+
    "An open\ndoor leads to a small room.\n"+
    "There are two obvious exits: east and down.\n"+
    "Three magnificent portals.\n");
  
  set_noshow_obvious(1);

  add_item("plaque", "There's some readable text on it...\n");
  add_cmd_item("plaque","read","@@plaque");
  add_item("window","Through the window you see the beautiful Isle of Gold.\n");
  add_item("stairs","They are made of stone and are leading down.\n");
  add_item(({"portal","portals"}),"These portals are links to the "+
    "outer world. You can enter them by typing 'enter north/south/west "+
    "portal.\n");
  
  add_exit(RICHCLUB+"richprivate2","down",0);
  add_exit(RICHCLUB+"richprivate4","east",0);
  
  INSIDE;

  restore_object(PORTOB);
}

void
init()
{
  ::init();

  add_action("portal","enter");
  add_action("portrait","hire");
}

int
portal(string str)
{
    NF("Enter what?\n");
    if (str=="north portal")
    {
        write("You feel a sudden heat and then you realize that "+
              "you have been teleported to a new location.\n");
        tell_room(PORTAL1,"A portal opens a few feet above the ground and "+
                  "out of it steps "+QTNAME(TP)+".\n");
        TP->move_living("through the northern portal",PORTAL1);

	ports["Gelan"] += 1;
	players[CQRLNAME(TP)] += 1;
	save_object(PORTOB);
        
        return 1;
    }
    else if (str=="south portal")
    {
        write("You feel a sudden heat and then you realize that "+
              "you have been teleported to a new location.\n");
        tell_room(PORTAL2,"A portal opens a few feet above the ground and "+
                  "out of it steps "+QTNAME(TP)+".\n");
        TP->move_living("through the southern portal",PORTAL2);

	ports["Kalad"] += 1;
	players[CQRLNAME(TP)] += 1;
	save_object(PORTOB);
        
        return 1;
    }
    else if (str=="west portal")
    {
        write("You feel a sudden heat and then you realize that "+
              "you have been teleported to a new location.\n");
        tell_room(PORTAL3,"A portal opens a few feet above the ground and "+
                  "out of it steps "+QTNAME(TP)+".\n");
        TP->move_living("through the western portal",PORTAL3);

	ports["Ansalon"] += 1;
	players[CQRLNAME(TP)] += 1;
	save_object(PORTOB);
        
        return 1;
    }

    if (str == "portal")
        NF("Enter which portal?\n");

    return 0;
}

int
portrait()
{
  write("Sorry, all artist are striking due to the, in their eyes, lousy "+
    "payment. The artists wants 2000 plats for a portrait and that is too "+
    "much in our opinion, what do you think?\n");
  return 1;
}















































