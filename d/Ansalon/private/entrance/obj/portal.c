/* Portal for Kender Quest, Gwyneth, August 1999 */

inherit "/std/object";
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <wa_types.h>

#define QROOM "/d/Ansalon/private/entrance/room/"
#define KENDER_AM_QUESTING "_kender_am_questing"

void
create_object()
{
    set_name("portal");
    add_name("_kender_quest_portal");
    set_adj("magic");
    set_short("magic portal");
    set_long("It's a mysterious tear in the fabric of space.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_GET, "How could you possible get a magic portal?\n");
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_INVIS, 1);
    add_cmd_item(({"portal", "magic portal", "through portal", 
        "through magic portal", "into portal", "into magic portal"}), 
        ({"enter", "step", "jump"}), "@@enter_portal");
}

string
enter_portal()
{
    object head_gear;
    if (TP->query_race_name() != "kender")
        return ("You take a step towards the portal, but a terrible " + 
            "feeling of fear sweeps over you, and you retreat.\n");
    if (TP->check_bit("ansalon", 3, 0))
        return("Why would you want to go there again? Go find something " + 
            "new to explore!\n");
    if (!TP->query_prop(KENDER_AM_QUESTING))
        return("You take a step towards the portal, but suddenly don't " + 
            "find it as interesting as you originally did.\n");

    head_gear = TP->query_armour(TS_HEAD);

    if (!head_gear->id("_kender_quest_mask_"))
        return("A small voice whispers in your head... 'The mask! Wear " + 
            "the mask!'\n");
    else
    {
        write("You leap into the magic portal, feeling a tingling up " + 
            "your spine as you hurtle through the very fabric of time " + 
            "and space. You feel mounting excitement as you wonder where " + 
            "this portal will land you.\n");
        say(QCTNAME(TP) + " makes a running leap, and disappears into " + 
            "a magic portal.\n");
        tell_room(QROOM + "q1", "A sharp crackling sound booms loudly " + 
            "above you.\n");
        set_alarm(5.0,0.0,"portal_message");
        TP->move_living("M", QROOM + "q1", 1, 1);
    }
    return "";
}

void
portal_message()
{
    /* Message while hurtling through the portal. */
    write("\n\nA bolt of lightning shoots out from nowhere and " + 
        "strikes not two feet away from you, leaving your ears " + 
        "ringing and your eyes blinded for a few moments. You were " + 
        "lucky...this time.\n\n\n");
    set_alarm(8.0,0.0, &write("\n\nAn enormous and exceedingly " + 
        "wicked looking beast appears from nowhere and rushes " + 
        "towards you, gaping jaws wide. Just as he is about to " + 
        "close his jaws over " + 
        "you, he explodes into pieces with a loud suffering " + 
        "wail.\n\n\n"));
    set_alarm(16.0,0.0,"land_message");
}

void
land_message()
{
    /* Landing message, and move to room. */
    write("Your journey through the magic portal comes to an end as " + 
        "you are flung out into the air. You land with a heavy thud " + 
        "on a cold stone floor.\n");
    tell_room(QROOM + "q3", QCTNAME(TP) + " comes flying out of " + 
        "thin air right above you. " + HE(TP) + " lands with a heavy " + 
        "thud on the ground.\n");
    TP->move_living("M", QROOM + "q3", 1, 0);
}

