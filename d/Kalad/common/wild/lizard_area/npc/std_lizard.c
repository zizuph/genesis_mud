/*
 * /d/Kalad/common/wild/lizard_area/npc/std_lizard.c
 *
 * New Lizard Standard file. Imported by Warriors/Shamans
 * Coded by Mirandus, February 2nd, 2022
 *
 *
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/std/active_monster_base.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";
inherit "/d/Kalad/lib/team_protect";
#define ROBE  ARM + "lcloak"
#define SHIRT ARM + "lshirt"
#define PANTS ARM + "lpants"
#define NECK  ARM + "lnecklace"
#define ENHANCE  WEP + "uenhancer"


#define TYPE ({"menacing","dour", "gruesome", "grim",\
    "tootsome", "leary", "menacing", "intelligent", "haughty", "refined", \
    "distraught"})
#define PHYS ({"pointy-eared", "narrow-eyed", "snake-nosed", "towering",\
    "barrel-chested", "musclebound", "lithe", "languid", "athletic", "weathered"})
#define EYES ({"blue", "green", "grey"})
#define SKIN ({"green-scaled", "blue-scaled", "grey-scaled", "red-scaled", "gold-scaled", "ebony-scaled"})

#define I_KILLED_LIZARDS "_i_killed_lizards"

object shirt,pants,necklace,robe;

int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string hself = "";
string CAPheshe = "";
string CAPhisher = "";
string gender_race = "";

// Prototypes
string                help_response();
public void           create_lizard_living();
public void           ask_for_assistance()     { } 
public void           assist()                 { } 


/*
 * Function name: determine_sex()
 * Description  : Randomly selects the sex of the NPC and sets pronouns.
 */
void determine_sex()
{
    switch(random(2))
    {
    case 0:  set_gender(G_MALE);
             hishers = "his";
             heshe = "he";
             himher = "him";
             hself  = "himself";
             CAPheshe = "He";
             CAPhisher = "His";
             gender_race = "saurian";
             x = 0;
             break;
    case 1:  set_gender(G_FEMALE);
             hishers = "her";
             heshe = "she";
             himher = "her";
             hself = "herself";
             CAPheshe = "She";
             CAPhisher = "Her";
             gender_race = "saurian";
             x = 1;
             break;
    default: set_gender(G_NEUTER);
             break;
    }
} /* determine_sex */


/*
 * Function name: create_active_monster
 * Description  : Constructor. Creates the monster.
 */
nomask void create_active_monster()
{
    /* Redefine this function to customize the npcs */
    create_lizard_living();         
} /* create_active_monster */

/*
 * Function name: check_aggressive()
 * Description  : Returns whether the NPC should be aggressive based on
 *                the actions of the player. If they've attacked any of
 *                the Priests, they are not targeted.
 */
int
check_aggressive()
{
    if (TP->query_prop(I_KILLED_LIZARDS))
    {
        return 1;
    }

    return 0;
}
/*
 * Function name: create_lizard_living
 * Description  : Sets all the basic properties for the npc.
 */
public
void create_lizard_living()
{ 
    determine_sex();    
    string type, phys, eyes,skin;
    int i;

    seteuid(getuid());
    type = one_of_list(TYPE);
    phys = one_of_list(PHYS);
    eyes = one_of_list(EYES);
    skin = one_of_list(SKIN);
    
    string npc_name = "saurian";
    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name(npc_name);
    set_name(gender_race);    
    add_name("_saurian_lizard_");
    set_long("Standing tall and proud, this "+type
        +" "+phys+" "+gender_race+" is devouted to an ancient faith and "
        +"protecting "+hishers+" people. "+CAPheshe+" stands attentive and"
        +"protective, interacting with others as they pass and patrolling "
        +"when need be to ensure things are safe. Occasionally, "
        +heshe+" mutters something under "+hishers+" breath, "+hishers+" "
        +eyes+" eyes constantly monitoring the situation.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    for(i = 0; i < 6; i++)
        set_base_stat(i, 180);

    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_AWARENESS,90);
    set_all_hitloc_unarmed(45);

    set_aggressive(VBFC_ME("check_aggressive"));
    set_prospective_cluster(({"_saurian_lizard_"}));

    set_alignment(-100);

    set_act_time(random(400));
    add_act("say We shall overcome.");
    add_act("say Damn Thanarian Fools.");
    add_act("say Those humans have pushed us too far.");
    add_act("emote lowers his head rembmering.");
    add_act("emote shudders with rage.");
    add_act("say I am but a tool for vengence.");
    add_ask(({"about quest","quest", "quests", "task", 
            "tasks", "help"}), help_response,1);



} /* create_lizard_living */

/*
 * Function name: help_response
 * Description  : Gives a response 
 * Returns      : a string with the response
 */
string
help_response()
{
    if(TP->query_race_name() == "human")
    {
        command("say You are not welcome here. Your race has done too much to destroy "
            +"for some false god. Leave before I make you leave.\n");
        command("emote spits in disgust.");
        command("peer warily " + OB_NAME(TP));
        return "\n";
    }
    else
    {
        command("say Watch yourself here. We need no help, but we also want no trouble.\n");
        return "\n";
    }
    
    return "say I do not have time for you!\n";
} /* help_response */


/*
 * Function name: attacked_by()
 * String       : the object attacking (ob)
 * Description  : Determines who is attacking and gives a response.
 *                
 */
void
attacked_by(object ob)
{
    if (!ob->query_prop(I_KILLED_LIZARDS))
        ob->add_prop(I_KILLED_LIZARDS, 1);

    command("say By the Ancestors who grant me the power to destroy you!");
    map(query_team_others(), &->notify_attack_on_team(this_object(),
            ob));

    ::attacked_by(ob);

} /* attacked_by */

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
public void
help_friend(object ob)
{
    if (ob && !query_attack() && environment(ob) == environment())
    {
        this_object()->action_attack(ob);
    }
}
/*
 * Function name: hook_friend_attacked
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *		  attacker - The attacker
 */
void
hook_friend_attacked(object friend, object attacker)
{
    if (query_attack())
        return;
    if (random(10))
        set_alarm(rnd(), 0.0, &help_friend(attacker));
}

/* Function:         do_die()
 * What's it do:     Ordinarily initiates death in slain monster.
 * What's it do now: Changes alignment if the player is not human, and
 *                   determines what might drop.
 */
void
do_die(object killer)
{
    command("say You've only delayed the inevitable.");
    command("emote falls dead.");

    ::do_die(killer);
} /* do_die */


/* Function:         query_my_enemies() : written by Mortricia
 * What's it do:     Creates an array of enemies to be used for randomizing
 */
public varargs object *
query_my_enemies(int how_to_sort = 0)
{
    int i, j, swap = 0;
    object foo, *all, *enemies = ({ });
    all = all_inventory(environment(TO)) - ({ TO });
    for (i=0; i<sizeof(all); i++) {
        if (living(all[i]) && member_array(TO, all[i]->query_enemy(-1)) >= 0)
            enemies += ({ all[i] });
    }
    if (how_to_sort == 0) return enemies;

    for (i=0; i<sizeof(enemies)-1; i++) {
        for (j=i+1; j<sizeof(enemies); j++) {
            switch (how_to_sort) {
            case -1:     /* Sort in decreasing stat order */
                if (enemies[i]->query_average_stat() <
                    enemies[j]->query_average_stat()) swap = 1;
                break;
            case 1:      /* Sort in increasing stat order */
                if (enemies[i]->query_average_stat() >
                    enemies[j]->query_average_stat()) swap = 1;
                break;
            default:
                return enemies;
            }
            if (swap) {
                foo = enemies[i];
                enemies[i] = enemies[j];
                enemies[j] = foo;
                swap = 0;
            }
        }
    }
    return enemies;
}/*query_my_enemies*/

/* Function:         query_smallest_enemy() : written by Mortricia
 * What's it do:     Allows to easily determine the smallest enemy.
 */
public object
query_smallest_enemy()
{
    object *enemies;
    if (sizeof(enemies = TO->query_my_enemies(1)) == 0) return 0;
    return enemies[0];
}/*query_smallest_enemy*/

/* Function:         query_biggest_enemy() : written by Mortricia
 * What's it do:     Allows to easily determine the biggest enemy.
 */
public object
query_biggest_enemy()
{
    object *enemies;
    if (sizeof(enemies = TO->query_my_enemies(-1)) == 0) return 0;
    return enemies[0];
}/*query_biggest_enemy*/
