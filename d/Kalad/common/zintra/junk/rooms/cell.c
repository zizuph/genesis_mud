inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

int passage;    /* 1 if secret passage is open 
                   0 if secret passage is closed */
object doora;

void
reset_room()
{
    object doorb;
    
    call_other(G_ROOMS + "passage2", "reset_me");
    call_other(G_ROOMS + "wine_cellar", "reset_me");
    if (doora)
    {
	doora->do_close_door();
	doora->do_lock_door();
        tell_room(G_ROOMS + "dungeon", BS("A guard strolls in, looks in " +
            "the cell for a moment, then closes and locks the door.  He " +
            "then leaves.\n"));
    }
    if (doorb = (G_ROOMS + "dungeon")->get_door_ob())
    {
	doorb->do_close_door();
	doorb->do_lock_door();
    }
    if (!present("skeleton", TO))
        room_add_object(G_OBJ + "skeleton");
    present("skeleton")->reset_container();
    if (passage != 0)
        tell_room(TO, BS("You feel dizzy for a moment.  When you " +
            "recover, things look a little different.\n"));
    passage = 0;
}

void
create_room()
{
    set_short("Inside Cell");
    set_long( BS(
"You are inside a tiny cell.  There is nothing of interest here.  No cot, " +
"water basin, nothing!  A tiny square of light is streaming from a small " +
"window on the cell door, but other than that...   Nothing to do in here " +
"except stare at the walls.\n" + "@@extra_long@@"));

    add_item("window",
"The window is tiny, and just lets in enough light to cast the cell in a " +
"dim light.  You can see a bare room, beyond.\n");

    add_item(({"walls", "wall"}), BS("Although these walls are constructed " +
        "of loose bricks, they seem very sturdy.\n"));

    add_item("bricks", "There are many of them.\n");

    add_item(({"east wall", "west wall", "north wall", "south wall"}),
"It would take a long time to examine the entire wall.  Perhaps you should " +
"take a closer look?\n");

    add_item(({"brick", "loose brick"}), "@@brick_desc");

    INSIDE
    add_prop("_obj_s_search_fun", "my_search");

    (doora = clone_object(G_OBJ + "cdoora"))->move(this_object());
    reset_room();
}

string
extra_long()
{
    if (passage) return "There is a small opening in the east wall.\n";
    return "";
}
void
init()
{
    ::init();

    add_action("stare_wall", "stare");
    add_action("pull_brick", "pull");
    add_action("push_brick", "push");
    add_action("move_east", "east");
    add_action("brick_search", "search");
}
    
int
brick_search(string str)
{
    if (str == "brick" || str == "loose brick")
    {
        if(TP->query_prop("_blackhands_found_brick")) return 0;
        write ("You don't find any brick to search.\n");
        return 1;
    }
    return 0;
}

int
stare_wall(string str)
{
    NF("What?\n");
    if(!str) return 0;
    if (str !="wall" && str != "walls" && str != "at wall" 
        && str != "at walls") return 0;
    write( BS(
"You stare at the walls for a while (why not?  Nothing else better " +
"to do).\n"));
    call_out("stare2", 10);
    return 1;
}

void
stare2()
{
write (BS("But, just for a minute, you think you notice something " +
"different about one of the walls.  You rapidly dismiss the thought.\n"));
}

my_search(object searcher, string str)
{
    if (!str) return 0;
    if (str == "wall" || str == "walls" || str == "at wall" || 
            str == "at walls") return "Wait a minute!  Which wall?\n";
    if (str == "north wall") return
        "You find some graffiti written on the wall next to the door.\n" +
        "     'Roxie was here.'\n";
    if (str == "south wall") return 
        "You find some profund graffiti written on the wall.\n\n" +
        "     'I believe in making the world safe for our children.\n" +
        "      But not for our children's children,\n" +
        "      Because I don't believe children should be having sex.'\n" +
        "                                -Jack Handley\n" + "\n" +
        "Death to the Blackhands!\n";
    if (str == "west wall") return BS("You find some obscene graffiti on the" +
        " west wall.  It's too perverted to describe.\n");
    if (str == "east wall")
    {
        TP->add_prop("_blackhands_found_brick", 1);
        say (QCTNAME(TP) + " finds something interesting on the east wall.\n");
        return BS("It seems that one of the bricks towards the bottom of " +
            "the east wall is loose.  You can't imagine why you would care " +
            "about this, except to help allevialte your boredom.\n");
      }
    return 0;
}

brick_desc()
{
    if(!TP->query_prop("_blackhands_found_brick"))
        return "You find no brick.\n";
    return BS("The brick is certainly loose, but it appears to be stuck.\n");
}

int
pull_brick(string str)
{
    NF("Pull what?\n");
    if (!str || str != "brick") return 0;
    if(!TP->query_prop("_blackhands_found_brick")) return 0;
    write("You can't seem to find enough purchase to pull the brick.\n");
    return 1;
}

int
push_brick(string str)
{
    NF("Push what?\n");
    if (!str || str != "brick") return 0;
    if(!TP->query_prop("_blackhands_found_brick")) return 0;
    if (passage)
    {
        passage = 0;
        write(BS("The brick pushes in easily, almost too easily.  The secret" +
            " door in the east wall suddenly disappears.\n"));
        say("The secret door in the east wall suddenly disappears.\n");
        call_other(G_ROOMS + "passage2", "west_open");
        return 1;
    }
    write(BS("The brick pushes in easily, almost too easily.  A secret door " +
            "appears in the east wall.\n"));
    say("A secret passage opens in the east wall.\n");
    call_other(G_ROOMS + "passage2", "west_open");
    passage = 1;
    return 1;
}

int
move_east(string str)
{
    if (str || !passage) return 0;
    set_dircmd("east");
    TP->move_living("into the small opening in the east wall", 
        G_ROOMS + "passage2");
    return 1;
}

void
open_wall()
{
    if(passage)
    {
        tell_room(TO, BS("If you see this message, there is a problem with " +
"the logic in the concerned areas.  This function has been written to help " +
"fix this automatically, but please report the bug, so I can fix it.  " +
"Please make the report as detailed as possible.  Thank you.\n"));
    return;
    }
    passage = 1;
    tell_room(TO, "Suddenly, a small passage appears in the east wall.\n");
}
