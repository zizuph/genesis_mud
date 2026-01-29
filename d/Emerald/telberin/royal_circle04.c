#include "defs.h"

inherit TELBERIN_ROYAL_CIRCLE;

public void
create_royal_circle()
{
    set_em_long("You stand on the southern loop of the Royal Circle,"
      + " between two incredibly beautiful buildings. To the south,"
      + " a heavily ornamented tower rises high above, branching as"
      + " a tree might as it extends upward, its many towers glowing"
      + " with a magical energy. More impressive still, the Palace of"
      + " Telberin stands before you to the north. Vaulting from the"
      + " center of the city in a display of both might and elegance,"
      + " it is a wonder to behold. The Magic Quarter of Emerald can"
      + " be seen following roads to the southwest and southeast, and"
      + " the the beautiful Royal Fruit Garden beckons to the west.\n");

    add_item( ({ "beautiful building", "beautiful buildings",
                 "incredibly beautiful building",
                 "incredibly beautiful buildings" }),
        "Up close like this, the Tower of Telan-Ri and Royal palace are"
      + " breathtaking beyond compare. Surely this city must attract"
      + " persons from distant lands simply to take in such visions.\n");
    add_item( ({ "ornament", "ornamentation", "ornamented tower",
                 "heavily ornamented tower", "heavy ornamentation" }),
        "The Tower of Telan-Ri, just south of here, is dazzlingly"
      + " ornamented. The organic nature of the architecture is unlike"
      + " anything you have ever seen, clearly mimicing the growth of"
      + " branches from a tree.\n");
    add_item( ({ "many towers", "energy", "magic", "magical energy",
                 "glow", "chamber", "chambers", "myriad chambers",
                 "myriad towers", "pinnacle", "pinnacles" }),
        "A glow emenates from the many towers of the Temple of Telan-Ri"
      + " to the south. Clearly, there is powerful magic at work within"
      + " its myriad chambers.\n");
    add_exit("royal_circle01", "northwest");
    add_exit("royal_circle03", "northeast");
    add_exit("channelers_way01", "southwest");

    set_no_exit_msg( ({ "southeast" }),
        "To the southeast, Channelers Way has been closed for repairs"
      + " after sustaining great damage in the recent raids.\n");
    set_no_exit_msg( ({ "south" }),
        "As you walk to the south, your steps grow slower and slower,"
      + " until you find that you have stopped walking entirely. A"
      + " soothing, yet authoritative voice echoes in your mind: You"
      + " have no business with the Order of Telan-Ri.\n");
    set_no_exit_msg( ({ "north" }),
        "Many guards block the way to the Palace. You overhear some"
      + " of them discussing how many people they have had to turn"
      + " back from visiting the Rulers since the raids began.\n");

    add_door_exit(TELBERIN_FRUIT_GARDEN_DIR + "garden_gate",
                  "/d/Emerald/telberin/fruit_garden/fruit01",
                  "west", 0, 0, 1);
}


/*
 * Function name:        do_enter
 * Description  :        allow players to try to enter the
 *                       buildings in the Royal Circle
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
//      notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [great] [royal] 'palace' [of] [telberin]"))
    {
        if (parse_command(arg, ({}),
            "[the] [great] 'tower' [of] [telan-ri] [telan] [ri]"))
        {
            if (this_player()->query_wiz_level())
            {
                write("Normally, we would move the player 'south'"
                  + " here, using command(). Since you are a wizard,"
                  + " that won't work. Simply go 'south' yourself.\n");
                return 1;
            } /* if (this_player()->query_wiz_level()) */

            this_player()->command("south");
            return 1;
        } /* if temple parse_command */
        
        return 0; /* can't parse the player's syntax */
    } /* if palace parse_command */

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'north' here, using"
          + " command(). Since you are a wizard, that won't work. Simply"
          + " go 'north' yourself.\n");
        return 1;
    }

    this_player()->command("north");
    return 1;
} /* do_enter */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
} /* init */
