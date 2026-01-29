inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

//   Prototypes
void return_introduce(string who);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;	

    set_living_name("overhill");
    set_name("overhill");
    set_title("Took, questmaster of Bree");
    set_race_name("hobbit");
    set_short("old hobbit");
    set_long("This is one of the elderly hobbits living in Bree. It looks like "
    	    +"he has been out travelling and adventuring a lot.\n");
    set_adj(({"serious","old"}));
    set_stats(({30,30,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    trig_new("%w 'introduces' %s","react_introduce");

    set_alarm(1.0,0.0,"arm_me");    
}

arm_me()
{
    object tunic;
    
    FIXEUID;

    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
    tunic->move(TO);
    command("wear all");
   
}

int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0,0.0,&return_introduce(who));
        return 1;
    }
}

void
return_introduce(string who)
{
    object obj;
    int    ran;
    
    if (obj = present(who,environment()))
    {
        ran = random(3);
        if (ran == 0)
        {
            command("say Good day " + obj->query_name() +", are you seeking help here?");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("say Welcome " + who +", can i help you with something?");
            command("smile serious " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings " + who + ".");
            command("bow deeply to " + who);
        }
    }
}
