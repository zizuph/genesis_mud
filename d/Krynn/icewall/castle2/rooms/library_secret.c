#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <macros.h>
#include <stdproperties.h>
 
inherit ICEINROOM;

object fael;

public void
reset_icewall_room()
{
    if (!fael)
    {
	fael = clone_object(NPCK + "fael-thas.c");
	fael->move_living("xx", TO);
        
        catch((ROOMSK + "treasury")->reset_treasure());
    }
}

void
create_icewall_room()
{

    set_short("Secret library");
    set_long("@@long_descr");

    add_exit("bare_tunnel","west","@@west");
    add_exit("library","south","@@south");

    add_item(({"window","narrow window"}),"There are no windows here. " +
        "The room is illuminated by a soft magic glow.\n");
    add_item(({"rug","green-black rug","vivid green-black rug"}), "" +
        "The rug is thick and undamaged. Mostly black, it has been " +
        "decorated with a green motif of a large plant called chokevine " +
        "renowned for the way it strangles other, less aggressive " +
        "plants.\n");
    add_item("chair","A simple, yet comfortable chair.\n");
    add_item("bookcase","There is only one bookcase " +
        "here, and about twenty volumes occupy its shelves. You see a " +
        "glimmer of magic around them.\n");
    add_item(({"books","book"}),"Definitely magic books, maybe even " +
        "spellbooks. You have been warned.\n");
    add_item("desk","A simple, yet sturdy desk. Just four legs and a " +
        "work bench. The desk is empty.\n");

    setuid();
    seteuid(getuid());

    reset_room();
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ 
    return ("" +
        "You stand in the castle's secret library. The place is warm " +
        "but silent as death. One bookcase stands here, as well as a " +
        "simple desk and a chair. The floor is covered with a thick, " +
        "sound muffling rug with a vivid, green-black pattern. " +
        "The room is illuminated with a magical glow.\n");
}


int
south()
{
    if (present("_big_bad_fael_", TO))
    {  
        if (random(10) > 5)
        {
            write("You manage to flee south, out of the library!\n");
            say(QCTNAME(TP) + " manages to flee south, out of the library!\n");
            return 0;
        }
        write("The dark elf moves to block the south exit!\n");
        say(QCTNAME(TP) + " tries to go south, but the dark elf " +
            "moves to block that exit!\n");
        return 1;
    }

    write("Having learned the trick now, you easily leave the " +
        "secret library.\n");
    return 0;
}

int
west()
{
    if (present("_big_bad_fael_", TO))
    {  
        say(QCTNAME(TP) + " tries to go west, but the dark elf " +
            "moves to block that exit!\n");
        write("The dark elf moves to block the west exit!\n");   
        return 1;
    }

    return 0;
}

int
sit(string str)
{
    if(str != "on chair")
    {
        notify_fail("Sit on what? The chair?\n");
        return 0;
    }

    write("Resting your bones, you plop down on the chair for a " +
        "while. Its not very soft though.\n");
    say(QCTNAME(TP) + " rests his bones, plopping down on the chair " +
        "for a while.\n");
    return 1;
} 

int
read(string str)
{
    if(str != "a book")
    {
        notify_fail("Read what? A book?\n");
        return 0;
    }

    say(QCTNAME(TP) + " reaches for a book and a dazzling " +
        "white flash of electricity leaps out to burn him!\n");
    write("You reach for a book and a dazzling white flash " +
        "of electricity leaps out to burn you!\n\n" +
        "It hurts, badly.\n");
    TP->heal_hp(-random(1000));

    return 1;
}

void
init()
{
    ::init();

    add_action(read, "read");
    add_action(sit,"sit");
}
