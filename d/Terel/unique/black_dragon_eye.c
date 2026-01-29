/*  
 *  Dragon's eye  /d/Terel/unique/dragon_eye.c 
 *
 *  The eye of Rulucaraz, the famous black dragon of Terel.
 *
 *  Spell enhancer for elements FIRE, AIR, and DEATH.
 *  Grants haste and some elemental res to death/fire/air. 
 *
 * Created by: Zizuph Oct 2022
 * Approved by: Ckrik Oct 2022
 *
 */

inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
inherit "/lib/item_expiration";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

// spell power is high, but only for 3 elements.
#define MY_SP  48
#define MY_RES 10
#define MY_QUICKNESS 50
#define COST   (get_dynamic_mana_cost(TP, TS_INT, 15, 0, 300))
#define TP     this_player()

void
create_object()
{
    set_name("eye of rulucaraz");
    add_name(({"eye", "orb", "dragoneye", "::rulucarazes_eye::"}));
    set_adj(({"red", "crimson", "dragon", "rulucaraz", "rulucaraz's"}));
    set_short("crimson dragon eye");
    set_long("This is the eye of Rulucaraz, a fiery dragon " +
      "who dwells in the Dragon Tooth Mountains of Terel. "+ 
      "Large as a melon and just as heavy, the iris of the eye is "+
      "crimson in color, while the rest of the orb is purest white. "+
      "The eye seems to pulse as if a heart of fire is buried deep inside. " +
      "\n");

    add_item(({"iris", "red iris", "crimson iris" }),
      "It is dark red, colored like dried blood.\n");
    add_item(({"white of eye", "white"}), "The white part of the eye is "+
      "as smooth and pale as finest alabaster.\n");

    set_slots(W_LEFT);
    set_keep(1);
    set_item_expiration();

    set_spellpower_elements(({
      SS_ELEMENT_AIR, SS_ELEMENT_FIRE, SS_ELEMENT_DEATH
                           	}));
    set_magic_spellpower(MY_SP);

    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC, ({90,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({
      "This eye has seen much death abound\n", 20,
      "Where wicked flames have oft been found\n", 30,
      "Air defense too the holder surround\n", 40,
      "and with speed thine enemy you will confound.\n", 50 }));

    add_prop(OBJ_S_WIZINFO, "This is the eye of the Black Dragon. It is "+
      "cloned by Rulucatraz on his death as a leftover. "+
      "This is a spell enhancer level "+ MY_SP +" that grants haste as "+
      "well as "+ MY_RES +" levels of fire, air, and death res.\n"+
      "Cloned by: /d/Terel/mountain/obj/dragon.\n");

    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME,  4000);
    add_prop(OBJ_I_VALUE,   2000);

}


/*
 * Function:    do_mana_cost
/* Player is holding it, so lets add the nifty stuff */
public mixed
hold()
{

    this_player()->catch_msg(
      "As you hold the dragon's eye in your hand " +
      "you feel it pulsing quicker.\n");

    /* Add the haste */ 
    this_player()->add_prop(LIVE_I_QUICKNESS,
      (this_player()->query_prop(LIVE_I_QUICKNESS) + MY_QUICKNESS));

    /* Add a bit of magic resistance */
    this_player()->add_magic_effect(this_object());

    /* Activate the item_expiration_combat counter when it is being used. */
    add_expiration_combat_hook(this_player());

    return 0;
}

/* When the player stops holding it, remove the benefits */
public mixed
release()
{
    this_player()->catch_msg(
      "As you release your hold on the dragon's eye " +
      "the pulsing slows down.\n");

    /* Remove the dark vision */
    this_player()->add_prop(LIVE_I_QUICKNESS,
      (this_player()->query_prop(LIVE_I_QUICKNESS) - MY_QUICKNESS));

    /* Remove the little bit of magic res */
    this_player()->remove_magic_effect(this_object());

    /* De-activate item_expiration_combat counter when not using. */
    remove_expiration_combat_hook(this_player());

    return 0;
}


/* Add a bit of resistance to Water, Air, and Cold elements. 
 *  This is the eye of an Ice Dragon.
 */ 
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (prop == MAGIC_I_RES_DEATH || prop == MAGIC_I_RES_AIR || prop == MAGIC_I_RES_FIRE)
    {
	protectee->catch_msg("The "+ short() +" in your hand "+
	  "suddenly vibrates as if resisting a magical force!\n");
	return ({ MY_RES, 1}); // additive
    }
}


/* This makes sure held items are released when leaving inventory. */
void leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

string query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
}

void init_recover(string arg)
{
    init_item_expiration_recover(arg);
}

public void set_spellpower_elements(int* element_skills)
{
    spellpower_elements = element_skills;
}

public void appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
    write(item_spellpower_desc());
}

public string stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}

