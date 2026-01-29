/*
 * Bjorn Armstrong, Chert's son

 * Added support for the commerce module in July 2002, by Boron
 * Also added the scalearmour to this buy.
 */


#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <money.h>

#include "../../guild.h"
#include "smith.h"

#include <macros.h>

#define PLAYER_I_SOLD    "_player_i_sold_to_chert"


inherit M_FILE /* The Krynn humanoid monster file */
inherit "/d/Genesis/lib/commerce";

inherit "/std/act/action";


/* Global variables */
int ordered;
int enter_alrm;
static int marker;
static string crest;
public mapping ing_map = ([]);

/* Prototypes */
public int forging_tells(object arm, object from);
public string query_true_name(object ob, int pl);

public string
query_crest()
{
    return crest;
}

public string
query_crest_desc(object ob)
{
    string ret_val;

    if ( wildmatch(query_crest(),"solamnian") )
       ret_val = "solamnian " + query_true_name(ob, 0) +
          " seems to be a splendid armour.";
    else
       ret_val = query_true_name(ob, 0) + " carries " +
          "the crest of a " + query_crest() +
          " it seems to be a splendid armour.";

    return ret_val;
}

public string
query_lcrest()
{
    string ret_val;

    if ( wildmatch(query_crest(),"solamnian") )
      ret_val = "";
    else
      ret_val = " crested with a " + query_crest();

    return ret_val;
}


public int
query_marker()
{
    return marker;
}

public int
set_marker(int mark)
{
    marker = mark;
}

void
preload_commodities(string *commod)
{
    if (!sizeof(commod))
    {
        return;
    }

    this_object()->hook_commerce_amount_update(commod[0], 0);
    set_alarm(0.5, 0.0, &preload_commodities(commod[1..]));
}

/*
 * Function name : hook_commerce_buy_prevent_buy
 * Description   : function is the last validator in the chain of buy
 *                 validators, when it returns false specified commodity
 *                 would be bought for sure, and when it returns 1 it
 *                 would not, this hook must generate it's own messages
 *                 when returning true
 * Arguments     : object  - the master object of commodity player buys
 *                 int     - the quantity of item he tries to buy
 * Returns       : int     - 1 when buy is prevented or 0 otherwise
 */
public int
hook_commerce_buy_prevent_buy(object commod, int amount)
{
    int value;

    if (!MEMBER(TP))
    {
        value = TP->query_prop(PLAYER_I_SOLD);
        if (value > commod->query_commodity_value())
        {
          command("say With the effort you put into this, there is nothing for you!");

          return 1;
        }
        else
        {
            TP->add_prop(PLAYER_I_SOLD, value - commod->query_commodity_value());
        }
    }

    return 0;
}

/*
 * Function name : hook_commerce_sell_prevent_sell
 * Description   : function is the last validator in the chain of sell
 *                 validators, when it returns false specified commodity
 *                 would be sold for sure, and when it returns 1 it
 *                 would not, this hook must generate it's own messages
 *                 when returning true (please do not destruct or split
 *                 the passed object, p.s. parsing macros split heaps)
 * Arguments     : object  - the commodity object player sells
 * Returns       : int     - 1 when sell is prevented or 0 otherwise
 */
public int
hook_commerce_sell_prevent_sell(object commod)
{
    int value;
    int prestige;

    if (MEMBER(TP))
    {
       prestige = commod->query_commodity_value() < 500 ? commod->query_commodity_value() : 500;
       prestige = prestige / (TP->query_knight_level() + TP->query_knight_sublevel());

       TP->change_prestige( prestige );
       command("say May Paladine bless you!");
    }
    else
    {
        // Normally it takes a number of ingridients to create a
        // valueable commodity, we only credit for one third of the
        // value
        value = TP->query_prop(PLAYER_I_SOLD);
        value = value + (commod->query_commodity_value() / 3);
        TP->add_prop(PLAYER_I_SOLD, value);
    }

    return 0;
}

public void
remove_object()
{
    remove_commerce();

    ::remove_object();
}

/*
 * Function:     query_pair
 * Description:  Used with cresting.
 *               Returns the correct short description of the item
 *               if pair or pairs is part of it like in a pair of
 *               gloves. An empty string is returned if *pair* is not part
 *               part of the description.
 * Arguments:    Object ob, the object we want to test on
 *               int pl, is this the plural description? 1 it is, 0 it isn't
 * Returns:      "pairs of " or "pair of" dependent on the pl argument
 */
public string
query_pair(object ob, int pl)
{
    string sh_desc = ob->short();

    if (wildmatch("*pair*", sh_desc))
    {
        if (pl)
        {
            return "pairs of ";
        }
        else
        {
            return "pair of ";
        }
    }
    return "";
}

/*
 * Function:     query_true_name
 * Description:  Used with cresting.
 *               We want to get a nice name from the objects short_desc.
 *
 * Arguments:    Object ob, the object we want to test on
 *               int pl, is this the plural description? 1 it is, 0 it isn't
 * Returns:      The name we find to be the best match
 */
public string
query_true_name(object ob, int pl)
{
    int i, sz;
    string *names, sh_desc, *descs, *temp;

    /* Find the names and short desc for the armour (non-plural forms) */
    if (!pl)
    {
        names = ob->query_names();
        sh_desc = ob->short();
    }
    /* Find the plural names and plural short for the armour if
       the pshort hasn't been set. */
    else if (!ob->plural_short())
    {
        names = ob->query_pnames();
        sh_desc = (ob->short() + "s");
    }
    /* Find the plural names and plural short for the armour if
       the pshort has been set. */
    else
    {
        names = ob->query_pnames();
        sh_desc = ob->plural_short();
    }

    if (wildmatch("*pairs*", sh_desc))
    {
        names = ob->query_names();
        sh_desc = ob->short();
    }

    /* Remove any names with spaces in them for the calculation,
       such as "pair of boots" in order to get a nicer
       looking output. */
    for (i = sizeof(names) - 1; i > -1; i--)
    {
        if (wildmatch("* *", names[i]))
        {
            names -= ({ names[i] });
        }
    }
    temp = names;

    /* Remove the name of armour(s) for the calculation, as it's not
       our first choice for a description. We put it back
       in the end in case armour is the only name. */
    if (member_array("armour", names) >= 0)
    {
        names -= ({ "armour" });
    }

    if (member_array("armours", names) >= 0)
    {
        names -= ({ "armours" });
    }

    /* Make an array of each word in the short desc. */
    descs = explode(sh_desc, " ");

    /* If a name is in the short desc, choose this for the
       name to return as in the case of "blue dragonscale armour" */
    for (i = 0, sz = sizeof(names); i < sz; i++)
    {
        if (member_array(names[i], descs) >= 0)
        {
            return names[i];
        }
    }

    /* We don't want the object number to be given if it
       comes down to that. */
    if (temp[0] == OB_NUM(ob))
    {
        if (pl)
        {
            return "armours";
        }
        else
        {
            return "armour";
        }
    }

    return temp[0];
}


public void
create_krynn_monster()
{
    set_name("bjorn");
    set_living_name("bjorn");
    set_race_name("dwarf");
    set_title("Armstrong of Thorbardin, Apprentice Blacksmith");
    set_long("This dwarf is well-muscled. He has a small black beard on " +
      "his chin and cheeks, and deep black eyes can be seen under his " +
      "sweating forehead, they are in deep concentration.\n");
    add_name(({"apprentice", "armstrong","blacksmith","smith"}));
    set_adj("well-muscled");
    add_adj("black-bearded");
    set_gender(G_MALE);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({120,90,200,60,60,120}));
    set_skill(SS_DEFENCE,        80);
    set_skill(SS_PARRY,          80);
    set_skill(SS_WEP_CLUB,       80);
    set_skill(SS_BLIND_COMBAT,   80);

    set_alignment(440);
    set_knight_prestige(-2);

    // Add commerce support
    set_commerce_savefile("/d/Krynn/common/commerce/bjorn_data");
    config_default_trade();

    add_demanded_commodity("iron bar", 2, 250, 1.3);
    set_commodity_amount("iron bar", 40);
    set_commodity_reserve("iron bar", 30);

    add_demanded_commodity("carbon bar", 3, 60, 1.8);
    set_commodity_amount("carbon bar", 10);
    set_commodity_reserve("carbon bar", 8);

    add_demanded_commodity("carbonpiece", 5, 60, 1.5);
    set_commodity_amount("carbonpiece", 10);
    set_commodity_reserve("carbonpiece", 8);

    add_supplied_commodity("s_sword", 13, 5, 1.2);
    set_commodity_amount("s_sword", 1);
    add_supply_requirement("s_sword",
                    ({ "iron bar", 3, "carbon bar" , 1}) );

    add_supplied_commodity("s_mace", 11, 5, 1.1);
    set_commodity_amount("s_mace", 1);
    add_supply_requirement("s_mace",
                    ({ "iron bar", 2, "carbonpiece" , 1}) );

    add_supplied_commodity("full_armour", 13, 5, 1.4);
    set_commodity_amount("full_armour", 2);
    add_supply_requirement("full_armour",
                    ({ "iron bar", 2, "carbon bar" , 1}) );

    add_supplied_commodity("s_shortsword", 17, 5, 1.1);
    set_commodity_amount("s_shortsword", 1);
    add_supply_requirement("s_shortsword",
                    ({ "iron bar", 1, "carbonpiece" , 1}) );



    set_default_answer("He looks at you then points north, and mumbles "+
      "something about his father might know.\n");
    add_ask(" [about] 'wax' / 'repair'", "say M'dad knows about that!",1);
    add_ask(" [about] 'task' / 'quest'", "say Get me some supplies "+
      "and we will reward you handsomely!",1);
    add_ask(" [about] 'steel'","say Solamnian steel is some of " +
      "the finest in the land! I craft weapons and armours, but " +
      "I need iron and carbon!",1);
    add_ask(" [about] 'carbon'","say Solamnian steel is some of " +
      "the finest in the land one of the core ingredients of steel " +
      "is carbon, I'd be happy to pay for it if need be!",1);
    add_ask(" [about] 'iron'","say Iron is a key ingredient in the " +
      "fine Solamnian steel.",1);
    add_ask(" [about] 'stock'", "@@list_my_stock", 1);
    add_ask(" [about] 'weapons'", "say I can make weapons aye, ask " +
      "about my stock if you want to know which", 1);
    add_ask(" [about] 'ingredients'", "say Ingredients for what? my " +
      "two main ingridients are carbon and iron, thats for making " +
      "steel!", 1);
    add_ask(" [about] 'armours'", "say Aye I make armours, you can buy "+
      "them in the shop up there. I'm also experimenting with some rather "+
      "interesting techniques where I can use material which is already magic!", 1);
    add_ask(" [about] 'order'", "say Order? Ask about the stock if you " +
      "wanna know what I might have, and then buy what ya need, not like " +
      "the little rodent who just grabs it...", 1);

    add_ask(" [about] [lance] [sword] [mace] [club] [blade]", "say Just " +
      "buy what you want from the shop...  that'll be more then others " +
      "do 'round here", 1);

    add_ask(" [about] 'rodent'", "say Ya know who I mean, the little... " +
      "Aaarggh - I never should've hired 'im!", 1);
    add_ask(" [about] 'kender'", "say Yeah what 'bout 'im? Don't go " +
      "mess with him, he 'pose to work not play!", 1);
    add_ask(" [about] [quality] 'material'", "say The dwarves in the "+
      "mountains mine some good material, their smith makes it into " +
      "some nice bars too!", 1);
    add_ask(" [about] [magic] [magical] [weapons] [armours] [weapon] [armours]",
      "@@magic_items", 1);
    add_ask(" [about] [magic] [magical] [ingredient] [ingredients] [material] ",
      "say I'm not too sure what magic to experiment with... but those " +
      "dragons are said to be all magic... maybe something from them!?", 1);
    add_ask(" [about] [dragon] [dragons]", "say Aye! By Reorx! They say the " +
      "evil dragons have returned!", 1);
    add_ask(" [about] 'reorx'", "say Well he created the world! How much "+
      "greater can ya be? I'll tell ya, being the only God who can empty "+
      "an ocean of beer now thats a God!", 1);
    add_ask(" [about] 'griffon'", "shout Nooo! Not you too! Its enough the " +
      "rodent is rambling on 'bout griffons - I don't care 'bout 'em!", 1);
    add_ask(" [about] [iron] [silver] [carbon] [supply] [supplies]",
      "@@check_supply", 1);

    // Order specific asks
    add_ask("[about] [how] [to] [do] [i] 'order' / 'ordering'",
            "say Type 'order <armour> from <material> of <quality> " +
            "quality'. You can ask me about weapons, materials and " +
            "qualities of course, too.",1);

    set_act_time(26);
    add_act("emote throws a quick glance at the piles in the corner");
    add_act("emote checks up on his iron supply");
    add_act("emote checks up on his carbon supply");
    add_act("emote checks up on his silver supply");
    add_act("say I am sure the dwarven craft will aid turn the tide " +
      "of evil back...");
    add_act("say The dwarves in the mountains are mining some really " +
      "good material!");
    add_act("say If someone could just fetch some quality material " +
      "for me...");
    add_act("say Steel is a fine metal to work with!");
    add_act("say I really need iron and carbon!");
    add_act("say Aye, my stock grows slowly now... at least until the " +
       "knights come and clean it out, or the little rodent!");


    add_act("emote looks at his work with appraising glances, ensuring " +
      "quality.");
    add_act("emote throws a quick look at the iron in the corner.");
    add_act("emote hammers a piece of metal repeatedly!\n\nCLANG!\n\n" +
      "CLANG!\n\nCLANG!\n\n\n");
    add_act("emote uses the bellows to stoke the fire.");
    add_act("say One day, I wish my craftsmanship would rival that of " +
      "the ancient dwarves!");
    add_act("shout By Reorx! I'm a fine craftsman!");
    add_act("emote wipes the sweat from his brow.");
    add_act("say If I'm slow in reacting t'day, it might be cause of the " +
      "bad weather I'm experiencing...");

    set_cact_time(3);
    add_cact("shout I'll smash your head soft like molten metal!");
    add_cact("shout Someone dares to attack me! Fool!");

    // lets move default items to shop
    preload_commodities(query_supplied_commodity());
}

void
write_debug(string str)
{
   object wizard = find_player("boron");

   if (!objectp(wizard))
     return;

   if ( environment(wizard) == environment(TO) )
      wizard->catch_tell(str);

}

/*
 * This function will return a percentage of what is in
 * stock of the pass commodity.
 */
public int
query_stock(string commod)
{
    int cap;
    int amo;
    int res;

    write_debug("Query stock on " + commod + "\n");

    if (!exist_demanded_commodity(commod))
      return 0;


    cap = query_commodity_capacity(commod);
    amo = query_commodity_amount(commod);
    res = amo * 100;

    write_debug("cap " + cap + "\tamo " + amo + " -- ");

    write_debug("res = amo * 100: " + amo * 100 + "  -- ");

    if ( res <= 0 )
       return 0;

    write_debug("res / cap: Percentage: " + res / cap + "\n");

    return (res / cap);
}


/*
 * We hook up here so we can move the object to the stock room, when
 * Chert is done making them.
 *
 * Items not going to the stock room includes objects which are not
 * allowed to be sold in a shop, ie. magic items like the scalemail
 *
 * -Boron, July 2002
 */
public void
hook_commerce_amount_update(string commod, int amount)
{
    //object *wizard = map(({ "boron"  }), find_player);
    object *oblist;
    object *ob;
    string  result;

    /*wizard->catch_tell("\n\nChert the Blacksmith reports:\nI am" +
        " producing " + amount + " units of " + commod + "\n");*/

    if (!exist_supplied_commodity(commod) )
    {
        return 0;
    }

    // Lets give the players a nice experience too
    if (E(TO) && amount)
    {
        ob = all_inventory(E(TO));
        ob = FILTER_PLAYERS(ob);
        if (ob && sizeof(ob))
        {
            ob->catch_msg("The kender arrives with a huge grin, he grabs "+
              "some newly made equipment and carries it north to the shop.\n" +
              "A kender arrives.\n" + QCTNAME(TO) + " throws quick glance at " +
              "the kender and grumbles: everything better be there when I " +
              "check the shop later.\nThe kender gets an offended look on his " +
              "face and hmpfs imitating a dwarf while running into the back room " +
              "with an old piece of iron flying after him.\n");
            command("curse wild");
            command("say That rodent!");
        }
    }

    amount = query_commodity_amount(commod); /* stock amount */
    add_commodity_amount(commod, -amount);   /* remove stock */

    /* clone_commodity would return array of cloned object   */
    /* with size 'amount' or a heap array with size '1'      */

    oblist = clone_commodity(MASTER_OB(find_commodity(commod)), amount);
    amount = sizeof(oblist);
    result = val2str(map(oblist, &->move(SHOP_STORE_ROOM, 1)));

    /*wizard->catch_tell("Tried to move " + amount + " such an " +
      "item(s) to the store with these results: "+ result +
      " check: 'sman /std/object move' for error result.\n");*/


}

string
check_supply()
{
    command("say The piles there");
    command("emote points at his piles in the corner.\nYou notice a " +
      "pile of silver, carbon and iron in the corner of the forge.");
    return "say That's all I have...";
}

/*
 * This function should give a response to magic,
 * Return the string as a command.
 * VBFC'ed from an add_ask
 */
string
magic_items()
{
    command("grumble");
    command("say I don't like magic more than any Knight...");
    command("shout I saw that! Get back to work in there, stop " +
       "playing with the water!");
    command("curse wild");
    command("say What did you ask again?");
    command("emote continues: Ahh yes magic... now there is some " +
       "trickery!  ...you know, now knights even have to fight " +
       "magical dragons!");
    return "say What if there was a way to combine the powers " +
       "of Reorx, use m' talents as a smith, and have evil turn " +
       "on it self?";
}


/*
 * This function should list what the dwarf have in stock
 * Return the string as a command.
 * VBFC'ed from an add_ask
 */
string
list_my_stock()
{
   return "say I'm trying to work out how to make some really nice " +
     "armours, anything else is sold in the shop!\n";
}

public int
alter_armour(object person, object arm, int crestChoice, int remake = 0)
{
    int mon;
    string *adjs;
    string desc, ldesc, sdesc, pdesc, *new_prop;

    adjs = arm->query_adjs();

    if (marker)
    {
        command("say Please come back later, I'm busy with something "+
          "else at the moment");
        return 1;

    }

    crest = CRESTS[crestChoice];
    arm->move(this_object(), 1);
    mon = ((arm->query_prop(OBJ_I_VOLUME) * 1728) / 2000);

    desc  = arm->short();
    ldesc = arm->query_long();
    sdesc = arm->query_short();
    pdesc = arm->plural_short();

    if (remake)
        arm->set_long( RLONG(arm) );
    else
        arm->set_long( LONG(arm) );


    log_file("crested", ctime(time()) + " " + this_player()->query_name() +
        " " + file_name(arm) +
        " " + CRESTS[crestChoice] + "(" + SHORT(arm) + "/" +
        PSHORT(arm) + ") for " + mon + " copper.\n");

    set_alarm(1.3, 0.0, &person->catch_tell("You request a replica of your " +
            arm->short() + query_lcrest() + ".\n"));

    forging_tells(arm, person);

    arm->add_prop(OBJ_S_CREST, ({ desc, CRESTS[crestChoice] }));
    arm->add_prop(OBJ_S_CREST_INFO, ({ ldesc, sdesc, pdesc, adjs }));
    arm->add_prop(OBJ_M_NO_ALTER, "This armour is a noble solamnian armour " +
       "it can not be altered here!\n");
    arm->remove_adj(adjs);
    arm->add_adj(ADJS);
    arm->add_adj("unworn");
    arm->set_short( SHORT(arm) );
    arm->set_pshort( PSHORT(arm) );
    arm->add_name("_solamnian_crested");
    return 1;
}


public void
init_living()
{
    ordered = 0;

    add_action("order","order");

    ::init_living();
    init_commerce();
}


int
order(string str)
{
    string crest, mess, *arr;
    mixed *armour;
    int crestChoice, mon;


    if (query_marker())
    {
      command("say I'm rather busy at the moment. Please come back later.");
      return 1;
    }

    if (!strlen(str))
    {
        notify_fail("Order copy of what armour?\n");
        return 0;
    }

    str = lower_case(str);

    /* simple hack to allow only knights to swap their armours
     * Added: by Torqual (Boron was notified) 25.04.2003
     */

    if (!MEMBER(this_player()))
    {
    notify_fail("The smith looks at you carefully and says: I think " +
        "you are not allowed to do that. Please ask some " +
        "high-ranking knight about it.\n");
    return 0;
    }

    if (!parse_command(str, all_inventory(this_player()),
      " %i %s ", armour, crest))
    {
        notify_fail("You don't seem to have that item.\n");
        return 0;
    }

    switch(crest)
    {
    case "kingfisher":
      crestChoice = 1;
    break;
    case "crown":
      crestChoice = 2;
    break;
    case "phoenix":
      crestChoice = 3;
    break;
    case "dolphin":
      crestChoice = 4;
    break;
    case "sword":
      crestChoice = 5;
    break;
    case "bison":
    case "horn":
    case "bison's horn":
    case "bisons horn":
      crestChoice = 6;
    break;
    case "rose":
      crestChoice = 7;
    break;
    case "dragon":
      crestChoice = 8;
    break;
    case "triangle":
      crestChoice = 9;
    break;
    case "black rose":
    case "black":
      crestChoice = 10;
    break;
    case "solamnian":
      crestChoice = 11;
    break;
    default:
      if (!wildmatch("*kingf*", crest) || crest != "")
      {
          notify_fail("Order a copy of what armour with what crest?");
      }
      crestChoice = 0;
    }

    armour = NORMAL_ACCESS(armour, 0, 0);

    if (sizeof(armour) > 1)
    {
        notify_fail("The smith can only work on one armour at a time.\n");
        return 0;
    }

    if (!sizeof(armour))
    {
        notify_fail("Order a copy of what armour?\n");
        return 0;
    }

    if (!IS_ARMOUR_OBJECT(armour[0]))
    {
        notify_fail("Only armours are copied here.\n");
        return 0;
    }

    if (wildmatch(VARM+"*",
      file_name(armour[0])))
    {
        notify_fail("That item looks just fine as it is.\n");
        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_GIVE))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("You can't give the " +
                LANG_THESHORT(armour[0]) + " to the smith.\n");
        }

        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_DROP))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("Oddly enough, you can't seem to do that.\n");
        }

        return 0;
    }

    if (armour[0]->query_lock())
    {
        notify_fail(capitalize(LANG_THESHORT(armour[0])) +
            " cannot be copied.\n");
        return 0;
    }

    if ( (mess = armour[0]->query_prop(OBJ_M_NO_ALTER)) && (!armour[0]->query_prop(OBJ_S_CREST)) )
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail(capitalize(LANG_THESHORT(armour[0])) +
            " cannot be crested.\n");
        }
    }

    arr = armour[0]->query_prop(OBJ_S_CREST);
    if (sizeof(arr) > 0)
    {
        if (arr[1] == CRESTS[crestChoice])
        {
            notify_fail(capitalize(LANG_THESHORT(armour[0])) +
                " is just that already.\n");
            return 0;
        }
        else if (query_marker())
        {
            command("emote looks rather busy. It " +
                "appears that you must wait your turn.\n");
            return 1;
        }
        else
        {
            if (!MONEY_ADD(this_player(),
              -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000)))
            {
                notify_fail("You can't afford to have " +
                    LANG_THESHORT(armour[0]) + " copied.\n");
                return 0;
            }
            mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000);
            write("You pay " + mon + " copper to " +
                query_the_name(this_player()) + ".\n");
            alter_armour(this_player(), armour[0], crestChoice, 1);
            return 1;
        }
    }
    if (query_marker())
    {
        command("emote looks rather busy. It " +
            "appears that you must wait your turn.\n");
        return 1;
    }

    mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000);
    if (!MONEY_ADD(this_player(),
      -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000)))
    {
        notify_fail("You can't afford to have " +
            LANG_THESHORT(armour[0]) + " copied.\n");
        return 0;
    }

    write("You pay " + mon + " copper to " +
        query_the_name(this_player()) + ".\n");

    alter_armour(this_player(), armour[0], crestChoice);

    return 1;

}

public string
stat_living()
{
    return ::stat_living() + stat_commerce();
}

public void
arm_me()
{
    clone_object(VWEP + "smith_hammer")->move(TO);
    clone_object(VARM + "s_shield")->move(TO);
    command("wield all");
    command("wear all");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}


public int
forging_tells(object arm, object from)
{
    string name = arm->short();

    if (marker)
    {
        notify_fail("emote looks rather " +
            "busy. It appears that you must wait your turn.\n");
        return 0;
    }

    set_marker(1);
    set_alarm(3.0, 0.0, &command("emote inspects the " + name +
        " carefully."));
    set_alarm(9.0, 0.0, &command("smile intere"));
    set_alarm(15.0, 0.0, &command("emote picks some heavy tools, and starts " +
        "to work on the " + name + " replica."));
    set_alarm(20.0, 0.0, &command("emote tries something on the " + name + "."));
    set_alarm(22.0, 0.0, &command("emote swears loudly as he hits his thumb "+
        "with a hammer."));
    set_alarm(31.0, 0.0, &command("emote proudly shows the replica around:"));
    set_alarm(31.5, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(33.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(from)));
    set_alarm(33.1, 0.0, &command("put " + OB_NAME(arm)));
    set_alarm(33.2, 0.0, &command("say I'm sorry to say, but I ruined the "
       + "original in the process."));
    set_alarm(33.1, 0.0, &command("shrug help"));
    set_alarm(33.2, 0.0, &set_marker(0));
    return 1;
}
