/*
 * Filename:        pier3.c
 * Description:     Area around Newports, Abanasinia
 *
 * Coded by:        Aridor, 03/95
 *
 * Ship Directory:   /d/Ansalon/taman_busuk/sanction/ship/newports/
 *
 * Revision history:
 * Aug    1999 by Ashlar: <I wonder what he actually did *Boron*>
 * Oct 25 1999 by Boron:  Added warfare support
 * Feb 22 2000 by Boron:  Updated warfare support, so the ship only sails
 *                        if dragon armies hold the area.
 *
 */
#include "/d/Krynn/common/warfare/warfare.h"
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit BASE_FILE;

#define CAPTAIN "/d/Ansalon/taman_busuk/sanction/ship/newports/captain"
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
         "state of the houses in this village, apparently a ship arrives here " +
         "at this pier at fairly regular intervals. To your north, south " +
         "and east, you can only see water as far as the eye can see. " +
         "There is no real beach around here, only a rugged coastline. " +
         "A soft salty breeze blows into your face and a few seagulls fly " +
         "overhead. A wooden sign has been affixed to the pier.\n");

    add_item("pier","It's a wooden pier, and seems just about solid enough to " +
         "walk on.@@plank_missing@@ A wooden sign is fixed to the pier.\n");
    add_search("pier",8,"get_plank",1);
    add_item("sign","@@read_sign@@\n");
    add_cmd_item(({"sign","words"}),"read","@@read_sign@@\n");
    add_item(({"houses","village"}),"You can reach it by going west.\n");
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


    add_exit(TDIR + "pier","southwest");
}

string
read_sign()
{
    if (ARMYMASTER->army_in_area(WAR_AREA_NEWPORT) == KNIGHT_ARMY)
        return "You see the text 'Ferry to Sanction' crossed over with red paint.";
    else
        return "You read:'Ferry to Sanction.'";
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


void
area_conquered(string newarmy, string oldarmy)
{
    // The Knights gained the area
    if (newarmy == KNIGHT_ARMY)
    {
        CAPTAIN->command("swear");
        CAPTAIN->command("say Those Knights will force me out of bussiness!");
        CAPTAIN->command("shrug");
        CAPTAIN->command("say I will have to cease my operation for abit...");
    }
}
