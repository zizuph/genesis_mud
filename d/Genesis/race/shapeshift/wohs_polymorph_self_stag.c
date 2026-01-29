/*
 *  Stag shapeshift creature for WoHS polymorph self spell
 *
 *  Strength and dex bonuses; dps shapeshift option  
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

#define A_ANTLERS  0                /* method of attack */
#define A_LHOOF 1
#define A_RHOOF 2

#define H_HEAD      0
#define H_BODY      1
#define H_LEFT_LEG  2
#define H_RIGHT_LEG 3
#define H_HIND      4

#define NO_INTRO_OBJ  "/d/Genesis/race/shapeshift/wohs_polymorph_self_no_intro_obj.c"

mapping player_hid_to_bear_hid = ([
        A_BODY  : H_BODY,
        A_L_ARM : H_LEFT_LEG,
        A_R_ARM : H_RIGHT_LEG,
        A_LEGS  : H_HIND,
        A_HEAD  : H_HEAD
    ]);

mapping hitloc_damage_effects = ([ H_BODY : ({ }),
                                   H_LEFT_LEG : ({ }),
                                   H_RIGHT_LEG : ({ }),
                                   H_HIND : ({ }),
                                   H_HEAD : ({ }) ]);

function *did_hit_imbue_effects = ({ });

// Prototypes
private void convert_armour_imbues();
private void convert_weapon_imbues();

string  *adj_list1 = ({"giant", "gargantuan", "towering", "enormous", "gigantic" }); 
string  *adj_list2;
string  adj1, adj2;

int player_wis, player_int;

void
create_shapeshift_creature()
{
    set_name("stag"); 
    set_race_name("deer");

    if (!IS_CLONE)
        return;

    set_gender(G_MALE);

    // refresh_living doesn't work
    // refresh_living();

    add_prop(CONT_I_WEIGHT, 680000); /* weight = 680 kilograms */
    add_prop(CONT_I_HEIGHT, 2100); /* height = 2.1 metres */
    add_prop(CONT_I_VOLUME, 680000); /* volume = 680 liters */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_MOUTH_BLOCKED, "While polymorphed in to this form you are " +
                  "unable to vocalise as you did in humanoid form!\n");
    add_prop(LIVE_M_NO_ACCEPT_GIVE, "This creature is not physically capable of accepting " +
                  "gifts from you!\n");

    set_m_in("trots in");  
    set_m_out("trots");

    // Whimpy is reset to brave, so setting a default of 20% here
    set_whimpy(20);

    set_shapeshift_duration(2400);

    clone_object(NO_INTRO_OBJ)->move(TO,1);
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

    tell_room(env, QCTNAME(player) + " arches "  +HIS(player)+ " back as a great rack of "+
         "horns branch out from " + HIS(player)+ " raised head, and " +HE(player)+ 
         " expands into the form of "+ LANG_ADDART(this_object()->query_nonmet_name()) + ".\n",
        ({ this_object(), player }));
    player->catch_tell("You arch your back as a great rack of horns branches out from your head " +
         "and your body expands into the form of "+ LANG_ADDART(this_object()->query_nonmet_name()) + ".\n");
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
    return "You have taken the form of " +LANG_ADDART(query_short())+
       ". Seven feet tall to the shoulder and almost 700 kilograms in weight, " +
       "you would give even the mightiest of predators reason to pause. " +
       "Great branching antlers expand from your head - formidably sharp and deadly";
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
    this_object()->catch_tell("You feel your form suddenly begin to " +
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

    player_int = player->query_stat(SS_INT);
    player_wis = player->query_stat(SS_WIS);


    /*                   DESCRIPTIONS                          */
    string robe = WOHS_MANAGER->query_wohs_order_colour(player);
  
    if(robe == "red")
       adj_list2 = ({"red", "red-brown", "russet", "chestnut"});
    else if(robe == "black")
       adj_list2 = ({"grey", "black", "sable", "brunet"});
    else
       adj_list2 = ({"white", "ivory", "white", "silvery-white"});

    adj1 = adj_list1[random(sizeof(adj_list1))];
    adj2 = adj_list2[random(sizeof(adj_list2))];

    set_short(adj2 + " " + adj1 + " stag");
    set_adj(({ adj1, adj2 }));

    set_long("Before you stands "+LANG_ADDART(adj1)+" stag of no ordinary proportions. Seven feet " +
      "tall to the shoulder and almost 700 kilograms in weight, this noble beast would give even " +
      "the mightiest of predators reason to pause. Great branching antlers expand from its head - "+
      "formidably sharp and deadly. It stares at you with intelligent eyes that you " +
       "find a little unsettling.\n");

    /*                   FORMULA FOR STATS                          */

    int stat_str, stat_dex, stat_con, stat_dis;

    // strength +20% of casters int to a max of 250
    stat_str = min(250, (player_int * 12) / 10);

    // dex +20% of casters wis to a max of 300
    stat_dex = min(250, (player_wis * 12) / 10);

    // con casters int to a max of 250
    stat_con = min(250, player_int);

    // dis casters wis to a max of 200
    stat_dis = min(200, player_wis);

    set_stats(({ stat_str, stat_dex, stat_con, 100, 100, stat_dis }));
    set_hp(10000);
    set_mana(10000);
    set_fatigue(1000);

    /*                   FORMULA FOR SKILLS                          */

    // Cooshee skills are between 60 and 100, based on player transmutation skill
    int poly_skill = player->query_skill(SS_FORM_TRANSMUTATION);

    set_skill(SS_DEFENCE, poly_skill);
    set_skill(SS_UNARM_COMBAT, poly_skill);

    /*                   FORMULA FOR NATURAL WEAPONS AND AC           */

    // to_hit between 30 and 50 depending on transmutation skill
    int poly_hit = player->query_skill(SS_FORM_TRANSMUTATION) / 2;

    // pen between 30 and 50 depending on transmutation skill
    // antlers have +10 pen
    int poly_pen = player->query_skill(SS_FORM_TRANSMUTATION) / 2;

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_ANTLERS,  poly_hit, (poly_pen + 10), W_IMPALE, 60, "great antlers");
    set_attack_unarmed(A_LHOOF, poly_hit, poly_pen, W_SLASH,  20, "left forehoof");
    set_attack_unarmed(A_RHOOF, poly_hit, poly_pen, W_SLASH,  20, "right forehoof");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */

    // ac between 36 and 60 depending on transmutation skill
    int poly_ac = (player->query_skill(SS_FORM_TRANSMUTATION) * 6) / 10;

    set_hitloc_unarmed(H_HEAD, ({ poly_ac, poly_ac, poly_ac, 0 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({ poly_ac, poly_ac, poly_ac, 0 }), 60, "body");
    set_hitloc_unarmed(H_LEFT_LEG, ({ poly_ac, poly_ac, poly_ac, 0 }), 10, "left foreleg");
    set_hitloc_unarmed(H_RIGHT_LEG, ({ poly_ac, poly_ac, poly_ac, 0 }), 10, "right foreleg");
    set_hitloc_unarmed(H_HIND, ({ poly_ac, poly_ac, poly_ac, 0 }), 10, "hindquarters");


    /*                        OTHER FUNCTIONS                         */

    convert_weapon_imbues();
    convert_armour_imbues();

    add_cmdsoul(ABILITY_DIR + "guilds/souls/spell_manager_soul");
    update_hooks();
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