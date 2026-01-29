/*
 * /w/petros/sparkle/library/obj/signature_book.c
 *
 * This is a quest item for the Genesis Library. The quest is
 * a small one from Nikolon where you are given a little book and
 * can use it to collect signatures of people in the Realms. Once
 * you collect 20 signatures, you can return it for a reward.
 *
 * Created April 2008, by Petros
 */
 
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include "defs.h"

// Defines
#define SIGNATURE_LIMIT 10

// Global Variables
string      owner_name;
string *    signees;

// Prototypes
public void             create_object();
public int              request_cmd(string arg);
public int              read_cmd(string arg);
public int              sign_cmd(string arg);
public int              return_cmd(string arg);
public void             add_signature(object player);
public void             remove_signature_book();

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_signature_book");
    add_name( ({"signature_book", "book"}) );
    add_adj( ({ "signature", "black" }) );
    set_short("black signature book");    
    set_long("This is the signature book that Nikolon has given you to "
           + "help him with his census. You can use it to <request> "
           + "signatures from people you have met. You can <read> it "
           + "to see which signatures you have collected. When you are "
           + "done collecting, you can <return> the book to Nikolon. "
           + "If for any reason you wish to be rid of the book, simply "
           + "drop it.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, "No one would want to buy this item.\n"); 
    add_prop(OBJ_M_NO_GIVE, "Why would you give this book away? You "
    	+ "should <return> it to Nikolon.\n");
    // Default book weight/volume/value taken from /doc/examples/book.c
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 254);
    add_prop(OBJ_I_VALUE, 678);
    
    set_keep(1);
    
    // Initialize the variables
    signees = ({ });
} // create_object


/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();    
    
    if (IS_PLAYER_OBJECT(environment(this_object())))
    {
        owner_name = environment(this_object())->query_real_name();      
    }
    add_action(read_cmd, "read");
    add_action(request_cmd, "request");
    add_action(sign_cmd, "sign");
    add_action(return_cmd, "return");
} // init

/* Function name:       sign_cmd
 * Description  :       Responds to the player trying to sign their
 *                      own book.
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
sign_cmd(string arg)
{
    object signing_book;
    
    signing_book = PARSE_COMMAND_ONE(arg, this_player(), "[the] %i");
    if (signing_book
        && MASTER_OB(signing_book) == (LIBRARY_OBJ_DIR + "signature_book"))
    {
        // Tell the player that it's rather silly to be signing your own
        // book.
        write("You take out the black signature book and open it up to "
            + "a blank page to sign your name. Then you realize that it "
            + "is actually quite a silly thing to do, and you put the "
            + "book away again.\n");
        return 1;
    }
    
    notify_fail("Sign what?\n");
    return 0;
}

/* Function name:       read_cmd
 * Description  :       You can use this to read the signatures that
 *                      you have collected so far.
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
read_cmd(string arg)
{
    int num_names;
    object signing_book;
    
    if (strlen(arg))
    {
        arg = lower_case(arg);
    }
    signing_book = PARSE_COMMAND_ONE(arg, this_player(), "[the] %i");
    if (signing_book
        && MASTER_OB(signing_book) == (LIBRARY_OBJ_DIR + "signature_book"))
    {
        num_names = sizeof(signees);
        switch (num_names)
        {
        case 0:
            write("You currently have no signatures in your book. You "
                + "need to collect " + SIGNATURE_LIMIT + " more "
                 + "signatures.\n");
            return 1;
            break;
        
        case 1:
            write("You have collected 1 signature in your book so far "
                + "from people in the Donut. You need to collect "
                + (SIGNATURE_LIMIT - 1) + " more signatures for Nikolon: "
                + "\n\n");
            break;
        
        default:
            write("You have collected " + sprintf("%d", num_names)
                + " signatures so far from people in the Donut. You "
                + "need to collect " 
                + sprintf("%d", num_names < SIGNATURE_LIMIT 
                                ? SIGNATURE_LIMIT - num_names : 0)
                + " more signatures for Nikolon:\n\n");
        }
        foreach (string player : sort_array(signees))
        {
            write(capitalize(player) + "\n");
        }
        return 1;
    }

    notify_fail("Read what?\n");
    return 0;
}

/* Function name:       return_cmd
 * Description  :       You use this command to return the book
 *                      to Nikolon
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
return_cmd(string arg)
{
    int num_names;
    object signing_book;
    object nikolon;
    nikolon = find_living("nikolon");
    
    if (strlen(arg))
    {
        arg = lower_case(arg);
    }
    signing_book = PARSE_COMMAND_ONE(arg, this_player(), "[the] %i [to] [nikolon]");
    if (signing_book
        && MASTER_OB(signing_book) == (LIBRARY_OBJ_DIR + "signature_book")
        && nikolon
        && environment(nikolon) == environment(this_player()))
    {
        if (!CAN_SEE_IN_ROOM(nikolon))
        {
            nikolon->command("$say Who's there? I can't see a thing!\n");
            return 1;
        }
        
        if (!CAN_SEE(nikolon, this_player()))
        {
            nikolon->command("$say Who's there? I can't see who's trying "
                           + "to get my attention.");
            return 1;
        }
        
        num_names = sizeof(signees);
        if (num_names < SIGNATURE_LIMIT)
        {
            nikolon->say_to_player("You have not yet collected the 20 "
                           + "signatures yet. Return the book to me "
                           + "when you have collected them all.",
                             this_player());
            nikolon->say_to_player("If you want to get rid of the book, "
                                 + "simply drop it.", this_player());
            return 1;
        }
        // The user has the required number of signatures
        nikolon->reward_player_sign_quest(this_player());
        set_alarm(3.0, 0.0, &remove_signature_book());
        return 1;
    }
    notify_fail("Return what?\n");
    return 0;
}
/* Function name:       request_cmd
 * Description  :       This command is used to request signatures from
 *                      people around you. You can only collect signatures
 *                      from people who have introduced themselves, and
 *                      people who are at least 10 days old.
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
request_cmd(string arg)
{
    object target;
    object hidden_object;
    int heartbeats;
    
    if (strlen(arg))
    {
        arg = lower_case(arg);
    }
    target = PARSE_COMMAND_ONE(arg, 0, "[signature] [from] %i");
    if (target)
    {
        if (!IS_PLAYER_OBJECT(target))
        {
            notify_fail("You can only request signatures from other "
                      + "players.\n");
            return 0;
        }
        
        if (target->query_wiz_level())
        {
            notify_fail("Do not skew the census data with requests to Wizards. "
                + "They are not travellers of the Donut, they are its "
                + "Stewards!\n");
            return 0;
        }
            
        // After the user has collected the limit, don't allow any more
        // to be collected.
        if (sizeof(signees) >= SIGNATURE_LIMIT)
        {
            notify_fail("You have already collected the "
                      + sprintf("%d", SIGNATURE_LIMIT) + " signatures "
                      + "that Nikolon requested. Return the book to him "
                      + "for a reward.\n");
            return 0;
        }
        
        if (this_player()->notmet_me(target))
        {
            notify_fail("You should introduce yourself to " 
                      + target->query_the_name(this_player()) 
                      + " before asking " + target->query_objective() 
                      + " to sign your book.\n");
            return 0;
        }
        
        if (target->notmet_me(this_player()))
        {
	    arg = target->query_objective();
            notify_fail(target->query_The_name(this_player()) + " has not "
                      + "introduced " + arg + "self "
                      + "to you yet. Perhaps you should ask "
                      + target->query_objective() + " to do so "
                      + "before requesting a signature from " +
		      arg + "?\n");
            return 0;
        }
        
        // Both players know each other. Now, we can compare to see whether
        // the other player has sufficient age.
        // 10 days == 10 * 3600 * 24 / 2 heartbeats  = 432000
        // (1 heartbeat == 2 seconds)
        heartbeats = target->query_age();
        if (heartbeats < 216000)
        {
            notify_fail(target->query_The_name(this_player()) + " is not "
                      + "yet old enough to be counted as a part of "
                      + "Nikolon's census.\n");
            return 0;
        }
        
        // We check to see if this player is already in the signature book
        // I purposely put this below all the other checks so that people
        // cannot use this book to figure out people's identities
        if (IN_ARRAY(target->query_name(), signees))
        {
            notify_fail(target->query_The_name(this_player()) + " has "
                      + "already signed your book!\n");
            return 0;
        }
     
        if (present("hidden_signature_obj", target))
        {
            notify_fail(target->query_The_name(this_player()) + " has "
                      + "already been asked to sign a book. Wait a bit "
                      + "before asking again.\n");
            return 0;
        }
        
        setuid();
        seteuid(getuid());
        
        // We clone the hidden signature object and pass it over to the
        // target person to sign.
        hidden_object = clone_object(LIBRARY_OBJ_DIR + "signature_object");
        hidden_object->set_owner(this_player(), this_object());
        hidden_object->move(target, 1);
        write("You carefully open your black signature book to a blank "
            + "page and ask " + target->query_the_name(this_player())
            + " to sign your black signature book.\n");
        target->catch_tell(this_player()->query_The_name(target)
            + " opens up " + this_player()->query_possessive() + " black "
            + "signature book and asks you to sign it for "
            + this_player()->query_objective() + ". You can <sign book> "
            + "to write your name into the book.\n");
        say(QCTNAME(this_player())
            + " opens up " + this_player()->query_possessive() + " black "
            + "signature book and asks " + QTNAME(target) + " to sign "
            + "it.\n", ({ this_player(), target }));
        return 1;
    }
    
    notify_fail("Request signature from whom?\n");
    return 0;
}

/* Function name:       add_signature
 * Description  :       This just adds the player object to the list
 *                      of people who have signed the book
 * Arguments    :       player - the player signing the book
 * Returns      :       nothing
 */
public void
add_signature(object player)
{
    if (!IN_ARRAY(player->query_name(), signees))
    {
        signees += ({ player->query_name() });
        save_object(LIBRARY_QUEST_DIR + owner_name);
        if (sizeof(signees) == SIGNATURE_LIMIT)
        {
            environment(this_object())->catch_tell("You have now "
                      + "collected all the signatures that Nikolon needs. "
                      + "Return it to him for your reward.\n");
        }
    }
}

/*
 * Function name: query_auto_load
 * Description  : Returns the path to the master of this module. It will
 *                only autoload to wizards.
 * Returns      : string - the path.
 */
string
query_auto_load()
{
    return LIBRARY_OBJ_DIR + "signature_book:" + owner_name;
}


/* 
 * Function name: init_arg
 * Description  : Called when autoloading. It will set the type of coins
 *                and the number of coins in the heap.
 * Arguments    : string arg - the auto-load argument.
 */
public void
init_arg(string arg)
{
    if (file_size(LIBRARY_QUEST_DIR + arg + ".o") > 0)
    {
        setuid();
        seteuid(getuid());
        
        restore_object(LIBRARY_QUEST_DIR + arg);
    }
}

public void
remove_signature_book()
{
    remove_object();
}

public void
remove_signature_book_from_room(object room)
{
    remove_object();
    tell_room(room, "The black signature book magically disappears.\n");
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
public void 
enter_env(object to, object from)
{    
    if (IS_ROOM_OBJECT(to))
    {
        set_alarm(2.0, 0.0, &remove_signature_book_from_room(to));      
        this_object()->add_prop(OBJ_M_NO_GET, 1);
    }
    
    ::enter_env(to, from);    
}

