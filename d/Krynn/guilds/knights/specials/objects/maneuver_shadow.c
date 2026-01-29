/*
 * Knight Maneuver Shadow
 *
 * When a Knight maneuvers his steed away, he essentially rescues his
 * steed from all attackers. There is a period of time where his
 * attackers can no longer attack the horse.
 *
 * Created by Petros, November 2008
 */
 
#include <stdproperties.h>
#include <std.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
// Mapping from Attacker => Defender, Time
public int  expire_time = 0;

public int
has_knight_maneuver_shadow()
{
    return 1;
}

public void
remove_knight_maneuver_shadow()
{
    remove_shadow();
}

public void
set_maneuver_duration(int duration)
{
    if (expire_time != 0)
    {
        // Can only set the duration once.
        return;
    }
    
    expire_time = time() + duration;
    set_alarm(itof(duration), 0.0, &remove_knight_maneuver_shadow());
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    object attacker, steed, knight;
    object * riders;
        
    if (prop == OBJ_M_NO_ATTACK)
    {
        attacker = this_player();
        steed = query_shadow_who();
        riders = steed->query_riders();    
        if (time() <= expire_time && pointerp(riders) && sizeof(riders) > 0)
        {
            knight = riders[0];
            // Steed is still being protected.
            return "You attempt to strike the " + steed->steed_short()
                + ", but " + knight->query_the_name(attacker) + " spurs " 
                + POSSESSIVE(knight) + " " + steed->steed_short() 
                + " forward and whirls around, facing you head on.\n";
        }
    }
    
    return shadow_who->query_prop(prop);
}
