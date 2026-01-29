#include "defs.h"

inherit TELBERIN_ROYAL_CIRCLE;

public void
create_royal_circle()
{
    set_em_long("Here beside the western loop of the Royal Circle,"
      + " a massive fortress is situated. Battlements atop its great"
      + " walls bear testimony to the martial nature of the"
      + " premesis, for it looks as if it could withstand a siege"
      + " on its own. A long walkway leads to an entrance in the"
      + " fortress west of here. To the east, the gates of the"
      + " Royal Palace run close along the street, preventing"
      + " access to any who are not on special business. Delightful"
      + " smells drift onto the street from the south, where the"
      + " Royal Fruit garden lies.\n");

    add_item( ({ "massive fortress", "battlement", "battlements",
                 "premesis" }),
        "The Keepers of Telberin have built a mighty fortress indeed to"
      + " house their operations. It would take a great army to breach"
      + " the walls of this structure, were the walls of the city ever"
      + " to fail. Perhaps this is the last stronghold which has"
      + " been prepared against such a calamity.\n");
    add_item( ({ "walkway", "long walkway", "entrance", "west",
                 "entrance in the fortress" }),
        "The Fortress of the Protectorate can be entered following"
      + " a long walkway to the west.\n");
    add_item( ({ "gate", "gates", "palace gates", "gates of the palace",
                 "gates of the royal palace" }),
        "The gates of the Royal Palace meet the edge of the Royal"
      + " Circle east of here, preventing one from driving into the"
      + " Royal Courtyard.\n");
    add_item( ({ "courtyard", "royal courtyard" }),
        "Beyond the gates of the palace lies a beautiful courtyard which"
      + " leads right up to the entrance to the Palace.\n");
    add_item( ({ "entrance to the palace", "palace entrance" }),
        "The entrance to the Palace is quite a ways to the east,"
      + " beyond the courtyard and the gates. It does not look"
      + " accessible.\n");
    add_item( ({ "smell", "smells", "aroma", "aromas",
                 "delightful smell", "delightful smells" }),
        "Aromas waft onto the street here from the Royal Fruit garden"
      + " to the south. You find yourself closing your eyes and"
      + " breathing in their deep fragrance.\n");

    add_exit("royal_circle02", "northeast");
    add_exit("royal_circle04", "southeast");
    add_exit("artisans_way07", "southwest");

    set_no_exit_msg( ({ "northwest" }),
        "Northwest of here, Artisans Way has been closed off to allow"
      + " for repairs to its shops which were heavily damaged in the"
      + " recent raids.\n");
    set_no_exit_msg( ({ "west" }),
        "As you begin your march along the walkway to the west, three"
      + " very serious guards march toward you, informing you that"
      + " you are not permitted on the premesis at this time. You"
      + " return to the Royal Circle.\n");
    set_no_exit_msg( ({ "east" }),
        "The gates of the Palace are closed and sealed. You cannot"
      + " enter the courtyard from here.\n");
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
        "[the] [great] [royal] 'palace' / 'gate' / 'gates'"
      + " [of] [telberin] [the] [palace]"))
    {
        if (parse_command(arg, ({}),
            "[the] [great] [massive] 'fortress' / 'building'"
          + " / 'structure' [of] [the] [protectorate] [to]"
          + " [the] [west]"))
        {
            if (this_player()->query_wiz_level())
            {
                write("Normally, we would move the player 'west'"
                  + " here, using command(). Since you are a wizard,"
                  + " that won't work. Simply go 'west' yourself.\n");
                return 1;
            } /* if (this_player()->query_wiz_level()) */

            this_player()->command("west");
            return 1;
        } /* if amphitheatre parse_command */
        
        return 0; /* can't parse the player's syntax */
    } /* if palace parse_command */

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'east' here, using"
          + " command(). Since you are a wizard, that won't work. Simply"
          + " go 'east' yourself.\n");
        return 1;
    }

    this_player()->command("east");
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
