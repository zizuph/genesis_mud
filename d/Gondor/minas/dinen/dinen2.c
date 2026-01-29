/*
 *  /d/Gondor/minas/houses/dinen2.c
 *
 *  The Rath Dinen - Second part of path.
 *
 *  Alto, 12 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"


#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    set_short("Somewhere along the Rath Dinen");
    set_long("This small path leads down into the Hallows "
        + "of Minas Tirith, where stand the House of Stewards "
        + "and the House of Kings. The Men of Gondor call this "
        + "path the Rath Dinen, or Silent Street. Except in "
        + "times of funeral, only the Lord of the city or those "
        + "bearing the token of the tombs are permitted to walk "
        + "this path. The Rath Dinen continues downhill to the west "
        + "and uphill back toward the city to the east.\n");

    add_exit(INNER_MINAS + "/dinen/dinen3", "west", 0, 0);
    add_exit(INNER_MINAS + "/dinen/dinen1", "east", 0, 0);

    add_item(({"path", "street", "rath dinen", "silent street"}),
        "Here the path of the Rath Dinen is very narrow and leads "
        + "west and east in almost a straight line. It is comprised of small "
        + "white pebbles that appear to have come from near the Sea. "
        + "Its surface has been raked smooth, and it looks as though "
        + "no feet have passed this way for some time. The path is "
        + "lined on both sides by a tall hedge.\n");
    add_item(({"pebbles", "white pebbles"}), "You suspect they were "
        + "transported here "
        + "from the Sea, where long years of tossing in the currents "
        + "made them smooth, rounded and white.\n");
    add_item(({"surface"}), "Because there are no footprints in the "
        + "pebbles, you surmise that nobody has walked here for a long "
        + "time. The prospect of violating this sacred place makes "
        + "you feel a somewhat nervous.\n");
    add_item(({"hedge", "tall hedge"}), "It is impossible to tell what "
        + "lies beyond the path because the tall hedge blocks your "
        + "view. It is mildly disconcerting that no birds or other "
        + "creatures can be seen or heard within them.\n");
    add_item(({"hallows", "house of stewards", "house of kings"}),
        "Because of the twisting of the Rath Dinen to the west, in "
        + "concert with the tall hedge blocking your view, you cannot "
        + "see the Hallows from this place. If you are brave enough, "
        + "perhaps you should continue west and have a look.\n");
    add_item(({"gravel"}), "It is mostly white pebbles.\n");
    add_item(({"shadow"}), "Maybe it was just your imagination.\n");
    add_item(({"sky"}), "The sky is dominated by the the massive mountain "
        + "rising out of sight to the west.\n");
    add_item(({"mountain", "mount mindolluin"}), "The Rath Dinnen "
        + "is built on its knees. It dominates the entire western sky.\n");
    add_item(({"clouds"}), "They appear to be gathering in the "
        + "eastern sky.\n");
    add_item(({"hand"}), "You must have imagined it.\n");
    add_item(({"fog", "mist"}), "It seems to be growing thicker with "
        + "every step. It appears to flow in from the hedges to either "
        + "side of the path.\n");
    

    /* These tells are common for all parts of the Rath Dinnen
     * except the entrance near the Fen Hollen.
     */

    set_tell_time(120);
    add_tell("A few drops of rain spatter on the white pebbles.\n");
    add_tell("A shadow crosses the hedge to your left. When you turn "
        + "to look it is gone.\n");
    add_tell("Wind howls mournfully down the path.\n");
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Something rustles in the hedge to your right.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("You hear the sound of gravel crunching under foot "
        + "somewhere nearby.\n");
    add_tell("Lightning flashes in the distant east.\n");
    add_tell("Low voices can be heard whispering somewhere nearby.\n");
    add_tell("Someone moans.\n");
    add_tell("Suddenly the noises cease. The silence is thick with "
        + "unseen menace.\n");
    add_tell("You feel a hand on your shoulder.\n");
    add_tell("A mighty warhorn can be heard in the distance.\n");
    add_tell("The air grows noticeably colder.\n");
    add_tell("You feel a presence behind you.\n");
    add_tell("You hear a small child crying somewhere nearby.\n");
    add_tell("Something groans. You feel certain it came from the "
        + "other side of the hedge.\n");
    add_tell("The wind suddenly stops. Everything is quiet.\n");


    /* These tells are unique to this room */

    add_tell("Fog rolls across the path from the hedge.\n");
    add_tell("The mist grows thicker. It is becoming difficult to see.\n");
    
    reset_room();

}   

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}





