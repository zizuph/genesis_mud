// OBJECT:  morgul mage doll

    /* Calia Domain

    HISTORY

    [99-11-19] Created by Sheytansha

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_object()

{

    set_short("stuffed morgul mage doll");

    set_name("doll");
    add_name("mage");
    add_name("toy");

    set_long("This small stuffed doll has been made to resemble" +
        " a morgul mage. It's wearing a black hooded robe and" +
        " has dark red glass eyes set onto its white face." +
        " As you move the doll around, you hear something" +
        " rattle in its body.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 700);
    
    add_prop(OBJ_M_NO_SELL, "The merchants eyes bug out of his head" +
        " when he sees the doll! 'No way! It's bad enough having real" +
        " mages using my shop. I'm not going to start stocking a" +
        " likeness of them!'\n");

    add_item(({"robe", "black robe", "black hooded robe"}),
        "The mage's robe is fairly thick, made of a sturdy" +
        " woven canvas. It's a full length robe covering the" +
        " entire doll in the rough cloth.\n");

    add_item(({"eye", "eyes", "red glass eyes", "glass eyes"}),
        "The eyes are very peculiar indeed. As you study them, the" +
        " light refracts and bounces off the eyes making them" +
        " twinkle oddly.\n");

    add_item(({"face", "white face"}),
        "The mage's face is a blue-white shade. In" +
        " direct light it appears deathly pale, which" +
        " was probably the intention of the dollmaker.\n");

}

// FUNCTIONS

// Function:  squeeze_mage

/*

Purpose:  to show why it's bad to bug a mage

Arguments:  string indicating this mage

Returns:  0/1

*/

int
squeeze_mage(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str))

    {

        notify_fail("Squeeze what or whom?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " squeezes a " + short() +
            " tightly. The dolls face scrunches up into a" +
            " disapproving frown and its eyes begin to glow" +
            " brightly!\n");

        write("You squeeze your " + short() + " tightly." +
            " The dolls face scrunches up into a disapproving" +
            " frown and its eyes start to glow a bright red!\n");

        return 1;

    }

    return 0;

}

// Function:  shake_mage

/*

Purpose:  To make the mage do what mages do best. 

Arguments:  string indicating this mage

Returns:  0/1

*/

int
shake_mage(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str))

    {

        notify_fail("Shake what or whom?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " shakes a " + short() +
            ". A strange rattling noise is emitted, it" +
            " sounds suspiciously like a raspy cackle!\n");

        write("You shake your " + short() +
            ". You hear a strange rattling noise from within the" +
            " doll, it sounds suspiciously like a raspy cackle!\n");

        return 1;

    }

    return 0;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(squeeze_mage, "squeeze");
    add_action(shake_mage, "shake");

}
