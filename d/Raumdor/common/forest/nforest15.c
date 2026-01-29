/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

int done;

void
create_room()
{
    forest_details = " There is a small pond here, where the water from " +
    "a small stream empties. The stream flows from the southeast.";
    ::create_room();
    add_item(({"pond"}),"@@pond@@");
    add_item(({"stream"}), "It empties into the pond here. It " +
           "looks clear and clean enough to drink from.\n");
    add_exit(FOREST_DIR + "nforest27","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest28","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest16","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest04","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest03","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest02","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest14","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest26","northwest",0,FOREST_FATIGUE);
    
    done = 1;
}

public void
key_available()
{
    done = 0;
}

string
pond()
{
    if (done == 0)
    {
        return
        "The pond is small, but looks deep. You cannot see "+
        "the bottom, for it is too deep and too dark. However, you think you "+
        "see something moving in there. It looks clear and clean enough to "+
        "drink from.\n";
    }
    if(done == 1)
    {
        return
        "The pond is small, but looks deep. You cannot see the bottom, "+
        "for it is too deep and dark. It looks clear and clean enough to "+
        "drink from.\n";
    }
}

void
init()
{
    ::init();
    add_action("drink", "drink");
}
int
drink(string str)
{
    object obj;
    if (str == "from stream" || str == "from the stream")
    {
        write("Ahh! Refreshing!\n");
        say(QCTNAME(TP) + " drinks from the stream.\n",TP);
        TP->drink_soft(300);
        return 1;
    }
    if (str == "from pond" || str == "from the pond")
    {
        if(!done)
        {
            write("As you lean down to drink from the pond, a dark shape " +
                    "grows large and looks like it's coming up! " +
                    "You jump back!\n");
            say(QCTNAME(TP) + " drinks from the pond, but then jumps back "+ 
                "suddenly!\n", TP);
            obj = clone_object(COMMON_NPC_DIR + "wight");
            clone_object(FOREST_DIR + "key")->move(obj);
            obj->set_short("water wight");
            obj->move_living("M", TO);
            tell_room(TO, "A water wight bursts out of the pond!\n");
            done = 1;
            return 1;
        }
        else
        {
            write("You drink from the pond.\n");
            say(QCTNAME(TP) + " drinks from the pond.\n");
            return 1;
        }
    }
    notify_fail("Drink from what? The pond?\n");
    return 0;
}
