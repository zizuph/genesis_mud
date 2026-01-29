/*
 * Gnomish Sun-Powered fan
 *
 * This fan is a gnomish gizmo sold by gnomes to help adventurers
 * cool themselves whenever they are in the sun.
 * It is powered completely by sunlight. When the sun is present,
 * the fan will be powered and provide cooling. This uses the Genesis
 * Timekeeper module to detect whether there is sunlight across any
 * domain.
 *
 * Created by Petros, October 2009
 *
 * Modification History:
 *   - Nov 1 2009 (Gorboth): Altered text artwork to include fan.
 *                           Made it impossible to use indoors.
 *                           Modified activation text to include fan.
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

// Defines
#define GENESIS_TIMEKEEPER  "/d/Sparkle/area/city/lib/genesis_timekeeper"

// Prototypes
public string   describe_fan();
public int      disassemble(string str);
public int      display_times(string str);

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("fan");
    add_name( ({ "_gnomish_sunpowered_fan", "contraption" }) );

    add_adj( ({ "gnomish" }) );
    
    set_long(describe_fan);
/*
    add_prop(OBJ_I_NO_DROP, "The gnomish fan is so useful, why would "
        + "you want to drop it? You can <disassemble> it "
        + "if you want to get rid of it.\n");
*/
    add_prop(OBJ_I_NO_SELL, "You'd better keep it. Too useful!\n");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, 590);
    
    add_item( ({ "squares", "black squares", "exterior" }),
              "The black squares feel a bit warm to the touch whenever "
            + "the sunlight strikes it. You gather it must have something "
            + "to do with powering the fan blades.\n" );
    
    add_item( ({ "fan blade", "fan blades" }),
              "The gnomish contraption's main purpose seems to be to "
            + "spin these fan blades to provide you with a breeze. You "
            + "think the black squares might have something to do with "
            + "it.\n" );
    
    add_item( ({ "slot", "coin slot" }),
              "The slot looks like one can <insert> a coin into it. But "
            + "who can predict what gnomish contraptions do?\n" );
    
    setuid();
    seteuid(getuid());
}

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(disassemble, "disassemble");
    add_action(display_times, "insert");
}


/*
 * Function name:        query_auto_load
 * Description  :        allow this to always start with the player
 */
public string
query_auto_load(void)
{
    return MASTER + ":";
} /* query_auto_load */

public int
disassemble(string str)
{
    notify_fail("Disassemble what?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    object target = PARSE_COMMAND_ONE(str, this_player(), "[the] %i");
    if (!objectp(target)
        || target != this_object())
    {
        return 0;
    }
    
    write("You disassemble the " + short() + " and the parts crumble "
        + "into dust.\n");
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public string
describe_fan()
{
    string long_desc = "You are looking at a complicated piece of gnomish "
        + "creativity. Black squares are strewn all over the exterior "
        + "of the contraption. At the top sits a small fan blade that "
        + "spins whenever sunlight hits the device. In the center of "
        + "the gadget, a coin slot allows one to <insert> a coin. It's hard "
        + "to figure out how all the pieces even fit together, but you think "
        + "you may be able to <disassemble> it if you tried really hard.\n\n";
        
    object player = environment(this_object());
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return long_desc;
    }
    
    int sunlight = GENESIS_TIMEKEEPER->query_sunlight(player);
    switch (sunlight)
    {
    case 0..1:
        long_desc += "The fan blades are completely still.\n";
        break;
    
    case 2..9:
        long_desc += "The fan blades are moving ever so slightly.\n";
        break;
    
    case 10..20:
        long_desc += "The fan blades are spinning quickly, providing "
            + "you with an adequate breeze.\n";
        break;
    
    case 21..30:
    default:
        long_desc += "The fan blades are spinning so fast, they are "
            + "creating quite a gust, cooling you from the heat "
            + "of the sunlight.\n";
        break;
    }
    
    return long_desc;
}

public string
query_domain_times()
{
    string * domains = ({ "ansalon", "avenir", "calia", "cirath", "earthsea",
        "emerald", "faerun", "gondor", "kalad", "khalakhor",
        "krynn", "raumdor", "shire", "sparkle", "terel" });
        
    string reading_desc = 
      " /:/:/:/:/:/::-:-:-:-:-:-O-:-:-:-:-:-::/:/:/:/:/:/\n"
    + "                        )|(\n"
    + "                       ( | )\n"
    + "                   ___,`   `.___\n"
    + "                 ,'             `.\n"
    + "   ,------------`       Time      `-----------.\n"
    + "  |                   Readings                 |\n"
    + "  | ------------------------------------------ |\n";
   
    foreach (string domain : domains)
    {
        string tod_desc = GENESIS_TIMEKEEPER->query_time_of_day(domain);
        reading_desc += sprintf("  | |%9-s - %28-s| |\n", 
            capitalize(domain), tod_desc);
    }
    reading_desc +=
      "  | ------------------------------------------ |\n"
    + "  `.__________________       ________________.'\n"
    + "                      `. | .`\n"
    + "                        )o(\n";
    
    return reading_desc;
}

public int
display_times(string str)
{
    if (!strlen(str))
    {
        notify_fail("Insert what?\n");
        return 0;
    }
    
    object coins = PARSE_COMMAND_ONE(str, this_player(),
        "[the] %i [into] [the] 'slot'");
    if (!objectp(coins))
    {
        notify_fail("Insert what into slot?\n");
        return 0;
    }
    if (!IS_COINS_OBJECT(coins))
    {
        notify_fail("You can only insert coins into the slot!\n");
        return 0;
    }
    
    if (coins->query_coin_type() != "platinum")
    {
        notify_fail("The slot doesn't seem to fit that type of coin! Maybe "
            + "you can try another type.\n");
        return 0;
    }

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("The coin slot is currently closed. It only seems"
          + " to open in the presence of natural light, out of doors.\n");
        return 0;
    }
    
    coins->split_heap(1);
    object leftover_coins = coins->make_leftover_heap();
    coins->remove_object();
    leftover_coins->move(this_player());
    
    write("You insert a platinum coin into the slot.\n"
         + "After a bit of clinking and rattling, the fan begins to turn"
         + " at the top of the device. A window on the side of the odd"
         + " gizmo pops open, and reveals the following:\n\n");
    write(query_domain_times() + "\n\n");
    
    return 1;    
}
