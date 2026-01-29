/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit SEWER_BASE;

int clean_mail;

void
reset_neraka_room()
{
    clean_mail = 0;
}

string
long_descr()
{
    return "This is a dark crypt somewhere below Neraka. The air is " +
    "dry and dusty, with a faint hint of something unpleasant. There " +
    "is a stone bier in the middle of the room. To the west, the room " +
    "opens up into a larger hallway.\n";
}

void
create_neraka_room()
{
    set_short("in a dark crypt");
    set_long("@@long_descr");

    add_crypt_items();
    add_item("crypt","@@long_descr");
    add_item("hallway",
    "A larger hallway is to the west, mostly lost in darkness.\n");
    
    add_item(({"bier","stone bier","slab"}),
    "The bier is a large slab of stone standing in the middle of the room. " +
    "There is a skeleton lying on the slab.\n");
    add_item("skeleton","This is the skeleton of a man long since " +
    "deceased. It is clad in a chainmail shirt.\n");
    add_item(({"shirt","chainmail","chainmail shirt"}),
    "@@exa_chainmail");

    remove_prop(ROOM_I_LIGHT);

    add_exit(NSEWER + "c2", "west");

    reset_room();
}

string
exa_chainmail()
{
    if (clean_mail)
        return "The chainmail shirt shines brilliantly in the light, " +
        "there is not a speck of dust or dirt on it. It looks to be " +
        "in excellent condition, despite being old.\n";
    else
        return "The chainmail shirt looks to be in good condition, " +
        "despite its age, but it is dirty and covered with dust.\n";
}

void
do_reward(object pl)
{
    object pearl;
    
    /* no reward if the player isn't in the room to recieve it */
    if (E(pl) != TO)
        return;

    seteuid(getuid());
    pearl = clone_object(NOBJ + "pearl");
    if (!pearl)
        return;

    if (pearl->move(pl))
    {
        if (pearl->move(E(pl)))
        {
            pearl->destruct_object();
            return;
        }
        else
        {
            write("Suddenly, a pearl jumps out of the skeleton's eye " +
            "socket and lands on the ground. You sense a feeling of " +
            "gratitude emanating from the skeleton.\n");
        }
    }
    else
    {
        write("Suddenly, a pearl jumps out of the skeleton's eye socket and " +
        "lands in your hand. You grip the pearl by reflex, and as you do, " +
        "you sense a feeling of gratitude emanating from the skeleton.\n");
    }
}

int
do_clean(string str)
{
    if (!str)
        return 0;

    if ((str != "shirt") && (str != "chainmail") &&
    (str != "chainmail shirt"))
        return 0;

    if (clean_mail)
    {
        write("But the chainmail shirt is already as clean as it can get.\n");
        return 1;
    }

    write("You carefully " + query_verb() + " the chainmail shirt until " +
    "it is as good as new.\n");
    tell_room( QCTNAME(TP) + " does something to the skeleton on the bier.\n",
    ({ TP }) );
    clean_mail = 1;
    
    set_alarm(2.0, 0.0, &do_reward(TP));

    return 1;
}

void
init()
{
    ::init();
    add_action(do_clean, "clean");
    add_action(do_clean, "polish");
}
