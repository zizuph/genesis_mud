#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/icewall/castle2/local.h"
#include <macros.h> 
#include "/d/Krynn/common/defs.h";
inherit "/d/Krynn/std/monster"; /* The Krynn humanoid monster file */

inherit "/std/act/action";

public void
create_krynn_monster()
{
    string str;

    set_name("neggel");
    set_living_name("neggel");
    set_race_name("half-ogre");
    set_title("To'tor, Blacksmith of the White Dragonarmy");
    set_long("This large half ogre has a strange, cunning look " +
      "in his eye. Thanks to his inbred skill with metal-working, " +
      "he rose to the safe position of the White Dragonarmy blacksmith. " +
      "Though Fael-theas has exchanged his officers' staff " +
      "several times, always in a bloody fashion, Neggel was " +
      "left untouched. If you have the coin he loves, he might " +
      "sharpen your weapons.\n");
    add_name(({"blacksmith","smith"}));
    set_adj("thick-skinned");
    add_adj("muscled"); 
    set_gender(G_MALE);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({190,136,220,80,80,136}));
    set_skill(SS_DEFENCE,        75);
    set_skill(SS_PARRY,          75);
    set_skill(SS_WEP_CLUB,       100);
    set_skill(SS_BLIND_COMBAT,   75);

    set_alignment(-650);
    set_knight_prestige(50);

    set_default_answer("The blacksmith ignores your question " +
     "and turns back to his work.\n");

    add_ask(" [about] 'repair'", "say If ye got da coin, I can " +
     "fix ye up!",1);
    add_ask(" [about] 'task' / 'quest'", "say I'm not da one " +
      "issuing orders around 'ere!",1);
    add_ask(" [about] 'master' / 'fael-theas'","say Are ye mad? " +
      "He can hear us talk 'bout him!",1);
    add_ask(" [about] 'dragonarmy'","say Ye have to be sharp to " +
      "survive here... Da Master sees spies and traitors everwhere! " +
      "Half the time, he's right... Sooner or later they confess!",1);
    add_ask(" [about] 'thanoi'","say Dumb creatures. Waste of " +
      "weapons, waste of food... But da Master thinks they be " +
      "too stupid to spy him.",1);
    add_ask(" [about] 'minotaurs'","say Simple brutes, but serve " +
      "us well. Know how to tend their weapons, too.",1);
    add_ask(" [about] 'castle'","say Nice place. " +
      "Da Master has all da Army camped outside, by the sea. Says " +
      "da noise makes his magicks go bad. But me thinks he's not " +
      "wanting any spies.",1);


    set_act_time(4);
    add_act("emote swears loudly and sets down to sharpen another " +
     "thanoi battleaxe.");
    add_act("emote curses the Gods of Light as he remounts a " +
     "barbed hook on a thanoi harpoon.");
    add_act("emote averts his eyes as he sharpens a heavy double-headed " +
     "axe. Sparks fly everywhere.");
    add_act("emote mutters in ogrish as he replaces a broken handle " +
     "on a thanoi mace.");
    add_act("say Ya brought da Master's ... special cargo? " +
     "Are they pretty?");
    add_act("emote glances cunningly at you.");
    add_act("say Last month da Master let me play with his pretties... " +
     "when he was done with 'em.");
    add_act("say Better ya go. Da Master doesn't like anybody from " +
     "white army around his castle. Last spy he fried with a " +
     "fireball.");
    add_act("emote sharpens the wavy blade of a flamberge.");
    add_act("say Stupid thanoi! They keep breaking their weapons!");
    add_act("shout Sargonnas damn those dumb Thanoi!");
    add_act("emote spits a gob of phlegm right under your feet.");
    add_act("Walrus blockheads keep banging " +
     "their weapons on the walls! They should be given stone clubs, " +
     " not quality axes!");

    set_cact_time(3);
    add_cact("shout I'll break your back!");
    add_cact("shout A spy! I caught a spy! Tell da Master!!");

    clone_object(KWEP + "smith_hammer")->move(TO);
    clone_object(KARM + "warmour1")->move(this_object(),1);
    clone_object(KARM + "white_fur")->move(this_object(),1);
    command("wield all");
    command("wear all");
}
