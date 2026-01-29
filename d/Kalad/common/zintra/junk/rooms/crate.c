inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../defs.h"

#define IFTP  if (this_player()->query_skill(SS_AWARENESS) <= 20)

int trapdoor;   /*  1 = trapdoor open
                  0 = trapdoor shut */
void
create_room()
{
    set_short("Inside Crate");
    set_long( break_string(
"You are inside a large wooden crate.  It is in the last stages of decay.  " +
"It looks as if it will come down on top of your head if you disturb " +
"anything.  Be careful!  There are rusty nails everywhere!\n" + 
"@@add_long@@", 78));

    add_exit(G_ROOMS + "warehouse", "out", "@@trap_fun");

    add_item(({"nail", "nails"}), break_string(
"More nails are here, protruding from the sides of the crate.  " +
"@@nail_desc@@", 78));
    add_item("large nail", "@@large_nail_desc");
    add_item("trapdoor", "@@trapdoor_desc");

    add_prop(ROOM_I_INSIDE, 1);
}

void
init()
{
    ::init();
    add_action("move_nail", "pull");
    add_action("move_nail", "push");
    add_action("move_nail", "move");
    add_action("move_nail", "press");
    add_action("go_down", "d");
    add_action("go_down", "down");
}

string
add_long()
{
    if (trapdoor) return "There is a trapdoor here, leading down.\n";
    else return "";
}

int
trap_fun()
{
    if (trapdoor) 
    {
        write("As you leave, the trapdoor snaps shut.\n");
        say ("As " + QCTNAME(this_player()) + " leaves the crate, " +
             "the trapdoor snaps shut.\n");
        trapdoor = 0;
        return 0;
     }
    else return 0;
}

string
nail_desc()
{
    IFTP return "\n";
    else return
"There is one large nail sticking up from under the crate, cleverly hidden " +
"in one shadowy corner.  Its a good thing you didn't step on it.\n";
}

string
large_nail_desc()
{
    IFTP return "All the nails look alike to you.\n";
    else return
"Although this nail is as rusty as the rest, there seems to be a very fine\n" +
"layer of oil on it, as if someone has been here recently.\n";
}

string
trapdoor_desc()
{
    if (trapdoor)
"There is a trapdoor here, with a ladder attached, leading downwards into\n" +
"the darkness.\n";  
    else return "You don't see any trapdoor here.\n";
}

int
move_nail(string str)
{
    notify_fail("What exactly are you trying to manipulate?\n");
    if(!str) return 0;
    if(str != "nail" && str != "large nail") return 0;
    IFTP return 0;
    if (trapdoor)
    {
        notify_fail("Once open, the trapdoor will close automatically.\n");
        return 0;
    }
    trapdoor = 1;
    write( break_string(
"Clever!  The nail is actually a lever.  You move it a tiny bit and a " +
"trapdoor opens in the floor beneath you.\n", 78));
    say ( break_string( QCTNAME (this_player()) + "fiddles with something," +
" and a trapdoor appears in the floor.\n", 78));
    return 1;
}

int
go_down(string str)
{
    notify_fail("Down where?\n");
    if (str) return 0;
    if (!trapdoor) return 0;
    this_player()->move_living(
        "into the trapdoor, which snaps shut immediately afterwards", 
        G_ROOMS + "under_crate", 1);
    trapdoor = 0;
    return 1;
}











