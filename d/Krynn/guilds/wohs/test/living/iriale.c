/*   WoHS quest npc
 *
 *   If mortals report her dialog getting stuck, poke or nudge her!
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <const.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <money.h>

inherit "/d/Krynn/std/monster";

#define WEP_STAFF       "/d/Krynn/solace/poolbottom/obj/wand"
#define HERB_POUCH      "/d/Gondor/common/obj/herbpouch"
#define SATCHEL         "/d/Gondor/common/potions/satchel"
#define BOOTS           "/d/Ansalon/taman_busuk/neraka/arm/boots1"
#define BELT            "/d/Ansalon/taman_busuk/neraka/arm/lbelt"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

// first meet Iriale
#define DIALOG_PROP     "_iriale_currently_dialoguing"
#define FIRST_MET       "_wohs_test_met_iriale"
#define FIRST_INTRO     "_wohs_test_intro_to_iriale"
#define NO_INTRO        "_wohs_test_did_not_intro_to_iriale"
#define NO_INTRO_2      "_wohs_test_did_not_intro_to_iriale_second_time"

// find evidence
#define FIRST_TASK      "_wohs_test_given_first_task"
#define AWARE_OF_PLAN   "_wohs_test_iriale_aware_of_plan" 

// find out how they will invade 
#define SECOND_TASK     "_wohs_test_given_second_task"
#define GRANTED_ACCESS  "_wohs_test_granted_daltigoth_tower_access"
#define SCRY_PROP       "_wohs_test_successful_scry"
#define OBSERVE_PROP    "_wohs_test_successful_observe"

// protect the barbican
#define THIRD_TASK     "_wohs_test_given_third_task" 
#define BATTLE_PROP    "_wohs_test_protected_tower"  
#define FLEE_WARNING   "_wohs_test_flee_warning"

// find the key to the heartroom
#define FOURTH_TASK     "_wohs_test_given_fourth_task"

public void        react_items(object obj, object to);

void get_me_soul();
void arm_me();

int soul_id;
object testee;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("iriale");
    set_living_name("iriale");
    set_title("of Ergoth, High Mage of the Order of the Black Robes and " +
        "Mistress of the Tower of Daltigoth");
    set_race_name("human");
    set_adj("cold");
    add_adj("raven-haired");
    set_gender(G_FEMALE);
    set_long("Before you stands a raven-haired female human of " +
        "indeterminate age cloaked in the black-robes of a Wizard of " +
        "the Orders of High Sorcery. Her face is unhooded, revealing " +
        "cold features that are creased with troubled thoughts.\n");

    set_stats(({160,160,400,300,300,160}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(OBJ_M_NO_ATTACK,"@@check_can_be_attacked");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_AIR, 100);

    add_prop(OBJ_I_RES_POISON, 100);
    set_all_hitloc_unarmed(90);
    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alignment(-1200);

    trig_new("%w 'introduces' %s","react_to_intro");

    set_default_answer("say We are under siege, Aspirant. We do not " +
        "have time for such questions.", 1);

    add_ask(({"help","task","quest"}),VBFC_ME("help_hint"));
    add_ask(({"missive","highmage","jorelia","highmage jorelia",
        "conclave"}), VBFC_ME("missive_hint"));
    add_ask(({"clerical presbyters","presbyters","presbyter"}),"say Be " +
        "wary of the Imperial Presbyters besieging our grove. Their " +
        "divine magics are potent, although they rely heavily on holy " +
        "pillars of flame in battle... so can be easily countered with " +
        "appropriate resistance spells.", 1);
    add_ask(({"light cavalry","cavalry","ergothian cavaliers",
        "cavaliers"}),"say The Ergothian cavaliers and imperial light " +
        "cavalry are some of the finest warriors in the realms, second " +
        "only to the knights of Solamnia.", 1);
    add_ask(({"scouts","scout","ergothian scouts"}),"say Ergothian " +
        "scouts have been sent into the grove. While it seems the " +
        "enchantments of the grove are still effective, keep your " +
        "guard up around them. While not as skilled in battle as " +
        "Ergothian cavaliers, they make up for it with dirty tricks " +
        "that can be more troublesome than an honourable sword and " +
        "shield wielder!", 1);
    add_ask(({"grove","kadothan grove","enchantments",
        "protective enchantments","barriers"}), "say Surrounding our " +
        "Tower of High Sorcery here in Daltigoth is the Kadothan Grove. " +
        "As with all the Towers of High Sorcery it is empowered with " +
        "protective enchantments, in our case generating a lethargy " +
        "resulting in an ensorcelled sleep.", 1);
    add_ask(({"test","test of high sorcery"}),"say Aspirant, with the " +
        "Orders on the verge of war with Istar, now is not the time " +
        "to talk about taking the Test of High Sorcery.", 1);
    add_ask(({"emperor","ergothian emperor","gwynned","emperor gwynned",
        "emperor of ergoth"}), "say Emperor Gwynned oversees an empire " +
        "in decline. Once the most powerful force on the continent, " +
        "now shadowed by Istar and Solamnia. He has followed the " +
        "Kingpriest into a Holy War against sorcery.", 1);
    add_ask(({"divine hammer","order of the divine hammer"}),
        "say The Order of the Divine Hammer are an army of Istarian " +
        "knights, loyal to the Kingpriest. Their numbers were " +
        "unrivaled, although recently have been thinned in their " +
        "attempt to purge the minotaur lands, and by an attack by " +
        "one of our own, Andras Rannoch.", 1);
    add_ask(({"daltigoth","daltigoth city","city","capital"}),
        "say Daltigoth city, the capital of the Empire of Ergoth and " +
        "the location of the crimson tower of High Sorcery known as " +
        "Rathfast! Before which you now stand.", 1);
    add_ask(({"army","armies","armed forces"}), "say An army of " +
        "Ergothian cavaliers, light cavalry and presbyters with the " +
        "holy powers of Corij surround our grove and attacking anyone " +
        "who dares exit. The only thing keeping them from entering " +
        "the grounds of the Tower is the protective enchantments of the " +
        "Kadothan Grove surrounding us.", 1);
    add_ask(({"corij","kiri-jolith"}), "say Corij? You don't know your " +
        "much of the Holy Order of the Stars, do you Aspirant. " +
        "You may know that god as Kiri-Jolith. You'll find many of the " +
        "clerical presbyters besieging us are worshippers of that " +
        "cow-faced god.", 1);
    add_ask(({"tower","rathfast","crimson tower","tower of high sorcery"}),
        "say You stand before the Rathfast, the crimson tower of High " +
        "Sorcery in the city of Daltigoth. One of the few bastions of " +
        "safety for spellcasters like us, although even that is " +
        "questionable at the moment with the Tower besieged.", 1);
    add_ask(({"duke","serl","duke serl","duke serl kar-thon",
        "serl kar-thon"}), "say Duke Serl of House Kar-thon... a " +
        "reckless nobleman in charge of the forces besieging us. Two " +
        "of his sons died when the mage Andras tried to assassinate " +
        "the Kingpriest of Istar, so he holds no love for wizards!", 1);
    add_ask(({"andras","andras rannoch","fool andras"}), 
        VBFC_ME("andras_hint"));   
    add_ask(({"war","siege","declared war","inauspicious time","emperor",
        "holy war"}), VBFC_ME("siege_hint"));
    add_ask(({"evidence","suspicions"}), VBFC_ME("evidence_hint"));
    add_ask(({"spy","spying","spying on duke serl","spy on duke serl",
        "spying on duke serl kar-thon"}), VBFC_ME("spy_hint"));
    add_ask(({"report","report back","observed","black tree",
        "tree of black needles", "tree of black bark","observation",
        "observations"}), VBFC_ME("report_hint"));
    add_ask(({"key","shadow key","vault","vault of secrets"}), 
        VBFC_ME("key_hint"));
    add_ask(({"heartroom","heart room","disrupt","disrupt the flow of " +
        "magic","means", "arcane lock", "lock"}), 
        VBFC_ME("heartroom_hint"));
    add_ask(({"halls","hall","halls of shadow","hall of shadow",
        "halls of shifting shadows", "hall of shifting shadows",
        "permission", "halls of shadows","hall of shadows"}), 
        VBFC_ME("hall_of_shadows_hint"));
    add_ask(({"maze of mirrors","maze"}), VBFC_ME("maze_of_mirrors_hint"));
    add_ask(({"moons of magic","moons","guardian","guardian of the maze",
        "resources"}), VBFC_ME("moons_guardian_hint"));
    add_ask(({"escape","flee","flee the tower"}), VBFC_ME("escape_hint"));
    add_ask(({"vault"}), VBFC_ME("vault_hint"));
    add_ask(({"destroy the tower","tower's destruction","explosion",
        "magical blast"}), VBFC_ME("explosion_hint"));
    add_ask("artifact","smile mysterious", 1);
    add_ask("library","say Yes, don't be surprised the Tower has a " +
        "library of all things! Not as extensive as the library in " +
        "Wayreth or Palanthas, and less impressive since we evacuated " +
        "most of the spellbooks.", 1);
    add_ask("chamber of eyes","say The Chamber of Eyes is where " +
        "diviners may make use of their scrying magic most " +
        "effectively.", 1);

}

string
check_can_be_attacked()
{
    if(TP->query_npc())
        return 0;
    else
        return "A powerful magic shield protects her from being " +
            "attacked.\n";
}

void
arm_me()
{
    object robe;

    clone_object(WEP_STAFF)->move(TO,1);
    command("hold wand");
    clone_object(WOHS_GUILD_OBJECT)->move(TO, 1);
    robe = clone_object(WOHS_ROBE);
    robe->set_robe_colour("black");
    robe->move(TO, 1);
    clone_object(BELT)->move(TO,1);
    clone_object(HERB_POUCH)->move(TO,1);
    clone_object(SATCHEL)->move(TO,1);
    command("wear all");
    command("tie pouch");
    command("tie satchel");
}

/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    set_alarm(1.0, 0.0, &react_items(ob, this_player()));
} /* show_hook */

/*
 * Function name:        react_items
 * Description  :        have the npc respond to a specific object
 * Arguments    :        object obj - the object that was shown
 *                       object to  - the player who showed it
 */
public void
react_items(object obj, object to)
{

    if (obj->id("_wohs_test_duke_orders"))
    {
        command("narrow .");
        command("say Are they missives or orders? Best give them to me " +
            "Aspirant.");
        return;
    }
 
    command("say It is not clear why you are showing me that, Aspirant.");
    return;
} /* react_items */

void
return_give_orders(object ob, object from)
{

   string who, what;
   who = from->query_real_name();

   from->add_prop(AWARE_OF_PLAN, 1);

   command("unfurl orders");
   command("read orders");

   if(from->query_prop(SCRY_PROP) || from->query_prop(OBSERVE_PROP))
   {
      command("say Another order planning to attack... it looks like " +
          "Duke Serl made a few of them.");

      return;
   }

   add_prop(DIALOG_PROP, 1);

   if(!from->query_prop(FIRST_TASK))
   {
       command("say These aren't missives from Highmage Jorelia! These " +
           "are plans for an assault on the Towers of High Sorcery!");
       command("say Aspirant, you have stumbled across the orders that " +
           "escalate the tensions between the Orders of High Sorcery " +
           "and the nations of Krynn to full blown war.");
   }

   WOHS_MANAGER->add_wohs_test_props(from, GRANTED_ACCESS, 1);
   WOHS_MANAGER->add_wohs_test_props(from, SECOND_TASK, 1);

   set_alarm(1.5,0.0, &command("say It is as I feared, the forces " +
       "besieging our grove have discovered a way to bypass the " +
       "protective enchantments of the Tower of High Sorcery."));
   set_alarm(2.5,0.0, &command("curse frust"));
   set_alarm(3.0,0.0, &command("say How? How will they weaken our " +
       "barriers?"));
   set_alarm(4.5,0.0, &command("say I need to know how they plan on " +
       "doing that!"));
   set_alarm(6.5,0.0, &command("say Aspirant, I task you with spying on " +
       "Duke Serl Kar-thon, Praetor-General of the Imperial Armies, and " +
       "finding out the means in which he will break through our grove."));
   set_alarm(8.5,0.0, &command("say You will have little chance of " +
       "finding out this information without using your Arts..."));
   set_alarm(10.5,0.0, &command("say So I grant you access to the inner " +
       "sanctum of the Tower of High Sorcery."));
   set_alarm(10.5,0.0, &from->add_prop(GRANTED_ACCESS, 1));
   set_alarm(10.5,0.0, &WOHS_MANAGER->add_wohs_test_props(from, 
       GRANTED_ACCESS, 1));
   set_alarm(12.5,0.0, &command("say You will be able to refresh your " +
       "spells and prepare yourself for the task ahead."));
   set_alarm(14.0,0.0, &command("say Return to me when you have found " +
       "out how Duke Serl is going to weaken our barriers!"));
   set_alarm(14.0,0.0, &from->add_prop(SECOND_TASK, 1));
   set_alarm(14.0,0.0, &WOHS_MANAGER->add_wohs_test_props(from, 
       SECOND_TASK, 1));
   set_alarm(14.0,0.0, &remove_prop(DIALOG_PROP));

}

void
give_it_back(object ob, object from)
{
    if (!objectp(ob))
        return;

    if(!ob->id("_wohs_test_duke_orders"))
    {
	if (ob->query_prop(OBJ_M_NO_DROP))
	    return;

        command("peer "+OB_NAME(ob));
        command("eyebrow quiz");
        command("say What is this? Some sort of strange gift?");
        command("drop "+OB_NAME(ob)); 
	return;
    }

    command("emote narrows her eyes alarmingly.");
    command("say I do not take gifts from strange intruders.");
    command("say I would suggest doing as I say, and introduce " +
        "yourself as I instructed!");
    command("drop "+OB_NAME(ob)); 
    from->add_prop(NO_INTRO, 1);
    WOHS_MANAGER->add_wohs_test_props(from, NO_INTRO, 1);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_wohs_test_duke_orders") && from->query_prop(FIRST_INTRO))
    {
	set_alarm(1.0,0.0, &return_give_orders(ob, from));
	return;
    }

    if(ob->id("wand"))
	return;
    if(ob->id("robe"))
	return;
    if(ob->id("pouch"))
	return;
    if(ob->id("satchel"))
	return;
    if(ob->id("spellbook"))
	return;
    if(ob->query_no_show())
	return;
    if(ob->id("belt"))
	return;

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

void
get_me_soul()
{
    add_cmdsoul(WOHS_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
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

int
query_guild_level_occ()
{
    return 12;
}

public int
can_ignore_ingredients(object caster)
{
    return 1;
}

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    set_alarm(0.5, 0.0, &command("kepeskwiivai"));

}

public int
no_repeat_harm_spell()
{
    return 0;
}

int
query_cantrip_spells_max()
{
    return 4;
}

int
query_minor_spells_max()
{
    return 4;
}

int
query_lesser_spells_max()
{
    return 4;
}

int
query_greater_spells_max()
{
    return 4;
}

void
react_to_intro(string who,string garbage)
{
    who = L(who);

    if(who == "serl")
        return;

    set_alarm(2.0, 0.0, "return_intro", who);
}

void
return_intro(string who)
{
    who = L(who); 
    if (P(who,E(TO)))
    {
        if(!TP->query_prop(FIRST_INTRO))
        {
            command("say The Conclave sends me an Aspirant?");
            command("eyebrow incredul");
            command("introduce myself");
            set_alarm(1.5,0.0, &command("say Hmm. Well you will have " +
                "to do."));
            set_alarm(2.5,0.0, &command("say Quickly. What missive has " +
                "Highmage Jorelia sent with you?"));
            TP->add_prop(FIRST_INTRO, 1);
            WOHS_MANAGER->add_wohs_test_props(TP, FIRST_INTRO, 1);
        }
        else
        {           
            command("smile cold");
            set_alarm(1.5,0.0, &command("introduce myself"));
        }
    }
}

void
prepare_introduction(object enemy)
{
    if(enemy->query_npc())
        return;

    if(enemy->query_prop(FIRST_MET))
        return;

    if(enemy->query_wiz_level())
        return;

    add_prop(DIALOG_PROP, 1);

    if(!CAN_SEE(TO, enemy))
    {
        command("emote raises her eyebrows knowingly.");
        command("say You can reveal yourself. No one enters the Tower " +
            "of High Sorcery without my knowing.");
        set_alarm(2.0,0.0, &command("say I detected your magical " +
            "arrival in the Grove."));
        set_alarm(4.0,0.0, &command("say I assume the Conclave has " +
            "sent you to assist me."));
        set_alarm(6.0,0.0, &command("smile cold"));
        set_alarm(8.0,0.0, &command("say Introduce yourself, and brief " +
            "me on what missive Highmage Jorelia has sent with you."));
        set_alarm(8.0,0.0, &remove_prop(DIALOG_PROP));
    }
    else
    {
        command("say to " +enemy->query_real_name()+ " I detected " +
            "your magical arrival in the Grove.");
        set_alarm(2.0,0.0, &command("say to " +enemy->query_real_name()+ 
            " I assume the Conclave has sent you to assist me."));
        set_alarm(4.0,0.0, &command("smile cold"));
        set_alarm(6.0,0.0, &command("say to " +enemy->query_real_name()+ 
            " Introduce yourself, and brief me on what missive " +
            "Highmage Jorelia has sent with you."));
        set_alarm(6.0,0.0, &remove_prop(DIALOG_PROP));
    }

    TP->add_prop(FIRST_MET, 1);
    WOHS_MANAGER->add_wohs_test_props(TP, FIRST_MET, 1);
    return;
}

void 
init_living() 
{
    string race_name = TP->query_race_name();
    set_alarm(1.0, 0.0, &prepare_introduction(TP));
    testee = TP;
 
    ::init_living(); 
}  

public void
emote_hook(string emote, object actor, string adverb, object *oblist,
        int cmd_attr, int target)
{
    if (emote == "poke" || emote == "nudge")
        set_alarm(1.0,0.0, "return_poke");

} 

void
return_poke()
{
    command("emote starts in surprise.");
    command("say Pardon, I was distracted. Did you have a " +
        "question for me?");
    remove_prop(DIALOG_PROP);
}

string
help_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
       return "Iriale is currently answering one of your other " +
           "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(AWARE_OF_PLAN))
   {
        WOHS_MANAGER->add_wohs_test_props(TP, GRANTED_ACCESS, 1);
        WOHS_MANAGER->add_wohs_test_props(TP, SECOND_TASK, 1);

        command("say It is as I feared, the forces besieging us have " +
            "discovered a way to bypass the protective enchantments " +
            "of the Tower of High Sorcery.");
        command("curse frust");
        command("say I need to know how they plan on doing that!");
        set_alarm(1.5,0.0, &command("say Aspirant, I task you with " +
            "spying on Duke Serl Kar-thon, Praetor-General of the " +
            "Imperial Armies, and finding out the means in which he " +
            "will break through our grove."));
        set_alarm(4.5,0.0, &command("say You will have little chance " +
            "of finding out this information without using your " +
            "Arts..."));
        set_alarm(7.5,0.0, &command("say So I grant you access to the " +
            "inner sanctum of the Tower of High Sorcery."));
        set_alarm(7.5,0.0, TP->add_prop(GRANTED_ACCESS, 1));
        set_alarm(7.5,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
            GRANTED_ACCESS, 1));
        set_alarm(8.0,0.0, &command("gesture west"));
        set_alarm(10.5,0.0, &command("say You will be able to refresh " +
            "your spells and prepare yourself for the task ahead."));
        set_alarm(14.0,0.0, &command("say Return to me when you have " +
            "found out how Duke Serl is going to weaken our barriers!"));
        set_alarm(14.0,0.0, TP->add_prop(SECOND_TASK, 1));
        set_alarm(14.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
            SECOND_TASK, 1));
        set_alarm(14.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      WOHS_MANAGER->add_wohs_test_props(TP, FIRST_TASK, 1);
      command("say Dark times have come to practitioners of magic in " +
          "the realms.");
      set_alarm(1.5,0.0, &command("say The Kingpriest of Istar had " +
          "been looking for an excuse to begin a crusade against the " +
          "arcane..."));
      set_alarm(4.5,0.0, &command("say And that fool Andras gave it to " +
          "him with his botched attempt to assassinate his holiness."));
      set_alarm(7.5,0.0, &command("snarl"));
      set_alarm(10.5,0.0, &command("say So now the Kingpriest has " +
          "declared a holy war against magic, and the Emperor of " +
          "Ergoth and Knights of Solamnia have sided with him."));
      set_alarm(14.0,0.0, &command("say As we speak, the Tower is " +
          "being sieged by the Imperial armies of the Ergothian " +
          "Emperor, with his cavalry and clerical presbyters " +
          "surrounding our magical grove here in the city of Daltigoth."));
      set_alarm(17.0,0.0, &command("say The magic enchantments of the " +
          "grove surrounding the Tower should protect us from the " +
          "armies approaching here."));
      set_alarm(20.0,0.0, &command("say Although I am uneasy. The " +
          "leader of the army besieging us has been persistent in " +
          "sending scouts into the grove, knowing the powerful " +
          "enchantments will not let them through."));
      set_alarm(23.5,0.0, &command("say Something is going on " +
          "Aspirant, and I want you to find out what."));
      set_alarm(26.0,0.0, &command("say Return to the grove and seek " +
          "out any evidence you can find that may support my " +
          "suspicions."));
      set_alarm(26.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          FIRST_TASK, 1));
      set_alarm(26.5,0.0, TP->add_prop(FIRST_TASK, 1));
      set_alarm(26.5,0.0, &remove_prop(DIALOG_PROP));
   }

   return "";
}

string
andras_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
       return "Iriale is currently answering one of your other " +
           "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   command("say Andras Rannoch was a brilliant apprentice under the " +
       "tutelage of Nusendran, a dark mage of legendary stature.");
   command("say Nusendran taught him well, and such was Andras's " +
       "talent that he might have ascended to the Conclave, or even " +
       "higher.");
   command("frown");
   set_alarm(4.5,0.0, &command("say Scarcely more than a year after " +
       "his initiation into the Orders however, tragedy struck. On a " +
       "mission to gather black lamb's blood, Nusendran and Andras " +
       "were caught by the Order of the Divine Hammer, the loyal " +
       "knights of the Kingpriest of Istar."));
   set_alarm(7.5,0.0, &command("say Nusendran burned at the stake, but " +
       "Andras was saved by the archmage Fistandantilus."));
   set_alarm(10.5,0.0, &command("say Recently Andras sought his " +
       "revenge against the Divine Hammer, releasing a horde of imps " +
       "from the Abyss at a tournament in Lattakay, killing a great " +
       "many of their Order."));
   set_alarm(13.5,0.0, &command("say Andras was captured, although the " +
       "Conclave ordered his rescue... our justice would be brought " +
       "against him, not that of others."));
   set_alarm(16.5,0.0, &command("say However Andras managed to escape " +
       "us under suspicious circumstances, and then attempted to " +
       "assassinate the Kingpriest at a meet with our Highmage. The " +
       "end result was death on both sides, the Kingpriest being badly " +
       "wounded and our Highmage slain, and a Holy War being declared " +
       "against us."));
   set_alarm(19.5,0.0, &command("say And now here we are. Besieged by " +
       "the armies of the Empire of Ergoth, and us evacuating our " +
       "tomes and relics to the Tower of Wayreth."));
   set_alarm(22.5,0.0, &command("say All because of that fool Andras."));
   set_alarm(22.5,0.0, &remove_prop(DIALOG_PROP));

   return "";
}


string
missive_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
       return "Iriale is currently answering one of your other " +
           "questions! Patience!\n";  

   if(!TP->query_prop(FIRST_INTRO))
   {   
       command("frown");
       command("say Insolence! I said introduce yourself, and then " +
           "brief me!");
       TP->add_prop(NO_INTRO_2, 1);
       WOHS_MANAGER->add_wohs_test_props(TP, NO_INTRO_2, 1);
       return "";
   }   

   add_prop(DIALOG_PROP, 1);

   command("say Highmage Jorelia? The White Robed enchantress and " +
       "Head of the Conclave?");
   command("say You know nothing of her?");
   command("frown");
   set_alarm(1.5,0.0, &command("say It has been some time since she " +
       "has sent missives to the Tower here, I had assumed you were " +
       "from her..."));
   set_alarm(1.5,0.0, &command("sigh"));
   set_alarm(2.5,0.0, &command("say You have come at an inauspicious " +
       "time Aspirant, as the Emperor of Ergoth has declared war on " +
       "the Orders of High Sorcery and has laid siege to the Tower of " +
       "High Sorcery here in Daltigoth city."));
   set_alarm(2.5,0.0, &remove_prop(DIALOG_PROP));

   return "";
}

string
siege_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
       return "Iriale is currently answering one of your other " +
           "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   command("say Inaspicious times may be an understatement!");
   command("chuckle dark");
   command("say Dark times have come to practitioners of magic in the " +
       "realms.");
   set_alarm(1.5,0.0, &command("say The Kingpriest of Istar had been " +
       "looking for an excuse to begin a crusade against the arcane..."));
   set_alarm(4.5,0.0, &command("say And that fool Andras gave it to " +
       "him with his botched attempt to assassinate his holiness."));
   set_alarm(7.5,0.0, &command("snarl"));
   set_alarm(10.5,0.0, &command("say So now the Kingpriest has " +
       "declared a holy war against magic, and the Emperor of Ergoth " +
       "and Knights of Solamnia have sided with him."));
   set_alarm(14.0,0.0, &command("say As we speak, the Tower is being " +
       "sieged by the Imperial armies of the Ergothian Emperor, with " +
       "his cavalry and clerical presbyters surrounding our magical " +
       "grove here in the city of Daltigoth."));

   if(TP->query_prop(AWARE_OF_PLAN))
   {
      set_alarm(17.0,0.0, &command("say The magic enchantments of the " +
          "grove surrounding the Tower would normally protect us from " +
          "these forces approaching the Tower."));
      set_alarm(20.0,0.0, &command("say But it seems they have found " +
          "a way through... we must determine what that is, and " +
          "awaken the Tower's defences!"));
      set_alarm(20.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      WOHS_MANAGER->add_wohs_test_props(TP, FIRST_TASK, 1);
      set_alarm(17.0,0.0, &command("say The magic enchantments of the " +
          "grove surrounding the Tower should protect us from the " +
          "armies approaching here."));
      set_alarm(20.0,0.0, &command("say Although I am uneasy. The " +
          "leader of the army besieging us has been persistent in " +
          "sending scouts into the grove, knowing the powerful " +
          "enchantments will not let them through."));
      set_alarm(23.5,0.0, &command("say Something is going on Aspirant, " +
          "and I want you to find out what."));
      set_alarm(26.5,0.0, &command("say Return to the grove and seek " +
          "out any evidence you can find that may support my " +
          "suspicions."));
      set_alarm(26.5,0.0, &remove_prop(DIALOG_PROP));
      set_alarm(27.0,0.0, TP->add_prop(FIRST_TASK, 1));
      set_alarm(27.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          FIRST_TASK, 1));
   }

   return "";
}

string
evidence_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(AWARE_OF_PLAN))
   {
      command("say My suspicions are confirmed, the Imperial armies " +
          "have found a way to breach the protective enchantments of " +
          "the grove.");
      remove_prop(DIALOG_PROP);
   }
   else
   {
      command("say Search the grove for anything that might give us " +
          "a better understanding of what is going on.");
      command("say Avoid accidently leaving the grove. The last thing " +
          "you want to do is walk out into the armed forces besieging " +
          "us.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
spy_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(THIRD_TASK))
   {
      set_alarm(1.0,0.0, &command("say I need to awaken the Tower's " +
          "gargoyle guardians. I need you to hold the Imperial forces " +
          "back from passing through the barbican until the guardians " +
          "awake."));
      set_alarm(5.0,0.0, &command("say Prepare yourself for combat! " +
          "Make use of the crimson orb in the library to memorise " +
          "spells suitable for battling scouts, clerical presbyters " +
          "and Imperial cavaliers."));
      set_alarm(10.0,0.0, &command("say Wait for them at the barbican " +
          "entry to our east. Do not let them pass through to me!"));
      set_alarm(13.0,0.0, &command("emote concentrates on a spell of " +
          "awakening. You notice the stone gargoyles along the walls " +
          "of the Tower begin to stir."));
      set_alarm(13.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else if(TP->query_prop(SCRY_PROP))
   {
      WOHS_MANAGER->add_wohs_test_props(TP, THIRD_TASK, 1);
      write("You report to Iriale what you observed through the " +
          "crystal ball.\n");
      command("emote looks troubled.");
      set_alarm(3.0,0.0, &command("say The black pine you saw in your " +
          "divination is a spell both dark and powerful. We have been " +
          "betrayed by one of our own."));
      set_alarm(5.0,0.0, &command("say I was not expecting the Imperial " +
          "forces to be able to bypass our enchantments so swiftly. " +
          "We are dangerously exposed!"));
      set_alarm(8.0,0.0, &command("say I need to awaken the Tower's " +
          "gargoyle guardians. I need you to hold the Imperial forces " +
          "back from passing through the barbican until the guardians " +
          "awake."));
      set_alarm(14.0,0.0, &command("say Prepare yourself for combat! " +
          "Make use of the crimson orb in the library to memorise " +
          "spells suitable for battling scouts, clerical presbyters " +
          "and Imperial cavaliers."));
      set_alarm(14.0,0.0, &command("say Wait for them at the barbican " +
          "entry to our east. Do not let them pass through to me!"));
      set_alarm(14.0,0.0, TP->add_prop(THIRD_TASK, 1));
      set_alarm(14.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          THIRD_TASK, 1));
      set_alarm(14.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else if(TP->query_prop(OBSERVE_PROP))
   {
      WOHS_MANAGER->add_wohs_test_props(TP, THIRD_TASK, 1);

      write("You report to Iriale what you observed spying on the " +
          "Imperial forces.\n");
      command("emote looks troubled.");
      set_alarm(3.0,0.0, &command("say The black pine you saw is a " +
          "spell of summoning both dark and powerful. We have been " +
          "betrayed by one of our own."));
      set_alarm(5.0,0.0, &command("say I was not expecting the " +
          "Imperial forces to be able to bypass our enchantments so " +
          "swiftly. We are dangerously exposed!"));
      set_alarm(8.0,0.0, &command("say I need to awaken the Tower's " +
          "gargoyle guardians. I need you to hold the Imperial forces " +
          "back from passing through the barbican until the guardians " +
          "awake."));
      set_alarm(14.0,0.0, &command("say Prepare yourself for combat! " +
          "Make use of the crimson orb in the library to memorise " +
          "spells suitable for battling scouts, clerical presbyters " +
          "and Imperial cavaliers."));
      set_alarm(14.0,0.0, &command("say Wait for them at the barbican " +
          "entry to our east. Do not let them pass through to me!"));
      set_alarm(14.0,0.0, TP->add_prop(THIRD_TASK, 1));
      set_alarm(14.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          THIRD_TASK, 1));
      set_alarm(14.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else if(TP->query_prop(AWARE_OF_PLAN))
   {
      WOHS_MANAGER->add_wohs_test_props(TP, SECOND_TASK, 1);

      command("say I task you with spying on Duke Serl Kar-thon, " +
          "Praetor-General of the Imperial Armies, and finding out the " +
          "means in which he will break through our grove.");
      command("say He is leading the army surrounding our grove.");
      set_alarm(3.0,0.0, &command("say You will not learn anything by " +
          "confronting him directly, so I suggest you use your Arts " +
          "to spy on him."));
      set_alarm(6.0,0.0, &command("say If you need to spend some time " +
          "refreshing your spells, I suggest making use of an artifact " +
          "in the library of the Tower to do so."));
      set_alarm(6.0,0.0, &remove_prop(DIALOG_PROP));
      set_alarm(6.0,0.0, &command("gesture west"));
      set_alarm(6.0,0.0, TP->add_prop(SECOND_TASK, 1));
      set_alarm(6.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          SECOND_TASK, 1));
      set_alarm(6.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that for, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
report_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   if(!CAN_SEE(TO, TP))
   {
     return "You are not visible. You need to reveal yourself to " +
         "report back to Iriale.\n";
   } 

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(THIRD_TASK))
   {
      set_alarm(1.0,0.0, &command("say I need to awaken the Tower's " +
          "gargoyle guardians. I need you to hold the Imperial forces " +
          "back from passing through the barbican until the guardians " +
          "awake."));
      set_alarm(5.0,0.0, &command("say Prepare yourself for combat! " +
          "Make use of the crimson orb in the library to memorise " +
          "spells suitable for battling scouts, clerical presbyters " +
          "and Imperial cavaliers."));
      set_alarm(10.0,0.0, &command("say Wait for them at the barbican " +
          "entry to our east. Do not let them pass through to me!"));
      set_alarm(13.0,0.0, &command("emote concentrates on a spell of " +
          "awakening. You notice the stone gargoyles along the walls " +
          "of the Tower begin to stir."));
      set_alarm(13.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else if(TP->query_prop(SCRY_PROP))
   {
      WOHS_MANAGER->add_wohs_test_props(TP, THIRD_TASK, 1);

      write("You report to Iriale what you observed through the " +
          "crystal ball.\n");
      command("emote looks troubled.");
      set_alarm(3.0,0.0, &command("say The black pine you saw in " +
          "your divination is a spell both dark and powerful. We have " +
          "been betrayed by one of our own."));
      set_alarm(5.0,0.0, &command("say I was not expecting the " +
          "Imperial forces to be able to bypass our enchantments so " +
          "swiftly. We are dangerously exposed!"));
      set_alarm(8.0,0.0, &command("say I need to awaken the Tower's " +
          "gargoyle guardians. I need you to hold the Imperial forces " +
          "back from passing through the barbican until the guardians " +
          "awake."));
      set_alarm(14.0,0.0, &command("say Prepare yourself for combat! " +
          "Make use of the crimson orb in the library to memorise " +
          "spells suitable for battling scouts, clerical presbyters " +
          "and Imperial cavaliers."));
      set_alarm(14.0,0.0, &command("say Wait for them at the barbican " +
          "entry to our east. Do not let them pass through to me!"));
      set_alarm(14.0,0.0, TP->add_prop(THIRD_TASK, 1));
      set_alarm(14.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          THIRD_TASK, 1));
      set_alarm(14.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else if(TP->query_prop(OBSERVE_PROP))
   {
      WOHS_MANAGER->add_wohs_test_props(TP, THIRD_TASK, 1);

      write("You report to Iriale what you observed spying on the " +
          "Imperial forces.\n");
      command("emote looks troubled.");
      set_alarm(3.0,0.0, &command("say The black pine you saw is a " +
          "spell of summoning both dark and powerful. We have been " +
          "betrayed by one of our own."));
      set_alarm(5.0,0.0, &command("say I was not expecting the " +
          "Imperial forces to be able to bypass our enchantments so " +
          "swiftly. We are dangerously exposed!"));
      set_alarm(8.0,0.0, &command("say I need to awaken the Tower's " +
          "gargoyle guardians. I need you to hold the Imperial forces " +
          "back from passing through the barbican until the guardians " +
          "awake."));
      set_alarm(14.0,0.0, &command("say Prepare yourself for combat! " +
          "Make use of the crimson orb in the library to memorise " +
          "spells suitable for battling scouts, clerical presbyters " +
          "and Imperial cavaliers."));
      set_alarm(14.0,0.0, &command("say Wait for them at the barbican " +
          "entry to our east. Do not let them pass through to me!"));
      set_alarm(14.0,0.0, TP->add_prop(THIRD_TASK, 1));
      set_alarm(14.0,0.0, &WOHS_MANAGER->add_wohs_test_props(TP, 
          THIRD_TASK, 1));
      set_alarm(14.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that for, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
key_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say The shadow key unlocks the " +
          "Heartroom of the Tower, a chamber where the Tower's magic " +
          "runs strongest."));
      set_alarm(5.0,0.0, &command("say Within the Heartroom you will " +
          "find the means to disrupt the flow of the magic of the " +
          "Tower, creating an incredible magical blast that will " +
          "destroy the Tower completely."));
      set_alarm(10.0,0.0, &command("say The shadow key resides in the " +
          "Tower's vault. To access the vault you must work your way " +
          "through the Maze of Mirrors in the Halls of Shifting " +
          "Shadows."));
      set_alarm(13.0,0.0, &command("say I have granted you access to " +
          "the Halls, however to figure out the maze you may need to " +
          "call on some of the resources of the library."));
      set_alarm(13.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that for, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
heartroom_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say The Heartroom of the Tower is " +
          "a chamber where the Tower's magic flows strongest."));
      set_alarm(5.0,0.0, &command("say Here you will find the means " +
          "to disrupt the flow of the magic of the Tower, creating an " +
          "incredible magical blast that will destroy the Tower " +
          "completely."));
      set_alarm(10.0,0.0, &command("say The Heartroom is protected " +
          "with an arcane lock that can only be opened by the shadow " +
          "key."));
      set_alarm(10.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about the " +
          "Heartroom, Aspirant. That is a room you need not concern " +
          "yourself with at this point.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
hall_of_shadows_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say The Halls of Shifting Shadows " +
          "takes many forms, with no set layout. It is where " +
          "illusionists practice their forms, and is also " +
          "where you will find the entry to the Maze of Mirrors."));
      set_alarm(5.0,0.0, &command("say Successfully navigating the " +
          "Maze of Mirrors will take you to the vault of the Tower " +
          "where you will find the shadow key to unlock the Heartroom."));
      set_alarm(10.0,0.0, &command("say Just be warned, the vault is " +
          "not unguarded."));
      set_alarm(10.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say You have no need of accessing the Halls of Shifting " +
          "Shadows, Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
maze_of_mirrors_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say The Maze of Mirrors is " +
          "challenging to the uninitiated, however even the lowliest " +
          "of apprentices is capable of navigating through the maze, " +
          "armed only with an understanding of the Moons of Magic."));
      set_alarm(4.0,0.0, &command("say Mind, entering the vault " +
          "requires the ability to defeat the guardian of the maze. " +
          "That can be a challenge."));
      set_alarm(7.0,0.0, &command("say If you remember nothing else " +
          "I tell you Aspirant, while navigating through the maze " +
          "always be seeking the Night of the Eye!"));
      set_alarm(7.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that for, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
moons_guardian_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("eyeroll"));
      set_alarm(2.0,0.0, &command("say When I said now was the time " +
          "to ask me any questions, I didn't intend to give lessons! " +
          "We don't have time for that Aspirant!"));
      set_alarm(5.0,0.0, &command("say If you are a quick reader, you " +
          "may find resources in the library that can help you " +
          "understand that."));
      set_alarm(5.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that for, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
vault_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say In better days, the vault " +
          "contained all our most powerful relics and dangerous " +
          "spellbooks... however the Conclave felt in prudent to " +
          "move them all to the Tower of Wayreth."));
      set_alarm(5.0,0.0, &command("say What still remains in the " +
          "vault is the shadow key that opens the lock of the Tower's " +
          "Heartroom."));
      set_alarm(5.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
escape_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say Your window of opportunity " +
          "to escape the Tower before it explodes would be small."));
      set_alarm(5.0,0.0, &command("say However, with the energies of " +
          "the Tower being disrupted you may be able to escape " +
          "through the pool in the Tower's hall if you have some " +
          "sort of teleportation spell."));
      set_alarm(5.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}

string
explosion_hint()
{ 
   if(TO->query_prop(DIALOG_PROP))
     return "Iriale is currently answering one of your other " +
         "questions! Patience!\n";        

   add_prop(DIALOG_PROP, 1);

   if(TP->query_prop(FOURTH_TASK))
   {
      set_alarm(1.0,0.0, &command("say It was anticipated by the " +
          "Conclave that extreme measures may need to be taken in " +
          "the event of any of the Towers of High Sorcery being taken."));
      set_alarm(5.0,0.0, &command("say The destruction of this Tower " +
          "will be a great loss to magic. But the alternative bares " +
          "not thinking about. And it may be an appropriate warning " +
          "to the mundane fools who attack us of how high a price " +
          "they will need to pay to take a Tower of High Sorcery."));
      set_alarm(5.0,0.0, &remove_prop(DIALOG_PROP));
   }
   else
   {
      command("say I am not sure why you are asking about that, " +
          "Aspirant.");
      remove_prop(DIALOG_PROP);
   }

   return "";
}
