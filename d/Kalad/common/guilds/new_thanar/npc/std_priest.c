/*
 * /d/Kalad/common/guilds/new_thanar/npc/std_priest.c
 *
 * Moderate priest who acts as just a grinding NPC.
 * Coded by Mirandus, January 17th, 2018
 *
 * This is the basic priest who will make up some of the main
 * level. Stronger and more worth targeting, but more dangerous.
 *
 * TODO - Add a response when a non-human enters the environment.
 *
 * Update Log - Set race name based on gender. Priest/Priestess - Mirandus
 *
 *
 * 2021-04-15 - Cotillion
 * - Set size to 180, removed random. 
 *   The skills don't even merit that kind of stat.
 * - Fixed issue with drop messages.
 *
 * 2021-08-08 - Meton
 *  Changed random coin drop in line 355, as random(10) gold inside the 
 *  array didnt work, to random 1440
 */

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
inherit "/d/Kalad/std/active_monster_base.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";
#define ROBE  ARM + "probe"
#define SHIRT ARM + "pmail"
#define PANTS ARM + "pleggings"
#define NECK  ARM + "pnecklace"
#define CLUB  WEP + "pclub"


#define TYPE ({"plain","dour", "friendly", "grim",\
    "stoic", "contemplative", "menacing", "intelligent", "refined", "pious", \
    "distraught"})
#define PHYS ({"big-eared", "round-eyed", "button-nosed", "towering",\
    "barrel-chested", "musclebound", "lithe", "languid", "athletic", "weathered"})
#define EYES ({"blue", "green", "brown", "hazel", "grey"})
#define SKIN ({"dark", "light", "pale", "tanned", "sun-burned", "ebony"})
#define HAIR ({"blonde", "dirty-blonde", "red", "black", "auburn", \
    "white", "grey"})

#define I_KILLED_PRIESTS "_i_killed_priests"

object shirt,pants,necklace,robe,club;

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
string                thanar_response();
public void           create_thanar_living();
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
             gender_race = "priest";
             x = 0;
             break;
    case 1:  set_gender(G_FEMALE);
             hishers = "her";
             heshe = "she";
             himher = "her";
             hself = "herself";
             CAPheshe = "She";
             CAPhisher = "Her";
             gender_race = "priestess";
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
    create_thanar_living();         
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
    if (TP->query_prop(I_KILLED_PRIESTS))
    {
        return 1;
    }

    return 0;
}
/*
 * Function name: create_thanar_living
 * Description  : Sets all the basic properties for the npc.
 */
public
void create_thanar_living()
{ 
    determine_sex();    
    string type, phys, eyes,skin, hair;
    int i;

    seteuid(getuid());
    type = one_of_list(TYPE);
    phys = one_of_list(PHYS);
    eyes = one_of_list(EYES);
    skin = one_of_list(SKIN);
    hair = one_of_list(HAIR);

    string npc_name = "human";
    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name(npc_name);
    set_name(gender_race);    
    add_name("_thanar_priest");
    set_long("Standing tall and proud in his faith, this "+type
        +" "+phys+" "+gender_race+" is intent on ensuring the spread and "
        +"following of "+hishers+" faith. "+CAPheshe+" tends to aspects "
        +"of the church answering questions of practitioners, cleaning "
        +"when need be and ensuring things are organized. Occasionally, "
        +heshe+" mutters something under "+hishers+" breath, "+hishers+" "
        +eyes+" eyes constantly monitoring the situation.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    for(i = 0; i < 6; i++)
        set_base_stat(i, 180);

    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,90);

    set_aggressive(VBFC_ME("check_aggressive"));
    set_prospective_cluster(({"_thanar_priest_"}));

    set_alignment(-100);

    set_act_time(random(400));
    add_act("say Humanity should rule Kalad.");
    add_act("say Thanar grants us clarity and wisdom.");
    add_act("say We hold power, by Divine Right! Damned Saurians and Goblins.");
    add_act("emote lowers his head in prayer.");
    add_act("emote turns his head to the sky in prayer.");
    add_act("say I am but a conduit for Thanar's power.");
    add_ask(({"about quest","quest", "quests", "task", 
            "tasks", "help"}), help_response,1);
    add_ask(({"about thanar", "thanar", "religion",
            "order"}), thanar_response,1);



} /* create_thanar_living */

/*
 * Function name: help_response
 * Description  : Gives a response 
 * Returns      : a string with the response
 */
string
help_response()
{
    if(TP->query_race_name() != "human" && TP->query_race_name() != "saurian"
        || TP->query_race_name() != "goblin")
    {
        command("say You stand within the Cathedral of the great and "
            +"omnipotent Thanar. You are welcome to gaze upon the glory of "
            +"this place.\n");
        command("emote frowns.");
        command("peer warily " + OB_NAME(TP));
        return "\n";
    }
    if(TP->query_race_name() == "saurian" || TP->query_race_name() == "goblin")
    {
        command("say You foul beast. How do you come to be here. "
            +"You and your kind seek only to steal the power we hold by Divine "
            +"right.\n"
            +"BEGONE!\n");
        command("kill " + OB_NAME(TP));
        return "\n";
    }
    //To add a response for a Thanar guild member.
    return "say I do not have time for you!\n";
} /* help_response */

/*
 * Function name: thanar_response
 * Description  : Gives a response 
 * Returns      : a string with the response
 */
string
thanar_response()
{
    if(TP->query_race_name() != "human" && TP->query_race_name() != "saurian"
        || TP->query_race_name() != "goblin")
    {
        command("say You stand within the Cathedral of the great and "
            +"omnipotent Thanar. You are welcome to gaze upon the glory of "
            +"this place.\n");
        command("emote frowns.");
        command("peer warily " + OB_NAME(TP));
        return "\n";
    }
    if(TP->query_race_name() == "saurian" || TP->query_race_name() == "goblin")
    {
        command("say You foul beast. How do you come to be here. "
            +"You and your kind seek only to steal the power we hold by Divine "
            +"right.\n"
            +"BEGONE!\n");
        command("kill " + OB_NAME(TP));
        return "\n";
    }
    //To add a response for a Thanar guild member.
    return "say The Thanarian order is dedicated to the worship of his Lord "
        +"Thanar, the patron saint of humanity. We stand to show that the Human "
        +"race is the most fit to rule Kalad by Divine Right. As a human you "
        +"should join us.\n";
} /* thanar_response */



/*
 * Function name: attacked_by()
 * String       : the object attacking (ob)
 * Description  : Determines who is attacking and gives a response.
 *                
 */
void
attacked_by(object ob)
{
    if (!ob->query_prop(I_KILLED_PRIESTS))
        ob->add_prop(I_KILLED_PRIESTS, 1);

    command("say Heretic! Thanar shall grant me the power to destroy you!");
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
    command("say Thanar grant me peace and smite my foe.");
    command("emote attempts to pray through gurgling blood.");

    if (killer->query_race_name() != "human")
    {
        this_object()->set_alignment(0);
    }

    /*This section decides whether a quest item drops or not. 20% chance for
     * for each of the four pieces.*/

    int meddrop = random(100);

    switch (meddrop)
    {
    case 1..20:
        tell_room(environment(), "You hear a metallic clank as the corpse falls. This "
            +gender_race+" must have been carrying a piece of the medallion.\n");
        seteuid(getuid(this_object()));
        object medallion;
        medallion = clone_object(OBJ + "lower_left_shard");
        medallion->move(TO, 1);
        break;

    case 21..40:
        tell_room(environment(), "You hear a metallic clank as the corpse falls. This "
            +gender_race+" must have been carrying a piece of the medallion.\n");
        seteuid(getuid(this_object()));
        object medallion2;
        medallion2 = clone_object(OBJ + "lower_right_shard");
        medallion2->move(TO, 1);
        break;

    case 41..50:
        tell_room(environment(), "As the "+gender_race+" slumps to the floor, dead, some "
            +"coins jingle within the folds of their robes.\n");
        this_object()->add_prop(OBJ_M_HAS_MONEY, (random(1440)));
        break;

    case 51..70:
        tell_room(environment(), "You hear a metallic clank as the corpse falls. This "
            +gender_race+" must have been carrying a piece of the medallion.\n");
        seteuid(getuid(this_object()));
        object medallion3;
        medallion3 = clone_object(OBJ + "upper_right_shard");
        medallion3->move(TO, 1);
        break;

    case 71..90:
        tell_room(environment(), "You hear a metallic clank as the corpse falls. This "
            +gender_race+" must have been carrying a piece of the medallion.\n");
        seteuid(getuid(this_object()));
        object medallion4;
        medallion4 = clone_object(OBJ + "upper_left_shard");
        medallion4->move(TO, 1);

    case 91..100:
        tell_room(environment(), "The "+gender_race+" slumps to the floor, dead.\n");
        break;

    default:
        tell_room(environment(), "The "+gender_race+" slumps to the floor, dead.\n");
        break;
    }

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
