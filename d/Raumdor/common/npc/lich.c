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

// TODO: Spells change attack targets

#pragma strict_types

#include "defs.h"

inherit STD_UNDEAD;
inherit LIB_DIR + "paralyze";
inherit LIB_DIR + "reanimate";
inherit LIB_DIR + "follow";

// Can we get rid of this?
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

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
#define ILLUSION_MANA_COST 50

// Prototypes

void do_tactics();
void update_long();


// Globals
int is_illusion = 0;
int damage_array_limiter = 0;
int *damage_history = ({});

object *active_enemies = ({});
object *copies = allocate(COPIES);
object original;
string eye_colour = one_of_list(EYE_COLOURS);
string adj = one_of_list(ADJ);

void
create_monster()
{
    object damMod = clone_object("/d/Genesis/specials/std/dam_mod_obj_base");

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
    add_prop(LIVE_I_NO_CORPSE, 1);

    add_prop(OBJ_I_RES_COLD, 60);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_POISON, 80);

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
    add_cact("say I will enjoy tormenting your soul.");
    add_cact("emote 's " + TO->query_eye_colour() +" eyes flare brightly " +
        "for a moment as it focuses its gaze on you.");
    add_cact("@@seen_emote stares at you with its " + TO->query_eye_colour() +
        " eyes, piercing your flesh and freezing you to the bone.");

    equip(({
        COMMON_ARM_DIR + "threadbare_robe",
        COMMON_OBJ_DIR + "tattered_book",
        COMMON_ARM_DIR + "lich_phylactery"
    }));

    seteuid(getuid());

    add_cmdsoul(COMMON_SOUL_DIR + "lich_soul");
    clone_object(MANA_SHADOW)->shadow_me(TO);
    update_hooks();

    damMod->move(TO, 1);
    damMod->set_dam_mod_combat_aid(50);
    damMod->start();
}

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

void
set_is_illusion(int value, mixed other)
{
    is_illusion = value;
    if (value)
        original = other;
    else
        copies = other;
}

int
query_is_illusion()
{
    return is_illusion;
}

object *
query_illusions_remaining()
{
    object *result = ({});
    foreach (object copy: copies)
    {
        if (copy)
            result += ({copy});
    }

    if (sizeof(result))
       return result; 
    return 0;
}

void
set_eye_colour(string colour)
{
    eye_colour = colour;
}

string
query_eye_colour()
{
    return eye_colour;
}

void
update_adj(string value)
{
    remove_adj(adj);
    adj = value;
    add_adj(adj);
    set_short("looming " + adj + " lich");
}

// Calculate who has been doing the most damage recently
object
query_biggest_threat()
{
    int highestDamage = -1,
        *new_history = ({}),
        time_limit = time() - 30; // 30 seconds
    mapping attackers = ([]);
    object ob,
           most_threatening = query_attack();

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


// Summon the illusions
void
summon_copies()
{
    int i, stat;
    object real, enemy;
    string colour, *remaining_colours = EYE_COLOURS - ({eye_colour});
    enemy = query_attack();

    command("emote closes its eyes and begins to vibrate and shimmer as " +
        "it becomes blurry. A blinding flash of light forces you to close " +
        "your eyes. When you open them again, you are surrounded by " +
        LANG_NUM2WORD(COPIES) + " more liches!");

    for (i = 0; i < COPIES; i++)
    {
        copies[i] = clone_object(MASTER);
        colour = one_of_list(remaining_colours);
        copies[i]->set_eye_colour(colour);
        remaining_colours -= ({colour});
        copies[i]->update_long();
        copies[i]->update_adj(adj);
        for (stat = 0; stat < 6; stat++)
        {
            copies[i]->set_base_stat(stat, query_base_stat(stat));
        }
        copies[i]->set_hp(query_hp());
    }

    copies->move_living("M", E(TO));
    foreach(object copy: copies)
        TO->team_join(copy);

    if (enemy)
        copies->command("kill " + OB_NAME(enemy));

    // Randomly determine which one is real, which may be the original
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
    copies->set_is_illusion(1, real);

    // This doesn't seem to be used, but its in the docs so we set it
    copies->add_prop(MAGIC_I_ILLUSION, 80);

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

int
sort_hp_ascending(object a, object b)
{
    return a->query_hp() - b->query_hp();
}

object *
query_enemies_nearest_death()
{
    active_enemies = active_enemies - FILTER_NOT_SEE(INV(E(TO)), TO) - ({0});
    foreach (object enemy:
      FILTER_UNDEAD_ENEMIES(FILTER_CAN_SEE(LIVE_OTHER(E(TO), TO), TO)))
        active_enemies |= ({enemy});
    
    active_enemies = sort_array(active_enemies, sort_hp_ascending);

    return active_enemies;
}

object
query_enemy_nearest_death()
{
    object *list = query_enemies_nearest_death();

    if (sizeof(list))
        return list[0];
    return 0;
}

int
special_attack(object enemy)
{
    object biggest_threat;

    do_tactics();
    
    if (!query_is_illusion())
    {
        if (query_mana() >= ILLUSION_MANA_COST &&
          query_hp() <= (query_max_hp() / 2) && !query_illusions_remaining())
        {
            add_mana(-ILLUSION_MANA_COST);
            summon_copies();
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
                    "see " + HIS(biggest_threat) + " body go " +
                    "rigid.\n" + QCTNAME(biggest_threat) + " is " +
                    "paralyzed!\n", biggest_threat, ({TO}));
                TO->catch_msg("You paralyze " + QTNAME(biggest_threat) + "!\n");
                paralyze(biggest_threat, 20);
                return 1;
            }
        }
    }
    command("cast " + CAST[random(sizeof(CAST))]);
    return 1; 
}

// Heal the illusions whenever the real lich is healed
void
heal_copies(int hp)
{
    if (hp > 0)
    {
        foreach(object copy : copies)
        {
            if (copy)
                copy->heal_hp(hp);
        }
    }
}

// We track incoming damage
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

// When the leader dies, this is called in the original lich
void
set_new_leader(object old)
{
    object *candidates = (query_illusions_remaining() - ({old}) + ({TO})),
           leader = one_of_list(candidates),
           *team = old->query_team();

    foreach (object member: team)
        old->team_leave(member);

    team -= ({leader}); 

    foreach (object member: team)
        leader->team_join(member);
}

void
do_die(object killer)
{
    int removed = 0;
    if(TO->query_is_illusion())
    {
        if (query_team())
            original->set_new_leader(TO);
        TELL_CAN_SEE(E(TO), "In apparent defeat, the lich evaporates!\n");
        remove_object();
        return;
    }

    command("emote moans: Thisss isss not the ennnnd. I will returrrrrrn.");
    command("emote 's eyes flash and thin trails of " + eye_colour +
        " smoke coil out of its skull.");
    command("emote collapses to the ground, crumbling to dust.");

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
        TELL_CAN_SEE(E(TO), "The " + LANG_NUM2WORD(removed) +
            " remaining " + (removed == 1 ? "lich" : "liches") +
            " suddenly " +
            (removed == 1 ? "disappears!\n" : "disappear!\n"));
    }

    ::do_die(killer);
}

// Callback when follow fails
void
follow_failed(object target)
{
    active_enemies -= ({target});
    do_tactics();
}

// Determine who we attack/chase
void
do_tactics()
{
    object current, target;

    if (query_leader() || !(target = query_enemy_nearest_death()))
        return;

    if (E(target) == E(TO))
    {
        if ((current = query_attack()) != target)
        {
            if (current)
            {
                command("say Thiss one! It will join uss quickly.");
                target->catch_msg(QCTNAME(TO) + " hisses at you.\n");
                TO->tell_watcher(QCTNAME(TO) + " hisses at " +
                        QTNAME(target) + ".\n", target);
            }

            command("kill " + OB_NAME(target));
                
            foreach(object member:query_team())
            {
                member->command("kill " + OB_NAME(target));
            }
        }
    }
//    else if (query_following() != target && E(target)->query_shadows_forest())
    else if (query_following() != target)
        seen_emote("tilts its head sideways, then looks into the distance.");
    
    if (query_following() != target)
        follow(target, 2.0, follow_failed);
}

void
notify_enemy_leaves(object enemy)
{
    do_tactics();
}

void
control_reanimation(object reanimation)
{
    command("emote gestures assertively toward the " + 
            reanimation->query_short() + ".");
    reanimation->command("$assist");
    reanimation->set_aggressive(1);
}

void
reanimation_located(object reanimation, int result)
{
    if (result)
        control_reanimation(reanimation);
    else
        reanimation->set_aggressive(1);
}

void
activate_reanimation(object reanimation)
{
    object leader = query_leader(),
           target = query_attack();

    //TODO: Remove this is everything else is working.
    if (leader)
        leader->team_join(reanimation);
    else
        TO->team_join(reanimation);

    if (E(reanimation) != E(TO))
        reanimation->locate(TO, &reanimation_located(reanimation));
    else
        control_reanimation(reanimation);
}

void
do_reanimate(object who)
{
    object reanimation;

    if (who->query_prop(LIVE_I_NO_CORPSE)
            || who->query_prop(LIVE_I_UNDEAD)
            || E(who) != E(TO))
        return;

    command("emote 's " + eye_colour + " eyes flash brightly as it eagerly " +
        "leans toward the fresh corpse, arms outstretched.");
    command("emote moans: Your ssssssoul isss miiiiiiinnnnne.");
    command("emote begins chanting and tracing runes in the air toward " +
        "the dead body.");
    TELL_CAN_SEE(E(who), "The corpse of " + QTNAME(who) +
        " immediately begins to stir...\n");
    reanimation = FIX_TP(&reanimate_living(who));
    reanimation->set_aggressive(0);
    reanimation->move(E(TO), 1);

    set_alarm(1.5, 0.0, &reanimation->command("emote clambers to its feet!"));
    set_alarm(3.0, 0.0,
            &reanimation->command("emote tilts its head haltingly."));
    set_alarm(4.0, 0.0, &activate_reanimation(reanimation));
    set_alarm(4.1, 0.0, do_tactics);
}

void
notify_you_killed_me(object who)
{
    object leader = query_leader();

    if (leader)
    {
        leader->notify_you_killed_me(who);
        return;
    }

    do_reanimate(who);
}

void
aggressive_attack(object target)
{
    do_tactics();
    ::aggressive_attack(target);
}

void
kill_copies()
{
    if (query_is_illusion())
    {
        original->kill_copies();
        return;
    }
    foreach (object copy: copies)
    {
        copy->set_hp(0);
        copy->do_die(this_player());
    }
}
