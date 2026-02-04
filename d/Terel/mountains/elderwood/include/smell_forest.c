/*
 * This module is designed to be inherited into my Palanthas
 * local.h to add the <smell area> command to every room.  Once
 * this command is available, the idea is to have an easy format
 * for returning results based on race and alive/undead status.
 *
 * e.g. A human might be seen to smell the air, an elf to inhale
 * it slowly, a goblin or orc might snort in great quantities,
 * and an undead is going to get a completely different sense
 * plus their interpretation of the smells in the room will each
 * potentially differ.
 *
 * Note, Mortis:  Need to check if underwater first.
 *
 * Mortis 09.2005
 * Louie was instrumental in setting up the functions that make
 * this actually work.
 * And thanks to Mercade for learning me on syntax.
 * Major props to Gorboth for polishing the smell_world system!
   Gorboth recommends underwater check in do_smell() function.
 */

/* Requires:
 * CMD(({"area", "here", "the air", "the area"}), "smell", "@@smell_world");
 */

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>

mapping smells_map;
int default_smells_loaded = 0;

void
add_smell(string key, string value)
{
    if (!smells_map) {
        smells_map = ([ ]);
    }

    if (!key || !value)
        return;

    smells_map[key] = value;
}

print_vampire_smell_message()
	{if (!smells_map || !smells_map["vampire"])
		{write("Warm blood is never far in a forest of this size.\n");} 
	else {write(smells_map["vampire"] +"\n");}
    }

print_morgul_smell_message()
	{if (!smells_map || !smells_map["morgul"])
		{write("There is no trace of your quarry here.\n");} 
	else {write(smells_map["morgul"] +"\n");}
    }

print_human_smell_message()
	{if (!smells_map || !smells_map["human"])
		{write("The scents on the air are familiar to your human "
		+ "nose.\n");} 
	else {write(smells_map["human"] +"\n");}
    }

print_elf_smell_message()
	{if (!smells_map || !smells_map["elf"])
		{write("The scent of humans is strong in the air along with "
	+ "the smells that accompany so many of their dwellings.\n");} 
	else {write(smells_map["elf"] +"\n");}
    }

print_goblin_smell_message()
	{if (!smells_map || !smells_map["goblin"])
		{write("The scent of human flesh and offings is strong here.\n");}
	else {write(smells_map["goblin"] +"\n");}
    }

print_dwarf_smell_message()
	{if (!smells_map || !smells_map["dwarf"])
		{write("The air though strong with human smells is clean "
	+ "enough to breathe.\n");} 
	else {write(smells_map["dwarf"] +"\n");}
    }

print_hobbit_smell_message()
	{if (!smells_map || !smells_map["hobbit"])
		{write("The air is cool and fresh.\n");} 
	else {write(smells_map["hobbit"] +"\n");}
    }

print_gnome_smell_message()
	{if (!smells_map || !smells_map["gnome"])
		{write("The air is good enough to breathe at the moment "
	+ "and strong with many inviting wilderness smells.\n");} 
	else {write(smells_map["gnome"] +"\n");}
    }

print_minotaur_smell_message()
	{if (!smells_map || !smells_map["minotaur"])
		{write("The smell of fresh game is strong here.\n");} 
	else {write(smells_map["minotaur"] +"\n");}
    }

print_halfhuman_smell_message()
	{if (!smells_map || !smells_map["halfhuman"])
		{write("The scents on the air of this large, wilderness are not "
		+ "unfamiliar to you.\n");} 
	else {write(smells_map["halfhuman"] +"\n");}
    }

print_halfelf_smell_message()
	{if (!smells_map || !smells_map["halfelf"])
		{write("-- insert half elf smell here -- \n");}
	else {write(smells_map["halfelf"] +"\n");}
    }

print_orc_smell_message()
	{if (!smells_map || !smells_map["orc"])
		{write("The smell of manflesh is enticingly strong here.\n");} 
	else {write(smells_map["orc"] +"\n");}
    }

print_hobgoblin_smell_message()
	{if (!smells_map || !smells_map["hobgoblin"])
		{write("The scents of human flesh, offings, and all "
	+ "the smells of a fortified human city abound here.\n");} 
	else {write(smells_map["hobgoblin"] +"\n");}
    }

print_kender_smell_message()
	{if (!smells_map || !smells_map["kender"])
		{write("Oh my!  You are almost overwhelmed by the "
	+ "multitude of amazing people and things to smell!  Human cities "
    + "must be very rich with things to discover and places to explore.\n");} 
	else {write(smells_map["kender"] +"\n");}
    }

print_noldor_smell_message()
	{if (!smells_map || !smells_map["noldor"])
		{write("The scent of humans is strong in the air along with "
	+ "the smells that accompany so many of their dwellings.\n");} 
	else {write(smells_map["noldor"] +"\n");}
    }

print_unknown_smell_message()
	{if (!smells_map || !smells_map["unknown"])
		{write("You smell.  Please mail Mortis your race.  It's not "
		+ "recognized.\n");} 
	else {write(smells_map["unknown"] +"\n");}
    }



void
hook_vampire_smell()
{
		write("You inhale slowly, taking in the scents on the air in "
		+ "predatory fashion.  ");
		/* say(QCTNAME(TP) + " assumes a predatory gaze as "
		+ HE_SHE + " sniffs the air.\n");  Vampires are allowed to
		 * smell without being noticed.  They don't breathe
		 * after all. */
}

void
hook_morgul_smell()
{
		write("You lower yourself to the ground and start sniffing for "
		+ "scents.  ");
		say(QCTNAME(TP) + " lowers " + HIM_HER + " to the ground and seems "
		+ "to sniff for something, as if hunting.\n");
}

void
hook_human_smell()
{
    write("You smell the air around you.  ");
    say(QCTNAME(TP) + " smells the air around " + HIM_HER + ".\n");
}

void
hook_elf_smell()
{
    write("You lift your chin, slowly taking in the scents on the "
	+ "air.  ");
    say(QCTNAME(TP) + " raises " + HIS_HER + " chin, lithely taking "
	+ "in the scents on the air.\n");
}
void
hook_goblin_smell()
{
    write("You snortle and grunt as you sniff the air around you.  ");
    say(QCTNAME(TP) + " makes a snortling grunting noise as " + HE_SHE + " sniffs "
	+ "the air around " + HIM_HER + ".\n");
}
void
hook_dwarf_smell()
{
    write("You snort in a whiff of air.  ");
    say(QCTNAME(TP) + " gruffly snorts in a whiff of air.\n");
}
void
hook_hobbit_smell()
{
    write("You wriggle your nose as you sniff the air around you.  ");
    say(QCTNAME(TP) + " wriggles " + HIS_HER + " nose adorably as " + HE_SHE
	+ " sniffs the air around " + HIM_HER + ".\n");
}
void
hook_gnome_smell()
{
    write("You concentrate with great focus as you sniff in several "
	+ "directions for scents in the air.  ");
    say(QCTNAME(TP) + " furrows " + HIS_HER + " brow looking very "
	+ "concentrated indeed as " + HE_SHE + " sniffs at the air all around "
	+ HIM_HER + ".\n");
}
void
hook_minotaur_smell()
{
    write("You flare wide your nostrils as you snort in a great lungfull of "
	+ "air, tasting its scents.  ");
    say(QCTNAME(TP) + " flares open " + HIS_HER + " bovine nostrils as "
	+ HE_SHE + " snorts in enough air to create a small breeze.\n");
}
void
hook_halfhuman_smell()
{
    write("You smell the air around you.  ");
    say(QCTNAME(TP) + " smells the air around " + HIM_HER + ".\n");
}
void
hook_halfelf_smell()
{
    write("You smell the air around you, slowly taking in the scents on the "
	+ "air.  ");
    say(QCTNAME(TP) + " smells the air around " + HIM_HER + ", slowly taking "
	+ "in the scents on the air.\n");
}
void
hook_orc_smell()
{
    write("You take a whiff of the air, eager for the taste of flesh.  ");
    say(QCTNAME(TP) + " emits a low growl as " + HE_SHE + " takes in a "
	+ "few whiffs of air with sudden voracity.\n");
}
void
hook_hobgoblin_smell()
{
    write("Your throat grumbles as you taste the air around you.  ");
    say(QCTNAME(TP) + " emits a throaty grumble as " + HE_SHE + " sniffs "
	+ "the air around " + HIM_HER + ".\n");
}
void
hook_kender_smell()
{
     write("You crane your neck to the side wiggling your nose as you "
	+ "sniff the air for interesting smells.  ");
    say(QCTNAME(TP) + " tilts " + HIS_HER + " head to the side wiggling "
	+ HIS_HER + "crinkled up nose cutely as " + HE_SHE + " sniffs the air with "
	+ "disturbing interest.\n");
}

void
hook_noldor_smell()
{
   write("You lift your nose to the wind inhaling its scents.  ");
    say(QCTNAME(TP) + " lifts " + HIS_HER + " head calmly inhaling its "
	+ "scents.\n");
}

void
hook_unknown_smell()
{
    write("You smell the air around you, but your race is unknown.  Please "
	+ "mail Mortis.  ");
    say(QCTNAME(TP) + " smells the air around " + HIM_HER + ".\n");
}

int
smell_world(string str)
{
	
string swrace;
swrace = QRACE(TP);

/*    if (!default_smells_loaded)
		{
        init_default_smells();
        default_smells_loaded = 1;
		}
*/
/* Underwater if() {} */

	if
		(TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		/* The if/else and switch cases below all call two standard
		 * things.  First is the hook_xxx_smell() function which
		 * contains a standard write() and say() for that particular
		 * race/guild.  The second is the print_smell_message() which
		 * is what is set for that race/guild via add_smell() in
		 * init_default_smells().
		 */
        hook_vampire_smell();
		print_vampire_smell_message("vampire");
	}

	else if
		(TP->query_guild_name_occ() == "Morgul Mages")
	{
        hook_morgul_smell();
		print_morgul_smell_message("morgul");
	}

	else

	switch(swrace)
	{

	case "human":
        hook_human_smell();
        print_human_smell_message("human");      
	break;

	case "elf":
        hook_elf_smell();
        print_elf_smell_message("elf");      
	break;

	case "goblin":
        hook_goblin_smell();
        print_goblin_smell_message("goblin");      
	break;

	case "dwarf":
        hook_dwarf_smell();
        print_dwarf_smell_message("dwarf");      
	break;

	case "hobbit":
        hook_hobbit_smell();
        print_hobbit_smell_message("hobbit");      
	break;

	case "gnome":
        hook_gnome_smell();
        print_gnome_smell_message("gnome");      
	break;

	case "minotaur":
        hook_minotaur_smell();
        print_minotaur_smell_message("minotaur");      
	break;

	case "half-human":
        hook_halfhuman_smell();
        print_halfhuman_smell_message("halfhuman");      
	break;

	case "half-elf":
        hook_halfelf_smell();
        print_halfelf_smell_message("halfelf");      
	break;

	case "orc":
        hook_orc_smell();
        print_orc_smell_message("orc");      
	break;

	case "hobgoblin":
        hook_hobgoblin_smell();
        print_hobgoblin_smell_message("hobgoblin");      
	break;

	case "kender":
        hook_kender_smell();
        print_kender_smell_message("kender");      
	break;

    case "noldor":
		hook_noldor_smell();
	    print_noldor_smell_message("noldor");
	break;

    default:
		hook_unknown_smell();
	    print_unknown_smell_message("unknown");

    break;
    }
	
    return 1;
}

