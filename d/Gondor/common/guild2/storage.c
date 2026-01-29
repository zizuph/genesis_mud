/*
 * File        : /d/Gondor/common/guild2/storage.c
 *               Idea and implementation by Chmee 11.09.2000
 * Description : These functions manage all the pending messages that should
 *               be sent to a mage who may not be in the realms.
 *               The message(s) will be delivered when the mage's shadow
 *               is loaded.
 */
inherit "/std/object.c";

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define NULL 0

mixed *Pending_messages = ({});
string *Mage_index = ({});

public int send_message( mixed mage, string message );
public int deliver_message( void );
nomask public string mtos( mixed name );

/*
 * Function name: send_message
 * Description  : Checks whether the mage mage is present in the realms
 *                and either sends him(her) a message message or stores
 *                it in the array Pending_messages.
 * Arguments    : mixed mage - name or an object pointer to a mage.
 *                string message - a message sent to a mage
 * Return values: -1 in the case of error, 0 if the message reached the
 *                recipent, 1 if the message was stored.
 */
public int send_message( mixed mage, string message )
{
 object mage_ob;
 int Index;
 
    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    }
    if (objectp( mage_ob = find_player( mage ) ))
    {
        tell_object( mage_ob, message );
        return 0;
    }
    else
    {
        setuid();
        seteuid( getuid() );
        restore_object( STORAGE );
        if ((Index = member_array( mage, Mage_index )) == -1)
        {
            Mage_index += ({ mage });
            Index = member_array( mage, Mage_index );
            Pending_messages += ({({ message })});
        }
        else
        {
		    if (member_array( message, Pending_messages[Index] )  >= 0)
			{
			    return 1;
			}
            Pending_messages[Index] += ({ message });
        }
    }
    save_object( STORAGE );
    return 1;
}

/*
 * Function name: deliver_message
 * Description  : Delivers stored messages to a mage mage when (s)he enters
 *                the realms (loads the guild shadow).
 * Return values: -1 in the case of error, 0 if the message reached the
 *                recipent, 1 if there was no messages for a mage mage.
 */
public int deliver_message( void )
{
 int Index, i, j;
 string mage;

    setuid();
    seteuid( getuid() );
    restore_object( STORAGE );
    mage = this_player()->query_real_name();

    if ((Index = member_array( mage, Mage_index )) == -1)
    {
        return 1;
    }
    j = sizeof( Pending_messages[Index] );
    for (i=0;i<j;i++)
    {
        tell_object( this_player(), Pending_messages[Index][i] );
    }
    Pending_messages -= ({ Pending_messages[Index] });
    Mage_index -= ({ mage });
    save_object( STORAGE );
    return 0;
}

/*
 * Function name: mtos
 * Description  : Makes sure that the argument name is a player's real name
 *                in lowercase.
 * Arguments    : An object pointer to a player or his(her) name.
 * Return values: A name in lowercase or NULL
 */
nomask public string mtos( mixed name )
{
    if (objectp( name ))
    {
        return name->query_real_name();
    }
    else if (stringp( name ))
    {
        return lower_case( name );
    }
    return NULL;
}

