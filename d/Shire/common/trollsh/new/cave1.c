inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/trollsh/new/defs.h"

//** Global Variables **//
int gBoxPresent = 1;

//** Prototypes **//
int check_exit();
string get_box();
string check_box();
string item_desc();

void
create_shire_room()
{
    FIXEUID

    set_short("Just inside a large cave");
    set_long("You stand at the entrace of a large cave. A foul "+
        "stench assails your nostrils as a faint draft blows "+
        "in from the cave entrance. The ground is littered with "+
        "what looks to be pieces of broken armour and weapons. "+
        "A large cart rests on its side in the middle of the "+
        "cave with its contents scattered about the floor. You "+
        "make out five distinct passageways leading away from "+
        "here. The cave entrance lies to the north, while four "+
        "smaller tunnels lead to the southwest, south, southeast "+
        "and east.\n");

    add_item(({"cave","entrance"}),
        "A large opening over ten feet high can be seen to "+
        "the north.\n");

    add_item(({"broken armour","broken weapons","pieces"}),
        "They all seem useless in their present condition.\n");

    add_item("passageways",
        "They lead off to the southwest, south, southeast, and east.\n");
    
    add_item(({"cart","large cart"}),
        "The broken wooden bed of the cart rests on its side "+
        "supported by one spoked wheel. Under the overturned "+
        "bed you see various tools it must have been carrying.\n");

    add_item("tools", item_desc);

    add_item("shovel",
        "It has a wide flat iron head and long wooden handle.\n");
 
    add_item("pick",
        "It has a curved iron head tapering to a dull point "+
        "sitting atop a stout wooden handle.\n");
 
    add_item(({"wheelbarrow","wheel-barrow","wheel barrow"}),
        "It has a small iron tub supported by two wooden "+
        "handles. A thick wooden wheel rests beneath it.\n");

    add_item(({"box","small box","wooden box","small wooden box"}), check_box);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Shire/common/trollsh/new/cove","north",check_exit,1);
    add_exit("/d/Shire/common/trollsh/new/home1","southwest",0,1);
    add_exit("/d/Shire/common/trollsh/new/home2","south",0,1);
    add_exit("/d/Shire/common/trollsh/new/home3","southeast",0,1);
}

string
item_desc()
{
    return (gBoxPresent ? "You see a shovel, a pick, a wheelbarrow, and a small box.\n"
        : "You see a shovel, a pick, and a wheelbarrow.\n");
}            

string
check_box()
{
    return (gBoxPresent ? get_box() : "You find no such thing.\n");
}

string
get_box()
{
    object box = clone_object(NEW_SHAWS_OBJ_DIR+"box");

    if (box->move(TP))
    {
        write("The small box is too small to be examined from afar.\n");
        box->move(ENV(TP));
    }

    else
        write("You stoop down and pick up the small wooden box.\n");

    gBoxPresent = 0;
    return "";
}

int
check_exit()
{
    // us trolls wouldnt want to leave the cave right now ;)
    if (TP->query_race() == "troll")
        return 1;

    return 0;
}
