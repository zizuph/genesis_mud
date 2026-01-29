/* /d/Faerun/mere/npcs/quest_npc4/
 * 
 *
 * Nerull 2019
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <options.h>
#include <filter_funs.h>
#include "/d/Faerun/guilds/fire_knives/guild.h"

void arm_me();

// Spawn locations
string *spawn_locations = ({
    "/d/Faerun/highroad/rooms/htr14",
    "/d/Faerun/highroad/rooms/htr09",
    "/d/Faerun/underdark/dark_dom/rooms/tu23",
    "/d/Faerun/underdark/dark_dom/rooms/tu12",
    "/d/Faerun/underdark/dark_dom/rooms/tu57",
    "/d/Faerun/highroad/rooms/htr03",
    "/d/Faerun/highroad/rooms/krd03",
    "/d/Faerun/highroad/rooms/srd17",
    "/d/Faerun/highroad/rooms/srd13",
    "/d/Faerun/highroad/rooms/srd09",
    "/d/Faerun/mere/rooms/me31",
    "/d/Faerun/mere/rooms/me26",
    "/d/Faerun/mere/rooms/me05",
    "/d/Faerun/mere/rooms/me08",
    "/d/Faerun/mere/rooms/metrail3",
    "/d/Faerun/highroad/farms/farm01/rd03",
    "/d/Faerun/highroad/farms/farm02/yard",
    "/d/Faerun/highroad/rooms/nrd03",
    "/d/Faerun/highroad/rooms/nrd09",
    "/d/Faerun/halflings/rooms/path02",
    "/d/Faerun/halflings/rooms/rd02",
    "/d/Faerun/highroad/rooms/beach03",
    "/d/Faerun/highroad/rooms/herb_cottage",
    "/d/Faerun/kryptg/rooms/forest/kr43",
    "/d/Faerun/kryptg/rooms/forest/kr22",
    "/d/Faerun/kryptg/rooms/forest/kr08",
    "/d/Faerun/kryptg/rooms/forest/kr18",
    "/d/Faerun/kryptg/rooms/forest/kr48",
});


/*
 * Function name:        move_dragon()
 * Description  :        Moves the dragon to either lair or other area.
 */
void move_me()
{
    tell_room(environment(this_object()), QCTNAME(this_object())
    +" wanders out.\n");
    
    this_object()->move_living("M", 
    spawn_locations[random(sizeof(spawn_locations))], 1);
    
    tell_room(environment(this_object()), QCTNAME(this_object())
    +" wanders in.\n");

    return;
}


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    set_name("_quest_npc4_");
    add_name("kruppe");
  
    set_adj("talkative");
    add_adj("small");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("talkative small male human");
    
    set_long("The small, talkative round man with short, oily, "
    +"curley hair, pencil-thin eyebrows and a round, "
    +"shiny face is apparently as harmless as he is "
    +"joyfully talkative. His girth prevents him from "
    +"entirely clasping all the buttons of his waistcoat, "
    +"and his wide, flopping stained sleeves are gathered "
    +"at the cuffs and lined inside with pockets of all "
    +"sizes. He is wearing a faded red waistcoat with "
    +"tattered tails and a broad brimmed hat.\n");

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 190);

    set_stats(({ 150, 140, 160,
                 143, 120, 180 }));

    set_hitloc_unarmed(A_HEAD, 45, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 45, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 45, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 45, 45, "body");
    set_hitloc_unarmed(A_LEGS, 45, 20, "legs");

    set_attack_unarmed(W_LEFT,  25, 25, W_BLUDGEON,
    80, "left fist");

    set_attack_unarmed(W_RIGHT,  25, 25, W_BLUDGEON,
    80, "right fist");
    
    set_attack_unarmed(W_FOOTR, 25, 25, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 25, 25, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,60);
    set_skill(SS_WEP_KNIFE,80);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_PARRY,70);
    set_skill(SS_AWARENESS,70);
    
    set_act_time(5);
    set_cact_time(5);
    add_act("emote takes out a silk handkerchief and "
    +"wipes the sweat off his brow.");
    
    add_act("emote says: Fat with sloth and neglect, some say, "
    +"is Kruppe, ohhh, and inclined to excess, he "
    +"is, clumsy, perhaps, some say.");
    
    add_act("emote proclaims: Such is the irony of life, "
    +"that one learns to distrust the obvious, surrendering "
    +"instead to insidious suspicion and confused conclusions. "
    +"But, is Kruppe deceived? Can an eel swim? Hurrah! These "
    +"seeming muddy waters are home to Kruppe, and his eyes are "
    +"wide with wonder!");
    
    add_act("emote waves his hand and says: Carelessly "
    +"constructed, Kruppe allows, yet none if you have ever "
    +"seen Kruppe dance! He glides like an unbroken "
    +"egg on a greased skillet.");
    
    set_cchat_time(5);
    add_cchat("Help! Somebody help me!");
    add_cchat("What have I ever done to you??");
    
    set_aggressive(0);
    
    set_random_move(8);
    
    arm_me();
}


mixed 
query_option(int opt) 
{
    return (opt == OPT_UNARMED_OFF); 
}


void
arm_me()
{
    object wep;

    wep = clone_object(FIREKNIVES_GUILD_DIR + "obj/kruppe_dagger");
    wep -> move(this_object(), 1);
    
    command("wield weapons");
    
    set_alarm(10.0, 0.0, &move_me());
}


/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks
 *                  we died.
 * Arguments:       object killer: The enemy that caused our death.
 *
 * This handles the various random drops aswell when the monster
 * is killed.
 */
void
do_die(object killer)
{
    if (killer->query_prop(FIREKNIVES_ON_GURUQUEST))
    {
        clone_object(FIREKNIVES_GUILD_DIR + "obj/quest_item4")->move(this_object(), 1);
    }

    ::do_die(killer);
}
