// basket-hilt falchion  /d/Avenir/common/holm/obj/falchion.c
// creator(s):           Lilith, 5/20/97
// purpose:              To be wielded by Hunter shadow-elves
// last update:          Lilith July 2014
//                       Added falchion quest code to this obj
//                       since runed falchions are hard to come by
// note:                
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";

#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

#define ALTAR_PROP   "_offered_at_altar"
#define F_QUESTOR    "_on_falchion_quest"
#define METAL        "/d/Avenir/common/holm/obj/quicksilver"
#define F_QUEST_LOG  "/d/Avenir/log/quest/falchion_quest"
#define SHADOW       "/d/Avenir/common/holm/obj/falchion_shadow"
#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? \
	    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
        (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

int alarm_id, alarm_id2, alarm_id3;

public
string my_long()
{
    return "A broad, short sword with a gently curving edge. The steel "+
           "blade is vaguely sickle-shaped, double-edged, and has a "+
           "tapering point, making it effective as both a cutting and "+
           "thrusting weapon. It has a long handle with an elaborate "+
           "basket-hilt.\n";
}
void 
create_weapon()
{
    set_name("fauxcwicseolfor");  /* Old English for quicksilver :) */
    add_name(({"sword", "weapon", "falchion"}));
    set_adj(({"basket-hilt", "broad"}));
    add_adj(({"basket", "hilt"}));              /* Removed 'short' reference */
    set_short("basket-hilt falchion");
    set_long(my_long());                                   
    set_hit(35 + random(5));
    set_pen(35 + random(5));
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_item(({"hilt", "basket", "handle", "basket hilt"}),
        "Steel has been woven in an elaborate, dizzying pattern that "+
        "forms a basket hilt for protection of the wielding hand.\n");
    add_item(({"pattern", "patterns", "weave" }),
        "This weave was done by someone obviously expert in the art of "+
        "working molten metal. The pattern is such that the eye cannot "+
        "follow the sinuous lines without becoming confused.\n");
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));
    add_prop(OBJ_S_WIZINFO, "This sword is a replica of Cwicseolfor"+
        ", the Sybarite Sword of Quickening.\n");
	add_prop(SPECIAL_OFFERING, 1);
    add_prop(ACLOLTHAYR_OFFERING, 1);
}


/* *****************  Falchion quest functions below  ***************** */

/* 
 * Function name:   do_vision
 * Description:     The special effect alarm when this object is offered 
 *                  at an altar to Aclolthayr. It is Called by the altar,
 *                  through the function altar_special, below.
 * Arguments:       None. 
 * Returns:         1 - success; 0 - failure.
 */
int
do_vision()
{
    if (living(environment(TO)))
    {
        environment(TO)->catch_tell("\n     Your vision blurs as a fine spider's "+
									"web seems to weave itself before your eyes.\n   ...you see before "+
									"you a busy marketplace...\n                 ...coals glow in a "+
									"shadow-draped room and you hear the clang of metal against metal.\n"+
									"      You feel a sense of urgency.\nYour blood pounds in your "+
									"ears and the strange webbing unravels.\n");
        SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
					  " was sent a vision.\n");
        return 1;
    }
    return 0;
}

/* 
 * Function name:   do_blood
 * Description:     The special effect alarm when this object is offered 
 *                  at an altar to Aclolthayr. It is Called by the altar,
 *                  through the function altar_special, below.
 * Arguments:       object altar - the altar that caused this function
 *                  to be called.
 */

void
do_blood(object altar)
{
    object metal;    
    
    tell_room(environment(altar), "The legs on the "+ altar->short() +
			  " seem to shift, causing the chains to rattle.\nIn a sudden, "+
			  "bewildering flash, the pool of blood at your feet is trans"+
			  "formed into a glossy sheet of silvery metal.\n");
	
    setuid();
    seteuid(getuid());
    metal=clone_object("/d/Avenir/common/holm/obj/quicksilver");
    metal->move(environment(altar), 1);
	
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
				  " caused blood to be transformed.\n");
	
    alarm_id = 0;
    alarm_id2 = 0;
}

/* 
 * Function name:   altar_special
 * Description:     The special effect when this object is offered at an altar 
 *                  to Aclolthayr. It is Called by the altar.
 * Arguments:       altar - The altar object. 
 * Returns:         1 - success; 0 - failure.
 */
int
altar_special(object altar, object player)
{
    if (alarm_id)
    {
        tell_object(player, "You've tried that already.\n");
        return 0;
    }
	
    /* Lets prevent multiple people from doing the quest with this sword. */
    if (query_prop(ALTAR_PROP) && (!player->query_prop(F_QUESTOR)))
    {
        tell_object(player, "The falchion is no longer an acceptable "+
					"offering.\n");
        return 0;
    }
    if (query_prop(ALTAR_PROP) && 
		(query_prop(ALTAR_PROP) != player->query_real_name()))
    {
        tell_object(player, "The falchion is no longer an acceptable "+
					"offering.\n");
        return 0;
    }
    if (!player->query_prop(I_MADE_BLOOD_OFFERING))
    {
		tell_object(player, "It must be cleansed in the blood sacrifice "+
					"before you can offer it.\n");
        return 1;
    }	
	
    tell_object(player, "You hold the "+ short() +" high in the air "+
				"above your head and extend it toward the "+ altar->short() +
				".\nSomething blows through you like a cool breeze, making "+
				"your nerve-endings tingle.\nEcstacy overwhelms you, pounding "+
				"into your head, forcing you to your knees.\nA cry of joy "+
				"and pain rips from your throat as the overwhelming Presence "+
				"of the goddess Aclolthayr settles fleetingly within your mind.\n");
	
    tell_room(environment(player), QCTNAME(player) +" holds "+ 
			  POSSESS(player) +" "+ short() +" high above "+ POSSESS(player) +
			  " head and extends it toward the "+ altar->short() +".\n"+
			  QCTNAME(player) +" falls to "+ POSSESS(player) +" knees, "+
			  "crying out a sound of both pleasure and pain.\n", player);
	
    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
				  " offered the falchion at altar.\n");
	
    add_prop(ALTAR_PROP, player->query_real_name());
    player->add_prop(F_QUESTOR, 1);
	
    if (player->query_prop(I_MADE_BLOOD_OFFERING))
    {
        alarm_id = set_alarm(200.0, 0.0, &do_vision());
        alarm_id2 = set_alarm( 100.0, 0.0, &do_blood(altar));
    }
    return 1;
}


/* EOF */
