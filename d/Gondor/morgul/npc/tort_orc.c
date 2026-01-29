/*
 * /d/Gondor/morgul/npc/tort_orc.c
 *
 * Stern, August 2000, based on Olorin's ithil_orc.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({ WEP_DIR + "orc_wep/saw_knife" })
#define WEP_ARRAY2 ({})
#define ARM_ARRAY1 ({ "/d/Gondor/ithilien/obj/apron" })
#define ARM_ARRAY2 ({})
#define ARM_ARRAY3 ({})

public void
create_ithil_orc()
{
}

nomask void
create_ithil_monster()
{
    int     rnd = random(31);
 
    set_short("fat indifferent orc");
    set_pshort("fat indifferent orcs");
    set_name("orc");
    add_name("torture_orc");
    set_pname("orcs");
    set_race_name("orc"); 
    set_adj("fat");
    set_adj("indifferent");
    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," ")))
       +  " orc with short crooked legs and long arms that hang almost "
       +  "to the ground. He has a cruel look in his eyes."));
    
    default_config_npc( 45 + rnd / 3);
    set_base_stat(SS_INT, 25 + rnd / 2);
    set_base_stat(SS_WIS, 25 + rnd / 2);
    set_base_stat(SS_DIS, 55 + rnd / 6);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  45 + rnd / 3);
    set_skill(SS_WEP_CLUB,   45 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  45 + rnd / 3);
    set_skill(SS_PARRY,      45 + rnd / 2);
    set_skill(SS_DEFENCE,    45 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* don't flee from the torture room */

    set_chat_time(4 + random(4));
    add_chat("Curse you!");
    add_chat("Scream all you want!");
    add_chat("You'll catch the Nine's attention with all your screaming!");
    add_chat("Lugburz wants it, we do it!");
    add_chat("Ready to tell the truth yet?");
    add_chat("Louder! The Nine appreciate the sounds of despair!");
    add_chat("You are the most pathetic elf I ever had the " +
             "pleasure to torture!");
    add_chat("No stamina, these elves.");
    add_chat("Now don't you die on me!");
    add_chat("What do you want? The rack or the Maiden?");
    add_chat("Clean up those stains!");

    set_cchat_time(5 + random(10));
    add_cchat("I'll cut you to pieces!");
    add_cchat("Curse you, you little maggot!");
    add_cchat("Come here, and I'll put you on the rack!!");
    add_cchat("Stand still and let me use these spikes on you!");
    add_cchat("What are you doing here?!?");
    add_cchat("Leave, before I put you next on my list.");

    set_act_time(3 + random(5));	
    add_act("burp");
    add_act("hiss");
    add_act("grin");		
    add_act("fart");		
    add_act("leer threateningly at elf");	
    add_act("emote wipes some blood from his hands.");	
    add_act("emote wipes some blood from the floor.");	
    add_act("torture lentil");	
    add_act("kick lentil");	
    add_act("knee lentil");	
    add_act("emote walks around his prisoner thinking of what to do next.");
    add_act("emote searches through the instruments on the table.");	
    add_act("polishes a spiked chain.");	
    add_act("emote caresses the Iron Maiden with a dreamy look on his face.");
    add_act("emote wipes some blood from Lentil's body with a dirty cloth.");
    add_act("emote picks his nose and eats the contents.");	

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("@@enemy_emote|kick@@"); 
    add_cact("@@enemy_emote|snarl@@"); 
    add_cact("@@enemy_emote|glare@@"); 

    create_ithil_orc();
}

static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;
}

public void
orc_leave()
{
    set_alarm(0.5,0.0,&command("emote wipes his hands and departs, " +
        "figuring his work is done."));
    set_alarm(1.0,0.0,&remove_object());
}

