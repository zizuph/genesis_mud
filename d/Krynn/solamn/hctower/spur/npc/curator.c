/*
 * A curator for the Knighthood museum in the Spur
 * Modified by Kentari from elistan.c - 12/96
 *
 * Added a spell hint for the SoHM - Arman 03/2016
 */
 
#include "../local.h"

inherit M_FILE

#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define SPUR_VISIT_MUSEUM  "_spur_visit_museum"
#define S_D_PRAYERBOOK     "_succeed_deliver_prayerbook"
#define SOHM_MANAGER       "/d/Krynn/guilds/sohm/lib/sohm_manager"

void
create_krynn_monster()
{
    set_name("ellard");
    set_living_name("ellard");
    add_name("curator");
    set_race_name("human");
    set_introduce(1);
    set_title("the Curator of the Sacred Solamnic Museum");
    set_gender(0);
    set_adj("grey-haired");
    add_adj("knowledgable");
    set_long("This is a man who seems old at first glance. His "+
	     "eyes are lighted by a glow from within. He radiates "+
	     "joy and good health, and would appear to know a great "+
	     "many things.\n");
    
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_SC(random(10) + 5)->move(TO);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS,  1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    default_config_npc(random(20) + 70);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    set_all_hitloc_unarmed(80);
    set_alignment(1000);
    set_knight_prestige(-10);

    set_act_time(180);

    add_act("say Please have a look around this humble museum, for " +
	    "there is much to see.");
    set_default_answer("Ellard says: I'm sorry, I don't know. Perhaps " +
		       "the answer lies within the museum.\n");
    
    add_ask(({"museum"}),
	    "say This museum is a wealth of knowledge and history about " +
	    "the Knights of Solamnia, for to explore one's future, one " +
	    "must learn the lessons of the past.\n" +
	    "Please, feel free to examine any and everything you see, " +
	    "and enjoy!", 1); 
    add_ask(({"spells","clerical spells","magic","clerics"}),
            VBFC_ME("spells_hint")); 
    add_ask(({"plains", "solamnia"}),
	    "say Why, I thought everyone knew that the Plains of Solamnia " +
	    "are southeast of this Spur!", 1);   
    add_ask(({"draconians", "army", "blue army"}),
	    "say I have no knowledge about military activities.",1);
    add_ask(({"help","task"}),
            "say I don't need any help at this time, but you may want to " +
	    "check with Gunthar in Vingaard Keep. He often has tasks " +
	    "for those willing to lend their aid.",1);
}

string
spells_hint()
{
    if(this_player()->query_guild_name_occ() == "School of High Magic" &&
       !SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
    {
       command("emote looks at you piercingly.");
       command("say Normally people who come here asking that sort of " +
           "question are interested in the lost blessings granted to the " +
           "knighthood prior to the Cataclysm.");
       command("say But I get the feeling you are interested in magicks " +
           "granted by study rather than from the divine.");
       command("frown");
       command("say The Knighthood has no time for those kind of spellcasters.");
       command("ponder");
       command("say However that was not always the case. Huma Dragonbane, " +
           "the heroic Knight of the Crown who banished the Dark Queen Takhisis " +
           "during the Third Dragon War had a mage companion by the name of Magius.");
       command("say Magius died to the forces of the Dark Queen during that war, " +
           "and the history books indicate Huma mourned his loss greatly. A few " +
           "relics of the war wizard survived those times, of which we have here " +
           "in the museum.");
       command("emote points to a dusty display case.");         
       return ""; 
    }

    command("emote sighs briefly and looks down in thought.");
    command("say Clerical abilities granted by Paladine and his sons were " + 
	    "withdrawn with the Cataclysm.");
    command("say We faithfully await the day in which our Gods shall return " +
            "to us, and with their coming, once again grant us a portion of " +
            "their divine powers.");

    return "";
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);

   if(from)
     set_alarm(1.0,0.0,"reward_me",ob,from);
}

void
reward_me(object ob, object from)
{
    if(ob->id("_q_prayerbook"))
    {
	if(interactive(from))
	{
	    if(from->test_bit("Krynn", 3, 2))
            {
		command("smile confused");
		command("say Well, um, thank you again for visiting the museum.");
		set_alarm(20.0,0.0,"remove_it",ob);
		return;
	    }
	    else
            {
		command("smile warmly");
		command("say You've brought it!");
		command("say These books are almost always kept only at " +
			"sanctified altars of the Knighthood.");
		command("emote ponders I guess Gunthar deemed this museum " +
			"to be a place holy to the Knighthood too.");
		command("thank " + from->query_name());
		command("say Please thank Gunthar for this gift, it is a " +
			"cherished one.");
		command("emote briefly gets embarrassed");
		command("say Oh, and of course, please take a look around the " +
			"Museum, for there is much to see and learn here.");
		
		TP->add_prop(S_D_PRAYERBOOK, 1);
		setuid();
		seteuid(getuid(TO));
		log_file("quests/spur_visit_museum",
			 extract(ctime(time()),4,15) + " " +
			 TP->query_name() + " delivered "+
			 "the prayerbook.\n");
		set_alarm(20.0,0.0,"remove_it",ob);
		return;
	    }
	}
    }
}

