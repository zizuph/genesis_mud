/*
 * Downstairs west hall of Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;
int closet_open;
object closet;

void
create_house_room()
{
    set_short("The east hallway");
    set_long("This is the east end of the hallway in the house. " +
        "The room is plain except for the simple staircase " +
        "leading upstairs and the lamps hanging from the ceiling. " +
        "A long carpet runs the length of the hall, adding warmth " +
        "and comfort to the hallway.\n");
    add_item(({"carpet"}),
        "The carpet is long and rectangular. It is the length of " +
        "the hallway with a white fringe on both ends. The carpet " +
        "is a soft blue color with abstract flower designs.\n");
    add_item(({"flower designs", "abstract flower designs", "designs"}),
        "The abstract flower designs are suggestive of water " +
        "lilies surrounded by twining ivy.\n");
    remove_item(({"candles", "candle"}));
    set_add_staircase("The staircase leads upstairs. Beneath the " +
        "staircase is a small door. The door is @@closet_status@@");
    set_add_staircase_closet();

    reset_shire_room();
// closet setup
    closet_open=0;
    closet = clone_object(ROOMS_DIR + "closet");
    closet->set_no_show();
    closet->move(TO);

    add_exit(ROOMS_DIR + "rm_pent",   "north", );
    add_exit(ROOMS_DIR + "rm_hall01", "west");
    add_exit(ROOMS_DIR + "rm_hall03", "up", );
}
void
init()
{
    ::init();
    add_action("open_stuff", "open");
    add_action("close_stuff", "close");

}


void
reset_shire_room()
{
}


/*returns whether closet is opened/closed message */
string closet_status()
{
    string full_msg;

    switch (closet_open)
    {
        case 0:
            return "closed door.";
            break;  
        case 1:
            return "open door, allowing access to the closet.";
            break;
     }
}


/* open/close routines for the closet door */
int open_stuff(string str)
{

// opens closet    
    if(str == "closet" || str == "door" || str == "closet door")
    {
        switch(closet_open)
        {
            case 0: /* closet closed */
            closet_open=1;
            write("You open the closet door.\n");
            say(QCTNAME(TP) + " opens the closet door.\n");
            closet->unset_no_show();
            break;

            case 1:
            write("The closet door is already opened.\n");
            break;
        }
        return 1;
    }


}

/*
 * close routine for closet door
 */
int close_stuff(string str)
{
// close the closet
    if(str == "closet" || str == "door" || str == "closet door")
    {
        switch(closet_open)
        {
            case 0: /* closet closed */
            write("The closet door is closed already.\n");
            break;

            case 1:
            write("You close the closet door.\n");
            say(QCTNAME(TP) + " closes the closet door.\n");
            closet->set_no_show();
            closet_open=0;
            break;
        }
        return 1;
    }

}
