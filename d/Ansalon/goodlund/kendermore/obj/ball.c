/* Coloured ball for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

/* Randomizes the ball colour */

void
create_object()
{
    set_name("ball");
    add_name("junk");
    set_adj("big");
    add_adj("bouncy");
    set_long("It's a brightly coloured ball. It looks fun to play with! " + 
        "You could roll it on the ground, throw it in the air, bounce it " + 
        "on the ground, or (if you are a wizard) throw it to someone else.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 15);
    add_cmd_item("ball", "bounce", "@@bounce_ball");
    add_cmd_item("ball", "roll", "@@roll_ball");
}

string
bounce_ball()
{
    NF("Bounce what?\n");
    write("You bounce the big bouncy ball on the ground.\n");
    say(QCTNAME(TP) + " bounces the big bouncy ball on the ground.\n");
    return "";
}

string
roll_ball()
{
    NF("Roll what?\n");
    write("You roll the big bouncy ball around on the ground.\n");
    say(QCTNAME(TP) + " rolls the big bouncy ball around on the ground.\n");
    return "";
}

int
throw_item(string ob)
{
    string receiver;
    object aball;
    if ((ob == "ball") || (!ob))
    {
        write("You throw the big bouncy ball into the air, catching it " + 
            "again easily.\n");
        say(QCTNAME(TP) + " throws the big bouncy ball into the air, " + 
            "catching it again easily.\n");
        return 1;
    }

    receiver = find_living(ob);

    if ((ob) && (TP->query_wiz_level()) && (receiver))
    {
        write("You send the big bouncy ball spinning and bouncing away.\n");
        receiver->catch_msg(QCTNAME(TP) + " bounces a big bouncy ball in " + 
            "your direction, which you easily catch.\n", TP);
        setuid();
        seteuid(getuid());
        aball = clone_object("/d/Ansalon/goodlund/kendermore/obj/ball");
        aball->move(receiver);
        set_alarm(1.0,0.0,"rem_ball");
        return 1;
    }

    if (!TP->query_wiz_level())
    {
        write("You try to throw the ball away, but you fumble, barely " + 
            "managing to catch it yourself again.\n");
        say(QCTNAME(TP) + " almost drops a big bouncy ball.\n");
        return 1;
    }

    write("Throw to whom?\n");
    return 1;
}

void
rem_ball()
{
    TO->remove_object();
}

void
init()
{
    ::init();
    add_action(throw_item, "throw");
}
