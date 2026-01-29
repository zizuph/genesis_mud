inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

int recently_searched;

void
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_prop(OBJ_S_SEARCH_FUN, "search_pile");

    set_short("Moist square chamber");
    set_long("The echo of water dripping from far off reaches your ears "+
            "from all angles, confusing your senses as to its true origin. This "+
            "roughly square-shaped chamber is filled with a large number of "+
            "stalagmites and stalactites. In addition, numerous bones along "+
            "with other refuse is scattered across the floor, filling the room "+
            "with a noxious scent. A passage leads to the north.\n");
    add_item(({"moist square chamber","moist chamber","square chamber","chamber","square-shaped chamber"}),
            "A natural cavity within the rock structure that seems to have been "+
            "converted into a living space...of sorts. The sole exit is a passage "+
            "leading to the north, a place of inky darkness.\n");
    add_item(({"passage","passageway","place"}),"This moist environment has helped "+
            "create a number of stalagmites and stalactites, which hinder speedy "+
            "movement through this area.\n");
    add_item(({"inky darkness","darkness"}),"A lightlessness that you "+
            "thought was only possible in your dreams.\n");
    add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
            "The natural rock formations litter this passageway, hindering "+
            "speedy movement.\n");
    add_item(({"floor"}),"The ground is barely visible due to the large "+
            "number of stalagmites intermixed with numerous bones and filth.\n");
    add_item(({"bones","bone","refuse","filth"}),"Gnawed and chewed "+
            "animal bones mixed with raw feces and other solid waste fills this "+
            "chamber. One large pile of filth in the corner is particularly "+
            "disgusting.\n");
    add_item(({"pile"}),"A massive pile of dung! Whew, boy does it stink!\n");
    add_exit(CPASS(desert/salt/l12),"north","@@hurt@@",1,2);

    add_npc("/d/Kalad/common/wild/pass/npc/liz_war");

    reset_room();
}

int
hurt()
{
    if (TP->query_base_stat(SS_DEX) < 50)
    {
        write("You stepped on a stalagmite! Ouch!\n");
        say(QCTNAME(TP) + " stepped on a stalagmite!\n");
        TP->heal_hp(-100);
        return 0;
    }
    write("You manage not to step on any stalagmites.\n");
    return 0;
}

void
reset_room()
{
    recently_searched = 0;
}

string
search_pile(object searcher, string place)
{
    if (!place || (place != "pile" && place != "the pile"))                                  
        return "";

    if (recently_searched)
    {
       return "You find nothing in the disgusting pile, and just get yourself "
           + "dirty for your effort!\n";
    }

    recently_searched = 1;
    say(QCTNAME(TP) + " discovered something from the pile!\n");
    clone_object("/d/Kalad/common/wild/pass/npc/chest_mimic")->move_living("M",TO);
    return "You discover a golden chest within the pile!\n";
}
