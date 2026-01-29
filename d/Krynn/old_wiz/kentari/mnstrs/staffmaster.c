/*
 * Gelnor the Gruff
 * modified from Sasha of Solace
 * by Kentari
 * January,'97
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE

inherit "/std/act/domove";     /* Allows Gelnor to move */
inherit "/std/act/action";     /* Allows Gelnor to act  */

#define OBJ "/d/Krynn/wayreth/obj/"

public void
create_krynn_monster()
{
    string str;

    set_name("gelnor");
    set_living_name("gelnor");
    set_race_name("human");
    set_title("the Gruff, Staffmaster of Wayreth");
    set_long("This hardened man has dark brown hair tied back in a " +
	"pony tail, penetrating brown eyes, a crooked nose that must " +
	"have broken and not set straight, and a scruffy beard. As " +
	"Staffmaster, he is here to help train those of the Tower to " +
	"use their staffs as something other than a walking stick and " +
	"teach scholarly mages some of the more worldly skills needed " +
	"outside the protection of the Tower. Though possessing a gruff " +
	"manner, this warrior holds only the deepest respect for the " +
	"Wizards of High Sorcery.\n"); 
    add_name(({"the gruff","staffmaster","master","man"}));
    set_adj("coarse");
    add_adj("fluid"); 
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);
    set_alarm(1.0,0.0,"arm_me");
    set_introduce(1);

    set_stats(({100,120,95,60,85,100}));
    set_skill(SS_DEFENCE,        70);
    set_skill(SS_PARRY,          70);
    set_skill(SS_BLIND_COMBAT,   70);
    set_skill(SS_AWARENESS,      90);
    set_skill(SS_UNARM_COMBAT,   80);
    set_skill(SS_WEP_POLEARM, 	101);

    set_alignment(100);
    set_knight_prestige(-2);

    set_default_answer("Gelnor grunts: I've no idea what you're talking " +
	    "about, just let me know when you want to train.\n");
   
    add_ask(" [about] 'appraise' / 'enemy' / 'monster' / 'value' / " +
	"'objects' / 'appraising'",
            "Gelnor says: You must know the strength of those you " +
	    "encounter, or their lack of it. Without knowing what " +
	    "to look for, you will grossly under or overestimate " +
	    "others, which would be a grave mistake indeed. You " +
	    "should also learn what to notice in objects, to " +
	    "optimize what you can carry into battle, and the " +
	    "values of things to sell in the stores.\n");
    add_ask(" [about] 'polearm' / 'staff' / 'pole'", "Gelnor grins " +
	    "and says: Polearms, such as staffs, are not only a " +
	    "Wizard's support, but deadly weapons when used in the " +
	    "right hands. Personally, I've devoted myself to " +
	    "mastering the simple looking stick, and in doing so, " +
	    "found my calling in life. I'd gladly share what I can " +
	    "with you to aid your mastery of the staff.\n");
    add_ask(" [about] 'awareness'", "Gelnor replies: How will you even " +
	    "think of casting spells to reveal someone, if you lack the " +
	    "awareness to know they are near? Let me help you sharpen " +
	    "your senses.\n");
    add_ask(" [about] 'quest' / 'task'","Gelnor says: Well, I have my " +
            "Valenwood staff and my wits, so at the moment there's " +
	    "not much you can do for me, but thanks for offering.\n");

    set_act_time(5);
    add_act("emote polishes his staff with a white cloth.");
    add_act("emote twirls his staff around in an impressive, " +
	    "yet lethal dance of practice forms.");
    add_act("say Don't just stand there, lets train!");
    add_act("emote looks you over with penetrating eyes, as if " +
            "judging your aptitude for combat.");
    add_act("emote scratches his chin thoughtfully.");
    add_act("say Spells can be ever so useful, but what're you " +
	    "gonna do when you've exhausted your mind?");

    set_cact_time(4);
    add_cact("shout You dare attack me?!? Well you better finish the job " +
	     "'cause I'll be hunting your ass down if you don't!");
    add_cact("say Someone will have their revenge on you, fool!");
    add_cact("emote tries to protect himself with his twirling staff."); 
    add_cact("write You get the feeling that Gelnor has raised some " +
	     "some sort of magical alarm and reinforcements may be " +
	     "on the way!");
}  

public void
arm_me()
{
    clone_object(OBJ + "vstaff")->move(TO);
    clone_object(OBJ + "ptunic")->move(TO);
    clone_object(OBJ + "pleggings")->move(TO);
    command("wear all");
    command("wield all");
}

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Gelnor the Gruff", killer);
    return 0;
}
