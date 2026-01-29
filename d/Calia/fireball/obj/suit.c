
/*  
    Padded leather armour for the fireball arena. 

    coder(s):   Maniac, 24/4/99

*/

inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"


void
create_armour()
{
    set_name("suit");
    set_adj(({"padded", "leather", "fireball"}));
    set_short("suit of padded leather fireball armour");
    set_pshort("suits of padded leather fireball armour");
    set_long("A suit of padded leather fireball armour that " +
             "offers protection for the body, arms " +
             "and legs. It has a pale red flame-shaped crest " +
             "on it.\n");

    set_ac(18);
    set_at(A_BODY | A_ARMS | A_LEGS);
    remove_prop(OBJ_I_VALUE); 
}


private void
tidy_up()
{
    tell_room(environment(), "A guard tidies away " +  
                             LANG_THESHORT(this_object()) + ".\n"); 
    remove_object(); 
}


void
leave_env(object from, object to)
{
    ::leave_env(from, to); 
    if (objectp(to) && !living(to)) 
        set_alarm(0.0, 0.0, tidy_up);  
}

