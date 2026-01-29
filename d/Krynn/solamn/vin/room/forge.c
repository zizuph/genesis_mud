/* The Redhammer Smithy */

#include "../knight/guild.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;
inherit "/lib/trade";

#define F_RANGE_RANDOM(orig, max, min, value) \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))


/* prototypes are here */
int calc_sharpen_value(object obj);
int calc_wax_value(object obj);
int calc_mend_value(object obj);
int distort(int price);

object gSmith;

string
kender()
{
    if (!gSmith || !P(gSmith, TO))
    return "";

    gSmith->update_commerce();

    return "As "+QTNAME(gSmith)+" walks into the back room, a tremendous "+
    "crash erupts from it accompanied by a shrill laughter. The shrill voice "+
    "cries out: Sorry, I forgot to shout 'Catch!' because I was laughing "+
    "too hard!\n"+
    QCTNAME(gSmith)+" grumbles as he emerges from the back room: Silliest "+
    "thing I ever did, hiring that doorknob of a kender as my assistant, "+
    "Reorx forgive me...\n";
}

string
tell_message1()
{
    if (!gSmith || !P(gSmith, TO))
    return "";

    gSmith->update_commerce();

    return "A shrill cry rings from the back room, along with a massive "+
           "boom of crashing metal. The shrill voice cries: Don't worry, " +
           "I'm okay! Just a small accident. It was rather fun to see... " +
           "oh! Look at that!...\n"+
           QCTNAME(gSmith)+" shakes his head, grumbling into his beard.\n";
}

string
tell_message2()
{
    gSmith->update_commerce();

    return "A high-pitched voice screams from the back room: Hey Chert, "+
           "did I ever tell you about the time I met a griffon?\n";
}

string
tell_message3()
{
    gSmith->update_commerce();

    return "A high-pitched voice screams from the back room: Hey Chert, "+
           "did I ever tell you about the time a wizard took me to his " +
           "magical tower in the clouds?\n";
}

string
tell_message4()
{
    if (!gSmith || !P(gSmith, TO))
        return "";

    gSmith->update_commerce();

    return "A high-pitched voice screams from the back room: Hey Chert, "+
           "did I ever tell you-   The voice is cut off as "+QTNAME(gSmith)+
           " suddenly twirls and hurls his hammer into the backroom, " +
           "shouting: Blasted kender, don't you ever shut up?!\n" +
           "The kender emerges from the back room with a grin and "+
           QTNAME(gSmith) + "'s hammer, saying: I think I did once, " +
           "actually.\n"+
           QCTNAME(gSmith)+" grumbles: Give me my hammer and get back " +
           "to work!\n"+
           "The kender sulks and returns to the back room.\n";
}

string
tell_message5()
{
    if (!gSmith || !P(gSmith, TO))
        return "";

    gSmith->update_commerce();

    return QCTNAME(gSmith)+" throws a dented helm into the backroom, and "+
           "grins as an angry voice screams loudly!\n"+
           QCTNAME(gSmith)+" says with a grin: Oops, did I forget to shout "+
           "'catch!'?\n";
}

public void
reset_vin_room()
{
    if (!gSmith)
    {
        gSmith = clone_object(VNPC + "chert");
        gSmith->move_living("xx", TO);
        gSmith->seq_new("do_thing");
        gSmith->seq_addfirst("do_thing","@@arm_me");

        gSmith->update_commerce();
    }
}

public void
create_vin_room()
{
    set_short("The Redhammer Smithy");
    set_long("The heat in the Redhammer Smithy is almost unbearable. " +
            "It radiates from the forge and the walls, bathing you in " +
            "a parching warmth. There are various items spread around " +
            "the smithy. Among those that catch your attention are the " +
            "bellows, the anvil, and a large basin of water as well as " +
            "a few piles of iron, carbon and silver. The forge devides the " +
            "room into two, this one and one further to the south. A hardened " +
            "steel floorplaque is embedded in the rock below your feet, " +
            "and a sign hangs from one of the walls. A bit of white powder " +
            "is spread on the floor, here and there. An exit to the street " +
            "is east, while a small extension of the smithy rests to the " +
            "north.\n");

    AI("forge","The forge glows a fiery-red colour. Obviously, it " +
       "has been well-stoked, and has had much coke added.\n");
    AI(({"powder","white powder","bit of white powder"}),"The white " +
         "powder is actually coke, a crushed carbonate rock which " +
         "allows the forge to reach the heat it requires to do its " +
         "purpose.\n");
    AI(({"walls","wall"}),"The walls radiate warmth, reflecting it back " +
         "to the forge.\n");
    ACI(({"walls","wall"}),"touch","The walls are warm to the touch.\n");
    AI(({"backroom", "back room"}), "The back room in which the excess "+
         "armours and weapons are kept.\n");
    AI("various items","The most interesting are the bellows, the " +
       "anvil, and the basin of water.\n");
    AI("ceiling","Above your head, the ceiling is made of volcanic rock.\n");
    AI(({"volcanic rock","rock"}),"It is most likely granite that makes " +
         "up the foundations and walls of the room.\n");
    AI("floor","Embedded in the volcanic rock is a floorplaque, with " +
       "etched words on it.\n");
    AI(({"floorplaque","plaque","steel plaque","hardened steel plaque",
         "steel floorplaque","hardened steel floorplaque"}),"A dull " +
         "grey-silver colour is its main property. It has words etched " +
         "into it.\n");
    ACI(({"words","etched words","etchings","plaque","steel plaque",
          "steel floorplaque","floorplaque","hardened steel plaque",
          "hardened steel floorplaque"}),"read","The plaque reads:\n\n"+
          "    From mountains come rock,\n"+
          "    From rock comes the steel,\n"+
          "    From the steel comes weapons,\n"+
          "    From the weapons come power,\n"+
          "    From power comes opportunity.\n"+
          "\n    Wisely grasp opportunies,\n"+
          "    To do the good the mountains dream of.\n\n");
    AI("bellows","The bellows are used to stoke the fire.\n");
    ACI("bellows","use","You stoke the fire, making it glow a little " +
        "brighter.\n");
    AI("anvil","The anvil is a weighty piece of tempered iron, " +
       "used to shape weapons.\n");
    AI(({"water","basin of water","large basin of water"}),"This is " +
         "where glowing-hot materials are cooled. It is half-empty " +
         "at the moment.\n");
    ACI("water","drink","The water from the basin is not potable.\n");
    AI(({"extension","small extension"}),"It seems to open into a " +
         "small store.\n");
    AI(({"list","pricelist","sign"}), "@@sign_long");
    AI(({"iron pile","iron"}), "@@check_iron");
    AI(({"silver pile","silver"}), "@@check_silver");
    AI(({"carbon pile","carbon"}), "@@check_carbon");
    AI(({"piles"}), "@@check_piles");

    AE(VROOM + "forge2","south",0);
    AE("/d/Shire/guild/smiths/rooms/vingaard_forge", "west", 0);
    AE(VROOM + "sol_store","north",0);
    AE(VROOM + "ws5", "east");

    reset_room();

    INSIDE;

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell("@@discriminate");

}

string
check_iron()
{
    string str = "";
    int stock;

    stock = gSmith->query_stock("iron bar");

    switch (stock)
    {
        case 0:
          str = "There are only few pieces of cast iron there, nothing useful for " +
                "a smith.";
          break;
        case 1..15:
          str = "There are almost no iron bars in the little heap in " +
                "the corner of the forge.";
          break;
        case 16..35:
          str = "The little heap in the corner of the forge contains some iron bars.";
          break;
        case 36..60:
          str = "This heap seems fairly impressive, it contains a fair amount of " +
                "iron bars";
          break;
        case 61..99:
          str = "The heap of iron bars seems to leave the smith well supplied for " +
                "time being. ";
        case 100:
          str = str + "You don't think he will be needing any more iron!";
          break;
        default:
          str  =  "There are some iron bars in the little heap in " +
                  "the corner of the forge.";
    }
    return str + "\n";
}

string
check_silver()
{
    string str = "";
    int stock;

    stock = gSmith->query_stock("silver bar");

    switch (stock)
    {
        case 0:
          str = "You can only spot some silver dust, nothing really useful for a " +
                "smith.";
          break;
        case 1..15:
          str = "There are almost no silver bars in the little heap in " +
                "the corner of the forge.";
          break;
        case 16..35:
          str = "The little heap in the corner of the forge contains some silver bars.";
          break;
        case 36..60:
          str = "This heap seems fairly impressive, it contains a fair amount of " +
                "silver bars";
          break;
        case 61..99:
          str = "The heap of silver bars seems to leave the smith well supplied for " +
                "time being. ";
        case 100:
          str = str + "You don't think he will be needing any more silver!";
          break;
        default:
          str  =  "There are some silver bars in the little heap in " +
                  "the corner of the forge.";
    }
    return str + "\n";
}

string
check_carbon()
{
    string str = "";
    string str2 = "";
    int stock;
    int stock2;

    stock = gSmith->query_stock("carbon bar");
    stock2 = gSmith->query_stock("carbonpiece");

    switch ( ((1 + stock + stock2) / 2) )
    {
        case 0:
	  str = "There is only some carbon powder there, nothing useful for " +
                "a smith";

          break;
        case 1..15:
          str = "There are almost no carbon in the little heap over in " +
                "the corner of the forge";
          break;
        case 16..35:
          str = "The little heap in the corner of the forge contains some carbon";
          break;
        case 36..60:
          str = "This heap seems fairly impressive, it contains a fair amount of " +
                "carbon";
          break;
        case 61..101:
          str = "The heap of carbon seems to leave the smith well supplied for " +
                "time being ";
          break;
        default:
          str  =  "There are some carbon in the little heap in " +
                  "the corner of the forge";;
    }

	if (stock == 100)
	{
	   str = str + ".\nYou don't think he will be needing anymore carbon chunks just now";
	   if (stock2 == 100)
	   str = str + ", nor do you think he will be needing anymore carbon pieces.";

    }
    else if (stock2 == 100)
	{
	   str = str + ".\nYou don't think he will be needing anymore carbon pieces just now";
    }
    return str + ".\n";
}

string
check_piles()
{
    return check_iron() + check_silver() + check_carbon();
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
      start_room_tells();
      gSmith->update_commerce();
    }
}

void
init()
{
    ::init();
    add_action("do_not_fix","mend",0);
    add_action("do_fix","sharpen",0);
    add_action("do_fix","wax",0);
    add_action("do_read","read",0);
    add_action("do_cost","cost",0);
}

string
sign_long()
{
    return
    "Weapon improvement:\n"
    + "-------------------\n"
    + "Sharpen dull weapons\n"
    + "Wax corroded weapons\n"
    + "\n"
    + "All prices depend on the price of the weapon.\n"
    + "Do \"cost <weapon>\" to see the costs.\n";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "list" && str != "pricelist" &&
        str != "sign")
    return 0;

    write(sign_long());
    return 1;
}

int
do_cost(string str)
{
    object *weapon, tp;
    int v1, v2, v3;

    if (!(present("chert", TO)))
    {
    write("It is impossible to cost your weapon without " +
          "the blacksmith here.\n");
    return 1;
    }

    tp = this_player();

    NF("The dwarf gruffs: Which weapon?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
        !sizeof(weapon))
    {
        return 0;
    }

    NF("Frowning, the dwarf says: Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
    {
        return 0;
    }

    NF("Smirking, the dwarf states: That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
        return 0;

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);
    v3 = calc_mend_value(weapon[0]);

    write("The dwarf suggests: Sharpening that " + weapon[0]->short() + " "
          + ((v1 == -1) ? "is not necessary.\n"
          : ("would cost about " + distort(v1) + " coppers.\n"))
          + "Waxing it "
          + ((v2 == -1) ? "is not necessary.\n"
          : ("would cost about " + distort(v2) + " coppers.\n"))
          + "Mending it "
          + ((v3 == -1) ? "is not necessary.\n"
          : ("is necessary but cannot be done here.\n"))
       //         : ("would cost about " + distort(v3) + " coppers.\n"))
    );
    return 1;
}

int
do_not_fix(string str)
{
    write("Sorry, this option is currently unavailable.\n");
    return 1;
}

int
do_fix(string str)
{
    object *weapon, tp;
    int int_str, value, *money_arr;
    string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
    verb;

    verb = query_verb();

    if (!(present("chert", TO)))
    {
    write("You are unable to do that when the blacksmith is absent.\n");
    return 1;
    }

    NF(capitalize(verb) + " what?\n");
    if (!str)
    return 0;

    tp = this_player();

    /*   Check if the player defines what she wants to pay with
     *   and what you would like in return.
     */
    if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
    get_type = "";
    /* Hmmm... Maybe she only wishes to pay with a certain type */
    if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
    {
        pay_type = "";
        item_name = str;
    }
    }

    if (pay_type != "")
    {
    if (member_array(pay_type, MONEY_TYPES) < 0)
    {
        tell_room(this_object(), "The smith says: I don't accept " +
                  "those " + pay_type + " coins, " +
                  tp->query_nonmet_name() + ".\n");
        return 1;
    }
    }

    if (get_type != "")
    {
    if (member_array(get_type, MONEY_TYPES) < 0)
    {
        tell_room(this_object(), "The dwarf states: " +
                  capitalize(get_type) + " coins? Never "
                  + "heard of those.\n");
        return 1;
    }
    }

    NF(capitalize(verb) + " what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
        !sizeof(weapon))
    {
        return 0;
    }

    NF("The dwarf shouts: Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
        return 0;

    NF("The smith laughs: That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
        return 0;

    /* Talk about tricky code! ;-) */
    value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

    NF("The smith says: I cannot " + verb + " that any further.\n");
    if (value == -1)
        return 0;

    /* Try to take the money */
    if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            tell_room(this_object(), "The smith says: I think that " +
                      weapon[0]->short() + " is a bit more"
                      + " expensive, " + tp->query_nonmet_name() + ".\n");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            tell_room(this_object(), "The smith says: You do not have " +
                      "any " + pay_type + " coins, "
                      + tp->query_nonmet_name() + ".\n");
            return 1;
        }
        else
        {
            tell_room(this_object(), "The smith says: I think that " +
                      weapon[0]->short() + " is a bit too expensive "
                      + "for you, " + tp->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    /* It is paid for, so let's fix the weapon */
    value = call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give the smith the " + weapon[0]->short() + ".\n");
    say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
        " " + weapon[0]->short() + ".\n");

    tell_room(this_object(),
              "The smith " + verb + ((verb == "wax") ? "es" : "s") + " the "
              + weapon[0]->short() + ".\n"
              + "The smith gives the weapon back.\n");

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
    sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the smith " +coin_pay_text+ ".\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " in return.\n");
    return 1;
}

int
calc_wax_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
        obj->query_corroded()))
    {
        return -1;
    }
    return obj->query_repair_cost_corr();
}

int
calc_sharpen_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
        obj->query_dull()))
    {
        return -1;
    }
    return obj->query_repair_cost_dull();
}

int
calc_mend_value(object obj)
{
    if (!(obj->query_prop(OBJ_I_BROKEN)))
    {
        return -1;
    }
    return obj->query_repair_cost_dull()*2;
}

void
fix_wax(object obj)
{
    obj->set_repair_corr(obj->query_repair_corr() + 1);
}

void
fix_sharpen(object obj)
{
    obj->set_repair_dull(obj->query_repair_dull() + 1);
}

void
fix_mend(object obj)
{
    //obj->remove_prop(OBJ_I_BROKEN);
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    return 105;
}

int
distort(int price)
{
    int trading;

    trading = this_player()->query_skill(SS_TRADING);
    if (trading > 100)
    trading = 100;
    if (trading < 0)
    trading = 0;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}
