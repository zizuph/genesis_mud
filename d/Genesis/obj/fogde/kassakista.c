/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

inherit "/std/weapon.c";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#define FOGDEN "_fogden_"
#define MAX_PC 30
#define MAX_GC 300
#define MAX_SC 1000
#define MAX_CC 10000
#define MIN_CS 100

#define NF(message)	notify_fail(message)
#define TP		this_player()
#define ETP		environment(this_player())
#define TI		this_interactive()
#define TO		this_object()
#define ETO		environment(this_object())
#define BS(message)	break_string(message, 75)

#define GET_ACC(p)		"/d/Genesis/obj/accounts"->query_account(p)
#define SET_ACC(p, data)	"/d/Genesis/obj/accounts"->set_account(p, data)

static void open_it();
public int show_allow(object pl);
public int find_money(object ob);

void
create_weapon()
{
    set_name(({ "box", "treasure box" }));
    set_adj(({"black", "reinforced"}));
    set_long(BS("The box is bound with iron bands bolted into the hard wood. Yes wood, but wood of a kind you've never seen before. It's black as night and harder than any wood you've ever seen before. It's polished to a rich gloss, almost reflecting your image where it isn't covered with iron bands. It opens from the top and judging from the look of the hinges it will take more than a common crowbar to pry it open. There's no visible lock. The iron bands are polished bright and there's a incription engraved in the bands all around the box reading \"Property of the poor of Genesis. Hands off or else!\"\n\n") + BS("There's also a small, coin-wide slot in the top of the box marked with the legend \"Insert money here\".\n"));

    set_hit(15);
    set_pen(15);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_cmd_item("box", ({ "shake", "rattle" }), ({ "@@shake_it@@", "@@shake_it@@" }));
    add_item("slot", BS("A coin slot, suitable for putting coins in. Why don't you try it?\n"));
}

void
init()
{
    ::init();
    add_action("open_box", "open");
    add_action("insert_money", "insert");
    add_action("insert_money", "put");
}

int
shake_it()
{
    write(BS("You hear a loud rattling, clanking sound as well as a soft complainging whine of gnomish quality.\n"));
    say(QCTNAME(TP) + " shakes a treasure box\n. It produces a loud rattling, clanking sound.\n");
    return 1;
}

int
insert_money(string str)
{
    mixed money, box;
    int amount, *acc;
    string type;

    if (!strlen(str))
    {
	NF("Insert what where?\n");
	return 0;
    }

    if (!parse_command(str, all_inventory(ETP) + all_inventory(TP), "%i 'in' %i", money, box))
	return 0;

    amount = money[0];
    money = VISIBLE_ACCESS(money, "find_money", TO);

    if (!sizeof(money) || !amount)
    {
	NF("It's a treasure box dummy! You can only insert money there.\n");
	return 0;
    }

    amount = amount < 0 ? 1 : amount;
    type = money[0]->query_coin_type();
    if (MONEY_MOVE(amount, type, environment(money[0]), 0) < 0)
    {
	NF("You don't have that kind of money...\n");
	return 0;
    }

    acc = GET_ACC(FOGDEN);
    if (!sizeof(acc))
	acc = ({ 0, 0, 0, 0, 0});
    acc[4] = time();
    
    switch(type)
    {
    case "platinum":
	acc[3] += amount;
	break;

    case "gold":
	acc[2] += amount;
	break;

    case "silver":
	acc[1] += amount;
	break;

    case "copper":
	acc[0] += amount;
	break;
	
    default:
	NF("Wierd coin type... argh... (" + type + ")\n");
	return 0;
	break;
    }
    SET_ACC(FOGDEN, acc);
    
    if (amount > 1)
	write("With a happy clanking sound, the coins disappear into the box.\n");
    else
	write("With a happy clanking sound, the coin disappears into the box.\n");
    say(QCTNAME(TP) + " inserts some money into the treasure box.\n");
    return 1;
}

public int
find_money(object ob)
{
    if (file_name(ob)[0..9] == "/std/coins")
	return 1;

    return 0;
}

int
open_box(string str)
{
    mixed box, stuff;
    int i;

    if (!strlen(str))
    {
	NF("Open what how?\n");
	return 0;
    }

    if (id(str))
    {
	NF("Open the box with what?\n");
	return 0;
    }

    if (sscanf(str, "%s with hands", str))
    {
	if (!id(str))
	    return 0;

	if (TP->query_skill(SS_OPEN_LOCK) > 70 &&
	    TP->query_stat(SS_STR) > 50 &&
	    TP->query_stat(SS_DEX) > 80 &&
	    TP->query_average_stat() > 50)
	    open_it();
	else
	    write(BS("You hear a faint gnomish laughter from the insides of the box.\n"));
	return 1;
    }

    if (!parse_command(str, all_inventory(ETP) + all_inventory(TP), "%i 'with' %i", box, stuff))
	return 0;

    if (box[0] == 0 || box[1] != TO)
	return 0;

    stuff = VISIBLE_ACCESS(stuff, "show_allow", TO);

    if (!sizeof(stuff))
    {
	NF("You can't open it with that!\n");
	return 0;
    }

    for (i = 0 ; i < sizeof(stuff) ; i++)
    {
	if (TP->query_skill(SS_OPEN_LOCK) > 10 &&
	    TP->query_stat(SS_STR) > 30 &&
	    TP->query_stat(SS_DEX) > 30 &&
	    TP->query_average_stat() > 40)
	{
	    open_it();
	    return 1;
	}
    }
    write(BS("You hear a faint gnomish laughter from the insides of the box.\n"));
    return 1;
}

static void
open_it()
{
    object *coin;
    int *amount, *acc, i;
    
    write(BS("The box glows with an eerie blue light and a whining, almost inaudble gnomish scream can be heard. As you pry the box open it suddenly turns white-hot in your hands and you have to throw it away in order not to get burned! As it leaves your hands it collapses inwards on itself, leaving a scattering of coins behind.\n"));
    say(QCTNAME(TP) + " suddenly drops a smoldering treasure box.\nThe box then implodes, leaving a scattering of money behind!\n");

    setuid();
    seteuid(getuid());

    amount = ({ 0, 0, 0, 0 });
    acc = GET_ACC(FOGDEN);
    if (!sizeof(acc))
	acc = ({ 0, 0, 0, 0, 0});

    amount[3] = acc[3] > MAX_PC ? MAX_PC : 
    	acc[3] < MAX_PC / MIN_CS ? MAX_PC / MIN_CS : acc[3];
    amount[2] = acc[2] > MAX_GC ? MAX_GC : 
    	acc[2] < MAX_GC / MIN_CS ? MAX_GC / MIN_CS : acc[2];
    amount[1] = acc[1] > MAX_SC ? MAX_SC : 
    	acc[1] < MAX_SC / MIN_CS ? MAX_SC / MIN_CS : acc[1];
    amount[0] = acc[0] > MAX_CC ? MAX_CC : 
    	acc[0] < MAX_CC / MIN_CS ? MAX_CC / MIN_CS : acc[0];

    acc[4] = time();
    for (i = 0 ; i < 4 ; i++)
    {
	acc[i] -= amount[i];
	acc[i] = acc[i] < 0 ? 0 : acc[i];
    }

    coin = allocate(4);

    if (amount[3])
	coin[3] = MONEY_MAKE_PC(amount[3]);
    if (amount[2])
	coin[2] = MONEY_MAKE_GC(amount[2]);
    if (amount[1])
	coin[1] = MONEY_MAKE_SC(amount[1]);
    if (amount[0])
	coin[0] = MONEY_MAKE_CC(amount[0]);

    SET_ACC(FOGDEN, acc);

    for (i = 0 ; i < 4 ; i++)
	if(coin[i])
	    coin[i]->move(ETP, 0);

    remove_object();
}

public int
show_allow(object pl)
{
    if ((pl->query_wt() == W_SWORD || pl->query_wt() == W_KNIFE) &&
	pl->query_dt() & W_IMPALE &&
	pl->query_hit() > 20 && 
	pl->query_pen() > 20)
        return 1;
    return 0;
}
