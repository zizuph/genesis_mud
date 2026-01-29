/*
 * /d/Gondor/common/dwarf_guild/obj/whetstone.c
 *
 * It is a whetstone or grindstone. You can buy it from Borin, the smith and
 * use it to sharpen an axe or other weapon type if you are skilled enough.
 *
 * /Mercade, 30 July 1994
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/keep";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../dwarf.h"
#include "/d/Gondor/defs.h"

#define STONE_ID     (DWARVEN_RACE_GUILD_PREFIX + "whetstone")
#define CHECK_WEAPON "check_weapon"
#define STD_WEAPON   "/std/weapon"
#define WEAPON_SKILL (30 + random(20))

/*
 * Prototype.
 */
int sharpen(string str);

void
create_object()
{
    set_name("stone");
    add_name("whetstone");
    add_name("grindstone");
    add_name(STONE_ID);

    set_pname("stones");
    add_pname("whetstones");
    add_pname("grindstones");

    add_adj("whet");
    add_adj("grind");
    add_adj("hard");
    add_adj("small");
    add_adj("round");
    add_adj("cylindric");
    add_adj("cylindrical");

    set_short("small whetstone");
    set_long("It is a small grindstone and has an almost cylindric form. " +
        "The whetstone is meant to whet or sharpen blades if they are " +
        "slightly dull. You cannot make out the type of stone, but it " +
        "looks to be very hard.\n");

    add_prop(OBJ_I_VALUE,   48 + random( 25));
    add_prop(OBJ_I_VOLUME, 300 + random(101));
    add_prop(OBJ_I_WEIGHT, 700 + random(201));
}

void
init()
{
    ::init();

    add_action(sharpen, "sharpen");
    add_action(sharpen, "whet");
}

int 
sharpen(string str)
{
    object  tp = TP;
    object  obj;
    object *to_whet;
    int     dull;
    int     repair;

    if (!strlen(str))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }

    if ((!parse_command(str, tp, "[the] %i", to_whet)) ||
        (!sizeof(to_whet = NORMAL_ACCESS(to_whet, 0, 0))))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }

    if (objectp(obj = tp->query_attack()))
    {
        NF0("You are currently fighting " + obj->query_the_name(tp) +
            "! You do not have the time to " + QVB + " anything.\n");
    }

    if (sizeof(to_whet) != 1)
    {
        NF0("Please select only one weapon to " + QVB + ".\n");
    }
    else
    {
        obj = to_whet[0];
    }

    if (function_exists(CHECK_WEAPON, obj) != STD_WEAPON)
    {
        NF0("You can only " + QVB + " weapons.\n");
    }

    if (!(obj->query_dt() & (W_IMPALE | W_SLASH)))
    {
        NF0("Your " + obj->short() + " can only bluntly mutilate " +
            "your opponents. It cannot get dull.\n");
    }

    repair = obj->query_repair_dull();
    dull   = obj->query_dull();
    switch(dull - repair)
    {
    case 0:
        NF0("There is no reason to " + QVB + " your " + obj->short() +
            ", since it is sharp as it can be.\n");

    case 1:
        break;

    default:
        NF0("The " + obj->short() + " is too dull. You cannot " + QVB +
            " it yourself. Only a smith may be able to do something about " +
            "it.\n");
    }

    if (!F_LEGAL_WEAPON_REPAIR_DULL(repair, dull))
    {
        NF0("The " + obj->short() + " has been sharpened too many " +
           "times now. Grinding it again would probably harm the " +
           "material it was made of.\n");
    }

    /* If the player does not have enough skill, the weapon will
     * actually get worse. Regardless of your skill, there is a chance of
     * failure :-)
     */
    if ((tp->query_skill(SS_WEP_FIRST - W_FIRST + obj->query_wt()) <
            WEAPON_SKILL) ||
        (!random(5)))
    {
        obj->set_dull(++dull);

        write("You take the grindstone out of your pocket and start to " +
            "sharpen your " + obj->short() + ". This makes a very " +
            "annoying SHRIEKING sound. Due to your fumbling, the quality " +
            "of the weapon actually becomes worse!\n");
        say(QCTNAME(TP) + " takes a whetstone out of " + POSSESSIVE(tp) +
            " pocket and starts to sharpen " + POSSESSIVE(tp) + " " +
            obj->short() + ". This makes a very annoying SHRIEKING sound, " +
            "giving you the creeps!\n");

        return 1;       
    }

    obj->set_repair_dull(++repair);

    write("You take the whetstone out of your pocket and start to " +
        "skilfully sharpen your " + obj->short() + ". This makes a " +
        "very annoying SHRIEKING sound. In the end, however, the weapon " +
        "becomes sharp again.\n");
    say(QCTNAME(TP) + " takes a grindstone out of " + POSSESSIVE(tp) +
        " pocket and starts to sharpen " + POSSESSIVE(tp) + " " +
        obj->short() + ". This makes a very annoying SHRIEKING sound, " +
        "giving you the creeps! However, it seems to make the weapon " +
        "sharper.\n");

    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
}