#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;

object sorceress;

void
reset_kendermore_room()
{
    if (!sorceress)
    {
        sorceress = clone_object(KNPC + "sorceress");
        sorceress->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A dark hut in the forests near Kendermore");
    set_long("There isn't much space to move around here. Shelves line " + 
        "the walls, overflowing with various potions, books, and various " + 
        "other things. A comfortable chair sits in front of a lit " + 
        "fireplace. Two tables have been shoved against opposite walls. " + 
        "They are also topped with potions, books and various other things. " + 
        "There are no windows here, leaving the fire and a small oil lamp " + 
        "as the only sources of light.\n");
    add_item("shelves", "Every inch of these shelves are taken up by books, " + 
        "potions, vials, herb jars, mortars, sealed jars, and many other " + 
        "things. From the contents, you guess the person who lives here " + 
        "uses black magic.\n");
    add_item("walls", "They are made of sturdy gray stones.\n");
    add_item(({"chair", "comfortable chair"}), "It's a plush black chair " + 
        "sitting close to the heat of the fire.\n");
    add_item(({"fire", "fireplace"}), "There is a crackling fire in the " + 
        "fireplace, and a bubbling cauldron sitting above it.\n");
    add_item(({"tables", "table"}), "There is little space left on these " + 
        "tables. Books, potions, vials, herb jars, mortars, sealed jars, " + 
        "and many other things have been placed on them.\n");
    add_item("potions","They are of all different colours, from bubbling " + 
        "green to opaque red.\n");
    add_item("books","They appear to be spellbooks.\n");
    add_item(({"small oil lamp", "lamp", "oil lamp", "small lamp"}), "It " + 
        "gives off a small amount of light, just enough to read by.\n");
    add_item("vials","Made of glass, they are used to mix potions in.\n");
    add_item(({"jars", "jar"}), "Which jars?\n");
    add_item(({"herb jar", "herb jars"}), "They are used to store and " + 
        "preserve herbs.\n");
    add_item(({"sealed jars", "sealed jar"}), "It looks like body parts " + 
        "are stored in them, eyes, noses, frog legs, etc.\n");
    add_item(({"mortar", "mortars"}), "They have pestles sitting in them, " + 
        "and are used to grind up herbs and other ingredients.\n");
    add_item("cauldron", "It's heavy, made of black metal. A black " + 
        "liquid bubbles inside it, giving off a strong unpleasant odour.\n");
    add_item("floor", "There isn't much of it that you can see, but it is " + 
        "made of wood.\n");

    add_cmd_item(({"book", "books", "spellbooks"}), "read", "@@read_books");

    add_exit(KROOM + "forest3", "out", 0);

    set_tell_time(300);
    add_tell("The liquid in the cauldron bubbles noisily.\n");
    add_tell("The fire crackles and pops.\n");
    add_tell("The flames of the fire dance hypnotically.\n");
    add_tell("The wind howls outside.\n");
    add_tell("The floor creaks loudly.\n");

    reset_kendermore_room();
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
read_books()
{
    write("They are written in the language of magic, but are sealed " + 
        "against casual opening.\n");
    return "";
}

