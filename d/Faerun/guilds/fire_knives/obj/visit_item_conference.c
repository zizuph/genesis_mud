inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";


void
remove_me()
{
    remove_object();
}


void
create_object()
{
    set_name(VISIT_ITEM_NAME_CONFERENCE);
    set_adj("tiny");
    set_adj("invisible");
    
    set_short("tiny invisible visit conference obj");
    
    set_long("This is a tiny invisible visit "
    +"obj. Players with this token can visit the Fire Knives "
    +"conference room.\n");
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    add_prop(OBJ_I_INVIS, 100);

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    set_alarm(600.0, 0.0, &remove_me());
}



