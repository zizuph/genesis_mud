/*
 * /d/Genesis/start/human/wild2/sparkle_forge.c
 *
 * Sparkle forge near Dwarfheim
 * Varian - February 2016
 *
 * Forgework ruthlessly stolen from /d/Gondor/lebennin/thornlin/forge.c
 */
#pragma strict_types

inherit "/lib/trade";
inherit "/std/room";

#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define WAX_COST     5  /* Waxing costs 5% per point */
#define SHARPEN_COST 10 /* Sharpening costs 10% */

static object hurgan;

void
create_room()

{
    set_short("Dwarven Smithy");
    set_long("You find yourself standing within the thick stone walls of " +
        "a local dwarven smithy. A quick glance around the blacksmith's " +
        "workshop reveals a plain, if clean and well organized, place of " +
        "business. A small sign with instructions rests on the east wall, " +
        "while waves of heat ripple across the room, eminating from the " +
        "forge set up against the northern wall. Several barrels are lined " +
        "up near a fire pit filled with coal, while a large bellows has " +
        "been positioned nearby. In the middle of the room, not far from " +
        "the forge, is the heavy iron anvil where the blacksmith does his " +
        "work. The walls and floor have been constructed from solid blocks " +
        "and slabs of a dark grey stone, with only one opening in the south " +
        "wall leading back to the Dark Road outside.\n");
  
    add_item(({"smithy", "room", "here", "workshop"}),
        "You find yourself standing within the thick stone walls of " +
        "a local dwarven smithy. A quick glance around the blacksmith's " +
        "workshop reveals a plain, if clean and well organized, place of " +
        "business. A small sign with instructions rests on the east wall, " +
        "while waves of heat ripple across the room, eminating from the " +
        "forge set up against the northern wall. Several barrels are lined " +
        "up near a fire pit filled with coal, while a large bellows has " +
        "been positioned nearby. In the middle of the room, not far from " +
        "the forge, is the heavy iron anvil where the blacksmith does his " +
        "work. The walls and floor have been constructed from solid blocks " +
        "and slabs of a dark grey stone, with only one opening in the south " +
        "wall leading back to the Dark Road outside.\n");
    add_item(({"wall","walls"}),
        "Like many buildings, this smithy has four disctinct walls. Each of " +
        "the walls has been crafted from massive blocks of a dark grey " +
        "stone. The blocks have been finely formed to fit tightly together, " +
        "ensuring a very strong and solid construction.\n");
    add_item(({"ceiling","up","above"}),
        "Several wooden beams span across the ceiling, holding up a series " +
        "of rafters which support the slate tiles of the roof outside. A " +
        "narrow chimney near the northern end allows the smoke from the " +
        "forge to escape.\n");
    add_item(({"floor","ground","down","slab"}),
        "The floor of the smithy is composed of several wide stone slabs, " +
        "diligently honed to provide a solid flat surface. You notice that " +
        "even along the joints, the slabs have been levelled with each " +
        "other, so as to provide no lip or edge which someone might " +
        "trip over. It appears that the blacksmith keeps his workshop " +
        "tidy, as the ground is mostly clear of ash from the forge.\n");
    add_item(({"ash","ashes","dust"}),
        "You can see a few ashes scattered around the floor of the " +
        "smithy, mostly around the fire pit, but far less than you would " +
        "expect! You have trouble even finding any collection of dust in " +
        "here. The blacksmith is obviously a clean and tidy dwarf.\n");
    add_item(({"joint","joints"}),
        "All of the joints between the stonework in this building are " +
        "very tight, speaking to the quality of craftmanship.\n");
    add_item(({"opening","exit","exits"}),
        "A narrow opening in the southern wall peeks outside towards the " +
        "Dark Road, the long road which connects the cities of Larton " +
        "and Sparkle. The opening itself has a brown leather flap hangning " +
        "down, battered and cracked, helping to keep the heat inside.\n");
    add_item(({"north wall","northern wall"}),
        "The northern wall of the smithy has a waist-high (for a dwarf!) " +
        "stone fire pit, the heart of the forge, set against it. Three " +
        "barrels full of liquid are lined up nearby, while above the fire " +
        "pit, an iron chimney rises up into the rafters, carrying away " +
        "most of the smoke.\n");
    add_item(({"south wall","southern wall"}),
        "The southern wall of the smithy is rather plain, unadorned unless " +
        "you consider the leather covered narrow opening which leads " +
        "back outside.\n");
    add_item(({"east wall","eastern wall"}),
        "The eastern wall of this workshop seems to be something of a " +
        "collecting ground for the blacksmith. Several tools lean up " +
        "against the wall, as well as crates of iron ore, coal and " +
        "charcoal.\n");
    add_item(({"west wall","western wall"}),
        "The western wall is covered in shelves full of various tools. It " +
        "seems like the blacksmith keeps many of his smaller tools stacked " +
        "neatly on these shelves along with some jars of nails.\n");
    add_item(({"dark road","road","darkroad","highway"}),
        "This road runs from the east to the west, just steps outside of " +
        "the smithy. At one time, the road was incredibly busy, connecting " +
        "the two cities of Larton and Sparkle. Yet now, it has been " +
        "dubbed the 'Dark Road' as bandits have ambushed so many " +
        "travellers in the pass through the mountains that few are " +
        "brave enough to use the highway any longer.\n");
    add_item(({"dwarfheim","mountain","mountains","grey mountains"}),
        "A mountain pass just east of the smithy connects the traditional " +
        "dwarven homelands of Dwarfheim in the north, with the Dark Road " +
        "and the city of Sparkle to the south.\n");
    add_item(({"pass","passes","mountain pass","mountain passes"}),
        "You cannot see them from here, but there are two mountain passes " +
        "nearby. The one on the Dark Road to the west supposedly connects " +
        "to the city of Larton, while the one to the east connects to the " +
        "dwarven homeland of Dwarfheim.\n");
    add_item(({"forge","pit","fire pit","fire"}),
        "Dozens of dark grey fieldstones have been stacked and mortared " +
        "to build a wide firepit which sits about three feet high. The " +
        "pit is filled with coal, which burns with waves of intense heat " +
        "that radiates in waves out from the forge. There is a bellows " +
        "positioned nearby to help make the fire even hotter while the " +
        "blacksmith works.\n");
    add_item(({"coal","charcoal","fuel"}),
        "Not only is there some coal currently sitting inside the forge, " +
        "you can see some crates of both coal and charcoal lined up against " +
        "the eastern wall of the smithy.\n");
    add_item(({"bellows","large bellows","air"}),
        "The large bellows has been set up and positioned to blow air " +
        "into the forge, enabling the smith to increase the heat of his " +
        "fire when needed for his work.\n");
    add_item(({"anvil","heavy anvil","iron anvil","heavy iron anvil"}),
        "This is a long slab of solid iron, with a flat face and slightly " +
        "pointed at one end. This appears to be the place where the " +
        "blacksmith hammers the heated metal into the desired shape.\n");
    add_item(({"block","blocks","stone blocks","stone block"}),
        "Large and square, with an almost delicate chiseled and honed " +
        "finish, the blocks which form these walls have obviously been " +
        "cut and laid by an expert.\n");
    add_item(({"slab","slabs","stone slab","stone slabs"}),
        "Several wide slabs of dark grey stone, which have been expertely, " +
        "honed and levelled stretch out across the floor. The slabs " +
        "are slightly worn with heavy use, but appear to be a little " +
        "cleaner than you might expect.\n");
    add_item(({"tool","tools","hardie tools","hardie tool"}),
        "There are several tools lined up on the shelves of the west wall, " +
        "many of them hardie tools which are used for cutting and shaping " +
        "iron.\n");
    add_item(({"crate","crates"}),
        "There are three crates lined up against the east wall. Most " +
        "of them are filled with fuel for the forge, but one crate seems " +
        "to be designated for iron ore.\n");
    add_item(({"hammer","hammers"}),
        "There is a wide variety of hammers and sledges, small and large, " +
        "all of which seem to be well used by the blacksmith.\n");
    add_item(({"barrels","three barrels","barrel"}),
        "There are three barrels full of liquid lined near the forge in " +
        "the northern wall.\n");
    add_item(({"water","water barrels"}),
        "There are two barrels of water here, beside a third barrel which " +
        "seems to be full of oil.\n");
    add_item(({"liquid","liquids"}),
        "You can see various liquids filling the three barrels along the " +
        "north wall.\n");
    add_item(({"fresh water","fresh water barrel","first barrel"}),
        "A quick taste of the water in the first barrel can tell you that " +
        "it is full of fresh water, used by the blacksmith for quenching.\n");
    add_item(({"brine","salt water","salt water barrel","second barrel"}),
        "A quick taste of the water in the second barrel can tell you that " +
        "it is full of salt water, otherwise known as brine, used by the " +
        "blacksmith for quenching.\n");
    add_item(({"oil","olive oil","oil barrel","olive oil barrel",
        "third barrel"}),
        "A quick taste of the oil in this third barrel indicates that it is " +
        "full of olive oil. You can imagine that olive oil is rather " +
        "expensive, but it must be useful to the blacksmith if he uses " +
        "it for quenching.\n");
    add_item(({"tongs","metal tongs"}),
        "There are several sets of metal tongs around the smithy, most " +
        "of which are leaning up against the eastern wall.\n");
    add_item(({"shelf","shelves","tool shelf","tool shelves"}),
        "The western wall is covered with several tool shelves, all made " +
        "of wood. Despite being in a smithy, the shelves look remarkably " +
        "clean of dust and ashes.\n");
    add_item(({"sparkle","port"}),
        "Obviously, you cannot see the city from inside the smithy. But " +
        "you are aware that the grand port city of Sparkle lies to the " +
        "southeast, at the beginning of the Dark Road.\n");
    add_item(({"larton"}),
        "Somewhere to the north and west lies the city of Larton, beyond " +
        "the mountain pass at the end of the Dark Road.\n");
    add_item(({"city","cities"}),
        "You cannot see any cities from here!\n\nBut if you were follow the " +
        "Dark Road outside, it is likely you would arrive in a city sooner " +
        "or later.\n");
    add_item(({"ore","iron ore","iron","first crate","crate of ore",
            "crate of iron ore","crate of iron"}),
        "This crate only has small pieces of iron ore left in the bottom. " +
        "Presumably, the smith is waiting for a new shipment so he can " +
        "smelt the ore in the bloomery outside.\n");
    add_item(({"bloomery","slag","oven","stone oven"}),
        "Judging from the slag you saw around the stone oven outside, you " +
        "would assume that it serves as the bloomery for the iron ore the " +
        "smith keeps inside his workshop.\n");
    add_item(({"coal","crate of coal","second crate"}),
        "This crate appears to be half-full of precious nuggets of coal! " +
        "Coal is not always easy to come by in these parts, but it makes " +
        "an excellent fuel for the forge.\n");
    add_item(({"charcoal","crate of charcoal","third crate"}),
        "This crate is full of charcoal, a common fuel for any blacksmith's " +
        "forge.\n");
    add_item(({"beams","wooden beams","beam","wooden beam","rafters"}),
        "Several thick wooden beams and rafters cross the ceiling, " +
        "supporting the planks of wood and the slate tiles of the " +
        "roof above them.\n");
    add_item(({"planks","wooden planks","planks of wood","roof","slate",
            "tiles","slate roof","slate tiles","tile","slate tile"}),
        "There are many long planks of wood sitting atop the rafters in " +
        "the ceiling. Judging by the nail marks, you assume that this is " +
        "what supports the slate tiles of the roof.\n");
    add_item(({"chimney","smoke"}),
        "There is a little bit of smoke inside the smithy, but most of it " +
        "is funneled up through a metal chimney that cuts up through the " +
        "ceiling.\n");
    add_item(({"nail","nails","iron nail","iron nails"}),
        "You see a few nails stacked in jars on the shelves beside the " +
        "blacksmith tools, and also the points of some which peak through " +
        "the wooden planks of the ceiling where the slate tiles of the " +
        "roof have been nailed in.\n");
    add_item(({"jar","jars","nail jars","nail jar","stone jar","stone jars"}),
        "There are a couple of stone jars full of iron nails sitting on " +
        "the shelves.\n");
    add_item(({"points","ceiling nails","ceiling nail"}),
        "You can see the points of some nails peeking through the planks " +
        "in the ceiling where slate tiles have been affixed.\n");
    add_item(({"out","outside","outdoors"}),
        "Peeking past the leather flap of the opening in the south wall, " +
        "you can see the Dark Road cutting east and west across open " +
        "fields of grass.\n");
    add_item(({"ruin","ruins"}),
        "There are not many people other than this smith living out in " +
        "this part of the world, although you have seen the occasional " +
        "set of ruins decaying in the nearby fields.\n");
    add_item(({"leather","leather flap","flap"}),
        "A stout leather flap, brown and battered, hangs down over the " +
        "opening in the southern wall, keeping much of the heat inside " +
        "the smithy.\n");
    add_item(({"field","fields","grass"}),
        "On the south side of the Dark Road, wide fields stretch out for " +
        "miles, largely uninhabited aside from the occasional crumbling " +
        "ruins of previous settlements.\n");
    add_item(({"ruin","ruins","settlement","settlements"}),
        "You cannot see any ruined settlements from here, but you have " +
        "heard about some on the plains south of here.\n");
    add_item(({"bandit","bandits","hideout","secret hideout",
            "bandit hideout"}),
        "It is rumoured that bandits plague the Dark Road, setting up " +
        "ambushes in the mountain passes and operating from a secret " +
        "hideout somewhere near Sparkle.\n");
    add_item(({"sign","small sign","little sign","pricelist","list"}),
        "@@sign_long@@");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
    
    add_exit(THIS_DIR + "field10", "south", "@@out@@");

    /* Set up the trading system */ 
    config_default_trade();  
    /* Else things go wrong with "sell all" */
    set_money_give_out(({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */

    reset_room();
}

void

init()
{
    ::init();
    add_action("do_fix","sharpen",0);
    add_action("do_fix","mend",0);
    add_action("do_fix","repair",0);
    add_action("do_fix","wax",0);
    add_action("do_read","read",0);
    add_action("do_cost","cost",0);
    add_action("do_pump","pump",0);
    add_action("do_taste1","taste",0);
    add_action("do_taste2","taste",0);
    add_action("do_taste3","taste",0);
    add_action("do_hammer","hammer",0);
}

public string
sign_long()
{
    return
    "Hurgan's Forge - Services:\n"
    + "-------------------\n"
    + "Sharpen dull weapons - if possible!\n"
    + "Wax corroded weapons - when needed!\n"
    + "\n"
    + "Weapons of finer quality will require more of my time \n"
    + "because of the precision involved. All prices are final! \n"
    + "You may \"cost <weapon>\" if you want me to give you a quote.\n";
}

int
calc_wax_value(object ob)
{
    if (ob->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_CORR(ob->query_repair_corr()+1,
    ob->query_corroded()))
        return -1;

    return (ob->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}

int
calc_sharpen_value(object ob)
{
    if (ob->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_DULL(ob->query_repair_dull()+1,
        ob->query_dull()))
        return -1;

    return (ob->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}

public int
do_pump(string str)
{
    if(!strlen(str))
    {
        notify_fail("Pump what, the bellows?\n");
        return 0;
    }

    if((str != "bellows") && 
        (str != "the bellows") && (str != "large bellows") 
        && (str != "the large bellows"))
    {
        notify_fail("Pump what, the bellows?\n");
        return 0;
    }

    write("As you grasp the handles of the bellows and close them, a gust " +
        "of air blows into the forge, making the fire even hotter so that " +
        "the blacksmith can work.\n");
    SAYBB(" moves over to the bellows and pumps them, causing the fire " +
        "in the forge to grow even hotter.");
    return 1;
} /* do_pump */

public int
do_taste1(string str)
{
    if(!strlen(str))
    {
        notify_fail("Taste which barrel? You have to be more specific.\n");
        return 0;
    }

    if((str != "first barrel") && 
        (str != "fresh water barrel"))
    {
        notify_fail("Taste which barrel? You have to be more specific.\n");
        return 0;
    }

    write("You taste the liquid in the first barrel, confirming that " +
        "despite the strange flavour, it is in fact fresh water.\n");
    SAYBB(" dips their finger into one of the barrels to taste what is " +
        "inside.");
    return 1;
} /* do_taste1 */

public int
do_taste2(string str)
{
    if(!strlen(str))
    {
        notify_fail("Taste which barrel? You have to be more specific.\n");
        return 0;
    }

    if((str != "second barrel") && 
        (str != "salt water barrel") && (str != "brine barrel"))
    {
        notify_fail("Taste which barrel? You have to be more specific.\n");
        return 0;
    }

    write("You taste the liquid in the second barrel, confirming that " +
        "it is in fact brine.\n");
    SAYBB(" dips their finger into one of the barrels to taste what is " +
        "inside.");
    return 1;
} /* do_taste2 */

public int
do_taste3(string str)
{
    if(!strlen(str))
    {
        notify_fail("Taste which barrel? You have to be more specific.\n");
        return 0;
    }

    if((str != "third barrel") && 
        (str != "oil barrel") && (str != "olive oil barrel"))
    {
        notify_fail("Taste which barrel? You have to be more specific.\n");
        return 0;
    }

    write("You taste the liquid in the third barrel, confirming that " +
        "it is in fact olive oil.\n");
    SAYBB(" dips their finger into one of the barrels to taste what is " +
        "inside.");
    return 1;
} /* do_taste3 */

public int
do_hammer(string str)
{
    if(!strlen(str))
    {
        notify_fail("Hammer what? Metal on the forge?\n");
        return 0;
    }

    if((str != "metal") && 
        (str != "forge") && (str != "metal on the forge") &&
        (str != "metal on forge") && (str != "iron") &&
        (str != "metal in forge") && (str != "metal in the forge") &&
        (str != "iron in forge") && (str != "iron in the forge") &&
        (str != "iron on forge") && (str != "iron on the forge"))
    {
        notify_fail("Hammer what? Metal on the forge?\n");
        return 0;
    }

    write("You move to pick up one of the hammers in the smithy, but a " +
        "glare from the blacksmith stops you and you quietly put the " +
        "hammer back down.\n");
    SAYBB(" picks up a hammer and quickly puts it back in place after " +
        "a glare from the blacksmith.");
    return 1;
} /* do_hammer */

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if((str != "list") && (str != "pricelist") &&
        (str != "sign") && (str != "little sign") &&
        (str != "small sign"))
    return 0;
    write(sign_long());
    return 1;
}

int
do_cost(string str)
{
    object *weapon, tp;
    int v1, v2, v3;
    tp = this_player();
    notify_fail("Which weapon?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
        !sizeof(weapon))
    {
        return 0;
    }

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
    {
        return 0;
    }

    notify_fail("That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
    {
        return 0;
        v1 = calc_sharpen_value(weapon[0]);
        v2 = calc_wax_value(weapon[0]);
        write("Sharpening that " + weapon[0]->short() + " "
            + ((v1 == -1) ? "is not necessary.\n"
            : ("would cost about " + (v1) + " coppers.\n"))
            + "Waxing it "
            + ((v2 == -1) ? "is not necessary.\n"
            : ("would cost about " + (v2) + " coppers.\n")));
        return 1;
    }
}

int
do_fix(string str)
{

    object *weapon, tp;
    int int_str, value, *money_arr;
    string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
    verb;
    verb = query_verb();
    notify_fail(capitalize(verb) + " what?\n");
    if (!str)
    {
        return 0;
        object tp = this_player();
        /*   Check if the player defines what she wants to pay with
         *   and what you would like in return.
         */
    }

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
            tell_room(this_object(), "The smith says: I don't accept those "
                + pay_type + " coins, " + tp->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    if (get_type != "")
    {
        if (member_array(get_type, MONEY_TYPES) < 0)
        {
            tell_room(this_object(), "The smith says: " + capitalize(get_type) 
                + " coins? Never heard of those.\n");
            return 1;
        }
    }

    notify_fail("Mend what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
        !sizeof(weapon))
        return 0;

    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
        return 0;

    notify_fail("That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
        return 0;

    notify_fail("I cannot repair broken weapons.\n");
    if(weapon[0]->query_prop(OBJ_I_BROKEN))
        return 0;
        /* Talk about tricky code! ;-) */
        value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

    notify_fail("The smith says: I cannot " + verb + " that any further.\n");
    if (value == -1)
        return 0;
        /* Try to take the money */

    if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            tell_room(this_object(), "The smith says: I think that " 
                + weapon[0]->short() + " is a bit "
                + "more expensive, " + tp->query_nonmet_name() + ".\n");
            return 1;
        }

        if (money_arr[0] == 2)
        {
            tell_room(this_object(), "The smith says: You do not have any " 
                + pay_type + " coins, " + tp->query_nonmet_name() + ".\n");
            return 1;
        }

        else
        {
            tell_room(this_object(), "The smith says: I think that " 
                + weapon[0]->short() + " is a bit too expensive for you, " 
                + tp->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    /* It is paid for, so let's fix the weapon */
    value = call_other(this_object(), "fix_"+verb, weapon[0]);
    write("You give the smith the " + weapon[0]->short() + ".\n");
    say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
        " " + weapon[0]->short() + ".\n");
    tell_room(this_object(),
        "The smith " + verb + ((verb == "sharpen") ? "s" : "es") + " the "
            + weapon[0]->short() + ".\n"
            + "The smith gives the weapon back.\n");
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
    sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the smith " +coin_pay_text+ ".\n");
    if (coin_get_text)
    {
        write("You get " + coin_get_text + " in return.\n");
        return 1;
    }
}

void
fix_wax(object ob)
{
    ob->set_repair_corr(ob->query_repair_corr() + 1);
}

void
fix_sharpen(object ob)
{
    ob->set_repair_dull(ob->query_repair_dull() + 1);
}

void
reset_room() 
{
    if(!hurgan) hurgan = clone_object(WILD_DIR + "npc/hurgan.c");
    if (!present(hurgan)) hurgan->move_living("somewhere", this_object());
}

int
out()
{
    write("\n\nThe cool, open air kisses your skin as you leave " +
        "the warmth of the smithy and walk back to the Dark Road.\n\n");
    return 0;
}