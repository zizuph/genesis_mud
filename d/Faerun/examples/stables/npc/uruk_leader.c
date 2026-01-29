/*
 *  Palmer December 2002
 * Added do_wander() to make uruk lead horse and team
 * along random pre-defined paths
 * Snarfed from:
 *	/d/Gondor/morgul/npc/ithil_uruk.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, Feb 1996
 */
#pragma strict_types

inherit "/d/Shire/bree/rooms/town/stable/npc/soldier.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "uruk_defs.h"
#include "../bree_stables.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/halberd", MORGUL_DIR + "obj/mornstar"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/chainmail"})

/* Globals */
int nbr_walks = 1;
int next = 1;
string *walk_path;

/* Function prototypes */
public void create_team();
public void destruct_team();
public void do_wander();

public void
create_ithil_uruk()
{
}

nomask void
create_ithil_soldier()
{
    int rnd = random(41);  // For random stat modifer

    set_short("huge angry uruk");
    set_pshort("huge uruks");
    set_name("uruk");
    set_pname("uruks");
    set_living_name("blarg");
    set_adj(({"huge", "angry"}));
    remove_adj("black-skinned");
    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," ")))
    + " orc, one of the uruk-hai, with crooked legs and long arms "
    + "that hang almost to the ground. He looks much stronger and "
    + "meaner than other orcs of lesser breeds."));

    default_config_npc(85 + rnd / 2);
    set_base_stat(SS_INT, 65 + rnd);
    set_base_stat(SS_WIS, 65 + rnd);

    set_alignment(-350-rnd*10);

    set_skill(SS_WEP_SWORD,   75 + rnd);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB,    75 + rnd);
    set_skill(SS_WEP_AXE,     75 + rnd);
    set_skill(SS_WEP_KNIFE,   75 + rnd);
    set_skill(SS_PARRY,       75 + rnd);
    set_skill(SS_DEFENCE,     75 + rnd);
    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 85000 + rnd * 500);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 80000 + rnd * 500);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_DONT_CLING, 1);
    add_prop("_horse_trust_", 1);
    create_ithil_uruk();
    create_team();
    TO->arm_me();
    reset_monster();
    set_alarm(60.0, 60.0, do_wander);

}

public void
create_team()
{
    object orc1, orc2, horse;
    string start_loc;

/* Notes:
*
*  I wanted to use  ONE_OF_LIST but it didn't like mixed type arrays
*
*  Paths are ~ 25 rooms at one minute each.
* The uruk leads the horse through two paths, so you have 50 minutes to do the quest.
*/

    switch (random(4))
    {
    case 0:
        walk_path = ({"/d/Shire/anduin/east/rd01", "w","w","s","s","s","s","s","s","se","se","se","s","s","s","se","s","s","s","s","s","s","s","s","s","s","s","e"});
                       // Ends /d/Gondor/ithilien/road/crossroads
        break;
    case 1:
        walk_path = ({"/d/Gondor/ithilien/road/rr6","n","nw","n","e","ne","e","e","e","ne","se","se","ne","se","e","s","e","e","n","n","e","ne","e","ne","e","s","s"});
                       // Ends /d/Gondor/ithilien/road/nr6
        break;
    case 2:
        walk_path = ({"/d/Gondor/ithilien/poros/p14", "se","se","e","e","e","ne","e","e","n","n","n","n","n","sw","w","w","nw","w","w","w","e","e","e","n","ne","e"});
                       // Ends /d/Gondor/ithilien/sforest/thicket4
        break;
    case 3:
        walk_path = ({"/d/Shire/annuminas/amc1", "s","s","sw","s","s","s","sw","se","sw","s","se","s","s","s","s","se","se","se","sw","sw","s","s","s","s","e","e"});
                       // Ends /d/Shire/eastroad/western/er17n
        break;
    default:
        walk_path = ({"/d/Gondor/ithilien/road/rr6","n","nw","n","e","ne","e","e","e","ne","se","se","ne","se","e","s","e","e","n","n","e","ne","e","ne","e","s","s"});
                       // Ends /d/Gondor/ithilien/road/nr6
    }

    start_loc = walk_path[0];

    orc1 = clone_object(BREE_STABLES_NPC_DIR + "uruk");
    orc1->arm_me();
    orc1->move_living("null", start_loc);

    orc2 = clone_object(BREE_STABLES_NPC_DIR + "uruk");
    orc2->arm_me();
    orc2->move_living("null", start_loc);

    horse = clone_object(BREE_STABLES_OBJ_DIR + "quest_steed");
    horse->move_living("null", start_loc);

    TO->move_living("null", start_loc);
    TO->team_join(orc1);
    TO->team_join(orc2);
    TO->command("lead horse");
}

// This is to keep the guy from chasing people
public void
start_follow(object ob)
{
    ;
}

public void
do_wander()
{
    int nbr_rooms = sizeof(walk_path);

    if (TO->query_attack())
    {
        return;
    }

    /* When we get to the last room, move then restart on another walk or destruct team if its second walk*/
    if (next == (nbr_rooms -1))
    {
        TO->command(walk_path[next]);
        if (nbr_walks == 2)
        {
            destruct_team();
            TO->remove_object();
        }
        else
        {
            nbr_walks = 2;
            next = 1;
            destruct_team();
            create_team();
        }
    }
    else
    {
        TO->command(walk_path[next]);
        next = next + 1;
    }
}


public void
destruct_team()
{
        object *team;
        team = TO->query_team();
        TO->leave_team(team[0]);
        TO->leave_team(team[0]);
        team[0]->remove_object();
        team[1]->remove_object();
        TO->command("hdestruct");
}

public void
do_die(object killer)
{
    killer->add_prop("_i_killed_uruk", 1);
    ::do_die(killer);
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm2 = ARM_ARRAY2;

    set_all_hitloc_unarmed(20);
}

