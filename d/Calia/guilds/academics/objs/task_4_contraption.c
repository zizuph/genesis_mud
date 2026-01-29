/* 
 * Contraption for Task 4 (Resistance) for Academics
 *
 * This contraption allows the student to learn a bit about resistance.
 *
 * Created by Petros, December 2009
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

// Global Variables
public string   owner_name;
public int      state = 1;
public int      cast_alarm;
public string * cast_messages = ({ 
    "You close your eyes and focus on the elemental energies.",
    "Instinctively, you lash out at the rack and a bolt of raw elemental "
  + "energy flies from your fingertips towards the rack!",
    "The bolt of energy crackles as it slams into the rack and the contraption "
  + "upon it. The first plate shatters and falls to the ground! "
  + "The second plate, still twirling on the pins seems somewhat "
  + "cracked and bent. The third plate looks completely unscathed!",
    "You take the contraption from the rack."
     });
     
// Prototypes
public void     display_cast_message(object player, string * messages);

void
create_object()
{
    set_name("contraption");
    add_name("academic_resistance_contraption");
    set_adj( ({ "three-plated", "metal" }) );
    set_long("@@long_desc");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

public void
set_owner_name(string name)
{
    owner_name = name;
}

public string
query_owner_name()
{
    return owner_name;
}

// There are different states
// 1. Initial, non-resistant state
// 2. Resistant state, before casting
// 3. Resistant state, after casting

public int
query_state()
{
    return state;
}

public void
set_state(int num)
{
    state = num;
}

public string
long_desc()
{
    string description;
    description = "This is by no means the normal master workmanship "
        + "of Bubba Hammerhead. This contraption consists of an old "
        + "metal pole with 3 rough but even-sized metal plates "
        + "attached to it. ";    
    switch (state)
    {
    case 1:
        description += "You should give this to Amjal.\n";
        break;
    
    case 2:
        description += 
             "You notice each of the plates glow, the first one very faintly, "
            + "the second one somewhat brightly and the last one gives off a "
            + "bright shine. You should go to the practice yard, <hang "
            + "contraption on rack>, and then <cast hydrokine on rack>.\n"; 
        break;
    
    case 3:
        description += "The contraption has clearly affected by your "
            + "experiment! The pole is frozen and cracked and the pins "
            + "seems ready to crumble. The first metal plate, "
            + "however, is completely missing! The second plate is rather "
            + "cracked and bent. The third plate hardly looks damaged! "
            + "Give this to Amjal right away before the whole thing falls "
            + "apart!\n";
        break;

    default:
        description += "\n";
        break;
    }
    
    return description;
}

public void
init()
{
    ::init();
    
    add_action("cast_experiment", "cast");
    add_action("hang_contraption", "hang");
    add_action("retrieve_contraption", "retrieve");
}

public int
in_practice_yard(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    object room = environment(player);
    if (MASTER_OB(room) == ACADEMIC_SCHOOL + "practiceyard")
    {
        return 1;
    }
    
    return 0;
}

public int
cast_experiment(string str)
{
    object player = this_player();
    if (!in_practice_yard(player))
    {
        return 0;
    }
    
    if (!strlen(str) || str != "hydrokine on rack")
    {
        notify_fail("Perhaps you should <cast hydrokine on rack>?\n");
        return 0;
    }
    
    if (get_alarm(cast_alarm))
    {
        write("You are already in the middle of casting!\n");
        return 1;
    }
    
    if (!query_no_show_composite())
    {
        write("You should probably hang the contraption on "
            + "the rack before you try casting at it!\n");
        return 1;
    }
    
    string * messages = cast_messages + ({ });
    cast_alarm = set_alarm(0.0, 0.0, &display_cast_message(player, messages));
    
    return 1;
}

public void
display_cast_message(object player, string * messages)
{
    string message = messages[0];
    messages = messages[1..];
    player->catch_tell(message + "\n");
    if (sizeof(messages))
    {
        cast_alarm = set_alarm(4.0, 0.0, &display_cast_message(player, messages));
    }
    else
    {
        set_state(3);
        unset_no_show_composite();
    }    
}

public int
hang_contraption(string str)
{
    object player = this_player();
    if (!in_practice_yard(player))
    {
        return 0;
    }

    if (!strlen(str) || str != "contraption on rack")
    {
        notify_fail("Perhaps you should <hang contraption on rack>?\n");
        return 0;
    }
    
    if (query_no_show_composite())
    {
        notify_fail("The contraption is already hanging on the rack!\n");
        return 0;
    }

    switch (state)
    {
    case 1:
        write("You should take the contraption to Amjal first!\n");
        break;
    
    case 2:
        write("You quickly find an empty practice rack and hang the "
            + "contraption on it horizontally. You step back. You may "
            + "now <cast hydrokine on rack>.\n");
        set_no_show_composite(1);
        break;
    
    case 3:
        write("You better take the contraption back to Amjal soon before "
            + "it falls apart!\n");
        break;        
    }
    return 1;
}

public int
retrieve_contraption(string str)
{
    object player = this_player();
    if (!in_practice_yard(player))
    {
        return 0;
    }

    if (!strlen(str) || str != "contraption from rack")
    {
        notify_fail("Perhaps you should <retrieve contraption from rack>?\n");
        return 0;
    }
    
    if (get_alarm(cast_alarm))
    {
        write("You are in the middle of casting! You can't retrieve the "
            + "contraption right now.\n");
        return 1;
    }

    if (!query_no_show_composite())
    {
        notify_fail("The contraption isn't hanging on the rack!\n");
        return 0;
    }

    write("You retrieve the contraption from the rack.\n");
    unset_no_show_composite();
    return 1;
}
