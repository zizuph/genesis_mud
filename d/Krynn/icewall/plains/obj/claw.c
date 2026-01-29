/*
 * Igneous' claw.
 *
 * An attempt to make an "unarmed weapon".  This piece of armour directly
 * modifies a players unarmed attack for whichever hand he places it on.
 * It covers the hand tool slot so wielding weapons in that hand is
 * impossible.  It increases a players hit by 10% and their pen by 20%
 * as well as making thier attacks for the hand it covers a slash instead
 * of buldgeon.
 *
 * Copyright (C) Chad Richardson    September 1997
 *
 * Modification log:
 * Because of the addition of holdable items players wear this claw were
 * unable to attack with this unarmed weapon.  I have corrected this.
 * Igneous,  May 18th 1998
 *
 * Modified by Shanoga, 2020-09-30
 *  - Removed set value to int hand (was always left-handed)
 *  - Removed set_at() from create_armour that made it weapon-slot only
 *  - Called set_lefthanded and set_righthanded randomly on creation
 *    and have it always taking up W_HAND as well as A_L/R_HAND (as
 *    originally intended?)
 *  - NO changes to shadow
 *
 * Cotillion, 2020-10-05
 * - Fixed recovery
 * Ckrik, 2021-11-18
 * - Ported over to unarmed_enhancer.
 */
#pragma strict_types

inherit "/std/unarmed_enhancer";
inherit "/lib/keep";

#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>

#define ERROR(s)  log_file("claw_error",ctime(time()) + " " + s + "\n")

// The shadow the wear function clones.
#define CLAW_SHADOW  "/d/Krynn/icewall/plains/obj/claw_shadow.c"

// Prototypes
int prevent(string str);

int hand;

/*
 * Function:     set_lefthanded
 * Description:  Sets the claw to a left handed one
 */
void
set_lefthanded()
{
    set_at(A_L_HAND);
    hand = 0;
    add_adj(({"left","left-handed"}));
}

/*
 * Function:     set_righthanded
 * Description:  Sets the claw to a right handed one
 */
void
set_righthanded()
{
    set_at(A_R_HAND);
    hand = 1;
    add_adj(({"right","right-handed"}));
}

void
create_unarmed_enhancer()
{
    set_short("polished jagged claw");
    set_long("@@my_long@@");
    set_adj(({"polished","metal","jagged"}));

    set_default_enhancer(36, 38, W_SLASH | W_IMPALE, 14, A_R_HAND, 0, this_object());
    hand = random(2);
    if (hand)
        set_righthanded();
    else
        set_lefthanded();    
    set_name("claw");
    set_am(({4,0,-4}));

    add_prop(OBJ_I_WEIGHT, 150 * (5 + random(6)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) * 2);
    add_prop(OBJ_I_VALUE, 75 * (7 + random(4)));
}

string
my_long()
{
    return capitalize(LANG_THESHORT(this_object())) + " is a "+
        "vicious slashing metal claw which would fit over your "+
        (hand == 1 ? "right" : "left") + " hand.  " +
        "Extending from the base of this piece of armour are 4 jagged "+
        "razor-sharp prongs, each about ten inches long, that "+
        "look like they could pierce just about anything.\n";
}

int
query_hand()
{
    return hand;
}

public int
query_attack_blocked(int aid)
{
    return 0;
}

/*
 * Function    : wear
 * Description : Wears the armour and addes the new attack to the player
 *               wearing the armour.
 * Arguments   : arm: the armour that we are wearing
 * Returns     : 1
 */
public mixed
wear(object arm)
{
    int pen, hit, uskill;
    object player = environment(this_object());
    object shadow;

    if (!player->query_is_claw_shadowed())
    {
        setuid(); seteuid(getuid());
        shadow = clone_object(CLAW_SHADOW);
        if (shadow->shadow_me(player) != 1)
        {
            ERROR("Failed to load shadow for "+player->query_name()+".");
            shadow->remove_shadow();
        }
        else
        {
            player->add_claw(this_object());
        }
    }
    else
    {
        player->add_claw(this_object());
    }

    player->catch_msg("You wear "+LANG_THESHORT(this_object())+
        " overtop your "+(query_hand() == 0 ? "left" : "right") +
        " hand.\n");
    say(QCTNAME(player) + " wears " + LANG_THESHORT(this_object()) +
        " overtop " + player->query_possessive() +" "+
        (query_hand() == 0 ? "left" : "right") + " hand.\n");
    return 1;
}

/*
 * Function    : remove
 * Description : removes the claw and sets the players hit/pen back to
 *               normal for an unarmed attack.
 * Arguments   : arm: the armour being removed
 * Returns     : 1
 */
public mixed
remove(object arm)
{
    object player = query_worn();
    object co = player->query_combat_object();
    int pen, hit, uskill;


    if (player->query_is_claw_shadowed())
    {
        player->remove_claw(this_object());
        player->query_remove_claw_shadow();
    }

    player->catch_msg("You remove " + LANG_THESHORT(this_object()) +
      " from your " + (query_hand() == 0 ? "left" : "right") +
      " hand.\n");
    say(QCTNAME(player) +" removes "+ LANG_THESHORT(this_object()) +
      " from "+ player->query_possessive() +" " +
      (query_hand() == 0 ? "left" : "right") + " hand.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(prevent, "get");
    add_action(prevent, "take");
    add_action(prevent, "pick");
    add_action(prevent, "give");
    add_action(prevent, "drop");
}

/*
 * Function    : prevent
 * Description :  Prevents players when wearing 2 claws from moving
 *                objects via give drop, take etc...
 * Arguments   : str: The str we were trying to get
 * Returns     : 0/1
 */
int
prevent(string str)
{
    string qvb = query_verb();
    object *claws;

    //  If the claw isn't worn then why should we prevent moving of items?
    if (!query_worn())
    return 0;

    // If the player is at a recovery place or armageddon is active
    // we don't prevent players from dropping items.
    if (this_player()->check_recover_loc() && qvb == "drop")
    return 0;

    claws = filter(this_player()->query_armour(-1), &->query_is_claw());
    // Player has one hand free so item movement is allowed
    if (sizeof(claws) < 2)
    return 0;

    write("You are unable to "+qvb+" anything while wearing your "+
      COMPOSITE_DEAD(claws)+".\n");
    return 1;
}

/* Function name:   query_is_claw
 * Description  :   Used by a filter to figure out this is indeed a claw
 */
int
query_is_claw()
{
    return 1;
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + hand;
}

public void
init_recover(string arg)
{
    string *a = explode(arg, "&&");

    if (sizeof(a) > 1 && a[1] == "0")
        set_lefthanded();
    else
        set_righthanded();

    init_arm_recover(arg);
}
