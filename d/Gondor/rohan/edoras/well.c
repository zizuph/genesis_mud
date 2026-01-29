inherit "/d/Gondor/common/lib/town";

#include "/d/Gondor/defs.h"

void    reset_room();

object *kid = allocate(2);

void
create_room() 
{
    hillside = "south";
    height =1;
    road = 1;
    density = 2;
    extraline = "You are standing on a little square, almost straight "
      + "south from Meduseld, which can be seen at the very top of "
      + "this 150 foot high hill. There is a little well in the center "
      + "of the square. Kingsroad leads around the hill to the northeast. ";
    make_the_room();
    add_exit(EDORAS_DIR + "path1","northeast",0);
    add_exit(EDORAS_DIR + "garden","northwest",0);
    add_item(({"well","little well","spring"}), BSN(
        "This is a little round well made of stone. From this some of "
      + "the people of Edoras get their water."));
    reset_room();
    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
}

void
init() 
{
    add_action("do_enter","enter");
    ::init();
}

void
reset_room() 
{
    int     i;

    for (i = 0; i < sizeof(kid); i++)
    {
        if (!objectp(kid[i]))
        {
            kid[i] = clone_object(EDORAS_DIR + "npc/child");
            kid[i]->arm_me();
            kid[i]->add_chat("I heard some strange sounds coming from the well.");
            kid[i]->add_chat("There is evil in the well.");
            kid[i]->add_chat("As a small child, I was always afraid of falling into "
              + "the well and drowning there!");
            kid[i]->move_living("into the game", TO);
        }
    }
}

int
do_enter(string str) 
{
    NFN(CAP(query_verb())+" what?");
    if (!strlen(str))
        return 0;

    if (str=="well" || str == "little well" || str == "spring") 
    {
        write("You climb into the little well.\n");
        TP->move_living("into the well", EDORAS_DIR + "in_well");
        return 1;
    }
    return 0;
}

