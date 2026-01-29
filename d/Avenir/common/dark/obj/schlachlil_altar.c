// file name:   /d/Avenir/common/dark/obj/schlachlil_altar.c
// creator(s):  Cirion, March 1999
// revision(s): 
// purpose:     Altar to the god Schlachlil
// note:             
// bug(s):           
// to-do:

inherit "/d/Avenir/inherit/altar";
#include "/d/Avenir/include/deities.h"
#include <stdproperties.h>
#include "../dark.h"

#define PRAYER_PROP        "_live_i_prayed_at_schlachlil_altar"

void
create_altar()
{
    set_name("altar");
    add_name(({"pillar","schlachlil_altar"}));
    set_altar_name("schlachlil_altar");
    set_god("schlachlil");
    set_altar_short("dazzling pillar");    
    set_adj(({ "smooth", "crystal", "bright", "white" }));

    set_id_long("Perfectly formed from smooth crystal, the pillar "
        + "rises up from the stone floor to the ceiling, and sheds "
        + "a dazzling glow throughout the area, which is refracted "
        + "in the sheets of water flowing violently all around. "
        + "There are light carvings on its "
        + "surface that are a little less brilliant then the "
        + "rest of the crystal. At the top of the pillar, there are "
        + "four chains attached "
        + "to the pillar that lead out of the room through "
        + "the waters. This "
        + "is the altar of Schlachlil, diety of the Source.");

    set_unid_long("Perfectly formed from smooth crystal, the pillar "
        + "rises up from the stone floor to the ceiling, and sheds "
        + "a dazzling glow throughout the area, which is refracted "
        + "in the sheets of water flowing violently all around. "
        + "There are light carvings on its "
        + "surface that are a little less brilliant then the "
        + "rest of the crystal. At the top of the pillar, there are "
        + "four chains attached "
        + "to the pillar that lead out of the room through "
        + "the waters.");

    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile", "deface"}));
    set_offer_command(({"offer", "sacrifice"}));
    set_offering_prop(({ SCHLACHLIL_OFFERING }));
    set_pray_command("pray");
    set_worship_command("worship");
	set_offer_max(20);
     
    add_prop(OBJ_M_NO_GET, 1);
    set_no_show_composite(1);
}                                                                            

void
remove_darksight(object pl)
{
    pl->add_prop(LIVE_I_SEE_DARK, pl->query_prop(LIVE_I_SEE_DARK) - 1);
    pl->catch_msg("Suddenly everything seems a bit more hazy.\n");
}

/*
 * Function name:  altar_result_pos
 * Description:    Here the message is written when the player
 *                 does something Positive to the altar.
 *                 You may redefine it if you wish, to add things 
 *                 like align adjustments, etc.
 * Arguments:      qvb  - The verb used 
 */
void
altar_result_pos(object pl, string qvb)
{
    // increment the prayer prop to increase the chance of failure
    // for continual attempts.
    this_player()->add_prop(PRAYER_PROP, this_player()->query_prop(PRAYER_PROP) + 1);

    if(random(2 + this_player()->query_prop(PRAYER_PROP)))
    {
        pl->catch_tell("Your prayers go unheard.\n");
        return;
    }

    pl->catch_msg("A feeling of ecstasy uplifts you, as though you can feel "+ 
        capitalize(query_god()) +"'s pleasure in your actions.\n");
    say(QCTNAME(this_player()) +" appears to be momentarily over"+
        "come with ecstacy.\n");

    if(pl->query_prop(LIVE_I_SEE_DARK) <= 0)
    {
        pl->add_prop(LIVE_I_SEE_DARK, pl->query_prop(LIVE_I_SEE_DARK) + 1);
        pl->catch_msg("You feel your pupils grow larger, and everything seems "
            + "to be in much clearer focus.\n");
        set_alarm(1000.0 + itof(random(2000)), 0.0, &remove_darksight(pl));
    }
}

