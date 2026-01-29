/*
 * Phlan city guard leader
 * Tharizdun, 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <defs.h>

inherit "std/monster.c";
inherit "/d/Genesis/lib/intro";

#define KILT  ARM + "kobold_kilt"
#define DAGGER  WEP + "kobold_dagger"

#define TYPE ({"a", "b", "c"})
#define PHYS ({"a", "b", "c"})
#define EYES ({"a", "b", "c"})
#define SKIN ({"a", "b", "c"})
#define HORNS ({"a", "b", "c"})

void arm_me(); 

void create_monster()

{
    string type, phys, eyes, skin, horns;
    int i;

    seteuid(getuid());
    type = one_of_list(TYPE);
    phys = one_of_list(PHYS);
    eyes = one_of_list(EYES);
    skin = one_of_list(SKIN);
    horns = one_of_list(HORNS);
 
    string npc_name = "kobold";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name(npc_name);
    set_name(gender_race);    
    set_short(type +" "+ phys + " " + gender_race);
    add_name(npc_name);
    set_gender(random(2));
        
    set_long("Both reptillian and dog-like, this "+type
        +" "+phys+" "+gender_race+" is intent on killing and torturing"
        +" pretty much any living thing it can catch. "+CAPheshe+" has "+skin+" skin, "
        +eyes+" eyes, and a pair of "+horns+" horns protruding from "+hisher+" forehead."
        +CAPheshe+" is a member of the Amber Kilts tribe of kobolds as indicated by the"
        +" yellowish-orange garment "+heshe+" wears.\n");
        
/*
*   size and skills
*/          
        
    add_prop(CONT_I_WEIGHT, 10000 + ramom,(9000));
    add_prop(CONT_I_HEIGHT, 90 + random(20));
                
    add_prop(LIVE_I_SEE_DARK, 20);

    for(i = 0; i < 6; i++)
        set_base_stat(i, 7 + random(20));

    set_skill(SS_WEP_KNIFE, 10 + random(10));
    set_skill(SS_PARRY, 10 + random(10));
    set_skill(SS_DEFENCE, 10 + random(10));
    set_skill(SS_AWARENESS,30);    

    set_alignment(-150 + random(50));
 
/* 
*   Actions 
*/

    set_act_time(25);
    add_act("emote yips Who are you?");
    add_act("emote barks You should leave!");
    add_act("emote flicks his tail suspiciously.");

    set_cact_time(10);
    add_cact("emote barks viciously!");
    add_cact("emote raises its lips in a snarl exposing small sharp teeth.");    
    
    arm_me(); 
}

void

/*
*   adding gear
*/

arm_me()

{
    seteuid(getuid(this_object()));
    equip(({
        KILT,
        DAGGER,
    }));   

}

/* 
*   Teaming
*
*
*   void
*   init_living()
*   {
*       ::init_living();
*       init_team_pickup();
*   }
*/
