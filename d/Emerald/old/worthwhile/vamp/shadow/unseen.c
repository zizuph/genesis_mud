#include "../guild.h"
#include <stdproperties.h>

void
set_unseen(int i)
{
    if (i)
    {
        if (!unseen_level)
	{
            add_mana_drain(5);
            modify_thirst_rate(-650);
            SW->add_subloc(UNSEEN_SUBLOC, this_object());
            CP(SW, OBJ_I_INVIS, i);
	}
        else
	{
            CP(SW, OBJ_I_INVIS, i - unseen_level);
        }

        unseen_level = i;
    }
    else
    {
        if (!unseen_level)
	{
            return;
	}

        add_mana_drain(-5);
        modify_thirst_rate(650);
        SW->remove_subloc(UNSEEN_SUBLOC);
        CP(SW, OBJ_I_INVIS, -unseen_level);
        unseen_level = 0;
    }
}

static int
try_break_unseen(int lvl)
{
    if (lvl && (power_check(lvl) > 0))
    {
        return 0;
    }

    SW->catch_tell("You are revealed.\n");
    set_unseen(0);
    return 1;
}

public int
break_unseen(object breaker, int dam)
{
    int light;

    if (!unseen_level)
    {
        return 0;
    }

    light = environment(SW)->query_prop(OBJ_I_LIGHT);

    if (light < 1)
    {
        /* If the room is dark, unseen might be broken by damage */
        return (dam ? try_break_unseen(dam * 2 / 3) : 0);
    }

    /* The room is light */

    if ((environment(SW)->query_prop(ROOM_I_LIGHT) > 0) ||
        (light > unseen_level))
    {
        /* If the room is "naturally" (by default) light or if the
         * light level exceeds the unseen level, unseen is broken.
         */
        return try_break_unseen(0);
    }

    /* If the room is naturally dark and the light level is less than
     * or equal to the unseen level, unseen might be broken by damage
     */
    return (dam ? try_break_unseen(dam * 2 / 3) : 0);
}

int
query_unseen_level() { return unseen_level; }

int
query_unseen() { return !!unseen_level; }

string
show_unseen_subloc(object carrier, object for_obj)
{
    if (for_obj == carrier)
    {
        return "You are concealed in the shadows.\n";
    }

    return 0;
} 
