
/* 
      Box which people can purchase pink potions from.        
      The potions give you a permanent double emote soul 
      effect when quaffed. 

      Coded by Maniac@Genesis, 13/6/97
 */ 

inherit "/std/object"; 

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <files.h>
#include "object.h"

void
create_object()
{
    set_name("box");  
    set_adj(({ "large" ,"tin"})); 
    set_long("A large tin box. It has a coin slot on it and " +
             "some kind of tube just below it. A sign below the " +
             "slot reads `For sale: Potions that expand your consciousness! " +
             "Just insert one silver coin!'\n"); 
    add_item("slot", "It's a slot for silver coins.\n"); 
    add_item("tube", "Perhaps the box dispenses potions in an unusual way.\n"); 
    add_prop(OBJ_I_WEIGHT, 50000);  
    add_prop(OBJ_I_VOLUME, 50000); 
    add_prop(OBJ_M_NO_GET, "The box is fixed in place.\n");  
}


int
do_insert(string str)
{
    object ob, tp;

    tp = this_player(); 

    notify_fail("Insert silver coin in slot?\n"); 

    if (!stringp(str)) 
        return 0;

    if (!parse_command(str,({ }),"[one] [silver] 'coin' 'in' 'slot' / 'box'")) 
        return 0;

    ob = present("silver coin", tp); 
    if (!objectp(ob) || (function_exists("create_heap", ob) != COINS_OBJECT)) {
        notify_fail("You don't have any silver coins!\n"); 
        return 0;
    } 

    ob->set_heap_size(ob->num_heap()-1); 

    seteuid(getuid()); 
    ob = clone_object(GELAN_OBJECTS+"pink_potion"); 
    write("You put a silver coin in the slot of the tin box.\n");        
    say(QCTNAME(tp) + " puts a silver coin in the slot of the tin box.\n"); 
    tell_room(environment(), "A series of clicking noises emanate from " +
                             "box. Suddenly " + LANG_ASHORT(ob) + " comes " +
                             "flying out!\n"); 

    if (ob->move(tp)) { 
        write("You fail to catch " + LANG_THESHORT(ob) + ", which " +
              "smashes on the floor.\n"); 
        say(QCTNAME(tp) + " fails to catch " + LANG_THESHORT(ob) + 
            ", which smashes on the floor.\n"); 
        ob->remove_object(); 
        return 1;
    } 
    write("You catch " + LANG_THESHORT(ob) + ".\n");  
    say(QCTNAME(tp) + " catches " + LANG_THESHORT(ob) + ".\n"); 
    return 1;
}

void
init()
{
    ::init(); 
    add_action(do_insert, "insert"); 
    add_action(do_insert, "put"); 
}

