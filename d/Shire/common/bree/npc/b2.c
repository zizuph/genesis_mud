/*
 *  /d/Shire/common/bree/npc/butterbur.c
 *
 *  The keeper of the Prancing Pony Inn in Bree.
 *  Cloned by ~Shire/common/bree/inn
 *
 *  Updated for use in the Dwarven Friend quest.
 *  Quest enabled by Mardil (~Shire/michel/npc/mardil.c).
 *  Glaurung 4-98
 */

inherit "/d/Shire/std/monster";

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

//** Global Variables **//
int gQuestEnabled = 0;

//** Prototypes **//
int  return_sigh(string s);
int  return_smile(string s, object o);
int  query_quest_enabled();
void set_quest_enabled(int i);
void give_things();

void
create_shire_monster() 
{
    FIXEUID

    set_name(({"barliman","butterbur","innkeeper"}));
    set_living_name("butterbur");
    set_title("Butterbur the Innkeeper of the Prancing Pony");
    set_race_name("human"); 
    set_adj(({"short","fat"}));
    set_long("This rotund human seems to be a jolly fellow. You wonder "+
          "what he is doing here in the land of the Hobbits. You guess he "+
          "is the owner of the Prancing Pony.\n");
    default_config_npc(30);
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,30);
    set_pick_up(75);
    set_introduce(1);
    
    add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
    add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
   
    set_act_time(3);
    add_act("emote cleans the counter meticulously.");
    add_act("chuckle");
    add_act("emote bustles about the inn, a tray of mugs in hand.");
    add_act("emote smiles so broadly his nose turns red.");
    add_act("emote wonders aloud if he'll need four kegs or five for that dwarven party.");
    add_act("emote sighs wistfully, remembering when more hobbits came from the Shire.");
    add_act("smile slee");
    add_act("shout Pipe down in there, I'm working!");
    add_act("shout If you run out of beer, I have more.");
    add_act("shout Is there a Mister Baggins in there by any chance?");
    add_act("say Even though I may not look it, I'm busy busy busy.");
    add_act("say I have not seen Gandalf the Grey in a long time.");
    add_act("say I hear rumors of orcs very near Bree.");
    add_act("shout Nob! Where are you? Those hobbits need more beer. Nob!");
    add_act("shout Bob, how many times have I told you about to keep the ponies in the stables, not the inn yard?");
    add_act("say Must I do everything myself?");
    add_act("say What is it I am forgetting?");
    add_act("say Hi there! What can I serve you?");

    add_ask("arthad", VBFC_ME("about_arthad"));
    add_ask("things", VBFC_ME("about_things"));
}

int
return_smile(string who, object actor) 
{
    if (ENV(actor) != ENV(TO)) 
        return 0;
   
    switch (random(4)) 
    {
        case 0: 
            command("smile"); 
            return 1;

        case 1: 
            command("smile " + who); 
            return 1;

        default:
            return 0;
    }
 
    return 0;
}

int
return_sigh(string who)
{
    if (!stringp(who))
        return 0;
    who = lower_case(who);
    if (random(3)) 
        return 0;
    command("say Are you gonna order something or what?");
    return 1;
}

void
emote_hook(string emote,object actor,string averb = 0)
{
    string name = actor->query_real_name();
   
    switch (emote)
    {
        case "sigh":
            set_alarm(3.0, 0.0, &return_sigh(name));
            break;
      
        case "smile":
            set_alarm(3.0, 0.0, &return_smile(name, actor));
            break;
    }
}

string
about_arthad()
{
    if (!query_quest_enabled())
    {
        command("say I cannot recall seeing him for some time.");
        command("say A friend of yours?");
        return "";
    }

    command("emote stops to think for a moment");
    command("say Yes he was in here a couple days ago.");
    command("say Actually he left a few things behind while he was here...");
    command("say You know how those dwarves get when they're drunk ;)");
    return "";
}

string
about_things()
{
    if (!query_quest_enabled())
    {
        command("say Eh? I am getting old, you will need to speak up!");
        return "";
    }

    command("say Would you mind returning them to him?");
    command("say I am simply too busy to do it myself.");
    command("emote wipes the sweat from his brow");
    give_things();
    return "";
}

void
give_things()
{
    object crate = clone_object("/d/Shire/common/bree/obj/crate");

    if (!objectp(present(TP, ENV(TO))))
    {
        crate->remove_object();
        set_quest_enabled(0);
        return;
    }

    crate->move(TO,1);
    command("give "+crate->short()+" to "+TP->query_real_name());
    command("say I think that's all...");
    command("whisper "+TP->query_real_name()+" You might want to "+
        "have a talk with Gloin. He and Arthad drink together sometimes.");
    command("emote motions towards the common room");
    set_quest_enabled(0);
}

void set_quest_enabled(int i) { gQuestEnabled = i; }

int query_quest_enabled() { return gQuestEnabled; }        
