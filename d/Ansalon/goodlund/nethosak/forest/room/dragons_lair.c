// Navarre Feb 2007: Fixed to disallow players to idle in rooms to steal all the weapons

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit MITHAS_IN;

object dragon;


void
reset_mithas_room()
{
    object* players;
    object lair, cave, crack, statue_room, ld_room;

    if(!objectp(dragon))
    {
        setuid();
        seteuid(getuid());
        
        dragon = clone_object(MNPC + "b_dragon");
        dragon->move(this_object());
        
        lair = find_object("/d/Ansalon/goodlund/nethosak/forest/room/dragons_lair");

        // Make sure the stuff doesn't boot if a player is idling here.
        if(lair)
        {
            players = all_inventory(lair);
            for(int i = 0; i < sizeof(players); i++)
            {
                if(interactive(players[i]))
                {
                      return;
                }
            }
        }    

        crack = find_object("/d/Ansalon/goodlund/nethosak/forest/room/crack");

        // Make sure the stuff doesn't boot if a player is idling here.
        if(crack)
        {
            players = all_inventory(crack);
            for(int i = 0; i < sizeof(players); i++)
            {
                if(interactive(players[i]))
                {
                      return;
                }
            }
        }    

        cave = find_object("/d/Ansalon/goodlund/nethosak/forest/room/main_cave");

        // Make sure the stuff doesn't boot if a player is idling here.
        if(cave)
        {
            players = all_inventory(cave);
            for(int i = 0; i < sizeof(players); i++)
            {
                if(interactive(players[i]))
                {
                      return;
                }
            }
        }    

        statue_room = find_object("/d/Genesis/obj/statue");
        if(statue_room)
        {
            players = all_inventory(statue_room);
            for(int i = 0; i < sizeof(players); i++)
            {
                ld_room = players[i]->query_prop("_statue_room_live_o_last_room");
                if(ld_room && (ld_room == lair || ld_room == cave || ld_room == crack))
                {
                    return;
                }
            }
        }

        (MROOM + "main_cave")->reset_treasure();
        (MROOM + "crack")->reset_treasure();
    }
}


void
create_mithas_room()
{
    set_short("Dark swampy cave");
    set_long("@@long_descr"); 

    add_exit(MROOM + "swamp2","out",0);

    add_exit(MROOM + "main_cave","east","@@main_cave_entry@@", 0);

    add_item(({"walls", "wall"}),
        "The walls here consists of walls and dried mud, that "+
        "is held together by strong roots. The walls that leads "+
        "further into the cave, seems to be made completely out of "+
        "stone, and looks much more stable.\n");

    add_item(({"root","roots"}),
        "The roots here are from the tall trees from above. Some of "+
        "them are rotten but most of them looks quite heathy.\n");

    add_item(({"bones","wolves", "deers", "floor"}),
        "The different bones here that cover the floor must be from "+
        "the poor creatures that has fallen down here from the "+
        "forest above.\n");

    add_prop(ROOM_I_LIGHT,0);
    reset_mithas_room();
}

string
long_descr()
{ 
    return
        "You find yourself inside an underground cave. This place smells "+
        "very rotten and a strong stench of sulphur fills the motionless air. "+
        "Above you the ceiling is filled with stalactites and water continuously "+
        "falls down from above. The floor here is littered with leaves and "+
        "bones of deers and wolves. The cave continues further downwards to the "+
        "east.\n";
}

int
main_cave_entry()
{
    if(objectp(dragon) && E(dragon) == this_object())
    {
        write("It is impossible to sneak past the black dragon.\n");
        return 1;
    }
    write ("You quickly move further into the cave.\n");
    return 0;
}
