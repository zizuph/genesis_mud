/*
 * This is a test join room for the Wild Elves. This way the files
 * can be altered and tested without affecting the live files.
 *
 *  -- Finwe, July 2001
 */

#pragma save_binary
#pragma strict_types

//#include "../wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

/* 
 * This is a set of handy definitions for the Wild Elves guild.          
 * Coded on 26/08/1995 by Tulix III. Based on the Grunts- no change there. 
 * Note: WRUNNER_DIR is defined in the file /d/Emerald/defs.h so make sure 
 * all objects that include this file also include the above file first!
 *
 * Updated June/July 2001 by Finwe for Cypress. Guild 'renamed' the Wild Elves,
 * though it still retains the titles for wildrunners and deathstalkers.

#ifndef GUILD_NAME

/* Define the general race guild characteristics */
#define GUILD_NAME          "Wild Elves Guild"
#define GUILD_TYPE          "race"
#define GUILD_STYLE         "elven wild elves"
#define GUILD_SOUL_ID       "wild elves"
#define GUILD_TAX           0
#define GUILD_OBJECT        WRUNNER_DIR + "wrunner_ring"
#define GUILD_SOUL          WRUNNER_DIR + "wr_soul"
#define GUILD_SHADOW        WRUNNER_DIR + "wrunner_shadow"
#define GUILD_HELP_DIR      WRUNNER_DIR + "help/"
#define GUILD_LOG           CYPRESS_DIR + "log/wrunner_guild"
#define GUILD_HELP          WRUNNER_DIR + "help/"
#define GUILD_NEWS          WRUNNER_DIR + "news"
#define GUILD_TRAINER       WRUNNER_DIR + "train"
#define GUILD_RING          WRUNNER_DIR + "wrunner_ring"
#define GUILD_SAVE          WRUNNER_DIR + "wrunner_save"
#define GUILD_MASTER        ({"finwe"})

#define IS_WIZ(x)           (x->query_wiz_level())
#define IS_MEMBER(p)        ((p)->query_guild_name_race() == GUILD_NAME)

#define BUILDING_BASE       WRUNNER_DIR + "base_guild_house.c"
#define LOG_SIZE            25000
#define WRITE_NAME(o)       sprintf("%-11s", capitalize((o)->query_real_name()))
#define RING_ID             "_wrunner_race_guild_ring_"
#define START               WRUNNER_DIR + "start_rm"
#define ROOM_DIR            WRUNNER_DIR + "rooms/"

#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support";
inherit "/d/Shire/cypress/guilds/wrunner/base_common_inside";

/*
* Global variables.
*/
private mapping members;

//static private string *titles = TITLES;

//   Prototypes
void dest_ring(object player);
void remove_from_list(string player);
void reset_room();


/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());
   
   if (file_size(GUILD_LOG) > LOG_SIZE)
      {
      rename(GUILD_LOG, (GUILD_LOG + ".old"));
   }
   
   write_file(GUILD_LOG, text);
}


public int
query_is_member(string name)
{
   if(members[name])
   {
         return 1;
   }

   return 0;
}



/*
* Function name: create_room
* Description : Called when the room is first loaded into memory.
*/
void create_room()
{
    set_short("An exquisite entrance");
    set_long("This is the entrance to the Wild Elves. The room " +
        "is circular with many columns set into the walls. The " +
        "columns are stylized versions of trees whose tops merge " +
        "and form the ceiling. An arch is set into the north " +
        "wall which leads out with another set into the south " +
        "wall leading elsewhere into the building. An image of " +
        "a book floats in the air between two columns.\n");
    add_item("entrance",
        "It is an intricately arch leading out of the building.\n");
    add_item(({"window", "windows"}),
        "There are no windows in the foyer.\n");
    set_add_column_walls("There are two openings, one leading " +
        "south into the guild and another leading north out " +
        "into the forest.");
    set_add_column_bldg();
    reset_room();

	clone_object(WRUNNER_DIR + "obj/book")->move(TO);
 
    add_prop(ROOM_I_INSIDE,          1);
    add_prop(ROOM_I_NO_CLEANUP,      1);
    add_prop(ROOM_I_NO_ATTACK,       1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
    create_guild_support();
   
    setuid();
    seteuid(getuid());
   
    restore_object(GUILD_SAVE);
    if (!mappingp(members))
    {
        members = ([ ]);
    }
   
//    add_exit("/d/Shire/cypress/thalandrone/rooms/glen/front", "out");
//    add_exit(ROOM_DIR + "hall", "south", "@@check_member@@");
  
}

int
check_member()
{
   
   object tp = this_player();
   
   if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
      {
      write("Only Wild Elves may go there.\n");
      return 1;
   }
   return 0;
}

/*
* Function name: init
* Description  : When someone enters the room, the commands are linked
*                to him/her.
*/
nomask public void
init()
{
   ::init();
   
   add_action("do_try",   "declare");
   add_action("do_break", "abandon");
   add_action("request",  "request");
}


/*
* Function name: do_try
* Description  : When a elf wants to join the guild, this function
*                makes him/her a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_try(string str)
{
    object tp = this_player();
    object shadow;
    int    result;
   
    if (!strlen(str) || str !="wild elves")
    {
        notify_fail("Declare your race as what? That's not possible.\n");
        return 0;
    }   

    if (tp->query_race() != "elf")
    {
        write("You are not a elf. Leave now.\n");
    return 1;
    }

// check if player is a member already
    if (IS_MEMBER(tp))
    {
        write("You are already a Wild Elf. If you have lost your " +
            "items, you may get a new ones using <request " +
            "ring>.\n");
    return 1;
    }

   
    if (tp->query_guild_member(GUILD_TYPE))

    {
        write("You cannot be a member of two racial guilds at " +
            "a time.\n");
    return 1;
    }

    shadow = clone_object(GUILD_SHADOW);
   
    if ((result = shadow->shadow_me(tp, GUILD_TYPE,
               GUILD_STYLE, GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
            " failed to add shadow with result " + result + ".\n");
        shadow->remove_shadow();
        write("The magic of the Wild Elves has failed. Please leave a " +
            "bug report in this room.\n");
    return 1;
    }
   
//  write("You seem to have a shadow...");
//    write("You are already counted as a Noldor.\n");
//    set_alarm(3.0,0.0,"init_me",tp);

// logs the join
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
        GUILD_NAME + ".\n");

// creates the guild item   
    clone_object(GUILD_RING)->move(tp, 1);

// joining message
//to new wild elf
    write("\nYou step forward to be named a Wild Elf. The walls " +
        "become translucent and seem to fade away. One by one, " +
        "the columns begin to glow until they become living " +
        "trees. The living trees begin to sway in a breeze, the " +
        "leaves seeming to sing praises to someone or something.\n\n");

    write("A light begins to infuse the leaves. The light begins " +
        "to swirl and coalesces into a beautiful elf. She is " +
        "grey skinned with long, pale, golden hair and violet " +
        "eyes. She wears a tunic of spun silver with an " +
        "intricate golden brooch pinned on her left breast.\n\n");

    write("She steps forward and embraces you, welcoming you to " +
        "the Wild Elves. The elf smiles and gives you a golden " +
        "ring, then turns away and returns to the trees.\n\n");

    write("The light dissipates from the trees, which materialize " +
        "back into columns. Walls reappear and the room returns " +
        "back to what it was before. A gentle singing can be " +
        "heard, fading in the distance.\n\n");

// to all in room
    say("\n"+QCTNAME(TP)+" steps forward and suddenly the room begins " +
        "to change. The walls fade way, opening up to a meadow. " +
        "One by one, the columns turn into trees, which sway " +
        "back and forth in the breeze. Pure light suddenly " +
        "begins to radiate from the leaves. It coalesces and " +
        "swirls into a beautiful elf.\n\n"+

        "She is grey skinned with long, pale, golden hair and " +
        "violet eyes. She wears a tunic of spun silver with an " +
        "intricate golden brooch pinned on her left breast.\n\n"+

        "The elf steps forward and hugs "+QCTNAME(TP)+". She " +
        "then turns away and disappears in the trees.\n\n"+

        "The light dissipates from the trees, which materialize " +
        "back into columns. Walls reappear and the room returns " +
        "back to what it was before. A gentle singing can be " +
        "heard, fading in the distance.\n\n");

    tp->clear_guild_stat(SS_RACE);
    tp->set_guild_pref(SS_RACE, GUILD_TAX);
    tp->add_cmdsoul(GUILD_SOUL);
    tp->update_hooks();
    members[tp->query_real_name()] = ({tp->query_age(), time() });
  
    save_object(GUILD_SAVE);
   
    return 1;
}


int init_me(object ob)
{
    ob->init_race_shadow();
    return 1;
}

/*
* Function name: lower_skill
* Description  : When a member leaves the guild or is kicked out due
*                to a change of race, this function punishes him/her,
*                removes the soul, shadow, etcetera.
* Arguments    : object tp - the object leaving.
*/
nomask private void
lower_skill(object tp)
{
    object ring;
   
    tp->set_guild_pref(SS_RACE, 0);
    tp->clear_guild_stat(SS_RACE);
    tp->remove_cmdsoul(GUILD_SOUL);
    tp->update_hooks();
    tp->setup_skill_decay();
   
   /* If the player starts in the guild by default, set this to
   * the default starting location for all players.
   */
    if (tp->query_default_start_location() == START)
    {
        tp->set_default_start_location(tp->query_def_start());
    }
   
    set_alarm(2.0,0.0,&dest_ring(tp));
//    {
//        ring->remove_object();
//    }
   
   /* Remove him/her from the list of members.
   */
    members = m_delete(members, tp->query_real_name());
   
    setuid();
    seteuid(getuid());
   
    save_object(GUILD_SAVE);
}

void remove_from_list(string player)
{
    player = lower_case(player);
    members = m_delete(members,player);
    setuid(); seteuid(getuid());
    save_object(GUILD_SAVE);
}

void dest_ring(object player)
{
    object ring;
   
    ring = present(RING_ID, player);
    if (objectp(ring))
    {
        ring->remove_object();
    }
}

/*
* Function name: do_break
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_break(string str)
{
    object tp = this_player();
    object ring;
    int    result;
   
    if (str != "wild elves")
    {
        notify_fail("Abandon who? The Wild elves?\n");
        return 0;
    }
   
    if (!IS_MEMBER(tp))
    {
        write("You cannot abandon the Wild Elves since you were never " +
            "one.\n");
    return 1;
    }
   
    if ((result = tp->remove_guild_race()) != 1)
    {
        log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
            " failed to remove shadow with result " + 
            result + ".\n");
      
        write("You are unable leave the Wild Elves. Please leave a " +
            "bugreport in this room about this. Thanks.\n");
    return 1;
    }
   
// starts skill decay and removes ring
    lower_skill(tp);

// remove the ring  
    ring = present(RING_ID, tp);
//write (ring+" ");
//write (RING_ID);
//    if (objectp(ring))
//    {
//        ring->remove_object();
    write("\nOne by one, the columns come to life. They begin to " +
        "turn black and the leaves begin to weep. A sad wind " +
        "fills the room, catching the tears which begin to " +
        "gently rain down on you.\n\n");
    write("As the tears fall, your membership in the " +
        "Wild Elves is washed from you. Your skills and " +
        "abilities begin to diminish and your elven ring melts " +
        "away, leaving a hole in your soul.\n\n");
    write("The columns return to their normal stone state and " +
        "are forever silent to you.\n\n");

    say("\nOne by one, the columns come to life. They begin to " +
        "turn black and the leaves begin to weep. A sad wind " +
        "fills the room, catching the tears, which begin to " +
        "gently fall on you and "+QCTNAME(TP)+".\n\n");
    say("As the tears fall, you feel a terrible anguish in " +
        "them. They seem to be weeping for " +QCTNAME(TP)+
        ". Soon, the weeping fades and the living trees turn " +
        "back to stone.\n\n");

//    }
   
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
        GUILD_NAME + ".\n");
   return 1;
}

/*
* Function name: do_list
* Description  : This function allows people to list their (major) guilds.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/

/*
nomask static int
do_list(string str)
{
    if (str != "guilds")
    {
        notify_fail("List what? Your guilds?\n");
    return 0;
    }
   
    str = this_player()->list_major_guilds();
   
    if (strlen(str))
    {
        write("You are a member of the following major " +
            "guilds:\n" + str);
    }
    else
    {
        write("You are not a member of any major guild.\n");
    }
    return 1;
}
*/


/*
* Function name: request
* Description  : Members who have lost their ring, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int request(string str)
{
    object tp = this_player();
   
    if (str != "ring")
    {
        notify_fail("Request what? A new ring?\n");
    return 0;
    }
   
    if (!IS_MEMBER(tp))
    {
        write("You are not a member of Wild Elves. You have no " +
            "right to a ring.\n");
    return 1;
    }
   
    if (objectp(present(RING_ID, tp)))
    {
        write("You already have a ring. You don't need two.\n");
    return 1;
    }
   
    setuid();
    seteuid(getuid());
   
    clone_object(GUILD_RING)->move(tp, 1);
   
    write("A new ring appears in the air before you. You reach out and " +
       "take it.\n");
    say(QCTNAME(tp)  + " stretches out " + HIS_HER(tp) + " hand " +
       "and takes a ring floating in the air.\n");
   
    return 1;
}

/*
* Function name: remove_player_changed_race
* Description  : Whenever a member changes his/her race (s)he is
*                mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void
remove_player_changed_race(object tp)
{
    tp->catch_msg("\nYou are no longer an elf, therefore you " +
        "do not belong in the " + GUILD_NAME + 
        " anymore. You are being expelled from the Wild Elves.\n");
   
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
        tp->query_race_name() + ") was kicked out.\n");
}

/*
* Function name: remove_player_low_alignment
* Description  : Whenever the alignment of a player is too low, the player
*                is mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
/*
nomask public void
remove_player_low_alignment(object tp)
{
    tp->catch_msg("\nIt seems the shadow of the Dark Lord has " +
        "grown within you. The Noldor shun all that is evil. " +
        "This means you can no longer be counted as a " + 
        GUILD_NAME + ".\n\n" +
        "Your ring bursts into flames, leaving behind a wisp " +
        "of smoke. \n");
   
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
        tp->query_alignment() + ") was kicked out.\n");
}
*/

/*
 * Function name: remove_player_inactive
 * Description: This is called when a player has been removed from the
 *              guild for inactivity.
 * Arguments:   object tp - the object to kick out.
*/
/*
nomask public void
remove_player_inactive(object tp)
{
    tp->catch_tell("You have been inactive for too long. You are no " +
        "longer counted as a " + GUILD_NAME + ".\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (inactive) " +
        "was kicked out.\n");
}
*/

/*
* Function name: leave_inv
* Description  : Called to remove the guild support if it is stuck.
* Arguments    : object obj - the leaving object.
*                object to  - the new destination of the object.
*/
/*
nomask public void leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
   
    gs_leave_inv(obj, to);
}
*/


/*
* Function name: test_members
* Description  : At the first of the month, we test whether all members
*                listed are still valid. Ie. players who have quit will
*                be kicked out of the list.
*/
/*
nomask static void
test_members()
{
   string *names = m_indices(members);
   int    index = -1;
   int    size = sizeof(names);
   
   setuid();
   seteuid(getuid());
   
   while(++index < size)
   {
      if (!(SECURITY->exist_player(names[index])))
         {
         log_guild(ctime(time()) +
            sprintf(" %-11s is no longer a player. -> removed.\n",
               capitalize(names[index])));
         
         members = m_delete(members, names[index]);
         }
   }
   
   save_object(GUILD_SAVE);
}


nomask public void
angry_valar(object tp)
{
    tp->catch_tell("\n \nYou have disappointed Manwe Sulimo.\n" +
      "Feel his wrath, and know that you are forsaken!\n");
    lower_skill(tp);
    log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " was removed from "+
      "the guild by the Valar.\n");
    tp->catch_tell("\nA thunderbolt rains down from the sky.\n");
    tp->catch_tell("It smites you in the forehead, and all goes black.\n");
    tp->heal_hp(-tp->query_max_hp());
    tp->do_die(TO);
    return;
}

nomask public int
valar_wrath(object player)
{
    int ran, ran2;

    ran = random(10);
    ran2 = random(10);

    if(ran + ran2 > 15)
    {
	set_alarm(3.0,0.0, &angry_valar(player));
	return 1;
    }

    if(ran2 < 9)
    {
	player->catch_tell("You are stung by the angry gaze of Varda.\n");
	player->heal_hp(-100);
	if (player->query_hp() <= 0)
	{
	    player->do_die(this_object());
	}  
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + 
        " was punished by Varda.\n");

	return 1;
    }

    if(ran > 7)
    {
	player->catch_tell("Ulmo looks upon you from afar and you feel his wrath.\n");
	player->add_fatigue(-100);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + 
        " was punished by Ulmo.\n");

	return 1;
    }

    if((ran < 3) || (ran2 < 3))
    {
	player->catch_tell("You feel an intense gaze coming from the Undying Lands.\n"+
	  "You feel very very afraid.\n");
	player->command("drop all");
	player->add_panic(150);
	log_guild(ctime(time()) + " " + WRITE_NAME(player) + 
        " was punished by Lorien.\n");

	return 1;
    }
}
*/


void reset_room()
{
}
 