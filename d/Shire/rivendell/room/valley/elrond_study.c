/*
 * Elrond's Study
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
#define MIN_AWARE 10

object inkpot;
 
void
create_house_room()
{
    set_short("Elrond's private study");
    set_long("You are in the private study of Elrond. This " +
        "peaceful room is where he holds private meetings with " +
        "those who seek his help. The room has a large desk " +
        "set near the south wall with some overstuffed chairs " +
        "surrounding it and a bookcase against one wall. The " +
        "walls are decorated with various paintings and a large " +
        "rug covers the floor. The room leads out to a corridor, " +
		"east to a bedroom, and down to the Hall of Elrond.\n");

    add_item(({"painting", "paintings"}),
        "The paintings are two sets of portraits. One set is of " +
        "his human father Earendil and his elven mother Elwing. " +
        "The second set of his wife's elven parents, Celeborn " +
        "and Galadriel.\n");
    add_item("desk",
        "Made of dark wood, the desk is large and dominates the " +
        "south end of the room. Various papers are neatly " +
        "stacked on its surface with some writing implements " +
        "scattered across the desk.\n");
    add_item(({"writing implements", "writing instruments"}),
        "On the desk you see some quills, an ink pot, and the " +
        "seal of Elrond.\n");
    add_item(({"quill", "quills"}),
        "The quills are fashioned from eagle feathers with a " +
        "sharp tip at the ends. There are traces of ink on " +
        "their tips.\n"); 
    add_item("ink pot",
        "The ink pot is small and half full of black ink. Traces " +
        "of ink are on the edges of the pot where excess ink " +
        "has been tapped off of the quills.\n");
    add_item(({"seal", "seal of elrond"}),
        "The seal is made of steel. It has a stylized 'E' set " +
        "on a background of a large tree.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a maroon color " +
        "with a golden fringe. The rug is decorated with a " +
        "large sailing ship upon a blue ocean.\n");
    add_item(({"overstuffed chairs", "overstuffed chair"}),
        "The chairs are large and comfortable looking. They " +
        "are forest green with a leaf pattern.\n");
    add_item(({"papers", "stacks of paper"}),
        "The papers are stacked neatly on the desk. You seem " +
        "unable to read them but some appear to be very " +
        "important looking while others appear to be blank.\n");
    add_item("staircase",
        "The staircase is made of dark wood with a polished " +
        "bannister. It leads downstairs to the Hall of Elrond.\n");
    add_item("bannister",
        "It is made of dark wood, polished to a deep shine.\n");
    add_item(({"feathers", "eagle feathers"}),
        "The feathers are dark brown and golden colored. Such " +
        "magnificent feathers can only be a gift from a noble " +
        "creature.\n");
    add_item("bookcase",
        "The bookcase is tall and sturdy. It is full of various " +
        "books.\n");
    add_item("books",
        "The books appear to be histories and tales. They seem to " +
        "be undecipherable since they are written in Quenya.\n");
    add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");
   add_item(({"south window", "southern window"}),
        "@@south_up@@ The river crashes down a waterfall.\n");
    add_item(({"west window", "western window"}),
        "@@west_up@@\n");
 
    set_extra_wall("The walls are decorated with paintings. " +
        "Large windows fill the west and south walls.");
    set_extra_floor("A large rug covers the floor.");

    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");
    add_item(({"west windows", "western windows", "west window",
        "western windows"}), "@@west_up@@\n");
    add_item(({"south windows", "southern windows", "south window",
        "southern windows"}), "@@south_up@@\n");
    add_prop("_obj_s_search_fun","do_search");
    reset_shire_room();

    num_of_windows=2;
 
    add_exit(VALLEY_DIR + "u_cor03",     "north");
    add_exit(VALLEY_DIR + "elrond_bdrm", "east");
    add_exit(VALLEY_DIR + "elrond_hall", "down");
}
 

void
init()
{
    ::init();
    add_action("do_nothing",    "north");
    add_action("do_nothing",    "east");
    add_action("do_nothing",    "down");
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "jump");
    add_action("do_nothing",    "tackle");
    add_action("do_nothing",    "dance");
    add_action("do_nothing",    "bow");
    add_action("do_nothing",    "curtsey");
    add_action("do_nothing",    "wiggle");
    add_action("do_nothing",    "strut");
    add_action("do_nothing",    "kill");
 
}
 
int
do_sit(string str)
{
    if(str != "in chair")
    {
        write("Sit where? Perhaps in a chair?\n");
        return 1;;
    }
 
    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting in an overstuffed chair");
    TP->add_prop("i_am_sat",1);
    write("You sit in an overstuffed chair.\n");
    say(QCTNAME(TP)+ " sits in an overstuffed chair.\n");
    return 1;
 
}
 
int
do_stand()
{
    if(!TP->query_prop("i_am_sat"))
    {
        write("But you're not sitting down!\n");
        say(QCTNAME(TP)+ " gazes at the pictures.\n");
        return 1;
    }
 
    TP->remove_prop("i_am_sat");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You stand up, refreshed and invigorated from the rest.\n");
    say(QCTNAME(TP)+ " arises from an overstuffed chair and " +
        "looks around.\n");
    return 1;
 
}
 
int
do_nothing()
{
    if(TP->query_prop("i_am_sat"))
    {
        write("You can't do that sitting down!\n");
        say(QCTNAME(TP)+ " looks around.\n");
        return 1;
    }
}



string
do_search(object searcher, string str)
{
   int awareness;

   awareness = searcher->query_skill(SS_AWARENESS);
   if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
   if(!str || (str!= "desk" && str!="ink pots" && str!="inkpot")) return 0;
   if(inkpot) return 0;
   seteuid(getuid(TO));
   inkpot = clone_object(ROBJ_DIR + "inkpot");
   inkpot->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something on the desk.\n");
   return "You find a ink pot on the desk.\n";
}


void reset_shire_room()
{
    inkpot = 0;
}
