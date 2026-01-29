/* 
 *  A lib which you can inherit into rooms so that you can change
 *  the non obvious exit messages.
 *
 *  Created by Igneous, thanks go to Gnadnar of Gondor who I basically
 *  borrowed the idea from :)
 *
 * How to use this file with your room.
 *
 * inherit "/d/Shire/std/room";
 *
 * void
 * create_shire_room()
 * {
 *     set_short("long sandy shoreline");
 *     set_long("You are standing on a beach along the shore of a majestic "+
 *       "lake. To the east is the lake and to your west stands and large "+
 *       "dense forest and a pile of rocks sits to the south.\n");
 *     add_exit("somewhere_else", "north", 0, 1);
 *     // Now we want to alter some of the no_exit messages here :-)
 *     set_no_exit_msg(({"northeast","east","southeast"}), 
 *       "You way is blocked by the waters of the lake.");
 *     set_no_exit_msg(({"northwest","west","southwest"}),
 *       "You are unable to make your way into the forest.");
 *     set_no_exit_msg("south", "A large pile of rocks makes "+
 *       "going south impossble.");
 * }
 *
 */

static mapping gNo_exit_msg = ([]);

/* Function name:  set_no_exit_msg
 * Description:    This function is used in your create_* function for your
 *                 room to set up alternate messages for when a player attempts
 *                 to go in a non-existant direction.
 * Arguments:      mixed dirs:  The directions we want to set the non-standard
 *                              message for.
 *                 string msg:  The message we want to print when a player goes
 *                              in one fo the dirs have it set for.
 * Returns:        0
 */
public void
set_no_exit_msg(mixed dirs, string msg)
{
    int i;

    if (!pointerp(dirs))
    {
	if (dirs == "all")
	{
	    dirs = ({"north", "northeast", "east", "southeast", "south",
	      "southwest", "west", "northwest", "up", "down"});
	}
	else
	    dirs = ({dirs});
    }
    i = -1;
    while (++i < sizeof(dirs))
	gNo_exit_msg[dirs[i]] = msg;

}

/* Function name:  unq_no_move (MASKED)
 * Description:    This function prints out the message when a player
 *                 attempts to use a non-existant exit.
 * Arguments:      string str:  The direction the player tried to go.
 * Returns:        A failure message and 0
 */
public int
unq_no_move(string str)
{
    string vb = query_verb();

    if (gNo_exit_msg[vb])
	notify_fail(gNo_exit_msg[vb] + "\n");
    else
	notify_fail("There is no obvious exit "+ vb +".\n");

    return 0;
}
