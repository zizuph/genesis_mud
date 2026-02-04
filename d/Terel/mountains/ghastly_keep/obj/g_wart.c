/*
 * /d/Terel/mountains/ghastly_keep/obj/g_wart.c
 *
 * Witch wart
 *
 * Can also be used as a summoning portal.
 *
 * - Summons a Vampire.
 *
 * In the cover of Darkness this vampire hunt, and torments
 * the habitants of Terel. Throughout its nightly missions 
 * it gathers a decent collection of gear.
 *
 * Znafsnuf
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  10/09-17           Added a cooldown between each mend              Znagsnuf 
 */

inherit "/std/object";

#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>

int do_mend(string str);
int stones = 0;

/*
 * Function name: set_stones()
 * Description  : Sets the number of stones.
 */
int
set_stones(int i)
{
    stones = i;
}

/*
 * Function name: query_stones()
 * Description  : Return the amount of stones.
 */
int
query_stones(int i)
{
    return stones;
}

void
create_object()
{
    set_name("wart");
    add_name("_ghastly_keep_wart");
    set_adj("witch");
    add_adj("wart");

    set_short("witch wart");

    set_long("This is a gross wart from a witch nose. It resembles "
            + "a cauliflower. @@check_power@@\n");

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);


    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}) );

    add_prop(MAGIC_AM_ID_INFO, ({
        "You feel there must be great powers in a witch's wart.\n", 20,
        "Legends tells about mending a witch wart using numerous "
      + "ghastly green stones to create a rift to the netherworld.\n", 50 }));

    add_prop(OBJ_S_WIZINFO, "This is one of the items used for the summoning "
        + "ritual.\n");
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() 
{
    ::init();
    add_action(do_mend, "mend");
    add_action(do_mend, "rub");
}

/*
 * Function name: do_mend()
 * Description  : Transport the player to the next room.
 */
int do_mend(string str)
{

    object stones = present("_ghastly_keep_stone", TP);
    object boss, mender;

    notify_fail(CAP(query_verb()) + " what?\n");
    if(!str || !stones)
        return 0;

    notify_fail("The " + TO->short() + " is currently in the prosess of growing.\n");
    if (this_player()->query_prop("_wart_mend_ghastly") + 60 > time()
                    || query_prop("_wart_mend_ghastly") + 60 > time())
        return 0;  

    notify_fail(CAP(query_verb()) + " what?\n");
    if (!parse_command(str, ({ }), 
        " [the] [ghastly] [green] 'stone' / 'stones' [with] [wart]"))
        return 0;   

    notify_fail("You are currently not close enough to the source.\n");
    if (!wildmatch("/d/Terel/mountains/ghastly_keep/*", file_name(ENV(TP)))) 
        return 0;

    if(stones)
    {
     write("\nYou rub the " + TO->short() + " on the " +stones->short()+ ", "
             + "forcing them to mend together. The " +TO->short()+ " pulses "
             + "as its consumes the powers kept within the "
             +stones->short()+ ".\n\n");
     say(QCTNAME(TP) + " rubs the "+TO->short()+" on the "+stones->short()+ ","
             + " forcing them to mend together.\nThe " +TO->short()+ " pulses " 
             + "as its consumes the powers kept within the "
             +stones->short()+ ".\n");

      //Add power to the current wart.
      set_stones(TO->query_stones() + 1);
      
      // Add timer to the player, and the object. To prevent spamming.
      this_player()->add_prop(("_wart_mend_ghastly"), time());
      add_prop(("_wart_mend_ghastly"), time());

      if((TO->query_stones()) > G_SUMMON)
      {
        mender = TP;
        
        // Remove the last stone.
        stones->remove_object();

        setuid();
        seteuid(getuid());

        // Summons the Vampire.
        boss = clone_object(GKEEP_NPC + "g_vampire");
        boss->arm_me();
        // boss -> move_living("M", ENV(TP) , 0, 1);

        boss->move(ENV(mender), 1);

            tell_room(ENV(TP), "\nAmid a shower of fiery, dancing sparks "
                 + "a " +boss->query_short()+ " arrives. From "
                 + "under " + boss->query_possessive() + " " 
                 + "shimmering veil all that could be seen by the firelight "
                 + "was the darkness in " +boss->query_possessive()+ " eyes. "
                 + "Behind " +boss->query_objective()+ " was cast a long "
                 + "malevolent shadow that seemed to move independently from "
                 + ""+boss->query_objective()+ " as if it too was making it's " 
                 + "own incantation to the spirits. In the putrefying air "
                 + "above " +boss->query_objective()+ " black swirling "
                 + "balls of mist formed, smelling of rotting "
                 + "flesh and death itself. The swirls grew until they "
                 + "combined and from them came this, the "
                 +boss->query_race_name()+ ".\n\n");

        // Attack the summoner    
        boss -> aggressive_attack(TP);

        // Remove the wart.
        TO->remove_object();
        return 1;
      }
      
      // Adding power, consuming the stone.
      stones->remove_object();
      return 1;
    }

    return 1;
}

/*
 * Function name: check_power
 * Description  : as simple as that
*/

public string
check_power()
{

    object power = TO->query_stones();

    switch (power)
    {
    case 0:
        return "Besides those features, the " + TO->short() + " looks "
              + "plain and simple.";
        break;
    case 1..3:
        return "The " + TO->short() + " is growing somewhat larger "
              + "and bumpier.";
        break;
    case 4..5:
        return "The " + TO->short() + " is emitting light from time "
              + "to time, like there is something trapped within.";
        break;
    case 6..7:
        return "The " + TO->short() + " is pulsating in a steadfast way.";
        break;
    case 8:
        return "The " + TO->short() + " is surrounded with a hellish "
              + "red aura.";
        break; 
    case 9:
        return "The " + TO->short() + " is vibrating full of power.";
        break;                     
    }
    return "";
} /* check_power */              
