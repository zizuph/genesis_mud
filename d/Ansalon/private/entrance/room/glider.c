#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define RDIR      "/d/Ansalon/private/entrance/room/"

int crashed = 0;
int on_balcony = 1;
int in_air = 0;
int flip_switched = 0;
int dial_turned = 0;
int button_pushed = 0;
int occupied = 0;

void
reset_kendermore_room()
{
    if (crashed)
    {
        on_balcony = 1;
        in_air = 0;
        crashed = 0;
    }
    flip_switched = 0;
    dial_turned = 0;
    button_pushed = 0;
}

void
create_kendermore_room()
{
    set_short("In a gnomish glider");
    set_long("You're in a tiny basket in a gnomish glider. Several " + 
        "dials, buttons and switches are on a panel in front of you. " + 
        "@@where_glider@@\n");
    add_item(({"forest", "green forest"}), "It is lush and thick.\n");
    add_item("panel", "It holds a number of dials, buttons and switches.\n");
    add_item("dials", "There are many dials. You could turn one if " + 
        "you wanted.\n");
    add_item("switches", "There are many switches. You could flip one if " + 
        "you wanted.\n");
    add_item("buttons", "There are many buttons. You could push one if " + 
        "you wanted.\n");

    add_cmd_item(({"dials", "dial", "one dial"}), "turn", "@@turn_dial");
    add_cmd_item(({"switches", "switch", "one switch"}), "flip", 
        "@@flip_switch");
    add_cmd_item(({"buttons", "button", "one button"}), "push",
        "@@push_button");
    set_tell_time(300);
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("A breeze wafts in from outside, giving you a " + 
        "breath of fresh air.\n");
    add_tell("A spider scurries across the panel.\n");
    add_tell("Something creaks, making you a bit uncertain about " + 
        "the safety of this machine.\n");

    add_exit(RDIR + "balcony", "out", "@@balcony_message");
    reset_kendermore_room();
}

string
turn_dial()
{
    if (dial_turned)
        return "You pick another dial and turn it. The glider makes " +
            "some strange sounds.\n";

    dial_turned = 1;

    if (flip_switched && button_pushed)
        set_alarm(0.5,0.0,"take_off");
    return "You pick a dial and turn it.\n";
}

string
flip_switch()
{
    if (flip_switched)
        return "You flip another switch at random. The glider " +
            "makes some buzzing sounds.\n";

    flip_switched = 1;

    if (dial_turned && button_pushed)
        set_alarm(0.5,0.0,"take_off");
    return "You flip a switch at random.\n";
}

string
push_button()
{
    if (button_pushed)
        return "You close your eyes and push another button. " +
            "The glider shakes a little bit.\n";

    button_pushed = 1;

    if (dial_turned && flip_switched)
        set_alarm(0.5,0.0,"take_off");
    return "You close your eyes and push a button.\n";
}


string
where_glider()
{
    if (on_balcony)
        return "The glider is resting on the balcony.";
    if (in_air)
        return "The glider is in the air.";
    if (crashed)
        return "The glider is hanging upside down in a tree.";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

int
balcony_message()
{
    if (on_balcony)
    {
        write("You leave the tiny basket and stretch your legs.\n"); 
        return 0;
    }
    if (in_air || crashed)
    {
        write("You wouldn't want to get out now!\n");
        return 1;
    }
}

void
balcony_air()
{
    string balcony;
    on_balcony = 0;
    in_air = 1;
    balcony = (RDIR + "balcony");
    balcony->glider_takeoff();
}

void
crash_desc()
{
    on_balcony = 0;
    in_air = 0;
    crashed = 1;
    TP->add_prop("_kender_i_crashed", 1);
}

void
crash_landing()
{
    string forest;
    forest = "/d/Ansalon/balifor/flotsam_forest/room/forest4s";
    if (present(TP))
    {
        tell_room(forest, "\nA strange machine comes spinning down to the " + 
            "ground. It crashes in a nearby tree, and " + QTNAME(TP) + " is " + 
            "ejected from the contraption. " +C(HE(TP)) + " lands on the " + 
            "ground with a huge grin of excitement.\n");
        set_alarm(1.0,0.0,&tell_room(forest, "The strange machine suddenly " + 
            "bursts into flame, explodes, and leaves no trace of itself.\n"));
        write("Just as the glider hits the " +
            "trees below, you are ejected from the basket by a spring " +
            "loaded seat. You land on the forest floor, slightly bruised, " +
            "but alive.\n");
        TP->move_living("M", forest,0,0);
        crashed = 1;
        return;
    }
    tell_room(forest, "\nA strange machine comes spinning down to the " + 
        "ground. It crashes in a nearby tree, bursts into flame and " + 
        "suddenly explodes, leaving no trace of itself.\n");
    crashed = 1;
}

void
take_off()
{
    string glider;
    glider = (RDIR + "glider");
    set_alarm(0.0,0.0, &tell_room(RDIR + "balcony", "The glider shakes " + 
        "a bit, and you step back when the wings start to move up and " + 
        "down.\n"));
    set_alarm(0.0,0.0, &tell_room(glider, "With your last fumbling at the " + 
        "panel, the glider shakes a bit, then its large wings start to move " + 
        "up and down.\n"));
    set_alarm(4.0,0.0, "balcony_air");
    set_alarm(4.0,0.0, &tell_room(RDIR + "balcony", "The glider lifts " + 
        "into the air, spluttering and giving off a bit of smoke.\n"));
    set_alarm(4.0,0.0, &tell_room(glider, "The machine lifts into the air, " + 
        "spluttering and giving off a bit of smoke.\n"));
    set_alarm(9.0,0.0, &tell_room(RDIR + "balcony", "The glider dives off " + 
        "the balcony, taking flight.\n"));
    set_alarm(9.0,0.0, &tell_room(glider, "You clap your hands in delight " + 
        "as the glider dives off the balcony, taking flight, regardless of " + 
        "the fact that you are probably diving to your death.\n"));
    set_alarm(12.5,0.0, &tell_room(glider, "You look around for a way to " + 
        "guide this monster machine, but can't seem to figure it out.\n"));
    set_alarm(15.0,0.0, &tell_room(glider, "You sit back and enjoy the " + 
        "ride.\n"));
    set_alarm(20.0,0.0, &tell_room(glider, "The wind brings a bug flying " + 
        "into your mouth, which you spit out in disgust.\n"));
    set_alarm(26.5,0.0, &tell_room(glider, "Uh oh! You hear some " + 
        "spluttering sounds, and smell smoke.\n"));
    set_alarm(28.0,0.0, &tell_room(glider, "The glider wobbles wildly as " + 
        "the right wing flies off!\n"));
    set_alarm(30.0,0.0, &tell_room(glider, "You start to go into a spin " + 
        "with the right wing missing!\n"));
    set_alarm(33.0,0.0, &tell_room(glider, "The excitement is almost too " + 
        "much to handle! What a story this is going to make. You briefly " + 
        "hope that you won't be telling it to Paladine!\n"));
    set_alarm(38.0,0.0, &tell_room(glider, "You're getting a bit dizzy " + 
        "with all this spinning!\n"));
    set_alarm(42.0,0.0, &tell_room(glider, "The ground is getting closer, " + 
        "and Closer and CLOSER!!\n\n"));
    set_alarm(43.0,0.0, &tell_room(glider, "CRASH!!!\n\n\n\n\n\n\n\n"));
    set_alarm(43.0,0.0, "crash_desc");
    set_alarm(43.3,0.0, "crash_landing");
}
