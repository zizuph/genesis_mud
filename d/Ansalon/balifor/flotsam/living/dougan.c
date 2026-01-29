/*
   Changed so ogres can do the quest with the shell, by
   removing INT requirment. Cherek - December 2015

   Added spell task hints

*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

#include <wa_types.h>

#define PLAYER_I_GOT_DOUGAN_QUEST  "_player_i_got_dougan_quest"
#define SOHM_DOUGAN_TASK "_sohm_earthskin_dougan_task_started"
#define RETRIEVED_ONJAT_DICE "_sohm_earthskin_onjat_dice_received"

#define PLAYER_I_FOUND_SEAELF  "_player_i_found_flotsam_seaelf"
#define PLAYER_I_FOUND_FISH    "_player_i_found_flotsam_fish"
#define PLAYER_I_FOUND_F_ROD   "_player_i_found_flotsam_f_rod"
#define PLAYER_I_FOUND_KEY     "_player_i_found_flotsam_key"
#define PLAYER_I_FOUND_WRECK   "_player_i_found_flotsam_wreck"
#define PLAYER_I_FOUND_WEBNET  "_player_i_found_flotsam_webnet"

#define ARM1 FOBJ + "armour/dougcoat"
#define ARM2 FOBJ + "armour/doughat"
#define ARM3 FOBJ + "armour/dougpants"
#define ARM4 FOBJ + "armour/dougshirt"

inherit AM_FILE

void
create_krynn_monster()
{

    if(!IS_CLONE)
	return;

    set_name("dougan");
    add_name("reorx");
    set_title("Redhammer, Warrior and Wanderer of the Realms");
    set_race_name("dwarf");
    set_adj("cheerful");
    add_adj("boisterous");
    set_gender("G_MALE");
    set_long("This loud, boisterous dwarf, whose voice it seems " +
      "could nearly wake the dead, seems to be quickly and proficiently " +
      "getting rid of a large amount of money through gambling and " +
      "drinking. Still, this plush lifestyle hardly seems to have " +
      "affected his physique, as he seems to be well muscled and " +
      "extremely hardy. \n");

    set_stats(({300,200,300,100,120,330}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_CLUB, 150);
    set_skill(SS_DEFENCE, 150);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);

    set_alignment(0);
    set_knight_prestige(-400);

    add_ask(({"quest","task"}),
      VBFC_ME("quest_hint"));
    add_ask(({"shell","pink shell","pink conch shell","conch shell"}),
      VBFC_ME("shell_hint"));
    add_ask(({"reorx","Reorx"}),VBFC_ME("reorx_hint"));
    add_ask(({"dwarf","dwarves","guild","dwarf guild"}),VBFC_ME("dwarf_hint"));
    add_ask(({"scroll","spell","teach magic","teach spell","magic",
      "spells"}), VBFC_ME("spell_hint"));
    add_ask(({"jems court","brix gang","brix","aesthetics quarter","kirk"}), 
      VBFC_ME("jems_court_hint"));
    add_ask(({"hobgoblin","hobgoblin chief","surly hobgoblin chief"}),
      "say Aye, don't know much about that cur. Kirk probably does though.", 1);
    add_ask("palanthas","say Aye, Palanthas... city in northern Solamnia. The " +
      "humans call it their jewel or something. It aint nothing on Thorbardin " +
      "let me tell ye!", 1);
    add_ask(({"onjat","onjat dice"}),"say Onjat? You nae heard of it? Hah! " +
      "You can't pull that one on me!", 1);


    add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
      "do not have the self-discipline to dare!\n");
    set_act_time(5);
    add_act("wink slyly");
    add_act("twinkle");
    add_act("emote roars: Who's willing to bet that I can't " +
      "catch a fly with chopsticks? eh? Anyone?");
    add_act("emote roars with laughter.");
    add_act("shout Barkeeper! More Dwarven Spirits at this table!");
    add_act("emote roars: By Reorx's toenails! Someone flogged me " +
      "axe! I'll bet my beard it was a sneaky little kender!");
    add_act("emote tugs his beard thoughtfully.");
    add_act("emote erupts into a bawdy tavern song!");

    add_cact("shout A feisty one eh? I like that in a person... " +
      "The ultimate gambler, betting all on his life!");
    add_cact("emote merrily sings a dwarven war chant!");

    trig_new("%w 'introduces' %s","react_to_intro");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid());
}

void
arm_me()
{
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    command("wear all");
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
    if (TP->test_bit("ansalon", 0, 16))
    {
	command("emote looks thoughtful for a second.");
	command("emote rumbles: Nope, I have no further tasks " +
	  "for you.");

	return "";
    }

    command("emote rumbles: Well, come to think of it, " +
      "I may have something for you...");
    command("emote strokes his long beard thoughtfully.");
    command("emote rumbles: It seems myself and the barkeep " +
      "are at odds over whether pink conch shells can be found " +
      "around this area. If you can bring one back to me there " +
      "is 5 steel pieces in it for me, and a shot of dwarven " +
      "spirits for you!");
    command("emote roars with laughter.");
    TP->add_prop(PLAYER_I_GOT_DOUGAN_QUEST, 1);

    return "";
}

string
reorx_hint()
{
    command("emote rumbles: Want to know about Reorx eh?");
    command("twinkle");
    command("say Well, I know little about Reorx, except that he was " +
      "one of the Old Gods, and is still beloved by the dwarves, even " +
      "after all the hardships they... we have gone through over the " +
      "ages.");
    command("emote rumbles: It is rumoured that a gate to the Lost " +
      "Dwarven Kingdom was placed somewhere around here before the " +
      "cataclysm by priests of Reorx, but none know whether it still " +
      "exists or ever did. My guess is that if it is it is somewhere " +
      "around here, it would be found in the forests of Goodlund, " +
      "or the ruins of Edon.");
    command("emote rumbles: Apart from that I know little else of " +
      "Reorx, although I hear that he was the most handsome of the " +
      "Gods in his time...");
    command("grin misch");
    return "";

}

string
dwarf_hint()
{
    command("emote strokes his beard in contemplation.");
    command("emote rumbles: Well, if ye got an idea for a " +
      "dwarven racial guild here in Ansalon, I know a dwarf " +
      "who would want to here from ye... mail Arman, if its " +
      "good enuff, he'll forge it!");
    return "";
}

string
shell_hint()
{
    command("emote looks confused.");
    command("emote scratches his head.");
    command("emote rumbles: Well... umm... they are " +
      "pink... umm shells! Yeah... thats what they are.");

    return "";
}

void
calculate_experience(object who)
{
    int xp_base = 20000;

    if (who->test_bit("ansalon", 0, 16))
    {
	who->catch_msg("Nice job, but no experience second time.\n");

	return;
    }

    xp_base -= (who->query_prop(PLAYER_I_FOUND_SEAELF) ? 0 : 1000);
    xp_base -= (who->query_prop(PLAYER_I_FOUND_FISH)   ? 0 : 1000);
    xp_base -= (who->query_prop(PLAYER_I_FOUND_F_ROD)  ? 0 : 1000);
    xp_base -= (who->query_prop(PLAYER_I_FOUND_KEY)    ? 0 : 3000);
    xp_base -= (who->query_prop(PLAYER_I_FOUND_WRECK)  ? 0 : 6000);
    xp_base -= (who->query_prop(PLAYER_I_FOUND_WEBNET) ? 0 : 3000);

    who->catch_msg("You feel more experienced!\n");
    if (who->query_wiz_level())
    {
	who->catch_msg("xp: " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 16);

    A_QUEST_LOG("quest", "Dougan Redhammer", who, xp_base);

    return;
}

void
return_give_shell(object from)
{

    object spirit;
    string who,
    what;

    who = from->query_real_name();

    if (!from->query_prop(PLAYER_I_GOT_DOUGAN_QUEST))
    {
	command("say Oh! .. Thank you, I was just thinking about "
	  + "exactly such a shell.");
	command("say A very nice gift indeed.");
	command("emote winks suggestively at the barkeeper.");

	return;
    }

	/* 
	   This just makes it impossible for ogres to finish the
	   quest. I commented it out for now. It makes little
       sense to have an INT requirement at all? 
	   Cherek - December 2015
	*/
	
	/*
    if(from->query_stat(SS_INT) < 50)
    {
	command("emote fumbles the pink conch shell and " +
	  "it rolls out the door of the tavern!");
	command("ack");
	command("emote rumbles: Hmm, didn't get time to " +
	  "examine it. Don't suppose you could find me " +
	  "another one?");

	return;
    }
	*/
	
    command("emote roars: Ha! A pink conch shell! " +
      "Pay up barman!");
    command("emote chuckles happily as the barkeeper " +
      "passes him some money.");
    command("emote rumbles: Here! Your reward!");
    spirit = clone_object(FOBJ + "drink/d_spirit");
    what = spirit->query_name();
    spirit->move(TO);
    command("give " + what + " to " + who);

    calculate_experience(from);

    command("emote waves to all, and leaves out the door.");
    remove_object();
}

void
return_give_dice(object ob, object from)
{

    object scroll;
    string who,
    what;

    who = from->short();

    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery")  
    {
        command("say Ahoy now! My onjat dice!");
        command("say What are the chances you randomly bringing them to me?");
        return;
    }
	
    command("say Ahoy now! My onjat dice!");
    command("emote tosses the dice into the air and then quickly snaps them up " +
       "in his rugged hands.");
    command("emote rumbles: Here! As promised, your reward!");
    command("emote drunkenly throws a furled parchment in to the air, and it falls " +
            "at your feet.");
    scroll = clone_object("/d/Krynn/common/scrolls/stoneskin_scroll");
    what = scroll->query_name();
    scroll->move(E(TO));
    ob->remove_object();
}

void
give_it_back(object ob, object from)
{
    string what,
    who;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("emote rumbles: I didn't ask for this!");
    command("laugh");
    command("say Here friend, take it back.");
    command("give " + what + " to " + who);
}

void
give_back_map()
{
    command("emote strokes his beard thoughtfully.");
    command("emote rumbles: Hmm. A map written in Auld " +
      "Centaurish.");
    command("say Shame I can't read it for you. Go speak " +
      "to Fermammon the Wise, for he may know something of " +
      "the language. Follow the road out the east gate. You " +
      "can't miss his cottage!");
    command("emote fumbles the map as the barkeeper offers " +
      "him another dwarven spirit.");
    command("drop map");
    command("say Oops! Oh well, you can pick it up for " +
      "yourself.");
    command("emote turns his attentions to his drink.");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_flotsam_c_shell_"))
    {
	set_alarm(1.0, 0.0, &return_give_shell(from));
	return;
    }
    else if(ob->id("_dougan_onjat_dice"))
    {
	set_alarm(1.0, 0.0, &return_give_dice(ob, from));
	return;
    }
    else if(ob->id("_flotsam_c_spirit_"))
    {
	return;
    }
    else if(ob->id("_stoneskin_scroll_"))
    {
	return;
    }
    else if(ob->id("_armour_quest_map"))
    {
	set_alarm(1.0, 0.0, &give_back_map());
	return;
    }
    else
      set_alarm(1.0, 0.0, &give_it_back(ob, from));

    return;
}


public void
attack_object(object ob)
{
    return;
}



string 
spell_hint()
{
    string what, who;
    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery")  
    {
        command("emote throws back a dwarven spirit.");
        command("say I can't help you with that.");
        return "";
    }
    if((this_player()->query_greater_spells_max() < 1))
    {
        command("eyebrow incred");
        command("emote roars: That weedy black-robe Satania send you did he? For me magic?");
        command("emote roars drunkenly: Well! I ain't dealing with no snotty runt-caster.. " +
                "Come back to me when you ah at your most powerful in your craft!");
        command("burp");
        return "";
    } 
    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
        command("eyebrow incred");
        command("say You ask me about spells like you can cast em!");
        command("emote roars with drunken laughter.");
        command("say Maybe come back and chat with me when you " +
                "have improved your spellcraft.");
        return "";
    }
    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"edarmolik"))
    {
        command("emote chuckles heartily.");
        command("say Ye come to a dwarf for magic? A dwarf? Hah!");
        command("say Well, you're out of luck. I can't teach you anything. But...");
        command("say I may have a scroll I won in a game of dice ye'd be surely " +
                "interested in.");
        command("say I will give it to you...");
        command("emote narrows his eyes cunningly.");
        command("say Although first ye must get me back something of mine.");
        command("say A pair of onjat dice I lost to a cheating whoreson " +
                "hobgoblin in Jems Court, Palanthas...");
        command("say Return me dice and i'll give ye this scroll.");
        command("emote waves a furled parchment around drunkenly.");

        this_player()->add_prop(SOHM_DOUGAN_TASK, 1);

        return "";
    }
    command("burp");
    command("say Sorry, I cannae help ye with that.");
    return "";
}

string
jems_court_hint()
{
    command("emote rumbles: Ah, Jems Court... ");
    command("sigh wistful");
    command("say In the aesthetics quarter of Palanthas you will " +
        "find a housing district full of debauchery and villainy.");
    command("emote rumbles: Jems Court. The Brix gang holds sway " +
        "in that territory, and nary a guard will you see step " +
        "foot in those quarters, let me tell ye!");
    command("cackle");
    command("say Anyhoo... the Brix gang run Krynn's greatest " +
        "onjat tables.");
    command("say When I was last visiting I played late in to the night " +
        "with the head of the Brix gang, Kirk the Alley King, and some " +
        "surly hobgoblin chief from the local mountains.");
    command("say Anyway, cutting a long story short I lost my lucky " +
        "onjat dice to the hobgoblin.");
    command("grumble");
    command("say Don't know much about him, although no doubt Kirk does.");
    return "";

}
