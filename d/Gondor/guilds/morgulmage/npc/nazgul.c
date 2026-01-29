#include "../morgulmage.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

inherit "/std/monster";
inherit "/d/Gondor/morgul/feeling";

object target_room;
object target_player;
object *original_enemies;
object steed;

mapping stopped_targets = ([ ]);
mapping stopped_enemies = ([ ]);
mixed original_room_m_no_attack;

int potential_target(object target, int no_feelings);

int sulambar = 0;
int casting = 0;
int preparing_special = 0;
int hostile = 0;
int departure_alarm = -1;
int target_check = -1;
object mace;
object *shield_attack_victims = ({ });

#define DEBUG(msg) (find_living("eowul")->catch_msg(msg + "\n"))

void
create_monster()
{
    set_name("nazgul");
    set_short("black-robed hooded wraith");
    set_pshort("black-robed hooded wraiths");
    set_race_name("wraith");

             // str  dex  con  int  wis  dis  race  occup
    set_stats(({200, 200, 350, 380, 347, 300,    0,   300 }));

    set_all_hitloc_unarmed(30);

    set_gender(G_NEUTER);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(OBJ_I_RES_MAGIC, 30);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 50);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);

    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);

    add_cmdsoul(MORGUL_COMMAND_SOUL);
    update_hooks();

    setuid();
    seteuid(getuid());
    object mage_shadow = clone_object(MORGUL_SHADOW);
    mage_shadow->shadow_me(this_object(), GUILD_TYPE, GUILD_STYLE,
        GUILD_NAME, "");

    this_object()->set_nazgul(1);
    set_alarm(1.0, 0.0, &command("wear robe"));
    set_alarm(1.1, 0.0, &command("hood me"));
}

void
rejoin_combat()
{
    if ((m_sizeof(stopped_enemies) == 0) && (m_sizeof(stopped_targets) == 0))
        return;

    // TODO Add message about restarting attacks
    tell_room(target_room, "Rejoining combat");

    foreach(object player, object *enemies : stopped_enemies) {
        foreach(object enemy : enemies) {
            player->query_combat_object()->cb_add_enemy(enemy);
        }
    }

    foreach(object player, object target : stopped_targets) {
        player->attack_object(target);
    }

    stopped_targets = ([ ]);
    stopped_enemies = ([ ]);
}

int
is_supporter(object target)
{
    if (!target->query_npc()) return 0;
    if (target->id("_morgul_monster")) return 1;
    if (target->id("_orcmaker_orc")) return 1;
    return 0;
}

object *
find_supporters()
{
    return filter(FILTER_LIVE(all_inventory(target_room)),
        is_supporter);
}

void
takeoff_steed()
{
    DEBUG("Removing Nazgul");
    tell_room(target_room, QCTNAME(steed) + " stretches its pinions and "
        + "flies off into the sky.");
    steed->remove_object();
    remove_object();
}

void
mount_steed()
{    
    if (!objectp(steed)) 
    {
        tell_room(target_room, QCTNAME(this_object()) + " leaves.\n");
        remove_object();
        return;
    }

    hostile = 0;
    this_object()->move("/obj/void", 1);
    tell_room(target_room, QCTNAME(this_object()) + " mounts "
        + QTNAME(steed) + ".\n");
    steed->set_stage(3);

    set_alarm(2.0, 0.0, takeoff_steed);
}

void
depart()
{
    if (objectp(query_attack()) 
        && (environment(query_attack()) == environment(this_object()))) return;

    command("hiss My work here is complete.");
    add_prop(OBJ_M_NO_ATTACK, 1);

    set_alarm(2.0, 0.0, mount_steed);
}

void
select_target()
{
    if (objectp(query_attack()) 
        && (environment(query_attack()) == environment(this_object()))) return;

    object *targets = filter(FILTER_PLAYERS(all_inventory(target_room)),
        potential_target);
    if (sizeof(targets) == 0) 
    {
        if (departure_alarm == -1) 
        {
            departure_alarm = set_alarm(60.0, 0.0, depart);
        }
        return;
    }

    if (departure_alarm != -1) {
        remove_alarm(departure_alarm);
        departure_alarm = -1;
    }

    object new_target = targets[random(sizeof(targets))];
    command("point " + OB_NAME(new_target));
    command("hiss That one is next!");
    command("kill " + OB_NAME(new_target));

    find_supporters()->command("kill " + OB_NAME(new_target));
}

void
initiate_combat()
{
    hostile = 1;
    rejoin_combat();

    if (target_check == -1) {
        target_check = set_alarm(0.0, 10.0, select_target);
    }
}

void
issue_warning()
{
    object *targets = filter(FILTER_PLAYERS(all_inventory(target_room)),
        potential_target);
    if (sizeof(targets) == 0) return;

    object target = targets[random(sizeof(targets))];
    command("mturn " + OB_NAME(target));
    command("hiss to " + OB_NAME(target) + " Run now or perish, worm");
}

void
clear_no_attack()
{
    // TODO: better message
    tell_room(target_room, "You feel able to attack again.\n");
    target_room->add_prop(ROOM_M_NO_ATTACK, original_room_m_no_attack);
}

void
add_weaponry()
{
    setuid();
    seteuid(getuid());

    mace = clone_object("/d/Gondor/morgul/obj/wraith_mace");
    mace->move(this_object(), 1);

    object fbb = clone_object("/d/Gondor/common/wep/nazgul_sword");
    fbb->move(this_object(), 1);

    command("wield all");
}

void
land()
{
    steed->set_no_show_composite(0);

    tell_room(target_room, "The huge winged beast descends from the "
        + "sky and lands here.\n");
}

void
dismount()
{
    this_object()->move(target_room, 1);
    tell_room(target_room, QCTNAME(this_object()) + " dismounts from "
        + QTNAME(steed) + ".\n");

    steed->set_stage(4);
}

int
potential_target(object target, int no_feelings = 0)
{
    if (member_array(target, original_enemies) != -1) return 1;
    if (IS_MEMBER(target)) return 0;
    if (target->query_anghoth_member()) return 0;
    if (target->query_prop(NPC_I_NO_RUN_AWAY)) return 0;
    if (target->query_invis()) return 0;
    if (target->query_wiz_level()) return 0;
    if (target->id("winged steed")) return 0;

    object *magesInTeam = filter(target->query_team_others(),
        &operator(==)(GUILD_NAME) @ &->query_guild_name_occ());
    if (sizeof(magesInTeam)) return 0;

    if (no_feelings) return 1;
    return query_feeling(target) >= 0 ? 1 : 0;
}

mixed
query_valid_exits()
{
    mixed *result = ({ });

    mixed *all_exits = target_room->query_exit();
    for(int i = 0; i < sizeof(all_exits); i = i + 3) {
        mixed *exit = ({ all_exits[i], all_exits[i + 1], all_exits[i + 2] });
        if (exit[2] == 0) result += ({ exit });
    }

    return result;
}

void
grab_and_remove_living()
{
    // TODO: Announce the winged beast if it doesn't do a toss
    steed->set_stage(3);

    mixed *exits = query_valid_exits();
    if (!sizeof(exits)) {
        DEBUG("No exits found");
        return;
    }

    mixed target_exit = exits[random(sizeof(exits))];

    object *all_livings = FILTER_LIVE(all_inventory(target_room));
    object *potential_targets = filter(all_livings, &potential_target(, 1));

    object *player_targets = FILTER_PLAYERS(potential_targets);
    if (sizeof(player_targets) == 1) potential_targets -= player_targets;

    if (!sizeof(potential_targets)) {
        DEBUG("No potential targets found for toss");
        return;
    }

    object target = potential_targets[random(sizeof(potential_targets))];

    target->catch_msg("A huge winged beast swoops in and grabs you in "
        + "it's claws. It tosses you " + target_exit[1] + ".\n");
    tell_room(target_room, "A huge winged beast swoops in, grabs "
        + QTNAME(target) + " and tosses " + target->query_objective()
        + " " + target_exit[1] + "\n", ({ target }));

    target->move_living("M", target_exit[0], 1);

    tell_room(target_exit[0], QCTNAME(target) + " comes crashing in.\n", ({ target }));

    // TODO: Paralyze player for a while, and do some damage
}

void
passify()
{
    tell_room(target_room, "\nBlind fear mixed with terror and deadly cold "
        + "embrace you as the dark shape draws nearer.\n\n");
    // TODO: Adjust message based on feeling towards the nazgul?

    object *livings = FILTER_LIVE(all_inventory(target_room));
    foreach(object living : livings)
    {
        object living_target = living->query_attack();
        if (objectp(living_target) && (environment(living_target) == target_room))
        {
            DEBUG(sprintf("Target for %O was %O", living, living_target));
            stopped_targets[living] = living_target;
        }

        object *present_enemies = filter(filter(living->query_enemy(-1), objectp),
            &operator(==)(target_room) @ environment);
        stopped_enemies[living] = present_enemies;

        living->stop_fight(present_enemies);
        DEBUG(sprintf("Enemies for %O: %O", living, present_enemies));
    }

    original_room_m_no_attack = target_room->query_prop(ROOM_M_NO_ATTACK);
    target_room->add_prop(ROOM_M_NO_ATTACK, "TODO: Determine message.\n");
}

void
announce_winged_steed()
{
    steed->set_stage(2);
    tell_room(target_room, "\nA dark shape, like a cloud and yet not like a "
        + "cloud, for it moves far too quickly, is coming out of the sky, "
        + "speeding towards you, blocking out all light as it "
        + "approaches.\n\n");
}

void
start_encounter(object summoning_mage)
{
    target_room = environment(summoning_mage);
    original_enemies = summoning_mage->query_enemy(-1);

    setuid();
    seteuid(getuid());
    steed = clone_object(MORGUL_NPC_DIR + "obj/winged_steed");
    steed->set_no_show_composite(1);
    steed->move(target_room);

    tell_room(target_room, "\nFar off, storm clouds break, and a distant "
        + "figure appears in the sky.\n\n");

    set_alarm(2.0, 0.0, announce_winged_steed);
    set_alarm(4.0, 0.0, passify);
    set_alarm(6.0, 0.0, grab_and_remove_living);
    set_alarm(8.0, 0.0, land);
    set_alarm(10.0, 0.0, dismount);
    set_alarm(12.0, 0.0, add_weaponry);
    set_alarm(14.0, 0.0, &command("hiss Who here dares to defy the Dark Lords will?"));
    set_alarm(16.0, 0.0, &command("gaze"));
    set_alarm(18.0, 0.0, issue_warning);
    set_alarm(20.0, 0.0, clear_no_attack);
    set_alarm(34.0, 0.0, initiate_combat);
}

void
remove_object()
{
    target_room->add_prop(ROOM_M_NO_ATTACK, original_room_m_no_attack);
    if (objectp(steed)) steed->dismiss_steed();
    ::remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->id("_nazgul_broadsword")) {
        ob->set_hands(W_ANYH);
    }
}

void
leave_inv(object ob, object to)
{
    if (ob->id("_nazgul_broadsword")) {
        ob->set_hands(W_BOTH);
    }
    ::leave_inv(ob, to);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    initiate_combat();
}

int
add_prop_live_i_concentrate()
{
    casting = 1;
    return 1;
}

int
remove_prop_live_i_concentrate()
{
    casting = 0;
}

private int
shield_attack_possible(object victim)
{
    if (member_array(victim, shield_attack_victims) != -1) {
        DEBUG("Victim already hit by shield attack");
        return 0;
    }

    object *shields = filter(victim->query_armour(-1), 
        &operator(==)(A_SHIELD) @ &->query_at());
    return sizeof(shields) > 0;
}

public void
perform_shield_attack(object victim)
{
    object *shields = filter(victim->query_armour(-1), 
        &operator(==)(A_SHIELD) @ &->query_at());
    if (sizeof(shields) == 0) return;

    shield_attack_victims += ({ victim });
    object target_shield = shields[random(sizeof(shields))];

    tell_watcher(QCTNAME(this_object()) + " slams " 
        + this_object()->query_possessive() + " " + mace->short()
        + " down upon " + QTPNAME(victim) + " " + target_shield->short()
        + ", shattering it with the powerfull blow.\n", this_object(),
        ({ victim }));
    victim->catch_msg(QCTNAME(this_object()) + " slams " 
        + this_object()->query_possessive() + " " + mace->short()
        + " down upon your " + target_shield->short() + ", shattering it.\n");
    target_shield->remove_broken();
}

public void mace_hit(object target) 
{
    int spike_hit = random(2);
    int pen = 800;
    mixed hitresult = target->hit_me(pen, spike_hit ? W_IMPALE : W_BLUDGEON, 
        this_object(), -1);

    if (sizeof(hitresult) < 5) return;

    DEBUG(sprintf("Hit result: %O", hitresult));
    if (hitresult[0] == -1) {
        // TODO: Dodge
        return;
    }

    if (hitresult[0] == -2) {
        // TODO: Parry
        return;
    }

    if (hitresult[0] == -1) {
        // TODO: miss
        return;
    }

    object cobj = target->query_combat_object();
    mixed target_hitinfo = cobj->query_hitloc(hitresult[4]);
    string hitloc_name = target_hitinfo[2];
    if (sizeof(target_hitinfo[4]) != 0) 
    {
        hitloc_name = target_hitinfo[4][0]->short();
    }

    // TODO: Vary descriptions based on phurt (hitresult[0])
    if (spike_hit) 
    {
        target->catch_msg(QCTNAME(this_object()) + " hits your "
            + hitloc_name + " with the spikes of the mace, hurting you.\n");
        tell_watcher(QCTNAME(this_object()) + " hits "
            + QTNAME(target) + ".\n", target, ({ target }));
    }
    else
    {
        target->catch_msg(QCTNAME(this_object()) + " slams your "
            + hitloc_name + " with the mace, hurting you.\n");
        tell_watcher(QCTNAME(this_object()) + " hits "
            + QTNAME(target) + "\n", target, ({ target }));
    }
}

public void
perform_special(object victim)
{
    if (mace->query_wielded() != this_object()) return;

    if (shield_attack_possible(victim)) {
        perform_shield_attack(victim);
    } else {
        object *all_livings = FILTER_LIVE(all_inventory(target_room));
        object *targets = filter(all_livings, &potential_target());

        tell_room(environment(this_object()), 
            "\n" + QCTNAME(this_object()) + " swings "
            + this_object()->query_possessive() + " " + mace->short()
            + " in a wide arc.\n\n", ({ }), this_object());

        foreach(object target : targets) mace_hit(target);
    }
}

private int
under_effect_of_gostangwedh(object victim) 
{
    object *effects = victim->query_magic_effects();
    if (!pointerp(effects)) return 0;
  
    foreach(object effect : effects) {
        if (objectp(effect) 
            && (MASTER_OB(effect) == MORGUL_SPELL_OBJ_DIR + "gostangwedh")) {
            return 1;
        }
    }

    return 0;
}

public void
perform_spell_attack(object victim)
{
    int whimpy = victim->query_whimpy();
    int health_target = ((whimpy + 5) * victim->query_max_hp()) / 100;

    if ((victim->query_hp() <= health_target) 
        && !under_effect_of_gostangwedh(victim)) 
    {
        command("hiss to " + OB_NAME(victim) + " Your time has come, wretch.");
        command("cast gostangwedh " + OB_NAME(victim));
    } else {
        command("cast morthul");    
    }    
}

public int
special_attack(object victim)
{
    if (!sulambar && !casting) {
        command("cast sulambar");
        sulambar = 1;
    } else if (!casting) {
        perform_spell_attack(victim);
    } 

    if (preparing_special > 0) {
        DEBUG(sprintf("PreparingSpecial: %d", preparing_special));
        preparing_special--;
        if (preparing_special == 0) {
            perform_special(victim);
        }
        return 1;
    }

    if (mace->query_wielded() != this_object()) {
        DEBUG("Mace not wielded.");
        return 0;
    }

    int special_chance = shield_attack_possible(victim) ? 4 : 8;
    int dice = random(special_chance);
    DEBUG(sprintf("Chance: %d, dice: %d", special_chance, dice));
    if (dice == 0) {
        // We announce the special attack using additional newlines as to
        // give them some chance to notice and act upon it.
        tell_room(environment(this_object()),
            "\n" + QCTNAME(this_object()) + " raises " 
            + this_object()->query_possessive() + " " + mace->short()
            + " high above " + this_object()->query_objective() 
            + " and raises a shrill cry to the wind.\n\n", ({ }),
            this_object());
        preparing_special = 1 + random(2);
        return 1;
    }

    return 0;
}
