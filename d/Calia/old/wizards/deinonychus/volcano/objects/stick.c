/* A stick.
 * The player has to throw this stick at the top of the volcano. 
 * If the player's got enough animal handling then the pteranodon on the
 * volcano will fly away and catch the stick. Meanwhile the eggs of the
 * reptile are not guarded and the player can take the pteranodon egg.
 */

inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

#include "objects.h"

/*
 * Function name: create_object
 * Description:   The standard create routine
 * Arguments:     none
 * Returns:       nothing
 */

void 
create_object()
{
    set_name("stick");
    set_pname("sticks");
    set_short("stick");
    set_pshort("sticks");
    set_long("On the stick you see some marks of a large beak.\n");
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,250);
    add_prop(OBJ_I_VALUE,0);
}

/*****************************************************************************/

/*
 * Function name: init
 * Description:   Adds commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void 
init()
{
    add_action("stick_throw","throw");
}

/*****************************************************************************/

/*
 * Function name:  stick_throw
 * Description:    The player tries to throw the stick.
                   If the player's at the top of the volcano
                   and if the pteranodon's there too, the reptile
                   will fly away, if the player's got enough animal-handling.
 * Arguments:      str - the string describing what he wants to throw.
 * Returns:        1/0
 */

int 
stick_throw(string str)
{
    object dinosaur; /* The dinosaur that could be in the same room */
    object room; /* The room where the stick is thrown */
    object *obj; /* The things of the name stick in the inventory */    

    room = environment(TP);
    dinosaur = present("pteranodon",room);

    /* Is it this stick he's trying to throw or something else? */
    notify_fail("Throw what?\n");
    if (!sizeof(obj = FIND_STR_IN_OBJECT(str, TP)) || (obj[0] != TO))
        return 0; /* Didn't try to throw this stick or doesn't hold it */

    /* Now we look if he's in the right room. */
    if (file_name(room) != TRACK + "top"){
        write("This is not a good place to throw this stick.\n");
        return 1;
    }
    
    /* The player's in the right room. If the pteranodon's here I check
     * if the player's good enough in animal-handling to motivate it
     * to fly away and catch the stick
    /*
    else if (!dinosaur || dinosaur->query_name() == "corpse"){
        write("You throw the stick as far as you can and feel quite foolish");
        TO->move(room);
        return 1;
    }

    /* The pteranodon's in the same room */
    else if (TP->resolve_task(TASK_ROUTINE, SS_ANI_HANDL) < 0){
        write(BS("You throw the stick as far as you can, but you can't "
            + "motivate the pteranodon to fly away and catch the stick. "
            + "Maybe you should try again.\n"));
        TO->move(room);
        return 1;
    }
    else{
        write(BS("You throw the stick as far as you can. Somehow you could "
            + "catch the attention of the pteranodon because it flies up "
            + "into the air to catches the stick.\n"));
        dinosaur->fly();
        TO->remove_object();
        return 1;
    }
}

