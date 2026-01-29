#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/poolbottom/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Krynn/std/monster";

#define WEP_STAFF "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("theobald");
    set_living_name("theobald");
    set_title("of Poolbottom, Master of the School of High Magic");
    set_race_name("human");
    set_adj("rotund");
    add_adj("officious");
    set_gender("G_MALE");
    set_long("Before you stands a rotund middle-aged man. Ponderous, " +
       "officious, and clearly quite full of his own self-importance, " +
       "he is not at all what you would expect from someone who has " +
       "passed the potentially deadly Test of High Sorcery and be in " +
       "the position of Master of Poolbottom, School of High Magic.\n");

    set_stats(({89,136,136,136,136,89,89}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_FORM_ENCHANTMENT, 100);

    set_alignment(10);
    set_knight_prestige(0);
    set_act_time(10);
    add_act("emote looks at you, his thick eyebrows narrowing " +
      "alarmingly.");
    add_act("emote flexes his thick fingers."); 
    add_act("emote mutters something about the youth of today.");
    add_act("say I am expecting a summons by the Conclave to the Tower " +
      "of Wayreth any day now.");
    add_prop(OBJ_M_NO_ATTACK,"Within the walls of his school, Master " +
      "Theobald is protected " +
      "by powerful runes of magic, keeping him safe from harm.\n");
    add_prop(NPC_I_NO_RUN_AWAY,1);

    add_ask(({"joining","join"}),VBFC_ME("join_hint"));
    add_ask(({"spells","learn spells","spell","learn spell","teach spell",
        "teach magic","magic spell","teach me"}),VBFC_ME("spell_hint"));

    trig_new("%w 'introduces' %s","react_to_intro");

    seteuid(getuid());
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP_STAFF)->move(TO,1);
    command("wield all");

}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

string
join_hint()
{
    command("eyebrow incredul");
    command("say You want to enroll in my school?");
    command("say Know I don't take just any riffraff.");
    command("say Those with less than two brain cells to rub together I " +
       "refuse to waste my time with.");
    command("say So that excludes all goblins, gully dwarves, and kender.");
    command("smirk");
    command("say And I can't abide dwarves or minotaurs. The first moment " +
       "they are disciplined out comes the axe!");
    command("rolleyes");
    command("say Anyway, the book on the lectern explains what you need to do.");
    command("emote points to the lecturn with a leather-bound book upon it.");
    return "";
}

string
spell_hint()
{
    object wand;
    string what, who;

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        command("eyebrow incredul");
        command("say If you want to learn magic from me, you'll need to " +
           "enroll in my school first!");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"kampiunarcanis"))
    {
        command("scowl dark");
        command("say I told you go to the library and learn the mental " +
          "exercises that will allow you to read magic!");
        command("gesture furious");
        command("say Don't bother me until you have completed that " +
          "simple task!");
        return "";
    }

    if(this_player()->query_skill(SS_SPELLCRAFT) < 30)
    {
        command("sigh dramatic");
        command("say Your spellcraft skills are too poor for me to " +
           "teach you anything.");
        command("say Come back to me when you have at least rudimentary " +
           "skills!");
        command("gesture dismiss");
        return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"talkarpas"))
    {
        if(SOHM_MANAGER->query_scribed_spell(this_player(),"ehtahhewa"))
        {
           command("sigh dramatic");
           command("say I don't have time to teach you anything right now.");
           command("say You aren't my only student!");
           command("gesture dismiss");
           return "";
        }

        command("say More training?");
        command("rolleyes");
        command("say Very well. I have only time to teach you...");
        command("think");
        command("say ...a minor divination spell.");
        command("say Now pay attention!");
        command("emote closes his eyes and falls in to a trance.");
        this_player()->catch_msg("\nYou observe Master Theobald closely as " +
           "he divines which students of the School are currently " +
           "at large in the realms. You note down the details of " +
           "'Ehtahhewa' in your spellbook.\n\n");

        SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ehtahhewa");

        command("emote blinks his eyes and comes out of his trance.");

        return "";
    }

    command("smile humourless");
    command("say So, now that you have mastered the ability to read magic " +
        "you probably are no doubt eager to summon demons and fling " +
        "around fireballs?");
    command("eyebrow");
    command("say Well not in my school!");
    command("emote huffs.");
    command("say Centuries have passed since the Cataclysm and magic " +
        "users are once again tolerated in Krynn.");
    command("say We have no need of spells of war or violence.");
    command("say So let me teach you one of my favourite spells.");
    command("emote raises his gnarled wooden staff and recites words of " +
        "magic, making his staff glow briefly for a moment.");

    this_player()->catch_msg("\nYou observe Master Theobald closely as " +
        "he casts the light spell, noting " +
        "down the details of 'Talkarpas' in your spellbook.\n\n");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"talkarpas");

    command("smile smugly");
    command("say You'll need a staff or wand to cast that spell.");
    command("emote fumbles around in his robes and pulls out a wooden wand.");
    command("emote Here... memorise that spell and try casting it with this.");

    wand = clone_object(EOBJ + "wand");
    what = wand->query_name();
    who = this_player()->query_real_name();
    wand->move(TO);
    command("give " + what + " to " + who);

    return "";
}
