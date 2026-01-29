/*
 * Gairent
 * Varian - March 2015
 *
 * Forgework copied from /d/Gondor/lebennin/thornlin/forge.c
 */

inherit "/lib/trade";

#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define WAX_COST     5  /* Waxing costs 5% per point */
#define SHARPEN_COST 10 /* Sharpening costs 10% */

inherit MIRKWOOD_OLDROAD_DIR + "base";
inherit MIRKWOOD_STD_DIR + "room";

static object palandur;


void

create_room()

{
    set_short("Smithy in Gairent");
    set_long("You are standing inside the large smithy of Gairent, watching the " +
        "shadows cast by the forge dance along the wooden walls. To the south, a " +
        "large door opens out into the rest of the village while a narrow doorway " +
        "in the eastern wall appears to lead out into a yard. In the middle of the " +
        "smithy is an anvil, set up close the forge, with several racks of tools " +
        "standing nearby allowing the blacksmith to work efficiently. The floor of " +
        "the smithy appears to be made of flat stones, although a thin layer of sand " +
        "makes it difficult to say for certain. A little sign on the wall seems " +
        "to offer some instructions for potential customers.\n");
  
    add_item_light(({"smithy", "room"}),
        "This is the large smithy of Gairent, where the " +
        "shadows cast by the forge dance along the wooden walls. To the south, a " +
        "large door opens out into the rest of the village while a narrow doorway " +
        "in the eastern wall appears to lead out into a yard. In the middle of the " +
        "smithy is an anvil, set up close the forge, with several racks of tools " +
        "standing nearby allowing the blacksmith to work efficiently. The floor of " +
        "the smithy appears to be made of flat stones, although a thin layer of sand " +
        "makes it difficult to say for certain. A little sign on the wall seems " +
        "to offer some instructions for potential customers.\n", LIGHT_ALL);
    add_item_light(({"door", "doors", "doorway"}),
        "There are two doors, one in the south wall leading back into the center " +
        "of the village, and one in the east wall leading into a side yard.\n", LIGHT_ALL);
    add_item_light(({"forge", "fire"}),
        "At the north end of the smithy, a brightly burning forge provides some " +
        "light, causing shadows to dance along the walls. In front of the forge " +
        "sits a heavy, iron anvil, where the blacksmith obviously does much of " +
        "his work. Near the anvil are also three small barrels, each full of " +
        "liquid. Several racks containing dozens of hammers, pliers and other " +
        "blacksmithing tools in all sizes also stand nearby, making it clear that " +
        "the blacksmith is a very organized man. On the top of the stone forge, a " +
        "tall, metal chimney reaches up through the ceiling while the bellows " +
        "is visible on one side of the forge.\n", LIGHT_ALL);
    add_item_light(({"east door", "narrow doorway", "east doorway", "narrow door"}),
        "The narrow door in the east wall opens up into a large, fenced yard which " +
        "is obviously owned by the blacksmith. The yard seems to be mostly filled with " +
        "a lot of junk, but there is a large cart which rests beneath a slender " +
        "maple tree in the middle. You could go visit it if you really " +
        "wanted to.\n", LIGHT_ALL);
    add_item_light(({"south door", "south doorway", "heavy door", "heavy doorway"}),
        "The heavy door in the south wall just opens up to lead back into the village " +
        "of Gairent.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls"}),
        "Like many buildings, this smithy has four walls. Which one did you " +
        "want to look at?\n", LIGHT_ALL);
    add_item_light(({"east wall", "eastern wall"}),
        "The eastern wall of the smith is made up of wooden planks, broken up " +
        "only by a narrow doorway leading into the side yard.\n", LIGHT_ALL);
    add_item_light(({"west wall", "western wall"}),
        "The western wall of the smithy is made up of wooden planks, and are " +
        "bare save for a little sign hanging in the middle.\n", LIGHT_ALL);
    add_item_light(({"north wall", "northern wall"}),
        "The northern wall of the smithy is made up of wooden planks, with the " +
        "stone of the blacksmith's forge sitting in front of it.\n", LIGHT_ALL);
    add_item_light(({"south wall", "southern wall"}),
        "The south wall of the smithy is made up of wooden planks, framing a " +
        "heavy door which leads back out into the village of Gairent.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "up"}),
        "Several thick, wooden beams stretch out across the ceiling, supporting " +
        "the wooden planks of the roof. A tall, metal chimney reaches up from the " +
        "forge before it pushes through the ceiling and roof of the smithy.\n", LIGHT_ALL);
    add_item_light(({"floor", "down"}),
        "The floor of the smithy appears to be composed mostly of heavy, flat stones " +
        "which have been set deep into the earth. A thin layer of sand seems to " +
        "be covering most of the floor everywhere you look.\n", LIGHT_ALL);
    add_item_light(({"stones", "flat stones"}),
        "These stones are rather flat, and most of them are quite large. They appear " +
        "to have been set deeply and firmly into the earth, providing a solid foundation " +
        "for the smithy to operate.\n", LIGHT_ALL);
    add_item_light(({"sand", "layer", "sand layer", "layer of sand"}),
        "There is a thin layer of sand which covers most of the floor here, obscuring " +
        "most of the large, flat stones which make up the floor.\n", LIGHT_ALL);
    add_item_light(({"anvil", "iron anvil", "heavy anvil"}),
        "In the middle of the smith is a heavy, iron anvil. This anvil is clearly " +
        "where the blacksmith does much of which work, hammering and flattening out " +
        "the iron he works. Nearby, the forge is brightly burning while several " +
        "racks of tools are within easy reach. Between the anvil and the forge are " +
        "three small barrels.\n", LIGHT_ALL);
    add_item_light(({"bellows", "large bellows"}),
        "These bellows serve to add more air into the forge, helping it to burn " +
        "hotter when used properly.\n", LIGHT_ALL);
    add_item_light(({"rack", "racks", "wooden rack", "wooden racks"}),
        "Several wooden racks, full of blacksmithing tools, have been set up in the " +
        "middle of the smithy close to the anvil and the forge. A quick glance tells " +
        "you that almost every imaginable blacksmithing tool sits somewhere on these " +
        "racks.\n", LIGHT_ALL);
    add_item_light(({"hammer", "hammers"}),
        "There are dozens of hammers here, all of different sizes, shapes and weights. " +
        "Most of the hammers have been stored neatly inside the wooden racks, save for " +
        "a couple of the larger sledges which lean up against the north wall.\n", LIGHT_ALL);
    add_item_light(({"pliers", "plier"}),
        "There are several pliers of different sizes sorted neatly inside the wooden racks " +
        "here with the rest of the blacksmithing tools.\n", LIGHT_ALL);
    add_item_light(({"tools", "blacksmith tools"}),
        "Organized neatly on the wooden racks are dozens of blacksmithing tools. A wide variety " +
        "of hammers, pliers, knives, chisels and every other blacksmithing tool you can imagine " +
        "are all found here.\n", LIGHT_ALL);
    add_item_light(({"yard", "east yard", "side yard"}),
        "The east yard is visible through the narrow doorway. The yard appears to be " +
        "fenced in, with barrels and crates scattered about the yard. In the middle, a " +
        "massive wooden cart rests beside a slender maple tree.\n", LIGHT_ALL);
    add_item_light(({"village", "gairent"}),
        "You are in the village of Gairent, deep within Mirkwood forest. You can reach " +
        "the center of the village by exiting through the heavy door in the south wall.\n", LIGHT_ALL);
    add_item_light(({"barrel", "barrels"}),
        "You see three small barrels, each full of liquid. They are labelled 'water', " +
        "'salt' and 'oil'. The barrels have been placed in between the anvil and the " +
        "forge.\n", LIGHT_ALL);
    add_item_light(({"chimney", "tall chimney", "metal chimney", "tall metal chimney"}),
        "This metal chimney stretches up from the forge all the way through the ceiling " +
        "of the smithy, helping to prevent the smoke from lingering too much inside " +
        "these walls.\n", LIGHT_ALL);
    add_item_light(({"beam", "beams", "wooden beam", "wooden beams"}),
        "Several thick, wooden beams stretch out across the ceiling, supporting the " +
        "wooden planks which make up the roof of the smithy.\n", LIGHT_ALL);
    add_item_light(({"plank", "planks", "wooden plank", "wooden planks"}),
        "The walls and roof of the smithy all seem to be constructed using thick, " +
        "wooden planks.\n", LIGHT_ALL);
    add_item_light(({"sign", "little sign"}),
        "This little sign just gives instructions on how the blacksmith does his " +
        "business. You can read it if you want more details.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(WOODSMEN_DIR + "gairent2", "south", "@@village@@");
    add_exit(WOODSMEN_DIR + "yard.c", "east");

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
    add_action("do_fix","wax",0);
    add_action("do_read","read",0);
    add_action("do_cost","cost",0);
}

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

do_read(str)
{
    notify_fail("Read what?\n");
    if (str != "list" && str != "pricelist" &&
        str != "sign" && str != "little sign")
        return 0;
    write(sign_long());
    return 1;
}
do_cost(str)
{
    object *weapon, tp;
    int v1, v2, v3;
    tp = this_player();
    notify_fail("Which weapon?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
        !sizeof(weapon))
    return 0;
    notify_fail("Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)

        return 0;

    notify_fail("That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
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
do_fix(str)
{

    object *weapon, tp;
    int int_str, value, *money_arr;
    string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
    verb;
    verb = query_verb();
    notify_fail(capitalize(verb) + " what?\n");
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
    write("You get " + coin_get_text + " in return.\n");
    return 1;
}
calc_wax_value(obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;
    if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
    obj->query_corroded()))
        return -1;
        return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}
calc_sharpen_value(obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;
    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
        obj->query_dull()))
        return -1;
        return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}
fix_wax(obj)
{
    obj->set_repair_corr(obj->query_repair_corr() + 1);
}
fix_sharpen(obj)
{
    obj->set_repair_dull(obj->query_repair_dull() + 1);
}


reset_room() 
{
    if(!palandur) palandur = clone_object(WOODSMEN_DIR + "npc/palandur.c");
    if (!present(palandur)) palandur->move_living("somewhere", this_object());
}

int
village()
{
    write("\n\nThe cool, open air of the village kisses your skin as you leave " +
        "the warmth of the smithy.\n\n");
    return 0;
}