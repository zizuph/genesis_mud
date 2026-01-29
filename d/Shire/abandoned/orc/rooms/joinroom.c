/*
* /d/Shire/hobbit/join.c
*
* This is the join room of the Hobbit race guild. You may join here.
* Modified from the join room of the Rockfriend guild, created by
   *
* /Mercade, 9 January 1994
*
* This room:
* /Dunstable
* /Mercade, 13 November 1994
*
* Revision history:
* Changed the descriptive aspects of the room
* /Dunstable 18 March 1994
*/

#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support";

#include "/d/Shire/sys/defs.h"
inherit "/d/Shire/std/room.c";
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include "local.h"
//#include "titles.h"

inherit TUNNEL_BASE;


#define ARMBAND_ID     "_orc_racial_guild_item_"
#define START          (GUILD_DIR+ "start")
#define LOG_SIZE       25000

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

/*
* Global variables.
*
* The mapping members has the names of the players as indices and the
* values are an array with two elements, the family name of the player
* and the date the player joined.
*/
private mapping members;

//   Prototypes
//void dest_band(object player);


/*
* Functio name: create_room
* Description : Called when the room is first loaded into memory.
*/
void
create_tunnel_room()
{

    set_long("@@tunnel_desc3@@");
    add_my_desc("Torches spread more light here than normal. A " +
        "large boulder sits in the middle of the room.\n");
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");
    add_item(({"large boulder", "boulder", "altar"}),
        "The boulder is about half as tall as a goblin and two " +
        "arm's length wide. The boulder is jet black and looks " +
        "like part of the mountain. Its surface is covered " +
        "with black stains.\n");
    add_item(({"stains", "black stains", "blood stains", "blood"}),
        "The stains are black and cover the boulder in spots. " +
        "Some look fresh while others have dried. Where the " +
        "stains are dry, the boulder is pitted with small holes\n");

//add_cmd_item( ({ "sign" }), ({ "read" }),
   
   add_exit(ORCR_ROOM+ "gld01","north");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_CLEANUP,      1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
   create_guild_support();
   
   setuid();
   seteuid(getuid());
   
//   restore_object(ORCR_RACE_GUILD_SAVE);
   if (!mappingp(members))
   {
      members = ([ ]);
   }
}

int
racejoin(string str)
{
    object tp = this_player();
    object sh;
    mixed why;

    if((tp->query_alignment() < -100))
    {
	write("\nOnly those who are devoted to the Dark Lord can hope " +
        "to join.\n\nBegone!\n");
	return 1;
    }

    if ((!strlen(str)) || (str !="blood"))
     {
      notify_fail(capitalize(query_verb()) + " what? blood? You " +
          "must <shed blood> to prove yourself to the Dark Lord!\n");
      return 1;
     }

    if (IS_MEMBER(tp))
      {
      write("You have already shed your blood for the Dark One. " +
          "If you have lost your way, you may <reshed blood> to " +
          "dedicate yourself again.\n");
      return 1;
      }
    if (tp->query_guild_member(GUILD_STYLE))
      {
      write("You cannot be a member of two racial guilds at a time.\n");
      return 1;
      }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is a goblin */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
    write("Raising your right claw, you bellow loudly and slash " +
       "yourself deeply across your forearm. Black blood spills " +
       "from the gashes and falls to the altar, hissing and " +
       "pitting the stone. Within moments, everything goes " +
       "black as your body convulses. You fall to the ground " +
       "and roar with pain. After a minute, you stand up, " +
       "shakily and disoriented. You are now an orc.\n");


   say(QCTNAME(tp) + " raises " +HIS_HER(tp) + " and slashes " + 
       HIS_HER(tp) + " right forearm. Black blood spills from " +
       "the new wound and falls to the altar, hissing and " +
       "pitting the stone. Suddenly, " + HE_SHE(tp) + 
       " begins to convulses then and falls behind the altar. " +
       "A loud, blood-curdling roar echoes throughout the room; " + 
       HE_SHE(tp) + " stands up from behind the altar, shaking. " +
       "There is something different about " + HIM_HER(tp) + 
       " now.\n");
    }
    else
    {
write(sh->add_race_shadow(this_player()));
        /* Try to add the shadow to the player */
	switch (sh->add_race_shadow(this_player()))
	{
	    case 1:
	        /* We have successfully shadowed the player, so we're set */
		write("Shadowed Successfully.\n");
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
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
raceleave(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("But you aren't a member of this guild!\n");
        return 1;
    }

    this_player()->remove_race_member();
    write("Removed from guild.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(racejoin, "shed");
    add_action(raceleave, "curse");
}
