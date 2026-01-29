/*
 * The entrance to Krynn from the domain tower
 */

inherit "/std/room";

#include <std.h>
#include <language.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

#define DOM    "Krynn"


void
load_board()
{
    object bb = clone_object("/d/Krynn/common/obj/disc_board");
    bb->move(TO);
}

void
create_room()
{
    set_short("Entrance to Krynn");
    set_long("You are standing on the back of a huge dragon! " +
         "From here you have a splendid view across all " +
         "of Krynn. You can see a lot of tiny spots down " +
         "there, Players enjoying the areas, battling the " +
         "evil Dragonarmies, and a few Wizards, who put " +
         "all their effort into expanding the world of " +
         "Krynn and making it an interesting place to be. \n" +
         "There is a board here for wizards and mortals aline " +
         "to discuss the state of Krynn and Ansalon.\n" +
         "@@current_info@@" +
         "\nThe Krynn workroom is to the east and the " +
         "safety of the domain tower is north.\n");
    add_exit("/d/Genesis/wiz/dom_a1", "north");
    add_exit("/d/Krynn/workroom", "east");

    load_board();
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
    if (lord == "")
      str += "\nThere is currently no Liege :-(\n\n";
    else
    {
    str += C(who) + " (" + C(WIZ_RANK_NAME(((SECURITY)->query_wiz_rank(who)))) + ")";
    file1 = read_file("/w/" + who + "/info");
    file2 = read_file("/w/" + who + "/project");
    if (file1)
      str += ": " + file1;
    if (!file1)
      str += "\n";
    if (file2)
      str += "     Project: " + file2 + "\n";
    }
    whos = (SECURITY)->query_domain_members(DOM);
    for(i=0;i<sizeof(whos);i++)
      {
      if (whos[i] == lord)
        continue;
      who = whos[i];
      str += C(who) + " (" + C(WIZ_RANK_NAME(((SECURITY)->query_wiz_rank(who)))) +
        (who != madwand ? "" : ", Madwand") + ")";
      file1 = read_file("/w/" + who + "/info");
      file2 = read_file("/w/" + who + "/project");
      if (file1)
        str += ": " + file1;
      if (!file1)
        str += "\n";
      if (file2)
        str += "     Project: " + file2;
      }
    return str;
}
