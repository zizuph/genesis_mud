/*
 *  IGARD_LIB + "gate_funcs.c"
 *
 *  Various functions common to ring wall gates.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

/* PROTOTYPES */

public string       exa_inscription();
public int          arrow_attack();
public int          permit_entry();
public int          knock_gate(string str);
public int          push_gate(string str);
public void         init();
public int          gate_add_items();

object           actor;

public int
gate_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"door", "doors", "gate", "gates", "entrance",
        "great gate", "great southern gate"}), "Two mighty doors of "
        + "iron tower above you. Each door stands more than thirty "
        + "feet high and together they span almost twenty across. The "
        + "iron is very weathered and scratched, but no dent can be "
        + "seen on the face of these doors for they have never been "
        + "broken. The doors are mounted on large iron hinges.\n");
    add_item(({"iron", "scratches", "scratch"}), "The doors are made "
        + "of iron quarried from mines in the Misty Mountains. The "
        + "iron is weathered and scratched, but no dent can be seen "
        + "anywhere.\n");
    add_item(({"hinge", "hinges", "iron hinge", "iron hinges",
        "large hinge", "large hinges"}), "The doors are mounted on "
        + "several large iron hinges bolted into the rock of the "
        + "ring wall. Through a marvel of engineering, the massive "
        + "doors are balanced on the hinges in such a way that a single "
        + "person can open or close them with a push.\n");
    add_item(({"arch", "archway", "stone arch"}), "A great arch of "
        + "stone encloses the mighty iron doors. Made from the same "
        + "daunting black stone as the ring wall, the arch bears a "
        + "weathered inscription at the top.\n");

    return 1;
}


public string
exa_inscription()
{
    return "The inscription reads:\n"
+" ___________________________________________________________\n"
+"|o_________________________________________________________o|\n"
+"||                                                         ||\n"
+"||        Friends need only push on the gate to            ||\n"
+"||        enter. All others face the peril they are due.   ||\n"
+"||_________________________________________________________||\n"
+"|o_________________________________________________________o|\n";

}


int
arrow_attack()
{
    int healed, health, pain, ouch;

    healed = TP->query_max_hp();
    health = TP->query_hp();
    pain = (healed/2);
    ouch = (health/2);
    actor = TP;

    write("A cloud of arrows erupts from the wall above you. Many of "
        + "them skitter off the stones of the street, but several of "
        + "them find their mark. Ouch!\n");
    tell_room(environment(actor), "A cloud of arrows erupts from the "
        + "wall overhead. Many of them skitter off the stones of the "
        + "street, but several of them strike " + QTNAME(TP) + ".\n", 
        ({actor}));

    if (health <= pain)
    {
        TP->set_hp(ouch);
        return 1;
    }

    else
    {
    TP->set_hp(pain);
    }

    return 1;
}


int
permit_entry()
{
    write("This should not happen. Please make a bug report.\n");
}


public int
knock_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("What is it that you are trying to knock on?\n");
       return 0;
    }

    write("A voice from above shouts down at you: Read the inscription, "
        + "you fool! Do you think we have all day to be answering the "
        + "door?\n");
    tell_room(environment(actor), "A voice from above shouts at " 
        + QTNAME(actor) + ": Read the inscription, you fool! Do you "
        + "think we have all day to be answering the door?\n", ({actor}));
    return 1;

}


public int
push_gate(string str)
{
    actor = TP;

    if (!strlen(str) || (str != "gate" && str != "door"
                      && str != "gates" && str != "doors"))
    {
	      NF0("Are you trying to push on the gate?\n");
       return 0;
    }

    if (GOODIE)
    {
        if (ENEMY)
        {
        write("A voice from above shouts at you: Enemy of Isengard, "
            + "flee whilst you can!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Enemy of Isengard, flee whilst you can!\n", 
            ({actor}));
        arrow_attack();
        permit_entry();
        return 1;
        }

        if (FRIEND)
        {
        write("A voice from above shouts at you: Hmm, there is still "
            + "something about you that does not ring true, stranger. "
            + "You may pass, but we are still suspicious of you!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Hmm, there is still something about you "
            + "that does not ring true, stranger. You may pass, but we are "
            + "still suspicious of you!\n", 
            ({actor}));
        permit_entry();
        return 1;
        }

        else
        {
        write("A voice from above shouts at you: You have no "
            + "business in Isengard, stranger. Begone!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": You have no business in Isengard, "
            + "stranger. Begone!\n", 
            ({actor}));
        arrow_attack();
        permit_entry();
        return 1;
        }

    }

    if (BADDIE)
    {
        if (ENEMY)
        {
        write("A voice from above shouts at you: Traitor of Isengard, "
            + "you are no longer welcome here! Begone!\n");
        tell_room(environment(actor), "A voice from above shouts at " 
            + QTNAME(actor) + ": Traitor of Isengard, you are no longer "
            + "welcome here! Begone!\n", ({actor}));
        arrow_attack();
        return 1;
        }

        else
        {
        write("A voice from above shouts at you: Friend "
            + "of Isengard, you may pass.\n");
        tell_room(environment(actor), "A voice from behind shouts at " 
            + QTNAME(actor) + ": Friend of Isengard, you may "
            + "pass.\n", ({actor}));
        permit_entry();
        return 1;
        }
    }

    else
    {
    NF0("There seems to be something wrong with the gate: please "
        + "make a bug report.\n");
    }

}


public void
init() 
{
    ::init();

    add_action(push_gate,       "push");
    add_action(knock_gate,      "knock");
}
