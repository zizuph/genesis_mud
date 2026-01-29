/* A simple room where you can join this guild. 
 *
 *
 */

#pragma strict_types
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/palanthas/local.h";
#include CLOCKH
#include "guild.h"

inherit SHIP_BASE;
inherit "/lib/skill_raise";

object board;

#define ENSIGN_ROOM "/d/Ansalon/guild/mariner/ensign_room"

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();


    sk_add_train(SS_LOC_SENSE, "navigate", "location sense", 0, 60);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 60);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "sail ships", "sail", 70, 100);
}

public int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
    {
	if (!TP->query_guild_member(GUILD_NAME))
	{
	    write("Only mariners may train their skills here.\n");
	    return 1;
	}
	return sk_list(steps);
    }


    tmp = explode(sk, " ");
    if(sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
	skill = implode(tmp[0 .. sizeof(tmp) -2], " ");
    else
    {
	skill = sk;
	steps = 1;
    }

    if(!TP->query_guild_member(GUILD_NAME))
    {
	write("Only mariners may train their skills here.\n");
	return 1;
    }
   
    return ::sk_improve(sk);

}

void
reset_palan_room()
{
    if(!objectp(board))
    {
       board = clone_object(GUILD_DIR + "mariner_board");
       board->move(TO, 1);
    }
}

void
create_palan_room()
{
    SHORT("the Guild of Mariners");
    LONG("@@long_descr");

    EXIT(SHIP + "s22", "northwest", 0, 0);
    EXIT(ENSIGN_ROOM, "down", "@@go_down", 0);

    add_item(({"large entry hall","entry hall","hall","guild",
        "guild of mariners"}),
        "You stand within the great entry hall of the Guild of " +
        "Mariners near the docks of the port city of Palanthas.\n");
    add_item(({"sailing regalia","regalia","ancient ensign flags",
        "ensign flags","ensign","flags","flag","figurehead","walls"}),
        "Sailing regalia hang all over the walls of the hall, ranging " +
        "from ancient ensign flags from ships that sailed for the " +
        "Holy Empire of Istar or Imperial Ergoth, to a beautifully " +
        "carved figurehead of an elven ship-of-the-line.\n");
    add_item(({"curios","curio","skeleton","seahorse","giant seahorse",
        "giant seahorse skeleton","gnomish steam engine","steam engine",
        "engine"}),
        "Some interesting curios hang from the walls of the hall - ranging " +
        "from a fragile giant seahorse skeleton, to the remains of " +
        "a gnomish steam engine.\n");
    add_item(({"charts","chart","maps","map"}),
        "A number of charts and maps line the walls here, showing seasonal " +
        "wind and ocean current patterns for the seas of Ansalon. There is " +
        "even one map that shows that sailing north of Palanthas takes you " +
        "to the high seas that eventually make landfall at the town of " +
        "Sparkle!\n");
    add_item(({"ship guides","guides","guide","ship guide"}),
        "@@ship_guide");
    add_item(({"staircase","stairs","circular staircase"}),
        "A narrow circular staircase leads down below the guild hall to a " +
        "room reserved for mariner Captains where they can register their " +
        "ensign insignia and colours.\n");

    add_cmd_item(({"small sign","sign","fineprint"}),"read","@@read_sign");

    /* configure the trainer */
    set_up_skills();
    reset_palan_room();

}

string
long_descr()
{
    return "You are in the large entry hall of the Guild of Mariners " +
        "based in the port of Palanthas. The hall is decked with a " +
        "century of collected sailing regalia, curios, charts, " +
        "maps, and ship guides. At the back of the hall a circular " +
        "staircase leads down below the guild hall.\n\n" +
        "Here those interested in <enlist>ing as a mariner may do so, " +
        "with a small sign detailing the fineprint of what enlisting means. " +
        "Existing mariners may <improve> their sailing skills or " +
        "<become a landlubber> if they no longer wish to sail the " +
        "seas of the realms.\n\n";
}

int
go_down()
{
    if (TP->query_wiz_level())
        return 0;

    if(TP->query_guild_name_craft() != GUILD_NAME)
    {
        write("Only mariners of Captain rank or higher are allowed down " +
            "the circular staircase.\n");
        return 1;
    }

    int sailor_lvl = TP->query_stat(SS_CRAFT) / 12; 

    // Mariner captain levels are 11 and 12.
    if(sailor_lvl < 11)
    {
        write("Only mariners of Captain rank or higher are allowed down " +
            "the circular staircase.\n");
        return 1;
    }

    write("You make your way down the narrow circular staircase...\n");
    say(QCTNAME(TP)+ " makes " +HIS(TP)+ " way down the narrow circular " +
         "staircase.\n");
    return 0;
}

string
read_sign()
{
    say(QCTNAME(TP)+ " reads the small sign.\n");

    return "The small sign reads:\n\n" +
        "      You can <enlist as a mariner> here, allowing you to\n" +
        "      train sailing skills that allow you to pilot ships of\n" +
        "      all sizes, as well as train your swimming skill and\n" +
        "      location sense up to superior craftman levels.\n\n" +
        "      This guild will fill your craft slot... thats right, \n" +
        "      craft slot! Not occupational, layman, or racial! So \n" +
        "      sign up now! There is no penalty for becoming a \n" +
        "      landlubber when you leave!\n" +
        "\n";
}

string
ship_guide()
{
    return "\n"+
        "                     ~===@   SHIPS OF KRYNN  @===~\n\n" +
        "    Type:         sloop\n"+
        "    Description:  The sloop-sized sailing ship is typically\n" +
        "                  single masted and is one of the smaller vessels\n" +
        "                  to ply the seas, tending to stay close to the\n" +
        "                  shoreline and avoid tricky sailing conditions.\n" +
        "                  Small fishing vessels fall within this category.\n\n" +
        "    Type:         cutter\n"+
        "    Description:  The cutter-sized sailing ship is a small to\n" +
        "                  medium-sized vessel, usually single-masted,\n" +
        "                  designed for speed rather than capacity.\n" +
        "                  Capable of navigating tricky sailing conditions,\n" +
        "                  these ships can range from smuggler vessels, to\n" +
        "                  harbour pilots, to nobleman pleasure yachts.\n\n" +
        "    Type:         schooner\n"+
        "    Description:  The schooner-sized sailing ship is one of the most\n" +
        "                  common vessels sailing the seas, typically equipped\n" +
        "                  with two or more masts and rigged both fore and aft.\n" +
        "                  Capable of navigating challenging conditions, these\n" +
        "                  ships are popular with merchants, military, and \n" +
        "                  pirates.\n\n" +
        "    Type:         corvette\n"+
        "    Description:  The corvette is one of many types of warships smaller\n" +
        "                  than a frigate. While smaller in capacity, corvettes\n" +
        "                  are easier to pilot than its bigger cousin and is\n" +
        "                  able to navigate extremely challenging conditions.\n" +
        "                  Corvettes are commonly used by navies as patrol boats\n" +
        "                  or escorts.\n\n" +
        "    Type:         frigate\n"+
        "    Description:  The frigate is the warship built for speed and \n" +
        "                  maneuverability, and are the mainstay of most navies. \n" +
        "                  They range from the Nordmaarian galleys to the rare\n" +
        "                  dwarven steam ironclads, and are capable of navigating\n" +
        "                  near impossible sailing conditions.\n\n" +
        "    Type:         man-o-war\n"+
        "    Description:  The man-o-war is the biggest and most powerful warship\n" +
        "                  type, usually the most powerful sailing vessel in any\n" +
        "                  navy. Capable of carrying vast numbers of troops, it is\n" +
        "                  also the most difficult to pilot, but is capable of \n" +
        "                  navigating near impossible sailing conditions.\n\n" +
        "    Type:         submersible\n"+
        "    Description:  The gnomish submersible of Mount Nevermind is a vessel\n" +
        "                  capable of navigating under the waters of Krynn! This\n" +
        "                  vessel is rarely seen for a number of reasons. By its nature\n" +
        "                  it travels covertly, but also being a gnomish invention\n" +
        "                  it has been known to have difficulty surfacing and are\n" +
        "                  commonly lost. Needless to say only the craziest of\n" +
        "                  captains would even consider piloting this vessel!\n\n" +
        "\n";
}


int
craftjoin(string str)
{
    object sh;
    mixed why;

    if(!str)
    {
	notify_fail("Enlist as what? A mariner?\n");
	return 0;
    }

    if(str != "as a mariner")
    {
	notify_fail("Syntax to become a mariner: " +
	  "'enlist as a mariner'.\n");
	return 0;
    }


    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
	write(why);
    }
    else
    {
	/* Try to add the shadow to the player */
	switch (sh->add_craft_shadow(this_player()))
	{
	case 1:
	    /* We have successfully shadowed the player, so we're set */
	    write("You eagerly look out to sea as you enlist as a mariner!\n");

	    say(QCTNAME(TP)+ " looks eagerly around, after enlisting as " +
             "a mariner!\n");


	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " became a mariner.\n", 500000);

	    return 1;

	case -4:
	    /* The player has a craft guild already, or one of his existing
	     * guilds has blocked this one.
	     */ 
	    write("Your other guilds don't want you in this one!\n");
	    break;

	default:
	    /* Some error in shadowing */
	    write("An error has prevented you from joining.\n");
	    break;
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
craftleave(string str)
{
    if(!str)
    {
	notify_fail("Become what? a landlubber?\n");
	return 0;
    }

    if(str != "a landlubber")
    {
	notify_fail("Syntax to leave the mariners: " +
	  "'become a mariner'.\n");
	return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of this guild!\n");
	return 1;
    }

    this_player()->remove_craft_member();
    write("You decide the sea is not for you, and return to being a landlubber!\n");
    say(QCTNAME(TP) + " is no longer a mariner!\n");
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " becomes a landlubber.\n", 500000);

    return 1;
}


void
init()
{
    ::init();
    add_action(craftjoin, "enlist");
    add_action(craftleave,"become");
    /* add the trainer's commands */
    init_skill_raise();

}
