// file name:	Porter.c
// creator(s):  Lucius
// purpose:     Porter - Delivers stuff for a fee.
// last update:
//
#pragma strict_types

#include <files.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/paths.h"

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/craftsman";

#define GIFT_BIN  (COM + "obj/gift_bin")
/*
 * This is a list of allowed items for delivery that
 * would otherwise fail the cargo scan tests.
 */
private static string *whitelist = ({
    /* Bazaar lockets. */
    "/d/Avenir/common/bazaar/Obj/worn/locket",
    /* Bazaar signet rings. */
    "/d/Avenir/common/bazaar/Obj/worn/sig_ring",
    /* Bazaar toothpicks. */
    "/d/Avenir/common/bazaar/Obj/misc/toothpick",
    /* Ziggurat paddle. */
    "/d/Avenir/common/city/zigg/obj/paddle",
    /* Ziggurat whip. */
    "/d/Avenir/common/city/zigg/obj/whip",
});
private static int alarm;

public void
create_monster(void)
{
    set_name("porter");
    set_short("sybarite porter");
    set_race_name(one_of_list(({"human", "half-elf"})));

    set_gender(0);
    set_alignment(0);

    set_adj(({
	one_of_list(({ "well-to-do", "affluent", "clean-cut", })),
	one_of_list(({ "paunchy", "portly", "round-bellied"}))
    }));

    string desc =  implode(query_adjs(), " ") +" " +
	query_gender_string() + " "+ query_race_name();

    /* Must come after other settings due to calls. */
    set_long("The "+ desc +" wears a yellow and green sash, marking "+
    	"himself as a proud member of the Porters Guild of Sybarus."+
	" He appears to have made some moderate success in the guild, "+
	"if his waistline is any indication. His aquisitive eyes are "+
	"always roving, looking for new customers needing to have "+
	"packages delivered.\n");

    set_stats(({100,100,100,100,100}));
    set_all_hitloc_unarmed(50);

    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_UNARM_COMBAT,50);

    add_prop(NPC_I_NO_FEAR,     1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_prop(OBJ_M_NO_MAGIC,
	"The Gods of Sybarus protect those who Serve.\n");
    add_prop(OBJ_M_NO_ATTACK,
	"The Gods of Sybarus protect those who Serve.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK,
	"The Gods of Sybarus protect those who Serve.\n");
    /*
     * Craftsman bits.
     */
    prefer_speech(1);
    craftsman_set_max_user_orders(2);
    craftsman_set_max_total_orders(2);
    craftsman_set_sold_item_names(({ "box", "item", }));

    set_act_time(100);
    add_act("say Deliveries here! Let us carry your boxes!");
    add_act("say Gift boxes! Get your gift boxes here!");
    add_act("say Need to pickup a delivery? This is the place!");
    add_act("emote fiddles with his green and yellow sash.");
    add_act("emote absently pats his rotund belly.");
    add_act("emote 's eyes scan the area, searching for customers.");

    set_dont_answer_unseen(1);
    add_ask(({"[about] / [for] 'help'"}),
	"say For a reasonable price I can sell you a lovely gift box "+
	"or deliver one for you. That is all the help I can offer.", 1);
    add_ask(({"[about] / [for] [a] 'task' / 'job' / 'quest'"}),
	"say I sell and deliver gift boxes. Those are the only "+
	"tasks I do.", 1);
    add_ask(({"[about] [the] / [a] / [an] [gift] 'box' / 'boxes' /"+
    	"'package' / 'packages'"}),
	"say As a member of the Porters Guild, I can sell you "+
	"Hegemon approved gift boxes that you can use to transport "+
	"gifts and other delicate items, or even have one of "+
	"our younger members deliver it for you! Just 'order' "+
	"one to do so.", 1);
    add_ask(({"[about] [the] / [a] / [an] 'claim' / 'pickup'"}),
	"say You can recieve a delivery held by the Porters Guild "+
	"from any available porter. Just 'claim' or 'pickup' "+
	"to do so!", 1);
    add_ask(({ "[about] [the] / [a] / [an] 'deliver' / 'delivery' / "+
    	"'deliveries'"}),
	"say I'll deliver any boxes ordered from a porter, "+
	"provided it doesn't run afoul of our restrictions. "+
	"To do so, just 'send' or 'deliver' one! If the recipient is "+
	"unavailable to recieve the delivery, I'll hold it until "+
	"they can claim it or Armageddon arives. Only the recipient "+
	"can claim it once it is sent and there's no refund for lost "+
	"boxes, so be careful what you send.", 1);
    add_ask(({"[about] [the] / [a] / [an] 'restriction' / 'restrictions'"}),
	"say I'm not going to give a comprehensive list, but "+
	"generally speaking, the Hegemon has restricted the "+
	"transport of most weapons, armours and magically "+
	"imbued items.", 1);
    add_ask(({"[about] / [for] [the] / [a] / [an] 'refund' / 'lost' [box]"}),
	"say No refunds, no exceptions!", 1);
    add_ask(({"[about] [the] / [a] / [an] [magically] [magical] [imbued] "+
	"'magic' / 'weapon' / 'weapons' / 'armour' / 'armours' / 'item' "+
	"/ 'items'"}),
	"say Potentially dangerous or seditious items cannot be delivered. "+
	"I will check every package for these items before we accept it "+
	"for delivery.", 1);
    add_ask(({"[about] [the] 'porter' / 'porters' / 'porters guild' / "+
	"'Porters Guild'"}),
	"say We proudly deliver gift boxes all over Sybarus, as well as "+
	"the Outlands -- although less proudly. The Porters Guild is "+
	"elite, and only the most gifted of messengers, highly trained "+
	"from a young age, are entrusted to make our deliveries.", 1);
    add_ask(({ "union", "shadow union", "warrior", "warriors"}), 
        "say We can deliver to them! But don't ask us where their Halls "+
        "are. We keep that sort of thing confidential", 1);
    add_ask(({"market", "bazaar", "marketplace", "merchantile pale", 
	"ziggurat", "holm", "underdark", "utterdark", "port", "city",
	"forbidden city", "baths"}), "say Of course we deliver there!", 1);
    add_ask(({"Outlands", "outland"}), "say We'll deliver there. Though "+
	"the price may be higher if we have to go anywhere too odorous.", 1);
    add_ask(({"infidel", "infidels"}), "say Certainly we would not deliver "+
	"to them! Be careful what you imply.", 1);
    add_ask(({"idrys", "Idrys"}), "say Being all powerful, they seldom "+
	"require deliveries. And we would be loathe to trouble them "+
	"with paltry packages.", 1);
    add_ask(({"hegemon", "Hegemon"}), "say We deliver packages to the "+
	"Hegemon, though of course we leave them with one of the "+
	"dej-mihna for inspection.", 1);
    add_ask(({"dej-minha"}), "say It is always a pleasure to deliver to "+
	"them. Well, most of them. Some are rather fierce. I try to make "+
	"those deliveries personally, when I can.", 1);
}

public void
arm_me(void)
{
//    MONEY_MAKE_GC(random(20))->move();

    clone_object(COM + "obj/mshirt")->move(this_object());
    clone_object(COM + "obj/mpants")->move(this_object());
    clone_object(COM + "obj/mshoes")->move(this_object());

    command("wear all");
}
/*
 * Craftsman portion.
 */
public void
craftsman_configure_order(int id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(id, COM + "obj/gift_box");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(id, 25 + random(21));

    // orderable attributes
    craftsman_add_attribute(id, "size", ({
	"small", "medium", "large",
    }));
    craftsman_add_attribute(id, "type", ({
	"felt", "straw", "bamboo", "kesoit", "banana",
    }));
    craftsman_add_attribute(id, "shape", ({
	"square", "rectangular", "circular", "heart-shaped",
    }));
    craftsman_add_attribute(id, "colour", ({
	"gold", "silver", "platinum", "copper", "bronze",
	"black", "charcoal", "grey", "white", "ivory",
	"green", "emerald", "jade", "olive", "aquamarine", "teal",
	"blue", "azure", "cerulean", "sapphire", "turquoise", "indigo",
	"orange", "apricot", "pink", "scarlet", "red", "burgundy",
	"crimson", "magenta", "maroon", "vermillion", "purple", "amethyst",
	"lavender", "lilac", "plum", "violet", "brown", "chocolate",
    }));
}

public void
craftsman_configure_item(object ob, mapping attrs, int id)
{
    ob->set_size(attrs["size"]);
    ob->set_type(attrs["type"]);
    ob->set_shape(attrs["shape"]);
    ob->set_colour(attrs["colour"]);

    ob->config_box();
}

public int
craftsman_calc_item_cost(object ob, int id)
{
    return ob->query_prop(OBJ_I_VALUE);
}
/*
 * Delivery section.
 */
public void get_delivery_details(int id);

#define INPUT_OBJ "/d/Genesis/obj/input_object"
/* We only re-use a subset of these. */
#define ORDER_STATUS           0
#define ORDER_OWNER            1
#define ORDER_ATTRS            2
#define ORDER_SELECTIONS       3
#define ORDER_FILE             4
#define ORDER_COST             7
#define ORDER_HOLD             8
#define ORDER_TIMEOUT          9
#define ORDER_INPUT           10
#define ORDER_SIZE            11
/*
 * Do any delayed post-delivery acceptance here.
 */
private void
post_deliver(object item)
{
    string adj = one_of_list(({"efficacious", "flustered", "lively", 
	"energetic", "efficient", "busy", "bustling", "teenaged", "gangly",
	"young", "adolescent", "brisk", "peppy", "spry", "zippy", "lanky",
    }));
	
    string clr = one_of_list(({
	"green", "yellow", "black", "red", "violet"
    }));

    alarm = 0;
    tell_room(environment(this_object()),
	capitalize(LANG_ADDART(adj)) +" waif sporting a "+ clr +" beret "+
	"rushes in, receiving some packages from "+
	QTNAME(this_object()) +" before speeding off again.\n");
}
/*
 * Scan gift box inventory for illicit materials.
 */
private int
scan_cargo(object box)
{
    if (!objectp(box))
    {
	tell_me("There was an error scanning your gift box.\n");
	return 1;
    }

    object *bad = ({ }), *deep_inv = deep_inventory(box);

    if (!sizeof(deep_inv))
    {
	tell_me("Porter Services isn't about to deliver an empty box!\n");
	return 1;
    }

    foreach(object item : deep_inv)
    {
	/* No delivering (semi-)alive things. */
	if (living(item))
	{
	    bad += ({ item });
	    continue;
	}

	/* Delivery of magic items is forbidden due  *
	 * to safety and insurance issues            */
	if (item->query_prop_setting(MAGIC_AM_MAGIC) ||
	    item->query_prop_setting(OBJ_I_IS_MAGIC_ARMOUR) ||
	    item->query_prop_setting(OBJ_I_IS_MAGIC_WEAPON))
	{
	    bad += ({ item });
	    continue;
	}
	/*
	 * Item is whitelisted, continue.
	 */
	if (IN_ARRAY(MASTER_OB(item), whitelist))
	    continue;
	/*
	 * No transport of herbs!
	 */
	if (strlen(item->query_herb_name()))
	{
	    bad += ({ item });
	    continue;
	}
	/*
	 * No arms smuggling allowed!
	 */
	if (IS_ARMOUR_OBJECT(item) ||
	    IS_WEAPON_OBJECT(item) ||
	    IS_LAUNCH_OBJECT(item) ||
	    IS_PROJECTILE_OBJECT(item) ||
	    IS_POTION_OBJECT(item))
	{
	    bad += ({ item });
	    continue;
	}
	/*
	 * If item has reached here, it's allowed.
	 */
    }  //  FOREACH

    int result = sizeof(bad);

    if (result)
    {
	tell_me("The following items in your "+ box->short() +
	    " disallowed on orders from the Hegemon.\n");
	tell_me("You'll have to remove them before "+
	    "Porter Services will deliver it.\n");

	foreach(object item : bad)
	    write("      "+ item->short(this_player()) +"\n");
    }

    return result;
}

public void
finish_delivery(int id)
{
    object box = m_orders[id][ORDER_FILE];
    m_orders[id][ORDER_STATUS] = 2;
    /*
     * Thieving tricksters.
     */
    if (!objectp(box) || !present(box, this_player()))
    {
	tell_me("You seem to have misplaced your gift box!\n");
	set_alarm(0.0, 0.0, &craftsman_cancel_order(id));
	return;
    }
    /*
     * Make sure they have the funds.
     */
    int cost = m_orders[id][ORDER_COST];
    if (TOTAL_MONEY(this_player()) < cost)
    {
	craftsman_check_cannot_pay_hook(cost, box, -1);
	return;
    }
    /*
     * Make sure we can accept gifts.
     */
    object bin = GIFT_BIN->get_this_object();

    if (!objectp(bin))
    {
	tell_me("There is a problem with accepting "+
	    "deliveries at present.\n");
	tell_me("Please make a bug report.\n");

	set_alarm(0.0, 0.0, &craftsman_cancel_order(id));
	return;
    }
    /*
     * Make sure it's closed.
     */
    box->add_prop(CONT_I_CLOSED, 1);

    write("You make sure the lid is on tight and hand over "+
	"your "+ box->short() +" for delivery.\n");
    say(QCTNAME(this_player()) +" hands something to "+
	QTNAME(this_object()) +".\n");

    if (scan_cargo(box) || !bin->register_gift(
	    m_orders[id][ORDER_OWNER], m_orders[id][ORDER_SELECTIONS], box))
    {
	write(this_object()->query_The_name(this_player()) +
	    " hands back your "+ box->short() +".\n");
	say(QCTNAME(this_object()) +" hands something to "+
	    QTNAME(this_player()) +".\n");

	set_alarm(0.0, 0.0, &craftsman_cancel_order(id));
	return;
    }

    /* Clean out order. */
    set_alarm(0.0, 0.0, &craftsman_cancel_order(id));

    if (box->move(bin))
	box->move(bin, 1);

    /* Already checked funds availability above. */
    MONEY_ADD(this_player(), -cost);

    tell_me(exclaim(1) +" Everything seems in order.\n");
    tell_me("Your delivery will be scheduled shortly.\n");

    if (alarm)
	return;

    alarm = set_alarm(2.0 + rnd(), 0.0, &post_deliver(box));

    tell_room(environment(this_object()),
	QCTNAME(this_object()) +" places two fingers to "+
	this_object()->query_possessive() +" lips, whistling shrilly.\n");
}

public void
set_delivery_details(string value, int id, string attr)
{
    if (!sizeof(m_orders[id]))
	return;
    /*
     * Tried to sneak away.
     */
    if (environment(this_player()) != environment(this_object()))
    {
	write("You appear to have wandered off.\n");
	set_alarm(0.0, 0.0, &craftsman_cancel_order(id));
	return;
    }

    if (!strlen(value))
    {
	/* Editor will return empty string for no message. */
	if (attr == "MESSAGE") {
	    value = "\n";
	} else {
	    get_delivery_details(id);
	    return;
	}
    }
    /*
     * We want to terminate the delivery.
     */
    if (value == "~q")
    {
	craftsman_abort_hook();
	craftsman_cancel_order(id);
	return;
    }
    /*
     * Validate input.
     */
    switch(attr)
    {
    case "ADDRESS":
	value = lower_case(value);
	if (!this_player()->query_wiz_level() &&
	    (!this_player()->query_remembered(value) &&
	     !this_player()->query_introduced(value)))
	{
	    value = "";
	    tell_me("We cannot deliver to someone you "+
		"cannot properly describe.\n");
	}
	break;

    case "MESSAGE":
	if (strlen(value) > 200)
	{
	    value = "";
	    tell_me("Your message is too long, "+
		"try to be more brief.\n");
	}
	break;
    }
    /*
     * If still a 'value' then we are validated
     * to continue onto the next attribute.
     */
    if (strlen(value))
    {
	m_orders[id][ORDER_SELECTIONS][attr] = value;
	m_orders[id][ORDER_ATTRS] = m_orders[id][ORDER_ATTRS][1..];
    }

    get_delivery_details(id);
}

public void
get_delivery_details(int id)
{
    if (m_orders[id][ORDER_TIMEOUT])
    {
	remove_alarm(m_orders[id][ORDER_TIMEOUT]);
	m_orders[id][ORDER_TIMEOUT] = 0;
    }

    string *attrs = m_orders[id][ORDER_ATTRS];

    if (!sizeof(attrs))
    {
	finish_delivery(id);
	return;
    }

    object input_obj; function input_foo;
    /*
     * Prompt for input.
     */
    switch(attrs[0])
    {
    case "ADDRESS":
	tell_me("To whom would you like the "+
	    m_orders[id][ORDER_FILE]->short() +
	    " delivered?\n");
	write("--> ");

	input_obj = clone_object(INPUT_OBJ);
	input_foo = input_obj->get_input;
	break;

    case "MESSAGE":
	tell_me("Enter a message to accompany the gift.\n");

	input_obj = clone_object(EDITOR_OBJECT);
	input_foo = input_obj->edit;
	break;
    }
    /*
     * Get the input.
     */
    m_orders[id][ORDER_INPUT]   = input_obj;
    m_orders[id][ORDER_TIMEOUT] = set_alarm(120.0, 0.0,
	&craftsman_timeout_selection(id));

    input_foo(&set_delivery_details(, id, attrs[0]));
}
/*
 * The main 'deliver' command.
 */
public int
deliver(string str)
{
    if (!strlen(str))
	return notify_fail("Deliver what?\n");

    object *obs = filter(all_inventory(this_player()), &->avenir_gift_box());

    if (!sizeof(obs = PARSE_COMMAND(str, obs, "[the] %i")))
    {
	tell_me("I will only deliver official Porters Guild "+
	    "gift boxes.\n");
	return notify_fail("");
    }

    if (sizeof(obs) > 1)
    {
	tell_me("I can only schedule one delivery at a time!\n");
	return 1;
    }
    /*
     * Re-use some of the craftsman bits.
     */
    int id; mixed *order = allocate(ORDER_SIZE);

    order[ORDER_OWNER]	= this_player()->query_real_name();
    order[ORDER_ATTRS]	= ({ "ADDRESS", "MESSAGE" });
    order[ORDER_COST]   = 2500 + random(2500) + random(2500);
    order[ORDER_FILE]	= obs[0];
    order[ORDER_HOLD]	= 0;
    order[ORDER_SELECTIONS] = ([ ]);

    sscanf(OB_NUM(this_player()), "%d", id);
    m_orders[id] = order;

    tell_me("You've chosen your "+ obs[0]->short() +".\n");
    tell_me("If you selected the wrong one, or wish to cancel, "+
	"enter \"~q\".\n");

    get_delivery_details(id);
    /*
     * !!! Players can manipulate their inventories while
     * !!! inside input_to, so scan at the end, not the
     * !!! beginning.
     */
    return 1;
}
/*
 * Pickup any outstanding deliveries.
 */
private static string *parr = ({
    "gift", "gifts", "delivery", "deliveries", "box", "boxes",
});
public int
pickup(string str)
{
    if (!strlen(str) || !IN_ARRAY(str, parr))
    {
	notify_fail("Are you trying to pickup a delivery?\n");
	return 0;
    }

    object bin = GIFT_BIN->get_this_object();

    if (!objectp(bin))
    {
	tell_me("There is a problem picking up "+
	    "deliveries at present.\n");
	tell_me("Please leave a bug report.\n");
	return 1;
    }

    int count = bin->receive_gifts(this_player());

    if (!count)
    {
	tell_me("I do not have any deliveries addressed to you.\n");
	return 1;
    }

    write(this_object()->query_The_name(this_player()) +
	" hands you "+ LANG_NUM2WORD(count) +" package" +
	(count > 1 ? "s" : "") +".\n");
    say(QCTNAME(this_object()) +" hands "+ (count > 1 ?
	    "some packages" : "a package") +" to "+
	QTNAME(this_player()) +".\n");

    command("$say Enjoy your gifts!");
    return 1;
}
/*
 * Initialization  code.
 */
public void
init_living(void)
{
    ::init_living();
    craftsman_init();

    add_action(deliver, "deliver");
    add_action(deliver, "send"   );
    add_action( pickup, "claim"  );
    add_action( pickup, "pickup" );
}

public string
race_sound(void)
{
    return "says";
}
