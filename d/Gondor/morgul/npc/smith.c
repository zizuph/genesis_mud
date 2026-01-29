/*
 * /d/Gondor/minas/npc/calmacil.c
 *
 * This is the blacksmith in Minas Tirith, he will craft armours for you
 * or he will repair armours if necessary.
 *
 * Originally coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * Mercade, 21 december 1993; added rejection of OBJ_I_BROKEN armours
 * Olorin, 17-feb-1995; finally (?) fixed the problem with minstrels by
 *                      replacing trigger on say by add_action()
 * Gnadnar, 14-jul-1998: cleanup, conform to domain.rules
 */

#pragma strict_types

inherit "/d/Gondor/morgul/npc/npc_dunadan.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/lib/trade.c";

#include <const.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

static mixed	*Fixing;
static int	Testing;
static int	Order_alarm;

/* prototypes */
public void	create_dunadan();
public void	init_living();
public int	catch_say(string what);
public void	make_order(object player);
public void	enter_inv(object obj, object from);
public void	give_back_busy(object obj, object from);
public void	give_back_now(object obj, object from);
public void	give_back(object *things);
static void	test_armour(object *things);
public void	repair_armour_max(object *things);
public int	repair_the_armour(object *things);
public void	hammer_noise(string what);
public void	sweat_action();
public void	cool_noise(string what);
public void	heat_noise(string what);
public int	*can_afford(object player, int price);
public string	give_it_back();
public string	fix_it_for_me();
public string	i_would_like_to_order();
public void	add_introduced(string name);
public void	do_intro(object pl);
public int	query_knight_prestige();
public void	already_ordered();


/*
 * Function name:	create_dunadan
 * Description	:	set up the smith
 */
public void
create_dunadan()
{
    set_name("thaurmirdan");
    add_name("blacksmith");
    add_name("smith");
    set_dunedain_house("Belecthor");
    set_race_name("human");
    set_living_name("thaurmirdan");
    set_title("Armourer");
    set_adj(({"strong","dark-eyed"}));
    set_long(BSN("This is the master of the armoury, Thaurmirdan "
        + "the Armourer, the blacksmith of Minas "
        + "Morgul. His strong muscles and soot-blackened " 
        + "body tell of much time spent in front of a forge. "
        + "As you look at him, he nods at a "
        + "sign.")); 

    set_gender(G_MALE);
    set_alignment(-250);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    default_config_npc(95 + random(6));

    set_base_stat(SS_CON, (155 + random(6)));
    set_base_stat(SS_STR, (155 + random(6)));

    set_skill(SS_WEP_CLUB, (85 + random(6)));

    set_tell_active(1);

    set_chat_time(8);
    add_chat("What would you like to order?");
    add_chat("If you want something, just say you would like to order.");
    add_chat("Read the sign, it contains instructions for ordering.");
    add_act("@@hammer_noise");
    add_act("@@sweat_action");
    add_act("@@cool_noise");
    add_act("@@heat_noise"); 

    add_ask("give it back", VBFC_ME("give_it_back"));
    add_ask("fix it for me", VBFC_ME("fix_it_for_me"));
    add_ask("i would like to order", VBFC_ME("i_would_like_to_order"));

    config_default_trade();

    set_equipment( ({ (WEP_DIR + "smithhammer"), (ARM_DIR + "smithapron"), }) );
} /* create_dunadan */


/*
 * Function name:	init_living
 * Description	:	add "say" verbs to catch orders
 */
public void
init_living()
{
    ::init_living();

    add_action(catch_say, "say");
    add_action(catch_say, "'", 2);
} /* init_living */


/*
 * Function name:	catch_say
 * Description	:	catch people wanting to order
 * Arguments	:	string what -- whatever they said
 * Returns	:	int -- 0 (always ... so real 'say' happens too)
 */
public int
catch_say(string what)
{
    object	ord,
		tp = TP;
    string	who = tp->query_real_name(),
		dummy,
		vb = QVB;

    what = LOW(what);

    if (sscanf(what, "%s like to order%s", dummy, dummy) == 2)
    {
        if (objectp(ord = ENV(TO)->query_ordering()))
        {
            if (ord == tp)
            {
                set_alarm(0.0, 0.0, &command("say But you are already "
		    + "ordering!"));  
            }
	    else
	    {
            	set_alarm(0.0, 0.0, &command("say You will have to wait, "
		   + tp->query_nonmet_name() + "."));
	    }
        }
	else
	{
             Order_alarm = set_alarm(5.0, 0.0, &make_order(tp));
	}
    }
    else if (sscanf(what, "%sive it back%s", dummy, dummy) == 2)
    {
        if (!pointerp(Fixing) ||
	    !sizeof(Fixing))
        {
            set_alarm(0.0, 0.0, &command("say Give what back? I don't "
                + "understand?")); 
            set_alarm(0.5, 0.0, &command("shrug"));
        }
        else if (Fixing[1] != tp)
        {
            set_alarm(0.0, 0.0, &command("say I have nothing "
                + "belonging to you, "
                + tp->query_nonmet_name() + "."));
            set_alarm(0.5, 0.0, &command("shrug"));
        }
        else
        {
            set_alarm(4.0, 0.0, &give_back(Fixing));
        }
    }
    else if (sscanf(what, "%six it for me%s", dummy, dummy) == 2)
    {
        if (!pointerp(Fixing) ||
	    !sizeof(Fixing))
        {
            set_alarm(0.0, 0.0, &command("say I can fix your armour "
		+ "if you just give it to me first."));
            set_alarm(5.0, 0.0, &command("smile"));
        }
        else if (Fixing[1] != tp)
        {
            set_alarm(0.0, 0.0, &command("say You will have to wait "
		+ "until I am finished with this."));
            set_alarm(0.0, 0.0, &command("bow "+tp->query_real_name()));
        }
        else
        {
            set_alarm(1.0, 0.0, &command("say I will fix it with pleasure."));
            set_alarm(6.0, 0.0, "repair_armour_max", Fixing);
        }
    }
    return 0;
} /* catch_say */


/*
 * Function name:	make_order
 * Description	:	start the ordering process
 * Arguments	:	object player -- the customer
 */
public void
make_order(object player)
{
    environment()->place_order(player);
} /* make_order */


/*
 * Function name:	enter_inv
 * Description	:	mask parent so we repair armour given to us
 * Arguments	:	object obj -- the entering object
 * Description	:	object from -- its source
 */
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
    if (!objectp(from)) 
    {
        return; /* Was probably cloned into me. */
    }
    if (obj->check_armour()) 
    {
        if (sizeof(Fixing) ||
	    Testing) 
        {
            set_alarm(4.0, 0.0, &give_back_busy(obj, from));
        }
	else
	{
            Testing = 1;
            set_alarm(4.0, 0.0, &test_armour(({ obj, from })));
	}
    }
    else
    {
	set_alarm(4.0, 0.0, &give_back_now(obj, from));
    }
} /* enter_inv */


/*
 * Function name:	give_back_busy
 * Description	:	give back an object because we're busy
 * Arguments	:	object obj -- the object to return
 *			object from -- its source
 */
public void
give_back_busy(object obj, object from)
{
    command("say If you could just wait a minute, "
        + from->query_nonmet_name()+".");
    if (!Fixing) 
    {
        command("say I'll look at it when I have the time.");
    }
    else 
    {
        command("say I'll look at it when I have dealt with the "+
            Fixing[1]->query_nonmet_name()+".");
    }
    command("give "+OB_NAME(obj)+" to "+from->query_real_name());
    if (ENV(obj) == TO)
    {
        command("drop " + OB_NAME(obj));
    }
} /* give_back_busy */


/*
 * Function name:	give_back_now
 * Description	:	return non-armour object
 * Arguments	:	object obj -- the object to return
 *			object from -- its source
 */
public void
give_back_now(object obj, object from)
{
    command("say You'd better keep that, " + from->query_nonmet_name() + ".");
    command("give " + OB_NAME(obj) + " to " + from->query_real_name());
    if (ENV(obj) == TO)
    {
        command("drop " + OB_NAME(obj));
    }
    Fixing = 0;
} /* give_back_busy */


/*
 * Function name:	give_back
 * Description	:	return fixed armour
 * Arguments	:	object obj -- the object to return
 *			object from -- its source
 */
public void
give_back(object *things)
{
    if (!living(things[1])) 
    {
        command("say I wonder where this "+things[0]->query_name()+
            " came from. I'll drop it here.");
    }
    else 
    {
        command("say Here is your "+things[0]->query_name()+
            ", "+things[1]->query_nonmet_name()+"!");  
    }
    command("give "+things[0]->query_name()+" to " +
        things[1]->query_real_name());  
    if (ENV(things[0]) == TO) 
    {
        command("drop "+things[0]->query_name());
    }
    Fixing = 0;
} /* give_back */


/*
 * Function name:	test_armour
 * Description	:	decide whether we can fix an armour
 * Arguments	:	object *things -- array of the armour and its source
 */
static void
test_armour(object *things)
{
    int		cond,
		rep,
		price;
    object	arm,
		pl;
    arm = things[0];
    pl = things[1];

    /* He cannot fix broken objects, /Mercade */
    if (arm->query_prop(OBJ_I_BROKEN))
    {
        command("say This "+arm->query_name()+" is broken, I cannot fix it.");
        set_alarm(4.0, 0.0, &give_back(things));
        Testing = 0;
        return;
    }

    cond = arm->query_condition();
    rep = arm->query_repair();
    if (!cond)
    {
        command("say This "+arm->query_name()+" is in excellent condition!");
        command("say I don't need to do anything with it.");
        set_alarm(4.0, 0.0, &give_back(things));
        Testing = 0;
        return;
    }
    price = (cond/2+2-rep);
    if (rep) 
    {
        command("say I notice this piece of "+arm->query_name()+" has been fixed before.");
        if (F_LEGAL_ARMOUR_REPAIR(rep+1,cond)) 
        {
            command("say It can still be fixed though. I will see what I can do.");
            command("say It will cost "+price+" silver to fix.");
            command("say So if you say 'fix it for me', I will do what I can.");
            Fixing = (({ things[0], things[1] }));
            Testing = 0;
            return;
        }
        command("say It has been fixed as much as possible, I can do nothing more.");
        command("sigh");
        set_alarm(4.0, 0.0, &give_back(things));
        Testing = 0;
        return;
    }
    command("say This "+arm->query_name()+" is damaged. I can fix it for...hmm..");
    command("say ...about "+price+" silver I guess. Just say 'fix it for me'.");
    Fixing = (({ things[0], things[1] }));
    Testing = 0;
    return;
} /* test_armour */


/*
 * Function name:	repair_armour_max
 * Description	:	fix the armour completely (if possible)
 * Arguments	:	object *things -- array of the armour and its source
 */
public void
repair_armour_max(object *things)
{
    object	arm,
		player;
    int		rep,
		orig_rep,
		cond,
		price;

    player = things[1];
    arm = things[0];
    orig_rep = arm->query_repair();
    rep = arm->query_repair();
    cond = arm->query_condition();

    while (F_LEGAL_ARMOUR_REPAIR(rep+1, cond))
    {
	if (!repair_the_armour(Fixing))
	{
	    if(!(arm->query_value()))
	    {
		/* armour is still broken */
		command("hmm");
		command("say I'm afraid I didn't manage to fix your armour.");
		command("say Too bad, all this work in vain!");
		command("say Here, take it back!");
	    }
	    else if (rep>orig_rep)
	    {
		price = (rep - orig_rep);
		pay((price*12), player, 0, 0, 0, 0, 0);
		tell_object(player, "You pay "+price+" silver for the repair.\n");
	    }
	    set_alarm(4.0, 0.0, &give_back(things));
	    return;
	}
	rep++;
    }
    if (!arm->query_value())
    {
	/* armour is still broken */
	command("hmm");
	command("say I'm afraid I didn't manage to fix your armour.");
	command("say Too bad, all this work in vain!");
	command("say Here, take it back!");
    }
    else
    {
	price = (rep - orig_rep);
	pay((price*12), player, 0, 0, 0, 0, 0);
	tell_object(player, "You pay "+price+" silver for the repair.\n");
    }
    set_alarm(4.0, 0.0, &give_back(things));
    return;
} /* repair_armour_max */


/*
 * Function name:	repair_the_armour
 * Description	:	repair armour one level
 * Arguments	:	object *things -- array of the armour and its source
 * Returns	:	0 if can't afford it, 1 if can
 */
public int
repair_the_armour(object *things)
{
    object	arm,
		player;
    arm = things[0];
    player = things[1];

    /* this "12" is the cost of just one repair step, not the entire job */
    if (!pointerp(can_afford(player, 12)))
    {
        command("say You can't afford to repair the "+arm->query_name()+" more.");
        return 0;
    }
    arm->set_repair(arm->query_repair()+1);
    set_alarm(2.0, 0.0, &hammer_noise("the " + arm->short()));
    return 1;
} /* repair_the_armour */


/*
 * Function name:	hammer_noise
 * Description	:	hammer on something
 * Arguments	:	string what -- the thing to hammer
 */
public void
hammer_noise(string what)
{
    tell_room(environment(TO),
	QCTNAME(TO)+" hammers on "+
	(strlen(what) ? what : "a glowing piece of metal")+".\n");
} /* hammer_noise */


/*
 * Function name:	sweat_action
 * Description	:	wipe brow
 */
public void
sweat_action()
{
  tell_room(environment(TO),
	QCTNAME(TO)+" wipes the sweat off his face.\n");
} /* sweat_action */


/*
 * Function name:	cool_noise
 * Description	:	cool something down
 * Arguments	:	string what -- the thing to cool
 */
public void
cool_noise(string what)
{
  tell_room(environment(TO),
	QCTNAME(TO)+" dips "+
	(strlen(what) ? what : "a glowing piece of metal")+" in a bucket of water.\n"+
	"A cloud of steam rises as the hot metal cools down.\n");
} /* cool_noise */


/*
 * Function name:	heat_noise
 * Description	:	heat something up
 * Arguments	:	string what -- the thing to heat
 */
public void
heat_noise(string what)
{
  tell_room(environment(TO),
	QCTNAME(TO)+" puts "+
	(strlen(what) ? what : "a piece of metal")+" into the hot forge,\n"+
	"using his pliers to turn the glowing coals around it.\n");
} /* heat_noise */


/*
 * Function name:	can_afford
 * Description	:	pay for the repair
 * Arguments	:	object player -- the customer
 *			int price -- how much to pay
 * Returns	:       An array describing the object payed and the change it got
 *	                Unless something went wrong, then it returns:
 *	                  0 - Noone to pay the price found
 *			  1 - The specified money is not enough to pay the price
 *	 		  2 - Choosed to pay with money object haven't got
 *	 		  3 - Haven't got enough money
 *	  		  4 - Can't pay the price after we compare what player has
 *	 		        to what we accept, i.e. can't pay in acceptable coins
 *	                Also, the last item in the array holds error code from the
 *	                money moving routine.
 *	                If > 0 then the player couldn't hold the money it
 *	 		    was getting and dropped it.
 *	                If = -1 then one couldn't move the money from the object
 *	                    that was specified.
 *	                Normally you don't have to bother at all about this one.
 */
public int *
can_afford(object player, int price)
{
    return pay(price, player, 0, 1, 0, 0, 0);
} /* can_afford */


/*
 * Function name:	give_it_back
 * Description	:	respond to "ask calmacil give it back"
 * Returns	:	string -- "" (response is handled in catch_say)
 */
public string
give_it_back()
{
    catch_say("give it back");
    return "";
} /* give_it_back */


/*
 * Function name:	fix_it_for_me
 * Description	:	respond to "ask calmacil fix it for me"
 * Returns	:	string -- "" (response is handled in catch_say)
 */
public string
fix_it_for_me()
{
    catch_say("fix it for me");
    return "";
} /* fix_it_for_me */


/*
 * Function name:	i_would_like_to_order
 * Description	:	respond to "ask calmacil i would like to order"
 * Returns	:	string -- "" (response is handled in catch_say)
 */
public string
i_would_like_to_order()
{
    catch_say("i would like to order");
    return "";
} /* i_would_like_to_order */


/*
 * Function name:	add_introduced
 * Description	:	schedule response to introductions
 * Arguments	:	string name -- name of person who intro'd
 */
public void
add_introduced(string name)
{
    object  pl;

    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond.
     */
    if (objectp(pl = present(name, ENV())) &&
	interactive(pl) &&
    	(!pl->query_met(query_name()) ||
	 pl->query_wiz_level()))
    {
	set_alarm(4.0, 0.0, &do_intro(pl));
    }
} /* add_introduced */


/*
 * Function name:	do_intro
 * Description	:	introduce ourself
 * Arguments	:	object pl -- the person to intro to
 */
public void
do_intro(object pl)
{
    string  name;

    if (objectp(pl) &&
	ENV(pl) == ENV(TO) &&
        CAN_SEE_IN_ROOM(TO) &&
	CAN_SEE(TO, pl))
    {
	name = pl->query_name();
	command("say Hail, "+name+"!");
	command("introduce me to "+name);
    }
} /* do_intro */

/* killing law-abiding merchants -- tsk tsk */
public int query_knight_prestige() { return -5; }

/*
 * Function name:	already_ordered
 * Descripition	:	remove our alarm if player is typing ahead
 */
public void
already_ordered()
{
    if (Order_alarm)
    {
	remove_alarm(Order_alarm);
	Order_alarm = 0;
    }
} /* already_ordered */
