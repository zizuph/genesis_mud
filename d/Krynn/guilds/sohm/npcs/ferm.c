inherit "/lib/unique";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Krynn/std/monster";

#define WEP "/d/Ansalon/balifor/flotsam_forest/obj/weapon/mag_staff"
#define WEP2 "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"
#define DRAGON_EGG_TASK "_fairy_dragon_egg_task"

void get_me_soul();

int soul_id;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("fermammon");
    set_living_name("fermammon");
    set_title("the Wise, renegade Archmage");
    set_race_name("human");
    set_adj("powerful");
    add_adj("ancient");
    set_gender("G_MALE");
    set_long("Before you stands an aged human, his skin " +
      "greying and wrinkled, sporting a long whispy white " +
      "beard. But that is where any resemblance to an old man " +
      "ends, for he stands as straight as a youth, as well as " +
      "with the confidence of a seasoned warrior. He seems " +
      "to exude an aura of power around him, and his eyes " +
      "when he looks at you seem to be able to see into your " +
      "soul.\n");

    set_stats(({89,136,136,136,136,89,89}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_CONJURATION, 75);
    set_skill(SS_FORM_ABJURATION, 75);
    set_skill(SS_ELEMENT_AIR, 75);

    set_alignment(10);
    set_knight_prestige(0);
    set_act_time(6);
    add_act("say Can nobody read anymore? Or is it just " +
      "that there are too many fools in this world that " +
      "don't read warning signs?");
    add_act("emote looks at you, his thick eyebrows narrowing " +
      "alarmingly.");
    add_act("emote mutters something about the youth of today.");
    add_act("say Don't enter the mists unless you know the " +
      "path through it!");
    add_act("say Curses! My apprentice has run off with my magic wand!");

    set_cact_time(10);
    add_cact("say Are you from the conclave? If so I'll " +
      "send you back to your tower with your robe between " +
      "your legs!");

    add_ask(({"mist","mists"}),"emote mutters: The path " +
      "dangerous it is, and ancient, yet beyond supposedly " +
      "lies ancient treasures... still, no one passes through " +
      "it without a map.",1);
    add_ask(({"task","quest"}),
      VBFC_ME("quest_hint"));
    add_ask("map","say A map through the mists perhaps? " +
      "Nay, I don't know of ones existance.",1);
    add_ask(({"auld centaurish","Auld Centaurish"}),
      "say It is the ancient written language of the centaurs. " +
      "I know of no scholar that knows it, and the few centaurs " +
      "I have met cannot read it. Seek out a centaur shaman. " +
      "One of them may still be able to read the script.",1);
    add_ask(({"centaurs","centaur","shaman","centaur shaman"}),
      "say I have observed a few centaurs in the forest south of " +
      "here. They mostly stay within one of the four glades " +
      "there. Of course, if you are truly interested in the " +
      "centaurs, the best people to ask are the locals of this " +
      "area, although they tend to mostly be kender.",1);
    add_ask(({"wand","magic wand","apprentice"}),"say My magic wand of " +
      "teleportation has been stolen by my ex-apprentice it would " +
      "seem! I'll need it back to get into my room.",1);
    add_ask(({"fairy dragon","fairy dragon egg","fairy dragons","dragon egg",
      "fairy dragon eggs","dragon eggs","egg","eggs"}),"say Fairy " +
      "dragons are mischievous creatures that are not uncommon in the " +
      "forests of Balifor. Mind, they are not easy to find... often very " +
      "well hidden.", 1);

    add_ask(({"help","spell","teach magic","teach spell","magic","spells"}),
    VBFC_ME("spell_hint"));

    trig_new("%w 'introduces' %s","react_to_intro");

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
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

void
attacked_by(object ob)
{
	::attacked_by(ob);
	mixed weapons = TO->query_weapon(-1);

	if (sizeof(weapons) == 1 && weapons[0]->id("_ferm_magic_staff_"))
	{
	    string chant_str = weapons[0]->query_chant_str();
		TO->command("chant " + chant_str);
	}
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_unique(WEP, 10, WEP2)->move(TO,1);
    command("wield all");
    clone_object(FOBJ + "armour/g_robe")->move(TO,1);
    clone_object(FOBJ + "chest_key2")->move(TO,1);
    command("wear all");
}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

int
special_attack(object enemy)
{
    int     attacktype = random(5);

    if (attacktype == 1)
    {
       if(!("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(TO)))
       {
         // Cast the magic shield spell if not in effect
          command("arcanfethos");
          return 1;
       }

       if(random(2) == 1)
          command("shochraos");
       else
          command("arcanisvaes");
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

string
quest_hint()
{
    if(TP->test_bit("ansalon",0,11))
    {
	TO->command("say Sorry, I have no tasks for you "+
	  "at present.");
	return "";
    }
    TO->command("scratch chin");
    TO->command("say I have been seeking an item that "+
      "is rumoured to lie hidden around this area, "+
      "a two-handed sword with a flaming blade, an "+
      "ancient relic of Ebon.");
    TO->command("say It is bound to be buried in "+
      "some ruin in the forest.");
    TO->command("say Anyway, if you find it, bring it "+
      "to me and you shall be rewarded.");
    return "";
}

void
calculate_experience(object who)
{
    int xp_base = 150;

    if(who->test_bit("ansalon", 0, 11))
    {
	who->catch_msg("You don't get a prize for doing this " +
	  "quest twice!\n");
	return;
    }

    who->catch_msg("You feel slightly more experienced!\n");
    if(who->query_wiz_level())
    {
	who->catch_msg("xp : " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 11);

    A_QUEST_LOG("quest","Fermammon Quest", who, xp_base);
    return;
}

void
return_give_sword(object from)
{
    object spirit;
    string who, what;

    who = from->query_real_name();
    command("cackle");
    command("say Well done! This relic of Ebon will " +
      "go nicely with the rest of my collection of " +
      "artifacts!");

    calculate_experience(from);
}

void
give_it_back(object ob, object from)
{
    string what, who;

    if (ob->query_no_show())
	return;

    what = L(ob->query_short());
    who = from->query_real_name();
    command("peer " + who);
    command("say Thanks... I think.");
    command("emote mumbles something under his breath " +
      "about his visitors getting stranger and stranger.");
    command("drop map");
    command("drop scroll");
}

void
return_give_wand()
{
    command("hmm");
    command("scratch chin");
    command("emote peers at the wand inquisitively.");
    command("say You know, I lost a wand just like this...");
    command("say I could have sworn my apprentice stole it. I wonder if this is it?");
    command("say Well, guess there is only one way to find out.");
    command("wave wand");
    command("shrug");
}

void
return_give_egg()
{
    string who,
    what;

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        command("eyebrow");
        command("say How did you know I liked fairy dragon eggs?");
        command("shrug");
        command("say Ah well... you know what they say... never look " +
          "a gift horse and all that.");
        command("eat egg");
        return;
    }

    if((this_player()->query_lesser_spells_max() < 1))
    {
        command("eyebrow");
        command("say How did you know I liked fairy dragon eggs?");
        command("shrug");
        command("say Ah well... you know what they say... never look " +
          "a gift horse and all that.");
        command("eat egg");
        return;
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"levexlaraek"))
    {
        command("beam");
        command("say Another egg! Excellent!");
        command("eat egg");
        return;
    }
	
    command("beam");
    command("say Ahah! A fairy dragon egg! Excellent, excellent!");
    command("say Or should I say egg-cellent?");
    command("chortle");
    command("eat egg");
    command("say Anyway enough chat. Let me teach you this spell.");
    this_player()->catch_msg("You are taught how to cast the transmutation spell "+
       "'levex laraek', and quickly scribe it down in your spellbook.\n");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"levexlaraek");

    return;
}

void
remove_sword_object(object ob)
{
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
	return;

    if(ob->id("_ansalon_flaming_sword_"))
    {
	set_alarm(1.0, 0.0, &return_give_sword(from));
	set_alarm(1.5, 0.0, &remove_sword_object(ob));
	return;
    }

    if(ob->id("coins"))
    {
	command("eyebrow");
	command("say Money? For me?");
	command("cackle");
	command("emote counts his money and puts it in his robe.");
	return;
    }

    if(ob->id("wand"))
    {
	set_alarm(1.0, 0.0, &return_give_wand());
	return;
    }

    if(ob->id("_fairy_dragon_egg"))
    {
	set_alarm(1.0, 0.0, &return_give_egg());
	return;
    }


    if(ob->id("coin"))
    {
	command("eyebrow");
	command("say Money? For me?");
	command("cackle");
	command("emote counts his coins and puts them in his robe.");
	return;
    }

    if(ob->id("robe"))
	return;

    if(ob->id("staff"))
	return;
    if(ob->id("key"))
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
        command("ponder");
        command("say After my last apprentice ended up stealing " +
          "from me, I am not terribly interested in training " +
          "another one.");
        command("say If you are interested in magic, I suggest " +
          "learning the basics at the School of High Magic near " +
          "Solace.");
        command("say Do that, and I may be gracious enough to teach " +
          "you a few tricks... for a price of course.");
        return "";
    }

    if((this_player()->query_lesser_spells_max() < 1))
    {
        command("say I could teach you a useful transmutation, " +
             "however you do not seem skilled enough to be able " +
             "to cast it.");
        command("say Come back to me when you have progressed " +
             "in your training where you can cast lesser spells.");

        if(!SOHM_MANAGER->query_scribed_spell(this_player(),
           "chikohk"))
        {
           command("ponder");
           command("say In the meantime, perhaps you may find " +
             "lost magicks in the ruins in the forest south of " +
             "Flotsam?");
           command("say The ruins of Ebon have a reputation amongst " +
             "treasure hunters of being full of magical relics...");
           command("say ..and being haunted.");
           command("shrug"); 
        }
        return "";
    }

    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
        command("ponder");
        command("say Your spellcraft skills are too poor for me to " +
           "teach you anything.");
        command("say Come back to me when you are more skilled in spell " +
           "lore.");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"levexlaraek"))
    {
        command("emote strokes his wispy white beard thoughtfully.");
        command("say Yes, I could teach you a spell you may find very " +
           "useful...");
        command("say A transmutation spell that enchants weapons.");
        command("say However...");
        command("say There is a price to be paid for such training.");
        command("smile humourlessly");
        command("say Fairy dragon eggs are a fantastic source of mana.");
        command("emote salivates slightly.");
        command("say Bring me one, and I will teach you that spell.");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(), "chikohk"))
    {
        command("ponder");
        command("say No, there is nothing I wish to teach you.");
        command("say Instead of bothering me, why not search " +
             "the ruins in the forest south of Flotsam?");
        command("say The ruins of Ebon have a reputation amongst " +
             "treasure hunters of being full of magical relics...");
        command("say ..and being haunted.");
        command("shrug"); 
        return "";
    }

    command("ponder");
    command("say No, there is nothing I wish to teach you.");

    return "";
}
