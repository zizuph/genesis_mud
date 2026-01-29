/*
 * Chapel of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 * Added Seeker code - Jaacar, July 2016
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

inherit TEMPLE_ROOM_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define DEATH_OBJECT (ELEMENTALIST_OBJS + "elemental_punishment")
#define JOINED(x) ({"The voice of Lord Pyros echoes in your mind: "+x->query_name()+" has joined the Circle.\n",\
        "Lady Gu's voice rings forth in your head: "+x->query_name()+" is the newest member of the Circle.\n",\
        "Echoing through your mind you hear Lord Diabrecho say: "+x->query_name()+" has just joined the Circle.\n",\
        "Like a small breeze in your ears you hear Lady Aeria say: "+x->query_name()+" has joined the Circle.\n"})
        
#define JOINED_SEEKERS(x) ({"The voice of Lord Pyros echoes in your mind: "+x->query_name()+" has joined the Seekers.\n",\
        "Lady Gu's voice rings forth in your head: "+x->query_name()+" is the newest member of the Seekers.\n",\
        "Echoing through your mind you hear Lord Diabrecho say: "+x->query_name()+" has just joined the Seekers.\n",\
        "Like a small breeze in your ears you hear Lady Aeria say: "+x->query_name()+" has joined the Seekers.\n"})

#define LEFT(x) ({"You hear the thunderous voice of Lord Pyros proclaim: "+x->query_name()+" has betrayed us and has been banished from the Circle!\n",\
        "Winds howl in the voice of Lady Aeria: "+x->query_name()+" has betrayed the circle and is no longer one of us!\n",\
        "The ground shakes violently below you momentarily as Lady Gu speaks: "+x->query_name()+" has betrayed the Elementals and is no longer one of the Circle!\n",\
        "You hear the angry voice of Lord Diabrecho: "+x->query_name()+" has betrayed the circle and is no longer with us!\n"})
#define I_PRAYED_WORSHIPPERS "_player_i_prayed_worshippers"

// Prototypes
public void betray1(object player);
public void join_worshippers(object player);
public void join_seekers(object player);

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public int
can_use_council_commands()
{
    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_ew_council(this_player(), 1))
    {
        return 1;
    }
    return 0;
}

public void
create_temple_room()
{
    set_short("In a chapel");
    set_long("@@desc_long_description");

    try_item( ({ "door", "sign", "slender door", "small sign", "library" }),
        "A tall door, crafted by an intrinsic mix of dark oak and petrified "
      + "wood is rather slender. The door itself is also "
      + "remarkably hefty, likely to prevent sounds from the prayers of the "
      + "chapel to travel into the hallway beyond.\n");
      
    try_item( ({ "chapel" }),
        "You are standing in the chapel, a place of worship and ceremonies.\n");
    
    try_item( ({ "altar", "marble altar", "polished altar",
        "polished marble altar" }),                   
        "The altar is made of white marble from the quarries of Argos, the "
      + "same material that is used in the marble columns.\n");
    
    try_item( ({ "copper brazier", "brazier", "censor", "silver censor",
        "tripod", "slendar tripod" }),  
        "The brazier, censor, and tripod are all implements used in the "
      + "rituals and ceremonies performed here at the temple.\n");
    
    try_item( ({ "mats", "prayer mats", "mat", "prayer mat" }),
        "It looks like you can <kneel> before the altar on one of the "
      + "prayer mats surrounding the altar if you wish to pray to the "
      + "Elementals of Calia.\n");
    

    add_exit(ELEMENTALIST_TEMPLE + "outer13a", "north"); 
}

public int
do_allow(string str)
{
    if (!can_use_council_commands())
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Who would you like to allow to join the Elemental Worshippers?\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());
    if (GUILD_MANAGER->query_is_worshipper(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Worshippers!\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_cleric(str))
    {
        write(capitalize(str) + " is already a member of the Elemental Clerics and cannot "
              + "join the Elemental Worshippers!\n");
        return 1;
    }

    if (!SECURITY->exist_player(str))
    {
        write(capitalize(str) + " doesn't appear to have ever walked the Realms.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_betrayed(str))
    {
        write(capitalize(str) + " has already betrayed the Elementals before and "
              + "is not allowed to join ever again.\n");
        return 1;
    }

    if (GUILD_MANAGER->query_is_guild_expelled(str))
    {
        write(capitalize(str) + " was expelled from the Elementals before. To "
              + "allow them to join, please <rempunish> them first.\n");
        return 1;
    }
    
    if (!GUILD_MANAGER->query_is_seeker(str))
    {
        write(capitalize(str) + " is already not a member of the Elemental Seekers and cannot "
              + "join the Elemental Worshippers!\n");
        return 1;
    }
    
    GUILD_MANAGER->set_can_join_worshippers(str, 1);
    str->add_prop(I_PRAYED_WORSHIPPERS, 1);
    string log_message = capitalize(str)
        + " has been given permission to join the Elemental Worshippers "
        + "by " + capitalize(this_player()->query_real_name())
        + ".\n";
    send_debug_message("ew_council", log_message);
    COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);
    write("Ok.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action("do_kneel", "kneel");
    add_action("do_rise", "rise");
    add_action("do_pray", "pray");
    add_action("do_betray", "betray");
    add_action(do_allow, "allow");
}

/*
 * Function name: do_kneel
 * Description  : Allows the player to kneel before the altar
 * Arguments    : arg - should be empty
 * Returns      : int 1/0 - success/failure.
 */
public int
do_kneel(string arg)
{
    // We need to add this function because the gs_catch_all captures
    // all of the commands. We do add_action here so that we can change
    // the verbs that are used to "meditate"
    if (this_player()->query_prop(LIVE_I_MEDITATES))
    {
        write("You are already kneeling!\n");
        return 1;
    }

    write("You find yourself an empty prayer mat and kneel before "
        + "the altar to begin praying. Once you are done, you can "
        + "<rise> to your feet.\n");
    say(QCTNAME(this_player()) + " kneels down on the prayer mat before "
        + "the altar.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is praying");
    this_player()->add_prop(LIVE_I_MEDITATES, 1);
    return 1;
}

/*
 * Function:    do_rise
 * Description: Function to allow someone to rise from the prayer
 *              mats.
 */
public int
do_rise(string arg)
{
    if (!this_player()->query_prop(LIVE_I_MEDITATES))
    {
        write("You are not kneeling!\n");
        return 1;
    }
    
    write("You complete your prayers and rise from the prayer "
        + "mat.\n");
    say(QCTNAME(this_player()) + " rises from the prayer mat.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    this_player()->remove_prop(LIVE_I_MEDITATES);
    return 1;
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    if (ob->query_prop(LIVE_I_MEDITATES))
    {
        ob->catch_tell("You can't leave while you're still kneeling and "
            + "praying! Try to <rise> from the prayer mat first.\n");
        return 1;
    }
    
    return 0;
}

public string
desc_long_description()
{
    string long_desc = 
          "You have entered the chapel of the Elemental Temple of "
        + "Calia, a place full of memories of ceremonies gone by. A "
        + "polished marble altar stands in the center of the room. On "
        + "top of one side of the altar sits a copper brazier, while "
        + "a silver censor sits atop a slender tripod on the other side. ";
    
    if (this_player()->query_prop(LIVE_I_MEDITATES))
    {
        long_desc += "You are kneeling at a prayer mat surrounding the altar "
            + "from which you can <rise>. ";
    }
    else
    {
        long_desc += "Closely surrounding the altar are prayer mats where one may "
        + "<kneel>. ";
    }
    
    long_desc += "Behind the mats a few rows of wooden benches encircle "
        + "the altar. To the north you see a slender door. "; 
      
    return long_desc += "\n\n";
}

// LEAVING FUNCTIONS

/*
 * Function:    betray
 * Description: Betray the Elementals and leave the guild
 */
public int
do_betray(string str)
{
    setuid();
    seteuid(getuid());
    if (!IS_WORSHIPPER(this_player()) && !IS_SEEKER(this_player()))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!strlen(str) || !parse_command(lower_case(str), this_player(), " [the] 'elementals' "))
    {
        notify_fail("Betray who? The Elementals\n");
        return 0;
    }

    str = lower_case(str);    
    clone_object("/std/paralyze")->move(this_player(), 1);
    present("_elemental_guild_wand", this_player())->remove_object();
    present("_elemental_guild_dagger", this_player())->remove_object();
    present("_elemental_guild_chalice", this_player())->remove_object();
    present("_elemental_guild_pentacle", this_player())->remove_object();
    
    GUILD_MANAGER->set_guild_betrayed(this_player(), 1);
    GUILD_MANAGER->leave_guild(this_player());
    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                       + " has betrayed the Elementals.", EVENTS_LOG);
    COUNCIL_LOG_BOOK->update_log_book(
        my_time() + capitalize(this_player()->query_real_name()) 
        + " has betrayed the Elementals.\n");
    write("The air around feels like it is closing in on you. Your "+
        "skin begins to feel very warm. Your blood temperature seems "+
        "to be rising very rapidly. You notice the area around you "+
        "begins to get darker. The ground beneath your feet rumbles "+
        "and shakes. Suddenly you find yourself surrounded by four "+
        "powerful beings, one made of earth, one of air, one of water, "+
        "and one of fire. Each seems to be invoking some terrible "+
        "spell. All goes dark.\nYou still feel the ground trembling.\n");
    tell_room(environment(this_player()),
              QCTNAME(this_player())+" prays at the altar.\nSuddenly, the air "+
              "around "+this_player()->query_objective()+" grows very dark, the ground "+
              "beneath "+this_player()->query_possessive()+" feet begins to shake violently. "+
              capitalize(this_player()->query_possessive())+" eyes glaze over.\n", this_player());
    set_alarm(2.0, 0.0, &betray1(this_player()));
    return 1;
}

public void
betray1(object player)
{
    setuid();
    seteuid(getuid());

    tell_object(player, "Your blood begins to boil under your skin.\n"+
                "You hear a demonic laughter filling the air around you.\n");
                              
    tell_room(environment(player), capitalize(player->query_pronoun()) +
              " is surrounded totally by "+
              "darkness.\nThe ground shakes massively.\n", player);
    if (IS_WORSHIPPER(player))
    {          
    	tell_object(player,"A voice echoes in your mind: You have betrayed us and "+
                "shall now pay the ultimate price!\n"+
                "The last thing you feel is your arms and legs literally exploding "+
                "from the pressure of your boiling blood.\n");
              
    	tell_room(environment(player),"Suddenly, all is back "+
              "to normal, except where " + QTNAME(player) + " was standing is now a "+
              "smouldering pile of remains.\n", player);
    	if (!player->query_prop(LIVE_I_NO_CORPSE))
    	{
        	player->add_prop(LIVE_I_NO_CORPSE, 1);
    	}
    	string enemy_race = player->query_race_name();
    	player->heal_hp(-player->query_max_hp());
      	player->do_die(this_object());
        object piece = clone_object(DEATH_OBJECT);
        piece->set_race(enemy_race);
        piece->move(this_object(), 1);
    }
    else if (IS_SEEKER(player))
    {
    	tell_object(player,"A voice echoes in your mind: You have betrayed us and "+
                "shall now pay the price!\n"+
                "You feel intense pain throughout your body and almost black out. "+
                "You feel you are on the verge of death and then suddenly everything "+
                "is calm. You feel as though you almost died!\n");
              
    	tell_room(environment(player),"Suddenly, all is back "+
              "to normal.\n", player);
    	player->heal_hp(-player->query_max_hp());
    }
    object * listeners = GUILD_MANAGER->query_awake_clerics() + GUILD_MANAGER->query_awake_worshippers();
    listeners->catch_tell(LEFT(player)[random(4)]);
}

public void
inform_player_joining_instructions(object player)
{
    // Begin Sequence
    player->catch_tell("An apparition appears to you.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes suddenly glaze over.\n", player);

    // Actual Instructions
    player->catch_tell(
        "The apparition speaks to you: If you are interested in becoming one with the "
        + "Elementals, then you should seek out the library within this Temple. There "
        + "you shall find information about Us and what is expected of you if you "
        + "choose to join us. You shall discover information about four items known as "
        + "the Elemental Tools. If you truly seek to join us, then you must prove "
        + "yourself by constructing these tools in the chamber within the Temple "
        + "gardens. You must also be accepted by a member of the Elemental Worshipper "
        + "Council. You can mail the council in post office in the Temple. Once you "
        + "have completed these tasks, return here and you shall be inducted into "
        + "the Elemental Worshippers.\n\n");

    // End Sequence
    player->catch_tell("The apparition disappears.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes return to normal.\n", player);
}


public void            
inform_player_need_permission(object player)
{
    // Begin Sequence
    player->catch_tell("An apparition appears to you.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes suddenly glaze over.\n", player);
        
    // Actual Instructions
    player->catch_tell(
        "The apparition speaks to you: Greetings again, child.\n");
    player->catch_tell(
        "The apparition speaks to you: You have not yet been accepted by a member "
        + "of the Elemental Worshippers Council. Return to me again once this has "
        + "been done. Remember that you can mail the Council from the post office "
        + "located in the southwest part of the Outer Circle.\n\n");
        
    // End Sequence
    player->catch_tell("The apparition disappears.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes return to normal.\n", player);
}

public void
inform_player_need_tools(object player)
{
    object * power_tools = filter(all_inventory(player), &->is_elemental_power_tool());
    
    // Begin Sequence
    player->catch_tell("An apparition appears to you.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes suddenly glaze over.\n", player);
        
    // Actual Instructions
    player->catch_tell(
        "The apparition speaks to you: Greetings again, child.\n");
    player->catch_tell(
        "The apparition speaks to you: You have not yet constructed all four of "
        + "the Elemental Tools, having " 
        + (sizeof(power_tools) == 0 ? "none" : "only " + LANG_NUM2WORD(sizeof(power_tools)))
        + " of the four needed.\n");
    string * missing_tools = 
        ({ "platinum earth pentacle", "copper fire wand", 
                "silver air dagger", "gold water chalice" }) 
        - map(power_tools, &->short());
    player->catch_tell(
        "The apparition speaks to you: You are missing a " + COMPOSITE_WORDS(missing_tools)
        + ". Return to me again when you have completed constructing your Tools.\n\n");
        
    // End Sequence
    player->catch_tell("The apparition disappears.\n");
    tell_room(this_object(), QCTPNAME(player) + " eyes return to normal.\n", player);    
}

public void
begin_worshipper_joining_sequence(object player)
{
    player->catch_tell(
        "The apparition speaks to you: You have brought all four of "
        + "the Elemental Tools and received permission from the Elemental "
        + "Worshippers Council.\n");
    set_alarm(2.0, 0.0, &join_worshippers(player));
}

public void
begin_seeker_joining_sequence(object player)
{
    player->catch_tell(
        "The apparition speaks to you: You have brought all four of "
        + "the Elemental Tools as you have been requested.\n");
    set_alarm(2.0, 0.0, &join_seekers(player));
}

public int
player_has_all_tools(object player)
{
    setuid();
    seteuid(getuid());
    if (objectp(present("_elemental_guild_wand", player))
        && objectp(present("_elemental_guild_dagger", player))
        && objectp(present("_elemental_guild_chalice", player))
        && objectp(present("_elemental_guild_pentacle", player)))
    {
        return 1;
    }
    return 0;
}

public int
do_pray(string str)
{
    setuid();
    seteuid(getuid());
 
    object player = this_player();
    if (!player->query_prop(LIVE_I_MEDITATES))
    {
        notify_fail("You should <kneel> before the altar to pray.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Pray to whom?\n");
        return 0;
    }
       
    if (GUILD_MANAGER->query_is_guild_betrayed(player))
    {
        write("A voice booms in your head:  LEAVE NOW!  You have "+
            "betrayed the Elementals!\n");
        return 1;
    }
    if (GUILD_MANAGER->query_is_guild_expelled(player))
    {
        write("You have been outcast from the Circle, and must seek "+
            "atonement before rejoining.\n");
        return 1;
    }

    str = lower_case(str);
    if (parse_command(str, player, " [to] [the] 'elementals' "))
    {
        if (IS_MEMBER(player) && !IS_SEEKER(player))
        {
            write("An apparition appears to you and says: "+
                  "Go in peace my child.\n");
            write("The apparition disappears.\n");
            return 1;
        }

        // If you're not a member, and you pray to the elementals:
        // 1. First time you pray, you are told what to do. A prop is added
        //    to indicate that the instructions have been given to you
        // 2. Next time you pray, if you don't have the tools, you are told
        //    the instructions again.
        //    If you have the tools, but do not have permission to join, you
        //    are told that you will need permission.
        // 3. If you have the tools, aren't a member of the Seekers and haven't
        //    been given permission, then you join the Seekers guild
        // 4. If you have the tools, are a member of the Seekers guild and
        //    have been given permission, then the joining sequence begins.
        
        if (!player->query_prop(I_PRAYED_WORSHIPPERS))
        {
            inform_player_joining_instructions(player);
            player->add_prop(I_PRAYED_WORSHIPPERS, 1);
            return 1;
        }
        else if (!player_has_all_tools(player))
        {
            inform_player_need_tools(player);
            return 1;
        }
        // If we get here, they are ready to become an Elemental Seeker
        else if (!GUILD_MANAGER->query_can_join_worshippers(player))
        {
        	// If they are already a Seeker, tell them they need permission
        	if (IS_SEEKER(player))
        	{
        		inform_player_need_permission(player);
        		return 1;
        	}
        	// If they aren't a Seeker, we can let them join here
        	begin_seeker_joining_sequence(player);
        	return 1;
        }
        // If we get here, they are ready to become an Elemental Worshipper
        begin_worshipper_joining_sequence(player);
        return 1;
    }
    else if (parse_command(str, player, " [to] 'psuchae' / 'pyros' / 'diabrecho' / 'aeria' / 'gu' "))
    {
        write("You pray fervently to the Elemental and you feel that your "
            + "prayer has been heard.\n");
        say(QCTNAME(player) + " prays fervently before the altar.\n");
    }
    else
    {   
        write("You pray " + str + ".\n");
        say(QCTNAME(player) + " prays fervently before the altar.\n");
    }

    return 1;
}

public void
join_worshippers(object player)
{
    setuid();
    seteuid(getuid());

    // Begin Section
    player->catch_msg(
        "A cloud suddenly appears and what you recognize as "
        + "the apparition takes on solid form before your eyes.\n");
    tell_room(environment(player), "A cloud suddenly appears and slowly "+
        "solidifies into human shape.\n", player);

    player->catch_msg(
        "The apparition speaks to you:\n"
        + "I am the Elder of The Elemental Worshippers of Calia. I congratulate you on "
        + "proving yourself worthy of becoming one with the Elementals. "
        + "I hereby welcome you into the Circle!\n"
        + "The Elder whispers to you: You must now select an Elemental to follow. "
        + "Go to the library and read about each of the Elementals, then seek out the "
        + "Elemental in this Temple and 'worship <name>' there. You may now pass through "
        + "into the inner parts of this Temple. May the Elementals guide your ways "
        + "always.\n");
    tell_room(environment(player),
              "The shape speaks to " + QTNAME(player) + ": "
              + "I am the Elder of the Elemental Worshippers of Calia. I congratulate "
              + "you on proving yourself worthy of becoming one with the Elementals. I "
              + "hereby welcome you into the Circle!\n"
              + "The shape whispers something to " + QTNAME(player) + ".\n", player);

    GUILD_MANAGER->join_guild(player);

    // End Sequence
    player->catch_tell(
        "The Elder disappears into a swirling mass of mist.\n");
    tell_room(environment(player),
              "The shape disappears into a swirling mass of mist.\n", player);

    // Inform the rest of the guild
    object * listeners = GUILD_MANAGER->query_awake_clerics() + GUILD_MANAGER->query_awake_worshippers() +
        GUILD_MANAGER->query_awake_seekers();
    listeners -= ({ player });
    listeners->catch_tell(JOINED(player)[random(4)]);

    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                       + " has joined the Elemental Worshippers.", EVENTS_LOG);
    COUNCIL_LOG_BOOK->update_log_book(
        my_time() + capitalize(this_player()->query_real_name()) 
        + " has joined the Elemental Worshippers.\n");
}

public void
join_seekers(object player)
{
    setuid();
    seteuid(getuid());

    // Begin Section
    player->catch_msg(
        "A cloud suddenly appears and what you recognize as "
        + "the apparition takes on solid form before your eyes.\n");
    tell_room(environment(player), "A cloud suddenly appears and slowly "+
        "solidifies into human shape.\n", player);

    player->catch_msg(
        "The apparition speaks to you:\n"
        + "I am the Elder of The Elemental Worshippers of Calia. I congratulate you on "
        + "proving yourself worthy of becoming one of the Seekers of the Elementals. "
        + "May the Elementals guide your ways always. You must now be accepted by a member "
        + "of the Elemental Worshippers Council. Return to me again once this has "
        + "been done. Remember that you can mail the Council from the post office "
        + "located in the southwest part of the Outer Circle.\n\n");
    tell_room(environment(player),
              "The shape speaks to " + QTNAME(player) + ": "
              + "I am the Elder of the Elemental Worshippers of Calia. I congratulate "
              + "you on proving yourself worthy of becoming one of the Seekers of the "
              + "Elementals. The shape whispers something to " + QTNAME(player) + ".\n", player);

    GUILD_MANAGER->join_seekers_guild(player);

    // End Sequence
    player->catch_tell(
        "The Elder disappears into a swirling mass of mist.\n");
    tell_room(environment(player),
              "The shape disappears into a swirling mass of mist.\n", player);

    // Inform the rest of the guild
    object * listeners = GUILD_MANAGER->query_awake_clerics() + GUILD_MANAGER->query_awake_worshippers() +
        GUILD_MANAGER->query_awake_seekers();
    listeners -= ({ player });
    listeners->catch_tell(JOINED_SEEKERS(player)[random(4)]);

    send_debug_message("worshipper", capitalize(this_player()->query_real_name())
                       + " has joined the Elemental Seekers.", EVENTS_LOG);
    COUNCIL_LOG_BOOK->update_log_book(
        my_time() + capitalize(this_player()->query_real_name()) 
        + " has joined the Elemental Seekers.\n");
}
