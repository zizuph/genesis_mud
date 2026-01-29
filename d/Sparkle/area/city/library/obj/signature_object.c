/*
 * /w/petros/sparkle/library/obj/signature_object.c
 *
 * When a user requests a signature from someone, this object
 * gets transferred to the other's inventory to give them the
 * necessary commands.
 *
 * Created April 2008, by Petros
 */
 
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include "defs.h"

// Defines

// Global Variables
object      owner;
object      signature_book;
int         already_signed;

// Prototypes
public void             create_object();
public int              sign_cmd(string arg);
public void             time_out_signing();
public void             set_owner(object player, object book);

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    set_name("_hidden_signature_obj");
    add_name( ({"hidden_signature_obj" }) );
    set_short("hidden signature object");    
    set_long("Players should not be able to see this hidden signature "
           + "object.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 
    
    set_no_show();
    
    already_signed = 0;
} // create_object


/* Function name:       init
 * Description  :       adds the action
 */
public void
init()
{
    ::init();    
    
    add_action(sign_cmd, "sign");
    set_alarm(10.0, 0.0, &time_out_signing());
} // init

/* Function name:       set_owner_name
 * Description  :       Sets up the owner_name so that we can look
 *                      up the person who we are signing this for.
 * Arguments    :       player - player who owns the signature book
 *                      book - pointer to signature book
 * Returns      :       nothing
 */
public void
set_owner(object player, object book)
{
    owner = player;
    signature_book = book;
}

/* Function name:       sign_cmd
 * Description  :       When a player signs the signature book, this
 *                      function gets called to handle the data
 * Arguments    :       arg - parameters
 * Returns      :       0/1 - whether command was successful.
 */
public int
sign_cmd(string arg)
{
    if (already_signed)
    {
        // If someone has already signed, simply return.
        return 0;
    }
    
    switch (arg)
    {
    case "book":
    case "signature book":
    case "black signature book":    
        break;
    default:
        notify_fail("Sign signature book?\n");
        return 0;
    }
    
    if (environment(owner) != environment(this_player()))
    {
        notify_fail("You attempt to sign " 
                  + owner->query_the_possessive_name(this_player()) 
                  + " signature book, but " + owner->query_pronoun() 
                  + " seems to have disappeared.\n");
        return 0;
    }
    
    signature_book->add_signature(this_player());
    // Set the flag so that they can't sign again.
    already_signed = 1;
        
    write("You scrawl your signature onto " 
        + owner->query_the_possessive_name(this_player()) 
        + " black signature book.\n");
    owner->catch_tell(this_player()->query_met_name() + " adds " 
      + this_player()->query_possessive() + " signature to "
      + "your black signature book.\n");
    say(QCTNAME(this_player()) + " adds " 
      + this_player()->query_possessive() + " signature to "
      + QTPNAME(owner) + " black signature book.\n",
        ({ this_player(), owner }) );
          
    return 1;
}

public void
time_out_signing()
{
    object player;
    
    player = environment(this_object());
    if (!already_signed)
    {
        player->catch_tell("You decide to pass on the opportunity to sign "
            + owner->query_the_possessive_name(player)
            + " black signature book.\n");
        owner->catch_tell(player->query_met_name() + " did not "
                        + "sign the black signature book. You close "
                        + "the book and put it away.\n");
        say(QCTNAME(player) + " did not agree to sign the black "
          + "signature book. " + QCTNAME(owner) + " closes the book and "
          + "puts it away for now.\n",
            ({ player, owner }) );    
    }
    remove_object();
}
