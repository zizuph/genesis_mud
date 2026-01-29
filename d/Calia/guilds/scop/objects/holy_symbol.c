/*
 * holy_symbol.c
 *
 * The guild object for the Spirit Circle of Psuchae
 * This symbol checks the players souls as well as has
 * the ability to store 600 mana and give it back to the
 * player when they would like it (doesn't save after logout)
 *
 * Copyright (C): Jaacar, August 1st, 2003
 *
 * Navarre March 3rd 2007:
 *   - Removed the mana charging part as per request from AoB
 *     Their precise word was: Mana regainers like that is evil 
 *                             Nuke it!
 *   - So it has hereby been fixed, they were also not paying tax
 *     for this ability.
 */


#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"
#include SPIRIT_HEADER

int stored_mana;

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
check_souls(object tp)
{
    seteuid(getuid());
    if (member_array(SPIRIT_LAY_SOUL, tp->query_cmdsoul_list()) == -1)
    {
        tp->add_cmdsoul(SPIRIT_LAY_SOUL);
        tp->update_hooks();
    }
    
    seteuid(getuid());
    if (member_array(SPIRIT_SOUL, tp->query_cmdsoul_list()) == -1)
    {
        tp->add_cmdsoul(SPIRIT_SOUL);
        tp->update_hooks();
    }
}

string
query_auto_load()
{
    return MASTER + ":";
}

void
create_object()
{
    set_name("sacred black and gold mandala");
    add_name("holy symbol");
    add_name("mandala");
    add_adj(({"sacred","black","gold"}));
    add_name("spirit_holy_symbol");
    add_name("_elemental_guild_mandala");
    set_short("sacred black and gold mandala");
    set_long("This sacred black and gold mandala is the holy symbol of Psuchae. "+
        "It is a small, black, round symbol with a pattern of gold in the middle. "+
        "The pattern consists of three same-sized, perfect circles intertwined, "+
        "surrounded by one large circle. @@circle_desc@@ Engraved along the "+
        "bottom edge of the symbol is 'help spirit'.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_STEAL,1);
}

string
circle_desc()
{
    switch(stored_mana)
    {
        case 0:
            return "The large circle is gold.";
            break;

        case 100:
            return "The large circle is glowing faintly.";
	        break;

        case 200:
            return "The large circle is glowing somewhat.";
            break;

        case 300:
            return "The large circle is glowing.";
            break;

        case 400:
            return "The large circle is glowing brightly.";
            break;

        case 500:
            return "The large circle is pulsating.";
            break;

        case 600:
            return "The large circle is pulsating very brightly.";
            break;

        default:
            return "The large circle is black. Please notify the guildmaster.";
            break;
    }
}

int
do_charge(string str)
{
    if (!str)
        return 0;

    if (str != "symbol" && str != "holy symbol" && str != "mandala" &&
        str != "sacred mandala")
    {
        NF("Charge what? Your sacred mandala?\n");
        return 0;
    }
        
    if (TP->query_mana() <= 100)
    {
        NF("You do not have enough mana to charge the sacred mandala.\n");
        return 0;
    }
        
    if (stored_mana >= 600)
    {
        NF("You cannot charge the sacred mandala any further.\n");
        return 0;
    }
        
    stored_mana += 100;
    TP->add_mana(-100);

    write("You hold the sacred mandala close to your heart, charging it "+
        "with your mental energies.\n");
    say(QCTNAME(TP)+" holds "+HIS+" sacred black and gold mandala close to "+
        HIS+" heart.\n");
    return 1;
}

int
do_drain(string str)
{
    if (!str)
        return 0;

    if (str != "symbol" && str != "holy symbol" && str != "mandala" &&
        str != "sacred mandala")
    {
        NF("Drain what? The sacred mandala?\n");
        return 0;
    }
        
    if (!stored_mana)
    {
        NF("You have no mana stored in the sacred mandala.\n");
        return 0;
    }
        
    stored_mana -= 100;
    TP->add_mana(100);
    write("You hold the sacred mandala close to your heart, absorbing some "+
        "of the mana stored inside.\n");
    say(QCTNAME(TP)+" holds "+HIS+" sacred black and gold mandala close to "+
        HIS+" heart.\n");
    return 1;
}

int
do_clasp(string str)
{
    if (!str)
        return 0;

    if (str != "symbol" && str != "holy symbol" && str != "mandala" &&
        str != "sacred mandala")
    {
        NF("Clasp what? Your sacred mandala?\n");
        return 0;
    }

    write("You clasp your sacred mandala and hold it close to your chest.\n");
    say(QCTNAME(TP)+" clasps "+HIS+" sacred black and gold mandala and holds "+
        "it close to "+HIS+" chest.\n");
    return 1;
}

void
init()
{
    ::init();
    if (is_spirit(TP))
        set_alarmv(0.5,0.0,"check_souls",({TP}));

    add_action(do_clasp,"clasp");
//    add_action(do_charge,"charge");
//    add_action(do_drain,"drain");
}
