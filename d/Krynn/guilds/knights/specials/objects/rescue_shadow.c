/*
 * Knight Rescue Shadow
 *
 * When a Knight rescues someone, that someone receives a period of time
 * where any attacks on them are turned back to their rescuer.
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
public mapping rescue_data = ([ ]);

public int
has_knight_rescue_shadow()
{
    return 1;
}

public void
remove_knight_rescue_shadow()
{
    remove_shadow();
}

public void
add_rescue_event(object knight, object attacker)
{
    rescue_data[file_name(attacker)] = ({ knight, time() + RESCUE_PROTECT_TIME });
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
    object attacker, player, knight;
    int expire_time;
    
    if (prop == OBJ_M_NO_ATTACK)
    {
        attacker = this_player();
        player = query_shadow_who();
        if (IN_ARRAY(file_name(attacker), m_indices(rescue_data)))
        {
            knight = rescue_data[file_name(attacker)][0];
            expire_time = rescue_data[file_name(attacker)][1];
            if (time() <= expire_time)
            {
                // Person is still being protected.
                return "You move to attack " 
                    + player->query_the_name(attacker) + ", but "
                    + knight->query_the_name(attacker) + " stands "
                    + "firmly in your way.\n";
            }
        }
        
        // If we're just returning, we should do a check through
        // the data to see if this shadow is no longer necessary.
        foreach (string key : m_indices(rescue_data))
        {
            expire_time = rescue_data[key][1];
            if (expire_time < time())
            {
                m_delkey(rescue_data, key);
            }
        }
        if (sizeof(m_indices(rescue_data)) == 0)
        {
            set_alarm(0.0, 0.0, &remove_knight_rescue_shadow());
        }
    }
    
    return shadow_who->query_prop(prop);
}
