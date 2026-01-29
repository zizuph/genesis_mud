/* The jewelled onyx breastplate - coded 09/07/96 by Tulix III.        */
/* This armour is used by /d/Emerald/cave/npc/ogrelord.c and thus will */
/* only be cloned along with the npc once per reboot.                  */
/* The armour is magical - when worn, it gives off light level 1.      */
/* The armour is quite brittle, and wears more than usual... it has    */
/* therefore been enchanted so that it repairs itself periodically.    */
/* These running repairs cost the wearer some mana though.             */


inherit "/std/armour";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Emerald/tulix/t_defs.h"                               

#pragma strict_types

/* Global variable */
int new_hits;

/* Prototype functions */
string long_desc_string();
string jewel_desc_string();

void
create_armour()
{
    /* Set names and descriptions. */
    set_name("breastplate");
    add_name(({"armour", "armor"}));
    set_pname("breastplates");
    add_pname(({"armours", "armors"})); /* Note American spelling too. */
    set_short("jewelled onyx breastplate");
    set_pshort("jewelled onyx breastplates");
    set_long(long_desc_string);
    set_adj("jewelled");
    add_adj(({"magic", "magical", "black", "onyx"}));
    add_item(({"emeralds", "jewels", "decorations"}), jewel_desc_string); 
    
    set_ac(44);                    /* Not the best, but still very good.   */
    set_am(({ 1, -2, 1}));         /* Very stiff, but also a bit brittle.  */
    set_at(A_BODY);                /* Protects the torso of the wearer.    */
    set_likely_break(1);           /* Very rigid, so not likely to break.  */
    set_likely_cond(50);           /* Brittle, so wears down more easily.  */
    
    add_prop(OBJ_I_WEIGHT, 10500); /* Quite a substantial piece of armour. */
    add_prop(OBJ_I_VOLUME, 2000);  /* Quite dense. Will sink in water.     */
    add_prop(OBJ_I_VALUE, 1728);

    /* Set props required by /doc/man/general/armour & armour_guide.       */
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_I_RES_EARTH, 30);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment"}) );
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The breastplate seems magical.\n", 0,
        "The breastplate is made of magical materials.\n", 20,
        "The breastplate has magical emeralds set into it.\n" +
        "The emeralds will glow when the armour is worn.\n", 40,
        "The breastplate has enchanted emeralds set into it.\n" +
        "The emeralds will glow when the armour is damaged, melting " +
        "the surface just enough to repair any damage.\n", 80, 
        "The breastplate has enchanted emeralds set into it.\n" +
        "The emeralds will glow when the armour is damaged, melting " +
        "the surface just enough to repair any damage. The armour also " +
        "helps protect the wearer from spells which are based on the " +
        "earth element.\n", 95 }) );
    add_prop(OBJ_S_WIZINFO,  "This breastplate is found on the Lord Ogre " +
        "(/d/Emerald/cave/npc/ogrelord.c) who can be found in room " +
        "/d/Emerald/cave/levelc/cave24c.c once per reboot. The emeralds " +
        "set into the armour glow when the breastplate is worn, " +
        "and the armour will repair itself magically during combat. " +
        "This will cost the wearer some mana, however.\n");
}

/*
 * Function name: wear
 * Description:   Try to wear the armour. We also make the emeralds glow.
 * Arguments:     obj - the armour we want to wear.
 * Returns:       0 - the armour can be worn normally.
 */
public mixed
wear(object obj)
{
    object room;

    if (TO->query_worn())
        return 0;
    
    write("The emeralds set into it the breastplate start to glow.\n");
    room = ENV(TP);
    TO->add_prop(OBJ_I_LIGHT, 1);
    if (room)
    {
        tell_room(room, "A green glow surrounds " + QTNAME(TP) + " as " +
            PRON(TP) + " wears the breastplate.\n");
    }

    return 0;
}

/*
 * Function name: remove
 * Description:   Try to remove the armour. Used here to change light prop.
 * Arguments:     obj - the armour to remove.
 * Returns:       0 - Remove the armour normally.
 */
public mixed
remove(object obj)
{
    object room;

    if (!TO->query_worn())
        return 0;
    
    write("The emeralds set into it the breastplate stop glowing.\n");
    room = ENV(TP);
    if (room)
    {
        tell_room(room, "The green glow around " + QTNAME(TP) + " fades " +
            "  away as " + PRON(TP) + " removes the breastplate.\n");
    }
    TO->remove_prop(OBJ_I_LIGHT);

    return 0;
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It is used here
 *                to magically repair the armour periodically.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    object worn_by;
    int new_repair;    

    /* Behave as normal armour for 95% of hits. */
    worn_by = TO->query_worn();
    if (new_hits < 20)
    {
        new_hits++;
        ::got_hit(hid, ph, att, dt, dam);
        return 0;
    }

    /* Reset the new hits counter. */
    new_hits = 0;

    /* Check to see if the armour is damaged. */
    if (TO->query_repair() < TO->query_condition())
    {
        /* We don't want to take too much mana from the wearer. */
        if (worn_by->query_mana() <= 100)
            return 0;

        /* There's no such thing as a free lunch... or free magic. */
        worn_by->add_mana(-40);

        /* Repair the armour back to prime condition. */
        new_repair = TO->query_repair() + 1;
        TO->set_repair(new_repair);
        
        tell_room( ENV(worn_by), "The emeralds set into the breastplate " +
            "worn by " + QTNAME(worn_by) + " heat up momentarily!\n" + 
            "The black onyx surface melts partially, covering up cracks " +
            "and holes.\n");
    
        worn_by->catch_msg("The emeralds set into your breastplate " +
            "suddenly heat up momentarily!\nThe black onyx surface melts " +
            "partially, covering up cracks and holes.\n");
    }
    
    return 0;
}

string
long_desc_string()
{
    string jewel_desc;
    
    if (TO->query_prop(OBJ_I_LIGHT))
        jewel_desc = "are glowing with a bright green light";
    else
        jewel_desc = "appear to be glowing slightly";
    
    return "This breastplate has been made from magical black onyx, " +
        "which only occurs naturally in the Emerald mines. As this type " +
        "of onyx is so resilient, it is reserved for use in only the very " +
        "finest pieces of armour. The decoration lavished on this " +
        "particular breastplate adds the final touch of quality to a most " +
        "impressive piece. This armour certainly has unique styling, " +
        "and it was clearly not made for use by common rabble. " +
        "The jewels set into the armour are emeralds, " +
        "which " + jewel_desc + ".\n";
}

string
jewel_desc_string()
{
    string jewel_desc;
    
    if (TO->query_prop(OBJ_I_LIGHT))
        jewel_desc = "which are glowing with a bright green light";
    else
        jewel_desc = "which appear to be glowing slightly";
    
    return "The emeralds which adorn this piece of armour are arranged " +
        "in a double helix which crosses itself four times on the way " +
        "up to the top. At the top, the double helix ends in a continuous " +
        "band of emeralds, " + jewel_desc + " as they encircle the neck.\n"; 
}
