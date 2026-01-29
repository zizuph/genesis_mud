/*
 *  /d/Sparkle/area/tutorial/npc/forest_animal.c
 *
 *  This is the file for the state-dependant animals that roam the
 *  Sterling Woods in Silverdell.
 *
 *  Created September 2005, by Cooper Sherry (Gondor)
 */

#pragma strict_types
#include "../defs.h"

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <macros.h>             /* for VBFC_ME                  */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */

/* Global Variables */
public string   Animal_Size = "";

/* Prototypes */
public void     create_creature();
public string   trigger_emote();
public string   describe_short();
public string   describe_long();
public void     config_animal(string type);


/*
 * Function name:       create_creature
 * Description  :       set up the animal
 */
public void
create_creature()
{
    set_name( ({ "animal" }) );
    add_name( ({ "creature", "beast", "_tutorial_animal", 
                 "wolf" }) );
    add_adj( ({ "black" }) );

    set_short(describe_short);
    set_long(describe_long);

    set_skill(SS_AWARENESS, 15);
    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 13600);      /* 30 lbs */
    /* 15" tall by 10" long by 8" wide */
    add_prop(CONT_I_HEIGHT, 45);        /* 20 inches */
    add_prop(CONT_I_VOLUME, 39330);     /* 2400 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* chasing npcs is not fun! */

    set_attack_unarmed(0,  5, 7, W_IMPALE,  70, "front teeth");
    set_attack_unarmed(1,  7, 5, W_SLASH,   30, "paws");

    set_hitloc_unarmed(0, ({ 6,  6,  2 }),  40, "back");
    set_hitloc_unarmed(1, ({ 7,  2,  7 }),  20, "left side");
    set_hitloc_unarmed(2, ({ 7,  2,  7 }),  20, "right side");
    set_hitloc_unarmed(3, ({ 10, 5,  2 }),  10, "head");
    set_hitloc_unarmed(4, ({ 5,  5, 10 }),  10, "paws");

    add_leftover(OBJ_DIR + "intestines", "intestine", 1, 0, 0, 1);
    add_leftover(OBJ_DIR + "teeth", "tooth", random(5), 0, 0, 0);
    add_leftover(OBJ_DIR + "skull", "skull", 1, 0, 0, 1);

    set_act_time(20);
    add_act(VBFC_ME("trigger_emote"));
} /* create_creature */


/*
 * Function name:        trigger_emote
 * Description  :        send a bit-specific emote to each player
 *                       in the room.
 * Returns      :        A null string.
 */
public string
trigger_emote()
{
    object *target = FILTER_LIVE(all_inventory(environment(
                       this_object())));
    int     i, n;
    string  wolf_actions = one_of_list( ({
                " stops and lets out a howl.",
                " whimpers eagerly as it circles around you.",
                " stares at you with baleful eyes.",
                " growls menacingly.",
                " bares its sharp teeth.",
                " watches your every move.", }) );
    string  normal_actions = one_of_list( ({
                " trots along the ground, sniffing the dirt.",
                " stops completely still and peers around.",
                " sits and licks its tail.",
                " sits down and licks its fur.",
                " crouches, as if ready to pounce.",
                " yawns lazily.",
                " ambles around the area looking for food.",
                " pushes some dirt around with its nose and snorts.",
                " stops and scratches behind its ear for a bit.", }) );

    for (i = 0, n = sizeof(target); i < n; i++)
    {
        set_this_player(target[i]);
        if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
        {
            this_player()->catch_tell("The " + short()
              + normal_actions + "\n");
        }
        else
        {
            this_player()->catch_tell("The " + short()
              + wolf_actions + "\n");
        }
    }

    return "";
} /* trigger_emote */


/*
 * Function name:        describe_short
 * Description  :        provide a bit-based short description for the
 *                       animal.
 * Returns      :        string - the short description
 */
public string
describe_short()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        switch(Animal_Size)
        {
            case "small":
                return "small brown hedgehog";
                break;
            case "medium":
                return "slim red fox";
                break;
            case "large":
                return "large grey bobcat";
                break;
        }
    }

    switch(Animal_Size)
    {
        case "small":
            return "small black wolf";
            break;
        case "medium":
            return "hungry black wolf";
            break;
        case "large":
            return "large black wolf";
            break;
    }
} /* describe_short()


/*
 * Function name:        describe_long
 * Description  :        provide a bit-based long description for the
 *                       animal.
 * Returns      :        string - the long description
 */
public string
describe_long()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        switch(Animal_Size)
        {
            case "small":
                return "This hedgehog is small and fat. He is ambling"
                  + " around the area sniffing the ground. Occasionally he"
                  + " stops, as if listening for something.\n";
                break;
            case "medium":
                return "Lean and brown, this small fox has a sleek coat"
                  + " of fur which gleams in the open air. It seems to be"
                  + " poking around, looking for food.\n";
                break;
            case "large":
                return "Prowling around the wilderness, this bobcat seems"
                  + " to be looking for his next lunch. It takes little"
                  + " notice of you.\n";
                break;
        }
    }

    return "The fur on the back of this " + short() + " is bristling as"
      + " it stares at you with hungry yellow eyes. You get the distinct"
      + " feeling that it is considering whether or not to make a meal of"
      + " this unknown " + this_player()->query_race() + " who"
      + " is wandering around in its woods.\n";
} /* describe_long */


/*
 * Function name:        arm_me
 * Description  :        give the animal its pelt
 */
public void
arm_me()
{
    object fang;

    object  pelt = clone_object(ARM_DIR + Animal_Size + "_pelt");
    pelt->move(this_object());

    if (!random(7))
    {
        fang = clone_object(OBJ_DIR + "fang")->move(this_object());
    }
} /* arm_me */


/*
 * Function name:        config_animal
 * Description  :        set up the animal based on its size
 * Arguments    :        string type - the type of animal we are creating
 */
public void
config_animal(string type)
{
    Animal_Size = type;

    switch(type)
    {
        case "small":
            default_config_creature(5);
            set_skill(SS_DEFENCE, 7);
            add_name( ({ "hedgehog" }) );
            add_adj( ({ "small", "brown" }) );
            break;
        case "medium":
            default_config_creature(7);
            set_skill(SS_DEFENCE, 9);
            add_name( ({ "fox" }) );
            add_adj( ({ "hungry", "slim", "brown" }) );
            break;
        case "large":
            default_config_creature(9);
            set_skill(SS_DEFENCE, 11);
            add_name( ({ "bobcat", "cat" }) );
            add_adj( ({ "large", "grey" }) );
            break;
    }
} /* config_animal */


/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor.
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 *                                  to damage.  If not specified or an
 *                                  invalid hitloc is given, a random
 *                                  one will be used.
 * Returns:         The hitresult as given by the external combat object
 *
 * I'm redefining this so that the tutorial is extremely easy for the new
 * players in terms of grinding. I'm having each hit on the npcs deal
 * 2x damage.
 */
public mixed
hit_me(int wc_pen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    return ::hit_me(wc_pen * 2, dt, attacker, attack_id, target_hitloc);
} /* hit_me */