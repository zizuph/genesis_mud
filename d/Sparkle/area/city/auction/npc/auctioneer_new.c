/*
 *  /d/Sparkle/area/city/auction/npc/auctioneer.c
 *
 *  Auctioneer that handles auction transactions
 *
 *  This auctioneer will allow players to start up
 *  auctions to sell items to other players
 *  This NPC will manage giving/receiving the auction items
 *  as well as paying the player any money owed.
 *
 *  Auctions can last up to MAX_AUCTION_TIME (72) hours, in one
 *  hour increments. The auctioneer will take AUCTION_FEE_PERCENT
 *  (10) as his fee, to keep players from using the auction house as a
 *  drop room. Also, starting bids of 20+ platinum will require a
 *  deposit to ensure the players aren't doing the same.
 *
 *  Ogres are blocked from selling, as their speech does not yet invoke
 *  the speech_hook needed to create an auction.
 *
 *  Presently, kender can sell items, but this may be changed if they
 *  abuse their 'borrow' ability.
 *
 *  Created March 2008, by Novo
 *
 * 2016-09-02 - Cotillion
 * - Fixed one of the auctioneer stuck issues
 * - Fixed one case where he revealed player names
 *
 * 2020-08 - Lucius
 * - Remove get_countdown_seconds() check as that function/timer
 *   were removed.
 * - Reduced some of the alarms to prevent excessive waiting
 * - Fix coins not merging
 *
 */
inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <files.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <const.h>
#include <time.h>

#include "greeting.h"

//Various auction preparing states
#define AUCTION_STATE_NONE          (0)
#define AUCTION_STATE_START_PRICE   (1)
#define AUCTION_STATE_END_PRICE     (2)
#define AUCTION_STATE_ANON          (3)
#define AUCTION_STATE_NUM_HOURS     (4)
#define AUCTION_STATE_CONFIRM       (5)
#define AUCTION_STATE_FINISHING     (6)

//Maximum number of hours for an auction
#define MAX_AUCTION_TIME            72


#define WHITELIST ({ "eggshard" })

//Quest properties
#define AUCTIONEER_DID_STAND        "_auctioneer_did_stand"
#define AUCTIONEER_NO_GREET         "_auctioneer_no_greet"

//other properties
#define AUCTION_MISSING_ITEMS       "_auction_missing_items"

//Details for the auction we wish to create
private object Auction_obj;
private string Seller;
private int Cancel_aid;
private int Auction_state=0;
private int Minimum_bid=0;
private int Maximum_bid=0;
private int Auction_hours=0;
private int Public_auction=0;
private int Deposit=0;
private int Last_quest_time=0;

//Prototypes
void arm_me();
void inform_player(int state);
void cancel_auction();
void return_item(object obj,string target);
void return_prize(object player, int aid);
public void return_money(object player);
public void give_paddle(object player);
public int allowed_paddle(object player);
public int has_pending_action(object player);
public void reset_auction();
public void complete_auction();
public void complete_auction2();
private void remove_case(object old_case);

private static string *type = ({ "dwarf" }),
		      *phys = ({ "broad-shouldered" }),
		      *mental = ({ "clever" });
void
create_monster()
{
    set_living_name("rommik");
    set_name(({"rommik","fankum"}));
    set_title("Fankum, Master Auctioneer");
    set_race_name("dwarf");

    set_adj(({
	    one_of_list(mental),
	    one_of_list(phys),
    }));

    set_gender(G_MALE);
    set_alignment(0);

    add_name(({"_auctioneer_", "auctioneer"}));

    default_config_npc(120 + random(20));

    set_long("This @@short@@ is an auctioneer. He makes "+
	"his living trading items for a fee. His eyes have a cunning "+
	"look to them, as if he has been in business for quite some time.\n");

    set_skill(SS_DEFENCE,       60+random(30));
    set_skill(SS_WEP_KNIFE,     60+random(30));
    set_skill(SS_WEP_AXE,       60+random(30));
    set_skill(SS_WEP_POLEARM,   60+random(30));
    set_skill(SS_WEP_SWORD,     60+random(30));
    set_skill(SS_UNARM_COMBAT,  60+random(30));
    set_skill(SS_AWARENESS,     60+random(30));
    set_skill(SS_PARRY,         60+random(30));

    add_ask( ({ "auction", "auctions", "sell" }),
        "say I will auction items for ye. Simply give me "+
        "what ye wish to have auctioned.",1 );

    add_ask( ({ "help", "task", "quest", "rest","job","stand","podium" }),
	"@@ask_help@@" );

    add_ask( ({ "bid", "bidding", "buying" }),
        "say Take a look at the paddle, ye use that to bid. Ye can "+
        "even bid elsewhere, me servant will collect the platinum.",1 );

    add_ask( ({ "paddle" }),
        "say I give ye one when ye arrive. Ye can use it anywhere after "+
        "that.",1 );

    set_act_time(25);

    add_act( "shout Come see some of the finest wares in all the lands!",1);
    add_act( "shout Amazing wares! The cheapest prices!",1);
    add_act( "say Come bid on these wares! Look at all the valuables "+
       "in these cases up for sale!");

    add_act( "say Not many are willing to stand on the podium and "+
	"do my work these days.");

    add_act( "say I be good at this job, sure ... but I wish someone "+
	"could fill in for me now and then. A dwarf needs a rest from time "+
	"to time, after all!");

    add_act( "say Show me what you wish to sell, and I will tell ye "+
       "what it is worth.");

    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);

    arm_me();
    reset_auction();
}

void
arm_me()
{
    clone_object(PADDLE)->move(TO);
    command("hold paddle");
}

public string
singular_short(object ob)
{
    if (ob->query_prop(HEAP_I_IS))
        return ob->singular_short();
    return ob->short();
}

/*
 * How many plats can the player carry?
 */
public int
can_carry(object player)
{
    int rw = player->query_prop(CONT_I_MAX_WEIGHT) - player->query_prop(OBJ_I_WEIGHT);
    int rv = player->volume_left() / MONEY_VOLUME[MONEY_PC_INDEX];

    return max(0, min(rw / MONEY_WEIGHT[MONEY_PC_INDEX], rv / MONEY_VOLUME[MONEY_PC_INDEX]));
}

/*
 * Function name: enter_inv
 * Description  : This function is called each time an object enters the
 *                inventory of this object. If you mask it, be sure that
 *                you _always_ call the ::enter_inv(ob, old) function.
 * Arguments    : object ob  - the object entering our inventory.
 *                object old - wherever 'ob' came from. This can be 0.
 */
void
enter_inv(object ob, object old)
{
    ::enter_inv(ob,old);

    if (!objectp(old) || !interactive(old))
        return;

    if (!get_available() || !CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO,old))
    {
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (!allowed_paddle(old))
    {
        command("say I do not trust ye yet!");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (ob->query_prop(HEAP_I_IS) && ob->num_heap() > 10 && (ob->num_heap() % 10) != 0)
    {
        command("say If ye want me to sell that many ye have to give me an "+
	    "amount I can count in tens!");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (ob->query_keep() && !ob->query_unsellable())
    {
        command("say Ye are keeping that object. If ye wish to auction "+
	    "it, <unkeep> it first.");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (ob->query_prop(OBJ_M_NO_SELL) &&
        member_array(ob->query_name(),WHITELIST)<0)
    {
        command("say That doesn't look good to sell.");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (ob->query_prop(LIVE_I_IS))
    {
        command("say That might be dead before it is sold.");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (ob->query_prop(OBJ_I_BROKEN))
    {
        command("say Would ye buy something already broke?");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    if (ob->query_prop(CONT_I_IN))
    {
        command("say Ye can not sell containers.");
        set_alarm(0.1,0.0,&return_item(ob,old->query_real_name()));
        return;
    }

    Seller = old->query_real_name();
    Auction_obj = ob;
    Auction_state = AUCTION_STATE_START_PRICE;

    set_occupied();
    set_alarm(2.0,0.0,&inform_player(Auction_state));
    Cancel_aid = set_alarm(60.0,0.0,cancel_auction);
}


/*
 * Function name: inform_player
 * Description  : This function is give the seller details on what they
                  need to do next, to get the auction going
 * Arguments    : int state - one of the pre-defined states
 */
void
inform_player(int state)
{
    if (Auction_state==AUCTION_STATE_NONE)
        return;

    if (!objectp(Auction_obj) || environment(Auction_obj)!=TO)
    {
        command("say Strange, where did it go? I suppose we'll have no "+
	    "auction then.");
        cancel_auction();
        return;
    }

    string item_short = Auction_obj->short();
    if (Auction_obj->query_prop(HEAP_I_IS) && Auction_obj->num_heap() > 1)
    {
        item_short = "set of " + LANG_WNUM(Auction_obj->num_heap()) + " " +
            Auction_obj->plural_short();
    }

    switch (state)
    {
        case AUCTION_STATE_START_PRICE:
            int price=AUCTION_HOUSE->get_average_selling_price(singular_short(Auction_obj));

            command("say Ahh, what a lovely "+ item_short
            + ". I am sure it will fetch a great price. "
            + (price ? "It often earns "+price+" platinum each. " : "")
            + "How many platinum do ye want the minimum bid to be?"
            + " If your starting bid is more than 20 platinum, "
            + "I will require ye to leave a deposit for 30% of this "
            + "bid. If there is no buyer, I will keep this deposit. If "
            + "the item is sold, ye will get yer full deposit back.");
            command("say Please <say> or <ask> me the price ye'd like "
            + "me to set the minimum bid at.");
            break;

        case AUCTION_STATE_END_PRICE:
            command("say The auction will start bidding at "
            + LANG_NUM2WORD(Minimum_bid) + " platinum. "
            + (Deposit ? "Your " + LANG_NUM2WORD(Deposit) + " platinum "
            + "deposit will be returned if the item is sold. " : "")
            + "Do ye want to have a maximum price? Your "
            + item_short + " can be sold immediately when "
            + "ye have a high enough bid. Tell me whether ye want no "
            + "maximum, or how much ye want the maximum bid to be.");
            break;

        case AUCTION_STATE_ANON:
            command("say " +
            (Maximum_bid ? "I will end the bidding if I get a bid of " +
            LANG_NUM2WORD(Maximum_bid) + " platinum." :
            "I will accept bids until the end of the auction.") +
            " Would ye like an anonymous, or public auction?" +
            " A public auction will show everyone who is " +
            "bidding and selling the item.");
            break;

        case AUCTION_STATE_NUM_HOURS:
            command("say Ye will have " +
            ( Public_auction ? "a public" : "an anonymous" ) +
            " auction. How many hours would ye like the auction to " +
            "last? Ye can choose have an auction for up to " +
            LANG_NUM2WORD(MAX_AUCTION_TIME)+ " hours.");
            break;

        case AUCTION_STATE_CONFIRM:
            command("say Your auction will last " +
            LANG_NUM2WORD(Auction_hours) +
            " hour" + (Auction_hours > 1 ? "s" : "" ) +
            ". Is your auction acceptable? I will take a "+
            LANG_NUM2WORD(AUCTION_FEE_PERCENT) +
            " percent fee from the winning bid.");
            break;

        case AUCTION_STATE_FINISHING:
            command("whistle loudly");
            break;
    }
}

/*
 * Function name: cancel_auction
 * Description  : Bail on this auction, due to time out or other problem
 */
void
cancel_auction()
{
    Auction_state = AUCTION_STATE_NONE;
    set_available();

    command("say Perhaps another time, then.");

    if (objectp(Auction_obj))
        return_item(Auction_obj,Seller);

    if (Deposit)
    {
        AUCTION_HOUSE->add_platinum_due(Seller,Deposit);
        add_waiting(Seller);
    }

    if (Cancel_aid)
        remove_alarm(Cancel_aid);

    reset_auction();
    Cancel_aid = 0;
}

/*
 * Function name: complete_auction
 * Description  : We have everything we need - make the actual auction
 */
public void
complete_auction()
{
    if (Auction_state==AUCTION_STATE_NONE)
        return;

    if (!objectp(Auction_obj) || environment(Auction_obj)!=TO)
    {
        command("say Strange, where did it go? I suppose we'll have no "+
	    "auction then.");
        cancel_auction();
        return;
    }

    Auction_state = AUCTION_STATE_FINISHING;
    remove_alarm(Cancel_aid);

    set_alarm(5.0,0.0,complete_auction2);
    set_alarm(2.0,0.0,&inform_player(Auction_state));
}

/*
 * Function name: complete_auction2
 * Description  : Final step, inform the auction_house of the auction
 */
public void
complete_auction2()
{
    if (Auction_state==AUCTION_STATE_NONE)
        return;

    if (!objectp(Auction_obj) || environment(Auction_obj)!=TO)
    {
        command("say Strange, where did it go? I suppose we'll have no "+
	    "auction then.");
        cancel_auction();
        return;
    }

    tell_room(environment(TO),"A spindly old gnome enters the tent, "+
	"pushing a marble pedestal with a large glass case on top.\n",
	({ }), TO);

    object container = clone_object(OBJ_DIR+"auction_container");
    container->move(environment(TO));
    Auction_obj->move(container,1);

    command("emote opens the case and puts the "+ Auction_obj->short() +
	" inside. He then closes and locks the case.");
    tell_room(environment(TO),"The gnome grunts and leaves again.\n",
	({ }), TO);

    if (!objectp(Auction_obj) || environment(Auction_obj)!=container)
    {
        command("say Strange, where did it go? I suppose we'll have no "+
	    "auction then.");
        container->remove_object();
        cancel_auction();
        return;
    }

    mapping result = AUCTION_HOUSE->create_auction(Auction_obj,Minimum_bid,
                                  Maximum_bid,Public_auction,Auction_hours,
                                  Seller,Deposit);

    container->set_auction(result["id"]);
    reset_auction();
    set_available();

    set_alarm(15.0,0.0,&remove_case(container));
}

/*
 * Function name: reset_auction
 * Description  : Clean out variables from a previous auction
 */
void
reset_auction()
{
    Auction_state = AUCTION_STATE_NONE;
    Minimum_bid = Maximum_bid = 0;
    Auction_hours = Public_auction = 0;
    Deposit = Auction_obj = 0;
    Seller = "";
}

/*
 * Function name: return_item
 * Description  : Give the player his money/purchased item
 */
void
return_item(object obj,string target)
{
    if (!objectp(obj))
        return;

    if (environment(obj)!=TO)
        return;

    command("say Here ye go.");

    string ob_name = OB_NAME(obj);

    if (obj->query_prop(HEAP_I_IS))
        ob_name = obj->query_pname();

    command("give " + ob_name + " to " + target);

    if (environment(obj) == TO)
    {
        command("shrug");
        command("drop " + ob_name);
    }

    if (environment(obj) == TO)
    {
        command("emote drops the "+ obj->short() + ".");
        obj->move(environment(TO),1);
    }
}

/*
 * Function name: init_living
 * Description  : This function is called each time a living enters the
 *                environment of this object. If you mask it, be sure that
 *                you _always_ call the ::init_living() function.
 */
void
init_living()
{
    ::init_living();
     notify_player_entered();
}

/*
 * Function name: default_react
 * Description  : This is what the NPC does when the player asks it
 *                something strange
 */
private static string *reacts = ({
        "emote peers at you with a blank look.",
        "emote raises an eyebrow, but doesn't seem to know anything.",
        "say I be knowin' nothing about that.",
        "say Sorry then, but I have nothin to say to that.",
        "emote peers at you, but has no response."
});

public void
default_react()
{
    command(one_of_list(reacts));
}

public void
react_quest(object actor,string str,int target)
{
    if (parse_command(str,({ }), "[i] [am] 'ready'"))
    {
	if ((time() - Last_quest_time) < 1200)
	{
	    command("say I'm always thankful for a break, but I just "+
		"got back from one. Maybe in a little while I'll feel "+
		"like taking another.");
	    return;
	}

	command("say Good luck! I will return when ye are done.");
	command("emote heads back into the store room.");
	TO->move(AUCTION_DATA_STORE);
	actor->remove_prop(AUCTIONEER_DID_STAND);
	actor->add_prop(AUCTIONEER_NO_GREET,1);
	AUCTION_HOUSE->start_quest_auction(actor);
	Last_quest_time = time();
	return;
    }

    switch(str)
    {
        case "yes":
        case "help":
        case "rest":
        case "task":
        case "job":
        case "auctioneer":
	    command("say All this auction work takes so much time, I do "+
		"not get enough rest!  What I need ye to do is to take over "+
		"as auctioneer for me.  Ye just need to know the three "+
		"steps.");
	    break;

        case "steps":
        case "parts":
        case "three steps":
        case "three parts":
	    command("say There are three parts to an auction - the "+
		"start, the middle and the end.");
	    break;

        case "first part":
        case "first step":
        case "start":
        case "the start":
	    command("say The first step is easiest.  Ye wait until the "+
		"benches are full, and then ye <begin> the auction.");
	    break;

        case "second part":
        case "second step":
        case "middle":
        case "the middle":
	    command("say The second step is the hardest.  Ye must <call> "+
		"out the next bid, so the bidders know how much ye want. If "+
		"ye see someone bid, you must <accept> bid from them.  Once "+
		"ye accept their bid, ye must call the next bid "+
		"so the others can bid more money.");
	    break;

        case "third part":
        case "third step":
        case "end":
        case "the end":
	    command("say If ye get no bids, <call> the next bid "+
		"three times.  After the last bid, ye should <exchange> the "+
		"money for the item.  When that is done, the auction is "+
		"complete!  Do a good job, and I will give ye a share of "+
		"the money");
	    command("say If ye understand all the steps, tell me you "+
		"are ready, and I will leave to get me rest.");
	    break;

        default:
	    if (target > 0)
		default_react();
    }
}

/*
 * Function name: speech_hook
 * Description  : This is how the NPC listens for the details of the
 *                auction. At each state it is waiting for information
 *                from the player.
 */
public void
speech_hook(string verb, object actor, string adverb, object *oblist,
    string text, int target)
{
    if (target < 0)
        return;

    if (!get_available() && actor->query_real_name()!=Seller)
        return;

    string str = lower_case(text);

    if (strlen(str) && str[strlen(str)-1]=='.')
        str=str[..strlen(str)-2];

    if (strlen(str) && str[strlen(str)-1]=='?')
        str=str[..strlen(str)-2];

    switch (Auction_state)
    {
        case AUCTION_STATE_START_PRICE:
            if (!parse_command(str, ({ }),
                "[i] [want] [a] [minimum] [bid] / [price] [of] %d "
                +"[platinum]", Minimum_bid))
            {
                break;
            }
            if (Minimum_bid<1)
            {
                command("say The minimum must be at least one platinum.");
                return;
            }
            if (Minimum_bid>20 && !actor->query_wiz_level())
            {
                int result=MONEY_MOVE(Minimum_bid*30/100,"platinum",
                    actor,0);
                if (result)
                {
                    command("say Ye must carry at least "
                    + LANG_NUM2WORD(Minimum_bid*30/100) +
                    " platinum for that minimum bid.");
                    return;
                }
                Deposit=Minimum_bid*30/100;

            }
            Auction_state=AUCTION_STATE_END_PRICE;
            remove_alarm(Cancel_aid);
            set_alarm(2.0,0.0,&inform_player(Auction_state));
            Cancel_aid=set_alarm(60.0,0.0,cancel_auction);
        return; //AUCTION_STATE_BEGIN_PRICE

        case AUCTION_STATE_END_PRICE:
            if (parse_command(str, ({ }),
                "[i] [want] 'no' [maximum] [bid] / [price] [.]"))
            {
                Maximum_bid=0;
                Auction_state=AUCTION_STATE_ANON;
                remove_alarm(Cancel_aid);
                set_alarm(2.0,0.0,&inform_player(Auction_state));
                Cancel_aid=set_alarm(60.0,0.0,cancel_auction);
                return;
            }

            if (!parse_command(str, ({ }),
                "[i] [want] [a] [maximum] [bid] / [price] [of] %d "
                +"[platinum] [.]", Maximum_bid))
            {
                break;
            }
            if (Maximum_bid<Minimum_bid)
            {
                command("say Your maximum bid must be at least "
                + LANG_NUM2WORD(Minimum_bid) + " platinum.");
                return;
            }
            Auction_state=AUCTION_STATE_ANON;
            remove_alarm(Cancel_aid);
            set_alarm(2.0,0.0,&inform_player(Auction_state));
            Cancel_aid=set_alarm(60.0,0.0,cancel_auction);
        return; //AUCTION_STATE_END_PRICE

        case AUCTION_STATE_ANON:
            string type;
            if (parse_command(str, ({ }),
                "[i] [want] [a] / [an] %w [auction]",type))
            {
                if (type!="public" && type!="anonymous")
                {
                    break;
                }

                Public_auction = (type == "public");
                Auction_state=AUCTION_STATE_NUM_HOURS;
                remove_alarm(Cancel_aid);
                set_alarm(2.0,0.0,&inform_player(Auction_state));
                Cancel_aid=set_alarm(60.0,0.0,cancel_auction);
                return;
            }
        break; //AUCTION_STATE_ANON

        case AUCTION_STATE_NUM_HOURS:
            if (parse_command(str, ({ }),
                "[i] [want] %d [hours] / [hour] ",Auction_hours))
            {

                if (Auction_hours<1)
                {
                    command("say That is too short for an auction!");
                    return;
                }
                if (Auction_hours>MAX_AUCTION_TIME)
                {
                    command("say That is too long for an auction!");
                    return;
                }

                int delay, interval;
                /* Calculate the delay if there's an uptime limit ... */
                if (delay = SECURITY->query_uptime_limit())
                {
                    delay += (SECURITY->query_start_time() - time());
                }

                if (delay <= 86400)
                {
                    interval = (delay <= 5400) ? 900 : 5400;
                }
                else
                {
                    interval = (delay <= 129600) ? 10800 : 21600;
                }

                int armageddon_hours = delay/3600;
                int max_auction_time = max(0, armageddon_hours - 1);

                int recoverable = ((Auction_obj->query_recover()) &&
		    			(!(Auction_obj->may_not_recover())));
                if (!recoverable && Auction_hours > max_auction_time)
                {
                    command("say This item will not survive Armageddon. " +
                            " The maximum auction time for this item is " +
                            max_auction_time + " hours. How many hours?");
                    return;
                }

                Auction_state=AUCTION_STATE_CONFIRM;
                remove_alarm(Cancel_aid);
                set_alarm(2.0,0.0,&inform_player(Auction_state));
                Cancel_aid=set_alarm(60.0,0.0,cancel_auction);
                return;
            }
        break; //AUCTION_STATE_NUM_HOURS

        case AUCTION_STATE_CONFIRM:
            if (parse_command(str, ({ }),
                "[it] [is] 'yes' / 'good' / 'acceptable' / 'ok' "))
            {

                complete_auction();
                return;
            }
            if (parse_command(str, ({ }),
                "[it] [is] 'no' / 'bad' / 'wrong' / 'unacceptable' "))
            {
                cancel_auction();
                return;
            }
        break; //AUCTION_STATE_CONFIRM

    }

    if (actor->query_prop(AUCTIONEER_DID_STAND))
    {
        set_alarm(2.0,0.0,&react_quest(actor,str,target));
    }

    if (target>0 && !ask_id(str) &&
        !actor->query_prop(AUCTIONEER_DID_STAND))
    {
        set_alarm(2.0,0.0,default_react);
    }
}

/*
 * Function name: emote_hook
 * Description  : This is how the NPC listens for the details of the
 *                auction. At present it allows the user to confirm
                  their auction with a nod.
 */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    int cmd_attr, int target)
{
    if (target < 0)
        return;

    if (Auction_state == AUCTION_STATE_NONE)
        return;

    if (actor->query_real_name() != Seller)
        return;

    switch (Auction_state)
    {
        case AUCTION_STATE_CONFIRM:
            if (emote=="shake")
            {
                cancel_auction();
                break;
            }
            if (emote="nod")
            {
                complete_auction();
            }
        break;
    }
}

/*
 * Function name: greet_player
 * Description  : The dwarf's greeting
 */
public void
greet_player(object player)
{
    string welcome = "";
    if (player->query_prop(AUCTIONEER_NO_GREET))
    {
        player->add_prop(AUCTIONEER_NO_GREET,
            player->query_prop(AUCTIONEER_NO_GREET) - 1);
    }
    else
    {
        welcome = "Welcome, " + QNAME(player) + "! ";
    }

    if (has_pending_action(player))
    {
	welcome += "Please stay here, I have something for you.";
    }

    if (strlen(welcome))
	command("say " + welcome);
}

/*
 * Function name: do_action
 * Description  : Checks if the player is owed anything, and
                  starts to hand it to them if needed.
 */
public void
do_action(object player)
{
    string name = player->query_real_name();

    if (!present(player, environment()))
    {
        command("say Where did they go?");
        return;
    }

    AUCTION_HOUSE->end_auction_check();

    int due = AUCTION_DATA_STORE->get_owed(name);

    if (due > 0 && can_carry(player) > 0)
    {
        set_occupied();
        command("say I have some money for you, "+ QNAME(player) +
	    ". Wait right there. ");
        command ("emote walks behind the counter.");
        set_alarm(2.5,0.0, &return_money(player));
        return;
    }

    int *won = AUCTION_DATA_STORE->get_won_auctions(name);
    // There is a chance that the won auction list contains items which are
    // not recoverable. In this case, we want to alert the user of this once
    // per login session, but not keep bothering them with it. We should also
    // allow them to continue to get their other working items.
    int *missing_items = player->query_prop(AUCTION_MISSING_ITEMS) || ({ });
    won = won - missing_items; // substract the missing items

    if (won && sizeof(won) && won[0])
    {
        set_occupied();

        mixed auction = AUCTION_DATA_STORE->get_auction(won[0]);
        command("say I have your " + auction["short"] +
            " for you, just a moment.");

        set_alarm(1.0, 0.0, &return_prize(player, won[0]));
		return;
    }

    //Todo: Change 1 to check the quest bit
    if (allowed_paddle(player) && !present("_auction_paddle_",player))
    {
        set_occupied();
        command("say Ye do not have an auction paddle. Let me get you one.");
        command("emote walks behind the counter.");
        set_alarm(1.5,0.0,&give_paddle(player));
        return;
    }
}

private void
remove_case(object old_case)
{
    if (environment(old_case) != environment(TO))
        return;

    tell_room(environment(TO),"A spindly old gnome enters the tent, "+
	"and pushes the glass case back out along with him.\n", ({ }), TO);

    if (!old_case->id("_auction_case_"))
    {
        write_file(LOG_DIR + "badcase",
            sprintf("%s trying to remove strange case %s %s\n",
            ctime(time()),
            file_name(old_case),
            this_player()->query_real_name(),
            ));
        return;
    }
    old_case->remove_object();
}

public void
return_prize(object player, int aid)
{
    object prize;

    // set_occupied is called before calling return_prize. Need to set_available
    // here or otherwise the auctioneer becomes stuck if the user becomes unavailable
    // due to linkdead, etc.
    set_available();

    if (!present(player, environment()))
    {
        command("say Where did they go?");
        return;
    }

    int *won = AUCTION_DATA_STORE->get_won_auctions(player->query_real_name());
    if (member_array(aid, won) < 0) {
        command("shrug");
        return;
    }

    try {
        prize = AUCTION_DATA_STORE->get_auction_item("" + aid);
    } catch(mixed a) {
        /* Runtime, item treated as missing */
    }

    if (!objectp(prize))
    {
        write_file(LOG_DIR + "missing",
            sprintf("%s %-14s due missing item from auction %d\n",
            ctime(time()),
            player->query_real_name(),
            aid));

        player->add_prop(AUCTION_MISSING_ITEMS,
            (player->query_prop(AUCTION_MISSING_ITEMS) || ({ })) + ({ aid }));

        command("say Where the bugger did it go!?");
	    command("shrug");

        mapping auction_data = AUCTION_DATA_STORE->get_auction(aid);
        int credit = auction_data["current_bid"];
		if (credit > 0)
		{
            command("say The item has vanished, so I will refund your money.");
		    AUCTION_HOUSE->add_platinum_due(player->query_real_name(), credit);
            AUCTION_HOUSE->delete_auction(aid);
            set_alarm(1.5, 0.0, &do_action(player));
			return;
		}
        if (has_pending_action(player))
        {
            // Finally, restart the process so that the player can get their next
            // item if it's there.
            command("say I need to investigate this, but don't leave yet. "+
		        "I have more for you.");
            set_alarm(1.5, 0.0, &do_action(player));
        }

	    return;
    }

    prize->move(TO,1);
    command("emote walks over to one of the glass cases.");
    command("emote unlocks the case.");
    command("emote takes the "+prize->short()+" from the case.");
    return_item(prize, player->query_real_name());
    command("whistle loudly");
    AUCTION_HOUSE->delete_auction(aid);

    write_file(AUCTION_LOG,
            sprintf("%s %-14s %i received the %30s\n",
            ctime(time()),
            player->query_real_name(),
            aid,
            prize->short()));

    if (has_pending_action(player))
    {
        command("say Don't leave yet, I have more for you.");
        set_alarm(1.5,0.0, &do_action(player));
    }
}

/*
 * Function name: give_paddle
 * Description  : Gets a new paddle for the player
 */
public void
give_paddle(object player)
{
    set_available();
    object paddle = clone_object(PADDLE);
    paddle->move(TO,1);

    command("emote returns from behind the counter with a new paddle.");
    return_item(paddle,player->query_real_name());

    if (has_pending_action(player))
        command("say Don't leave yet, I have more for you.");
}

/*
 * Function name: return_money
 * Description  : Returns platinum due to the player
 */
public void
return_money(object player)
{
    string name = player->query_real_name();
    int due = AUCTION_DATA_STORE->get_owed(name);

    set_available();

    if (due <= 0)
        return;

    command("emote returns from behind the counter.");
    command("say I have "+ LANG_NUM2WORD(due) +" platinum for you.");

    int carry = min(can_carry(player), due);
    object coins = MONEY_MAKE_PC(carry);

    if (!carry) {
        command("say But you can't carry any more coins!");
        return;
    }

    tell_room(environment(this_object()),  QCTNAME(this_object()) + " gives " 
		+ QSHORT(coins) + " to " + QCTNAME(player) + ".\n", ({ player }));
    player->catch_tell(this_object()->query_The_name(player) + " gives " + coins->short() + " to you.\n");


    if (coins->move(player)) {
        command("say I seem to have misplaced the coins...");
        return;
    }

    if (carry < due) {
        command("say Return again for the rest when you can carry em.");
    }

    AUCTION_DATA_STORE->add_owed(name, -carry);

    write_file(CASH_LOG,
            sprintf("%s %-14s got %5d platinum\n",
            ctime(time()),
            player->query_real_name(),
            carry));

    if (has_pending_action(player))
    {
        command("say Don't leave yet, I have more for you.");
        do_action(player);
    }
}

/*
 * Function name: tell_player_occupied
 * Description  : Greeting message when the dwarf is busy.
 */
public void
tell_player_occupied(object player)
{
    string welcome = "";

    if (player->query_prop(AUCTIONEER_NO_GREET))
    {
        player->add_prop(AUCTIONEER_NO_GREET,
            player->query_prop(AUCTIONEER_NO_GREET)-1);
    }
    else
    {
        welcome = "Welcome, "+QNAME(player)+"! ";
    }

    if (has_pending_action(player) && player->query_real_name() != Seller)
    {
        welcome += " Please wait a moment, when I am done" +
	    " I will take care of your business.";
    }

    if (strlen(welcome))
	command("say " + welcome);
}

/*
 * Function name: tell_player_occupied
 * Description  : Greeting message when the dwarf is STILL busy.
 */
public void
tell_player_still_occupied(object player)
{
    if (!has_pending_action(player))
        return;

    if (player->query_real_name() == Seller)
        return;

    command("say I have not forgotten you, "+ QNAME(player) +
	"! I will get back to you shortly.");
}

/*
 * Function name: allowed_paddle
 * Description  : Returns 1 if the player can have a paddle
 */
public int
allowed_paddle(object player)
{
    //Todo: Change 1 to check the quest bit
    return 1;
}

/*
 * Function name: has_pending_action
 * Description  : Returns true if the dwarf must give something
 *                to the player.
 */
public int
has_pending_action(object player)
{
    string name = player->query_real_name();

    if (AUCTION_DATA_STORE->get_owed(name) > 0 && can_carry(player) > 0)
        return 1;

    int *won = AUCTION_HOUSE->get_won_auction(name);

    // Remove the missing items so that we don't keep processing them over and over again
    int *missing_items = player->query_prop(AUCTION_MISSING_ITEMS);
    if (sizeof(missing_items))
	won = won - missing_items;

    if (won && sizeof(won))
        return 1;

    if (allowed_paddle(player) && !present("_auction_paddle_",player))
        return 1;

    return 0;
}


/*
 * Function name: prevent_enter
 * Description  : Keeps the auctioneer from getting too many items
 */
public int
prevent_enter(object ob)
{
    if (Auction_obj)
    {
        write("The auctioneer already has his hands full.\n");
        return 1;
    }

    return 0;
}

/*
 * Function name: react_stand
 * Description  : React to a player standing in front of the podium
 */
public void
react_stand(object player)
{
    if (!get_available())
        return;

    //Todo: Check quest bit, and do nothing if set

    if (!player->query_prop(AUCTIONEER_DID_STAND))
    {
        player->add_prop(AUCTIONEER_DID_STAND,1);
        command("say Ye look good up in front of that podium! Would "+
	    "ye like to help out, and give me a moment's rest?");
    }
}

public void
ask_help()
{
    if (TP->query_prop(AUCTIONEER_DID_STAND))
        return;

    command("say Working all hours is tough! I wish someone would stand "+
	"behind the podium for me once in a while.");
}

/*
 * Function name: show_hook
 * Description  : Tell people what the item may be worth
 */
public void
show_hook(object obj)
{
    if (!objectp(obj))
        return;

    if (!get_available())
        return;

    int price = AUCTION_HOUSE->get_average_selling_price(singular_short(obj));
    if (price)
    {
        command("say I bet ye could earn " + price + " platinum "+
	    "for that.");
    }
    else
    {
        command("say I have not sold that before.");
    }
}

/*
 * Function name: react_intro
 * Description  : the npc introduces himself
 * Arguments    : tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where did they go?");
        return;
    }

    command("introduce me");
} /* react_intro */

/*
 * Function name: add_introduced
 * Description  : Called automatically from the mudlib whenever a person
 *                introduces himself to this NPC.
 * Arguments    : string name - the name of the person being introduced.
 */
void
add_introduced(string name)
{
    set_alarm(itof(intro_delay), 0.0, &react_intro(name));
}

