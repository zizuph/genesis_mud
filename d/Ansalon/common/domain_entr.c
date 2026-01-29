/*
* The entrance to Ansalon from the domain tower
*/

inherit "/std/room";

#include <std.h>
#include "/d/Ansalon/common/defs.h"
#define DOM    "Ansalon"

void
create_room()
{
   set_short("Entrance to Ansalon");
   set_long("You find yourself standing on the red moon, " +
      "Lunitari! From this spot, you have an excelent view " +
      "of the continent of Ansalon. " +
      "You can see areas which the Krynn wizards have " +
      "created, bustling with busy mortals. You also see " +
      "The Krynn wizards working on some new areas " +
      "in the northern and southern regions of " +
      "the continent. Then, you see something that really " +
      "catches your eye! There's something new here......" +
      "A new team of wizards, lead by Lord Arman, has formed " +
      "to work side-by-side with the wizards of Krynn. You see " +
      "this fresh new team busy at work on the eastern and " +
      "western regions of the continent.\nThese are the wizards " +
      "of Ansalon!\n" +
      "@@current_info@@" +
      "\nThe Ansalon workroom is to the south and the " +
      "safety of the domain tower is east.\n");
   add_exit("/d/Genesis/wiz/dom_a2", "east");
   add_exit("/d/Ansalon/workroom", "south");
}

string
current_info()
{
   string lord, who, *whos, file1, file2, madwand;
   string str = "\nCurrent Work Force:\n-------------------\n";
   int i;
   who = (SECURITY)->query_domain_lord(DOM);
   madwand = (SECURITY)->query_domain_madwand(DOM);
   lord = who;
   str += C(who) + " (" + ((SECURITY)->query_wiz_level(who)) + ")";
   file1 = read_file("/d/" + DOM + "/" + who + "/info");
   file2 = read_file("/d/" + DOM + "/" + who + "/project");
   if (file1) 
      str += ": " + file1;
   if (!file1)
      str += "\n";
   if (file2)
      str += "     Project: " + file2 + "\n";
   whos = (SECURITY)->query_domain_members(DOM);
   for(i=0;i<sizeof(whos);i++)
   {
      if (whos[i] == lord)
         continue;
      who = whos[i];
      str += C(who) + " (" + ((SECURITY)->query_wiz_level(who)) + 
      (who != madwand ? "" : ", Madwand") + ")";
      file1 = read_file("/d/" + DOM + "/" + who + "/info");
      file2 = read_file("/d/" + DOM + "/" + who + "/project");
      if (file1)
         str += ": " + file1;
      if (!file1)
         str += "\n";
      if (file2)
         str += "     Project: " + file2;
   }
   return str;
}
