/*
 * /d/Gondor/common/dwarf_guild/arm/npc_belt.c
 *
 * Copyright (C) Stas van der Schaaf - January 10 1994
 *               Mercade @ Genesis
 *
 * This belt is the guild object of the Dwarven race guild. The name of the
 * bearer is is branded in/on it. This particular object is the stripped
 * belt. It is used by NPC's in the guild. There is no autoloading
 * functionality in it. However, it will recover :-)
 */

#pragma save_binary

inherit "/std/armour";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define ARMOUR_CLASS        3
#define BELT_LOG           (DWARVEN_RACE_GUILD_ARMOURS + "belt_log")
#define TIME_BETWEEN_HITS  30
#define MAXIMUM_HIT_DAMAGE 25

/*
 * Global variables
 */
static string owner_name;
static int    last_thrash_time = 0;

void
create_armour()
{
    set_name("belt");
    add_name(DWARVEN_RACE_GUILD_BELT_ID);
    set_pname("belts");

    add_adj("broad");
    add_adj("supple");
    add_adj("leather");
    add_adj("brown");

    set_short("supple leather belt");
    set_pshort("leather belts");

    set_long("@@long_description@@");

    add_item( ({ "brand", "letters" }),
        "@@brand_description@@");
    add_cmd_item( ({ "brand", "letters" }), ({ "read" }),
        "@@brand_description@@");

    add_item( ({ "buckle", "silver buckle", "clasp" }),
        BSN("The buckle on the belt is made of silver. It has the design " +
        "of a dwarf wielding his axe and you are amazed by its many " +
        "details. It is the art of a master silver smith who made this " +
        "clasp with great patience and love for his work."));

    set_ac(ARMOUR_CLASS);
    set_at(A_WAIST);
    set_am( ({ 1, 0, -1 }) );

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE,  300);

    // guild objects do not expire over time as normal equipment.
    // this should not be called in an object without AoB approval!
    remove_item_expiration();

}

string
brand_description()
{
    string str;

    if (!strlen(owner_name))
    {
        return "There is no brand on the belt.\n";
    }

    str = "The letters \" " +
        (implode(map(explode(owner_name, ""), capitalize), " ")) +
        " \" are branded into the leather belt. ";

    if (TP->query_real_name() == owner_name)
    {
        str += "This brand means that this is your belt!";
    }
    else
    {
        str += "This brand means that this belt is not yours!";
    }

    return BSN(str);
}

string
long_description()
{
    string str = "It is a belt, made of supple brown leather. This belt is " +
        "given to all the members of the " + DWARVEN_RACE_GUILD_NAME +
        " as a token of friendship. ";

    if (strlen(owner_name))
    {
        str += "Some letters are branded into the belt. ";
    }

    str += "The belt is rather broad and has a beautifully designed silver " +
        "buckle on it.";

    return BSN(str);
}

int
thrash(string str)
{
    object *oblist;
    object victim;
    int    damage;

//  notify_fail("Due to repeated abuse as if it were a silly combat special, " +
//      "I have disabled this command. Whom the cap fits, knows to wear it.\n");
//  return 0;

    if (ENV(TO) != TP)
    {
        NFN0("You cannot thrash someone if you are not holding this " +
            short() + ".");
    }

    if (query_prop(OBJ_I_BROKEN))
    {
        NFN0("The " + short() + " is broken. You cannot use it to thrash " +
            "anyone with.");
    }

    if ((last_thrash_time + TIME_BETWEEN_HITS) > time())
    {
        NFN0("If you use the " + short() + " too many times in too short a " +
            "period, the leather may wear out faster. Better wait before " +
            "use it on someone again.");
    }

    if ((str == "enemy") ||
        (!strlen(str)))
    {
        victim = TP->query_attack();

        if (!objectp(victim))
        {
            NF0("You are not in combat. Whom do you wish to thrash?\n");
        }
    }
    else
    {
        oblist = PARSE_THIS(str,
            "[the] %l [with] [the] [supple] [leather] [belt]");

        switch(sizeof(oblist))
        {
        case 0:
            NF0("Thrash whom with your belt?\n");
            /* not reached */

        case 1:
            victim = oblist[0];
	    break;

        default:
            NFN0("Please select one victim to thrash at a time.\n");
            /* not reached */
        }

        if (!F_DARE_ATTACK(TP, victim) &&
            victim->query_npc() &&
            (member_array(victim, TP->query_enemy(-1)) == -1))
        {
            NF0("You do not dare attack " + victim->query_the_name(TP) +
                "\n.");
        }
    }

    if (!TP->query_wiz_level() &&
        victim->query_wiz_level())
    {
        victim->catch_tell(TP->query_name() + " briefly, ... very briefly, " +
            "considers to thrash you with " + POSSESSIVE(TP) +
            " Rockfriend belt.\n");
        NFN0("It would be very unwise to lift a weapon against a wizard. " +
            "Wizards are known not to react favourably to offensive actions " +
            "and their wrath has turned life-forms into dead-forms before.");
    }

    setuid();
    seteuid(getuid());
    write_file(BELT_LOG, sprintf("%s %s on %s (%s)\n", ctime(time()),
        CAP(TP->query_real_name()), CAP(victim->query_real_name()),
        file_name(victim)));

    write(BSN("You " + (worn ? "remove your belt and swing it" :
        "swing your belt") + " towards " + victim->query_the_name(TP) +
        " and beat " + OBJECTIVE(victim) + " up with it, hurting " +
        OBJECTIVE(victim) + " severely."));
    victim->CATCH_MSG((worn ? (" removes " + POSSESSIVE(TP) +
        " belt and swings it") : (" swings " + POSSESSIVE(TP) + " belt")) +
        " towards you and beats you up with it, hurting you severely.", TP);
    tell_room(ENV(TP), QCTNAME(TP) + (worn ? (" removes " + POSSESSIVE(TP) +
        " belt and swings it") : (" swings " + POSSESSIVE(TP) + " belt")) +
        " towards " + QTNAME(victim) + " and beats " + OBJECTIVE(victim) +
        " up with it, hurting " + OBJECTIVE(victim) + " severely.\n",
        ({ TP, victim }) );

    damage = (MAXIMUM_HIT_DAMAGE / 2) + random(MAXIMUM_HIT_DAMAGE / 2) + 1;
    victim->heal_hp(-(damage));

    /* count the hit with the belt. */
    got_hit(0, 0, TP, 0, damage);

    last_thrash_time = time();

    if (victim->query_hp() <= 0)
    {
        victim->do_die(TP);

        return 1;
    }

    /*
     * We check whether the player is already fighting the victim and if
     * so, do not attack for if we do, it will move TP on top. Maybe we
     * should make TP attack victim.
     */
    if ((victim->query_npc()) &&
        (member_array(victim, TP->query_enemy(-1)) == -1))
    {
        TP->command("kill " + OB_NAME(victim));
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(thrash, "thrash");
}

/*
 * Let the owner name be branded in the belt.
 */

void
set_owner_name(string name)
{
    owner_name = LOW(name);
}

string
query_owner_name()
{
    return owner_name;
}

/*
 * Recovery stuff
 */

string
query_recover()
{
    return MASTER + ":#name#" + (strlen(owner_name) ? owner_name : "_") +
        "#" + query_arm_recover();
}

void
init_recover(string arg)
{
    string foobar;

    sscanf(arg, "#name#%s#%s", owner_name, foobar);

    if (owner_name == "_")
    {
        owner_name = "";
    }

    init_arm_recover(arg);
}
