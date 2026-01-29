/*
 * Allowing containers to add objects
 *
 * Varian - Feb 2020
 *
 */

varargs void
cont_add_object(string file, int num, string mess)
{
    int i;

    object ob;

    if (num < 1)
	num = 1;

    seteuid(getuid());
    for (i = 0; i < num; i++)
    {
	ob = clone_object(file);
	if (stringp(mess))
	{
	    tell_room(this_object(), mess);
	    ob->move(this_object(), 1);
 	}
	else if (living(ob))
	    ob->move_living("xx", this_object());
	else
	    ob->move(this_object(), 1);
    }
}