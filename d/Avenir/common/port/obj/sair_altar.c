// file name    /d/Avenir/common/port/obj/sair_altar
//              cloned to /d/Avenir/common/port/port5
// creator(s)   Lilith
// revision(s)
// purpose      Shrine to Sair in the Port area Quest
// note         May bless the player with temporary boost  
//		         to STR (5) and Earth spell skills (5) 
// bug(s)     
// to-do      
#pragma strict_types

inherit "/d/Avenir/common/city/zigg/lib/altar";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"

#include "../port.h"
#include "/d/Avenir/include/deities.h"
#include <macros.h>
#include <stdproperties.h>

/* Find Sair's Shrine Quest */
#define GROUP     1
#define BIT      13
#define  EXP      500
#define PRAYER_PROP      "_live_i_prayed_at_sair_altar"
#define CHECK_QUEST(x)   (x)->test_bit("Avenir", GROUP, BIT)

/*
 * set_id_long(string)      - Identified long desc.
 * set_unid_long(string)    - Unidentifed long desc.
 * set_altar_short(string)  - Short desc.
 * set_god(string *)        - God(s) of altar.
 * set_altar_hour(int)      - Hour of the God.
 * set_offer_max(int)       - Max offerings.
 * set_altar_name(string)   - True name of altar.
 * set_offering_prop(*string)   - Acceptable offerings have these props.
 ** ADD ACTIONS BELOW **
 * set_bless_command(string *)     - Accepted commands to bless altar.
 * set_defile_command(string *)    - Accepted commands to defile altar.
 * set_repair_command(string *)    - Accepted commands to repair altar.
 * set_destroy_command(string *)   - Accepted commands to destory altar.
 * set_offer_command(string *)     - Accepted commands to make offerings.
 * set_pray_command(string *)      - Accepted commands to pray at altar.
 */

public void
create_altar(void)
{
    set_god("sair");
    set_altar_hour(1);
    set_altar_name("_Avenir_Sair_Shrine");
    set_altar_short("shrine carved into the cavern wall");
    add_name(({"shrine", "column", "shrine to sair", "sair shrine"}));
    set_adj(({"stone", "sair", "octagonal", "orange", "red-gold"}));

    set_unid_long("A section of the cavern wall has been chiseled away "+
	    "to reveal a massive octagonal column of red-gold opalescent "+
		"stone. It looks like a shrine of sorts.");
    set_id_long("A section of the cavern wall has been chiseled away "+
	    "to reveal a massive octagonal column of red-gold fire opal "+
		"that sets the mist nearby aglow with a tangerine-orange color.\n"+
		"   This shrine has been dedicated to Sair the Strong, Goddess "+
		"of the First Hour, Keeper of Walls and Remover of Obstacles.");

    set_offering_prop(({SAIR_OFFERING}));

    set_offer_command(({"offer", "place", "fit", "lay"}));
    set_pray_command(({"pray", "petition", "worship", "respect", "revere" }));
    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile"}));

    set_offer_max(20);
    set_no_show_composite(1);  //don't want it to show up in room desc.
    add_prop(OBJ_M_NO_GET, "The column is far too heavy to be gotten.\n");
}

/* This is a newbie quest, so lets make it easy */ 
public varargs int
id_altar_check(object pl = this_player())
{
    return 1;
}
/*
 * Function name:  reset_altar()
 * Description:    Reset the offerings so more can be made at intervals
 */   
public void
reset_altar() { this_object()->remove_prop(ALTAR_IS_OCCUPIED); }


public void
do_sair_bless(object player)
{
    object blessing;
	
    player->catch_msg("A feeling of Rightness settles upon you. It would " 
	    +"appear that Sair is pleased by your actions.\n");
    say(QCTNAME(player) +" appears to have entered a state of bliss.\n");

    if (!present("_Avenir_Sair_Blessing", player))
    {
	    blessing = clone_object(PORT +"obj/sair_blessing");
	    blessing->move(player, 1);  
    }
}

public void
altar_result_pos(string verb, string god)
{
	
    /* Player found the altar and made an offering */
	if (!CHECK_QUEST(TP))
	{
	    reward_quest("Find Sair's Shrine", TP, GROUP, BIT, EXP);
		FLUX("\nA beautiful tangerine-colored light emits from the Source.\n"
		   +"You aren't certain how you know this, but you are certain "
		   +"that someone has pleased the Goddess Sair.\n\n");
        STATSERV_LOG_EVENT("Sair", "found Sair's shrine");
		do_sair_bless(TP);
		return;
    }

    // increment the prayer prop to increase the chance of failure
    // for continual attempts.
    TP->add_prop(PRAYER_PROP, TP->query_prop(PRAYER_PROP) + 1);
    if(TP->query_prop(PRAYER_PROP) > random(10))
    {
        TP->catch_tell("It seems you are being ignored.\n");
        return;
    }

    do_sair_bless(TP);
}
