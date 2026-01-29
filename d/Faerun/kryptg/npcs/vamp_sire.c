/*
 * Vampire sire of Kryptgarden
 * by Finwe, Oct 2007
 * Added bite, which poison's players temporarily, turning them undead.
 * Thanks Novo for the help!
 * Finwe, August 2008
 * Added battleaxe and updated equiping functions
 * Finwe, September 2017
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define UNDEAD_POISON   "/d/Faerun/kryptg/obj/undead_convert_poison"
#define BLOODSAMPLE     "_hunting_for_bloodsample"

#define GENESIS_TIMEKEEPER  "/d/Sparkle/area/city/lib/genesis_timekeeper"

#define BOOTS           (ARM_DIR + "vamp_boots")
#define ARMOUR          (ARM_DIR + "vamp_armour")
#define CAPE            (ARM_DIR + "vamp_cape")
#define SWORD           (WEP_DIR + "lifes")
#define BATTLEAXE       (WEP_DIR + "lifea")
#define DEF_WEAPON      (WEP_DIR + "scimitar")

int home = 1;

void arm_me();


void
vamp_move_me()
{
    object room = environment(this_object());   
    mixed * time_info = GENESIS_TIMEKEEPER->query_time(this_player());    
    string domain = lower_case(room->query_domain());   
    int hour = time_info[0];
    
    if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
    {
        if (home == 0)
        {
            tell_room(environment(this_object()), "The "+query_short()
            +" suddenly realizes the presence of sunlight, and transforms "
            +"into a bat and flies away!\n");  
            
            this_object()->move_living("M","/d/Faerun/kryptg/rooms/forest/vamphome",1);  
            
            home = 1;

            return;
        }
        
    }
    else
    {
        if (home == 1)
        {
            this_object()->move_living("M","/d/Faerun/kryptg/rooms/forest/kr23",1);       
            tell_room("/d/Faerun/kryptg/rooms/forest/kr23", "A "+query_short()
            +" suddenly emerge from the shadows of the night!\n");
        
            home = 0;

            return;            
        }      
    }        
    
    return;
}


nomask void create_monster()
{
    int i;
    string type, phys;

    seteuid(getuid());

    type = "terrible";
    phys = "pale-skinned";

    npc_name = FOR_NPC;

    set_race_name("vampire");
    set_name(npc_name);
    add_name("sire");
    add_name("_faerun_vampire_");
    add_name("vampire");
    add_name("undead");
    set_adj(type);
    set_adj(phys);
    set_short(type + " " + phys + " vampire");
    set_pshort(type + " " + phys + " vampires");
    set_long("This is a " + query_short() + ". He is a sire of vampires " +
        "and looks handsome. He looks strong with an angular shaped face. " +
        "His eyes are piercing and unlike other vampires, has a aura " +
        "of strength about him.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 250);
	add_prop(LIVE_I_SEE_DARK, 80);
	add_prop(LIVE_I_SEE_INVIS, 80);
    add_prop(LIVE_I_UNDEAD,100);

    set_gender(G_MALE);
    set_pick_up_team(npc_name);
    set_alignment(-300);

    set_stats(({190+random(50),
	    150+random(50),
		150+random(50),
		100+random(50),
		100+random(50),
		150}));

    set_skill(SS_DEFENCE,100);
    set_skill(SS_WEP_AXE,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT,100);

    arm_me();

    set_act_time(5);
    add_act("emote smiles captivatingly.");
    add_act("emote beckons you to come to " + HIM_HER(TO) + ".");
    add_act("emote wrings " + HIS_HER(TO) + " hands dangerously and hungrily.");
    add_act("emote growls threateningly.");
    add_act("emote licks his lips mysteriously.");
    add_act("emote closes his eyes, suddenly lost in thought, and smiles " +
        "evilly.");
    add_act("emote smiles charmingly, revealing two white pearlescent " +
        "fangs.");
    add_act("emote looks around the area, absentmindedly scratching one " +
        "of his fangs.");
    add_act("emote steps behind you. His hot breath can be felt on your neck.");
    add_cact("emote rises to his full height and power.");
    
    // Enable at release.
    set_alarm(10.0, 10.0, &vamp_move_me());
}


void
do_die(object killer)
{
    object vamp_obj;
    object bloodsample;
    
    object recipe;
    
    /*if (objectp(bloodsample = present("_quest_vampire_bloodsample", killer)))
    {
        ::do_die(killer);
        
        return;
    }*/

    // Starting object for vampires joining path
    if (killer->query_prop(BLOODSAMPLE) == 1)
    {
        clone_object("/d/Faerun/guilds/vampires/obj/bloodsample")->move(killer, 1);
        
        killer->catch_tell("You collect a sample of blood from the corpse.\n");
    }
    		
    ::do_die(killer);
}


void arm_me()
{
    object wep, gem, recipe;

    make_gems(TO,1);

    equip(({BOOTS, ARMOUR, CAPE}));
  

    switch(random(5))
    {
        case 0: case 2: case 4:
        {
            wep = clone_unique(SWORD, MAX_UNIQUE_ITEMS, 
                WEP_DIR + "scimitar");
            break;
        }
        case 1: case 3: case 5:
        {
            wep = clone_unique(BATTLEAXE, MAX_UNIQUE_ITEMS, 
                WEP_DIR + "mace");
            break;
        }
    }
    
    if (random(2) == 0)
    {
        recipe = clone_object("/d/Faerun/alchemy/recipes/dragonfire_recipe");
        recipe->move(this_object(), 1);
    }

    equip(wep);
}


int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;

    if (random(3))
        return 0;
        
    // Vampire will not use special attacks vs the dead.
    if (enemy->query_prop(LIVE_I_UNDEAD))
    {
        return 0;
    }

    hitresult = enemy->hit_me(500 + random(150), W_BLUDGEON, me, -1);
    how = " with little effect";
    if (hitresult[0] > 0)
        how = " lightly";
    if (hitresult[0] > 5)
        how = " with " + HIS_HER(TO) + " fangs, puncturing some exposed flesh";
    if (hitresult[0] > 10)
        how = " with " + HIS_HER(TO) + " fangs, leaving smudges behind";
    if (hitresult[0] > 15)
        how = " with " + HIS_HER(TO) + " fangs, leaving traces of blood behind";
    if (hitresult[0] > 20)
        how = " with " + HIS_HER(TO) + " fangs, leaving trickles of blood behind";
    if (hitresult[0] > 25)
        how = " with " + HIS_HER(TO) + " fangs so hard, that blood runs from the wounds";
    if (hitresult[0] > 30)
        how = " with " + HIS_HER(TO) + " fangs, so hard, the flesh is shredded";

    enemy -> catch_msg(QCTNAME(me) + " bites" + how + ".\n");
    tell_watcher(QCTNAME(me) + " bites " + QTNAME(enemy) + "!\n"+
        capitalize(enemy->query_pronoun()) + " is bitten"+
        how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1;
}


void
init_living()
{
    ::init_living();
    init_team_pickup();
}

