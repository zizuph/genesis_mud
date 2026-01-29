/* 
 *
 * Pirate for the pier in Mithas
 * Elmore, 28/4/00 
 *
 */ 
#include <options.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h";

inherit AM_FILE

/* prototypes */
string do_drink();
string face();

void
create_krynn_monster()
{ 
    object shadow_object;

    set_race_name("human"); 
    set_name("pirate");
    set_adj(face()); 
    add_adj("scarred"); 
    set_long("This human is dressed in dirty clothes. "+
             "His head and arms are filled with deep scars made "+
             "from some sort of cutting weapon. This dark hair "+
             "blows gently in the wind, as he gazes out towards the "+
             "Bloodsea.\n"+
             "He has wise black eyes.\n"+
             "He has scars on his left arm, right arm, nose and " +
	        "right eyebrow.\n"+
             "A faded tattoo of a steel sword adorns his right wrist. \n"+
             "A magnificent tattoo of a dead minotaur adorns his " +
	        "left wrist.\n");
    
    set_stats(({100,160,120,80,90,100}));
    set_alignment(-150);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);
    set_random_move(70); 
    
    set_act_time(random(20));
    add_act("say Soon, those pathetic cows will surrender their city to " +
            "us.");
    add_act("say I could really eat a nice minotaur steak.");
    add_act("emote inspects his cutlass carefully.");
    add_act("emote looks out towards the Bloodsea.");
    add_act("emote swings his cutlass through the air, testing it's balance.");

    // Set skills.
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 50);

    MONEY_MAKE(random(10) + 10,"silver")->move(this_object(),1);
    MONEY_MAKE(random(5),"gold")->move(this_object(),1);  
    clone_object(MWEP + "cutlass.c")->move(this_object(),1);
    clone_object(MWEP + "shortsword.c")->move(this_object(),1); 
    command("wield all");
    command("wear all");

    /* we inherit all those pirate things so we can stagger and such */
    shadow_object=clone_object("/d/Ansalon/guild/pirates/shadow/pirate_shadow");
    shadow_object -> add_lay_shadow(TO);
    set_alarm(10.0, 120.0, &do_drink()); // always intoxicated
}

string
face()
{
    // Set description.
    string *faces;
    faces = ({"one-eyed", "one-legged", "tall", "strong", "black-eyed"});
    return faces[random(sizeof(faces))];
}

int
query_option(int opt)
{
    if (opt == OPT_UNARMED_OFF)
    {
        return 1;
    }
    else
    {
        return ::query_option(opt);
    }
}

string
do_drink()
{
    // I don't bother to show anything to players, it is only to make him drunk
    TO->set_intoxicated(intoxicated_max());
    return "";
}
