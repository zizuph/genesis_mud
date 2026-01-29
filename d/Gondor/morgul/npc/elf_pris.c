/*
 * /d/Gondor/morgul/npc/elf_pris.c
 *
 * Elf prisoner to free from the torture room as part of
 * the regrow scroll recovery.
 *
 * Coded by Gwyneth, June 3, 2000
 */

inherit "/std/monster";

#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define GOOD_EMOTES ({ "admire", "bow", "compliment", "caress", \
        "comfort", "curtsey", "greet", "kiss", "kneel", \
        "smile", "worry" })
#define BAD_EMOTES ({ "curse", "explode", "frown", "fume", "flex", \
        "glare", "growl", "roar", "scold", "scowl", "startle", "swear", \
        "smirk", "snarl", "spit", "sneer" })
#define GOOD_CONTACT_EMOTES ({ "bounce", "hug", "hold", "pat", "pounce", \
        "squeeze", "tackle" })
#define BAD_CONTACT_EMOTES ({ "bite", "jump", "kick", "knee", "pinch", \
        "poke", "slap", "spank", "touch" })

#define MAX_RESPONSE 7
#define GOOD_RESPONSE ({ " A light of warmth in this darkest of places ", \
        " Your action gives me courage ", \
        " Please, release me from this torture ", \
        " Your manner gives me great comfort ", \
        " Your gesture makes the pain easier to bear ",\
        " So kind, may the blessings of the Valar be with you ",\
        " Such a simple thing, such hope it brings me "})
#define BAD_RESPONSE ({ "cringe", "sob quiet", "glare defiant", \
        "laugh bitter", "say Please have mercy!", "blanch", "avert" })

void
create_monster()
{
    set_name("lentil");
    set_living_name("lentil");
    set_race_name("elf");
    set_title("of Imladris");

    set_adj("weary");
    add_adj("tortured");

    set_short("weary tortured elf");
    set_pshort("weary tortured elves");

    set_long("Strands of blood-caked hair fall limply over " +
        "this elf's pain creased face and across deep sunken eyes " +
        "that stare at you with a mixture of fear and determination.\n");

    default_config_npc(50);

    add_prop(CONT_I_VOLUME, 32000);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 32000);

    set_alignment(800);

    set_act_time(20);
    add_act("emote shuts his eyes as waves of pain rack his body.");
    add_act("emote groans quietly in pain.");
    add_act("emote cries out for help.");
    add_act("emote prays to the Valar to give him strength.");

    add_ask(({"torture", "rack"}), "say My captors torture me " +
        "night and day to the brink of death. My body is torn " +
        "from the rack, but my spirit cannot be crushed.", 1);
    add_ask(({"regrowth", "spell", "spells", "knowledge", "bilbo"}), "say " +
        "It is all so hazy. I can barely remember the light of the " +
        "sun on my face in Imladris. If I were free, maybe it would " +
        "return to me.", 1);
    add_ask("imladris", "say Imladris is my home. How I wish I could " +
        "return!", 1);
    add_ask(({"free", "freedom", "help"}), "emote groans and pleads " +
        "for you to release him.", 1);
    set_default_answer("A groan of pain and something unintelligible " +
        "escapes from the elf's lips.\n");        
}

void
arm_me()
{
    clone_object(MORGUL_DIR + "obj/rags")->move(TO);
    command("wear all");
}

public int
query_knight_prestige()
{
    return -100;
}

void
introduce(string name)
{
    command("present me to " + name);
    command("say to " + name + " Please release me from this torture!");
}

public void
add_introduced(string name)
{
    set_alarm(1.0, 0.0, &introduce(name));
}

public void
handle_emotes(string emote, object actor)
{
    if(member_array(emote, GOOD_EMOTES) != -1)
    {
        command("say to " + OB_NAME(actor) +
            GOOD_RESPONSE[random(MAX_RESPONSE)] +
            (TP->query_gender() ==
            G_FEMALE ? "my lady." : "good sir."));
        return;
    }

    if(member_array(emote, GOOD_CONTACT_EMOTES) != -1)
    {
        command("say to " + OB_NAME(actor) +
            GOOD_RESPONSE[random(MAX_RESPONSE)] +
            (TP->query_gender() ==
            G_FEMALE ? "my lady." : "good sir."));
        command("emote tries to hide the pain inflicted " +
            "by even the slightest bit of contact with " +
            "his battered body.");
        return;
    }

    if(member_array(emote, BAD_EMOTES) != -1)
    {
        command(BAD_RESPONSE[random(MAX_RESPONSE)]);
        return;
    }

    if(member_array(emote, BAD_CONTACT_EMOTES) != -1)
    {
        command(BAD_RESPONSE[random(MAX_RESPONSE)]);
        command("emote bites back a groan of pain at " +
            "the agony inflicted by even " +
            "the slightest bit of contact with his " +
            "battered body.");
        return;
    }
}

public void
emote_hook(string emote, object actor, string adverb, int target)
{
    if(target)
    {
        set_alarm(1.0, 0.0, &handle_emotes(emote, actor));
    }
}

public void
do_die(object killer)
{
    object orc;

    if (orc = present("torture_orc", environment(TO)))
    {
        orc->orc_leave();
    }

    ::do_die(killer);
}
