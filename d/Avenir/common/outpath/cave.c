// file name:    /d/Avenir/common/outpath/cave1.c
// creator(s):   Cirion, April 1996
// last update:	 Sirra added the mandible bone in the bedding, March 98.
// purpose:      Cavern where the quarls dwell.
//			Search the bedding, find the mandible bone
//			for the Wolf Quest
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";

#include "/d/Avenir/common/outpath/outpath.h"
#include "/d/Avenir/common/holm/wolf.h"

string find_wolf_bone(object player, string str);

object   *quarl = allocate(5);
int found;
  
void 
reset_room()
{
    int  i;
    found = 1;

    for(i=0;i<sizeof(quarl);i++)
    {
        if (!quarl[i])
        {
            quarl[i] = clone_object(MON+"quarl");
            quarl[i]->arm_me();
        }

        if (!present(quarl[i]))
            quarl[i]->move_living("along the rock", TO);
    }
}

void 
create_room()
{
    set_short("damp cavern");
    set_long("This cavern is damp and smelly, as if something horrible "
        +"had crawled down and died here. The walls rise up to the low ceiling, which "
        +"is slowly dripping foul water onto the floor. Scattered along the rough rock "
        +"floor are piles of moist and decaying bedding. The cavern leads out to "
        +"the east.\n");
  
    add_item(({"bedding","bed","pile","piles"}),"It looks like something foul lives "
        +"here.\n");
    add_item(({"wall","walls","rock"}),"The rocks walls of the cavern are rough "
        +"and unhewn.\n");
    add_item(({"water","drops","moisture"}),"It is foul and dirty.\n");

    add_cmd_item(({"water","drops","moisture"}),({"drink","taste"}),
        "It tastes awful!\nYou feel befouled.\n");

    add_prop(OBJ_S_SEARCH_FUN, "find_wolf_bone");
    add_prop(OBJ_I_SEARCH_TIME, 2);

    remove_prop(ROOM_I_LIGHT);
    IN;

    add_exit(OUTPATH+"ledge3","east");
    reset_room();
}

string
find_wolf_bone(object player, string str)
{
    object bone;

    if (found<1)
        return "";

    if (str != "bedding")
	return "";

    found--;
	
    bone = clone_object(WOLF_BONE + "redherring.c");
    bone->move(this_player(),1);

    return "You find a bone in the bedding!\n";
}

		
