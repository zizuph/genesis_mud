
/*  
    Hardened leather fireball helm. 

    coder(s):   Maniac, 24/4/99
*/

inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"


void
create_armour()
{
    set_name("helm");
    set_adj(({"hardened", "leather", "fireball"}));
    set_short("hardened leather fireball helm");
    set_pshort("hardened leather fireball helms");
    set_long("A hardened leather helm that offers " +
             "good protection for the head in fireball " +
             "games. It has a pale red flame-shaped crest " +
             "on it.\n"); 

    set_ac(18);
    set_at(A_HEAD);
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

