/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"

/* Global variable */
object npc;

/* Prototype functions */
public void reset_room();
public string mage_description();

public void 
create_room()
{
    object door;

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    set_short("The home of Enzalcaspin");    
    set_long("   "+
        "This cave is startlingly different from all the others. " +
        "There are ornate tapestries on the wall and a large carpet on " +
        "the floor. The room is not dark, yet there is no discernable " +
        "source of light; quite odd. There is a large bench at the far end " +
        "of the room upon which you see several old scrolls and some rather " +
        "strange equipment, which you are unfamiliar with. The " +
        "ceiling has a large painting on it, depicting several " +
        "large dragons being slain by the single figure in the centre " +
        "of the painting. " +
        "@@mage_description");

    add_item(({"wall", "walls", "tapestry", "tapestries"}),
        "The walls are covered with large and very finely detailed " +
        "tapestries. They are obviously quite old, but are still in " +
        "very good condition. The scenes they depict are filled with " +
        "mythical beasts, mighty warriors and powerful mages. " +
        "They are quite priceless and really belong in a museum. " +
        "They certainly look nicer than the bare volcanic rock " +
        "that lies behind them.\n");

    add_item(({"roof", "ceiling", "painting", "paintings"}),
        "The ceiling is covered almost completely by a large " +
        "painting. It shows several large dragons attacking " +
        "a mage in the centre of them. He seems to be using " +
        "magic spells, judging by the large numbers of lightning bolts " +
        "and fireballs that are being thrown at the dragons! The " +
        "painting must have taken a long time to complete and a lot " +
        "of work has gone into it.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing is covered with a " +
        "large carpet. The carpet is the most unusual you have ever seen!\n" +
        "Below that is the familiar volcanic rock " +
        "from which these caves are formed.\n");

    add_item(("carpet"),
        "The carpet is woven from some kind of fibre that you are not " +
        "sure you have ever seen before. The carpet is soft, but feels " +
        "as though it would never wear out, no matter how much it is used. " +
        "The most striking feature of the carpet is the way it is coloured; " +
        "the different colours (mainly blue, yellow and green) seem to swirl " +
        "around and merge together as you look at them. Shapes form and then " +
        "disappear in front of your eyes, re-forming on another part " +
        "of the carpet. Perhaps a little magic is at work here....\n");

    add_item(("bench"),
        "The bench is a rather large one, taking up almost the whole of " +
        "the northern wall. It is made from some rather well carved oak, " +
        "and the style in which it is carved is a testament to its age. " +
        "There are several scrolls lined up on the bench. A few of them " +
        "are open and readable. The equipment on the bench looks as though " +
        "it is made from glass with some metal components. It looks like " +
        "this bench is where Enzacaspin works on his magic.\n");

    add_item(({"equipment","glass"}),
        "The equipment on the bench is a very complicated system of " +
        "flasks connected by various pieces of glass and metal tubing. " +
        "You have no idea what it is for and it would probably best to " +
        "leave it alone - it's never a good idea to tamper with stuff " +
        "that you don't understand. Besides, the equipment has quite a " +
        "substantial layer of dust on it, which leads you to the idea " +
        "that it has not been used much lately. Perhaps it just there for " +
        "show these days.....\n");

    add_item(({"scroll", "scrolls"}),
        "On closer inspection, the scrolls are written in a language " +
        "that you don't even recognise, let alone be able to read. " +
        "Also, whenever you try to touch them, you find that there is " +
        "a force that prevents the scrolls from being touched.\n");


    door=clone_object(CAVE_DIR + "obj/door27c");
    door->set_key(271281);
    door->move(this_object());

    add_exit(THIS_DIR+"cave26c", "south", 0, 1);
    
    reset_room();
}

public string
mage_description()
{
    object enzalcaspin;

    enzalcaspin=present("enzalcaspin");

    if (enzalcaspin)
    {
        return("Not only that, but the man from the painting is standing "+
               "before you and does not seem too bothered by your "+
               "presence. He doesn't look particularly well armed, but then " +
               "again, looks can be deceptive.\n\n");
    }
    else
    {
        return("Odd that the occupier isn't here at the moment.\n\n");
    }
}

public void
reset_room()
{
#if 0
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/wise_old_mage");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
        return;
    }

    /* Bring Enzalcaspin back if he has left for any reason. */
    if (!present(npc, TO))
        npc->move_living("into a cave", this_object(), 1, 1);
    
    return;
#endif
}
