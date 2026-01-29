/*
 *  /d/Sparkle/area/tutorial/npc/bunny.c
 *
 *  This is the infestation that the player is called to deal with
 *  in the farms north of Greenhollow in the tutorial.
 *
 *  Created August 2005, by Cooper Sherry (Gondor)
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
public string   Bunny_Type = "";

/* Prototypes */
public void     create_creature();
public string   trigger_emote();
public string   describe_short();
public string   describe_long();
public void     config_bunny(string type);
public void     notify_death(object killer);


/*
 * Function name:       create_creature
 * Description  :       set up the bird
 */
public void
create_creature()
{
    set_name( ({ "bunny" }) );
    add_name( ({ "rabbit", "creature", "beast", "animal", "rodent",
                 "demon", "_tutorial_bunny", "vermin",
                 "bunny rabbit" }) );
    add_pname( ({ "bunnies" }) );
    add_adj( ({ "little", "large", "white", "demonic", "black", "bunny",
                "fluffy" }) );
    set_race_name("rabbit");

    set_short(describe_short);
    set_long(describe_long);

    /* this seems to be the only way to allow for "exa bunny rabbit" /*
    add_cmd_item( ({ "bunny rabbit" }), ({ "exa" }), long);

    set_skill(SS_AWARENESS, 15);
    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 1360);      /* 3 lbs */
    /* 7" tall by 12" long by 4" wide */
    add_prop(CONT_I_HEIGHT, 17);        /* 7 inches */
    add_prop(CONT_I_VOLUME, 19665);     /* 1200 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* chasing npcs is not fun! */

    set_attack_unarmed(0,  2, 5, W_IMPALE,  70, "front teeth");
    set_attack_unarmed(1,  2, 3, W_SLASH,   30, "paws");

    set_hitloc_unarmed(0, ({ 6,  6,  2 }),  40, "back");
    set_hitloc_unarmed(1, ({ 7,  2,  7 }),  20, "left side");
    set_hitloc_unarmed(2, ({ 7,  2,  7 }),  20, "right side");
    set_hitloc_unarmed(3, ({ 10, 5,  2 }),  10, "head");
    set_hitloc_unarmed(4, ({ 5,  5, 10 }),  10, "paws");

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
    mixed  *target = FILTER_LIVE(all_inventory(environment(
                       this_object())));
    int     i, n;
    string  demon_actions = one_of_list( ({
                " lets out an unnatural growl.",
                " peers at you with glowing red eyes.",
                " emits a long, spine-tingling hiss.",
                " spits some blood on the ground.",
                " digs in the ground as if looking for something.",
                " produces a low, gurgling sound.", }) );
    string  normal_actions = one_of_list( ({
                " hops over a clod of dirt.",
                " sniffs at the air.",
                " moves quickly around, its nose sniffing the soil.",
                " twitches its whiskers at you.",
                " stops perfectly still, peering at you.",
                " lifts its head as if listening to something.", }) );

    for (i = 0, n = sizeof(target); i < n; i++)
    {
        set_this_player(target[i]);
        if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
        {
            this_player()->catch_tell("The " + short()
              + normal_actions + "\n");
        }
        else
        {
            this_player()->catch_tell("The " + short()
              + demon_actions + "\n");
        }
    }

    return "";
} /* trigger_emote */


/*
 * Function name:        describe_short
 * Description  :        provide a bit-based short description for the
 *                       bunny.
 * Returns      :        string - the short description
 */
public string
describe_short()
{
    object tp = this_player();
    object *ply;
    if (tp == this_object())
    {
        ply = FILTER_PLAYERS(all_inventory(environment(
            this_object())));
        if (sizeof(ply))
            tp = ply[0];
    }
    
//    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    if (TUTORIAL_MASTER->query_tutorial(tp->query_real_name(), (BUNNY_BIT)))
    {
        switch(Bunny_Type)
        {
            case "baby":
                add_adj( ({ "baby" }) );
                return "fluffy baby bunny";
                break;
            case "bunny":
                return "fluffy white bunny";
                break;
            case "rabbit":
                return "fluffy white rabbit";
                break;
            case "large":
                return "large white rabbit";
                break;
            case "jack":
                add_name( ({ "jackrabbit" }) );
                add_adj( ({ "jack" }) );
                return "white jackrabbit";
                break;
        }
    }

    switch(Bunny_Type)
    {
        case "baby":
            add_adj( ({ "baby" }) );
            return "demonic baby bunny";
            break;
        case "bunny":
            return "demonic black bunny";
            break;
        case "rabbit":
            return "demonic black rabbit";
            break;
        case "large":
            return "large demonic rabbit";
            break;
        case "jack":
            add_name( ({ "jackrabbit" }) );
            add_adj( ({ "jack" }) );
            return "demonic jackrabbit";
            break;
    }
} /* describe_short()


/*
 * Function name:        describe_long
 * Description  :        provide a bit-based long description for the
 *                       bunny.
 * Returns      :        string - the long description
 */
public string
describe_long()
{
    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        return "Though probably capable of being a bit of a pest in the"
          + " garden, this fluffy little fellow is rather cute. Its"
          + " white fur is poofing out all over the place.\n";
    }

    return "This " + short() + " is a rather horrifying sight! Its"
      + " fur is black as night, and its eyes glow with a demonic"
      + " intensity that sends chills down your spine.\n";
} /* describe_long */


/*
 * Function name:        arm_me
 * Description  :        give the bunny its foot
 * Arguements   :        string type - what type of bunny foot?
 */
public void
arm_me(string type)
{
    object  foot = clone_object(OBJ_DIR + type + "_foot");
    foot->move(this_object());
} /* arm_me */


/*
 * Function name:        config_bunny
 * Description  :        set up the bunny based on its type
 * Arguments    :        string type - the type of bunny we are creating
 */
public void
config_bunny(string type)
{
    Bunny_Type = type;

    switch(type)
    {
        case "baby":
            default_config_creature(1);
            set_skill(SS_DEFENCE, 2);
            break;
        case "bunny":
            default_config_creature(2);
            set_skill(SS_DEFENCE, 5);
            break;
        case "rabbit":
            default_config_creature(3);
            set_skill(SS_DEFENCE, 7);
            break;
        case "large":
            default_config_creature(4);
            set_skill(SS_DEFENCE, 10);
            break;
        case "jack":
            default_config_creature(5);
            set_skill(SS_DEFENCE, 12);
            break;
    }

    if (!random(7))
    {
        arm_me("lucky");
    }
    else
    {
        arm_me(Bunny_Type);
    }
    
} /* config_bunny */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 *                clone more bunnies if in the henhouse.
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    tell_room(environment(this_object()), 
        QCTNAME(this_object()) + " died.\n", this_object());

    if (!living(killer))
    {
        return;
    }
 
    /*
     * Give specific information about who killed this poor soul.
     */
    tell_object(killer, 
        "You killed " + this_object()->query_the_name(killer) + ".\n");
    tell_room(environment(this_object()),  QCTNAME(killer) + " killed " +
        this_object()->query_objective() + ".\n", ({ this_object(), killer }));

    if (environment(this_object())->id("_tutorial_henhouse"))
    {
        environment(this_object())->reset_room();
    }
} /* notify_death */


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
