/* A simple room where you can join this guild. */

#pragma strict_types

inherit "/std/room";
inherit "/lib/skill_raise";

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>

/* prototypes */
void set_up_skills();

object priest;

static string *layman_origin = 
  ({"of Solace",
    "of Sanction",
    "of Neraka",
	"of Haven",
	"of Gateway",
	"of Pax Tharkas",
	"of Que Shu",
	"of Tarsis",
	"of Xak Tsaroth",
	"of Zhaman",
	"of Icereach",
	"of Teyr"});

void
reset_guild_room()
{
   if(!objectp(priest))
   {
      priest = clone_object(GUILD_NPC + "wyrllish");
      priest->move(TO);
   }
}

void
create_room()
{
    set_short("Large cave under the Temple of Takhisis");
	set_long("You are standing in a huge underground cave in Neraka. The "+
		"rock walls must have been carved out using powerful magic, creating "+
		"a smooth and clean surface. The cave stretches upwards in an arc and "+
		"clear water continous drips from statactites hanging from the ceiling. "+
        "A huge stack of colored eggs have been placed in the in center of "+
		"the room. The room seems strangely warm, and moist - almost comfortable. "+
		"Just besides the eggs, a desk has been placed together with a few chairs, "+
		"and primitive bed bunks.\n"+
		"A thick book is lying on the table, and next to it, a shimmering crystal.\n"+
		"You can join the " + GUILD_NAME_RACE + " here; just type \"racejoin\".\n" +
        "If you wish to leave the guild, type \"raceleave\".\n");

    add_item(({"walls","wall"}), "It is impossible to determine how these "+
	     "walls were created. It must have been some ancient form of magic, "+
		 "or divine power which have carved out this cave.\n");
    add_item("chairs","A number of chairs surround the square table.\n");
    add_item(({"bunks", "beds"}),"There are multiple beds, you wonder who uses them.\n");
	add_item("ceiling","The ceiling has been carved in the same way as the walls, "+
	     "they are however, covered with statactites.\n");
	add_item("statactites","These statactites must have been created by the water "+
	     "dripping from above.\n");
	add_item("water","The water is completely clear, however you could prefer not "+
	     "to drink it. It falls from an unknown source above the ceiling, and forms "+
		 "small pools of water, before disappearing between the cracks in the floor.\n");
	add_item("cracks","They are just some normal cracks created by the water erosion.\n");
	add_item(({"book","large book"}), "The large book has a picture of a draconian on "+
	     "the cover. Beneath it the words 'Draconians of Krynn' have been written.\n"+
		 "You might want to \"read the book\".\n");
	add_item(({"table","desk"}),"The desk is filled with ancient books and scrolls. "+
	   "You are unable to read any of them.\n");
	add_item("eggs","As you study the eggs closer, you notice that these are dragon eggs. "+
	   "They have different colors, depending on the type of dragon. You wonder "+
	   "where the dragons are should be protecting these.\n");
	add_item("crystal","You stare into the crystal, and sense a strange ominous power "+
	   "trapped within it. This is definitely something that is not meant to be in "+
       "mortal hands.\n");
	
    add_exit("start", "east");
	
	    /* configure the trainer */
    set_up_skills();
	reset_guild_room();
}

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 30);
    sk_add_train(SS_DEFENSE, "defend against attacks", "defense", 0, 30);
	sk_add_train(SS_WEP_AXE, "fight with axes", "defense", 0, 30);
	sk_add_train(SS_WEP_POLEARM, "fight with polearms", "defense", 0, 30);
	sk_add_train(SS_WEP_SWORD, "fight with swords", "defense", 0, 30);
	sk_add_train(SS_WEP_KNIFE, "fight with knives", "defense", 0, 30);
	sk_add_train(SS_SPELLCRAFT, "cast spells", "spellcraft", 0, 40);
	sk_add_train(SS_FORM_CONJURATION, "cast conjuration spells", "conjuration", 0, 40);
	sk_add_train(SS_FORM_DIVINATION, "cast divination spells", "divination", 0, 40);
	sk_add_train(SS_FORM_TRANSMUTATION, "cast transmutation spells", "transmutation", 0, 40);
	sk_add_train(SS_FORM_ENCHANTMENT, "cast enchantment spells", "enchantment", 0, 40);
	sk_add_train(SS_ELEMENT_WATER, "cast water spells", "water", 0, 40);
	sk_add_train(SS_ELEMENT_EARTH, "cast earth spells", "earth", 0, 40);
	sk_add_train(SS_ELEMENT_LIFE, "cast life spells", "life", 0, 40);
	sk_add_train(SS_ELEMENT_DEATH, "cast fire spells", "fire", 0, 40);
}

int
sk_improve(string str)
{
    int steps;
    string skill, *tmp;

    if(!objectp(priest))
	{
		write("But the guild trainer is not here!\n");
		return 1;
	}
	
	if (TP->query_race_name() != "draconian")
	{
		write("Only draconians are allowed to train here.\n");
		return 1;
	}
	
	if (TP->query_drac_type() == "baaz")
	{
		write("Baaz draconians are not allowed to train anything here.\n");
		return 1;
	}
    return ::sk_improve(str);
}

int
start(string str)
{
    if (str != "here") 
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!TP->query_guild_member(GUILD_NAME_RACE))
    {
        write("You are not a member of this guild!\n");
        return 1;
    }

    if (TP->set_default_start_location(GUILD_STARTLOC))
        write("Ok.\n");
    else
        write("Sorry, some problem prevents you from starting here.\n");

    return 1;
}

int
joinracial(string dracType)
{
	mixed why;
	object shadow_race;
	/* Clone the race shadow */
    setuid();
    seteuid(getuid());

    shadow_race = clone_object(GUILD_SHADOW_RACE);

    /* See if this member is acceptable */
    if (stringp(why = shadow_race->acceptable_member(TP)))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
		switch (shadow_race->add_race_shadow(TP, dracType))
		{
			case 1:
				/* We have successfully shadowed the player, so we're set */
			shadow_race->add_autoshadow(GUILD_SHADOW_RACE + ":" + dracType);
			write("Ok.\n");
			
			return 1;
    
			case -4:
				/* The player has an race guild already, or one of his existing
				 * guilds has blocked this one.
				 */ 
			write("Your other guilds don't want you in this one!\n");
			break;
    
			default:
				/* Some error in shadowing */
			write("An error has prevented you from joining.\n");
			break;
		}
	
		/* We couldn't shadow the player, so remove the shadow */
		shadow_race->remove_shadow();
	}
    return 0;
}

int
joinlayman()
{
	mixed why;
	object shadow_layman;
	/* Clone the race shadow */
    setuid();
    seteuid(getuid());

    shadow_layman = clone_object(GUILD_SHADOW_LAYMAN);

    /* See if this member is acceptable */
    if (stringp(why = shadow_layman->acceptable_member(TP)))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
		switch (shadow_layman->add_layman_shadow(TP))
		{
			case 1:
				/* We have successfully shadowed the player, so we're set */
			write("Ok.\n");
			shadow_layman->add_autoshadow(GUILD_SHADOW_LAYMAN);
			return 1;
    
			case -4:
				/* The player has an race guild already, or one of his existing
				 * guilds has blocked this one.
				 */ 
			write("Your other guilds don't want you in this one!\n");
			break;
    
			default:
				/* Some error in shadowing */
			write("An error has prevented you from joining.\n");
			break;
		}
	
		/* We couldn't shadow the player, so remove the shadow */
		shadow_layman->remove_shadow();
	}
    return 0;
}

int
finishJoinProcess(string dracType)
{
	// Always join the racial branch
	int race_join_success = joinracial(dracType);
	
	if (race_join_success)
	{
		write("Ok, you have joined the racial branch of the dracs.\n");
		if (dracType != "baaz")
		{
			// Join the layman branch - if the racial join was a success
			int layman_join_success = joinlayman();
			
			if (!layman_join_success)
				TP->remove_race_member(); //Remove the newly added racial
			                              //since we couldn't lay shadow TP
			else
				write("Ok, you have joined the layman branch of the dracs.\n");
		}
	}
    return 1;
}

int
racejoin(string dracType)
{
    if(!objectp(priest))
	{
		write("But the guild trainer is not here!\n");
		return 1;
	}
	
    if (!strlen(dracType))
    {
        write ("Join which draconian type?\n");
		return 1;
    }

	if (dracType != "aurak" && dracType != "sivak" && 
		dracType != "kapak" && dracType != "baaz" && dracType != "bozak")
	{
        write ("Join which draconian type? Of where?\n"+
		       "Eg. use 'racejoin [draconian type] (of location)'\n");
		return 1;
	}

	if (TP->query_alignment() > 1000)
	{
		write ("You must stray from the path of Paladine to be able to join this guild.\n");
		return 1;
	}
	
	if (TP->query_guild_name_race())
	{
		write("You already have a racial guild.\n");
		return 1;
	}
	
	if (dracType != "baaz" && TP->query_guild_name_lay())
	{
		write("You already have a layman guild.\n");
		return 1;
	}
	
	string color;
	
    switch (dracType)
    {
      case "kapak":
	  {
		color = "copper";
		break;
	  }
      case "aurak":
	  {
		color = "gold";
		break;
	  }
      case "bozak":
	  {
		color = "bronze";
		break;
	  }
      case "sivak":
	  {
		color = "silver";
		break;
	  }
      case "baaz":
	  {
		color = "brass";	
        break;
	  }
	  default:
	  {
		color = "unknown";
        break;
	  }
	}

	set_alarm(4.0, 0.0,&priest->command("emote holds his right hand over a "+color+" colored dragon egg."));
	set_alarm(6.0, 0.0,&priest->command("emote 's black medallion begins to glow in a sinister grey light."));
	set_alarm(8.0, 0.0,&priest->command("emote holds his left hand over your chest."));
	set_alarm(12.0, 0.0,&write("You can feel your entire body being torn apart!\n"));
	if (dracType != "aurak")
		set_alarm(14.0, 0.0,&write("A stinging pain errupts from your back and two leathery wings "+
	                           "suddenly bursts through your skin.\n"));
	set_alarm(16.0, 0.0,&write("A large scaled tail errupts from your lower back.\n"));
	set_alarm(20.0, 0.0,&write("Your fingers and toes turn into sharp claws.\n"));
	set_alarm(24.0, 0.0,&write("You feel a burning sensation in your face as it begins to change "+
	                           "your mouth and nose into an elongated snout.\n"));
	set_alarm(28.0, 0.0,&write("Your tongue changes and becomes thin and forked.\n"));
	set_alarm(32.0, 0.0,&write("Your entire skin begins to sting as it slowly transforms into "+
	                           "small "+color+ " scales.\n"));
	set_alarm(36.0, 0.0,&finishJoinProcess(dracType));
	set_alarm(40.0, 0.0,&priest->command("say Praise Takhisis! The transformation was a success!"));
	
	return 1;
}


int
readbook(string str)
{
    if (!strlen(str))
    {
        write("Read what? The book?\n");
		return 1;
    }
    if (str != "book" && str != "the book")
    {
        write("Read what? The book?\n");
		return 1;
    }

    write("You open the book and turn to the index page, it reads:\n"+
	  "+---------------------------------------------------------|\n"+
	  "|          <-oO   The Draconians of Krynn   Oo->          |\n"+
	  "|                 .,.,.,.,.,.,.,.,.,.,.,.                 |\n"+
	  "|                                                         |\n"+
	  "| This is the racial and layman branch of the Draconians  |\n"+
	  "| of Krynn. You can join the various draconian branches   |\n"+
	  "| here, if you are not completely devoted to Paladine.    |\n"+
	  "| The guild is otherwise neutral, and any draconian are   |\n"+
	  "| subject to their own fate and choices in life.          |\n"+
	  "|                                                         |\n"+
	  "| The index lists the following chapters:                 |\n"+
	  "|                                                         |\n"+
	  "| Chapter 1: Draconian races             \"read page 1\"    |\n"+
	  "| Chapter 2: Baaz draconians             \"read page 2\"    |\n"+
	  "| Chapter 3: Kapak draconians            \"read page 3\"    |\n"+
	  "| Chapter 4: Bozak draconians            \"read page 4\"    |\n"+
	  "| Chapter 5: Sivak draconians            \"read page 5\"    |\n"+
	  "| Chapter 6: Aurak draconians            \"read page 6\"    |\n"+
	  "| Chapter 7: Rules                       \"read page 7\"    |\n"+
	  "| Chapter 7: Leaving                     \"read page 8\"    |\n"+
	  "|                                                         |\n"+
	  "| Any questions or issues, please mail Elmore             |\n"+
	  "+---------------------------------------------------------+\n");
	return 1;
}

int
raceleave(string str)
{
    if(!objectp(priest))
	{
		write("But the guild trainer is not here!\n");
		return 1;
	}
	
    if (strlen(str))
    {
        return 0;
    }

    if (!TP->query_guild_member(GUILD_NAME_RACE))
    {
        write("But you aren't a member of this guild!\n");
        return 1;
    }
	if (TP->query_guild_name_layman() == GUILD_NAME_LAYMAN)
	{
		write("Ok, you leave the layman branch of the draconians.\n");
		TP->remove_layman_member(); // Remove Layman guild if its draconian
	    TP->set_guild_pref(SS_LAYMAN,0);
		TP->clear_guild_stat(SS_LAYMAN);
	}
	if (TP->query_guild_name_race() == GUILD_NAME_RACE)
	{
		write("You reach out for the shimmering crystal.\n");
		write("As you touch it, a bolt of lightning strikes your hand!\n");
		clone_object(GUILD_OBJ + "stun_obj")->move(TP);
		
		write("A tearing pain goes through you, and you feel your body returning "+
		  "to normal.\n");
		priest->command("emotes whispers: Traitor, but I guess that is expected "+
		  "from someone as weak in both body and mind, as you.\n");
		  
        TP->remove_race_member(); //Remove the draconian race guild
	    TP->set_guild_pref(SS_RACE,0);
        TP->clear_guild_stat(SS_RACE);
		
		write("Your body has returned to normal."+
		      "You have left the Draconians of Krynn.\n");
		priest->command("emotes whispers: Consider this my final gift for you.\n");
		clone_object(GUILD_OBJ + "blind_obj")->move(TP);
		priest->command("laugh demonically");
		priest->command("emote mumbles a spell");
		write("You suddenly feel dizzy.\n");
		TP->move("/d/Ansalon/estwilde/plains/4f");
		TP->heal_hp(-random(1000));
	}
	write("Ok.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(raceleave, "raceleave");
	add_action(readbook, "read");
	add_action(racejoin, "racejoin");
	add_action(start, "start");
	init_skill_raise();
}
