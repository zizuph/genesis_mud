/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

#define CLUB_LOG   "/d/Shire/log/treehouse"

inherit ROAD_BASE;


void down_tree();

void
create_road_room()
{   
    object board;

    setuid();
    seteuid(getuid());

    apples = 0;
    set_areadesc("secret");
    set_area("tree house");
    set_areaname("the orchard");
    set_land("Bree");
    add_my_desc("It is tucked away in the branches of the tree. A platform " +
        "of wood planks make up the floor of the tree house. Branches " +
        "grow around it forming walls. Leaves hang from the branches, " +
        "blocking your view. Apples hang from the branches, hidden within " +
        "the leaves. There is a hole in the platform where you may leave. " +
        "Someone has hung a message board on a branch. An iron box is attached " +
        "to one of the branches.\n");
    add_item(({"apple","apples", "fruit"}),
        "The apples are large, red, and juicy. They hang from the " +
        "branches like ruby jewels, ready to be picked and enjoyed.\n");
    add_item(({"blossom","apple blossom"}),
        "The apple blossoms are soft and pink. Many hang from the " +
        "branches and fill the air with a sweet smell.\n");
    add_item(({"apple tree", "fruit tree"}),
        "This is an old apple tree. Its branches are rough and gnarled " +
        "and full of green leaves. Many large, juicy apples hang from " +
        "the branches. Some are even low enough to be picked easily.\n");
    add_item(({"path"}),
        "The path isn't visible from up here. The leaves and branches " +
        "block the view.\n");
    add_item(({"road"}),
        "The road isn't visible from here. The leaves and branches block " +
        "the view.\n");
    add_item(({"grass"}),
        "The grass isn't visible from up here. The leaves and branches " +
        "block the view.\n");
    add_item(({"branches"}),
        "They are old and gnarled. They are twisted, brown, and rough " +
        "looking. The branches grow up and around the platform.\n");
    add_item(({"leaves", "leaf"}),
        "They are oval shaped with a light serrated edte. The leaves " +
        "are green on the fronts and a downy white color on the back. " +
        "They hang from the branches, waving in the breeze.\n");
    add_item(({"hole"}),
        "It is cut into the platform, and enables you to climb down out " +
        "of the tree house.\n");
    add_item(({"platform", "ground", "floor"}),
        "The platform is made of wood planks. They are laid across some " +
        "branches and make up the floor of the tree house. A hole is cut " +
        "into it so you can climb down to the orchard.\n");
    add_item(({"wood planks", "wood plank", "planks", "plank"}),
        "They are long and laid across some branches, making up the " +
        "platform.\n");
    add_item(({"box", "iron box"}),
        "The box is square shaped and made of strong iron. On the top is a " +
        "slot where you can insert gold coins. Beneath the slot you read:\n\n" +
        "\tShow your support for treehouses everywhere by inserting \n" +
        "\ta gold coin. The money will go to maintain them everywhere.\n");

    add_room_tell("Sweet apples swing from the branches.");
    add_room_tell("Large bumblebees dance from blossom to blossom.");
    add_room_tell("A hummingbird darts from flower to flower.");

    reset_shire_room();
    
    if (!objectp( board) )
    {
        board = clone_object("/d/Shire/std/board");
        //board->set_long("This is a message board with various notices posted " +
        //    "on. Visitors often leave notes here for others to read.\n");
        board->set_short("message board");
        board->set_num_notes(30);
        board->set_board_name( ROAD_DIR + "treehouse_board");
        board->move(this_object());
    }
}

public void
init()
{
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("get_apple", "get");
    add_action("get_apple","pick");
    add_action("do_climb", "climb");
    add_action("insert","insert");
    add_action("leave","leave");

    ::init();
}

int do_climb(string str)
{
    if(str=="down" || str =="tree" || str == "branch")
        down_tree();
    else 
        write("Climb where?\n");
    return 1;
}

void
down_tree()
{
    write("\nYou carefully climb down several branches to the orchard below.\n\n");
    say(QCTNAME(TP) + " carefully climbs down several branches to the orchard below.\n\n");
    TP->move_living("M",ROAD_DIR + "orchard04");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from the tree house above.\n\n",TP);
}

/*
 * Club routines
 */

int
leave(string s)
{
    NF("Leave what? The club?\n");
    if(s!="club")
        return 0;

    NF("You're not a member!\n");
    if(!present("_shire_medallion",TP))
        return 0;

    present("_shire_medallion", TP)->remove_object();

    write("You throw the badge away. It bounces around a few times, then " +
        "rolls out of the treehouse and disappears.\n");
    say(QCTNAME(TP)+" throws something away.\n");
    
    return 1;
}
int 
insert(string s)
{
    FIXEUID;

    NF("Insert what into what?\n");
    if (!s) return 0;
    
    if(!parse_command(s,TO,"[gold] 'coin' 'in' / 'into' [the] [iron] 'box'"))
        return 0;

    NF("You don't have any gold coins.\n");
    
    if("/sys/global/money"->move_coins("gold",1,TP,0))
        return 0;
  
    say(QCTNAME(TP)+" joins the Society for the Preservation of the Treehouse in Bree.\n");
    write("You receive a small badge.\n");
    write("To leave the club, return here and type 'leave club'.\n");
    clone_object(OBJ_DIR + "medallion")->move(TP);

    return 1;
}
