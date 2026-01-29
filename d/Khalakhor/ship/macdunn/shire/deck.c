/* File:          /d/Khalakhor/ship/macdunn/shire/deck.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications: 
 * Purpose:       The deck is a room on the Khalakhor to
 *                Shire ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      This room also uses the flight prop.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"

public void
create_deck()
{
    set_short("on the deck of the Corran");
    set_long("   This is the deck of the ship Corran. It is a " +
      "vessel used to carry freight and passengers. A mastpole " +
      "towers above you, while a cabin rests near the stern. " +
      "The railings of the ship curve upwards to the front and " +
      "rear of the ship, following the lines of the boat. " +
      "The smell of salt in the air is coupled with the " +
      "vista of the oceanic surroundings.\n");
    add_item(({"deck","area"}),"@@query_long");
    add_item(({"ship","vessel","Corran","corran","boat"}),"This is the " +
      "that ferries passengers and freight between the lands of " +
      "Khalakhor and the Shire.\n");
    add_item(({"mastpole","pole","mast","up"}),"The mastpole made of " +
      "white pine stands tall, and is as straight as the " +
      "proverbial arrow. Knotted ropes allow passage " +
      "to the crow's nest above.\n");
    add_item(({"pine","white pine"}),"White pine is a wood " +
      "with an extremely straight grain, and often used by " +
      "woodworkers.\n");
    add_item(({"ropes","knotted ropes","rope"}),"The ropes " +
      "are knotted and tied around the wood, acting as handholds " +
      "and footholds for climbers.\n");
    add_item(({"knots","knot"}),"The knots are made of rope, and " +
      "can support a fair weight.\n");
    add_item(({"nest","crow's nest"}),"The crow's nest above is a " +
      "small wooden landing where observations of distant realms " +
      "and objects can be made.\n");
    add_item(({"landing","wooden landing","small landing",
        "small wooden landing"}),"It is the crow's nest, above your " +
      "head.\n");
    add_cmd_item(({"mastpole","pole","mast","the mast","the pole",
        "the mastpole","rope","ropes","the ropes","the knotted ropes",
        "up the mast","up","up the mastpole","up the pole","up the ropes",
        "up the knotted ropes","up the mast"}),"climb","@@go_climb");
    add_cmd_item(({"mastpole","pole","mast","up the mast","up the pole",
        "up the mastpole","up","to the crow's nest","to the nest",
        "to the lookout","to crow's nest","to lookout"}),({"levitate",
        "fly"}),"@@go_fly");
    add_item(({"sails","sail","series of sails"}),"The series of sails " +
      "are suspended from the mast.\n");
    add_item("cabin","A small cabin sits toward the stern of the " +
      "ship, most likely the dwelling of the captain.\n");
    add_item("railings","They are of wooden construction, and of " +
      "little interest, unless a storm was to cause havoc with " +
      "the ship.\n");
    add_item(({"smell","smell of salt"}),"It gives the air a salty " +
      "tang.\n");
    add_cmd_item(({"tang","salty tang","the salty tang","air",
        "in the tang","in the salty tang","in the air","salt"}),
      ({"smell","breathe"}),"The smell of salt almost burns " +
      "your nostrils when you breathe it in.\n");

    add_exit(THIS_DIR + "cabin", "cabin", 0);
    add_exit(THIS_DIR + "fore", "fore", 0);
    add_exit(THIS_DIR + "mast", "asglkjhsag", 1,1,1);

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK);

    set_deck_sound("@@sounds");

}

public string
sounds()
{
    if(random(2))
        return "The ship steadily and gently rocks to and fro.\n";

    return "The ship sails smoothly over an area of placid water.\n";
}

public string
go_climb()
{
    if((this_player()->query_skill(SS_CLIMB) <= 15))
    {
        write("You find that despite the relative easiness of " +
          "the climb, you are unable to maneuver yourself " +
          "properly up the pole.\n");
        say(QCTNAME(this_player()) + " attempts to climb the mastpole, " +
          "but fails.\n");
        return "";
    }

    write("You climb the mastpole easily, using the handholds.\n");
    set_dircmd("up");
    this_player()->move_living("climbing the mastpole",
      THIS_DIR + "mast", 0, 0);
    return "";
}

public string
go_fly()
{
    if(!(this_player()->query_prop(LIVE_I_FLYING)))
    {
        write("You are not able to fly up at the moment.\n");
        say(QCTNAME(this_player()) + " attempts to fly upwards, " +
          "but fails miserably.\n");
        return "";
    }

    write("You easily fly from the ship deck to the crow's nest.\n");
    set_dircmd("up");
    this_player()->move_living("flying upwards",
      THIS_DIR + "mast", 0, 0);
    return "";
}
