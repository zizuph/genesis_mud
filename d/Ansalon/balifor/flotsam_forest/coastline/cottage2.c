#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/guilds/sohm/defs.h"
#include <ss_types.h>

inherit FOREST_IN;

int tome_present = 0;
object chest,idol;

void
reset_flotsam_room()
{
    if(!objectp(chest))
    {
	chest = clone_object(FOBJ + "chest2");
	chest->move(TO);
    }

    if (!P(idol, chest))
    {
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
	idol = clone_object(FOBJ + "idol");
	idol->move(chest,1);
    }
}

create_flotsam_room()
{
    set_short("magicians' bedroom");
    set_long("@@long_descr");

    add_item(({"bedroom","room","magicians' bedroom"}),
      "@@long_descr");
    add_item(({"wall","walls","southern wall","ceiling"}),
      "You are surprised to find four walls in this room! " +
      "You have the niggling suspicion that they are conspiring " +
      "to hold up the ceiling. The nerve!\n");
    add_item(({"tall bookshelf","bookshelf"}),
      "A tall bookshelf spreads across one of the walls of " +
      "this room, and is filled with spellbooks and tomes " +
      "of magic.\n");
    add_item(({"bed","comfortable looking bed"}),
      "A comfortable looking bed, neatly made.\n");
    add_item(({"spellbooks","tomes","tomes of magic"}),
      "@@spellbooks");
    add_item(({"desk","mahogany desk","quill","inkwell"}),
      "A mahogany desk sits in the middle of the room. A quill " +
      "and inkwell sit neatly to one side of the desk, while a " +
      "recently scribed scroll sits drying in the middle of the " +
      "desk.\n");
    add_item("staircase","A wooden staircase leads down to " +
      "the lower floor.\n");
    add_item(({"window","closed window"}),"In the southern " +
      "wall there is a closed window that looks out onto a " +
      "great evergreen forest.\n");
    add_item(({"scroll","recently scribed scroll",
         "scribed scroll"}),"Drying on the middle of the desk is a " +
         "neatly scribed scroll, newly penned. By the looks of the " +
         "arcane symbols it is probably a powerful spell of magic. " +
         "As you look at the scroll you also notice faint shimmering " +
         "runes of protection surrounding the desk, making you think " +
         "anyone foolish enough to touch anything on the desk will " +
         "regret it!\n");
    add_item(({"faint shimmering runes","shimmering runes","runes"}),
         "Faintly shimmering runes seem to surround the desk. " +
         "No doubt runes of protection, trying to touch anything on " +
         "it is likely to end in pain.\n");

    add_cmd_item(({"spellbooks","tomes","tomes from bookshelf",
	"spellbooks from bookshelf"}),({"get","take"}),"@@zap1");
    add_cmd_item(({"window","closed window"}),"open","@@zap2");
    add_cmd_item(({"tome","tome on recharging magical devices",
	"tome on recharging magical devices from bookshelf",
	"tome from bookshelf"}),({"get","take"}),"@@get_tome");

        add_cmd_item(({"scroll","recently scribed scroll",
         "scribed scroll"}), ({"read","study"}),"@@read_scroll");

        add_cmd_item(({"scroll","recently scribed scroll",
         "scribed scroll"}), ({"get","turn","pick","take"}),
         "@@steal_scroll");

    add_exit(CROOM + "cottage1","down",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a magicians' bedroom on the top " +
    "floor of an old-fashioned cottage. Against one wall " +
    "stands a bookshelf, filled no doubt with tomes and " +
    "spellbooks best left to those skilled in magic. Against " +
    "another wall there is a comfortable looking bed, neatly " +
    "made. A desk sits in the middle of the room, everything " +
    "on it also neatly arranged. A staircase leads down, and " +
    "in the southern wall there is a closed window.\n";
}


string
zap1()
{
    write("As your hands come close to the tomes and spellbooks, " +
      "you are zapped by a magical ward set to protect them.\n" +
      "You jump back in pain.\n");
    say(QCTNAME(TP) + " reaches towards a spellbook on the " +
      "bookshelf and is suddenly zapped by a magical ward " +
      "of protection.\n" +
      QCTNAME(TP) + " jumps back in pain.\n");
    return "";
}

string
zap2()
{
    write("You go to open the window and are zapped by a " +
      "magical ward.\n");
    say(QCTNAME(TP) + " reaches forward to open the window, " +
      "but is zapped by a magical ward.\n");
    return "";
}

string
get_tome()
{
    if(tome_present == 0)
    {
	write("You reach forward and pull a tome from the " +
	  "bookshelf.\n");
	say(QCTNAME(TP) + " pulls a tome from the bookshelf.\n");
	clone_object(FOBJ + "tome1")->move(TP);
	tome_present = 1;
	return "";
    }
    else
	write("Nah, you don't want to risk getting zapped by " +
	  "some protection ward of the magicians.\n");
    return "";
}

string
spellbooks()
{
    if(tome_present == 0)
    {
	return "Scanning through the spellbooks and tomes, " +
	"a tome on recharging magical devices catches your eye.\n";
    }
    else
	return "Scanning through the spellbooks and tomes, you " +
	"notice nothing of interest.\n";
}

string
read_scroll()
{
    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
	write("Your spellcraft skills are too poor even begin " +
          "comprehending " +
          "the magical symbols on the scroll before you.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " tries to comprehend the symbols on the scroll, " +
        "but doesn't have the spellcraft skills.\n",({ this_player() }));
	return "";
    }

    if(this_player()->query_guild_name_occ() != GUILD_NAME) 
    {
        write("You are unable to decypher the magical writing " +
        "on the scroll.\n");
        return "";
    } 

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the " +
        "magical runes in the spell tome. Perhaps try again after " +
        "preparing yourself to read magic?\n");
        return "";
    } 

    if(this_player()->query_lesser_spells_max() < 1)
    {
        write("This spell is too advanced for you to learn at this " +
        "time.\n");
        return "";
    } 

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"shochraos"))
    {
        write("The scroll seems to detail the spell 'shochraos', or " +
            "lightning bolt, which you have already scribed in your " +
            "spellbook.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " reviews the scroll on the desk, but discovers " +
        "nothing of interest.\n", ({ this_player() }));
        return "";
    }

    write("Ah! The scroll details an unknown spell to you! " +
        "The lightning bolt spell!\nYou carefully study the scroll " +
        "and scribe the spell in to your spellbook!\n");
    say(QCTNAME(this_player()) + " carefully reviews the scroll on " +
       "the desk and begins copying a spell in to " +
        this_player()->query_possessive() + " leather-bound " +
       "spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"shochraos");

    return "";
}

string
steal_scroll()
{
    write("BOOOOOOOOOOOOOOOM!!!!!!!!\nYou touch the scroll on the " +
       "desk and shimmering runes of protection around it explode " +
       "in fiery wrath! You scream out in pain!\n");

    say("As " +QTNAME(this_player()) + " reaches out to touch the " +
       "scroll on the desk you notice protective runes around it " +
       "begin to glow angrily and then explode in a fiery wrath!\n" +
       QCTNAME(this_player())+ " screams out in agony!\n");

    // Scroll rune does a lot of damage! But meant more to scare, 
    //not kill, so no do_die
    this_player()->heal_hp(-500);

    return "";
}