/*
 * /d/Krynn/raceguild/obj/race_soul.c
 *
 * This soul holds the general commands and feelings of the Krynn Race Guild
 * Don't put any race/region/tribe specific emotes here in this file. Put
 * those in the appropriate file in the soul/ subdirectory.
 *
 * Aridor 12/96
 */

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <composite.h>
#include <formulas.h>
#include <std.h>
#include <tasks.h>

/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string
get_soul_id() 
{
    return "Krynn Race Guild"; 
}

int
query_cmd_soul() 
{ 
    return 1; 
}

/*****************************************************************************
 * Global variables
 *
 * regions:
 *   This is used for cmd identifying (via query_cmdlist()) and
 *   for help identifying (via the 'help' command).
 *****************************************************************************/
string *regions = ({});

void
init_regions()
{
    /* We need this construct because we have to initialize regions before
     * the variable is used the first time. See below in query_cmdlist for
     * details.
     */
    regions = ({"human",
      "elf",
      "dwarf",
      "goblin",
      "half_elf",
      "kender",
      "minotaur",
      "hobgoblin",

      "hum_solamnian",
      "hum_abanasinian",
      "hum_balifor",
      "hum_kern",
      "hum_khur",
      "hum_nordmaar",
      "hum_caergoth",
      "hum_icereach",
      "hum_kalaman",
      "hum_lemish",
      "hum_neraka",
      "hum_sancrist",
      "hum_sanction",
      "hum_solanthus",
      "hum_tarsis",
      "hum_estwilde",
      "hum_ergoth",
      "elf_qualinesti",
      "elf_silvanesti",
      "elf_dark",
      "dwf_kharolis",
      "dwf_thorbardin",
      "dwf_zhakar",
      "dwf_kayolin",
      "gob_throtyl",
      "gob_blode",
      "gob_kern" });
}

/*****************************************************************************
 * Includes
 * Here we include the special commands for each race/region/tribe.
 * There must be a check at the beginning of each command, if the guild
 * member is of the correct tribe, and is allowed to use the command.
 ****************************************************************************/
#include "soul/human.h"
#include "soul/elf.h"
#include "soul/dwarf.h"
#include "soul/goblin.h"
#include "soul/half_elf.h"
#include "soul/kender.h"
#include "soul/minotaur.h"

/*#include "soul/hobgoblin.h"*/
/*#include "soul/hum_solamnia.h"
#include "soul/hum_abanasinia.h"
#include "soul/hum_balifor.h"
#include "soul/hum_kern.h"
#include "soul/hum_khur.h"
#include "soul/hum_nordmaar.h"
#include "soul/hum_caergoth.h"
#include "soul/hum_icereach.h"
#include "soul/hum_kalaman.h"
#include "soul/hum_lemish.h"
#include "soul/hum_neraka.h"
#include "soul/hum_sancrist.h"
#include "soul/hum_sanction.h"
#include "soul/hum_solanthus.h"
#include "soul/hum_tarsis.h"
#include "soul/hum_estwilde.h"
#include "soul/hum_ergoth.h"
#include "soul/elf_qualinesti.h"
#include "soul/elf_silvanesti.h"
#include "soul/elf_dark.h"
#include "soul/dwf_kharolis.h"
#include "soul/dwf_thorbardin.h"
#include "soul/dwf_zhakar.h"
#include "soul/dwf_kayolin.h"
#include "soul/gob_throtyl.h"
#include "soul/gob_blode.h"
#include "soul/gob_kern.h"
*/

/*****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 *****************************************************************************/

mapping
query_cmdlist()
{
    int i;
    mapping tmp;
    mapping clist = ([ /* general commands are here */
      "guilds":"guildlist",
      "help":"help",
    ]);

    setuid();
    seteuid(getuid());

    /* This is some tricky design here. If you change anything at this concept,
     * be prepared to spend a few hours debugging :-)
     * I got it to work finally, with Mercade's help.
     * However, Mercade suggested to hardcode the commands into query_cmdlist,
     * and seeing the trouble this gave, he's probably right. But now I have
     * it working the way I wanted, and I'd rather see my time having been
     * useful and the code be used this way now, too :-)
     * ~Aridor 12/96
     */
    if (!regions || !sizeof(regions))
	init_regions();

    /* search for commands in all included files (regions) */
    for(i=0;i<sizeof(regions);i++)
    {
	/* call all function like query_cmdlist_human,
	 * query_cmdlist_hum_solamnian, etc. and get the commands.
	 */
	tmp = call_other(TO, "query_cmdlist_" + regions[i]);
	if (mappingp(tmp))
	    clist += tmp;
    }

    return clist;
}

/*****************************************************************************
 * Here follows the functions. New functions should be added in alphabetic
 * order.
 *
 * Here, we only have the general emotes for the guild.
 * -guildlist
 * -help
 * 
 ****************************************************************************/

/********************* guildlist ********************************************/
int
guildlist(string str)
{
    string name;
    object ob, paralyze;

    if (str)
    {
	if (TP->query_wiz_level())
	{
	    name = C(str) + " is ";
	    NF("No such player found.\n")
	    if (!(ob = find_player(str)))
		return 0;
	}
	else 
	{
	    write("Curious aren't we?\n");
	    return 1;
	}
    }
    else
    {
	ob = TP;
	name = "You are ";
    }

    str = ob->list_major_guilds();
    if (str)
	write(name + "member of the following guilds:\n" + str);
    else
	write(name + "not member of any guilds.\n");

    return 1;
}

/********************* help *************************************************/
int
help(string str)
{
    string subject, filename;
    int i, found = 0;

    if (!str)
	return 0;

    if (sscanf(str, "race%s", subject) != 1)
	if (sscanf(str, "krynn race%s", subject) != 1)
	    if (sscanf(str, "krynn%s", subject) != 1)
		return 0;

    if (subject[0..0] == " ")
	subject = subject[1..];

    if (subject == "" || subject == "help")
    {
	write("THE KRYNN RACE GUILD\n" +
	  "====================\n" +
	  "Use 'help race <subject>' to get detailed info on these topics:\n" +
	  " deny     : How to deny your heritage in Krynn.\n" +
	  " emotions : The list of emotes available.\n" +
	  " help     : This page.\n" +
	  "\n");
	found = 1;
    }

    if (subject == "deny")
    {
	write("THE KRYNN RACE GUILD\n" +
	  "====================\n" +
	  "How to deny your heritage in Krynn.\n" +
	  "Seek the Great Library in Palanthas, where you have found\n" +
	  "your roots in Krynn already, and deny your heritage of Krynn\n" +
	  "there. May you have little need for this option.\n");
	found = 1;
    }

    if (!regions || !sizeof(regions))
	init_regions();
    /* call all help functions. Any function that was appropriate will return 1
     * and found will be true.
     */
    for(i=0;i<sizeof(regions);i++)
	found |= call_other(TO,"help_" + regions[i], subject);

    NF("No help on that subject I'm afraid.\n");
    return found;
}


