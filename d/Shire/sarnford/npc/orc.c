/*
* Varian - February 2015
*/

inherit "/std/monster";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"


int alarm_id;

string physlook();
string emotelook();

create_monster()
{
    if (!IS_CLONE)
        return;

    set_race_name("orc");
    
    set_stats(({10, 12, 10, 5, 5, 15}), 50);
    MAKE_MONEY;
    set_alignment(-50);
    
    set_adj(({emotelook(),physlook()}));

    set_skill(SS_WEP_KNIFE,30);
    set_skill(SS_WEP_SWORD,30);
    set_skill(SS_WEP_AXE,30);
    set_skill(SS_WEP_POLEARM,30);
    set_skill(SS_WEP_CLUB,30);
    set_skill(SS_PARRY,20);
    set_skill(SS_DEFENCE,20);

    set_gender(G_MALE);

    set_chat_time(12);
    
    add_chat("I hate hobbits! We should kill them all!");
    add_chat("Those nasty elves, I hopes the boss lets us kill some!");
    add_chat("I have had enough of those humans, lets exterminate 'em!");
    add_chat("There is nothing I hate more than dwarves!");
    add_chat("Wait, wait, wait! I'm tired of waiting, when do we kill something?");
    add_chat("Does anyone really know why the boss wants us out here?");
    add_chat("I am bored of this, time to go raid those pesky humans!");
    add_chat("Roast hobbit sure is tasty! I hope we get to have some more soon.");
    add_chat("I hopes the boss makes up his mind soon. It gets boring out here.");
    add_chat("What should we do now boys?");
    add_chat("Sarn Ford? Just what is a ford anyways, does anyone know?");
    add_chat("I hates this I does!");
    add_chat("Enough is enough, time to go a raiding again boys!");
    
    set_act_time(2);

    add_act("snarl");
    add_act("cough");
    add_act("pick");
    add_act("cackle insane");
    add_act("emote lets out a blood-curdling howl.");
    add_act("scream");
    add_act("emote picks some roast hobbit out of his teeth.");
    add_act("emote bares his teeth at you aggressively.");
    add_act("emote digs a dirty finger in his ear in an attempt to clean it.");
    add_act("emote doubles over with a hacking cough, before spitting out a gooey, black lump.");
    add_act("spit");
    add_act("emote howls wildly at the moon.");
    add_act("swear");
    add_act("curse");
    add_act("emote wanders around in circles, muttering angrily under his breath.");
    add_act("emote starts playing with his weapon, eagerly looking for a new target.");
    add_act("emote suddenly lifts his head and begins to sniff at the air.");
    
    set_cact_time(5);

    add_cact("emote snarls viciously at you.");
    add_cact("emote screams: Here's a fresh one boys! Get 'em!");

    set_cchat_time(3);
    add_cchat("Let's see how you like this!");
    add_cchat("After I kill you, I'm going to cook your corpse for dinner!");
    add_cchat("You don't know who you are messing with!");

    set_alarm(0.5,0.0,"arm_me");

}

void   

arm_me()
{
    object sword,mail,greaves,gloves,helm,boots,shield,cloak;

    FIXEUID;

    sword = clone_object("/d/Shire/sarnford/wep/orc_sword.c");
    mail = clone_object("/d/Shire/sarnford/arm/orc_mail.c");
    greaves = clone_object("/d/Shire/sarnford/arm/orc_greaves.c");
    gloves = clone_object("/d/Shire/sarnford/arm/orc_gloves.c");
    helm = clone_object("/d/Shire/sarnford/arm/orc_helm.c");
    boots = clone_object("/d/Shire/sarnford/arm/orc_boots.c");
    shield = clone_object("/d/Shire/sarnford/arm/orc_shield.c");
    cloak = clone_object("/d/Shire/sarnford/arm/orc_cloak.c");

    sword->move(TO);
    mail->move(TO);
    greaves->move(TO);
    gloves->move(TO);
    helm->move(TO);
    boots->move(TO);
    shield->move(TO);
    cloak->move(TO);
    command("wear all");

}

string
physlook()
{
    string *physlooks;
    physlooks = ({"ugly", "brutish", "yellow-skinned", "green-skinned",
        "hairy", "red-eyed", "fat", "scarred", "orange-skinned", "black-skinned",
        "tattooed", "milky-eyed", "long-fanged", "cross-eyed", "big-boned",
        "beady-eyed", "long-nosed", "big-eared", "bald", "drooling", "slobbering",
        "one-eared", "hunchbacked", "grey-skinned", "wide-shouldered", "sharp-eyed",
        "stinky", "long-legged", "thick-armed","dead-eyed", "wide-shouldered"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"angry,", "fierce,", "hungry,", "bloodthirsty,",
        "vicious,", "crazy,", "mean,", "cruel,", "deadly,", "dangerous,",
        "demonic,", "snarling,", "roaring,", "evil,", "ferocious,", "screaming,",
        "strong,", "muscled,", "growling,", "drunk,", "insane,", "mad,",
        "mean,", "murderous,", "nasty,", "raging,", "lazy,", "awkward,",
        "savage,", "sinister,", "terrifying,", "wicked,", "frothing,", "watchful,",
        "hateful,", "hate-filled,", "coughing,", "silent,", "gruesome,"});
    return emotelooks[random(sizeof(emotelooks))];
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should never have done that!");
    command("emote lets out a bestial roar as he draws his weapon!");
    command("wield all");
    command("wear all");
    command("emote rushes into combat with you.");
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("say Looks like we have meat tonight boys!");
    command("emote looks hungrily at the corpse.");
}
