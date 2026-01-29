/*
 *  Dragon hatchling form for the serpent figurine magic item
 *  /d/Krynn/tharkadan/obj/polymorph_figurine.c 
 *
 *  Arman 2017
 */

inherit "/d/Genesis/race/shapeshift/shapeshift_creature";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Genesis/imbuement/imbuement.h"
#include "/d/Genesis/specials/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define MAP             "/d/Sparkle/std/obj/magic_map"

#define A_BITE  0                /* method of attack */
#define A_RWING 1
#define A_LWING 2
#define A_RCLAW 3
#define A_LCLAW 4

#define H_HEAD      0
#define H_BODY      1
#define H_TAIL      2
#define H_WING      3
#define H_BELLY     4

#define NO_INTRO_OBJ  "/d/Genesis/race/shapeshift/wohs_polymorph_self_no_intro_obj.c"
#define DRAGON_FEAR "/d/Ansalon/guild/dragonarmy/dragons/dragon_fear_obj_new.c"

mapping player_hid_to_bear_hid = ([
        A_BODY  : H_BODY,
        A_L_ARM : H_TAIL,
        A_R_ARM : H_WING,
        A_LEGS  : H_BELLY,
        A_HEAD  : H_HEAD
    ]);

mapping hitloc_damage_effects = ([ H_BODY : ({ }),
                                   H_TAIL : ({ }),
                                   H_WING : ({ }),
                                   H_BELLY : ({ }),
                                   H_HEAD : ({ }) ]);

function *did_hit_imbue_effects = ({ });

string colour;

// Prototypes
private void convert_armour_imbues();
private void convert_weapon_imbues();

void
create_shapeshift_creature()
{
    set_name("dragon"); 
    add_name("hatchling");
    set_race_name("dragon");

    if (!IS_CLONE)
        return;

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, "This creature is not physically capable of accepting " +
                  "gifts from you!\n");

    /* Can talk in dragonform

    add_prop(LIVE_M_MOUTH_BLOCKED, "While polymorphed in to this form you are " +
                  "unable to vocalise as you did in humanoid form!\n");
    */

    set_shapeshift_duration(165);
    set_alarm(5.5,0.0, &command("fly2 vale"));

    clone_object(NO_INTRO_OBJ)->move(TO,1);
    // clone_object(MAP)->move(TO,1);
}

public int
ansalon_krynn_dragon()
{
    return 1;
}

public object
clone_dragon_fear_object()
{
    setuid();
    seteuid(getuid());
    return clone_object(DRAGON_FEAR);
}

private void
dragon_fear_player(object who)
{
    object *inv;
    object player = get_player();

    if(!objectp(who))
    return;

    if(who == player)
    {
      return;
    }

    if(QRACE(who) == "draconian" || QRACE(who) == "dragon")
    {
      return;
    }

    inv = filter(all_inventory(who), &->ansalon_krynn_dragonfear());

    if(sizeof(inv))
    {
        inv[0]->slow_refresh_dragon_fear(); 
    }
    else
    {
        clone_dragon_fear_object()->move(who, 1);
    }
}

private void
remove_polymorph_object_from_closet()
{
   object env = E(TO);
   string closet = "/d/Genesis/specials/std/spells/obj/shapeshift_closet";

   if(file_name(env) == closet)
     TO->remove_object();

   return;
}

public void
enter_env(object to, object from)
{
   string closet = "/d/Genesis/specials/std/spells/obj/shapeshift_closet";

   if(file_name(to) == closet)
    set_alarm(0.1, 0.0, &remove_polymorph_object_from_closet());

}

public void
init_living()
{
    ::init_living();

    // set_alarm(0.1, 0.0, &remove_polymorph_object_from_closet());
    set_alarm(0.2, 0.0, &dragon_fear_player(TP));
}

/*
 * Function name: race_sound
 * Description  : This function returns the VBFC value for the sound a
 *                particular living hears when this player speaks. It
 *                operates on previous_object(-1). Notice that we use
 *                query_race rather than query_race_name since the first
 *                will always return a true and valid race name. The
 *                person speaking is this_player().
 * Returns      : string - the race sound the receiver hears.
 */
public string
race_sound()
{
    return "hisses";
}

/*
 * Function:    query_presentation
 * Description: Gives a presentation of the living in one line. Including
 *              Name, Race, Guild titles, Alignment and Experience level
 *              This should only be displayed to met players.
 *              E.g.: "Fatty the donut-fan, wizard, male gnome (eating)"
 * Returns:     The presentation string
 */

public string
query_presentation()
{
/*
    return "You have taken the form of " +LANG_ADDART(query_short())+ ". Covered " +
        "with thick scales from the tip of your tail to your toothy mouth, " +
        "formidable natural weapons in your teeth and claws, and great wings " +
        "strong enough to roam the skies, you revel in a form " +
        "unchallenged as one of the most powerful creatures in the realms";
*/
    return "The "+query_short();
}

public string
query_dragon_colour()
{
    return colour;
}


/*
 * Function name: hook_pre_shapeshift_transform
 * Description  : Called before the player is moved to their shapeshifted form
 *              : The player object is still in the room so it can be
 *              : used for VBFC's and the like.
 */

public void
hook_pre_shapeshift_transform()
{
    object env = environment(this_object());
    object player = get_player();

    tell_room(env, "As the icy vapours spread through " +QTPNAME(player) + " body, "  +HE(player)+ 
         " begins to change form! Stretching " +HIS(player)+ " arms out wide, " +HE(player)+
         " jubilantly shrieks to the sky as " + HIS(player)+ " body expands into the draconic form " +
         "of "+ LANG_ADDART(this_object()->query_nonmet_name()) + ".\n",
        ({ this_object(), player }));
    player->catch_tell("As the icy vapours spread through your body, you begin to feel yourself change " +
        "form! You spread your arms wide and shriek jubilantly to the sky as your " +
        "body expands into the draconic form of "+LANG_ADDART(this_object()->query_nonmet_name()) + ".\n");
}

/*
 * Function name: hook_pre_shapeshift_return
 * Description  : Called before the player is returned to their real body.
 *              : The player object is already in the room so it can be
 *              : used for VBFC's and the like.
 */
public void 
hook_pre_shapeshift_return()
{
    object env = environment(this_object());
    object player = get_player();

    tell_room(env, QCTPNAME(this_object()) + " form suddenly begins " +
        "to contract, and reform into " +QTNAME(player)+ ".\n", ({ this_object(), player }));
    this_object()->catch_tell("You feel your draconic form suddenly begin to " +
        "contract, and you find yourself changing back to your "
        + player->query_race_name() + " form.\n");
}

public void
hook_prepare_shapeshift_target()
{
    // Handle skill conversion
    // Handle resistances
    // Handle hit / pen / ac 
    // Handle stats
    // Handle quickness
    // Handle health conversion
    // Handle fatigue / stuffed 
    // Todo: check for handling of weapons like the mage bane while in the holding room

    object player = get_player();


    /*                   DESCRIPTIONS                          */

    string age;
    int *teeth, *claw, *wing, *skin, rank_mod;

    age = "hatchling";
    colour = "white";

    teeth = ({ 25, 25 });
    claw = ({ 25, 25 });
    wing = ({ 25, 25 });
    skin = ({ 25, 25, 25, 25, 25 });
    add_prop(CONT_I_WEIGHT, 80000); /* weight = 80 kilograms */
    add_prop(CONT_I_HEIGHT, 1200); /* height = 1.2 metres */
    add_prop(CONT_I_VOLUME, 80000); /* volume = 80 liters */    

    set_short(colour + " dragon " + age);
    set_adj(({ age, colour }));

    set_long("Before you stands " +LANG_ADDART(colour)+ " dragon " +age+ ". Covered " +
        "with scales from its tail-tip to toothy mouth, formidable natural weapons " +
        "in its teeth and claws, and great wings strong enough to roam the skies, it is " +
        "no wonder these reptiles when fully grown are unchallenged as the most powerful " +
        "creatures in the realms! This one however is a juvenile, with much growth to do " +
        "to reach its full potential.\n");

    if(player->query_gender() == G_FEMALE)
       set_gender(G_FEMALE);
    else
       set_gender(G_MALE);

    /*                   FORMULA FOR STATS                          */

    set_stats(({ 100, 100, 150, 100, 100, 100 }));

    set_hp(10000);
    set_mana(10000);
    set_fatigue(1000);
    set_stuffed(10000);

    /*                   FORMULA FOR SKILLS                          */

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_ELEMENT_AIR, 40);
    set_skill(SS_ELEMENT_WATER, 40);
    set_skill(SS_FORM_TRANSMUTATION, 40);

    /*                   FORMULA FOR NATURAL WEAPONS AND AC           */

    // ac and hit pen determined by dragon age

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE, teeth[0], teeth[1], W_IMPALE, 30, "bite");
    set_attack_unarmed(A_RWING, wing[0], wing[1], W_BLUDGEON, 15, "right wing");
    set_attack_unarmed(A_LWING, wing[0], wing[1], W_BLUDGEON, 15, "left wing");
    set_attack_unarmed(A_RCLAW, claw[0], claw[1], W_SLASH, 45, "right claw");
    set_attack_unarmed(A_LCLAW, claw[0], claw[1], W_SLASH, 45, "left claw");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */

    set_hitloc_unarmed(H_HEAD, skin[0], 20, "head");
    set_hitloc_unarmed(H_BODY, skin[1], 40, "body");
    set_hitloc_unarmed(H_TAIL, skin[2], 25, "tail");
    set_hitloc_unarmed(H_WING, skin[3], 14, "wing");
    set_hitloc_unarmed(H_BELLY, skin[4], 1, "belly");


    /*                        OTHER FUNCTIONS                         */

    convert_weapon_imbues();
    convert_armour_imbues();

    add_cmdsoul(ABILITY_DIR + "guilds/souls/spell_manager_soul");
    add_cmdsoul(SOHM_DIR + "souls/wohs_polymorph_self_soul");
    update_hooks();

    clone_object(MANA_SHADOW)->shadow_me(this_object());
}

// Generic imbue handling

/*
 * Function name: imbue_shadows
 * Description:   Goes over an objects shadows to find all imbues
 * Arguments:     ob - the object to check for imbues
 * Returns:       A list of imbues (or empty if none)
 */
private object *
imbue_shadows(object ob) 
{
    object *shadows = ({ });
    while (ob = shadow(ob, 0)) 
    {
        if (ob->has_imbue_shadow()) shadows += ({ ob });
    }
    return shadows;
}

/*
 * Function name: handle_imbue
 * Description:   Convert imbues that are not weapon / armour damage related
 * Arguments:     imbue - the imbue to convert 
 */
private void
handle_imbue(object imbue)
{
    send_debug_message("handle_imbue", 
        sprintf("Convert imbue %O for shapeshifting\n", imbue));

    // TODO effect_healing_shadow
} 

// Weapon imbue handling
private void
bane_strike_message(object imbue, object item_owner, object enemy,
    string hitloc_desc, string hit_desc, string damage_desc, int damage)
{
    string damage_msg = imbue->query_damage_msg();

    item_owner->catch_msg(capitalize(damage_msg) + " your "
      + " claws and " + hit_desc + " the " + hitloc_desc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + damage_desc + ".\n");

    enemy->catch_msg(capitalize(damage_msg) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " your " + hitloc_desc + "!\n"
      + "You are " + damage_desc + ".\n");

    item_owner->tell_watcher(capitalize(damage_msg) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " the " + hitloc_desc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + damage_desc
      + ".\n", enemy);
}

private void
bane_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger bane effect %O\n", imbue));
    imbue->check_race(this_object(), enemy, hid, &bane_strike_message(imbue), 0);
}

private void
elemental_strike_message(object imbue, object item_owner, object enemy,
    string hitloc_desc, string hit_desc, string damage_desc, int damage)
{
    string *damage_msgs = imbue->query_damage_msgs();

    item_owner->catch_msg(capitalize(damage_msgs[0]) + " your "
      + " claws and " + hit_desc + " the " + hitloc_desc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + damage_desc + " by the " + damage_msgs[1] + ".\n");

    enemy->catch_msg(capitalize(damage_msgs[0]) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " your " + hitloc_desc + "!\n"
      + "You are " + damage_desc + " by the " + damage_msgs[1] + ".\n");

    item_owner->tell_watcher(capitalize(damage_msgs[0]) + " "
      + QTNAME(item_owner) + "'s claws and " + hit_desc
      + " the " + hitloc_desc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + damage_desc
      + " by the " + damage_msgs[1] + ".\n", enemy);
}

private void
damage_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger damage effect %O\n", imbue));
    imbue->elemental_strike(this_object(), enemy, hid, &elemental_strike_message(imbue));
}

private void
poison_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger poison effect %O\n", imbue));
}

private void
slow_imbue_effect(object imbue, int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam, int hid)
{
    send_debug_message("hit_imbue", sprintf("Trigger slow effect %O\n", imbue));
}

public varargs int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam, int hid)
{
    if (phurt > 0) 
    {
        foreach(function effect : did_hit_imbue_effects) {
            set_alarm(0.0, 0.0, &effect(aid, hdesc, phurt, enemy, dt, phit, dam, hid));
        }
    }
    
    return 0;
}

/*
 * Function name: convert_weapon_imbues
 * Description:   Handle offensive weapon imbues
 */
private void 
convert_weapon_imbues()
{
    foreach(object weapon : get_player()->query_weapon(-1))
    {
        if (!weapon->has_imbue_shadow()) continue;

        foreach(object imbue : imbue_shadows(weapon))
        {
            string imbue_init = function_exists("init_imbue_shadow", imbue);

            if (function_exists("race_damage", imbue)) 
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found bane imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &bane_imbue_effect(imbue) });
            } 
            else if (function_exists("elemental_strike", imbue)) 
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found damage imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &damage_imbue_effect(imbue) });
            }
            else if (imbue_init == SHADOW_DIR + "effect_poison_shadow")
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found poison imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &poison_imbue_effect(imbue) });
            }
            else if (imbue_init == SHADOW_DIR + "effect_slow_shadow")
            {
                send_debug_message("convert_weapon_imbues",
                            sprintf("Found slow imbue %O on %s\n", imbue, 
                                weapon->short()));
                did_hit_imbue_effects += ({ &slow_imbue_effect(imbue) });
            }
            else handle_imbue(imbue);
        }
    }
}

// Armour imbue handling

/*
 * Function name: cr_got_hit
 * Description:   Called from the combat object when we get hit, we use this
 *                to similate the got_hit function on arour that triggers
 *                imbues.
 * Arguments:     hid:   The hitloc id
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage in hitpoints
 */
public varargs void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    if (ph == 0) return;

    object *effects = hitloc_damage_effects[hid];
    if (!pointerp(effects) || !sizeof(effects)) return;

    foreach(object effect : effects) 
    {
        // TODO: Handle imbue on hit
        send_debug_message("shapeshift_armour_imbue",
            sprintf("TODO trigger armour imbue on %O\n", effect));
        effect->check_race(this_object(), att, hid, &bane_strike_message(effect), 1);
    }
}

/*
 * Function name: convert_armour_imbues
 * Description:   Maps imbues on armours to hit locations on the bear
 *                and triggers handling of non bane imbues
 */
private void 
convert_armour_imbues()
{
    object *other_imbues = ({ });
    foreach(int hid : ({ A_BODY, A_L_ARM, A_R_ARM, A_LEGS, A_HEAD })) 
    {
        int bear_hid = player_hid_to_bear_hid[hid];
        mixed *hitloc = get_player()->query_combat_object()->query_hitloc(hid);
        if (!pointerp(hitloc[4])) continue;

        foreach(object armour : hitloc[4]) 
        {
            if (!armour->has_imbue_shadow()) continue;

            foreach(object imbue : imbue_shadows(armour)) 
            {
                // Bane imbues also trigger when an armour gets hit
                if (function_exists("race_damage", imbue)) 
                {
                    send_debug_message("convert_armour_imbues",
                        sprintf("Found bane imbue %O on %s (from %s)\n", imbue, 
                            hitloc[2], armour->short()));

                    hitloc_damage_effects[bear_hid] += ({ imbue });
                } 
                else 
                {
                    if (member_array(imbue, other_imbues) == -1) 
                    {
                        other_imbues += ({ imbue });
                    }
                }
            }
        }
    } 

    map(other_imbues, handle_imbue);
}