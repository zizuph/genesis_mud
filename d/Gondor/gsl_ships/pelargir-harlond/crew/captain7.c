/*
 *	/d/Gondor/common/ship/captain7.c
 *
 *	Coded by Olorin
 *
 *	Modification log:
 *	12-Feb-1997, Olorin:	Inherit captain.c
 *  13-Jun-2009, Tapakah: ported to the new ship system
 */

#pragma save_binary
#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit "/d/Gondor/common/ship/pel_tours";
inherit "/d/Gondor/common/ship/gsl_captain";

public void
create_gondor_captain()
{
    set_name("hothronduin");
    add_name( ({ "man", }) );
    set_living_name("hothronduin");
    set_race_name("human");
    set_adj(({"barrel-chested", "red-bearded"}));
    set_title("the River Captain");

    set_chat_time(12);
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("Minas Tirith is still bustling with activity. Trade is good.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("Somebody is opening a route to the Grey Havens I've heard.");
    add_chat("Fair wind today. We should be able to stay on schedule.");
    add_chat("In Minas Tirith, visit Hunthor, the Master of Advice!");
    add_chat("I think there will be a good wind to sail up the Anduin.");
    add_chat("I heard rumours in Pelargir that a corsair is running a "
      + "ship line between Tharbad and the crossings of Poros.");
    add_chat("In Pelargir, visit Carastur, the Lord Councillor of the city!");
    add_chat("I prefer the tour from Pelargir to Minas Tirith, it is much safer than the open ocean.");
    add_chat("Go to the Harbour Masters in the Harlond and in Pelargir, they often offer small jobs.");
    add_chat("I've heard the plains of Rohan are orc infested. Stay to the road!");
    add_chat("At the Harlond they tell that armies of orcs and Haradrim have overrun Ithilien.");
    add_chat("In Edoras, look for Elfhelm the Marshal.");
    add_chat("Don't go to Ithilien unless by Leave of the Steward!");
    add_chat("If you are looking to help someone, see if you can find Grub on the Pelargir docks.");
    add_chat("I hear a little boy named Grub is looking for help. I saw him on the docks of Pelargir.");    
    set_cchat_time(11);
    add_cchat("Hey! Are you one of the pirates of Umbar??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Corsairs of Umbar!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_up_pelargir_tour();

}
