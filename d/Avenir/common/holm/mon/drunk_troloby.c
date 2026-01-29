inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#define FIXEUID         setuid(); seteuid(getuid())

int flag;

void
create_monster()
{
    flag=0;

    set_name("a_drunk_troloby_from_the_troloby_camp");
    set_race_name("troloby");
    set_gender(G_FEMALE);
    set_adj("pale");
    set_adj("dirty");
    set_long("This troloby is leaning against a big rock and without any " + 
             "doubt she would probably fall over otherwise.\n" +
             "She is very dirty and extremely drunk.\nDespite her poor " +
             "condition you notice a desperate pride in her eyes.\n");

    set_stats( ({ 20, 20, 60, 30, 30, 10 }) );
  
    refresh_mobile();
  
    set_skill(SS_BLIND_COMBAT, 10);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 20);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT,60000);
    add_prop(OBJ_I_VOLUME,60000);
  
    set_act_time(5);
    add_act("hiccup");
    add_act("emote grins drunkedly and looks at you with a blank look in " +
            "her face.");
    add_act("emote suddenly sways back and forth and with great effort " +
            "she manages to stay on her feet."); 
    add_act("emote squints her eyes at you.");
    add_act("emote wobbles a bit against the rock.");
       
    set_chat_time(6);
    add_chat("Are you one of them infidelsch?"); 
    add_chat("Hey, you better get out of here before the wizard makesch " + 
             "a poschion outta you.");
    add_chat("You shouldn't drink and fight.");  
    add_chat("Schelebrate the schource.");

    set_cchat_time(4);
    add_cchat("Help!");
   
}

public void
arm_me()
{
    object leather_tunic;

    setuid();
    seteuid(getuid());
    leather_tunic = clone_object("/d/Avenir/rangorn/temp/leather.c");
    leather_tunic->move(this_object());
    command("wear all");
}



