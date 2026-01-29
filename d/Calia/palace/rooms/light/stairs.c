/*
    this is the stairwell on the first floor of the crystalline palace


    coder(s):   Glykron & Maniac

    history:
             11/2/99    added yule tree to reset_room    Uhclem
             6/4/96     tidied up kroug handling         Maniac
             29/9/95    block npcs from going up         Maniac
             22/9/95    kroug raid code installed        Maniac
             17/8/95    gear exit blocked off            Maniac
             8.12.94    minor changes                    Maniac
             5. 2.93    header added and stairs up open  Glykron

    purpose:    junction
    exits:      n, s, w, e, u

    objects:    none
    npcs:       guardian calians

    quests:     none
    special:    none

    to do:      make guardian protect stairs
    bug:        none known
*/

#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

#define NUM 2
object *calian = allocate(NUM);

void
make_monster(int i)
{
    calian[i] = clone_object(MONSTER("calian_guardian"));
    calian[i]->move(THIS);
    tell_room(THIS, QCTNAME(calian[i]) + " arrives.\n");
}

int
npc_check()
{
    if (this_player()->query_npc())
         return 1;
    else
         return 0;
}

void
create_room()
{
    set_short("Central Palace");
    set_long("This is a large octagonal-shaped room.  " +
        "A spiral staircase ascends upward.  " +
        "An intense beam of white light shines through the spiral.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_hall"), "south", 0);
    add_exit(ROOM("light_gold"), "north", 0);
    add_exit(ROOM("light_training"), "west", 0);
    add_exit(ROOM("light_lightroom"), "east", 0);
    add_exit(ROOM("light_stairs2"), "up", "@@npc_check");
    add_item( ({ "staircase", "stair", "stairs" }),
        "It is made of crystal.\n");
    reset_room();
}

// Function:  reset_room

/*

Purpose:  called by system about once per hour to reset room condition.

Arguments:  none

Returns:  nothing

*/

void
reset_room()

{

    object ob;
    object room = this_object();
    string *datetext = explode(ctime(time()), " ");

    /*
     *  Uhclem changed reset_room to deploy a Christmas tree from
     *  December 23 to 29 of every year.  Original contents of this
     *  function begin here.
     */

    int i;
    for(i = 0; i < NUM; i++)
        if(!calian[i])
            make_monster(i);

    /*
     *  End of original reset_room() contents.    
     */

    if (strlen(datetext[2]) == 1)

    {

        datetext[2] = "0" + datetext[2];

    }

    /*
     *  The yule tree is deployed over many days so that 
     *  all players have an opportunity to come by and enjoy
     *  it sometime during the holiday period.    
     */

    if (datetext[1] == "Dec" &&
        datetext[2] >= "23" &&
        datetext[2] <= "29" &&
        !present("tree", room))

    {

        ob = clone_object("/d/Calia/yuleware/palace_tree");
        ob->move(room);

        tell_room(room, capitalize(LANG_ADDART(ob->short())) +
            " suddenly falls from above and hits the floor with a" +
            " loud THUD! It wobbles for a moment, then settles" +
            " perfectly in an upright position.\n");

    }

}
