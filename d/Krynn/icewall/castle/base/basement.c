/************************************************/
/*    Basement of Icewall Castle */
/*              Coded by Steve*/
/************************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

int crevice, manhole;
string star, basedesc, str, manholedesc, crevicedesc;

create_icewall_room()
{
   set_short("Basement");
   set_long("@@base_desc");
   
   
   add_item(({"stair","stairs"}),
      "The flight of stairs lead up into the castle.\n"
      + "You should be able to make it up them if you are careful.\n");
   add_item("sink",
      "The sink is old and cracked and is half full with murky water.\n");
   add_item("tap",
      "The tap is dripping continously into the sink.\n");
   add_item(({"rack","wine rack"}),
      "The wine rack contains hundreds of bottles of vintage wine.\n");
   add_item(({"bottles","bottle","wine"}),
      "There are some very old bottles of wine here.\n");
   add_item("manhole","@@manhole_desc");
   add_item("crevice","@@crevice_desc");
   
   
   
   add_exit(ICE_CAST1_R + "top_stairs.c", "up");
   add_exit(CAVE + "cavern1.c", "down", "@@check_manhole");
   set_noshow_obvious(1);
   add_exit(BASE+"prisons","north",0);
   
   crevice = 0;/* 0 = empty, 1 = filled */
   manhole = 0;/* 0 = locked, 1 = open */

}

init()
{
   ::init();
   add_action("open_manhole","open");
   add_action("fill_crevice","put");
}

check_manhole()
{
   if (manhole == 1) {
      write(
         "You slowly climb into the manhole and are hit with a blast "
         + "of frigid, arctic air.  Your body goes numb instantly and "
         + "you slip, falling down...\n");
      write("SPLASH!!!\n");
      return 0;
   }
   else
      {
      write("There is no obvious exit down.\n");
      return 1;
   }
}


base_desc()
{
   if (manhole == 1)
      {
      write("You are in the basement of the castle which smells very"
         + " damp and old. Over in the corner is an old and cracked"
         + " sink into which a tap drips. There is a flight of stairs"
         + " leading back up into the castle. Along one wall is a wine"
         + " rack which is filled with hundreds of bottles of wine."
         + " A heavy door is set in the north wall. In the center of"
         + " the floor is a round manhole around which ice has formed.\n"
         + "There are three obvious exits: up, down, north.\n");
   }
   
   else
      {
      write("You are in the basement of the castle which smells very"
         + " damp and old. Over in the corner is an old and cracked"
         + " sink into which a tap drips. There is a flight of stairs"
         + " leading back up into the castle. Along one wall is a wine"
         + " rack which is filled with hundreds of bottles of wine."
         + " A heavy door is set in the north wall. In the centre of"
         + " the floor is a round manhole.\n"
         + "There are two obvious exits: north, up.\n");
   }
   return basedesc;
}


open_manhole(str)
{
   if (str != "manhole")
      {
      notify_fail("Open what?\n");
      return 0;
   }
   
   if (crevice == 0)
      {
      write("You try to open the manhole but it won't budge.\n");
      say(QCTNAME(this_player()) + " tries to open the manhole but fails.\n");
      return 1;
   }
   
   if (crevice == 1)
      {
      if (manhole == 1)
         {
         write("The manhole is already open.\n");
         return 1;
       }
      else
         {
         write("You press on the manhole and it slides downwards into the\n"
            + "darkness.\n");
         manhole = 1;
         return 1;
       }
   }
}

int fill_crevice(string str)
{
   object star;
   if ((str == "star in crevice") && (star = present("star",TP)))
      {
      star->remove_object();
      crevice = 1;
      write("You place the ten pointed star in the crevice on the manhole.\n"
         + "The manhole starts to glow and the star vanishes. You hear something\n"
         + "unlocking. Perhaps the manhole might open now.\n");
      return 1;
   }
   NF("Put what?\n");
   return 0;
}

manhole_desc()
{
   if (manhole == 1)
      manholedesc = ("You look down the manhole into complete darkness.  "
      + "An icy wind bites at your face.\n");
   else
      manholedesc = ("The manhole cover has a crevice on it. It is cold to the touch.\n");
   return manholedesc;
}

crevice_desc()
{
   if (manhole == 1)
      crevicedesc = "There is no crevice here.\n";
   else
      crevicedesc = "The crevice is shaped like a ten pointed star.\n";
   return crevicedesc;
}

reset_icewall_room()
{
   if ((manhole == 1) || (crevice == 1))
      {
      say("A rumbling sound fills the room and the manhole slides back\n"
         + "into place.\n");
      crevice = 0;
      manhole = 0;
   }
   
}



