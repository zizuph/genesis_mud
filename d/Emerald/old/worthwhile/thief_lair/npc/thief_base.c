inherit "/d/Emerald/std/elf";

#include "../defs.h"
#include <ss_types.h>
#include <const.h>
#include <options.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <macros.h>

static int thief_level;

/* 
 * Function name: set_thief_skill
 * Description:   set a skill, keeping the existing skill level if it
 *                is higher.
 */
public void
set_thief_skill(int skill, int level)
{
    if (query_base_skill(skill) >= level)
    {
        return;
    }

    set_skill(skill, level);
}

void
config_thief(int level)
{
    config_elf(level);

    thief_level = level;

    set_alignment(random(level * 3) - level);

    map(({ SS_WEP_SWORD, SS_WEP_KNIFE, SS_UNARM_COMBAT,
           SS_2H_COMBAT, SS_PARRY, SS_DEFENSE, SS_SNEAK,
           SS_HIDE, SS_PICK_POCKET, SS_BACKSTAB, SS_FR_TRAP,
           SS_AWARENESS }), &set_thief_skill(, level));

    set_thief_skill(SS_BLIND_COMBAT, max(40, level / 2));

    set_all_hitloc_unarmed(level / 4);

    add_prop(LIVE_I_QUICKNESS, level / 2);
}    

void
make_default_eq()
{
    int level = thief_level / 35;

    add_equipment(({
        THIEF_LAIR_DIR + "wep/stiletto",
	THIEF_LAIR_DIR + "arm/elf_chainmail" }));

    if (level > 0)
    {
        add_equipment(THIEF_LAIR_DIR + "obj/pouch" + min(3, level));
    }

    if (random(2))
    {
        add_equipment(THIEF_LAIR_DIR + "arm/quilt_leggings");
    }
    
    if (!random(4))
    {
        add_equipment(({ THIEF_LAIR_DIR + "arm/iron_buckler",
                                        THIEF_LAIR_DIR + "arm/visored_helm" }));
    }
}

string
def_answer()
{
    command(({ "emote denies everything", "smirk", "shrug",
        "emote looks at you and sneers: Get lost!",
        "say Shove it!" })[random(5)]);
    return "";
}
    
void
create_thief()
{
}

nomask void
create_elf()
{
    set_name("thief");
    set_pname("thieves");
    
    set_gender((random(5) > 0) ? G_MALE : G_FEMALE);
    
    set_default_answer(def_answer);
    
    set_act_time(10);
    add_act("cackle");
    add_act("grin");
    add_act("smile misch");
    add_act("ponder");

    /* Increased LIVE_I_QUICKNESS and special attacks make them worth more */
    set_exp_factor(120);

    create_thief();
}

void
start_wander()
{
    set_monster_home(THIEF_LAIR_DIR + "clone_handler");
    set_restrain_path(({ THIEF_LAIR_DIR }));
    set_random_move(7);
}

int
check_blind(object ob)
{
    return (!CAN_SEE_IN_ROOM(ob) || !CAN_SEE(ob, this_object()));
}

int
stab(object enemy)
{
    object *weps = query_weapon(-1), chosen_wep;
    mixed *ret;
    int dt;

    if (!sizeof(weps))
    {
        return 0;
    }

    chosen_wep = weps[random(sizeof(weps))];

    ret = enemy->hit_me(thief_level * 4, MAGIC_DT, this_object(), -1);

    if ((dt = chosen_wep->query_dt()) & W_IMPALE)
    {
        enemy->catch_tell("Someone stabs you in the " + ret[1] + "!\n");
    }
    else if (dt & W_SLASH)
    {
        enemy->catch_tell("Someone slashes at your " + ret[1] + "!\n");
    }
    else
    {
        enemy->catch_tell("Someone smashes you in the " + ret[1] + "!\n");
    }

    if (!random(3))
    {
        stab(enemy);
    }

    return 1;
}

int
sneak_away()
{
    string *dirs;
    object *enemies;
    int i;

    dirs = environment(this_object())->query_exit_cmds();

    if (sizeof(dirs))
    {
        /* Have to stop fighting to sneak out.  This could probably
         * be done more cleanly.
         */
        enemies = query_enemy(-1);
        stop_fight(enemies);
        i = command("sneak " + dirs[random(sizeof(dirs))]);
        map(enemies, attack_object);
        return i;
    }

    return 0;
}
    
int
special_attack(object enemy)
{
    object *enemies = all_inventory(environment()) & query_enemy(-1);
    object *blinded, bomb;
    int i;

    if (random(3))
    {
    	blinded = filter(enemies, check_blind);
    
    	if (sizeof(blinded))
    	{
    	    i = stab(enemies[random(sizeof(enemies))]);
    
    	    if ((sizeof(blinded) == sizeof(enemies)) && !random(3) && sneak_away())
    	    {
    		return 1;
    	    }
    
    	    return i;
	}
    }

    if (!random(10) &&
        !present("smoke_bomb_effect", environment()) &&
        (bomb = present("smoke_bomb", this_object())))
    {
        bomb->use_bomb();
        return 1;
    }
}

void
init_living()
{
    int hide;

    ::init_living();

    /* Auto-hide when players arrive */

    if (query_prop(OBJ_I_HIDE))
    {
        return;
    }

    if (sizeof(FILTER_PLAYERS(all_inventory(environment())) -
       ({ this_player() })))
    {
        return;
    }

    if (environment()->query_prop(ROOM_I_HIDE) < 0)
    {
        return;
    }

    hide = query_skill(SS_HIDE);
    hide = hide / 4 * 3 + random(hide / 4);
    add_prop(OBJ_I_HIDE, hide);
}

/*
 * Set the "unarmed off" option
 */
int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}

public mixed
oke_to_move(string exit)
{
    mixed ret = ::oke_to_move(exit);

    if (stringp(ret))
    {
        ret = "sneak " + ret;
    }

    return ret;
}

/*
 * Prevent the thief from doing actions while hidden
 */
void
monster_do_act()
{
    string name;

    if (query_prop(OBJ_I_HIDE))
    {
        name = query_seq_act_name();
        seq_clear(name);
        seq_addlast(name, ({ monster_act_time, monster_do_act }));
        return;
    }

    ::monster_do_act();
}

/*
 * Prevent the thief from doing chats while hidden
 */
void
monster_do_chat()
{
    string name;

    if (query_prop(OBJ_I_HIDE))
    {
        name = query_seq_chat_name();
        seq_clear(name);
        seq_addlast(name, ({ monster_chat_time, monster_do_chat }));
        return;
    }

    ::monster_do_chat();
}
