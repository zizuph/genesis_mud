// file name  :  altar_cahor.c
// creator(s) :  Zielia
// revision(s):
// purpose    :  Altar for the Ziggurat
// note       :  Player may receive a blessing which will temporarily
//		 give them +1 to LIVE_I_SEE_INVIS 
// bug(s)     :
// to-do      :
#pragma strict_types


#include "zigg.h"
#include "/d/Avenir/include/deities.h"

#include <macros.h>
#include <stdproperties.h>

#define PRAYER_PROP       "_live_i_prayed_at_cahor_altar"

inherit (ZIG_LIB + "altar");

/*
 * set_id_long(string)		- Identified long desc.
 * set_unid_long(string)	- Unidentifed long desc.
 * set_altar_short(string)	- Short desc.
 * set_god(string)		- God of altar.
 * set_altar_hour(int)		- Hour of the God.
 * set_offer_max(int)		- Max offerings.
 * set_altar_name(string)	- True name of altar.
 * set_offering_prop(*string)	- Acceptable offerings have these props.
 ** ADD ACTIONS BELOW **
 * set_bless_command(string *)     - Accepted commands to bless altar.
 * set_defile_command(string *)	   - Accepted commands to defile altar.
 * set_destroy_command(string *)   - Accepted commands to destory altar.
 * set_dismantle_command(string *) - Accepted commands to dismantle altar.
 * set_offer_command(string *)	   - Accepted commands to make offerings.
 * set_pray_command(string *)	   - Accepted commands to pray at altar.
 */

public void
create_altar(void)
{
    set_god("Cahor");
    set_altar_hour(7);
    set_altar_name("ziggurat::cahor");
    set_altar_short("stone slab with a crystal basin of water on it");

    add_name(({"orb", "sphere"}));
    set_adj(({"blue-black", "blue", "black", "flaming"}));

    set_unid_long("A black stone slab "+
	"supports a crystal basin of pure clear water next to which "+
	"lies a neatly folded piece of black webcloth.");
    set_id_long("A black stone slab supports a crystal basin of "+
	"pure clear water and the neatly folded piece of black webcloth "+
	"Anchorites of Cahor use for their rituals.");

    set_offering_prop(({CAHOR_OFFERING, UNIVERSAL_OFFERING}));

    set_offer_command(({"offer", "sacrifice"}));
    set_pray_command(({"pray", "supplicate", "petition","worship","revere"}));

    set_offer_max(20);
    set_no_show_composite(1);  //don't want it to show up in room desc.
    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be gotten.\n");

    add_item(({"slab","stone slab","black stone slab"}),"@@see_slab"	);
    add_item(({"basin","basins",		}),	"@@see_basin"	);
    add_item(({"cloth","cloths","webcloth"	}),	"@@see_cloth"	);
}

public int
check_seen(object who)
{
    return CAN_SEE_TRUE(who);
}

public string
see_slab(void)
{
    if (!CAN_SEE_TRUE(TP))
    {
        return "You find no slab.\n";
    }
    else
    {
        return "It is a heavy rectangular slab of glossy black stone "+
	    "similar to the stone that comprises most of the Ziggurat.\n";
    }
}

public string
see_basin(void)
{
    string str;

    if (!CAN_SEE_TRUE(TP))
    {
        return "You find no basin.\n";
    }
    else
    {
	str= "It is a large basin: Your arms would likely just fit "+
	     "around it. It is made of flawlessly cut lead crystal and "+
	     "faceted so that it refracts the Sourcelight so it casts an "+
	     "aura of tiny rainbows all around the basin and into the pure, "+
	     "clear water inside it.";

	if (id_altar_check(TP))
	    return str +" It is said that all manner of truths might be "+
		"revealed in this bowl for those who can See.\n";
	else
	    return str +"\n";
    }
}

public string
see_cloth(void)
{
    string str;

    if (!CAN_SEE_TRUE(TP))
    {
        return "You find no cloths.\n";
    }
    else
    {
        str = "A neatly folded square of black webcloth sits on the slab "+
	    "next to the crystal basin.";

	if (id_altar_check(TP))
	{
	    return str +" An Anchorite of Cahor might use the cloth in a "+
	    "ritual to cover the basin and veil the truths within.\n";
	}
	else
	    return str +"\n";
    }
}

public string
long(string str, object for_obj = TP)
{
    if (!CAN_SEE_TRUE(TP))
    {
        return "You find no altar.\n";
    }

    return ::long(str, for_obj);
}

public int
do_pray(string str)
{
    if (!CAN_SEE_TRUE(TP))
    {
        notify_fail("What?\n");
	return 0;
    }

    return ::do_pray(str);

}

public int
do_offer(string str)
{
    if (!CAN_SEE_TRUE(TP))
    {
        notify_fail("What?\n");
	return 0;
    }

    return ::do_offer(str);

}

public int
do_bless(string str)
{
    if (!CAN_SEE_TRUE(TP))
    {
        notify_fail("What?\n");
	return 0;
    }

    return ::do_bless(str);

}

public int
do_defile(string str)
{
    if (!CAN_SEE_TRUE(TP))
    {
        notify_fail("What?\n");
	return 0;
    }

    return ::do_defile(str);

}

public int
do_repair(string str)
{
    if (!CAN_SEE_TRUE(TP))
    {
        notify_fail("What?\n");
	return 0;
    }

    return ::do_repair(str);

}

public int
do_destroy(string str)
{
    if (!CAN_SEE_TRUE(TP))
    {
        notify_fail("What?\n");
	return 0;
    }

    return ::do_destroy(str);

}

public int
do_cover(string str)
{
    if (str == "basin" || str == "basin with cloth")
    {
        notify_fail("You don't dare touch an Anchorite's tools.\n");
	return 0;
    }
}

/*
 * Function name: offer_text
 * Description	: The text given for a normal offering.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 * 		  string what - What was offered.
 */
static void
offer_text(string verb, string god, string what)
{
    write("Your "+ verb +" of "+ LANG_ADDART(what) +" at the "+
	real_short() +" has been accepted by "+ god +".\n");

    foreach(object who : filter(all_inventory(ENV()), query_interactive))
    {
	if (who == TP)	
	    return;	    
	    
	if (CAN_SEE_TRUE(who))
	{
	    who->catch_msg(QCTNAME(TP) +" "+ LANG_PWORD(verb) +
		" "+ LANG_ADDART(what) +" at the "+ real_short() +".\n");
	}
	else
	{
	    who->catch_msg(QCTNAME(TP) +" places "+ LANG_ADDART(what) +
		" on the stone floor at the center of the room where "+
		"it disappears!\n");
	}
    }
}


/*
 * Function name: bloody_offer_text
 * Description	: The text given for a bloody offering.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 * 		  string what - What was offered.
 * 		  object wep  - The weapon used.
 */
static void
bloody_offer_text(string verb, string god, string what, object wep)
{
    write("Making an offering to "+ god +", you slit the "+ what +
	" open on the "+ real_short() +" with your "+ wep->short() +
	".\nThe "+ what +" writhes and twitches spasmodically "+
	"under your hands, splashing blood everywhere.\n");
	
    foreach(object who : filter(all_inventory(ENV()), query_interactive))
    {
	if (who == TP)	
	    return;	    
	    
	if (CAN_SEE_TRUE(who))
	{
	    who->catch_msg(QCTNAME(TP) +" offers the "+ what +
		" as a blood sacrifice upon the "+ real_short() +".\n"+
		QCTNAME(TP) +" slits the "+ what +" open with "+
		HIS(TP) +" "+ wep->short() +"and watches as it writhes "+
		"and twitches spasmodically, splashing blood everywhere.\n");
	}
	else
	{
	    who->catch_msg(QCTNAME(TP) +" stands at the center "+
	    	"of the room and slits the "+ what +" open with "+
		HIS(TP) +" "+ wep->short() +". "+ HE(TP) +" watches as "+
		"it writhes and twitches spasmodically, splashing blood "+
		"everywhere before "+ HE(TP) +" somehow disposes of the "+
		"lifeless remains.\n");
	}
    }
}

/*
 * Function name: pray_text
 * Description	: Here the prayer/worship message is written.
 * Arguments	: string verb - The verb used (pray or worship)
 * 		  string god  - The god invoked.
 */
static void
pray_text(string verb, string god)
{
    if (verb == "pray")
	verb += "ing";

    write("You assume the proper posture for "+ verb +" to "+ god +
	".\n\nYou kneel before the "+ real_short() +", pressing "+
	"your forehead against the ground and stretching your "+
	"arms out toward it.\n");

    foreach(object who : filter(all_inventory(ENV()), query_interactive))
    {
	if (who == TP)	
	    return;	    
	    
	if (CAN_SEE_TRUE(who))
	{
	    who->catch_msg(QCTNAME(TP) +" kneels before the "+
		real_short() +" in supplication.\n");
	}
	else
	{
	    who->catch_msg(QCTNAME(TP) +" kneels upon the stone "+
		"floor in supplication.\n");
	}
    }
}

public void
altar_result_pos(string verb, string god)
{
    object obj;

    // increment the prayer prop to increase the chance of failure
    // for continual attempts.
    TP->add_prop(PRAYER_PROP, TP->query_prop(PRAYER_PROP) + 1);

    if(random(2 + TP->query_prop(PRAYER_PROP)))
    {
        TP->catch_tell("Your prayers go unheard.\n");
        return;
    }

    write("A feeling of ecstasy uplifts you, as though you can feel "+
        LANG_POSS(god) +" pleasure in your actions.\n");

    say(QCTNAME(TP) +" appears to be momentarily over"+
        "come with ecstacy.\n");

    if (!present("Cahor::Blessing", TP))
    {
	obj = clone_object(ZIG_OBJ + "c_blessing");
	obj->move(TP, 1);
    }

    /*  Below are the quest-related bits for Ry'nal.  */

    /*
     * Already did the quest.
     *
     * Check disabled to allow for repeatability in getting the diadem.
     *
    if (TP->test_bit("Avenir", ZQ_GROUP, ZQB_RYNAL))
	return;
     */

    /* Not on the quest, or diadem already cloned. */
    if (TP->query_prop(RYNAL_I_QUEST) != 1)
	return;

    obj = clone_object(ZIG_OBJ + "diadem");
    clone_object(ZIG_OBJ + "diashad")->shadow_me(obj);

    /* Things are broken, bummer! */
    if (!obj->query_diadem_shadow())
    {
	obj->remove_object();
	write("The diadem has become permanently lost, "+
	    "contact a wizard.\n");
	return;
    }

    TP->add_prop(RYNAL_I_QUEST, 2);

    /* The diadem will move itself into a random place. */
    obj->set_questor(TP);
}

public void
init(void)
{
    ::init();

    add_action(do_cover, "cover");
}


