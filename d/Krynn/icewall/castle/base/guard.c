/* room originally made by somebody, but fixed up and made workable
* by Stevenson 2/19/95
*/

#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

void reset_icewall_room();

int key;
object skguard1, skguard2;

void create_icewall_room()
{
   set_short("Guard room");
   set_long(
      "You are in the dungeon guard room. In the center of the "
      + "room is a table covered in layers of dust. @@sk@@"
      + "\n" );
   
   
   add_item("guards",
      "It looks like it may come to blows.\n");
   add_item("dice",
      "It appears that one is heavier than the other.\n");
   add_item("key",
      "It is a solid iron key with the number 4 written on it.\n");
   add_item("table","@@table_desc");
   
   
   add_exit(BASE + "prisonn","south",0);
   
   INSIDE
   reset_icewall_room();
}

void reset_icewall_room()
{
   if (!skguard1)
      {
      skguard1=clone_object(ICE_CAST_M+"skguard");
      skguard1->move(TO);
   }
   if (!skguard2)
      {
      skguard2 = clone_object(ICE_CAST_M+"skguard");
      skguard2->move(TO);
   }
   if ( !key ) key = 1;
}

void init()
{
   ::init();
   add_action("get_key","get");
}

int get_key( string str )
{
   NF("Get what?\n");
   if (str != "key")
      return 0;
   
   if (key == 1)
      {
      clone_object(ICE_CAST_O + "key1")->move(TP, 1);
      write("You pick up the key from the dust.\n");
      tell_room(TO, QCTNAME(TP) +
         " gets on " + POSSESSIVE(TP) +
         " hands and knees and begins to search under "
         + "the table.\n", TP );
      key = 0;
      return 1;
   }
   else
      NF("There is no key here.\n");
   return 0;
}

string table_desc()
{
   if (key == 1)
      {
      write("As you look under the table you spy a key lying in the dust.\n");
      return "";
   }
   else
      {
      write("As you look under the table you see disturbed dust.\n");
      return "";
   }
}

string sk()
{
   if ( skguard1 && skguard2 )
      return "Standing next to the table are two "
   + "skeletons arguing over a game of dice.";
   if ( skguard1 && !skguard2 || !skguard1 && skguard2 )
      return "Standing next to the table is a skeleton "
   + "muttering something about cheating and dice.";
   return "";
}
