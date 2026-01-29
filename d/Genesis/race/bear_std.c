#pragma strict_types

inherit "/std/player";
inherit "/std/combat/unarmed";
inherit "/d/Genesis/std/mail_stuff";
inherit "/d/Genesis/std/special_stuff";

#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define QEXC query_combat_object()

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_BHUG  3
    
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
    
public void
finger_info()
{
    finger_mail();
    finger_special();
}

static void 
genesis_commands()
{
}

string
query_race()
{
    return "bear";
}

public int
add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
{
    if (!QEXC)
        return 0;
    return (int)QEXC->cb_add_attack(wchit, wcpen, damtype, prcuse, id);
}

public int
remove_attack(int id)
{
    if (!QEXC)
       return 0;
    return (int)QEXC->cb_remove_attack(id); 
}

public int
add_hitloc(int *ac, int prchit, string desc, int id)
{
    if (!QEXC)
        return 0;
    return (int)QEXC->cb_add_hitloc(ac, prchit, desc, id);
}

public int
remove_hitloc(int id)
{
    if (!QEXC)
        return 0;
    return (int)QEXC->cb_remove_hitloc(id); 
}

void
cr_configure()
{   
    add_attack(45, 40, W_SLASH,    25, A_BITE);
    add_attack(55, 50, W_BLUDGEON, 30, A_RPAW);
    add_attack(55, 50, W_BLUDGEON, 30, A_LPAW);
    add_attack(55, 60, W_BLUDGEON, 15, A_BHUG);
    
    add_hitloc( ({ 4, 5, 5 }), 15, "head", H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 60, "body", H_BODY); 
    add_hitloc( ({ 9, 9, 9 }), 25, "legs", H_LEGS);
}

string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE: return "bite";
    case A_RPAW: return "right front paw";
    case A_LPAW: return "left front paw";
    case A_BHUG: return "bearhug";
    }
}

public void
start_player()
{
    if (!sizeof(query_cmdsoul_list()))
    {
        add_cmdsoul("/d/Genesis/cmd/misc_cmd_dwarf");
        add_cmdsoul("/d/Genesis/cmd/soul_cmd_dwarf");
    }

    add_prop(CONT_I_VOLUME, 120000);
    add_prop(CONT_I_WEIGHT, 110000);

    ::start_player();
}

public nomask string
query_def_start()
{
    return "/w/mercade/forest";
}

public string
query_def_post()
{
    return "/d/Gondor/common/dwarf_guild/post";
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
}

static nomask void
stats_to_acc_exp()
{
    int il  = (SS_STR - 1);
    int sum = 0;
    int tmp;

    while(++il < SS_NO_STATS)
    {
        tmp = stat_to_exp(query_base_stat(il));

        if (tmp > 0)
        {
            set_acc_exp(il, tmp);

            /* Only count the "real" stats in the total sum. */
            if (il < SS_NO_EXP_STATS)
            {
                sum += tmp;
            }
        }
        else
        {
            set_acc_exp(il, 0);
        }
    }

    set_exp_quest(sum);
    set_exp_combat(0);
    set_exp_general(0);
}

void
acc_exp_to_stats()
{
    int il = (SS_STR - 1);

    while(++il < SS_NO_STATS)
    {
        if (query_base_stat(il) >= 0)
        {
            set_base_stat(il, exp_to_stat(query_acc_exp(il)));
        }
    }
}

public nomask void
update_stat(int stat)
{
    set_base_stat(stat, exp_to_stat(query_acc_exp(stat)));
}

public nomask int
query_statmod(int stat)
{
    return 10;
}

public int
query_humanoid()
{
    return 0;
}

string
race_sound()
{
    return "growls";
}

string
actor_race_sound()
{
    return "growl";
}

mapping
query_com_sounds()
{
    return ([ "human":"growls", "dwarf":"growls", "hobbit":"growls",
        "elf":"growls", "gnome":"growls", "goblin":"growls" ]);
}
