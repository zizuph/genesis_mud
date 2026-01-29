/*
    This is a test spell object. Used to test SCoP spells as they
    are recoded, before adding them to the guild.

    Bishop of Calia, April 2004.
 
*/


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("nerfbat");
    add_name("scop_college_test");
    set_short("conspicuous nerfbat");
    
    set_long("This nerfbat is an object that can be used to test the Calian" +
        " riposte special. The command 'start_test' will clone the riposte" +
        " shadow and add it to you, 'stop_test' removes the shadow again.\n");
        
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL,1);
   
}

int
test_riposte(string str)
{   
    object shadow;
 
    setuid();
    seteuid(getuid());
 
    shadow = clone_object("/d/Calia/palace/specials/riposte_test");
      
    shadow->shadow_me(this_player());
    
    return 1;
}

int 
stop_riposte_test(string str)
{
   
    setuid();
    seteuid(getuid());    
    this_player()->remove_riposte_shadow();
    
    return 1;
}

init()
{
    ::init();
    add_action(test_riposte,"start_test");
    add_action(stop_riposte_test,"stop_test");
}
