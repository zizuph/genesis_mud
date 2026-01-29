/*
 * A Wedding Plaque (I hope)
 *
 * Idea and descriptions by Digit
 *
 * Auto_load stuff added by Napture
 *
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

string owner, spouse, date, message;
/* NB: `owner` is the *owner* of this plaque!  Not necessarily
 *     is owner female, or spouse, male...
 */
#define EDIT_OBJECT "/std/edit"

void
create_object()
{
   set_name("wedding plaque");
    add_name("wedplaque");
   set_adj("small");
   set_long("A small plaque.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL,
        "You decide not to sell your valued wedding plaque.\n");
  /* Don't want to add NO_GIVE or NO_DROP! */

}

init()
{
    ::init();
    if (environment(this_object()) == this_player() &&
          SECURITY->query_wiz_rank(this_player()->query_name()) != 0)  {
        add_action("set_info", "wedinfo");
    }
}
        
query_auto_load()
{
    return MASTER + ":" +
            owner + "++" + spouse + "++" + date + "++" + message;
}

init_arg(string arg)
{
    if (sscanf(arg, "%s++%s++%s++%s", owner, spouse, date, message) != 4)  {
        set_alarm(6.0, 0.0, "arg_error");
    }
    new_long();
}

arg_error()
{
    this_player()->catch_msg("Your wedding plaque seems to have faded!\n");
  /* Probably want more than this simple message here */
}

enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!owner)  return;
    
    if (dest != find_player(owner))
        set_alarm(120.0, 0.0, "move_to_owner");
}

move_to_owner()
{
    object env, to;
    string txt;

    if (!owner)  return;
    
    env = environment(this_object());
    to = find_player(owner);
    txt = "The wedding plaque suddenly disappears!\n";

    if (living(env))
        env->catch_msg(txt);
    else
        tell_room(env, txt);

    if (!to)
        remove_object();

    move(to);
    to->catch_msg("Your wedding plaque suddenly appears!\n");
}            

new_long()
{
   set_long("The small plaque reads:\n"+
            "\n"+
            " To Commemorate the Wedding on "+date+" of \n"+
            "    "+capitalize(owner)+" & "+capitalize(spouse)+"\n\n"+
            message + "\n");
}

copy_plaque()
{
    object p;
    
    setuid();
    seteuid(getuid());

    if (!this_player())  return;
    if (environment(this_object()) != this_player())  return;

    p = clone_object(MASTER);
    p->move(this_player());

    p->set_info_other(spouse, owner, message);
    this_player()->catch_msg("A duplicate appears in your hands!\n");
}    

/* Called when duplicating a plaque */
/* The owner/spouse names will be swapped! */
set_info_other(string s1, string s2, string s3)
{
    owner = s1;
    spouse = s2;
    message = s3;
    date = ctime(time())[0..9];
    new_long();
}
        

usage()
{
    notify_fail("Usage: wedinfo <owner name> <spouse_name>\n" +
        "Then you will be prompted for a message.\n" +
        "The date will be added as for today's date.\n");
}

string s1, s2, tmes, tdate;  /* Some temp strings to fix problem with edit() */
int male;  /* Is s1 or s2 the spouse? */
  /* This is needed, so a plaque can still be generated, even if
   * one of the players logs out during the edit() phase!
   * Doesn't actually matter if owner or bride male...
   */
   
set_info(string arg)
{
    if (!arg) {
        usage();
        return 0;
    }
    
    if (environment(this_object()) != this_player())  {
        notify_fail("You have to be holding the plaque to change it!\n");
        return 0;
    }

    if (owner && spouse)  {
        notify_fail(VBFC_ME("already_set"));
        return 0;
    }

    tdate = ctime(time())[0..9];

    if (sscanf(arg, "%s %s %s", s1, s2, tmes) != 3)  {
        if (sscanf(arg, "%s %s", s1, s2) != 2)  {
            usage();
            return 0;
        }
    }

    s1 = lower_case(s1);
    s2 = lower_case(s2);
    if (!find_player(s1))  {
        write("Failed to find "+capitalize(s1)+
              " - they have to be logged in!\n");
        return 1;
    }
    if (!find_player(s2))  {
        write("Failed to find "+capitalize(s2)+
              " - they have to be logged in!\n");
        return 1;
    }

  /* If this is changed to be a comemorative plaque rather than just
   * a wedding plaque, then this bit is not needed...it may not be
   * needed depending on how you feel either!
   * Eg, though single sex 'marriages' may not be allowed, this plaque
   * could be given instead!
   */
    if (find_player(s1)->query_gender()==find_player(s2)->query_gender())  {
        write("Sorry, only heterosexual mariages currently allowed!\n");
        return 1;
    }

    if (find_player(s1)->query_gender() == G_MALE)
        male = 1;
    else
        male = 2;
        
  /* 3 args given, so don't prompt for message */
    if (tmes)  {
        if (male == 1)  {
            spouse = s1;
            owner = s2;
        }
        else  {
            spouse = s2;
            owner = s1;
        }
        message = tmes;
        date = tdate;
        new_long();
        write("Plaque info set.\n");
        copy_plaque();
        return 1;
    }
        
    setuid();
    seteuid(getuid());
    clone_object(EDIT_OBJECT)->edit("finished_edit");

    return 1;
}
    
finished_edit(string edstr)
{
    if (!edstr)  {
        write("Message aborted, plaque not set!\n");
        return;
    }
    message = edstr;
    date = tdate;
    if (male == 1)  {
        spouse = s1;
        owner = s2;
    }
    else  {
        spouse = s2;
        owner = s1;
    }
    new_long();
    write("Plaque info set.\n");
    copy_plaque();
    return;
}
        
already_set()
{
    new_long();
    return "Owner and Spouse names already set!\n";
}    
