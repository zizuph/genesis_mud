/*
 * path.c
 * By Skippern
 * 
 * Functions used common for the Path of the Dead
 */
//inherit "/d/Gondor/std/delay_room.c";
inherit "/d/Gondor/common/lib/area_room";
inherit "/d/Gondor/std/room";

#include "../erech.h"

public void
tunnel_items()
{
  add_item(( { "wall", "walls", "tunnel" } ), "The walls in the tunnel " +
           "are clean and smooth, almost cut clean when the tunnel was " +
           "built milleniums ago.\n");
  add_item(( { "shadow", "shadows", "darkness" } ), "Perhaps it is just " +
           "your imagination, but looking into the darkness, you can feel " +
           "someone or something staring back at you.\n");
  add_item(( { "ground", "path" } ), "The ground is dry and clean. No dust " +
           "or dirt lies on the smooth surface, as if someone has cleaned " +
           "the tunnel.\n");
}

int
pass()
{
    string race = this_player()->query_race_name();

    switch(race)
    {
    case "elf":
    case "kender":
        return 0;
    default:
        this_player()->add_panic(PANIC);
        return 0;
    }
}

reset_ghosts(string *ghost, int nr)
{
    int i;

    for(i = 0; i < nr; i++)
    {
	if(!ghost[i] || !present(ghost[i],TO))
	{
	    ghost[i] = clone_object(E_NPC + "ghost");
	    ghost[i]->move(TO);
	}
    }
}
