/*
 *  RANGERS_ITH_DIR + "i_drop_tun.c"
 *
 *  Temporary room for travelling to RoI droproom.
 *
 *  Coded by Alto, 29 March 2002
 *
 */
inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* Prototypes */
public string      long_func();
public int         start_tunnel(object actor);
public int         move_tunnel(object actor);
public int         exit_tunnel(object actor);
public int         remove_excess_item(object ob);

/* Global Variable */

public void
create_gondor()
{
    set_short("in a dark tunnel");
    set_long(&long_func());

    add_item(({"tunnel", "room", "dark tunnel"}), &long_func());
    add_item(({"cart", "wood", "planks", "iron"}), "The cart is made "
        + "from planks of wood bound with iron. It seems very sturdy.\n");
    add_item(({"team", "horse", "horses"}), "Great and swift horses are "
        + "hitched to the cart and draw it along the tunnel at "
        + "incredible speed.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_MAGIC, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    reset_room();
}


public string
long_func()
{
    string  longtxt;

    longtxt = 
        "Although the darkness makes it difficult to see beyond a "
        + "short distance, you sense that the tunnel around you stretches "
        + "through a vast expanse ahead. The cart in which you stand "
        + "crashes and rattles along behind a team of huffing and "
        + "snorting horses. Wind roars and howls through the tunnel.\n"; 

    return longtxt;
}


public int
move_tunnel(object actor)
{
    set_alarm(2.0, 0.0, &actor->catch_tell("Hands in the "
        + "dark force you with great urgency into a cart "
        + "hitched to several stamping and huffing horses.\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("The horses leap forward!\n"));
    set_alarm(7.0, 0.0, &actor->catch_tell("The cart strikes a large " 
        + "bump and you are nearly thrown off!\n"));
    set_alarm(10.0, 0.0, &actor->catch_tell("Wind howls along the "
        + "tunnel and flattens you against the back of the cart.\n"));
    set_alarm(15.0, 0.0, &actor->catch_tell("Reaching a sudden bend "
        + "in the tunnel, the horses turn quickly, nearly upsetting "
        + "the cart!\n"));
    set_alarm(20.0, 0.0, &actor->catch_tell("A light appears far "
        + "ahead in the distance.\n"));
    set_alarm(22.0, 0.0, &actor->catch_tell("The horses swerve "
        + "and you are thrown from the cart! After bouncing "
        + "further along the tunnel, you eventually "
        + "roll to a stop.\n"));
    return 1;

}


public int
exit_tunnel(object actor)
{

    actor->catch_tell("You dust yourself off and look around.\n");
    tell_room(environment(actor), QCTNAME(actor) + " is thrown from "
        + "the cart!\n", actor);
    tell_room(RANGERS_ITH_DIR + "start", QCTNAME(actor) + " suddenly rolls "
        + "into the room from the tunnel.\n", actor);
    actor->move_living("M", RANGERS_ITH_DIR + "start", 1, 0);
    return 1;
}


int
start_tunnel(object actor)
{
    move_tunnel(actor);
    set_alarm(23.0, 0.0, &exit_tunnel(actor));        
    return 1;
}



public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_tunnel(ob);
        return;
    }

    set_alarm(2.0, 0.0, &remove_excess_item(ob));
}


public int
remove_excess_item(object ob)
{
    string excess;

    excess = capitalize(LANG_THESHORT(ob));
    tell_room(environment(ob), excess + " falls out of the cart "
        + "and disappears into the darkness stretching out behind you.\n");
    ob->remove_object();
    return 1;
}

