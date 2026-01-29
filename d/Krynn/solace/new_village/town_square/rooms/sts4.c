/*
* STS Room 4
* Created by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit SQUARE_BASE;

void
reset_solace_room()
{
}

void
create_solace_room()
{
    set_add_buildings();
    add_item(({"trees", "tree"}), "There are a few vallenwood trees in this area. As you gaze about, you notice one especially beautiful one to your northeast. Suddenly some insects that are buzzing about a tree closer to you catch your eye.\n");
    add_item(({"insect", "insects"}), "Looking closer at the insects, you notice that they are common outdoor flies. They sure are buzzing contentedly around a pile of something.\n");
    add_item("pile", "@@examine_pile@@");
    add_exit(ROOM2, "north");
    add_exit(SOUTHSTS4, "south");
    add_exit(ROOM5, "east");
    add_exit(WESTSTS4, "west");
    add_exit(ROOM3, "northeast");
    add_exit(ROOM1, "northwest");
    reset_solace_room();
}

string examine_pile(string str)
{
    if(!present("_dung_for_dirtying", TO) & !present("_dung_for_dirtying", TP))
    {    
        clone_object(DUNG)->move(TO, 1);
        return "Upon closer inspection, the pile causing such a fuss among the flies is a pile of animal dung. One sniff of the air confirms this, as you wrinkle your nose in disgust.\n";
    }
    
    else
        return "";

}
