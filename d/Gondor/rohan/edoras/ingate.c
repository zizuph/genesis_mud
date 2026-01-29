inherit "/d/Gondor/common/lib/town";

#include "/d/Gondor/defs.h"

void    reset_room();
string  sign_text();

object man;

void
create_room()
{
    hillside = "north";
    height = 1;
    road = 0;
    density = 3;
    extraline = "You find yourself just inside the gates of Edoras. "+
    "Proud Rohirrim men and women are all around you, hastening around doing "+
    "their business, ignoring the newcomer in town. "+
    "A long broad staircase leads up south towards Meduseld, "+
    "the mighty hall of Theoden, king of Rohan. There are great stonelaid "+
    "streets leading up around the hill to the southwest and downwards to "+
    "the southeast. There is a sign here. It looks quite important. ";
    make_the_room();
    add_exit(EDORAS_DIR + "gate","north",0);
    add_exit(EDORAS_DIR + "stairs1","south",0);
    add_exit(EDORAS_DIR + "path2","southwest",0);
    add_exit(EDORAS_DIR + "path1","southeast",0);
    add_item(({"sign"}), sign_text());
    add_cmd_item(({"sign"}), "read", sign_text());
    reset_room();
}

string
sign_text()
{
    return "The sign states in large black letters:\n\n  Notable places in Edoras: \n\n"+
    "The Golden Hall of Meduseld: ...... At the top of the hill south of here.\n"+
    "The Edoras Adventurers Guild:  .....Southwest from here.\n"+
    "The Transport Service Stables: .....Southwest from here.\n"+ 
    "The Barracks: ......................Southeast from here.\n"+ 
    "The Proud Stag Pub: ................South of here.\n"+
    "The Edoras Post Office: ............South of here.\n"+
    "Bendar's General store: ........ ...Southwest from the square south of here.\n"+
    "Alwine's Armoury: .............. ...Southeast from the square south of here.\n"+
    "The Bank of Edoras:  .............. Three squares south of here.\n"+
    "The Sleeping Stallion Inn: ........ Three squares south of here.\n"+
    "The Library of Edoras: .. ..........Southwest from the second square south of here.\n\n";
}

void
reset_room()
{
    if (!objectp(man))
    {
	man = clone_object(EDORAS_DIR + "npc/citizen");
	man->arm_me();
	man->move_living("south", TO);
    }
}

