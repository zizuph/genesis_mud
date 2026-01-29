/* Updated desription to change it some from its creation 2003
 * when the quest was closed due to the climber part being 
 * broken (?). opened up this quest as a follow up on re-opening
 * the climber.  And I kept this rusty version since it is a bit
 * interesting to have the key rust in regards of elves living 
 * for a long time...    
 *                            2008-05-05, Toby
 */

inherit "/std/key";
#include <stdproperties.h>

int handle_with_care;

create_key()
{
    set_name("key");
    set_pname("keys");
    set_adj("rusty");
    add_adj("small");
    set_short("small rusty steel key");
    set_pshort("small rusty steel keys");
    set_long("This small steel key is very rusty. In fact, it is almost as one "+
             "small piece of rust. You better handle it with extreme care "+
             "otherwise it would most certainly break.\n");
    add_prop(OBJ_I_WEIGHT,5); /* 5 grams */
    add_prop(OBJ_I_VOLUME,1); /* 1 ml    */
    add_prop(OBJ_I_VALUE,5);  /* 5 cc    */

    set_key("_rusty_gcaves_quest_key_");

    handle_with_care = 0;
}

void
enter_env(object dest, object old)
{
    handle_with_care += 1;
    if(handle_with_care == 3)
	set_alarm(itof(30 + random(60)), 0.0, "destruct_key");
    return;
}

void
destruct_key()
{
    object room; 

    room = this_object();
    while(!(room=environment(room))->query_prop(ROOM_I_IS));
    tell_room(room, "The small rusty key suddenly turns into dust.\n");
    remove_object();
}

