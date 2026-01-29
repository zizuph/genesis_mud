//-*-C++-*-
// cleaning woman /d/Avenir/common/mon/cleaner.c    
// creator(s): Lilith, July 1997
// revised:
// purpose:    To clean up messes after killings  
// note:       The cleaning woman has many possible uses. The 
//             intended one is to clone as an intermediary npc
//             to an area after the original inhabitants have 
//             been killed.
// bug(s): 
// to-do:

inherit "/d/Avenir/inherit/spy_npc";

#include "/d/Avenir/include/defs.h"      /* Short-hand macros */
#include "/d/Avenir/include/paths.h"     /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"    /* ADD_SKIN, etc */
#include "/d/Avenir/include/relation.h"  
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* properties */
#include <wa_types.h>                    /* weapon and armour defs */
#include <ss_types.h>                    /* skill and stat defs */

int    kill_id;
string *randadj;
string *randes;
string my_long();

void
create_monster()
{
    randadj = ({"little", "dark-eyed", "tall", "sad", "busy", "tired",
                "slender", "wise", "angry", "dirty", "voluptuous",
                "willowy", "bruised", "concerned", "frightened", "plump",
                "secretive", "smiling", "wide-eyed", "innocent", "sweet",
                "pleasant", "ancient", "haggard", "exquisite", "gentle",
                "lovely"});
    randes = ({ " scrubbing the floor", " cleaning up", " mopping up blood",
                " sitting on her heels", " on her hands and knees"});

    set_name("cleaning woman");
    add_name(({"woman", "female", "servant", "slave"}));
    set_adj(randadj[random(sizeof(randadj))]);
    set_race_name("human");
    set_gender(G_FEMALE);
    set_long(my_long);
    set_stats(({60,60,60,40,40,50}));
 
    set_alignment(0);
    set_pick_up(1);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20, 11);

set_skill(SS_INFIDEL, 11); 
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 20);

    add_prop(CONT_I_HEIGHT, 100 + random(100)); 
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_S_EXTRA_SHORT, randes[random(sizeof(randes))]);    

    set_act_time(10);
    add_act("emote slops some water onto the floor and scrubs it with "+
        "her brush.");
    add_act("emote wipes her forehead with the back of her hand.");
    add_act("emote mops the floor around a weird stranger at a table.");
    add_act("emote stops to stretch, but notices you looking and "+
        "turns back to her work.");
    add_act("emote rubs some balm into her cracked, bleeding hands.");
    add_act("emote sneaks a bite of bread from her apron when she "+
        "thinks you aren't looking.");
    add_act("emote wipes up some blood.");
    add_act("emote mops her forehead with her sleeve.");
    add_act("emote blows a wisp of hair from her eyes.");
    add_act("emote shifts to a more comfortable position.");
    add_act("emote hums tonelessly to herself.");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"help","task","job","errand","quest","assignment"}), 
        VBFC_ME("give_job"), 1);
    add_spy_ask();
    seteuid(getuid(TO));
}

string
my_long()
{
    string str;

    switch(random(6))
    {
        case 0:
            str = "seems to be a whirlwind of activity";
            break;
        case 1:
            str = "scrubs with slow, measured movements, as though she "+
                  "is pacing herself";
            break;
        case 2:
            str = "wears a dingy scarf over her shaved head";
            break;
        case 3:
            str = "has smudge-marks on her face and her hands are red "+
                  "and chapped";
            break; 
        case 4:
            str = "has a large bottom that sways as she scrubs";
            break;
       case 5:
            str = "has broad shoulders and muscular forearms that ripple "+
                  "under her pale skin";
            break;                 
    }
    return "A "+ query_adj() +" cleaning woman.\n"+
           "She "+ str +".\n"+        
           "She is demure and obedient, a typical "+
           "sybarite servant shrouded in a quiet dignity.\n"+
           "She appears to be well-fed and healthy despite her hard "+
           "labour.\n";
}

string
what_me()
{
    switch(random(7))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I scrub floors and clean messes. That is all I know.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
        case 4:
            command("emote looks fearfully around.");
            command("say Would you see me beaten?");
            break;
        case 5:
            command("say I am not worthy of your attention.");
            break;
        case 6:
            command("emote shrugs and goes back to her work.");
            break;
    }
    return "";    
}

string
give_job()
{
    command("smile " + TP->query_name());
    command("say You're very kind, but I must do this myself, "+
        "or face the consequences.");
         return "";
}

void 
return_to_normal()
{
    if (TO->query_attack())
    {
        command("say I beg you please, kill me quickly.");
        return;
    }
    remove_alarm(kill_id);
    kill_id = 0;
    add_prop(LIVE_S_EXTRA_SHORT, " on her knees");    
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    if (TO->query_prop(LIVE_S_EXTRA_SHORT))
        TO->remove_prop(LIVE_S_EXTRA_SHORT);
    if (kill_id)
        return;
    kill_id = set_alarm(20.0, 60.0, return_to_normal);
}

