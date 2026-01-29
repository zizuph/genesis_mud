/*
 *  IGARD_WALL + "gate_tun6.c"
 *
 *  Behind the northern tunnel gate of Isengard.
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

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();
public string      exa_inscription();
public int         push_gate(string str);
public int         arrow_attack();
public int         permit_exit();

object             actor;

string
long_desc()
{
    return "You are standing in a broad tunnel within the great "
    + "ring wall of Isengard. The tunnel is extremely wide and could "
    + "accomodate an army in which twenty soldiers marched abreast. "
    + "Firelight flickers off the stone walls and floor from massive "
    + "iron lanterns set into small alcoves along the way. Two mighty "
    + "doors of iron stand to the north, set beneath a great stone "
    + "arch, while the tunnel itself leads away to the south. Two "
    + "small doorways open to the west and east.\n";
}


public void
create_gondor()
{
    set_short("Behind the northern tunnel gate");
    set_long(&long_desc());

    wall_add_items();

    add_item(({"inscription", "weathered inscription"}), &exa_inscription());
    add_cmd_item(({"inscription", "weathered inscription"}), "read",
        &exa_inscription());

    add_item(({"room", "area", "surroundings", "place", "tunnel"}), long_desc);

    add_item(({"door", "doors", "gate", "gates", "exit",
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
    add_item(({"doorway", "doorways"}), "It is difficult to see what "
        + "is behind them from here. Something about them warns you to "
        + "be careful outside them.\n");

    add_exit(IGARD_WALL + "gate_tun5",           "south");
    add_exit(IGARD_WALL + "tun_guardrm3",        "west");
    add_exit(IGARD_WALL + "tun_guardrm4",        "east");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


public string
exa_inscription()
{
    return "The inscription reads:\n"
+" ___________________________________________________________\n"
+"|o_________________________________________________________o|\n"
+"||                                                         ||\n"
+"|| Friends need only push on the gate to enter the plain   ||\n"
+"|| of Isengard. All others face the peril they are due.    ||\n"
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

    write("Arrows fly into the area from somewhere nearby. Many skitter "
        + "harmlessly across the ground, but several of them find their "
        + "mark. Ouch!\n");
    tell_room(environment(actor), "Arrows fly into the area from somewhere "
        + "nearby. Many skitter harmlessly across the ground, but several of "
        + "them strike " + QTNAME(TP) + ".\n", 
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

    permit_exit();

    return 1;
}


int
permit_exit()
{
    actor = TP;

    write("You push on the massive iron doors with both hands and they "
        + "swing easily upon their hinges. You quickly slip outside as the "
        + "doors close behind you.\n\n");
    tell_room(environment(actor), QCTNAME(actor) + " pushes on the massive "
        + "iron doors with both hands. The doors open effortlessly and "
        +  PRONOUN(actor) + " slips quickly outside.\n"
        + "The doors return to their original position.\n", 
        ({actor}));
    tell_room(IGARD_PLAIN + "south_gate", "The great iron doors open for a "
        + "moment and " + QTNAME(TP) + " slips quickly outside.\n"
        + "The doors return to their original position.\n");

    TP->move_living("M", IGARD_PLAIN + "south_gate", 1, 0);

    return 1;
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

    write("A voice from behind shouts at you: Read the inscription, "
        + "you fool! Do you think we have all day to be answering the "
        + "door?\n");
    tell_room(environment(actor), "A voice from behind shouts at " 
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
        write("A voice from behind shouts at you: Enemy of Isengard, "
            + "flee whilst you can!\n");
        tell_room(environment(actor), "A voice from behind shouts at " 
            + QTNAME(actor) + ": Enemy of Isengard, flee whilst you can!\n", 
            ({actor}));
        arrow_attack();
        return 1;
        }

        if (FRIEND)
        {
        write("A voice from behind shouts at you: Hmm, there is still "
            + "something about you that does not ring true, stranger. "
            + "You may pass, but we are still suspicious of you!\n");
        tell_room(environment(actor), "A voice from behind shouts at " 
            + QTNAME(actor) + ": Hmm, there is still something about you "
            + "that does not ring true, stranger. You may pass, but we are "
            + "still suspicious of you!\n", 
            ({actor}));
        permit_exit();
        return 1;
        }

        else
        {
        write("A voice from behind shouts at you: You have no "
            + "business in Isengard, stranger. Begone!\n");
        tell_room(environment(actor), "A voice from behind shouts at " 
            + QTNAME(actor) + ": You have no business in Isengard, "
            + "stranger. Begone!\n", 
            ({actor}));
        arrow_attack();
        return 1;
        }

    }

    if (BADDIE)
    {
        if (ENEMY)
        {
        write("A voice from behind shouts at you: Traitor of Isengard, "
            + "you are no longer welcome here! Begone!\n");
        tell_room(environment(actor), "A voice from behind shouts at " 
            + QTNAME(actor) + ": Traitor of Isengard, you are no longer "
            + "welcome here! Begone!\n", ({actor}));
        arrow_attack();
        return 1;
        }

        else
        {
        write("A voice from behind shouts at you: Friend "
            + "of Isengard, you may pass.\n");
        tell_room(environment(actor), "A voice from behind shouts at " 
            + QTNAME(actor) + ": Friend of Isengard, you may "
            + "pass.\n", ({actor}));
        permit_exit();
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

