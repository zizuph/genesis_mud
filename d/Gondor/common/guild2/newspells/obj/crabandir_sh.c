/*
 *  /d/Gondor/common/guild2/newspells/crabandir_sh.c
 *
 *  A support for the Morgul crabandir spell.
 */

inherit "/std/shadow";

#include <files.h>

private nomask varargs int pass_msg( object from_player );

object puppet;

public void
attacked_by( object ob )
{
    shadow_who->catch_tell( "Sudden pain violently breaks your "+
        "concentration!\n" );
    shadow_who->attacked_by( ob );
    puppet->remove_craban();
}

void catch_msg( mixed str, object from_player )
{
    if (pass_msg( from_player ))
    {
        shadow_who->catch_msg( str, from_player );
    }
}

public void catch_tell( string msg )
{
    if (pass_msg())
    {
        shadow_who->catch_tell( msg );
    }
}

void set_puppet( object ob )
{
    puppet = ob;
}

/*
 * Function     : pass_msg
 * Description  : It checks whether to pass a message to a mage or not.
 *              : At the moment it passes messages from the invoked craban,
 *              : messages sent by palanquendo and wizards 
 */
private nomask varargs int pass_msg( object from_player )
{
 object T1;
 string T2;

/*
T1 = calling_object( 0 );
if (objectp(T1))
{
	find_player("chmee")->catch_tell("calling_object( 0 ): "+
		file_name( T1 )+ "\n");
}
T1 = calling_object( -1 );
if (objectp(T1))
{
	find_player("chmee")->catch_tell("calling_object( -1 ): "+
		file_name( T1 )+ "\n");
}
T1 = calling_object( -2 );
if (objectp(T1))
{
	find_player("chmee")->catch_tell("calling_object( -2 ): "+
		file_name( T1 )+ "\n");
}
T1 = calling_object( -3 );
if (objectp(T1))
{
	find_player("chmee")->catch_tell("calling_object( -3 ): "+
		file_name( T1 )+ "\n\n");
}

T2 = calling_program( 0 );
if (strlen( T2 ))
{
	find_player("chmee")->catch_tell("calling_program( 0 ): "+ T2+ "\n");
}
T2 = calling_program( -1 );
if (strlen( T2 ))
{
	find_player("chmee")->catch_tell("calling_program( -1 ): "+ T2+ "\n");
}
T2 = calling_program( -2 );
if (strlen( T2 ))
{
	find_player("chmee")->catch_tell("calling_program( -2 ): "+ T2+ "\n");
}
T2 = calling_program( -3 );
if (strlen( T2 ))
{
	find_player("chmee")->catch_tell("calling_program( -3 ): "+ T2+ "\n");
}

if (objectp( from_player ))
{
	find_player("chmee")->catch_tell(from_player->query_name()+ "\n");
}
*/

                                /*A message sent by a wizard.             */
    if (objectp( from_player ))
    {
        if (SECURITY->query_wiz_level( from_player->query_name() ))
        {
            return 1;
        }
    }
                                /*A craban is the source of message.      */
    T1 = calling_object( -1 );
    if (objectp( T1 ))
    {
        if (T1 == puppet)
        {
            return 1;
        }
    }
    T1 = calling_object( -2 );
    if (objectp( T1 ))
    {
        if (T1 == puppet)
        {
            return 1;
        }
    }
                                /*Message sent by palanquendo or paralyze.*/
    T2 = calling_program( -1 );
    if (strlen( T2 ))
    {
        if ((T2 == "d/Gondor/common/guild2/newspells/palanquendo.c" ) ||
			(T2 == "std/paralyze.c"))
        {
            return 1;
        }
    }
    return 0;
}

