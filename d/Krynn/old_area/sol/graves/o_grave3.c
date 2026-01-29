#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

object ob;

create_solace_room()
{
    set_short("The Old Graveyard");
    set_long(BS("This is a clearing in the old grave yard. There is actuall" +
		"y a burial mound here. " +
		"There are brambles on both the east and the so" +
		"uth sides of the clearing. An old weathered fence runs fro" +
		"m east to west just north of the burial mound. A giant val" +
		"lenwood tree is visible towering over the rest of the grave" +
		"yard, to the south.", 70)); 

    add_item(({"fence", "wrought iron fence", "old fence"}), BS(
             "This is a tall old wrought iron fence. It has been freshly pa" +
             "inted black. Funny though, it has only been painted on one si" +
             "de. The other side is still peeling and rusty. It is free of" +
             " all plants on this side but not t'other side. The paint is s" +
             "mooth and the fence repaired, making climbing next to impossib" +
             "le.", 70));
    add_item(({"vallenwood tree", "tree"}), BS(
             "It looks like it might have a building way up amoung its great" +
             " branches, but distance and the other lesser trees and brushes" +
             " make it difficult to tell.", 70));
    add_item(({"burial mound", "mound"}), BS(
        "This is an old burial mound, yet it stands out because unlike almos" +
        "t everthing else, it is kept in good maintenence. The grass growin" +
        "g on it is uniform and kept well groomed." +
        "", 70));
 
    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_cmd_item(({"the", "fence"}), "jump", "@@over_fence");
    add_cmd_item("fence", "climb", "@@over_fence");

    add_exit(TDIR + "o_grave2", "west");
    reset_room();
}

reset_solace_room()
{
    if (!ob)
	(ob = clone_object(MONSTER + "skeletal_cat"))->move_living("xx", TO);
}

string
over_fence() 
{
    return "The fence proves too much of a challenge to you.\n";
}
