/*
 * This is an NPC lich that will be included as a boss in Raumdor. It is a
 * spellcaster who does not use any physical attacks. He has 5 damaging spells,
 * one of which includes a damage-over-time component (poison/plague). It also
 * can use the paralyze status found in the Raumdor forest and has a special
 * ability to create copies of itself. These copies are identical to the
 * original except for their eyes. Players have a chance to resist the illusion
 * which allows the player(s) to see the eye colour of the real lich. The
 * copies do not deal damage, apply the poison/plague, paralyze, or create
 * additional copies.
 *
 * The means of its arrival are still to be determined in collaboration with
 * Liege Malus.
 *
 * Updated 2018.04.08 (Shanoga)
 */

#pragma strict_types

#include "defs.h"

inherit STD_UNDEAD;
inherit LIB_DIR + "paralyze";
inherit LIB_DIR + "reanimate";
inherit LIB_DIR + "follow";



#undef  DOMAIN_DIR
#undef  COMMON_DIR
#define DOMAIN_DIR      "/d/Raumdor/development/shanoga/"
#define COMMON_DIR      DOMAIN_DIR + "common/"







// Can we get rid of this?
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

// TODO: Determine file location for these files
#define SPELLS  "/d/Raumdor/development/shanoga/common/npc/spells/"
#define SOUL    "/d/Raumdor/development/shanoga/common/npc/soul/lich_spell_soul"
        
#define EYE_COLOURS ({ \
    "dull amber", \
    "dull crimson", \
    "faint scarlet", \
    "crystal blue", \
    "pale green", \
})

#define ADJ ({ \
    "pestilent", \
    "deadly", \
    "necrotized", \
    "malignant", \
})

#define CAST ({ \
    "life_drain", \
    "magic_missile", \
    "ice_storm", \
    "plague_swarm", \
    "frost_ray", \
})

#define COPIES 4

int is_illusion = 0;
int damage_array_limiter = 0;
int *damage_history = ({});

object *copies = allocate(COPIES);
object *reanimations;
string eye_colour = one_of_list(EYE_COLOURS);
string adj = one_of_list(ADJ);

void create_copies();
void set_eye_colour(string colour);
void set_is_illusion(int value, object *illusions = ({}));
void update_long();
void update_adj(string value);

/*
 * Function name: create_monster
 * Description  : The masked create routine
 */
void
create_monster()
{
    ::create_monster();
    set_race_name("lich");
    set_gender(G_NEUTER);
    set_adj(({"looming", adj}));
    set_short("looming " + adj + " lich");
    update_long();
    set_stats(({135, 135, 135, 180, 180, 200}), 5);
    set_alignment(-1000);
    set_aggressive(1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);

    set_cact_time(5);
    add_cact("say I will enjoy devouring your soul.");
    add_cact("emote 's " + TO->query_eye_colour() +" eyes flare brightly " +
        "for a moment as it focuses its gaze on you.");
    add_cact("emote stares at you with its " + TO->query_eye_colour() +
        " eyes, piercing your flesh and freezing you to the bone.");

    // TODO: Add this level of resistance magically. Stoneskin?
    /* Not sure what's going on here
    set_hitloc_unarmed(4,30,15,"head");
    set_hitloc_unarmed(32,30,10,"left arm");
    set_hitloc_unarmed(16,30,10,"right arm");
    set_hitloc_unarmed(2097154,35,45,"body");
    set_hitloc_unarmed(8,30,20,"legs");
    */
    equip(({
        COMMON_ARM_DIR + "threadbare_robe",
        COMMON_OBJ_DIR + "tattered_book",
        COMMON_ARM_DIR + "lich_phylactery"
    }));

    seteuid(getuid());
    add_cmdsoul(SOUL);
    clone_object(MANA_SHADOW)->shadow_me(TO);
    update_hooks();
}

/*
* Function name: set_is_illusion
* Description  : Sets the illusion status of the NPC. This is needed when
*              : objects are copied in the create_copies function. Illusions
*              : do no damage and provide no experience.
* Arguments    : int value - 0 or 1 to set illusion status
*              : object *illusions - optional, array of objects to set
*/
void
set_is_illusion(int value, object *illusions = ({}))
{
    is_illusion = value;
    if (!value)
    {
        copies = illusions;
    }
}

/*
* Function name: query_is_illusion
* Description  : Checks the illusion status of the NPC. This is needed when
*              : casting spells and upon death of the NPC. Illusions
*              : do no damage and provide no experience.
* Returns      : int value - 0 or 1 to indicate illusion status
*/
int
query_is_illusion()
{
    return is_illusion;
}

/*
* Function name: query_illusions_remaining
* Description  : Checks the copies array to see if there are any illusions
*              : in the room. This is used to determine if the NPC can create
*              : more illusions or not.
* Returns      : int value - 0 or 1 to indicate illusion status
*/
int
query_illusions_remaining()
{
    foreach(object copy : copies)
    {
        if (copy)
        {
            return 1;
        }
    }
    return 0;
}

/*
* Function name: set_eye_colour
* Description  : Sets the eye colour of the NPC. This is needed because
*              : the illusions initially have the same eye colour as
*              : the real NPC and should be different so players can
*              : determine the difference between the real NPC and illusions.
* Arguments    : string colour - The colour used for NPC eyes.
*/
void
set_eye_colour(string colour)
{
    eye_colour = colour;
}

/*
* Function name: query_eye_colour
* Description  : Checks the eye colour of the NPC. This is needed after
*              : the create_copies function to determine the original NPC
*              : eye colour and determine how to set the copy eye colours.
* Returns      : string eye_colour - The eye colour of the NPC
*/
string
query_eye_colour()
{
    return eye_colour;
}

/*
* Function name: update_adj
* Description  : Updates the description of the copied NPCs so that
*              : they have the same adjective as the original NPC rather
*              : than a randomly determined adjective and short description.
* Arguments    : string value - The adjective of the original NPC.
*/
void
update_adj(string value)
{
    remove_adj(adj);
    adj = value;
    add_adj(adj);
    set_short("looming " + adj + " lich");
}

/*
* Function name: update_long
* Description  : Updates the long description of the NPCs so they are
*              : the same but take account for the eye colour as set by
*              : the set_eye_colour function.
*/
void
update_long()
{
    set_long("This decrepit corpse is hardly a shell of what was once a " +
        "great wizard. The rags draped over its shoulders reveal flesh and " +
        "bones that must be centuries old. The shredded robes have faded " +
        "to grey, losing any semblance of their original colour. The empty " +
        "sockets where the eyes once were located are now smoldering with " +
        "a " + eye_colour + " glow.\n");
}

/*
* Function name: query_biggest_threat
* Description  : This function uses the damage_history array to determine
*              : which target has done the most damage to it over the prior
*              : 30 seconds. This is called to determine the target of the
*              : paralyze spell.
* Returns      : object most_threatening - the enemy object that has one the
*              : most damage in the last 30 seconds
*/
object
query_biggest_threat()
{
    int *new_history = ({});
    int time_limit = time() - 30; // 30 seconds
    mapping attackers = ([]);
    int highestDamage = -1;
    object ob;
    object most_threatening = query_attack();
    foreach(int *entry: damage_history)
    {
        if (entry[0] < time_limit)
            continue;
        new_history += ({ entry });
        attackers[entry[1]] += entry[2];
    }
    damage_history = new_history;
    damage_array_limiter = 0;
    foreach(int attacker, int damage : attackers)
    {
        ob = present("ob_" + sprintf("%d", attacker),
            environment(this_object()));
        if (ob && damage > highestDamage)
        {
            most_threatening = ob;
            highestDamage = damage;
        }
    }

    return most_threatening;
}

/*
* Function name: query_weakest_link
* Description  : This function determines which enemy has the lowest hp or CON
*              : and targets that living so he can create a larger undead army.
* Returns      : object weakest_link - the enemy object that has one the
*              : most damage in the last 30 seconds
*/
object
query_weakest_link()
{
    int hp, lowestHP;
    object *all_enemies = query_enemy(-1);
    object weakest_link = query_attack();

    lowestHP = weakest_link->query_hp();
    foreach(object link : all_enemies - ({weakest_link}))
    {
        if (present(link, E(TO)))
        {
            hp = link->query_hp();
            if (hp < lowestHP)
            {
                weakest_link = link;
                lowestHP = link->query_hp();
            }
        }
    }

    return weakest_link;
}

/*
 * Function name: special_attack
 * Description  : This is called by the combat file. Using random selections
 *              : this function determines whether the illusion spell is used,
 *              : the palyer is paralyzed, or a damaging spell is cast. The
 *              : illusion spell is cast if the NPC is not an illusion, no
 *              : copies have been created yet, and the NPC is at or below half
 *              : of its maximum health.
 * Arguments    : object enemy - The enemy of the NPC as set in the combat file
 * Returns      : int 1 - tells the combat file that a special was cast
 */
int
special_attack(object enemy)
{
    object biggest_threat;
    object new_target = query_weakest_link();
    if (query_attack() != new_target)
    {
        if (sizeof(query_team()))
        {
            new_target->catch_msg(QCTNAME(TO) + " senses weakness in you " +
                "and shifts the focus of its deadly energy to you, " +
                "commanding its minions to do the same.\n");
            TO->tell_watcher(QCTNAME(TO) + " senses weakness in " +
                QTNAME(new_target) + " and shifts the focus of its deadly " +
                "energy to " + new_target->query_objective() + ", " +
                "commanding its minions to do the same.\n", new_target,
                ({ TO, new_target }));
            command("kill " + OB_NAME(new_target));
            
            foreach(object member:query_team())
            {
                member->command("assist");
            }
        }
        else
        {
            new_target->catch_msg(QCTNAME(TO) + " senses weakness in you and " +
                "shifts the focus of its deadly energy.\n");
            TO->tell_watcher(QCTNAME(TO) + " senses weakness in " +
                QTNAME(new_target) + " and shifts the focus of its deadly " +
                "energy.\n", new_target, ({ TO, new_target }));
            command("kill " + OB_NAME(new_target));
        }
        
    }
    
    if (!query_is_illusion())
    {
        if (query_hp() <= (query_max_hp() / 2) && !query_illusions_remaining())
        {
            create_copies();
            return 1;
        }

        if (!random(10))
        {
            biggest_threat = query_biggest_threat();
            if (!is_paralyzed(biggest_threat))
            {
                biggest_threat->catch_msg(QCTNAME(TO) + " reaches its " +
                    "crooked fingers toward you and you feel every muscle " +
                    "go rigid at its touch.\nYou are paralyzed!\n");
                tell_watcher(QCTNAME(TO) + " reaches its crooked " +
                    "fingers toward " + QTNAME(biggest_threat) + " and you " +
                    "see " + biggest_threat->query_possessive() + " body go " +
                    "rigid.\n" + QCTNAME(biggest_threat) + " is " +
                    "paralyzed!\n", biggest_threat, ({ }));
                paralyze(biggest_threat, 20);
                return 1;
            }
        }
    }
    command("cast " + CAST[random(sizeof(CAST))]);
    return 1; 
}

/*
* Function name: create_copies
* Description  : This function is an illusion spell that the NPC can cast.
*              : The spell is triggered if the NPC is not an illusion, is at
*              : or below 50% health and if there are no current copies.
*              : The copy eye colours are each set to be different from each
*              : other and the adjectives and the short descriptions are set
*              : to be identical so the players cannot determine the illusions
*              : from the real NPC at a glance. The players are able to
*              : resist the spell and see the true eye colour, then they must
*              : examine the NPCs to determine which one to focus on.
*              : The real NPC is not determined until all copies are created
*              : so there is a randomness to the position of the real one
*              : within the list, otherwise it would always be the fifth NPC.
* Arguments    : object enemy - The enemy of the NPC as set in the combat file
* Returns      : int 1 - tells the combat file that a special was cast
*/
void
create_copies()
{
    int copy, i, stat;
    object real, enemy;
    string *remaining_colours = EYE_COLOURS - ({eye_colour});
    enemy = query_attack();

    command("emote closes its eyes and begins to vibrate and shimmer as " +
        "it becomes blurry. A blinding flash of light forces you to close " +
        "your eyes. When you open them again, you are surrounded by " +
        LANG_NUM2WORD(COPIES) + " more liches!");

    for (copy = 0; copy < COPIES; copy++)
    {
        copies[copy] = clone_object(MASTER + ".c");
        i = random(sizeof(remaining_colours));
        copies[copy]->set_eye_colour(remaining_colours[i]);
        remaining_colours = remaining_colours - ({remaining_colours[i]});
        copies[copy]->update_long();
        copies[copy]->update_adj(adj);
        for (stat = 0; stat < 6; stat++)
        {
            copies[copy]->set_base_stat(stat, query_base_stat(stat));
        }
        copies[copy]->set_hp(query_hp());
        //team_join(copies[copy]);
    }

    
    copies->move_living("M", E(TO));
 
    //TODO: Shouldn't they join his team?
    // I think this would work in the above for block?
    // copies[copy]->team_join(TO);

    if (enemy)
    {
        copies->command("kill " + OB_NAME(enemy));
    }

    i = random(COPIES + 1);
    if (i < COPIES)
    {
        real = copies[i];
        copies[i] = TO;
    }
    else
    {
        real = TO;
    }

    real->set_is_illusion(0, copies);
    copies->set_is_illusion(1);
    
    
    foreach(object illus: copies)
    {
        real->team_join(illus);
    }
    

    foreach (object player: FILTER_IS_SEEN(TO,
                FILTER_CAN_SEE_IN_ROOM(FILTER_PLAYERS(AINV(E(TO))))))
    {
        if (player->resolve_task(TASK_DIFFICULT,
                ({SKILL_AVG, SS_FORM_ILLUSION, SS_SPELLCRAFT, TS_INT, TS_WIS,
                 SKILL_END, SKILL_AVG, SS_FORM_ILLUSION, SS_SPELLCRAFT,
                 TS_INT, TS_WIS, SKILL_END})) > 0)
        {
            player->catch_msg("Keeping your wits about you, you study " +
                "the liches and notice the " + real->query_eye_colour() +
                " glow of one lich's eyes pulse slightly. That must be its " +
                "true embodiment!\n");
        }
    }
}

/*
 * Function name: command_reanimation
 * Description  : This is called to add some emotes for the lich when the
 *                reanimated zombie rises and begins the zombie's actions.
 * Arguments    : object reanimation - the reanimated zombie
 */
void
command_reanimation(object reanimation)
{
    object target = query_attack();
    command("emote gestures assertively toward the " + 
            reanimation->query_short() + ".");
    TO->team_join(reanimation);
    reanimation->command("$assist");
    reanimation->set_aggressive(1);
}

/*
* Function name: notify_you_killed_me
* Description  : The description the player sees upon dying to the NPC.
* Arguments    : object who - the NPC that is dying
*/
void
notify_you_killed_me(object who)
{
    object reanimation;

    if (who->query_prop(LIVE_I_NO_CORPSE)
            || who->query_prop(LIVE_I_UNDEAD))
        return;
    command("emote 's " + eye_colour + " eyes flash brightly as it eagerly " +
        "leans toward the fresh corpse, arms outstretched.");
    command("emote moans: Your ssssssoul isss miiiiiiinnnnne.");
    command("emote begins chanting and tracing runes in the air toward " +
        "the dead body.");
    TELL_CAN_SEE(who, "The corpse of " + QTNAME(who) +
        " immediately begins to stir...\n");
    reanimation = reanimate_living(who);
    reanimation->move(E(TO), 1);
    
    set_alarm(1.5, 0.0, &reanimation->command("emote clambers to its feet!"));
    set_alarm(3.0, 0.0,
            &reanimation->command("emote tilts its head haltingly."));
    set_alarm(4.0, 0.0, &command_reanimation(reanimation));
}

/*
* Function name: heal_copies
* Description  : This function is a modification of the heal_hp() function
*              : located at /std/living/savevars.c
*              : This is called whenever the life_drain spell is cast so the
*              : copies are healed in addition to the main NPC being healed.
* Arguments    : int hp - The amount of hp to be healed
*/
void
heal_copies(int hp)
{
    if (hp > 0)
    {
        foreach(object copy : copies)
        {
            if (copy)
            {
                copy->heal_hp(hp);
            }
        }
    }
}

/*
* Function name: hit_me
* Description  : This is a masked version of hit_me to track the damage
*              : done to the NPC and store it into a damage_history array
*              : that is used to determine the paralyze target.
* Arguments    : see /std/living/combat.c   line:646
* Returns      : see /std/living/combat.c   line:646
*/
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id,
    int target_hitloc = -1)
{
    int attackerNum;
    damage_array_limiter += damage_array_limiter;
    if (damage_array_limiter > 1000)
    {
        query_biggest_threat();
        damage_array_limiter = 0;
    }
    mixed *hres = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
    if (hres[3] > 0)
    {
        sscanf(OB_NUM(attacker), "%d", attackerNum);
        damage_history += ({({time(), attackerNum, hres[3]})});
    }
    return hres;
}

/*
 * Function name: notify_enemy_leaves
 * Description  : This routine is called when an enemy leaves the room. It
 *                is used here so the lich can hunt enemies that leave in the
 *                middle of combat. There is a delay so the lich doesn't
 *                follow too quickly.
 * Arguments    : object enemy - the enemy who left us
 */
void
notify_enemy_leaves(object enemy)
{
    //TODO: Test this a bit more with an updated follow code?
    set_alarm(1.0, 0.0, &follow_target(query_weakest_link(),1.0));
}

/*
* Function name: do_die
* Description  : This function sets the xp gained to 0 for illusions and sets
*              : the descriptions when an illusion or real NPC dies. If the
*              : real NPC is killed, the illusions are removed as well.
* Arguments    : object who - the NPC that is dying
*/
void
do_die(object killer)
{
    int removed = 0;
    int charges;
    if(TO->query_is_illusion())
    {
        TELL_CAN_SEE(TO, "In apparent defeat, the lich evaporates!\n");
        remove_object();
        return;
    }

    command("emote moans: Thisss isss not the ennnnd. I will returrrrrrn.");
    command("emote 's eyes flash and thin trails of " + eye_colour +
        " smoke snake out of its skull as it tumbles to the ground.");

    foreach(object copy: copies)
    {
        if (copy)
        {
            copy->remove_object();
            removed += 1;
        }
    }
    
    if (removed)
    {
        TELL_CAN_SEE(TO, "The " + LANG_NUM2WORD(removed) +
            " remaining " + (removed == 1 ? "lich" : "liches") +
            " suddenly " +
            (removed == 1 ? "disappears!" : "disappear!\n"));
    }

    ::do_die(killer);
}
