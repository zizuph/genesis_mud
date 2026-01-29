
/* 
   The corpse of the polymorph demon, part of the polymorph quest.

   Coded by Maniac 31/8/95
*/

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "obj.h"
#include POLYMORPH_QUEST

string *valid_slayer = ({ });

void
create_object()
{
    set_name("corpse");
    add_name("monstrosity"); 
    add_name(CORPSE_NAME);
    set_adj(({"many-eyed", "tentacled"}));
    set_short("corpse of a many-eyed tentacled monstrosity");
    set_pshort("corpses of many-eyed tentacled monstrosities"); 
    set_long("The corpse of a many-eyed tentacled monstrosity. You find yourself " +
             "feeling very relieved that the creature is no longer " +
             "alive. You feel that you should <report> back to Gamalus " +
             "now.\n"); 
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE, 0); 
    add_prop(OBJ_M_NO_SELL, 1);
    set_alarm(1000.0, 0.0, "decompose");
    set_alarm(10.0, 0.0, "kroug_message");
}



/* Kroug knows when his demon has been defeated */
void
kroug_message()
{
    int i;

    for (i = 0; i < sizeof(valid_slayer); i++)
       find_player(valid_slayer[i])->catch_msg("An apparition of Kroug " +
                    "appears to you.\nHe tells you: I will remember " +
                    "you, fool.\nThe figure then disappears.\n"); 
}



/* 
   Record identity of a player who is on this quest that 
   was instrumental in killing the demon 
*/
void
add_valid_slayer(string str)
{
   if (member_array(str, valid_slayer) == -1)
       valid_slayer += ({str});
}


/* Returns 1 if player was a valid slayer of the demon */
int
query_valid_slayer(string str)
{
   if (member_array(str, valid_slayer) > -1)
        return 1;
   else 
        return 0;
}


/* Corpse decays to dust if not returned to Gamalus quick enough. */
void
decompose()
{
    object e = environment(this_object());
    if (living(e))
        e->catch_msg("The " + short() + " decays into dust.\n");
    else if (e->query_prop(ROOM_I_IS))
        tell_room(e, "The " + short() + " decays into dust.\n");

    remove_object();
}

