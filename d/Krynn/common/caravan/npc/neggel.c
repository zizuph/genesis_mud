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
    set_title("To'tor, Retired Blacksmith of the White Dragonarmy");
    set_long("This large half ogre has a strange, cunning look " +
      "in his eye. Thanks to his inbred skill with metal-working, " +
      "he rose to the safe position of the White Dragonarmy blacksmith. " +
      "Though Fael-theas has exchanged his officers' staff " +
      "several times, always in a bloody fashion, Neggel was " +
      "left untouched. Neggel however got tired of the cold environment " +
      "and dwarves breaking into his smithy, so he decided to retire. " +
      "If you have the coin he loves, he might sharpen your weapons.\n");
    add_name(({"blacksmith","smith", "retired"}));
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
    add_ask(" [about] 'task' / 'quest'", "say If ye come back later," +
     "me can use some special metals!\n",1);
    add_ask(" [about] 'master' / 'fael-theas'","say Are ye mad? " +
      "ye don't talk bout him!",1);
    add_ask(" [about] 'dragonarmy'","say Ye have to be sharp to " +
      "survive here... Da Master sees spies and traitors everwhere! " +
      "Half the time, he's right... Sooner or later they confess!",1);
    add_ask(" [about] 'thanoi'","say Dumb creatures. Waste of " +
      "weapons, waste of food... But da Master thinks they be " +
      "too stupid to spy him.",1);
    add_ask(" [about] 'minotaurs'","say Simple brutes, but serve " +
      "us well. Know how to tend their weapons, too.",1);
    add_ask(" [about] 'castle'","say Too cold for me. " +
      "And all tha dorfs commin there, make ye paranoid. Maybe oi " +
      "may return in time, fer now, me go back ta Sanction. " ,1);
    add_ask(" [about] 'dwarf' / 'dwarves' / 'dorf' ",
      "say Dum creatures, I wish 'em all dead!",1);
    add_ask(" [about] 'cold' ",
      "say Da Castle be too cold for me likin, Ye will move back ta " +
      "me place in Sanction, and open me smith there again, many troops " +
      "in Sanction need sharpenin ye know?",1);



    set_act_time(4);
    add_act("emote swears loudly and sets down to sharpen another " +
     "battleaxe.");
    add_act("emote curses the Gods of Light as he remounts a " +
     "barbed hook on a thanoi harpoon.");
    add_act("emote averts his eyes as he sharpens a heavy double-headed " +
     "axe. Sparks fly everywhere.");
    add_act("emote mutters in ogrish as he replaces a broken handle " +
     "on a thanoi mace.");
    add_act("emote glances cunningly at you.");
    add_act("emote sharpens the wavy blade of a flamberge.");
    add_act("say Stupid thanoi! They keep breaking their weapons!");
    add_act("shout Sargonnas damn those dumb Thanoi!");
    add_act("emote spits a gob of phlegm right under your feet.");
    add_act("Walrus blockheads keep banging " +
     "their weapons on the walls! They should be given stone clubs, " +
     " not quality axes!");
    add_act("emote shivers as he gets reminded of the cold of the castle.");
    add_act("say I love da heat of tha fireplace, makes me feel as " +
            "comfy as when me rip dem pretties apart.");
    add_act("say Can't wait getting back ta Sanction, me get much coins, " +
            "from da army there.");
    add_act("say Dum Thanois don't live in Sanction, me happy, me sharpen, " +
            "for dem bright army soldiers dem knows how ta tend dem weapons " +
            "too.");

    set_cact_time(3);
    add_cact("shout I'll break your back!");
    add_cact("shout A spy! I caught a spy! Tell da Master!!");

    clone_object(KWEP + "smith_hammer")->move(TO);
    clone_object(KARM + "warmour1")->move(this_object(),1);
    clone_object(KARM + "white_fur")->move(this_object(),1);
    command("wield all");
    command("wear all");
}
