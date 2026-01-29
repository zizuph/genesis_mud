/*
 * Navarre: November 13th 2015, Commenting out actions with crates that leads to rooms
 *          that are part of an unfinished quest, and should not be available to mortals.
 */ 
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_IN;

#define PARCHMENT_PROP "_garren_prop_read_note"
#define FOUND_KALEN_KEY "_garren_prop_found_key"

// Prototypes
string move_crates();
string move_barrels();
string open_trapdoor();
string unlock_trapdoor();
string lock_trapdoor();
string close_trapdoor();
string trapdoor_descr();
string lock_descr();

int crates_searched = 0;
int crates_moved = 0;
int trapdoor_locked = 1;
int trapdoor_open = 0;

void
create_sanction_room()
{
    set_short("A storage building in the harbour area of Sanction");
    set_long("This warehouse is an old wooden storage building in " +
             "the harbour area of Sanction. There are large crates " +
             "and barrels piled throughout the room.\n");
    add_item(({"building", "warehouse"}), long());
    add_item(({"board", "floor"}), "The floor is made out of old wooden boards.\n");
    add_item(({"crates", "large crates"}), "They are large crates " +
               "normally used to hold various items.\n");
    add_item("barrels", "These are old barrels " +
             "used to store various items.\n");
 //   add_cmd_item(({"crates", "large crates"}), "move", move_crates);
 //   add_cmd_item("barrels", "move", move_barrels);
 //   add_item("trapdoor", trapdoor_descr);
 //   add_item("lock", lock_descr);
 //   add_cmd_item("trapdoor", "open", open_trapdoor);
 //   add_cmd_item("trapdoor", "unlock", unlock_trapdoor);
 //   add_cmd_item("trapdoor", "close", close_trapdoor);
 //   add_cmd_item("trapdoor", "lock", lock_trapdoor);
    add_search(({"large crates", "crates"}), 2, "search_crates", 1);
    add_search("barrels", 2, "search_barrels", 1);
    add_exit(SCITY + "pier02", "out");
}


void
reset_sanction_room()
{
    crates_searched = 0;
    crates_moved = 0;
    trapdoor_locked = 1;
    trapdoor_open = 0;
    remove_exit("down");
}

string
trapdoor_descr()
{
    if(crates_moved)
    {
        return "This is a trapdoor leading down into a cellar of this old warehouse.\n";
    }
    return "You find no trapdoor.\n";
}

string lock_descr()
{
    if(crates_moved)
    {
        return "You notice a lock in the trapdoor.\n";
    }
    return "You find no lock.\n";
}

string search_crates()
{
    string find_string = "";
    int num_halberd = 3+random(8);
    int num_mace = 3+random(8);
    int num_sword = 3+random(8);

    if(crates_searched)
    {
        find_string = "You search through the old crates but find nothing of interest.\n";
    }
    else 
    {
        if(TP->query_prop(PARCHMENT_PROP))
        {
            find_string = "You find a key and a pile of old weapons in the large crates. You dump your findings on the floor.\n";
            clone_object(SOBJ + "kalen_key")->move(TO, 1);
            TP->add_prop(FOUND_KALEN_KEY, 1);
        }
        else
        {
            find_string = "You find a pile of old weapons in the large crates. You dump your findings on the floor.\n";
        }
        crates_searched = 1;

        for(int i = 0; i < num_halberd; i++)
        {
            clone_object(SOBJ + "weapon/halberd")->move(TO, 1);
        }
        for(int i = 0; i < num_mace; i++)
        {
            clone_object(SOBJ + "weapon/mace")->move(TO, 1);
        }
        for(int i = 0; i < num_sword; i++)
        {
            clone_object(SOBJ + "weapon/shortsword")->move(TO, 1);
        }
    }
    return find_string;
}

string
search_barrels()
{
    return "You search through the barrels but find nothing of interest.\n";
}

string
move_barrels()
{
    return "You move the barrels with little effort.\n";
}

string
move_crates()
{
    if(!crates_searched)
    {
        return "You put all your strength into moving the crates, but fail to move them.\n";
    }
    crates_moved = 1;
    return "You put all your strength behind it and manage to move the crates. " +
           "You notice a trapdoor where the crates used to stand.\n";
}

string open_trapdoor()
{
    if(!crates_moved)
    {
        return "What?\n";
    }

    if(trapdoor_locked)
    {
        return "You can't open it, it is locked.\n";
    }
    add_exit(SCITY+"cellar", "down");
    
    trapdoor_open = 1;
    (SCITY+"cellar")->set_trapdoor_open_state(1);
    return "You open the trapdoor.\n";
}

string unlock_trapdoor()
{
    if(!crates_moved)
    {
        return "What?\n";
    }

    if(!trapdoor_locked)
    {
        return "The trapdoor is already unlocked.\n";
    }
 

    if(present("key", TP))
    {
        object key = present("_kalen_key", TP);
        if(key)
        {
            trapdoor_locked = 0;
            key->remove_object();
            (SCITY+"cellar")->set_trapdoor_locked_state(0);
            return "You unlock the trapdoor with your large steel key. Unfortunately " +
                   "you manage to break the key in the process.\n";
        }
        return "You don't have a key that fits in this lock.\n";
    }
    return "Unlock the trapdoor with what?\n";
}

string close_trapdoor()
{
    if(!crates_moved)
    {
        return "What?\n";
    }

    if(trapdoor_open)
    {
        trapdoor_open = 0;
        remove_exit("down");
        (SCITY+"cellar")->set_trapdoor_open_state(0);
        return "You close the trapdoor.\n";
    }
    return "The trapdoor is already closed.\n";
}

string lock_trapdoor()
{
    if(!crates_moved)
    {
        return "What?\n";
    }

    if(trapdoor_locked)
    {
        return "The trapdoor is already locked.\n";
    }

    if(present("key", TP))
    {
        if(!present("_kalen_key", TP))
        {
            return "You don't have a key that fits in this lock.\n";
        }
        return "The lock on the trapdoor appears to be broken.\n";
    }
    return "Lock the trapdoor with what?\n";
}


void set_trapdoor_locked_state(int locked)
{
    trapdoor_locked = locked;
    tell_room(TO, "You hear a soft click.\n");
}

void set_trapdoor_open_state(int open)
{
    trapdoor_open = open;

    if(!crates_moved)
    {
        tell_room(TO, "You hear a noise as if someone opens a door.\n");
    }
    else
    {
        tell_room(TO, "Someone opens the trapdoor.\n");
    }
}
