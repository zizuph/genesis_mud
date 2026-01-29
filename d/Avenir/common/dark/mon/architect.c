// architect for the utterdark
// formerly foreman_s.c
// Cloned at: /d/Avenir/common/dark/l2/n6.c
// Lilith, Nov 2021
// revisions:  Lilith Feb 2022, added asks

#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/room_creator";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/sigil";
inherit "/d/Avenir/inherit/hair_eyes";

#include "/d/Avenir/include/relation.h"
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include "../dark.h"


int alarm_id, check_alarm, am_busy;


public string
ask_seq(string *ask, int count = 0, object tp = TP)
{
    set_this_player(tp);  
  
    if (count == 0 && am_busy)
    {
        command("emote is too busy to answer right now.");
        return "";
    }
        
    am_busy = 0;

    if (ENV(TO) != ENV(tp))
        return "";
        
    command(ask[count]);
    
    if (++count != sizeof(ask))
        am_busy = set_alarm(2.5, 0.0, &ask_seq(ask, count, tp));
    
    return "";
}

public string
default_answer(void)
{

    switch(random(4))
    {
    case 0:
        command("say to "+ OB_NAME(TP) +" That doesn't interest me.");
        break;
    case 1:
        ask_seq(({"frown", "say to "+ OB_NAME(TP) +" Is that some kind of "+
        "Outlander thing?"}));
        break;
    case 2:
        ask_seq(({"think stupid questions. ", "say to "+ OB_NAME(TP) +
        " I have nothing to say about that."}));
        break;
    default:
        ask_seq(({"grumble", "say It is too dangerous here to allow myself "+
        "to by distracted by your chit-chatting. Sorry."}));
        break;
    }

    return "";
}


private string
ask_quest()
{
    ask_seq(({"smile .", "say to "+ OB_NAME(TP) +" I am on a quest of my "+
        "own.", "say I want to bring some fresh ideas home to build "+
        "upon.", "say Ask me 'building' if you're interested in "+
        "helping me."}));     
    return "";     
}

private string
ask_secret()
{
    ask_seq(({"gasp", "say to "+ OB_NAME(TP) +
        " Trust me, some secrets should be kept secret."}));        
    return "";
}

private string
ask_maivia()
{
    ask_seq(({"sigh .", "say Those dark elves really don't like me being "+
        "here.", "say Maivia is the worst. If you want to deal with him "+
        "you'll find him on the first level of the Utterdark, in the "+
	    "southeast corner.", "say Just don't tell him I sent you."}));
    return "";	
	
}

private string
ask_isle()
{
    ask_seq(({"say The Necronisi, or Isle of the Dead, is where the bodies "+
        "of the dead of Sybarus are disposed.", "You can get to it from the "+
        "north end of the bazaar island."})); 
     return "";
}

public string
query_long()
{
    string res;

    if (!notmet_me(TP))
    {
        res = TO->query_name() + " is " +
            LANG_ADDART(TO->query_nonmet_name()) +
            ", presenting " + TO->query_objective() + "self as:\n" +
            TO->query_presentation() + ".\n";
    }
    else if (!(TO->short(TP)))
    {
        return "";
    }
    else
    {
        res = CAP(TO->query_pronoun()) + " is " +
            LANG_ADDART(TO->short(TP)) +".\n";
    }

    res += "She is an architect from Sybarus surveying the tunnels of the "+
          "Utterdark.\nShe is looking for ideas to build.\n"+
         "Her hair is dark as coal and her skin is so pale you're certain "+
		 "she has never seen daylight.\n"+
		 "She has hazel eyes that look around her with wonder.\n";

    return res;
}

static void
check_meet(object who, string oname)    {  }

private nomask void
init_meet(object who)
{
    check_alarm = 0;

    if (objectp(who) && present(who, environment()))
        check_meet(who, OB_NAME(who));
}

public void
init_living(void)
{
    ::init_living();

    if (!check_alarm &&
        query_interactive(TP) && CAN_SEE(TO, TP))
    {
        float delay = 1.5 + itof(random(2));
        check_alarm = set_alarm(delay, 0.0, &init_meet(TP));
    }
}


void
create_monster()
{
    if (!IS_CLONE)
	return;

    reset_euid();
    ::create_sybarite();
	
	set_title("icu Tirisi, Architect of Sybarus");
	set_syb_house("Tirisi");
    set_name("anyadela");
    add_name(({"faithful", "sybarite", "architect"}));
    set_adj(({"industrious", "enthusiastic"}));
    set_race_name("human");
    set_gender(G_FEMALE);
	
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_HEIGHT, 200);
	add_prop(LIVE_I_NON_REMEMBER, 1);

    set_appearance_offset(-30);
    set_alignment(0);
    set_stats(({ 80+random(60), 85+random(15), 80+random(50),
                 90+random(50), 80+random(50), 80+random(50) }));

    set_skill(SS_LANGUAGE,      40);
    set_skill(SS_WEP_KNIFE,     50 + random(40));
    set_skill(SS_WEP_SWORD,     50 + random(40));
    set_skill(SS_PARRY,         55);
    set_skill(SS_ACROBAT,       60);
    set_skill(SS_AWARENESS,     75);
    set_skill(SS_DEFENCE,       50);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_BLIND_COMBAT,  55);

    set_default_answer("@@default_answer@@");	
    add_ask(({"quest", "task", "job", }), ask_quest, 1);
    add_ask(({"secret"}), ask_secret, 1);	
    add_ask(({"god", "gods", "idrys"}), 
	    "say They make everything possible.", 1);	
	add_ask(({"dark elves", "maivia", "dark elf captain"}), ask_maivia, 1);
    add_ask(({ "[about] [the] [shadow] 'union' [of] [warriors]"}),
        "say They are the Many who are One, united in the effort to "+
        "protect Sybarus from all threats, external and internal.", 1);
    add_ask(({"[about] [the] 'necronisi'"}), ask_isle, 1);
	add_ask(({"[about] [the] 'isle' [of] [the] [dead]"}), ask_isle, 1);
    add_ask(({"[about] [the] 'undead' [on] [the] [necronisi]"}),
		"say The infidels become undead wandering the marshes, an army "+
        "awaiting the chance to redeem themslves by answering the call "+
		"to defend the shores of Sybarus. They are terrible foes.", 1);
    add_ask(({"[about] [the] 'catacombs'"}), 
	    "say Only the Faithful may rest "+
        "within the catacombs. It is there where we await rebirth. Some "+
		"dead even wander there, as Mascarvin wishes.", 1); 
    add_ask(({"[about] [the] 'vampire' / 'vampires'"}),
        "say I heard they are undead, but know an unlife different from "+
        "the undead on the Necronisi.", 1);
    add_ask(({"[about] [the] [goddess] 'mascarvin'"}),
        "say She is the Goddess of Death and Rebirth, the one who gathers "+
		"us to her breast and nurtures us until it is time for rebirth.", 1);
    add_ask(({"[about] [the] [goddess] 'sair'"}),
	    "say Sair is the goddess of walls. She keeps them from crumbling "+
        "down on us.", 1);
    add_ask(({"plalgus"}),
        "say He is the God of Judgement. Fear his hammer.", 1);
    add_ask(({"[about] [the] 'halls' 'of' 'shadow'"}),
	    "say They are here, in the Deep. A more beautiful place is "+
        "difficult to find. It inspires me to be a great architect "+
		"one day.", 1);
	add_ask(({"[about] [the] [gneiss] 'gnomes'"}),
        "say They are such talented jewelers! I sent samples to the "+
		"Inquisitors. Perhaps we will find a way to incorporate them "+
        "into Sybarus. They've been isolated for a long time.", 1);
    add_ask(({"[about] [the] 'albi' / 'albus'"}),	
        "They are albino goblins living down on the second level, not "+
        "far from the gneiss gnomes. They are afraid of strangers and "+
        "aggressive, so be careful.", 1);
    add_ask(({"[about] [the] 'hobgoblin' / 'hobgoblins'"}),	
        "I heard hobgolins are supposed to be bigger than regular goblins "+
        "but the ones I found in the southeast of level one are tiny. "+
        "Maybe they call themselves hobgoblins to scare the dark elves "+
        "off?", 1);		
		
    set_act_time(30);
    add_act("say Its important to make sure these tunnels remain passable.");
    add_act("say We need more Sair-marks on these tunnel walls.");
    add_act("say There are many possibilities here.");
    add_act("say I should get the stone cutters to come collect a few "+
        "blocks here.");
    add_act("emote examines a crack in the tunnel wall.");
    add_act("emote writes something on some vellum.");
    add_act("emote examines the wall.");
    add_act("say The Gods provide for us as we Deserve.");
    add_act("say I'm looking for help on building something new and "+
       "different.");	
	set_cact_time(4);
	add_cact("say May Plalgus smite thee, fool!");
	add_cact("say I will laugh at you from my resting place in the Cataombs.");
	add_cact("say Mascarvin will come for me when I die, and I will return.");
    	
	
    // path to which we will write out our generated rooms
    set_room_path ("/d/Avenir/common/dark/submissions/");
    // path to which we will log room creations
    set_room_log_file ("/d/Avenir/common/dark/submissions/sublog");
    // reset all variables
    reset_room_creator ();
    // allow the player to obtain help by asking
    set_room_creation_ask_help();
    set_room_includes (({ "\"defs.h\"" }));
    set_min_room_items(2);
    set_min_room_cmd_items(2);
	

}

void
equip_me()
{
    object obj;
	
    equip("/d/Avenir/common/bazaar/museum/obj/pad"); 	
    equip("/d/Avenir/common/dark/obj/d_clothes");
	equip("/d/Avenir/common/dark/obj/knife");
	equip("/d/Avenir/common/obj/torch");
    obj = clone_object("/d/Avenir/common/bazaar/Obj/misc/poet_pen");
    obj->randomize();
    obj->move(this_object(),1);
	command("wield all");
}


/*
 * React to introductions.
 */
static void
return_intro(object who, string oname)
{
    if (IS_INFIDEL(who))
        return;

    command("introduce me to "+ oname);
    command("say to "+ oname +" Celebrate the Source!");
}


string race_sound()
{
   string *strs = ({ "says with a sybarite lilt" });

   return strs[random(sizeof(strs))];
}

int valid_help(object ob)
{
    if(interactive(ob) || !ob->id("troll") || ob->query_attack())
        return 0;

    return 1;
}

int special_attack(object enemy)
{
    object   *people;

    switch (random(7))
    {
        case 0: command("punch enemy");
            return 1;
        case 1: command("neck enemy");
            return 0;
        case 2: command("punch enemy");
            return 0;
        case 3: command("pommel enemy");
            return 0;
        case 4: command("heal me");
            return 1;
        default:
            command("slaugh");
    }

    people = filter(all_inventory(ENV(TO)), valid_help);

    if (!sizeof(people))
        return 0;

    call_other(people, "command", "kill " + enemy->query_real_name());
        return 0;
}
