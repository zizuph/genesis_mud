
/* 
   Pink potion that expands your consciousness (gives you an  
   autoloading object that adds the double emote soul). 

   Coded by Maniac, 12/6/97
*/

inherit "/std/drink";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include "object.h"


void
special_effect(int n)
{
    object tp = this_player();

    if (tp->query_wiz_level()) { 
        tell_object(tp, "You'll need to add the cmdsoul `" + 
                        DOUBLE_EMOTE_SOUL + 
                        "' to yourself, wiz.\n"); 
        return;   
    } 

    if (present(DOUBLE_EMOTE_OB_ID, tp)) { 
        tell_object(tp, "Type `help double' for information.\n"); 
        return;
    } 

    seteuid(getuid()); 
//     clone_object(GELAN_OBJECTS + "de")->move(tp);

    switch (random(4)) { 
        case 0 : 
            tell_object(tp, "Hey, look at all those far out colours!\n"); 
            break;
        case 1 : 
            tell_object(tp, "Out of the corner of your eye you see pink " +
                            "gopheroos dancing merrily.\n"); 
            break;
        case 2 :
            tell_object(tp, "Like, wow, what's happening?!\n");  
            break;
        default : 
            tell_object(tp, "WooooOOOOOOOoooooiiiiiaaaaaahhhhh!!\n"); 
            break;
    } 
//    tell_object(tp, "Type `help double' for information.\n"); 
}


void
create_drink()
{
    set_name("potion");
    set_adj(({"pink", "bubbling"}));
    set_short("pink bubbling potion");
    set_long("A pink bubbling potion. Apparently this one is supposed " +
             "to expand your consciousness.\n"); 
    set_soft_amount(40);
    set_alco_amount(1);
    add_prop(HEAP_I_UNIT_WEIGHT, 330);
    add_prop(HEAP_I_UNIT_VOLUME, 330);
}


void
init()
{
    ::init();
    add_action(drink_it, "quaff");
}

