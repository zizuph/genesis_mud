/*
 *  The Red Eye Inn in Minas Morgul
 *  
 *  copied from the Sleeping Stallion in Edoras
 *
 *  created by unknown (Elessar?)
 *  Olorin, July 93
 *
 *  Modification log:
 *  Inherited /d/Gondor/common/lib/inn.c. Olorin, December 1995
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/d/Gondor/common/lib/inn.c";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"

#define STAND_DIR	MORGUL_DIR + "obj/"
#define MY_PRICES	({  3, 10, 16, 46, 110, 18, 30, 58, 225, 1728, 550, 288})

object ramarth,
       soldier,
       mercenary,
       drunk;

public void    reset_room();

public void
create_morgul_room()
{
    set_road(9);
    set_short_desc("in the Red Eye Inn in Minas Morgul");
    set_extraline(
        "Here you can eat and drink to your heart's delight. Some of the "
      + "tables here are occupied by mercenaries or soldiers in the Morgul "
      + "Army. By the north wall is a counter. In front of it, several men "
      + "are standing, drinking beer or wine. On the wooden floor lies a "
      + "rug, which has seen better times. It is worn out, covered with "
      + "dirt, pipe ashes and holes. A few lamps are hanging from the "
      + "ceiling, creating a gloomy atmosphere. To the left of the counter "
      + "there are stairs leading upstairs to a room where one can stay for "
      + "the night. On the wall behind the counter is a pricelist and menu.");
    add_item(({"rug","holes","ashes","dirt"}),BSN(
        "The rug was once beautiful and red, but now it is grey, full of "
      + "holes, and covered with pipe ashes and dirt."));
    add_item(({"floor","ground"}), BSN(
        "The floor is made of old, run down wooden planks. On the planks "
      + "in front of the counter lies an old dirty rug."));
    add_item(({"table","tables","chair","chairs"}), 
        "Most of the tables are free, but some are occupied by the "
      + "customers of this inn.\n");
    add_item("counter", BSN(
        "Above the wooden counter are a lamp and a shelf. On the shelf are "
      + "several brands of liquor. On the wall behind the counter there "
      + "hangs a pricelist and menu."));
    add_item(({"pricelist","list","prices","menu"}), price_long());
    add_cmd_item(({"pricelist","list","prices","menu"}), "read", price_long());

    add_exit(MORGUL_DIR + "city/rooms/hotel", "up", check_exit, 2);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out(({ 2000, 700, 50, 4}));
    set_money_give_reduce(({1,1,1,1})); 

    clone_object(MORGUL_DIR + "city/doors/inndoorin")->move(TO);

    reset_room();
}

/*
 * Function name: price_long
 * Description:   print the menu
 *                dummy example
 * Usage:         in create_room()
 *                add_item(({"menu", "prices", }), price_long());
 *                add_cmd_item(({"menu", "prices", }), "read", price_long());
 */
string
price_long()
{
   return (
      "The pricelist reads:\n\n"
    + "DRINKS:\n"
    + "   Water                 ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Morgul Vale Ale       ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Red Eye Beer          ...  " + money_text(MY_PRICES[2]) + "\n"
    + "   Wine from Khand       ...  " + money_text(MY_PRICES[3]) + "\n"
    + "   Whiskey from Mirkwood ...  " + money_text(MY_PRICES[4]) + "\n\n"
    + "HOT MEALS:\n"
    + "   Porridge              ...  " + money_text(MY_PRICES[5]) + "\n"
    + "   Blackroot Stew        ...  " + money_text(MY_PRICES[6]) + "\n"
    + "   Poached Spider        ...  " + money_text(MY_PRICES[7]) + "\n"
    + "   Dog Chow              ...  " + money_text(MY_PRICES[8]) + "\n"
    + "   Bowl of Elf Toes      ...  " + money_text(MY_PRICES[9]) + "\n"
    + "   Fried Elfmeat         ...  " + money_text(MY_PRICES[10]) + "\n\n"
    + "ROOMS:\n"
    + "   Key for a room        ...  " + money_text(MY_PRICES[11]) + "\n\n"
    + "\tYou can buy up to 6 of one item at the same time.\n\n");
}

public int
query_allow_escape(object invader, object guard)
{
    if (guard->id("_morgul_monster"))
    {
        invader->catch_msg("The " + guard->query_nonmet_name() + " stops you!\n");
        return 0;
    }
    return 1;
}

public void
add_things()
{
    if (!objectp(soldier))
    {
        soldier = clone_object(MORGUL_DIR + "npc/variag");
        soldier->add_act("@@get_money");
        soldier->add_act("buy wine");
        soldier->add_act("drink wine");
        soldier->add_act("buy ale");
        soldier->add_act("drink ale");
        soldier->add_act("buy beer");
        soldier->add_act("drink beer");
        soldier->add_act("burp");
        soldier->add_act("kick human");
        soldier->add_act("spit human");
        soldier->add_chat("The wine from Khand is the best wine there is!");
        soldier->add_chat("Rhun sucks! Nurnan rules!");
        soldier->add_chat("I hate those haradrim even more than these stinking orcs!");
        soldier->arm_me();
        soldier->move_living("down", TO);
    }
    if (!objectp(mercenary))
    {
        mercenary = clone_object(MORGUL_DIR + "npc/mercenary");
        mercenary->add_act("@@get_money");
        mercenary->add_act("buy wine");
        mercenary->add_act("drink wine");
        mercenary->add_act("buy ale");
        mercenary->add_act("drink ale");
        mercenary->add_act("buy beer");
        mercenary->add_act("drink beer");
        mercenary->add_act("burp");
        mercenary->add_act("kick human");
        mercenary->add_act("spit human");
        mercenary->add_chat("Too bad they don't have any better wine here!");
        mercenary->add_chat("They should at least have a decent inn in this forsaken town!");
        mercenary->add_chat("This beer sucks! It taste like the water in the Morgulduin!");
        soldier->arm_me();
        mercenary->move_living("down", TO);
    }
    if (!objectp(drunk))
        drunk = clone_npc(drunk, MORGUL_DIR + "npc/drunk");

    if (!objectp(ramarth))
        ramarth = clone_npc(ramarth, MORGUL_DIR + "npc/ramarth");
}

void
reset_room()
{
    set_alarm(0.0, 0.0, add_things);
}

void
init()
{
    ::init();

    init_inn();
}

int
check_enemy(object enemy)
{
    int     feeling;

    if (enemy->query_prop("no_service_in_MM_inn"))
        return 1;
    if ((feeling = ramarth->query_feeling()) == -1)
        return 0;
    else if (ramarth->check_attack(enemy))
        return 1;
    return 0;
}

public int
no_keeper()
{
    NF("There is no innkeeper here, so you can't do that!\n");
    return 1;
}

public int
check_keeper()
{
    if (!present("innkeeper"))
    {
        no_keeper();
        return 0;
    }
    else if (objectp(ramarth->query_attack()))
    {
        NFN("The innkeeper is fighting for his life!");
	return 0;
    }
    else
        return 1;
}

public void
hook_not_got_coin_type(string pay_type, object tp)
{
    ramarth->command("say You ain't got no "+pay_type+" coins, sucker.");
}

public void
hook_not_enough_coin_type(string pay_type, string ware, object tp)
{
    ramarth->command("say You ain't got no "+pay_type
      + " coins to pay for the "+ware+", stupid ape.");
}

public void
hook_not_enough_money(object tp, string ware)
{
    ramarth->command("say You ain't got no money to to pay for "
      + "the "+ware+", you snivelling swine.");
}

/*
 * Function name: do_buy
 * Description:   parse the command
 * Arguments:     str - argument to command verb
 * Returns:       0/1 - failure/success
 */
public int
do_buy(string str)
{
    object  tp = TP;

    if (!strlen(str))
        return 0;

    tp->reveal_me(1);

    if (!check_keeper())
        return 0;

    if (!CAN_SEE(ramarth, tp))
    {
        NFN("The innkeeper looks rather confused as if he is hearing "
          + "voices out of nowhere.");
	return 0;
    }

    if (objectp(tp->query_attack()))
    {
        NFN("You cannot buy anything while you are fighting!");
	return 0;
    }

    if (check_enemy(tp))
    {
        ramarth->command("spit "+tp->query_real_name());
        ramarth->command("say Begone, foul "+tp->query_race_name()+"!");
        return 1;
    }

    return ::do_buy(str);
}

/*
 * Function name: buy_it
 * Description:   identify the item the player tries to buy
 *                dummy example
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    object  tp = TP;

    switch (item_name)
    {
    case "water":
    case "waters":
        if (can_afford(MY_PRICES[0], number, "water", pay_type, get_type))
        {
            buy_item(RANGER_DIR + "obj/water", number);
        }
        break;

    case "morgul":
    case "ale":
    case "ales":
    case "morgul ale":
    case "morgul ales":
        if (can_afford(MY_PRICES[1], number, "ale", pay_type, get_type))
        {
            buy_item(STAND_DIR + "ale", number);
        }
        break;

    case "beer":
    case "beers":
    case "red eye beer":
    case "red eye beers":
        if (can_afford(MY_PRICES[2], number, "beer", pay_type, get_type))
        {
            buy_item(STAND_DIR + "beer", number);
        }
        break;

    case "wine":
    case "wines":
    case "wine from khand":
    case "wines from khand":
        if (can_afford(MY_PRICES[3], number, "wine", pay_type, get_type))
        {
            buy_item(STAND_DIR + "wine", number);
        }
        break;

    case "whiskey":
    case "whiskeys":
    case "whiskey from mirkwood":
    case "whiskeys from mirkwood":
        if (can_afford(MY_PRICES[4], number, "whiskey", pay_type, get_type))
        {
            buy_item(STAND_DIR + "whiskey", number);
        }
        break;

    case "porridge":
    case "porridges":
        if (can_afford(MY_PRICES[5], number, "porridge", pay_type, get_type))
        {
            buy_item(STAND_DIR + "porridge", number);
        }
        break;

    case "stew":
    case "stews":
    case "blackroot stew":
    case "blackroot stews":
    case "blackroot":
    case "blackroots":
        if (can_afford(MY_PRICES[6], number, "blackroot stew", pay_type, 
          get_type))
        {
            buy_item(STAND_DIR + "stew", number);
        }
        break;

    case "poached":
    case "spider":
    case "spiders":
    case "poached spider":
    case "poached spiders":
        if (can_afford(MY_PRICES[7], number, "poached spider", pay_type, 
          get_type))
        {
            buy_item(STAND_DIR + "spider", number);
        }
        break;

    case "dog":
    case "dogs":
    case "chow":
    case "chows":
    case "dog chow":
    case "dog chows":
        if (can_afford(MY_PRICES[8], number, "dog chow", pay_type, get_type))
        {
            buy_item(STAND_DIR + "dogchow", number);
        }
        break;
    case "sauteed":
    case "elftoes":
    case "toes":
    case "bowl of elf toes":
    case "bowl of sauteed elf toes":
    case "sauteed elf toes":
    case "bowl of toes":
    case "bowl of elf":
    case "elf toes":
        if (can_afford(MY_PRICES[9],number,"bowl of sauteed elf toes",
          pay_type,get_type))
        {
            buy_item(STAND_DIR + "elf_toes", number);
        }
        break;

    case "fried":
    case "elfmeat":
    case "elfmeats":
    case "fried elfmeat":
    case "fried elfmeats":
        if (can_afford(MY_PRICES[10], number, "fried elfmeat", pay_type, 
          get_type))
        {
            buy_item(STAND_DIR + "friedelf", number);
        }
        break;

    case "room":
    case "key":
    case "keys":
    case "single room":
    case "single rooms":
    case "night":
    case "nights":
        if (ramarth->query_feeling(tp) > -1)
        {
            ramarth->command("peer "+tp->query_real_name());
            ramarth->command("say I don't like you!");
            ramarth->command("say You look like a traitor, and I don't "
              + "want you in my house.");
            return 1;
        }
        if (number > 1)
        {
            ramarth->command("say Only one room at a time!");
            ramarth->command("say And only for one night at a time!");
            return 1;
        }
        if (can_afford(MY_PRICES[11], number, "room", pay_type, get_type))
        {
                buy_item(MORGUL_DIR + "obj/hotel_key", number,
                    "a single room to spend the night in Minas Morgul");
                write("The innkeeper gives you the key to the room. Don't lose it!\n");
        }
        break;

    default:
        NFN("The innkeeper says: Order what's on the menu, fool!");
	return 0;
        break;
    }
    return 1;
}

public int
check_inn_time(string str)
{
    if (present(ramarth,TO))
    {
        write("You ask the innkeeper what time it is.\n");
        say(QCTNAME(TP)+" asks the innkeeper what time it is.\n",TP);
        ramarth->command("say It is about "+qstime()+".");
        return 1;
    }
    return check_time(str);
}
