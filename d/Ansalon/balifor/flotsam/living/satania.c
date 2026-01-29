/*
 * Updated, Nov 7. 2000
 *
 * Added a check to see if the object that a player gives to Satania
 * is the correct one. If not, he'll drop it, to prevent people from
 * collapsing him with coins etc.
 * - Elmore.
 *
 * Added sanity check for wounds from Avenir's weapons
 * - 12.01.2001 Torqual
 *
 * Fixed runtime errors
 * 13.8.2002 Milan
 *
 * Arman May 2016 - Added SoHM spell task
 *
 * Arman Nov 2016 - Gave Satania SoHM shadow and spells
 *                - updated his mentals
 *                - removed his special attack
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit AM_FILE
inherit "/lib/unique";


#define WEP "/d/Ansalon/balifor/flotsam/obj/weapon/carnage"
#define WEP2 "/d/Ansalon/balifor/flotsam/obj/weapon/sat_scimitar"
#define ARM1 "/d/Ansalon/balifor/flotsam/obj/armour/elven_chain"
#define ARM2 "/d/Ansalon/balifor/flotsam/obj/armour/hooded_robe"
#define HERB_POUCH      "/d/Gondor/common/obj/herbpouch"
#define SATCHEL         "/d/Gondor/common/potions/satchel"

#define PLAYER_I_FOUND_WAND "_player_i_found_wand"

void get_me_soul();

int soul_id;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("satania");
    set_living_name("satania");
    set_title("Caltian, High Rogue of the Bloodsea and exiled " +
      "Sorcerer of Silvanesti");
    set_race_name("elf");
    set_adj("dark-robed");
    add_adj("silver-haired");
    set_gender("G_MALE");
    set_long("Before you stands a silver-haired elf, whose " +
      "haughty gaze seems to size you up as barely noteworthy. " +
      "His dark-robes mark him as an evil warlock who has passed " +
      "the Tests of High Sorcery, and his lithe yet strong " +
      "body, and the comfortable way he holds his weapons, " +
      "mark him as a bladesman worthy of respect.\n");

    set_stats(({150, 200, 160, 160, 160, 100}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS, 140);

    set_skill(SS_SPELLCRAFT, 90);
    set_skill(SS_FORM_ENCHANTMENT, 90);
    set_skill(SS_FORM_CONJURATION, 85);
    set_skill(SS_FORM_ABJURATION, 85);
    set_skill(SS_FORM_ILLUSION, 60);
    set_skill(SS_FORM_TRANSMUTATION, 60);
    set_skill(SS_ELEMENT_FIRE, 75);
    set_skill(SS_ELEMENT_EARTH, 60);
    set_skill(SS_ELEMENT_WATER, 60);
    set_skill(SS_ELEMENT_AIR, 60);

    set_alignment(-600);
    set_knight_prestige(700);
    set_all_hitloc_unarmed(25);
    set_act_time(10);
    add_act("say I may have a job for one such as you.");
    add_act("smile wicked");
    add_act("say Curse the Silvanesti elves! I'll have my " +
      "revenge.");
    add_act("say Hull Nightstar is, for a human, a most " +
      "skilled captain.");
    add_act("emote mumbles an incantation under his breath.");
    add_act("say I have been sent by the Conclave of the " +
      "Wizards of High Sorcery to destroy the renegade mage, " +
      "Fermammon the self-proclaimed Wise.");

    set_cact_time(5);
    add_cact("emote hisses: Fool! You court death!");
    add_cact("laugh man");

    add_ask(({"quest","task","job"}),
      VBFC_ME("quest_help"));
    add_ask("apprentice","say You mean ex-apprentice. " +
      "He is the cabin boy.",1);
    add_ask("ex-apprentice","say He is the cabin boy.",1);
    add_ask(({"hull nightstar","hull"}),"say He is the " +
      "Captain of this ship.",1);
    add_ask("artifact","say Question me not! It is of " +
      "no concern to you.",1);
    add_ask(({"elf","elves","silvanesti","silvanesti elves"}),
      "say The Silvanesti elves are all fools - they do not " +
      "understand what it takes to achieve true power.",1);
    add_ask("wand","say What is this talk of a wand? It must "+
      "be some insignificant magical trinket.",1);
    add_ask("power","say You cannot understand true power. I have "+
      "survived tests that you could never imagine.",1);
    add_ask("help","say You may be able to help me with "+
      "a small job.",1);
    add_ask(({"spirit stone","stone"}),"say I know of one that was " +
      "used in ages past. Ancient elven lore speaks " +
      "of an elven drow's spirit being trapped for crimes now long " +
      "forgotten, and forced to protect the secret burial treasures " +
      "of Kith Kanan.", 1);
    add_ask(({"kith kanan"}),"say Kith Kanan? A formidable elven king of the " +
      "Qualinesti. His tomb is the mighty fortress Pax Tharkas. His vault " +
      "I believe is hidden somewhere there.", 1);
    add_ask(({"treasure","vault","treasures","burial treasures"}),
      "say The mighty fortress Pax Tharkas is also the tomb of the elven king " +
      "Kith Kanan. You will find the secret vault there.", 1);
    add_ask(({"help","spell","teach magic","teach spell","magic",
      "spells"}), VBFC_ME("spell_hint"));

    trig_new("%w 'introduces' %s","react_to_intro");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());

    seteuid(getuid());
}

void
get_me_soul()
{
    add_cmdsoul(SOHM_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul("/d/Genesis/specials/guilds/shadows/mana_shadow");
    update_hooks();
    remove_alarm(soul_id);
}

string
query_wohs_order_colour()
{
    return "black";
}

string
query_guild_name_occ()
{
    return "Wizards of High Sorcery";
}

public int
can_ignore_ingredients(object caster)
{
    return 1;
}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

string
quest_help()
{
    if(TP->test_bit("ansalon", 0, 12))
    {
	TO->command("say Sorry, I have no tasks for you "+
	  "at present.");
	return "";
    }
    TO->command("say Yes, I do have a " +
      "job for one such as you. A renegade mage lives in a " +
      "small cottage just outside of Flotsam, going by the name " +
      "of Fermammon.");
    TO->command("say I was sent by the conclave to dispose of " +
      "him, but to be frank, am only here to make sure his " +
      "precious magical artifact does not fall into the hands " +
      "of someone who does not understand its power.");
    TO->command("grin malev");
    TO->command("say Bring " +
      "me this artifact and you will earn my favour. Oh yes, " +
      "one thing that you may find of interest is that his " +
      "ex-apprentice now works on this ship. Perhaps you should " +
      "talk to him?");   
    return "";
} 

int
special_attack(object enemy)
{
    int     attacktype = random(5);

    if (attacktype == 1)
    {
       if(!TO->query_prop("_sohm_blur_effect"))
       {
         // Cast the blur spell if not in effect
          command("kadenadon");
          return 1;
       }
       if(!enemy->has_illfortunate_shadow())
       {
         // Cast the curse spell if not in effect
          command("chikohk");
          return 1;
       }

       if(random(3) == 1)
          command("wintektor");
       else
          command("apianak");
       return 1;
    }

    return 0;

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

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_unique(WEP, 5, FOBJ + "weapon/long_dagger")->move(TO, 1);
    clone_unique(WEP2, 5, FOBJ + "weapon/cutlass")->move(TO, 1);
    command("wield all");

    clone_unique(ARM1, 5, FOBJ + "armour/shirt")->move(TO, 1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(HERB_POUCH)->move(TO,1);
    clone_object(SATCHEL)->move(TO,1);
    command("tie pouch");
    command("tie satchel");
    command("wear all");
}


void
calculate_experience(object who)
{

    int xp_base = 7500;

    if(who->test_bit("ansalon", 0, 12))
    {
	who->catch_msg("Nice job, but no experience second time.\n");
	return;
    }

    xp_base -= (who->query_prop(PLAYER_I_FOUND_WAND) ? 0 : 6000);
    who->catch_msg("You feel more experienced!\n");
    if (who->query_wiz_level())
    {
	who->catch_msg("xp : " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 12);

    A_QUEST_LOG("quest","Idol Quest", who, xp_base);
    return;
}

void
return_give_idol(object from)
{
    object spirit;
    string who, what;

    who = from->query_real_name();

    command("cackle");
    command("say You have found the idol!");
    command("laugh wicked");
    command("say Excellent. You have earnt my dark favour. Here is your reward!");
    command("emote raises his hands, and speaks the spidery language of the magi!");

    calculate_experience(from);

    command("say I have no reason to remain here. Farewell!");
    command("emote mutters a magical spell under his breath, and disappears in " +
      "a puff of smoke.");
    remove_object();
}

void
give_it_back(object ob, object from)
{
    if (!objectp(ob))
        return;

    if(!ob->id("_ansalon_wizard_idol_"))
    {
	// Sanity check for non-visible items - wounds from Avenir weapons
	if (ob->query_prop(OBJ_M_NO_DROP))
	    return;

        command("peer "+OB_NAME(ob));
        command("sneer");
        command("say What is this? It is not what I asked for!");
        command("drop "+OB_NAME(ob));
	return;
    }
}

void
return_give_spirit_stone(object ob)
{
    string who,
    what;

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        command("eyebrow suspicious");
        command("say How did you get this?");
        command("emote tucks the icy black stone into his robe.");
        ob->remove_object();
        return;
    }

    if((this_player()->query_lesser_spells_max() < 1))
    {
        command("eyebrow suspicious");
        command("say Interesting you bring this to me.");
        command("emote tucks the icy black stone into his robe.");
        command("say Did you expect something in return?");
        command("sneer");
        ob->remove_object();
        return;
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ricindenthanus"))
    {
        command("eyebrow");
        command("say Another spirit stone? My, aren't you resourceful.");
        command("say But do not expect any further knowledge from me.");
        command("ponder");
        command("say Although perhaps a certain dwarf frequenting the " +
          "bars in Flotsam may be able to direct you to some spell tomes " +
          "of interest.");
        command("smile mysterious");
        ob->remove_object();
        return;
    }
	
    command("cackle");
    command("say Ah! A spirit stone! Well done apprentice!");
    command("say From a banshee protecting the treasures of Kith Kanan " +
       "himself!");
    command("chuckle evil");
    command("emote tucks the icy black stone into his robe.");
    ob->remove_object();
    command("say Anyway enough chat. Let me teach you this spell.");
    this_player()->catch_msg("You are taught how to cast the offensive enchantment "+
       "'ricin denthanus', and quickly scribe it down in your spellbook.\n");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ricindenthanus");

    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_wizard_idol_"))
    {
	set_alarm(1.0,0.0, &return_give_idol(from));
	return;
    }

    if(ob->id("_pax_banshee_spirit_stone_"))
    {
	set_alarm(1.0,0.0, &return_give_spirit_stone(ob));
	return;
    }

    if(ob->id("scimitar"))
    {
	return;
    }
    if(ob->id("carnage"))
	return;
    if(ob->id("shirt"))
	return;
    if(ob->id("cutlass"))
	return;
    if(ob->id("robe"))
	return;
    if(ob->id("chainmail"))
	return;

    if(ob->query_no_show())
	return;
    if(ob->id("knife"))
	return;
    if(ob->id("dagger"))
	return;
    if(ob->query_wt(W_KNIFE))
	return;

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

string
spell_hint()
{
    string what, who;

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        command("sneer");
        command("say Do I look like a tutor to you?");
        command("say Begone!");
        return "";
    }

    if((this_player()->query_lesser_spells_max() < 1))
    {
        command("emote narrows his eyes coldly.");
        command("say You are nothing but a dabbler in the Arts.");
        command("say You have nothing you can offer me at this " +
           "point, apprentice. Come back when you are more powerful.");
        return "";
    }

    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
        command("sneer");
        command("say Your spellcraft skills are an embarrassment! Even " +
          "if I had the remotest interest in training you, you are too " +
          "inept for my sophisticated spells!");
        command("snicker");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"ricindenthanus"))
    {
        command("emote narrows his eyes coldly.");
        command("say You seeking magic from me?");
        command("sneer");
        command("say You are nothing but a dabbler in the Arts.");
        command("say You have nothing you can offer me at this ti...");
        command("hmm");
        command("emote strokes his narrow pointy chin thoughtfully.");
        command("say Perhaps you can? Perhaps you can.");
        command("say I can teach you a spell of power, but it comes at " +
          "a price.");
        command("smile humourlessly");
        command("say I am in need of a spirit stone, an item powerful " +
          "elven mages have used in ancient times to entrap malevolent " +
          "spirits and force them into servitude.");
        command("say Bring me a spirit stone, and I will teach you that spell.");
        return "";
    }

    command("frown");
    command("say Do not expect any further knowledge from me, I have rewarded " +
        "you amply!");
    command("sigh");
    command("say Although perhaps a certain roguish dwarf frequenting the " +
        "bars in Flotsam may be able to direct you to some spell tomes " +
        "of interest.");
    command("say It never fails to amaze me what manages to cross his grubby " +
            "palms.");
    command("say So go annoy him!");
    command("emote waves his hand dismissively.");

    return "";
}