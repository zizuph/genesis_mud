/*
 * waterdeep/std/waterdeep_npc.c
 * Base file for NPCs of the city of Waterdeep
 *
 * Created by Brine, Feb 2021
 * --------------------------------------------------------------------
 * Feb 2022 Brine   Expanded to include occupation, attack and assist logic
 */

#pragma strict_types
#pragma no_clone

#include "../defs.h"
#include <macros.h>
#include <formulas.h>

inherit FAERUN_STD + "faerun_npc";

// Some constants
#define HUMAN               "human"
#define DWARF               "dwarf"
#define ELF                 "elf"
#define GNOME               "gnome"
#define HALFLING            "halfling"
#define HALF_ORC            "half-orc"
#define HALF_ELF            "half-elf"

private string my_occupation = "commoner";

void
create_waterdeep_npc()
{
    // Redefine this
}

void
create_faerun_npc()
{
    setuid();
    seteuid(getuid());

    add_prop(IS_WATERDEEP_NPC, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, " doesn't accept any gifts from you.\n");

    create_waterdeep_npc();
}

string
query_subrace_name()
{
    string race = query_race_name();

    switch (race)
    {
        case DWARF:
            return "shield dwarf";
        case HALFLING:
            return "lightfoot halfling";
        default:
            return race;
    }
}

void
create_shield_dwarf()
{
    set_race_name(DWARF);
    add_name(query_subrace_name());
}

void
create_lightfoot_halfling()
{
    set_race_name(HALFLING);
    add_name(query_subrace_name());
}

void
select_race()
{
    int rand_number = random(100) + 1;
    // TODO: create func for all races with weight and height
    switch (rand_number)
    {
        case 1..5: // half-orc
            set_race_name(HALF_ORC);
            break;
        case 6..10: // halfling
            create_lightfoot_halfling();
            break;
        case 11..15: // gnome
            set_race_name(GNOME);
            break;
        case 16..25: // half-elf
            set_race_name(HALF_ELF);
            break;
        case 26..35: // elf
            set_race_name(ELF);
            break;
        case 36..50: // dwarf
            create_shield_dwarf();
            break;
        default: // human
            set_race_name(HUMAN);
            break;
    }
}

void
do_die(object killer)
{
    killer->add_prop(ENEMY_OF_WATERDEEP, 1);
    ::do_die(killer);
}

void
request_team_assistance()
{
    query_team()->command("assist");
}

void
try_kill_enemy(object enemy, string msg = "")
{
    object *team = query_team();

    // One enemy at a time, and only attack foes we can see and that are present
    if (query_attack() || !CAN_SEE(TO, enemy) || !present(enemy, ENV(TO)))
        return;
    
    // Only attack if we are the leader of our team, or we are not in one
    if (sizeof(query_team_others()) && !sizeof(team))
        return;
    
    // Don't run our mouth if we don't dare to attack, or if we have nothing
    // to say
    if (F_DARE_ATTACK(TO, enemy) && strlen(msg))
    {
        command("say to " + enemy->query_real_name() + " " + msg);
    }

    command("kill " + enemy->query_real_name());
    set_alarm(1.0, 0.0, &request_team_assistance());
}

void
replenish_me()
{
    set_hp(query_max_hp());
    set_mana(query_max_mana());
    set_fatigue(query_max_fatigue());
}

void
set_occupation(string occupation)
{
    my_occupation = occupation;
}

string
query_occupation()
{
    return my_occupation;
}
