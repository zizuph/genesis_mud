/*

   Create an object file, where you can add file paths, by calling
   add_smith_object, it should have an unique string ID which can be
   searched on

 */


#include "../knight/guild.h"
#include "../local.h"
#include "../armour/forged/forging.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#pragma save_binary

inherit IN_BASE;

//int do_mark(string str);
int light_fire(string str);
int fill_forge_with_coal(string str);
int forge_item(string str);
int fired_up = 0, got_coal = 0;

void
reset_vin_room()
{
    return;
}

create_vin_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"forge","old outdoor forge", "outdoor forge"}),
      "This old dwarven fireplace is where a smith may heat " +
      "metal before shaping it. @@fireplace_desc@@\n");
    add_item("moss","Moss grows along the sides of the " +
      "forge, indicating it has been sitting here unused " +
      "for some time.\n");
    add_item(({"bin","coal","bin of coal", "coal bin"}),
      "A weathered wooden bin sits near the forge, nearly " +
      "overgrown with wild grasses. It is full of coal for the " +
      "forge.\n");
    add_item(({"wild grasses","grasses"}),
      "Over time, wild grasses have grown up around the coal " +
      "bin.\n");
    add_item(({"smithy tools", "tools"}),
      "A selection of smithy tools have been left on the forge, " +
      "carefully wrapped in oiled deerskin. With these tools, a " +
      "Neidar may <mark> weapons or armours.\n");
    add_item(({"anvil"}),
      "An anvil of steel, that has begun to rust over. It once " +
      "was used to <forge> axes, warhammers and shields for the warriors of " +
      "Iron Delving, but since the loss of their smith, it has " +
      "been largely unused for some time.\n");
    add_item(({"path"}),
      "A path leads back towards Iron Delving to your northeast.\n");
    add_item("river","To your northwest is a river that runs merrily " +
      "past you.\n");
    add_item(({"oiled deerskin","deerskin"}),
      "An oiled deerskin has been used to protect a bundle of wood " +
      "from the elements.\n");
    add_item(({"bundle","bundle of wood","wood"}),
      "Resting against the coal bin is a bundle of wood wrapped " +
      "in oiled deerskin. From the looks of the wood, it is too " +
      "finely fashioned to be for the forge. You would guess these " +
      "pieces are used as handles for axes and warhammers forged " +
      "here.\n");

    add_cmd_item(({"coal","coal from bin"}),({"get","take"}),
      "@@get_coal");

    reset_vin_room();
}

string
get_coal()
{
    return "If you want to get coal for the forge, simply " +
    "'fill forge with coal', otherwise it would be best to " +
    "leave it alone.\n";
}

string
fireplace_desc()
{
    if(fired_up)
    {
    return "Right now it is fired up, and burning " +
    "with an intense heat.";
    }

    return "From the moss growing along its sides, and " +
    "its cold hearth, it looks like it hasn't been " +
    "used in a long time.";
}

string
short_descr()
{
    return "Before an old outdoor forge";
}

string
long_descr()
{
    return "You stand at the outskirts of Iron Delving " +
    "before an old outdoor forge. While unused for what " +
    "seems like an age, it was left with a full bin of " +
    "coal as well as with its smithy tools for the next smith " +
    "who uses the forge. Against the bin rests a bundle of wood " +
    "securely wrapped in oiled deerskin. " +
    " An anvil sits next to the forge, " +
    "while a path leads back towards Iron Delving to your " +
    "northeast.\n";
}

void
init()
{
    ::init();
    //add_action(do_mark, "mark" );
    add_action(light_fire, "light");
    add_action(fill_forge_with_coal, "fill");
    add_action(forge_item, "forge");

}


/*
private void
msg_mark(string text)
{
    TP->catch_msg("You fire up the forge and begin to heat a " +
      "branding iron in the hot coals. Once glowing, you pull the iron " +
      "from the fire, and " +
      "mark the " + text + " with the symbol of two twin peaks, " +
      "the mark of Iron Delving.\n");
    say(QCTNAME(TP) + " fires up the forge and begins to heat up a " +
      "branding iron in the hot coals. After a moment, " +HE(TP)+ " " +
      "pulls the glowing iron from the fire, and then carefully " +
      "marks " +HIS(TP)+ " " +text+ " with the symbol of two twin peaks.\n");
}

*/
private int
forge_item(string str)
{
    object ore, strap, shield, warhammer, axe, haft;
    string type, what;


    if (sscanf(str, "%s %s", type, what) != 2)
    {
        notify_fail("Forge what? See the poster for more info?\n");
        return 0;
    }

    if (!TP->query_wiz_level())
    {
        TP->catch_msg("You are not allowed to forge here, yet!");

        if( TP->query_guild_member("The Smiths Guild") )
        {
        TP->catch_msg("Only smiths may use the forge to " +
          "craft items.\n");
        return 1;
        }
    }

    if(!fired_up)
    {
        TP->catch_msg("As the forge isn't lit you decide to do so!\n");
        if (!light_fire("forge"))
            return 1;
    }

    switch (what)
    {
        case "shield":
            if (!TP->query_wiz_level())
                TP->catch_msg("\nTrying to forge shield.\n");

            TP->catch_msg("Forging what: " + type + what + "\n");

        break;

        default:
            TP->catch_msg("Default what: " + type + what + "\n");

    }

/*
    if(str == "shield")
    {
    if(P("skin", TP))
    {
        strap = P("skin", TP);
    }
    else if(P("hide", TP))
    {
        strap = P("hide", TP);
    }
        else if(P("pelt", TP))
        {
            strap = P("pelt", TP);
        }
    else
    {
        TP->catch_msg("You don't have anything to fashion " +
          "an arm strap with! Perhaps you should find yourself " +
          "some sort of hide?\n");
        return 1;
    }

    ore = P("ore", TP);
    strap_short = strap->short();
    TP->catch_msg("You fire up the forge until the coals glow like " +
      "the sun, and then carefully begin heating the " +ore->short()+
      ". Finally satisfied with its maleability, you take the glowing " +
      "ore from the forge with a large pair of tongs to the anvil, where " +
      "you begin hammering this shapeless mass with the care and " +
      "precision of a dwarven smith into the form of a large shield. " +
      "Carefully, you take the glowing shield to the nearby river, where " +
      "you quench it, sending a curtain of hissing steam up into the air. " +
      "Finally, you fashion an arm strap made from " +strap_short+ ", and " +
      "attach it to the shield.\n");

    say(QCTNAME(TP)+ " fires up the forge until the coals glow like " +
      "the sun, and then carefully begins heating the " +ore->short()+
      ". Finally satisfied with its maleability, " +QTNAME(TP)+ " takes the " +
      "glowing ore from the forge with a large pair of tongs to the anvil, where " +
      HE(TP)+ " begins hammering this shapeless mass with the care and " +
      "precision of a dwarven smith into the form of a large shield. " +
      "Carefully, " +QTNAME(TP)+ " takes the glowing shield to the nearby river, " +
      "where " +HE(TP)+ " quenches it, sending a curtain of hissing steam up into the " +
      "air. Finally, " +HE(TP)+ " fashions an arm strap made from " +strap_short+ ", " +
      "and attaches it to the shield.\n");

    material = ore->query_adj();
    switch(material)
    {
    case "iron":
        ac = 32;
        break;
    case "steel":
        ac = 37;
        break;
    default:
        ac = 30;
    }

    ore->remove_object();
    strap->remove_object();
    shield = clone_object(ARMOUR + "forged_shield");
    shield->set_ac(ac);
    shield->update_armour(shield);
    shield->set_material(material);
    shield->set_strap(strap_short);
    shield->add_adj(material);
    shield->move(TP);
    return 1;
    }

    if(str == "warhammer")
    {
    ore = P("ore", TP);

    TP->catch_msg("You fire up the forge until the coals glow like " +
      "the sun, and then carefully begin heating the " +ore->short()+
      ". Finally satisfied with its maleability, you take the glowing " +
      "ore from the forge with a large pair of tongs to the anvil, where " +
      "you begin hammering this shapeless mass with the care and " +
      "precision of a dwarven smith into the form of the head of a " +
      "warhammer. " +
      "Carefully, you take the glowing head to the nearby river, " +
      "where you quench it, sending a curtain of hissing steam up into the " +
      "air. While cooling, you take a wooden haft from the pile by the coal " +
      "bin and quickly fit it to the head, finishing off a fine dwarven warhammer!\n");

    say(QCTNAME(TP)+ " fires up the forge until the coals glow like " +
      "the sun, and then carefully begins heating the " +ore->short()+
      ". Finally satisfied with its maleability, " +QTNAME(TP)+ " takes the " +
      "glowing ore from the forge with a large pair of tongs to the anvil, where " +
      HE(TP)+ " begins hammering this shapeless mass with the care and " +
      "precision of a dwarven smith into the form of the head of a " +
      "warhammer. " +
      "Carefully, " +QTNAME(TP)+ " takes the glowing head to the nearby river, " +
      "where " +HE(TP)+ " quenches it, sending a curtain of hissing steam up into the " +
      "air. While cooling, " +QTNAME(TP)+ " takes a wooden haft from the pile by the coal " +
      "bin and quickly fits it to the head, finishing off a fine dwarven warhammer!\n");



    material = ore->query_adj();
    switch(material)
    {
    case "iron":
        hit = 30;
        pen = 35;
        break;
    case "steel":
        hit = 35;
        pen = 35;
        break;
    default:
        hit = 25;
        pen = 32;
    }

    ore->remove_object();
    warhammer = clone_object(WEP + "forged_hammer");
    warhammer->set_hit(hit);
    warhammer->set_pen(pen);
    warhammer->update_weapon(warhammer);
    warhammer->set_material(material);
    warhammer->add_adj(material);
    warhammer->move(TP);
    return 1;
    }

    if(str == "axe")
    {
    ore = P("ore", TP);

    TP->catch_msg("You fire up the forge until the coals glow like " +
      "the sun, and then carefully begin heating the " +ore->short()+
      ". Finally satisfied with its maleability, you take the glowing " +
      "ore from the forge with a large pair of tongs to the anvil, where " +
      "you begin hammering this shapeless mass with the care and " +
      "precision of a dwarven smith into the form of the head of an " +
      "axe. " +
      "Carefully, you take the glowing head to the nearby river, " +
      "where you quench it, sending a curtain of hissing steam up into the " +
      "air. While cooling, you take a wooden haft from the pile by the coal " +
      "bin and quickly fit it to the head. While still warm, you run a whetstone " +
      "quickly over the twin blades of the axe, sharpening them to a fine edge, " +
      "completing yourself a dwarven axe!\n");

    say(QCTNAME(TP)+ " fires up the forge until the coals glow like " +
      "the sun, and then carefully begins heating the " +ore->short()+
      ". Finally satisfied with its maleability, " +QTNAME(TP)+ " takes the " +
      "glowing ore from the forge with a large pair of tongs to the anvil, where " +
      HE(TP)+ " begins hammering this shapeless mass with the care and " +
      "precision of a dwarven smith into the form of the head of an " +
      "axe. " +
      "Carefully, " +QTNAME(TP)+ " takes the glowing head to the nearby river, " +
      "where " +HE(TP)+ " quenches it, sending a curtain of hissing steam up into the " +
      "air. While cooling, " +QTNAME(TP)+ " takes a wooden haft from the pile by the coal " +
      "bin and quickly fits it to the head. While still warm, " +QTNAME(TP)+ " runs a " +
      "whetstone quickly over the twin blades of the axe, sharpening them to a fine edge, " +
      "completing a dwarven waraxe!\n");


    material = ore->query_adj();
    switch(material)
    {
    case "iron":
        hit = 33;
        pen = 34;
        break;
    case "steel":
        hit = 35;
        pen = 35;
        break;
    default:
        hit = 27;
        pen = 30;
    }

    ore->remove_object();
    axe = clone_object(WEP + "forged_axe");
    axe->set_hit(hit);
    axe->set_pen(pen);
    axe->update_weapon(axe);
    axe->set_material(material);
    axe->add_adj(material);
    axe->move(TP);
    return 1;
    }

    TP->catch_msg("At the moment, smiths cannot forge " +
      "that here.\n");
    return 1;
    */
}

private int
fill_forge_with_coal(string str)
{
    if(str != "forge with coal")
    {
    TP->catch_msg("Fill what? The forge with coal?\n");
    return 1;
    }

    if(got_coal)
    {
    TP->catch_msg("The forge's furnace is already full of " +
      "coal.\n");
    return 1;
    }

    TP->catch_msg("You fill the forge's furnace with coal.\n");
    say(QCTNAME(TP)+ " fills the forge's furnace with coal.\n");
    got_coal = 1;
    return 1;
}

private int
light_fire(string str)
{
    if(str != "forge")
    {
    TP->catch_msg("Light what? The forge?\n");
    return 1;
    }

    if(!got_coal)
    {
        TP->catch_msg("There is no coal to light up the forge, so " +
          "you decide to fill it with coal first!\n");

        fill_forge_with_coal("forge with coal");

        return 1;
    }

    TP->catch_msg("The forge roars to life as you light it up!\n");
    say("The forge roars to life as " +QTNAME(TP)+ " lights it up!\n");

    fired_up = 1;
    return 1;
}

/*
private int
process_marked(int num, object ob, string text)
{
    object tp = this_player();
    string obj_short, stringtmp;

    if(!fired_up)
    {
    TP->catch_msg("The forge has not been lit yet!\n");
    return 1;
    }

    if(ob->query_prop(MARKED))
    {
    TP->catch_msg("It has already been marked.\n");
    return 1;
    }

    if (function_exists("create_object", ob) != "/std/weapon" &&
      function_exists("create_object", ob) != "/std/armour")
    {
    TP->catch_msg("Only weapons and armours can be marked.\n");
    return 1;
    }
    else
    { // not heap
    if (num != 1)
        return 0; // do not handle 'mark two swords'
    obj_short = ob->short();


    msg_mark(obj_short);
    stringtmp = ob->long();
    stringtmp += "It has been recently marked with the " +
    "symbol of two twin peaks.\n";
    ob->set_long(stringtmp);
    ob->add_prop(MARKED, 1);
    ob->add_prop(OBJ_M_NO_SELL, "This is the property of " +
      "the Neidar clan! The shopkeeper isn't brave enough to " +
      "buy stolen equipment owned by those crazy warriors!\n");
    return 1;
    }
}

int
do_mark(string str)
{
    object ob;
    int num;
    string text;

    if(!str)
    {
    notify_fail("Mark what?\n");
    return 0;
    }

    if(!TP->query_guild_member("Dwarven Warriors of the Neidar Clan"))
    {
    notify_fail("Only Neidar warriors may brand items with the " +
      "Iron Delving mark.\n");
    return 0;
    }

    // parse_command working on empty list is fast like sscanf
    // We need the text because ob->short() does not work correclty
    // with heaps. %o below will match the heap before split.
    if (!parse_command(str, ({0}), "%s", text))
    return 0;

    notify_fail("Mark what item?\n");

    if (parse_command(str, all_inventory(TP), "%o", ob))
    return process_marked(1, ob, text);

    if (parse_command(str, all_inventory(TP), "%d %o",
    num, ob))
    return process_marked(num, ob, text);
    return 0;
}
*/
