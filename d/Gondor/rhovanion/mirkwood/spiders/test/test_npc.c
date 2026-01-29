/*
 * Base NPC for testing purposes.
 *
 * Will include ability to load different guilds
 *
 * Created by Petros, February 2009
 * Adapted by Eowul for testing the mirkwood spiders
 */

#pragma strict_types

#include <ss_types.h>

inherit "/std/monster";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Genesis/specials/guilds/test/npc_setup.h"
#include "/d/Genesis/specials/guilds/test/npc_special_attack.h"

// Defines
#define GUILD_TESTER        "/d/Genesis/specials/guilds/guild_tester_soul"
#define DATA_DIR            "/d/Genesis/specials/guilds/test/data/"

// Prototypes
public int      load_guild(string guildname);
public void     set_max_skills();
public void     equip_test_npc();
public void     load_data(string file);
public void     save_data(string file);

// Global Variables
public int total_healed = 0;
public mapping  npc_data = ([
    "track_damage"              : 1,
    "prevent_damage"            : 1,
    "guilds"                    : ({ }),
    "commands"                  : ({ }),
    "equipment"                 : ({ }),
    "names"                     : ({ "test_npc" }),
    "short_desc"                : "test npc",
    "long_desc"                 : "This is a test npc.\n",
    "base_stats"                : ({ 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 }),
    "base_race"                 : "human",
    "setup_function"            : "",
    "special_attack_function"   : "",
    "spell_notify_function"     : "",
    "alignment"                 : 0,
    ]);
    
/* 
 * Function:        create_test_npc
 * Description:     Mask this function to create your own test npc
 */
public void
create_test_npc()
{
}

public string *
query_equipment_list()
{
    return npc_data["equipment"];
}

public void
equip_test_npc()
{
    setuid();
    seteuid(getuid());
    foreach (string eq : query_equipment_list())
    {
        object masterob;
        if (!objectp(masterob = find_object(eq)))
        {
            if (LOAD_ERR(eq)
                || !objectp(masterob = find_object(eq)))
            {
                send_debug_message("test_npc", "Cannot clone equipment "
                    + eq + ".");
                continue;
            }
        }
        clone_object(eq)->move(this_object(), 1);
    }
    command("wield all");
    command("wear all");
}

public nomask void
create_monster()
{
    ::create_monster();
    // This property ensures that when npcs wield weapons, they won't
    // try and do unarmed attacks.
    add_prop(NPC_I_NO_UNARMED, 1);
    
    setuid();
    seteuid(getuid());

    create_test_npc();
}

static void
set_max_skills()
{
    mixed * obs;
    mixed otmp;
    
    /* Get the list of trainer objects */
    obs = ({});
    otmp = this_object()->query_guild_trainer_occ();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_race();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_lay();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_craft();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    obs -= ({ 0 });
    
    object oldtp = this_player();
    set_this_player(this_object());
    foreach (mixed trainer : obs)
    {
        foreach (int snum : trainer->sk_query_train())
        {
            set_skill(snum, min(100, 
                max(query_base_skill(snum), trainer->sk_query_max(snum))));
        }
    }
    set_this_player(oldtp);
}

public int
load_guild(string guildname)
{
    setuid();
    seteuid(getuid());
    GUILD_TESTER->start_guild(guildname, this_object());
    
    set_max_skills();    
    return 1;    
}

public void
refresh_npc()
{
    if (this_object()->query_prevent_damage())
    {
        // Replenish all fatigue and mana and panic that may have been lost
        add_fatigue(500);
        add_mana(5000);
        add_panic(-5000);
    }
}

public void
setup_npc()
{
    if (strlen(npc_data["setup_function"]))
    {
        call_other(this_object(), npc_data["setup_function"]);
    }
    equip_test_npc();
}

public void
load_from_mapping(mapping data)
{
    // Update the npc_data with the input information
    npc_data = data;
    
    // Perform all the initialization from the data
    if (sizeof(npc_data["names"]))
    {
        set_name(npc_data["names"][0]);
        add_name(npc_data["names"][1..]);
    }
    set_short(npc_data["short_desc"]);
    set_long(npc_data["long_desc"]);
    set_race_name(npc_data["base_race"]);
    set_alignment(npc_data["alignment"]);
    for (int i = SS_STR; i <= SS_CRAFT; ++i)
    {
        set_base_stat(i, npc_data["base_stats"][i]);
    }
    stats_to_acc_exp();
    heal_hp(query_max_hp());
    add_mana(query_max_mana());
    add_fatigue(query_max_fatigue());
    foreach (string guildname : npc_data["guilds"])
    {
        load_guild(guildname);
    }

    // Call the setup function that's been specified.
    set_alarm(1.0, 0.0, setup_npc);
    total_healed = 0;
}

public void
load_data(string file)
{
    if (file_size(DATA_DIR + file + ".o") <= 0)
    {
        return;
    }
    
    mapping loaded_data = restore_map(DATA_DIR + file);    
    load_from_mapping(loaded_data);
}

public void
save_data(string file)
{
    save_map(npc_data, DATA_DIR + file);
}

/*
 * Function:    special_attack
 * Description: This npc will always try and execute all of his commands
 *              when special_attack is called (every heartbeat).
 */
public int
special_attack(object target)
{
    if (strlen(npc_data["special_attack_function"]))
    {
        call_other(this_object(), npc_data["special_attack_function"], target);
        refresh_npc();
        return 0;
    }
    
    // If there is no special attack specified, we go ahead and
    // just run through all the commands
    foreach (string action : npc_data["commands"])
    {
        command(action);
    }

    refresh_npc();
    return 0;
}

public void
notify_spell_complete(object spellobj, string arg)
{
    send_debug_message("test_npc", "Notified for spell "
        + spellobj->query_spell_name());
    if (strlen(npc_data["spell_notify_function"]))
    {
        call_other(this_object(), npc_data["spell_notify_function"], spellobj, arg);
        return;
    }
    
    // By default, this notification function will not do
    // anything.
}

/*
 * Function name: stop_fight
 * Description  : Makes this living stop fighting others.
 * Arguments    : mixed elist - the enemy or enemies to stop fighting.
 */
public void
stop_fight(mixed elist)
{
    ::stop_fight(elist);
    
    // In case the person is casting, we abort the spell.
    command("abort spell");
}

public void
notify_you_killed_me(object victim)
{
    object *enemies = query_enemy(-1);
    enemies -= ({ victim });
    if (!sizeof(enemies)) 
    {
        set_alarm(0.1, 0.0, environment(this_object())->fight_finished);
    }
}

public void
do_die(object killer)
{
    environment(this_object())->fight_finished();
    ::do_die(killer);
}

public void
heal_hp(int hp)
{
    ::heal_hp(hp);
    if (hp > 0) total_healed += hp;
}

public int
query_total_healed()
{
    return total_healed;
}