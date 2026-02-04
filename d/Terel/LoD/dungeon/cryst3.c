/*
 * cryst3.c
 *
 * Inside the quest crystal.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"
#include "/d/Terel/include/quest_bits.h"

#define DUNG_DIR     (LOD_DIR + "dungeon/")
#define SORCERER     (LOD_DIR + "monster/sawoq")
#define BACK         (DUNG_DIR + "cryst2")
#define CAVE         (DUNG_DIR + "cave2")

public string *
query_moving_object_list()
{
    return ({ SORCERER });
}

public void
reset_room()
{
    ::reset_room();
}

public void
create_room()
{
    ::create_room();
    
    set_short("strange place");
    set_long("You are in a very strange place. Despite it is very bright " +
             "here you cannot see very far.\n");
    
    add_prop(ROOM_I_LIGHT, 3);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    
    add_exit(BACK, "southwest", 0);
    
    set_noshow_obvious(1);
    
    reset_room();
}
