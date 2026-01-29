/*
 * Air Dagger for the Elemental Worshippers
 *
 * Created by Petros, March 2014
 */

#pragma save_binary

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include "defs.h"

inherit ELEMENTALIST_OBJS + "power_tool_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define DAGGER_SUBLOC "_elemental_guild_dagger_subloc"
#define LEFT(x) ({"You hear the thunderous voice of Lord Pyros proclaim: "+x->query_name()+" has betrayed us and has been banished from the Circle!\n",\
        "Winds howl in the voice of Lady Aeria: "+x->query_name()+" has betrayed the Circle and is no longer one of us!\n",\
        "The ground shakes violently below you momentarily as Lady Gu speaks: "+x->query_name()+" has betrayed the Elementals and is no longer one of the Circle!\n",\
        "You hear the angry voice of Lord Diabrecho: "+x->query_name()+" has betrayed the Circle and is no longer with us!\n",\
        "Resonating in your mind you hear Psuchae say: "+x->query_name()+" has betrayed the Circle and is no longer with us!\n"})
#define DEATH_OBJECT (ELEMENTALIST_OBJS + "elemental_punishment")
#define CLERIC_BOARDROOM          (ELEMENTALIST_TEMPLE + "ec_boardroom")

// Global Variables
public int worn = 0;

// Prototypes
public void betray1(object player);

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

/*
 * Function:    create_power_tool
 * Description: Override this to customize the power tool
 */
public void
create_power_tool()
{
    set_name("dagger");
    add_adj("silver");
    add_adj("air");
    add_name("_elemental_guild_dagger");
    set_short("silver air dagger");
    set_element_flag(AIR_FLAG);
}

/*
 * Function:    is_worn
 * Description: This is not a real wearable object. Instead, we just keep
 *              track of the worn variable ourselves.
 */
public int
is_worn()
{
    return worn;
}

/*
 * Function:    remove
 * Description: Removes the dagger from the belt subloc
 */
public int
unsheathe(string str)
{
    object this = this_object();
    object tp = this_player();
    if (!present(this,tp))
    {
        notify_fail("You don't have the " + short() + " to unsheathe!\n");
        return 0;
    }
    if (!worn)
    {
        notify_fail("You don't have the " + short() + " sheathed in your belt!\n");
        return 0;
    }
    tp->remove_subloc(DAGGER_SUBLOC);
    worn = 0;
    write("You unsheathe the " + short() + " from your belt.\n");
    say(QCTNAME(tp)+" unsheathes a " + short() + " from " 
        + tp->query_possessive() + " belt.\n");
    set_no_show_composite(0);
    return 1;
}

/*
 * Function:    show_subloc
 * Description: Displays the appropriate message when the dagger is sheathed
 *              on the player's belt.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != DAGGER_SUBLOC)
    {
        return "";
    }

    string data;
    if (for_obj != on)
    {
        data = capitalize(on->query_pronoun())+ " has a " + short()
            + " sheathed in " + on->query_possessive() + " belt.\n";
    }
    else
    {
        data = "You have a " + short() + " sheathed in your belt.\n";
    }
    return data;
}

/*
 * Function:    sheathe
 * Description: Puts the dagger into the subloc on the player.
 */
public int
sheathe(string str)
{
    object this = this_object();
    object tp = this_player();
    if (!present(this, tp))
    {
        notify_fail("You don't have the " + short() + " to sheathe!\n");
        return 0;
    }
    if (worn)
    {
        notify_fail("You already have the " + short() + " sheathed in your belt!\n");
        return 0;
    }
    tp->add_subloc(DAGGER_SUBLOC, this);
    worn = 1;
    write("You sheathe the " + short() + " in your belt.\n");
    say(QCTNAME(tp)+" sheathes a " + short() + " in " 
        + tp->query_possessive() + " belt.\n");
    this->set_no_show_composite(1);
    return 1;
}

/*
 * Function:    hook_destroy_message
 * Description: Override this hook to show your custom message for the
 *              destruction of the power tool.
 */
public string
hook_destroy_message(object env)
{
    return "The " + short() + " shatters into thousands of tiny pieces.\n";
}

/*
 * Function:    hook_describe_long
 * Description: Override this for the main part of the description for
 *              the power tool. The rune information will be added at
 *              the end.
 */
public string
hook_describe_long()
{
    return "This " + short() + " is also known as an Air Dagger. The blade "
        + "is about one foot in length, and it is coated in silver. The "
        + "hilt is brightly polished and along the length of it are carved "
        + "strange runes. "
        + "Alongside the runes, you see the words 'dsheathe' and 'dunsheathe'.\n";}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "Egsousia";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "Aeria";
}

public int
wield(string str)
{
    object target = PARSE_COMMAND_ONE(str, this_player(), "[the] %i");
    if (objectp(target) && target == this_object())
    {
        write("It would be disrespectful to use one of the Elemental "
                + "Tools in combat!\n");
        return 1;
    }
    return 0;
}

public int
do_touch(string str)
{
    object target = PARSE_COMMAND_ONE(str, 0, "%i");
    if (!target)
    {
        notify_fail("Touch whom with your air dagger?\n");
        return 0;
    }
    
    this_player()->catch_msg("You touch "+(target->query_The_name(this_player())) + 
        " on the left shoulder with your air dagger briefly.\n");
    target->catch_msg((TP->query_The_name(target))+" touches you on the left shoulder "+
        "with "+TP->query_possessive()+" air dagger briefly. You feel a light breeze "+
        "blowing across your skin for a moment.\n");
    tell_room(TO,QCTNAME(TP) + " touches "+QTNAME(target)+" on the left shoulder with "+
        TP->query_possessive()+" air dagger briefly.\n",
        ({target,TP}));
    return 1;
}

/*
 * Function:    betray
 * Description: Betray the Elementals and leave the guild
 */
public int
do_betray(string str)
{
    object player = this_player();
    setuid();
    seteuid(getuid());
    if (!IS_MEMBER(player))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!strlen(str) || !parse_command(lower_case(str), player, " [the] 'elementals' "))
    {
        notify_fail("Betray who? The Elementals? (WARNING! This will likely result in your "+
            "death!)\n");
        return 0;
    }

    str = lower_case(str);    
    clone_object("/std/paralyze")->move(player, 1);
        
    COUNCIL_LOG_BOOK->update_log_book(
        my_time() + capitalize(player->query_real_name()) 
        + " has betrayed the Elementals.\n");
    write("The air around feels like it is closing in on you. Your "+
        "skin begins to feel very warm. Your blood temperature seems "+
        "to be rising very rapidly. You notice the area around you "+
        "begins to get darker. The ground beneath your feet rumbles "+
        "and shakes. Suddenly you find yourself surrounded by four "+
        "powerful beings, one made of earth, one of air, one of water, "+
        "and one of fire. Each seems to be invoking some terrible "+
        "spell. All goes dark.\nYou still feel the ground trembling.\n");
    tell_room(environment(player),QCTNAME(player)+" closes "+
        player->query_possessive()+" eyes.\nSuddenly, the air "+
        "around "+player->query_objective()+" grows very dark, the ground "+
        "beneath "+player->query_possessive()+" feet begins to shake violently. "+
        capitalize(player->query_possessive())+" eyes glaze over.\n", player);
    set_alarm(2.0, 0.0, &betray1(player));
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
    	GUILD_MANAGER->leave_guild(player);
    	string enemy_race = player->query_race_name();
    	player->heal_hp(-player->query_max_hp());
      	player->do_die(this_object());
        object piece = clone_object(DEATH_OBJECT);
        piece->set_race(enemy_race);
        piece->move(this_object(), 1);
    }
    else if (IS_CLERIC(player))
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
    	if (player->is_elemental_racial_cleric())
    	    GUILD_MANAGER->leave_race_guild(player);
    	GUILD_MANAGER->leave_occ_guild(player);
    	object board = present("board", CLERIC_BOARDROOM->get_this_object());
        if (objectp(board)) 
        { 
            board->create_note("Betrayal!", 
                     "Sehis", capitalize(player->query_real_name()) + 
                     " has betrayed the Elementals and is no longer welcome in "+
                     "this Temple!\n\nSehis\n"); 
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
    	GUILD_MANAGER->leave_seekers_guild(player);
    }
    present("_elemental_guild_wand", player)->remove_object();    
    present("_elemental_guild_chalice", player)->remove_object();
    present("_elemental_guild_pentacle", player)->remove_object();
    present("_elemental_guild_mandala", player)->remove_object();
    present("_echosen_", player)->remove_object();
    
    GUILD_MANAGER->set_guild_betrayed(player, 1);

    object * listeners = GUILD_MANAGER->query_awake_clerics() + GUILD_MANAGER->query_awake_worshippers();
    listeners->catch_tell(LEFT(player)[random(5)]);
    present("_elemental_guild_dagger", player)->remove_object();
}

public void
init()
{
    ::init();

    add_action(wield, "wield");
    add_action(sheathe, "dsheathe");
    add_action(unsheathe, "dunsheathe");
    add_action(do_touch, "ltouch");
    add_action(do_betray, "betray");
}

