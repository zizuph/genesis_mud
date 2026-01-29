/*
 * Talia Westan of Solace, Trainer in Vingaard Keep
 * by Teth
 * Jan 3 97 
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit M_FILE

inherit "/std/act/action";     /* Allows Talia to act  */

#include "killer.h"

public void
create_krynn_monster()
{
    string str;

    set_name("talia");
    set_living_name("talia");
    set_race_name("human");
    set_title("Westan of Solace, Vingaard Keep Trainer");
    set_long("This woman has straight brown hair that is cut short. " +
      "Her face has a soft look about it, and it appears " + 
      "she possesses a clever mind. Her well-muscled body " +
      "lends itself to the confidence she obviously feels about " +
      "herself.\n"); 
    add_name(({"westan","trainer","woman"}));
    set_adj("straight-haired");
    add_adj("well-muscled"); 
    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);
    add_prop(CONT_I_WEIGHT,30000);

    set_stats(({84,103,82,57,66,83}));
    set_skill(SS_DEFENCE,        30);
    set_skill(SS_PARRY,          30);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    set_skill(SS_UNARM_COMBAT,   75);

    set_alignment(623);
    set_knight_prestige(-2);

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] [animal] 'handling'", "say The " +
      "training and handling of animals can be a very useful " +
      "skill. For example, I have used it in the past to help " +
      "capture rabbits and call birds. It's also helpful when " +
      "calming horses, so that they are not so jittery.",1);
    add_ask(" [about] [appraise] 'enemy' / 'object' / 'appraise'",
      "say Knowing the qualities of an object, friend " +
      "or foe can be very helpful. You should be aware that when " +
      "you are relatively unskilled in these attributes, you may " +
      "make some wild and unbelievable estimates.",1);
    add_ask(" [about] 'axe'", "say The use of an axe has been " +
      "known to save the life of many an adventurer. Proper use " +
      "requires balance and knowledge of axe-cleaving methods.",1);
    add_ask(" [about] 'blindfighting'","say Fighting when you can't " +
      "see your opponent is a difficult thing to do, and hard " +
      "to train.", 1);
    add_ask(" [about] 'knife'", "say Being skilled with " +
      "a knife has many advantages. For one, you wouldn't cut " +
      "yourself shaving!",1);
    add_ask(" [about] 'sasha'","say Sasha is my " +
      "sister, also a trainer of adventurers! She has decided " +
      "to live in Solace, now. Perhaps you should visit her!",1);
    add_ask(" [about] 'sword'","say " +
      "Sword fighting is a very useful skill for any adventurer. " +
      "Most humanoid enemies find the sword a preferable weapon, " +
      "so that if you manage to vanquish them, you'll find as often " +
      "as not a sword among the loot. Considering how commonplace " +
      "the weapon is, it is a good idea to be proficient in this " +
      "skill.",1);
    add_ask(" [about] 'tracking'","say Knowledge and " +
      "proficiency in being able to discern and read tracks is " +
      "a valuable skill to a hunter.",1);
    add_ask(" [about] [unarmed] 'unarmed' / 'combat' / 'fighting'",
      "say A basic skill, that is the starting point for every " +
      "adventurer.", 1);
    add_ask(" [about] 'quest'","say I wouldn't know " +
      "anything about that.",1);

    set_act_time(5);
    add_act("emote breathes a deep sigh.");
    add_act(({"say I hope that the Solamnians have prepared the defences " +
        "of Vingaard Keep properly!", "emote smiles hopefully."}));
    add_act("emote whistles a wandering tune.");
    add_act("say I hope my sister, Sasha, is doing well.");
    add_act("say You can ask me about the skills I train!");
    add_act("emote inspects the sand in the corner of the room.");
    add_act("emote squints with one eye.");

    set_cact_time(4);
    add_cact("shout Help me! I'm being attacked!");
    add_cact("say Someone will have their revenge on you, fool!");
    add_cact("emote tries to protect herself."); 
    add_cact("shout The Solamnians will not let my death go unpunished!");
}


public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Talia Westan", killer);
    return 0;
}
