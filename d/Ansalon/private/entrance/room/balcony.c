#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_OUT;

#define RDIR      "/d/Ansalon/private/entrance/room/"

int glider_present = 1;

void
reset_kendermore_room()
{
    if (!glider_present)
    {
        tell_room(RDIR + "balcony", "A strange machine lands on the " + 
            "balcony.\n");
        glider_present = 1;
    }
}

void
create_kendermore_room()
{
    set_short("A balcony overlooking a green forest");
    set_long("You are standing on a large balcony overlooking a " + 
        "green forest. @@glider_here@@ A bell has been mounted on the " + 
        "wooden railing which encircles the balcony. A set of stairs leads " + 
        "down here. A sign is posted at the beginning of the stairs.\n");
    add_item(({"stairs", "set of stairs"}), "They look well built, perhaps " + 
        "dwarvish.\n");
    add_item("sign", "Guaranteed to be the safest way back to civilized " + 
        "lands! (Or you can take the glider, haha!)\n");
    add_item("bell", "A small bell has been mounted on the wooden railing. " + 
        "You think it must be a magical bell!\n");
    add_item(({"railing", "wooden railing"}), "It encircles the balcony, " + 
        "helping to prevent people from falling.\n");
    add_item(({"forest", "green forest"}), "It is lush and thick.\n");
    add_item("doorway", "The doorway leads back into the " + 
        "tower.\n");
    add_item(({"stone", "rough stone", "limestone"}),
        "Rough hewn blocks of limestone make up the walls and floors " + 
        "of this balcony.\n");
    add_item(({"frame", "light frame", "wooden frame", "light wooden frame",
        "cloth", "white cloth", "wings"}), "@@frame_desc");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone.\n");
    add_item(({"nuts", "bolts"}), "A few nuts and bolts lie on the floor.\n");
    add_item(({"gnomish device", "device", "gnomish glider", "glider"}),
        "@@glider_desc");
    add_item(({"dials", "buttons", "nobs"}), "@@dial_desc");
    add_item(({"basket", "tiny basket"}), "@@basket_desc");

    add_cmd_item("sign", "read", "@@read_sign");
    add_cmd_item(({"stairs", "down"}), "climb", "@@climb_down");
    add_cmd_item(({"basket", "tiny basket", "glider", "device", "machine"}),
        "enter", "@@enter_glider");
    add_cmd_item("bell", "ring", "@@ring_bell");

    set_tell_time(300);
    add_tell("The sound of something large moving below you can " + 
        "be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A breeze ruffles your hair and clothes, refreshing you.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_exit(RDIR + "tower", "in", "@@balcony_message");
    reset_kendermore_room();
}

string
read_sign()
{
    return "Guaranteed to be the safest way back to civilized " +
        "lands! (Or you can take the glider, haha!)\n";

}

string
ring_bell()
{
    write("You ring the bell loudly.\n");
    set_alarm(1.0,0.0, "reset_kendermore_room");
    return "";
}

void
glider_takeoff()
{
    glider_present = 0;
}

string
enter_glider()
{
    if (glider_present)
    {
        tell_room(RDIR + "glider", QCTNAME(TP) + " hops into the basket, " + 
            "a big grin on " + HIS(TP) + " face.\n");
        TP->move_living("M", RDIR + "glider", 1, 0);
        tell_room(RDIR + "balcony", QCTNAME(TP) + " hops into the basket, " + 
            "a big grin on " + HIS(TP) + " face.\n");
        return "You hop into the basket, tingling with excitement.\n";
    }
    else
        return "The glider isn't here right now!\n";
}

string
climb_down()
{
    object mask;
    string forest;
    forest = "/d/Ansalon/balifor/flotsam_forest/room/forest4s";
    TP->move_living("down the stairs", forest, 1, 1);
    if (mask = present("_kender_quest_mask_", TP))
    {
        mask->remove_object();
        return "Trying to alleviate the boredom of the very safe stairs, " + 
            "you skip down backwards, slip, and rip the mask that " + 
            "Merldon gave you. When you look back, the stairs are gone, " + 
            "replaced by forest.\n";
    }
    return "You waltz down the stairs and feel a slight dizziness as " + 
        "you step into the forest. When you turn back, the stairs are " + 
        "gone.\n";
}

string
dial_desc()
{
    if (glider_present)
        return "You're not sure what each dial, button and nob do " + 
            "specifically, but they probably control the glider.\n";
    else
        return "The glider isn't here right now!\n";
}

string
basket_desc()
{
     if (glider_present)
         return "You can enter the basket if you dare! It is, after " + 
             "all a gnomish machine.\n";
     else
         return "The glider isn't here right now!\n";
}

string
frame_desc()
{
    if (glider_present)
        return "The wooden frame of the glider seems to have been made " + 
            "of some very strong, yet very light wood. It is covered in " + 
            "white cloth.\n";
    else
        return "The glider isn't here right now!\n";
}

string
glider_desc()
{
    if (glider_present)
        return "This device has a light wooden frame covered with cloth. " + 
            "You can enter a tiny basket under the wings. In the basket " + 
            "are several different dials, buttons and nobs.\n";
    else
        return "The glider isn't here right now!\n";
}

string
glider_here()
{
    if (glider_present)
        return "A very gnomish looking device has been left on the floor " + 
            "here. It appears to be a glider, how exciting!";
    return "A few nuts and bolts lie on the floor, as if some gnomish " + 
        "device used to sit here.";
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
    write("You leave the fresh air behind, and step into the dusty " + 
        "workroom.\n");
    return 0;
}
