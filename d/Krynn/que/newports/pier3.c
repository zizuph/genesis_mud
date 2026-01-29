/*
 * Filename:        pier3.c
 * Description:     Area around Newports, Abanasinia
 *
 * Coded by:        Aridor, 03/95
 *
 * Revision history:
 * Oct 25 1999 by Boron: Added warfare support
 *
 */

#include "local.h"

inherit BASE_FILE;

#define PLANK   OBJ + "plank"

int plank = 1;

void
reset_newport_room()
{
    plank = 1;
}

void
create_newport_room()
{
    set_short("A pier in the village of Newports");
    set_long("You are on a pier in the village Newports. Despite the desolate " +
        "state of the houses in this village, a small rowboat arrives " +
        "at this pier at fairly regular intervals. To your north " +
        "is the village, while to the south " +
         "and east, you can only see water as far as the eye can see. " +
         "There is no real beach around here, only a rugged coastline. " +
         "A soft salty breeze blows into your face and a few seagulls fly " +
         "overhead. A wooden sign has been affixed to the pier.\n");

    add_item("pier","It's a wooden pier, and seems just about solid enough to " +
         "walk on.@@plank_missing@@ A wooden sign is fixed to the pier.\n");
    add_search("pier",8,"get_plank",1);
    add_item("sign","The sign reads:\n\nPassage to Solace! 5 copper coins!\n\n");
    add_cmd_item(({"sign","words"}),"read","The sign reads:\n\n" +
        "Passage to Solace! 5 copper coins!\n\n");
    add_item(({"houses","village"}),"You can reach it by going north.\n");
    add_item(({"water","ocean","sea","newsea"}),
         "The ocean extends to the east as far as you can see. It's the " +
         "Newsea, a body of water created by the Cataclysm.\n");
    add_item("beach","There is no beach around here.\n");
    add_search("beach",-4,"You don't find any beach.\n");
    add_item("breeze","A soft breeze coming in from the sea.\n");
    add_item("seagulls","They are having fun flying about in the breeze.\n");
    add_item(({"rugged coastline","coastline"}),
         "It consists of fairly big rocks, which have been washed free by " +
         "the water.\n");
    add_item("rocks","You cannot see anything special about them.\n");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    /* Warfare: This is a pier, we do not want guards here! */
    set_num_npc(0);

    (SHIPLINE_OTHER_PIER3)->load_me();
    add_exit(TDIR + "village","north");
}

string
plank_missing()
{
    if (plank)
      return "";
    return " One of the planks in the pier is missing.";
}

string
get_plank()
{
    if (!plank)
      return "Your search reveals nothing special.\n";
    plank = 0;
    clone_object(PLANK)->move(TO,1);
    return "You find that one of the planks on the pier seems loose and yank " +
      "so hard on it that it comes off.\n";
}
