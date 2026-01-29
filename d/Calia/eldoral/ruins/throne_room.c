#pragma strict_types

#include "defs.h"

inherit STDROOM;

object *on_throne,
       poltergeist;

public void create_room();
public void init();
public int do_sit(string str);
public int do_put(string str);
public void add_to_throne(object dagger);
public void leave_inv(object ob, object to);
public void summon_lord();

public void
create_room()
{
    set_short("In a throne room in the ruins of " +
        CASTLE_NAME);
    set_long("You have entered a very large room with " +
        "a high, vaulted ceiling. Long windows along " +
        "the edges of the ceiling cast rays of light " +
        "down into the center of the room. At the far " +
        "northern end of the room, the light falls " +
        "upon a huge throne carved from stone. Behind " +
        "the throne, two stone pillars stand. One is " +
        "still standing strong, but the other has " +
        "collapsed and fallen over to lean at a sharp " +
        "angle against the wall. A large, but empty " +
        "fireplace in the east wall is the only other " +
        "notable feature here.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling vaults high over your head, meeting " +
        "at a peak directly above the throne at the north " +
        "end of the room.\n");
    add_item(({"windows", "long windows"}),
        "Spaced out along the edge of the ceiling, long, " +
        "vertical windows allow light to stream in from " +
        "outside.\n");
    add_item(({"throne", "huge throne", "stone throne"}),
        "The stone throne sits, covered in dust, in the north " +
        "end of the room. Carved from a solid block of stone, " +
        "it can't be comfortable, but it looks impressive. " +
        "With a high back, topped with a carving of two " +
        "chimeras, and legs designed to look like the hind legs " +
        "of some well-muscled animal, it's a daunting sight. " +
        "You notice a dark stain down the back of the throne " +
        "is the only thing that breaks the monotony of its " +
        "solid grey colour.\n");
    add_item(({"stain", "dark stain"}),
        "It's impossible to identify, just a long, discoloured " +
        "streak down the back of the throne, as if someone with " +
        "some sort of dye on their back had sat in it and leaned " +
        "back.\n");
    add_item(({"pillars", "stone pillars"}),
        "The pillars are huge, but of a simple design. The one " +
        "to the right of the throne still stands tall, but the " +
        "other has toppled over, leaning at a precarious angle " +
        "against the wall.\n");
    add_item(({"first pillar", "left pillar"}),
        "The pillar standing to the left of the throne stands " +
        "tall, still intact and supporting the ceiling with " +
        "its smoothly-rounded bulk.\n");
    add_item(({"second pillar", "right pillar"}),
        "The pillar standing to the right of the throne has " +
        "collapsed at some time near the ceiling, and now " +
        "lies at an awkward angle, leaning against a wall.\n");
    add_item(({"walls", "wall"}),
        "The walls of the room are much like the walls in any " +
        "other part of the ruins, large blocks of cut grey stone, " +
        "meticulously assembled. Here and there along the walls, " +
        "the rusted remains of torch sconces break up the " +
        "otherwise unblemished surface of the walls.\n");
    add_item(({"sconces", "rusted sconces"}),
        "Rusted rings of iron, these objects would have once " +
        "held torches, but those days are long past.\n");
    add_item(({"fireplace"}),
        "Against the east wall stands a grand fireplace, large " +
        "enough for a short human to stand in without having to " +
        "stoop over. It stands cold, now, the last flame to burn " +
        "it having died out untold years ago.\n");

    INSIDE;

    add_exit(RUIN + "main_hall_4", "south");
}

public void
init()
{
    ::init();
    add_action(do_put, "put");
    add_action(do_put, "place");
    add_action(do_put, "lie");
    add_action(do_sit, "sit");
}

public int
do_sit(string str)
{
    notify_fail("Sit where?\n");
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, TP, "[in] / [on] [the] 'throne'"))
    {
        write("As interesting an idea as that may be, you " +
            "are overwhelmed with a strong urge to avoid " +
            "that particular activity.\n");
        return 1;
    }
    return 0;
}

public int
do_put(string str)
{
    string verb;
    object dagger;

    verb = query_verb();

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP,
        "[the] %o 'on' [seat] [of] [the] [stone] 'throne'", dagger))
        {
            notify_fail(capitalize(verb) + " what on the seat of " +
                "the throne?\n");
            return 0;
        }

    if (!CAN_SEE(TP, dagger) || !CAN_SEE_IN_ROOM(TP))
    {
        notify_fail("It is too dark to see\n");
        return 0;
    }
        
    if (dagger->move(TO))
    {
        notify_fail("You are unable to drop the " + 
            dagger->short() + ".\n");
        return 0;
    }

    add_to_throne(dagger);
    return 1;
}

public void
add_to_throne(object dagger)
{
    write("You place the " + dagger->short() + " on the " +
        "seat of the stone throne.\n");
    say(QCTNAME(TP) + " lies " + LANG_ADDART(dagger->short()) + " " +
        "upon the seat of the stone throne.\n");
    dagger->add_prop(OBJ_S_ORIG_SHORT, dagger->query_short());
    dagger->set_short(dagger->query_prop(OBJ_S_ORIG_SHORT) + 
        ", resting upon the seat of the throne");
    if (!on_throne)
        on_throne = ({dagger});
    else
        on_throne += ({dagger});
    if (poltergeist && present(poltergeist, TO))
        set_alarm(5.0, 0.0, &poltergeist->react_dagger(dagger, TP));
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (member_array(ob, on_throne) >= 0)
    {
        ob->set_short(ob->query_prop(OBJ_S_ORIG_SHORT));
        ob->remove_prop(OBJ_S_ORIG_SHORT);
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!interactive(ob))
        return;

    summon_lord();
}

public void
summon_lord()
{
    if (!poltergeist)
    {
        poltergeist = clone_object(NPC + "poltergeist");
        poltergeist->move(TO);
        poltergeist->start_poltergeist();
    }

    if (!present(poltergeist, TO))
    {
        poltergeist->move_home(TO);
    }
}   
              
