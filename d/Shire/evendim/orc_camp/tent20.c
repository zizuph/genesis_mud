/*
 * Inside tent in Bree orc camp
 * By Finwe, May 2001
 */
 
#pragma strict_types
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include <language.h>
inherit TENT_BASE;
inherit CAMP_DIR + "evendim_orcs";
inherit "/d/Shire/evendim/orc_camp/dig_rooms";

/*string *dig_rooms = ({
	"/d/Shire/annuminas/amc2",
	"/d/Shire/annuminas/amc5",
	"/d/Shire/annuminas/amc9",
    "/d/Shire/annuminas/am9",
    "/d/Shire/evendim/ev8",
});

int selected_room;
*/
#define TENT_EXIT CAMP_DIR + "track20"

object ob, ob2;
 
void
create_tent_room()
{
   selected_room = random(sizeof(dig_rooms));
write (selected_room+ " " +dig_rooms[selected_room]+"\n");
    add_my_desc("You are inside a field tent. This is where a " +
        "commander of the group of orcs hangs out when he is " +
        "waiting for scouts to return or to torture unlucky " +
        "prisoners. Crudely constructed furniture lies " +
        "scattered about the tent. Debris is piled in heaps " +
        "throughout the tent.\n");
 
    add_exit(TENT_EXIT, "out");
    reset_shire_room();
 
    furniture();
    chairs();
    table();
}
 
void reset_shire_room()
{
    if(!ob)
    {
	    ob=clone_object("/d/Shire/evendim/npc/leader_orc");
        ob->move(TO);
    }

    if(!ob2)
    {
        ob2=clone_object("/d/Shire/evendim/npc/prisoner");
        ob2->move(TO);
    }
    
}

/*
string
query_selected_room()
{
   return dig_rooms[selected_room];
}
*/