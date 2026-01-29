/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
inherit INSIDE_BASE;

object skc1 = 0;

int altar2, altar3, num;
string long;

void
create_solace_room()
{
    set_short("Crypt room");
    set_long("@@slong");
    (TDIR + "crypt10.c")->load_me();

    add_item(({"carving", "mural", "tree", "north wall"}),
         "@@carving");
    add_item(({"hand", "lich"}), "The lich seems to have his hand " +
         "outstretched towards you.\n");
    add_item("floor", "@@floor");
    add_item(({"wall", "walls", "hall", "hallway", "ceiling", "roof"}), "@@wall");
    add_item(({"light", "column", "black light", "column of black light"}),
         "@@blight");
    add_item(({"white light","column of white light"}), "@@wlight");
    if (altar3 == 0)
    {
    add_item(({"ball", "golden ball"}), "@@ball");
    add_item(({"statue", "gold dragon", "dragon"}), "@@statue");
    }

    INSIDE;
    LIGHT;

    set_alarm(0.7,0.0,reset);
    set_alarm(1.0,0.0,"restore_me");

}

void
restore_me()
{
    restore_object(TDIR + "questnumber");
}

string
slong()
{
    altar2 = call_other(TDIR + "crypt10.c", "query_altar");
    long = "This is a very large well lit room. The south"
      + " wall has a beautiful mural carving that gives a "
      + "very realistic three dimensional effect of a lich. ";
    if (altar2 != 2)
    {
    long = long + "The centre of the room has a column of what can only"
      + " be described as black light, it reaches from the"
      + " floor to the roof and is about 1 foot in diameter.\n";
    }
    if (altar2 == 2)
    {
    long = long + "The centre of the room has a column of what can only"
      + " be described as white light, it reaches from the"
      + " floor to the roof and is about 1 foot in diameter.\n";
    }
    if (altar3 == 0)
    {
    long = long + "Directly in front of you is an extremely realistic"
      + " statue of a gold dragon the only reason you think"
      + " it is a statue is because it hasn't moved from when you"
      + " came in.\n";
    }
    return long;
}

void
reset_solace_room()
{
    altar3 = 0;
    altar2 = call_other(TDIR + "crypt10.c", "query_altar");
    if (!skc1)
    {
    skc1 = clone_object(MONSTER + "skcwarrior");
    skc1->move_living("xxx", TO);
    }
}

void
init()
{
    ::init();

    ADA("shake");
    ADA("get");
    ADD("get", "take");
}

string
statue()
{
    write("As you look closely at the statue suddenly a telepathic"
      + " voice comes from it. 'Many years ago I was imprisoned here"
      + " by an evil mage and my soul was imprisoned within that"
      + " column of light. Please mortal help"
      + " me......'  The voice fades away as if retreating far far"
      + " away.\n");
    say(QCTNAME(TP) + " studies the statue carefully.\n");
    return "";
}

string
ball()
{
    write("The ball seems to be made of gold!\n");
    say(QCTNAME(TP) + " studies the ball carefully.\n");
    return "";
}

int
get(string str)
{
    int xp;

    if (altar3 == 0)
    {
    NF("Get what?\n");
    if ((str == "ball") || (str == "ball from light") || (str == "golden ball")
        || (str == "golden ball from light") || (str == "ball from column")
        || (str == "golden ball from column"))
    {
        altar2 = call_other(TDIR + "crypt10.c", "query_altar");
        if (altar2 == 2)
        {
        if (TP->test_bit("Krynn", 2, 0))
        {
            write("You get the golden ball and the dragon thanks"
              + " you once again for helping him. Then he disappears"
              + " in a puff of smoke.\n");
            say(QCTNAME(TP) + " grabs the golden ball from the light, " +
            "which then takes on a life of its own and disappears " +
            "into the dragon statue. The statue shudders and then " +
            "animates into a real dragon! The dragon speaks to " +
            QCTNAME(TP) + " for a few minutes, then disappears in " +
            "a puff of smoke!\n");
            altar3 = 1;
            return 1;
        }
        seteuid(getuid(this_object()));
        TP->set_bit(2, 0);
        write("You grab the golden ball from the light, "
              + "it seems to have a will of its own and drags you"
              + " over to the dragon. The ball flies from your hand"
              + " and seemingly gets absorbed into the statue. The"
              + " statue seems to shudder and suddenly it animates into"
              + " a real gold dragon! The dragon turns to you and says:"
              + " 'Thank you mortal for giving me my freedom, I am sure"
              + " the gods will reward you.' At this the dragon seems to"
              + " concentrate for a moment and disappears in a puff of"
              + " smoke. You feel more experienced.\n");

        xp = 6000;
        /* Removed july 2002 by Boron, since the .o file gets
         * corrupted some players got the bonus later. Lets stop
         * that.

        if (num == 0)
        {
            write("Because you are the first to do this quest you get"
              + " an experience bonus!\n");
            xp += 6000;
        }
        if (num == 1)
        {
            write("Because you are the second to do this quest you get"
              + " an experience bonus!\n");
            xp += 3000;
        }
        if (num == 2)
        {
            write("Because you are the third to do this quest you get"
              + " an experience bonus!\n");
            xp += 1500;
        }
        */
        TP->add_exp_quest(xp);
        STD_QUEST_LOG("Crypt", TP, xp);
        num = num + 1;
        save_object(TDIR + "questnumber");

        say(QCTNAME(TP) + " grabs the golden ball from the light, which"
            + " then takes on a life of its own and disappears into the "
            + " dragon statue. The statue shudders and then animates "
            + " into a real dragon! The dragon speaks to " + QCTNAME(TP) +
            " for a few minutes, then disappears in a puff of smoke!\n");
        altar3 = 1;
        return 1;
        }
        write("The evil from the black light repels you. You fail to"
          + " get the ball.\n");
        say(QCTNAME(TP) + " tries to get the ball from the light but can't.\n");
        return 1;
    }
    return 0;
    }
    return 0;
}

string
blight()
{
    if (altar2 != 2)
    {
    if (altar3 == 0)
    {
        write("The column of black light appears to have a small"
          + " golden ball suspended in it.\n");
        say(QCTNAME(TP) + " studies the black light carefully.\n");
        return "";
    }
    write("It's a column of black light.\n");
    say(QCTNAME(TP) + " studies the black light carefully.\n");
    return "";
    }
    return "Examine what?\n";
}

string
wlight()
{
    if (altar2 == 2)
    {
    if (altar3 == 0)
    {
        write("The column of white light appears to have a small"
          + " golden ball suspended in it.\n");
        say(QCTNAME(TP) + " studies the white light carefully.");
        return "";
    }
    write("It's a column of white light.\n");
    say(QCTNAME(TP) + " studies the white light carefully.\n");
    return "";
    }
    return "Examine what?\n";
}

void
go_south()
{
    set_alarm(1.0,0.0,"remove_south");
    return 0;
}

void
remove_south()
{
    write("The exit closes behind you.\n");
    say("The exit closes silently.\n");
    remove_exit("south");
}

int
shake(string str)
{
    string *dirs;
    dirs = this_object()->query_exit_cmds();
    if (sizeof(dirs) && member_array("south",dirs) >= 0)
    {
    write("The exit is already open.\n");
    return 1;
    }
    NF("Shake what?\n");
    if ((str == "lich") || (str == "the hand") || (str == "hand"))
    {
    write("You reach out and shake the lich's hand."
          + " You hear a soft click and a secret passage"
          + " opens in the south wall.\n");
    say(QCTNAME(TP) + " reaches out to shake hands with the mural and"
        + " a secret passage opens in the south wall!\n");
    add_exit(TDIR + "crypt2", "south", "@@go_south");

    return 1;
    }
    return 0;
}

string
floor()
{
    write("The floor is just a clean bare normal stone floor.\n");
    say(QCTNAME(TP) + " studies the floor carefully.\n");
    return "";
}

string
wall()
{
    write("The walls and the ceiling of the room are black though"
      + " they appear to only be made of normal stone, unlike the clean"
      + " white floor. The exception is the south wall which"
      + " depicts a beautiful carving of an lich. The"
      + " lich looks very realistic.\n");
    say(QCTNAME(TP) + " studies the room carefully.\n");
    return "";
}

carving()
{
    write("The mural is an amazing work of art. It is an almost"
      + " life like representation of a lich his hand outstretched.\n");
    say(QCTNAME(TP) + " studies the mural carefully.\n");
    return "";
}

