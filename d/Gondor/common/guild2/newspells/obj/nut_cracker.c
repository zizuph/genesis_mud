/*
 * File: /d/Gondor/common/guild2/newspells/obj/nut_cracker.c
 * Designed as a support for MM narusse spell.
 */

inherit "/std/object";

/*
 * Function name: crack
 * Description  : Handles delayed destruction of the desired object
 *                when it can't be done more directly.
 * Arguments    : object _ob - the object that should be destructed
 * Return values: 1 if _ob is an object 0 otherwise.
 */
int crack( object _ob )
{
    if (objectp( _ob ))
    {                           /*A delay is set so the object tying to
                                 *destruct itself had a chance to finish
                                 *its code.                               */
        set_alarm( 0.1, 0.0, (_ob->remove_object) );
        return 1;
    }
    return 0;
}
