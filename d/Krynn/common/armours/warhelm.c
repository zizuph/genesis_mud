/* By Boron, June 2003
   Modified by Arman March 2005
*/

/* Navarre Feb 2007 Changed to use F_WEIGHT_DEFAULT_ARMOUR and F_ARMOUR_VALUE */
/*
 * Navarre Jan 2011 Changed descriptions in Magic Info to match actual change.
                    Lowered the Mana drain on removal from all mana to 450 drain.
*/

inherit "/lib/keep";
inherit "/std/armour";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

#define INVIS_LEVEL  5

int id;

public void
create_armour()
{
    set_name("helm");
    add_name(({"helmet","armour", "mask"}));
    set_pname(({"armours","helmets"}));
    set_adj(({"steel","tempered", "despair", "of despair"}));
    set_short("mask of despair");
    set_pshort("masks of despair");
    set_ac(40);
    set_at(A_HEAD);
    set_am( ({-2,3,-1}) );
    set_wf(TO);
    set_long("The helmet has spikes on the back of the helmet " +
        "and a large pointy spike is formed on the top of it. " +
        "The front is protected by a face shaped metal mask perfectly aligned " +
        "to the face, where the eyes go, there is nothing " +
        "but darkness.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
             "This helmet allows the wearer to see level " + INVIS_LEVEL +
             " invisible objects, it drains one mana point per second. " +
             "It doesn't like undead at all, and will not allow itself to be " +
             "worn by one. If it is, it drains the undead of mana " +
             "in an explosion that removes it from the game.\n");
    add_prop(MAGIC_AM_ID_INFO,
             ({"This helmet will drain mana when worn.", 20,
               " It doesn't like undeads, and will not allow itself to " +
               "be worn by them.", 35,
               " When worn, the wearer will be able to see into the realms " +
               "of shadows, see what is normally unseen.\n", 65}));



/*               " It doesn't like undeads, and will not allow itself near " +
               "them.", 35,
               " If it is forced near them, it will explode leaving the " +
               "undead greatly scared.", 45,
               " When worn, the wearer will be able to see into the realms " +
               "of shadows, see what is normally unseen.\n", 65}));
*/
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));


    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));
}

void
invis_drain()
{
    object player;
    player = TO->query_worn();

    if ( !objectp(player) )
        return;

    if ( player->query_npc() )
    {
        player->heal_hp(100);
    }
    else if (player->query_mana() < 15)
    {
        player->heal_hp(-100);
        player->catch_msg("You are so mentally exhausted it drains your health.\n");
    }
    else
    {
        player->set_mana(player->query_mana() - 15);
    }

}

public mixed
wear()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        if ( interactive(TP) )
            TP->set_mana(TP->query_mana() / 2);
        else
            TP->set_mana(0);
                      
        TP->heal_hp(-250);
        TO->remove_object();
        return "The helmet vibrates madly in your undead hands, and " +
          "suddenly explodes in an inferno of fire and light!\n" +
          "You feel yourself mentally drained and burnt by the explosion.\n";
    }
    TP->add_prop(LIVE_I_SEE_INVIS, (TP->query_prop(LIVE_I_SEE_INVIS) + INVIS_LEVEL) );
    TP->catch_msg("As you wear the helmet your eyes relax, and you " +
            "feel aware.\n");
    id = set_alarm(15.0, 15.0, invis_drain);
    return 1;
}

public mixed
remove()
{
    set_this_player(query_worn());
    
    TP->add_prop(LIVE_I_SEE_INVIS, (TP->query_prop(LIVE_I_SEE_INVIS) - INVIS_LEVEL) );
    TP->catch_msg("As you remove the helmet your eyes tense as you try to see the unseen. " +
            "You feel mentally drained as you try to keep your eyes focussing.\n");
    TP->set_mana(MAX(TP->query_mana() - 450, 0));
    remove_alarm(id);
    return 1;
}


void enter_env(object dest, object old)
{
    ::enter_env( dest,  old);

/*  This part removed into the wear command due to its obvious
    potential for abuse - Arman 03/05  

    if (dest->query_prop(LIVE_I_UNDEAD))
    {
        if ( interactive(old) )
            dest->set_mana(dest->query_mana() / 2);
        else
            dest->set_mana(0);
                        
        dest->catch_msg("The helmet explodes in an inferno of light.\n" +
            "You feel yourself mentally drained by the power of the light.\n");
        dest->heal_hp(-250);
        TO->remove_object();
    }
*/

}
