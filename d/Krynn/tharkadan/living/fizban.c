#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <money.h>

inherit "/d/Krynn/std/monster";

#define WEP_STAFF    "/d/Ansalon/balifor/flotsam_forest/obj/weapon/staff"
#define HERB_POUCH   "/d/Gondor/common/obj/herbpouch"
#define SATCHEL      "/d/Gondor/common/potions/satchel"
#define BOOTS        "/d/Ansalon/taman_busuk/neraka/arm/boots1"
#define BELT         "/d/Ansalon/taman_busuk/neraka/arm/lbelt"

#define MANA_SHADOW  "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define DIALOG_PROP  "_fizban_currently_dialoguing"

void get_me_soul();
void arm_me();

int soul_id;
object robe, belt, pouch, satchel, guild_ob, staff;

string
wohs_extra()
{
    if(WOHS_IS_MEMBER(TP))
      return " Yet you get the feeling he is far from harmless, " +
          "as he exudes an incredible aura of power.";
    else
      return "";
}

string
no_attack()
{
   if(TP->query_npc() && TP->query_race_name() == "draconian")
     return 0;

   if(TP->query_guild_name_occ() == "Priests of Takhisis")
     return "As you approach " +COMPOSITE_LIVE(TO)+ " with hostile " +
       "intent, you feel the presence of the Dark Queen withdraw... " +
       "as if she was not prepared for this engagement. You decide to " +
       "follow her lead and leave this strange individual alone.\n";

   TP->catch_msg("You approach " +QTNAME(TO)+ " threateningly. " +
       QCTNAME(TO)+ " suddenly turns and stares at you with a lucid " +
       "gaze that radiates incredible menace and power.\n");
   tell_room(environment(TP), QCTNAME(TP)+ " approaches " +
       QTNAME(TO)+ " threateningly. " +QCTNAME(TO)+ " suddenly turns " +
       "and stares at " +QTNAME(TP)+ " with a lucid gaze that " +
       "radiates incredible menace and power.\n" +
       QCTNAME(TP)+ " steps back, seriously shaken.\n", ({ TP }), TP);

   TP->add_panic(500);
   TP->set_whimpy_dir("northwest");
   TP->run_away();
   return "Shaken, you retreat to regain your nerve.\n";
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("fizban");
    set_living_name("fizban");
    set_title("the Fabulous");
    set_race_name("human");
    set_adj("befuddled");
    add_adj("grey robed");
    set_gender("G_MALE");
    set_long("Before you stands an old man dressed in grey robes and a " +
        "bent conical hat. Engaged in a furious one-sided argument with " +
        "the lonely oak tree standing here, this man is clearly " +
        "befuddled.@@wohs_extra@@\n");

    set_stats(({90,160,400,400,400,200}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(OBJ_M_NO_ATTACK, "@@no_attack");

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

    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_RES_POISON, 100);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_all_hitloc_unarmed(200);

    set_act_time(20);
    add_act("emote angrily shakes a worn walking staff at the lonely " +
         "oak tree.");
    add_act("emote says sternly to the lonely oak tree: I say, did you " +
        "hear me? I said move your shadow, and I meant it!");
    add_act("emote beats vigorously on the tree with his staff.");
    add_act("emote mumbles: ...spell for vagrant trees. Hmm, what was " +
        "it again? Fizbut? Furball?");
    add_act("say My hat! Where's my hat!");
    add_act("get all");

    set_cact_time(2);
    add_cact("cast ixengarmth");

    trig_new("%w 'introduces' %s","react_to_intro");

    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alignment(1200);

    set_default_answer(VBFC_ME("default_answer"));

    add_ask(({"spell","teach magic","teach spell","magic","spells"}),
        VBFC_ME("spell_hint"));
    add_ask(({"tree","oak tree","lonely oak tree","oak"}),
        VBFC_ME("tree_hint"));
    add_ask(({"tree limb","limb","long shadow","shadow"}),
        VBFC_ME("limb_hint"));
    add_ask(({"fizban","fizban the fabulous"}),VBFC_ME("fizban_hint"));
    add_ask(({"fireball"}),VBFC_ME("fireball_hint"));
    add_ask(({"dragonlance"}),VBFC_ME("dragonlance_hint"));
    add_ask(({"narrative"}),VBFC_ME("narrative_hint"));
    add_ask(({"paladine","valiant warrior"}),
        VBFC_ME("paladine_hint"));
    add_ask(({"quest","task","help"}), VBFC_ME("quest_hint"));

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
        command("say Hmph? Oh! Now what was my name again...");
        set_alarm(1.5,0.0, &command("say Oh yes..."));
        set_alarm(1.5,0.0, &command("introduce myself"));
        set_alarm(3.5,0.0, &command("say Yes that's it. Fizban."));
        set_alarm(3.5,0.0, &command("smile brightly"));
    }
}

void
arm_me()
{
    staff = clone_object(WEP_STAFF);
    staff->move(TO,1);
    command("wield all");

    guild_ob = clone_object(WOHS_GUILD_OBJECT);
    guild_ob->move(TO, 1);
    robe = clone_object(WOHS_ROBE);
    robe->set_robe_colour("grey");
    robe->move(TO, 1);
    belt = clone_object(BELT);
    belt->move(TO,1);
    pouch = clone_object(HERB_POUCH);
    pouch->move(TO,1);
    satchel = clone_object(SATCHEL);
    satchel->move(TO,1);

    command("wear all");
    command("tie pouch");
    command("tie satchel");

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
    return "white";
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

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
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

// Fizban can't die... he just vanishes mysteriously (or chases his hat).

public void
do_die(object killer)
{
    command("emote suddenly has his hat blown off his head by a great " +
        "gust of wind.");
    command("say My hat!");
    command("emote ambles off to the southeast chasing his hat.");

    TO->remove_object();
}

// Question responses

string
default_answer()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   if(random(2))
   {
      command("say Now that is an interesting question.");
      command("say And I do hope you find someone who can help you " +
          "with that!");
      command("say I would help, however I am currently quite busy. " +
          "This oak has a lot to answer for!");
      command("emote whacks the lonely oak tree with his staff.");
      return "";
   }
   else if(random(2))
   {
      command("say Hmm. Yes. Now I knew the answer to that question...");
      command("ponder");
      command("say Don't tell me... it will come to me any second now...");
      command("think");
      return "";
   }

   command("frown irrit");
   command("say How am I supposed to know that?");
   command("say What do I look like? A god?");
   return "";
}

string
spell_hint()
{
    if(TO->query_prop(DIALOG_PROP))
       return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

    if(this_player()->query_guild_name_occ() != "Wizards of High Sorcery" &&
       this_player()->query_guild_name_occ() != "School of High Magic") 
    {
        command("emote scratches his beard.");
        command("say You want to learn magic hey?");
        command("think");
        command("say There is a school of magic up near Solace. While " +
           "the school master is a dolt, you should be able to pick up " +
           "a few tricks there.");
        return "";
    }

    if((this_player()->query_advanced_spells_max() < 1)) 
    {
        command("say You're magi? No kidding!");
        command("emote looks immensely tickled.");
        command("say Small world Krynn! I'll have to teach you a few of " +
            "my spells...");
        command("say ...when you are capable of more advanced " +
            "incantations.");
        command("say Come back to me then.");
        command("smile bright");
        return "";
    }

    if(WOHS_MANAGER->query_scribed_spell(this_player(),"ixengarmth"))
    {
        command("smile vagu");
        command("say Oh, I am sure I could teach you another spell...");
        command("think");
        command("emote mutters to himself, and gets distracted by a " +
           "shadow cast by a lonely oak tree nearby.");
        return "";
    }

    command("say You're magi? No kidding!");
    command("emote looks immensely tickled.");
    command("say Small world Krynn! I'll have to teach you a few of my " +
        "spells...");
    command("think");
    command("say Now what was the name of that spell again? Fireplace? " +
        "Furball?");

    TO->add_prop(DIALOG_PROP, 1);
    E(TO)->summon_dragonarmy_patrol(TP);

    return "";
}

string
tree_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   command("emote stares suspiciously towards the lonely oak tree.");
   command("say Oaks. Can't be trusted... this one in particular!");
   command("say Did you know they can capture your soul?");
   command("eyebrow wild");
   command("say Because if you believe that, you are a bigger bumpkin " +
       "than you look!");
   command("snort amuse");
   command("say Still, 'ware the shadow!");
   command("emote waves his arms around while softly cooing 'wooo!!'.");

   return "";
}

string
limb_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   command("emote points to the tree limb overhanging the path.");
   command("say That tree limb...");
   command("emote points to the long shadow cast by the tree limb " +
       "across the path.");
   command("say ...is colluding with that shadow. There is something " +
       "sinister going on.");
   command("say I am not sure what, but I am going to figure it out.");
   command("frown");
   return "";
}

string
fizban_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   command("jump");
   command("say Fizban? Where!");
   command("say Oh. You mean me.");
   command("smile sheepishly");
   return "";
}

string
fireball_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   command("say Ah, fireball... a great spell.");
   command("say I once knew a joke about a fireball...");
   command("say Punchline was 'that's the way the fireball bounces'!");
   command("chortle");
   return "";
}

string
dragonlance_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
         "possibly with a tree. You may want to wait a moment and ask " +
         "again when you are likely to catch his attention?\n";

   command("say Of I've come across Dragonlances in my time.");
   command("smile knowing");
   command("say It was a weapon similar to.. no, actually it was " +
       "closer to..");
   command("ponder");
   command("say Almost a... rather it was sort of a lance. That's it!");
   command("nod earnest");
   command("say And it was rather good against dragons.");
   return "";
}

string
narrative_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   command("say Narrative?");
   command("emote scratches his beard.");
   command("say Well... it's like magic. But a lot more powerful.");
   return "";
}

string
paladine_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   command("say Paladine? The one who calls himself the Valiant Warrior?");
   command("emote scratches his beard.");
   command("say Haven't seen him around these parts for a while, but if " +
       "I do I'll let him know you are asking for him!");
   command("twinkle");
   return "";
}

// May add a quest at the end of this dialogue where Fizban's hat gets 
// blown off and the player needs to go searching the mountains to find it.

string
quest_hint()
{
   if(TO->query_prop(DIALOG_PROP))
     return "The befuddled wizard seems to be currently in dialogue... " +
          "possibly with a tree. You may want to wait a moment and ask " +
          "again when you are likely to catch his attention?\n";

   if (!TP->test_bit("krynn", 2, 2) || !TP->test_bit("krynn", 2, 3))
   {
       command("whisper to " +TP->query_real_name()+ " You need " +
          "more narrative... or storyline progression.");

       if(!TP->test_bit("krynn", 2, 2))
       {
         command("whisper to " +TP->query_real_name()+ " The disks " +
             "of Mishakal need to be recovered - for good or evil.");
         if(TP->query_alignment() > 0)
            command("whisper to " +TP->query_real_name()+ " You should " +
                "seek out Lord Gunthar in Vingaard Keep and assist him " +
                "in the recovery.");
         else
            command("whisper to " +TP->query_real_name()+ " Being of " +
                "dark heart, perhaps Dragon Highlord Verminaard in Pax " +
                "Tharkas is the path you should take.");
       }
       if(!TP->test_bit("krynn", 2, 3))
       {
         command("whisper to " +TP->query_real_name()+ " In the fortress " +
                "of Pax Tharkas to our northwest is a family needing " +
                "rescuing.");
         command("whisper to " +TP->query_real_name()+ " Help them out, " +
                "and you will have the 'narrative' you need to continue " +
                "down this trail.");
       }
       command("wink conspir");
       return "";
   }

   TO->add_prop(DIALOG_PROP, 1);
   command("snort");
   command("say I guess I do look a bit like a questmaster, don't I?");
   command("chuckle");
   set_alarm(1.5,0.0, &command("say Now lets see..."));
   set_alarm(1.5,0.0, &command("ponder"));
   set_alarm(6.0,0.0, &command("say Kill ten rats? No, no... done to " +
       "death."));
   set_alarm(6.0,0.0, &command("hmm"));
   set_alarm(11.5,0.0, &command("emote mumbles to himself: You could " +
        "send them running around delivering packages to random " +
        "people! That would be a hoot!"));
   set_alarm(11.5,0.0, &command("giggle"));
   set_alarm(15.0,0.0, &command("emote opines out loud: Forge the " +
        "Dragonlance? Maybe find the lost eggs of the good dragons?"));
   set_alarm(15.0,0.0, &command("say No... " +HE(TP)+ " doesn't have " +
        "the narrative for that yet."));
   set_alarm(19.0,0.0, &command("frown"));
   set_alarm(19.0,0.0, &command("say to " +TP->query_real_name()+ " Um, " +
        "no. I have nothing for you to do. But thanks for offering! If " +
        "I think of any grand quests I'll, er, be sure to give you " +
        "a call!"));
   set_alarm(21.0,0.0, &command("smile bright"));
   set_alarm(21.0,0.0, &remove_prop(DIALOG_PROP));
   return "";
}

void
destroy_picked_up_stuff(object ob)
{
   command("emote tucks a " +ob->short()+ " into a curious pocket in " +
       "his robe.");
   ob->remove_object();
}

void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(ob->id("robe"))
      return;
    if(ob->id("staff"))
      return;
    if(ob->id("satchel"))
      return;
    if(ob->id("pouch"))
      return;
    if(ob->id("belt"))
      return;
    if(ob->id("spellbook"))
      return;
    if(ob->query_no_show())
	return;

    set_alarm(1.0, 0.0, &destroy_picked_up_stuff(ob));
    return;
}