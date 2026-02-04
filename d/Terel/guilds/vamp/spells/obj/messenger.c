/* Novo May 2008
 *
 * updated by Lilith  March 2009
 *   -added weight and volume for messengers it was defaulting to 70kilo
 * updated by Petros  April 2009
 *   -70 kilo is default for default_config_mobile. Lilith incorrectly
 *    set OBJ_I_WEIGHT instead of CONT_I_WEIGHT. Corrected this so that
 *    the weight is correct. Bats and Rats weigh less. Wolves should
 *    weigh more.
 */

#include "../../guild.h"

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

#define A_CLAWS 0
#define A_TEETH 1
 
#define H_HEAD 0
#define H_BODY 1

#define TIME_FACTOR 7
#define MAX_TRIES 10

inherit "/std/messenger";
inherit SPELLOBJ_DIR+"spell_obj";

public void 
create_messenger()
{
    default_config_creature(20);
    
    set_attack_unarmed(A_CLAWS, 15, 15, W_SLASH, 10, 
        "claws");
    set_attack_unarmed(A_TEETH, 15, 15, W_SLASH, 10, 
        "sharp teeth");
 
    set_hitloc_unarmed(H_HEAD, ({15, 15, 15, 15 }), 20, 
        "head");
    set_hitloc_unarmed(H_BODY, ({15, 15, 15, 15 }), 80, 
        "body");
    set_short(0); // allow the short to be generated automatically
    switch (random(3))
    {
        case 0:
            set_race_name("bat");
            set_name("bat");
            set_mm_in("flies in.");
            set_mm_out("flies out.");
            set_adj( ({
            one_of_list( ({
                "hairy-legged", 
                "white-winged",
                "tiny",
                "rabid",
                })),
            one_of_list( ({
                "vampire", 
                "fruit",
                })) }));
            set_long("This is a large-bodied bat, with small but broad "+
            "wings. The wings and membranes are black. Dark grey hair "+
            "covers its body and its large pointed ears. Its head jets "+
            "out directly from its body, making it look relatively "+
            "small. By contrast, its sharp teeth seem to be on the verge "+
            "of swooping out of its little jaws.\n");
            // Rats don't weigh as much as 70 kgs
            add_prop(CONT_I_WEIGHT, 1000);
            add_prop(CONT_I_VOLUME, 1000);   
            break;
        case 1:
            set_race_name("rat");
            set_name("rat");
            set_mm_in("scurries in.");
            set_mm_out("scurries out.");
            set_adj( ({
            one_of_list( ({
                "large", 
                "frightened",
                "tiny",
                "rabid",
                })),
            one_of_list( ({
                "long-tailed", 
                "short-tailed",
                "mottled",
                "noisy"
                })) }));
            set_long("This rat has its tail longer than its and body "+
            "combined. While the tail is entirely naked, the rat itself "+
            "has an uneven darkish fur. On its back, however, the fur "+
            "and even the skin have begun to peel, baring the very flesh "+ 
            "of this filthy creature. It is most likely a carrier of "+
            "fleas or disease.\n");
            // Bats don't weigh as much as 70 kgs
            add_prop(CONT_I_WEIGHT, 1000);
            add_prop(CONT_I_VOLUME, 1000);   
            break;
        default:
            set_race_name("wolf");
            set_name("wolf");
            set_adj( ({
            one_of_list( ({
                "big", 
                "wicked",
                "vicious",
                "lanky",
                "husky",
                })),
            one_of_list( ({
                "long-tailed", 
                "wild-eyed",
                "white",
                })) }));
            set_long("Wolves and dogs sometimes look alike, but there is "+
            "no mistaking here. This creature has a narrower chest, but "+
            "longer legs and a wider head than any dog you've ever seen. "+
            "Its coat is both shadowy and silvery, with darker and "+
            "lighter nuances blending perfectly with one another. Though "+
            "wide, its head tapers forward, ending in a pair of massive "+
            "jaws.\n");
            set_mm_in("lopes in.");
            set_mm_out("lopes out.");
    }
    
    add_name("messenger");
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_AWARENESS,100);
    add_prop(LIVE_I_SEE_DARK,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);

    set_spell_effect_desc("control your messenger");

    // Set Messaging Options
    set_can_deliver_indoors(1);
    set_number_of_uses(MAX_TRIES);        
}

varargs public int
dispel_spell_effect(object dispeller)
{

    move_living("X",ROOM_DIR+"wait_room");	
    remove_spell_effect_object();
    return 1;
}

public int
query_delivery_time(object sender, object receiver)
{       
    if (!sender || !environment(sender))
    {
        return 0;
    }
    if (!receiver || !environment(receiver))
    {
        return 0;
    }

    string * start=explode(MASTER_OB(all_environment(receiver)[-1..][0]),"/");
    string * end=explode(MASTER_OB(all_environment(sender)[-1..][0]),"/");

    int time=1+max(sizeof(start),sizeof(end));
    
    for (int i=0;i<min(sizeof(start),sizeof(end));i++)
    {
        if (start[i]==end[i])
        {
            time--;
        }
        else
        {
            return time * TIME_FACTOR;
        }
    }
    return time * TIME_FACTOR;
}

public int
start()
{
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }
    // Call move_living twice, once to generate the arrival message,
    // and once to put it in the caster's inventory.
    move_living("X",environment(effect_caster));
    move(effect_caster, 1);
    return 1;
}

public void
hook_send_message()
{
    write("You hand your message to the " + short() + ".\n");
	say(QCTNAME(this_player()) + " hands a message to " 
	    + this_player()->query_possessive() + " " 
	    + QNAME(this_object()) + ".\n");
	tell_room(environment(this_player()), QCTNAME(this_object()) + " " 
	    + query_mm_out() + "\n");
}

public void
hook_resend_message()
{
    write("You instruct the " + short() + " to try again.\n");
	say(QCTNAME(this_player()) + " convinces " 
	    + this_player()->query_possessive() + " " + short() 
	    + " to try again.\n");
	tell_room(environment(this_player()), QCTNAME(this_object()) + " " 
	    + query_mm_out() + "\n");
}

public void     
hook_deliver_message_failure(object sender)
{
	tell_object(sender, "Your " + short() + " returns unable to find "
	    + capitalize(gReceiver) + ".\n");
	tell_room(environment(sender), QCNAME(this_object()) + " arrives "
	    + "jogging and hands " + QTNAME(sender) + " a message.\n", sender);
}

public void     
hook_deliver_message_success(object receiver)
{
	receiver->catch_msg(QCNAME(this_object()) + " arrives and gives you a "
    	+ "message from " + capitalize(gSender) + ".\n");
	tell_room(environment(receiver), QCNAME(this_object()) + " arrives "
	    + "and gives " + QTNAME(receiver) + " a message.\n", receiver);
}

public void
hook_messenger_returns_home()
{
	object room;

	if (living(room = environment(this_object())))
		room = environment(room);

	tell_room(room, QCTNAME(this_object()) + " " + query_mm_out() + "\n");
}

/*
 * Function:    hook_cannot_deliver_player_unavailable
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to someone who is either LD or not in the game.
 * Arguments:   who - the person the sender is trying to send to
 * Returns:     nothing
 */
public void
hook_cannot_deliver_player_unavailable(string who)
{
    notify_fail(capitalize(LANG_THESHORT(this_object()))
       + " looks at you confusedly, unable to understand who " 
       + capitalize(who) + " is!\n");
}
