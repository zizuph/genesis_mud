/*
 * Herbalist in Haven
 * Based on Herbalist in Gairent by Varian - August 2015
 *
 */
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/sohm/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>

inherit "/d/Krynn/haven/town/npc/herbalist_base";

inherit M_FILE

#define HERB_SAVE   "/d/Krynn/haven/town/npc/herbalist_herbs"

void
introduce_me();
arm_me();

int intro_id;

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("lemuel");
   add_name("herbalist");
   set_race_name("human");
   set_living_name("lemuel");
   set_title("the Hedge Wizard and Herbalist");
   set_adj("short");
   add_adj("balding");
   set_long("This short balding human is the owner of the Mageware shop " +
      "in Haven. Clad in faded red robes covered with dirt at the knees, it " +
      "seems he is accostomed to spending a lot of his time in his garden " +
      "tending his herbs.\n");
   set_gender(G_MALE);
   set_stats(({ 70, 55, 60, 99, 98, 55 }));
   set_introduce(1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_LOOKS,1);

   add_prop(CONT_I_WEIGHT,60000);
   add_prop(CONT_I_HEIGHT,172);

   add_prop(OBJ_M_NO_ATTACK,"He is protected " +
      "by powerful runes of magic, keeping him safe from harm.\n");
   
   set_skill(SS_HERBALISM,96);
   set_skill(SS_UNARM_COMBAT,65);
   set_skill(SS_DEFENCE,52);

   set_alignment(200);
   set_knight_prestige(-50);
   
   set_act_time(10);
   add_act("say Par-Salian never allowed me to sit the Test. He said it " +
       "would be tantamount to murder.");
   add_act("say My father was an archmage, a war wizard. When the Conclave " +
       "refused to let me sit the Test, he left home and never returned.");
   add_act("say There isn't much need for a Mageware shop in Haven. Would " +
       "have been better to set up in Palanthas, but I would really miss " +
       "my herb garden.");
   add_act("say If you have an unknown herb, I might be able to identify " +
           "it.");
   add_act("say I sell items of use to those who dabble in spellcraft. " +
           "I even have a few spell scrolls I can sell for the right price.");
   add_act("emote searches the shelves for dried herbs.");
   add_act("emote takes an herb to his nose and smells it.");
      
    set_alignment(350);
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");
    set_max_herbs_kept(250);
    set_herbalist_id_herbs();
    configure_herbalist(HERB_SAVE);

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"par salian","par-salian"}),
       "say Par-Salian is the Master of the Conclave of High Sorcery. " +
       "My father was very disappointed when Par-Salian refused to allow " +
       "me to sit the Test to join an Order of High Sorcery.", 1);
    add_ask(({"father","archmage","battle mage","war wizard"}), 
        VBFC_ME("ask_father"));
    add_ask(({"spells","spellbooks","spell","spellbook","scrolls","scroll"}),
        VBFC_ME("ask_scrolls"));

    add_ask(({"detect magic scroll","detect magic","detect magic cantrip",
              "detect magic spell"}), VBFC_ME("ask_detect_magic"));
    add_ask(({"magic shield scroll","magic shield","magic shield spell"}), 
              VBFC_ME("ask_magic_shield"));

    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herb lore"}), VBFC_ME("ask_lore"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid());
}



//equip function

arm_me()
{
  //anything added here you'll need to exclude in the enter_env function
}

void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("bow polite");
   command("introduce me"); 
   set_alarm(15.0, 0.0, allow_introductions);
}

void
init_living()
{
    init_herbalist();
    ::init_living();
}

string
wizinfo()
{
    string str;
    str = "This Herbalist stores up to "+query_herbs_max_kept()+
    " herbs of same type at one time.\n\n";
    if (!query_herb_list_size())
    {
    str += "The herbalist has no herbs for sale now.\n";
    return str;
    }
    str += "The herbalist has these herbs for sale:\n";
    str += query_herb_list();
    str +="-Lord Arman-\n";
    return str;
}


// ask responses

string
ask_herbs()
{
    command("say Herbs? Well, I have lots of herbs available right " +
        "here in my store! Would you like to buy some? Or perhaps you " +
        "have some you would like to sell? I might even be able to " +
        "identify a herb for you if you are not sure what you have!"); 
    return "";
}

string
ask_lore()
{
    command("say Well, I am very knowledgable about herbs if I do say " +
        "so myself, but there is still so much to learn! I once met " +
        "a young aspirant named Raistlin who was quite knowledgable, " +
        "even the White Mage Antimodes passes through here occasionally " +
        "and we shared what we knew of herblore.");
    return "";
}

string
ask_father()
{
    command("say My father was a powerful archmage - a battle mage who even " +
       "was sought after by the elves of Silvanesti!");
    command("say Anyway, he desperately wanted me to follow in his footsteps.");
    command("say I just didn't have the talent for magic he had.");
    command("sigh sadly");
    command("say When Par-Salian refused me the chance to sit the Test, my father " +
       "left the house and never returned.");
    command("say He even left most of his spellbooks and scrolls.");
    return "";
}

string
ask_scrolls()
{
    command("say When my father left, he left behind a number of spellbooks and " +
        "spell scrolls.");
    command("say Most were lesser spells of a war wizard.");
    command("ponder");

    if(this_player()->query_guild_name_occ() == GUILD_NAME) 
    {
      command("say A few years ago I gave most of them to a young mage of the Red " +
        "Robes, Raistlin Majere...");
      command("say But I do have a few scribed scrolls I could trade with you.");
      command("say A detect magic cantrip..");
      command("say ..and a magic shield spell.");
      command("say Ask me about either spell and I will tell you what I will "  +
        "trade for it.");
     }
    return "";
}

string
ask_detect_magic()
{
    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
      command("say Yes, I have the spell but I don't think it would be of " +
          "interest to you.");
      return "";
     }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ickrakarcanis"))
    {
        command("say Oh, you already know this spell.");
        command("shrug");
        return "";
    }

    command("say The merchant from Palanthas hasn't turned up this month, " +
       "and I am running short on fuel for my fire.");
    command("ponder");
    command("say Bring me a block of peat and I will trade you a scroll " +
       "containing the detect magic cantrip.");

    return "";
}

string
ask_magic_shield()
{
    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
      command("say Yes, I have the spell but I don't think it would be of " +
          "interest to you.");
      return "";
     }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanfethos"))
    {
        command("say Oh, you already know this spell.");
        command("shrug");
        return "";
    }

    command("say The alchemist Faldarten promised to give me a rare tulip " +
       "bulb if I provided him a silver nugget for his experiments.");
    command("ponder");
    command("say I am not sure where you might find one, maybe from a " +
       "dwarven mine? However if you " +
       "bring me one I will trade it for the magic shield spell.");

    return "";
}

default_answer()
{
    command("say I don't know much about that!");
    return "";
} 

void
give_it_back(object ob, object from)
{
    string what,
    who;
    what = L(ob->query_short());
    who = from->query_real_name();
    command("emote looks closely at the " + what + ".");
    command("say Thank you, but I have no use for that.");
    command("say Here, take it back friend.");
    command("give " + what + " to " + who);
    command("drop " +what);
}

void
return_give_peat(object ob, object from)
{

    string who,
    what;
    who = from->query_real_name();
    what = ob->short();


    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ickrakarcanis"))
    {
        command("say Ah thank you friend, another block of peat is " +
           "very generous of you.");
        command("emote throws the peat on to the fire.");
        ob->remove_object();
        return;
    }

	
    command("beam");
    command("say Wonderful! This will keep me warm during the winter " +
       "months.");
    ob->remove_object();
    command("emote rubs his hands together gleefully.");
    command("say Now, what did I offer you? Ah of course, the detect " +
       "magic cantrip.");
    command("say Here, copy this scroll in to your spellbook.");
    command("emote places a newly-scribed scroll on to the table.");
    from->catch_msg("You quickly scribe down in your spellbook the detect " +
       "magic cantrip.\n");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"ickrakarcanis");
}

void
return_give_silverpiece(object ob, object from)
{

    string who,
    what;
    who = from->query_real_name();
    what = ob->short();


    if(SOHM_MANAGER->query_scribed_spell(this_player(),"arcanfethos"))
    {
        command("say Ah thank you friend, but I do not need another " +
           "silver nugget.");
        command("say Here, take it back friend.");
        command("give " + what + " to " + who);
        command("drop " +what);
        return;
    }

	
    command("beam");
    command("say Wonderful! Oh Faldarten will be pleased!");

    ob->remove_object();
    command("say And he will happily trade that bulb to me.");
    command("dance");
    command("say Here, copy this scroll in to your spellbook.");
    command("emote places a neatly-scribed scroll on to the table.");
    from->catch_msg("You quickly scribe down in your spellbook the magic shield " +
       "spell.\n");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"arcanfethos");
}

void
herbalist_not_herb_hook(object ob, object player)
{
    command("ponder");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    init_herbalist_identify(ob,from);

    if(ob->id("herb"))
    {
	return;
    }

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
     }

    if(ob->id("silverpiece"))
    {
	set_alarm(1.0, 0.0, &return_give_silverpiece(ob, from));
	return;
    }

    if(ob->id("peat"))
    {
	set_alarm(1.0, 0.0, &return_give_peat(ob, from));
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}
