/*
 *  /d/Sparkle/guilds/new_merc/rooms/join.c
 *
 *  The inside of the old lumber mill. This is the room where players
 *  may freely join or leave the guild.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <cmdparse.h>
#include <macros.h>         /* For MASTER_OB */
#include <stdproperties.h>
#include <time.h>


/* Definitions */
#define            WARNING_PROP    "_leave_merc_warning"
#define            OLD_MERC_SHADOW "/d/Sparkle/guilds/mercs/lib/merc_shadow"
#define            MARK_PROP       "_mark_warning_prop"

/* Global Variables */
public string     *Persona_Non_Grata = ({});
public string      Mark_Text = "The insignia of the Mercenary Guild has"
                     + " been stamped into it - no merchant would dare"
                     + " to buy it!\n";

/* Prototypes */
public void        create_merc_room();
int                occjoin(string str);
int                occleave(string str);
void               init();
public int         has_old_merc_shadow(object player);
public int         transfer_membership(string arg);
public int         do_mark(string arg);

public string     *query_png() { return Persona_Non_Grata; }

/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("inside an old sawmill");
    set_long("The inside of this old sawmill has been converted to"
      + " function as a headquarters, of sorts, for the Mercenary"
      + " guild. Resting on a large table is a book which contains"
      + " the active registry of guild members. If you wish to"
      + " join the guild, you may <register> here. Similarly,"
      + " members can <unregister> to leave the guild. Beside"
      + " the table is a large anvil used to <mark> guild-protected"
      + " gear from illegal sale. A doorway leads outside to the"
      + " south.\n\n");

    add_item( ({ "inside", "inside of the sawmill", 
                 "inside of this sawmill",
                 "inside of this old sawmill" }),
        "You know, the opposite of outside.\n");
    add_item( ({ "outside", "south", "door", "doorway",
                 "open doorway" }),
        "Through the doorway to the south, you glimpse the path"
      + " leading back toward the lodge.\n");
    add_item( ({ "path", "pathway",
                 "path leading back toward the lodge" }),
        "It is outside the doorway to the south.\n");
    add_item( ({ "lodge" }),
        "You can't see much of the lodge from in here. Only the corner"
      + " is visible through the doorway.\n");
    add_item( ({ "corner", "corner of the lodge" }),
        "As you stand, looking at the corner of the lodge through"
      + " the doorway, you take a moment to consider the life you've"
      + " lead. Was it all worth it? Just think ... yesterday you"
      + " had no idea you'd be here, now, gazing upon this sight. You'll"
      + " probably never be the same, will you?\n");
    add_item( ({ "mill", "here", "room", "area", "sawmill",
                 "saw mill", "old sawmill", "old saw mill",
                 "old mill", "old saw-mill", "saw-mill" }),
        "Once the heart of the logging operation, the mill has been"
      + " emptied of most of the equipment from its lumber-sawing"
      + " days. You do notice that at the north end of the room,"
      + " the axle from the huge waterwheel still slowly turns.\n");
    add_item( ({ "axle", "waterwheel axle", "axle from the waterwheel",
                 "axle from the huge waterwheel" }),
        "The axle turns endlessly, its motion producing a soft creaking"
      + " sound every so often. It is no longer connected to the"
      + " machinery that the mill once housed for sawing lumber.\n");
    add_item( ({ "machinery", "equipment",
                 "equipment from the lumber-sawing days" }),
        "The equipment and machinery of the mill appears to have been"
      + " removed long ago.\n");
    add_item( ({ "waterwheel", "wheel", "water wheel",
                 "huge waterwheel", "huge wheel",
                 "huge water wheel" }),
        "The waterwheel is outside, beyond the north wall of the mill."
      + " In here, all you can see is its axle.\n");
    add_item( ({ "headquarter", "headquarters" }),
        "It seems this is where business for the guild is conducted.\n");
    add_item( ({ "business", "business for the guild" }),
        "More often than not, the business deals with people who want to"
      + " <join> or <leave> the guild.\n");
    add_item( ({ "guild", "mercenary guild" }),
        "This whole camp is run by the Mercenary Guild.\n");
    add_item( ({ "camp", "mercenary camp" }),
        "Look around you. You're in it.\n");
    add_item( ({ "sky", "sun", "cloud", "clouds" }),
        "You can't see much from inside.\n");
    add_item( ({ "up", "ceiling", "roof", "ceiling of the mill" }),
        "Gazing up, you notice that the ceiling of the mill is quite"
      + " high above the floor. Huge rafters support the roof.\n");
    add_item( ({ "rafter", "rafters", "huge rafter", "huge rafters" }),
        "They are just as large as the lumber used to make the walls.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor of the mill is hardwood, and rather worn.\n");
    add_item( ({ "hardwood", "hardwood floor" }),
        "Looks like oak.\n");
    add_item( ({ "oak" }),
        "You can tell by the pattern of the grain.\n");
    add_item( ({ "pattern", "grain", "pattern of the grain" }),
        "You get down on your hands and knees and begin pouring over"
      + " the finer details of the floor, taking in every inch of"
      + " the beauty in the wood. Realizing that the room has gone"
      + " suddenly quiet, you peer up and see the Mercenaries in"
      + " the mill peering at you with raised eyebrows. Somewhat"
      + " sheepishly you rise to your feet and mutter something about"
      + " high-quality materials.\n");
    add_item( ({ "wood", "lumber", }),
        "Its pretty much all around you here, having been used to"
      + " build just about every surface of the mill.\n");
    add_item( ({ "surface", "every surface" }),
        "Wood, wood, everywhere ... and not a drop to ... uh ... "
      + "nevermind.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall did you wish to examine?\n");
    add_item( ({ "south wall", "southern wall", "wall to the south" }),
        "A doorway in the wall to the south opens onto the outside.\n");
    add_item( ({ "east wall", "eastern wall", "wall to the east",
                 "west wall", "western wall", "wall to the west" }),
        "The wall is made of wood, and looks strongly-built.\n");
    add_item( ({ "north wall", "northern wall", "wall to the north" }),
        "The north wall contains an opening through which the axle of"
      + " the massive waterwheel extends into the mill.\n");
    add_item( ({ "opening" }),
        "The opening is just large enough to allow the axle to"
      + " extend into the mill.\n");
    add_item( ({ "table", "large table" }),
        "Resting on the table is a large book.\n");
    add_item( ({ "book", "large book" }),
        "The book appears to be the registry of active guild"
      + " members. You can <register> to join the guild or <unregister>"
      + " to end your career as a Free Mercenary.\n");
    add_item( ({ "registry", "active registry" }),
        "There is nothing fancy about it. It is purely functional.\n");
    add_item( ({ "name", "names" }),
        "The members of the guild have put their names down in the"
      + " registry.\n");
    add_item( ({ "member", "members", "member of the guild",
                 "members of the guild", "guild member", "guild members" }),
        "If you aren't one already, you could <join> them.\n");
    add_item( ({ "motion", "motion of the axle", "axle motion" }),
        "The motion of the axle is smooth and steady - just a slow"
      + " endless turning.\n");
    add_item( ({ "turning", "endless turning", "slow turning",
                 "slow endless turning" }),
        "On, and on, and on ...\n");
    add_item( ({ "sound", "soft sound", "creaking sound",
                 "soft creaking sound", "creaking", "creak" }),
        "Its the sort of thing that might coax a baby to sleep.\n");
    add_item( ({ "baby" }),
        "No.\n");
    add_item( ({ "river", "copper river" }),
        "The river isn't visible in here, but you can hear the sounds"
      + " of the water.\n");
    add_item( ({ "sound", "sounds" }),
        "There is a dull roar from the endless spilling of the"
      + " waterwheel outside.\n");
    add_item( ({ "dull roar", "roar" }),
        "Dull enough to put you to sleep.\n");
    add_item( ({ "guard", "guards", "guard outside the door",
                 "guards outside the door" }),
        "There are a few guards stationed just outside the door. They"
      + " look a bit bored, and peek in every so often.\n");
    add_item( ({ "grounds" }),
        "The camp is visible through the door.\n");
    add_item( ({ "window", "windows" }),
        "There aren't any windows in here other than one on the"
      + " south wall near to the door.\n");
    add_item( ({ "one window", "south window",
                 "window on the south wall",
                 "window in the south wall" }),
        "The window looks out onto the grounds. The head of a guard"
      + " is visible through it.\n");
    add_item( ({ "head", "head of a guard", "guard head",
                 "guards head", "guard's head" }),
        "Looks like he's going a bit bald, poor chap.\n");
    add_item( ({ "mercenary", "mercenaries" }),
        "There are a number of Mercenaries in this room at all times."
      + " Evidently, they feel it is necessary to watch over the"
      + " registry to help keep track of who is active in the guild.\n");
    add_item( ({ "anvil", "large anvil" }),
        "The anvil is large enough to allow Mercenaries room to place"
      + " any piece of armour or weaponry upon it. A heavy hammer"
      + " rests nearby which can be used to <mark> a desired piece"
      + " of gear with the insignia of the guild. Merchants"
      + " throughout the land know better than to trade in items"
      + " with that mark upon them, unless they have a deathwish.\n");
    add_item( ({ "mark" }),
        "Mercenaries can <mark> gear they wish to be protected from"
      + " sale here.\n");
    add_item( ({ "hammer", "heavy hammer" }),
        "The hammer looks much like any other, save that it is far"
      + " larger, and the strikepoint bears the insignia of the"
      + " Mercenaries, such that anything that might be given a"
      + " <mark> with one of its blows will be protected from sale"
      + " to any merchant.\n");
    add_cmd_item( ({ "name", "names" }),
                  ({ "read" }),
        "The members of the guild have put their names down in the"
      + " registry.\n");
    add_cmd_item( ({ "book", "registry", "active registry" }),
                  ({ "read" }),
        "You glance through the book. Looks like there are quite a few"
      + " names there. You can <register> to become a Free Mercenary"
      + " yourself, or <unregister> if you already belong to the guild"
      + " and wish to leave.\n");
    add_cmd_item( ({ "opening", "the opening", "through the opening",
                     "through opening", "into opening",
                     "into the opening", "in opening", "in the opening" }),
                  ({ "enter", "crawl", "climb" }),
        "There is no way you'd fit. Plus, if you tried, you'd probably"
      + " be ground painfully into a mashed pulp by the turning axle.\n");
    add_cmd_item( ({ "axle", "up axle", "on axle", "up on axle",
                     "up the axle", "on the axle", "up on the axle",
                     "onto the axle", "onto axle" }),
                  ({ "climb", "stand" }),
        "What, going to practice your log-rolling skills or something?\n");

    add_tell("One of the guards outside the door peers into the"
      + " mill briefly and then resumes his watch on the grounds.\n");
    add_tell("A slight creaking comes from the axle of the waterwheel.\n");
    add_tell("Sounds from the river quietly filter into the room.\n");
    add_tell("You hear a distant bird song from outside.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("path4", "south");

    set_no_exit_msg( ({ "southwest", "west", "northwest", "north",
                        "northeast", "east", "southeast" }),
        "You wander around the mill, but can't proceed in that"
      + " direction.\n");

    add_npc(NPC_DIR + "morgan");
} /* create_merc_room */


/*
 * Function name:        occjoin
 * Description  :        allow players to try to join the guild
 * Arguments    :        string str - what was typed after the verb
 * Returns      :        0 - failure, 1 - success
 */
int
occjoin(string str)
{
    object sh;
    mixed why;

    if (strlen(str))
    {
        notify_fail("Simply <register> to join the Mercenaries.\n");
        return 0;
    }

    if (has_old_merc_shadow(this_player()))
    {
        write("One of the Mercenaries says: Ahhh ... I recognize you as"
          + " one of the warriors from Maligant's old outfit. Well, you"
          + " are a special case. No need to let all that training you've"
          + " had go to waste! If you'd like to join us here in this new"
          + " location, just <transfer membership> and we'll get you all"
          + " registered!\n");
        return 1;
    }

    /* If they got caught working on the Merc Spy Quest, we force
     * them to wait for a reset before they are trusted again. This
     * routine should be altered in the case that the game has
     * uptimes that are exceptionally long. At the time of this
     * writing, the uptimes for the game are around a week. That is
     * my intended duration for the punishment. (Gorboth, 2010)
     */
    if (IN_ARRAY(this_player()->query_real_name(), Persona_Non_Grata))
    {
        write("One of the Mercenaries says: Get the hell out of here,"
          + " you pathetic weasel! Maybe we'll forgive you in a few"
          + " days ... and I mean MAYBE.\n");
        tell_room(this_object(), "One of the Mercenaries says to "
          + QTNAME(this_player()) + ": Get the hell out of here, you"
          + " pathetic weasel! Maybe we'll forgive you in a few days"
          + " ... and I mean MAYBE.\n", this_player());
        write_file(LOG_DIR + "join_rejects",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " was refused entrance to the guild for spying.\n");
        return 1;
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
	switch (sh->add_occ_shadow(this_player()))
	{
	    case 1:
	        /* We have successfully shadowed the player, so we're set */
		write("You add your name to the registry of active"
                  + " Mercenaries.\n\n");
                say(QCTNAME(this_player())
                  + " adds " + this_player()->query_possessive()
                  + " name to the registry of active Mercenaries.\n\n");
                write("Two Mercenaries approach you and clap you heartily"
                  + " on the shoulder. One of them says: Your"
                  + " skills and knowledge are needed here, "
                  + ( (this_player()->query_gender()) ? "good Lady" :
                    "Brother") + "! Welcome to the Free Mercenary"
                  + " Guild!\n\n");
                say("Two Mercenaries approach " + QTNAME(this_player())
                  + " and clap " + this_player()->query_objective()
                  + " heartily on the shoulder. One of them says: Your"
                  + " skills and knowledge are needed here, "
                  + ( (this_player()->query_gender()) ? "good Lady" :
                    "Brother") + "! Welcome to the Free Mercenary"
                  + " Guild!\n\n");
                write("You are handed a Mercenary insignia.\n");
                say("One of the Mercenaries hands " + QTNAME(this_player())
                  + " something.\n");
                MERC_MASTER->set_info(this_player(), "join_time", time());

                write_file(LOG_DIR + "join_log",
                   TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                 + ctime(time())[11..18] + ") "
                 + capitalize(this_player()->query_real_name()) 
                 + " joined the guild.\n");

                TELL_G("\n\t" + capitalize(this_player()->query_real_name())
                  + " joined the New Mercs!\n");

		return 1;
    
	    case -4:
	        /* The player has an occ guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
                if (IS_MERC(this_player()))
                {
                    write("You are already one of the Mercenaries!\n");
                }
                else
                {
		    write("It seems your current guilds will not allow"
                      + " you to join the Mercenaries.\n");
                }
		break;
    
	    default:
	        /* Some error in shadowing */
		write("An error has prevented you from joining. Please"
                  + " mail the AoP immediately.\n");
		break;
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
} /* occjoin */


/*
 * Function name:        occleave
 * Description  :        Allow players to try to leave the guild
 * Arguments    :        string str - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
int
occleave(string str)
{
    object  journal;

    if (strlen(str))
    {
        notify_fail("Simply <unregister> to leave the Mercenaries.\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You'd need to be a member before you could do that!\n");
        return 1;
    }

    if (!this_player()->query_prop(WARNING_PROP))
    {
        write("Leave the Mercenary Guild? If you are sure, then"
          + " <unregister> one more time.\n");
        this_player()->add_prop(WARNING_PROP, 1);
        return 1;
    }

    this_player()->remove_occ_member();
    write("You hand in your Mercenary Insignia and cross your name off"
      + " of the active registry of guild members.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " crosses "
      + this_player()->query_possessive() + " name off the registry of"
      + " active guild members.\n", this_player());

    TELL_G("\n\t" + capitalize(this_player()->query_real_name())
      + " left the New Merc guild. Awwwwww ... \n");

    /* If they are currently working on the Merc Spy Quest, we put
     * a stop to it here. The quest is not to be completed by
     * quickly joining and then leaving the guild.
     */
    if (objectp(journal = present("_merc_spy_journal", this_player())))
    {
        tell_room(this_object(), "One of the guards says: Hey,"
          + " what is that you've got there? Hand that over!\n");
        tell_room(this_object(), "The guard takes something from "
          + QTNAME(this_player()) + " and looks it over.\n",
            this_player());
        write("The guard takes the red leatherbound journal from"
          + " you and looks it over.\n");

        if (strlen(journal->query_note_txt()))
        {
            tell_room(this_object(), "The guard gasps in"
              + " astonishment!\n");
            tell_room(this_object(), "The guard says: Well now,"
              + " doing a little spying for someone are we? Not"
              + " on my watch you little weasel! I'm keeping"
              + " this. Now get out of here!\n");

            journal->remove_object();
            Persona_Non_Grata += ({ this_player()->query_real_name() });

            write_file(LOG_DIR + "merc_spy",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_real_name()) 
              + " got caught trying to leave the guild as a spy.\n");
        }
        else
        {
            tell_room(this_object(), "The guard goes hmmm ...\n");
            tell_room(this_object(), "The guard says: Must not be"
              + " what I thought it was.\n");
            tell_room(this_object(), "The guard returns what he"
              + " had taken to " + QTNAME(this_player()) + ".\n",
                this_player());
            write("The guard gives you the journal back.\n");
        }
    }

    write_file(LOG_DIR + "leave_log",
       TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
     + ctime(time())[11..18] + ") "
     + capitalize(this_player()->query_real_name()) 
     + " left the guild.\n");

    return 1;
} /* occleave */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
void
init()
{
    ::init();
    add_action(occjoin, "register");
    add_action(occleave, "unregister");
    add_action(transfer_membership, "transfer");
    add_action(do_mark, "mark");
    add_action(do_mark, "mmark");
} /* init */


/* 
 * Function name:       has_old_merc_shadow
 * Description  :       Goes through the shadows and sees if the player
 *                      has the old merc shadow.
 * Arguments    :       player - player to check if they have the merc
 *                               shadow
 * Returns      :       0/1 - does not have old shadow/has old shadow
 */
public int
has_old_merc_shadow(object player)
{
    object current_shadow;
    
    current_shadow = player;
    while (current_shadow = shadow(current_shadow, 0))
    {
        if (MASTER_OB(current_shadow) == OLD_MERC_SHADOW)
        {
            return 1;
        }
    }
    
    return 0;
} /* has_old_merc_shadow */


/*
 * Function name:        transfer_membership
 * Description  :        This is special code to accomodate members of
 *                       the old Mercenary guild who wish to join the
 *                       new one.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
transfer_membership(string arg)
{
    if (!strlen(arg) ||
        arg != "membership")
    {
        notify_fail("Transfer what? Transfer membership, perhaps?\n");
        return 0;
    }

    if (!has_old_merc_shadow(this_player()))
    {
        if (IS_MERC(this_player()))
        {
            notify_fail("You are already a Mercenary!\n");
            return 0;
        }

        notify_fail("Only members of Maligant's old guild may transfer"
          + " membership here.\n");
        return 0;
    }

    write("You decide to transfer your membership to the Free Mercenary"
      + " guild.\n\n");

    /* This is a call to code defined in:
     *
     *     /d/Sparkle/guilds/mercs/lib/merc_shadow.c
     *
     * It is the code from the old guild which I have modified to make
     * possible the transfer to the new guild without loss of
     * occupational guild exp.
     */
    this_player()->remove_occ_merc(this_player(), "transfered", 1);

    write("\nA few Mercenaries gather around, and nod approvingly. One"
      + " says: Looks like this one's ready to become one of ours"
      + " now!\n\n");

    /* Now we go ahead and assume all will work properly, and initiate
     * the regular join sequence.
     */
    this_player()->command("$register");
    return 1;
} /* transfer_membership */


/*
 * Function name:        do_mark
 * Description  :        Allow players to mark weapons and armours
 *                       to prevent them from being sold.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_mark(string arg)
{
    mixed    obj;
    mixed    sell_prop;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to <mark>?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("Only Mercenaries may use the anvil.\n");
        return 1;
    }

    obj = PARSE_COMMAND_ONE(arg, all_inventory(this_player()),
                "[the] [a] [an] %i");

    if (!objectp(obj))
    {
        notify_fail("You don't seem to have any such thing.\n");
        return 0;
    }

    if (!obj->check_weapon() && !obj->check_armour())
    {
        notify_fail("Only armours and weapons may be marked.\n");
        return 0;
    }

    if (obj->query_auto_load() ||
        obj->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail("That is certainly not something you need to"
          + " mark!\n");
        return 0;
    }

    if (obj->query_worn() ||
        obj->query_wielded())
    {
        notify_fail("You cannot mark something you currently"
          + " have equipped!\n");
        return 0;
    }

    sell_prop = obj->query_prop(OBJ_M_NO_SELL);

    if (sell_prop)
    {
        if (sell_prop == Mark_Text)
        {
            notify_fail("It has already been marked with the Mercenary"
              + " insignia. No need to mark it twice!\n");
        }
        else
        {
            notify_fail("This already cannot be sold. There is no need"
              + " to mark it.\n");
        }
        return 0;
    }

    if (!obj->query_prop(MARK_PROP))
    {
        write("Mark the " + obj->short() + " with the Mercenary"
          + " insignia? Doing so will mean that it cannot be sold."
          + " If that is your wish, then re-enter the command.\n");
        obj->add_prop(MARK_PROP, 1);
        return 1;
    }

    this_player()->reveal_me(1);

    write("You place the " + obj->short() + " on the anvil and strike"
      + " it with a single clean blow with the heavy hammer. The"
      + " insignia of the Mercenary guild is now embedded in it's"
      + " surface, virtually guaranteeing that no merchant in the"
      + " realms will dare to accept it for sale.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " places "
      + LANG_ADDART(obj->short()) + " on the anvil and strikes"
      + " it once with a heavy hammer.\n", this_player());

    obj->add_prop(OBJ_M_NO_SELL, Mark_Text);
    return 1;
} /* do_mark */

