/* Trollshaws master
 *
 * Used to make trolls that are outside during the day run back inside so they
 * don't turn into stone ;-)
 */

object *Trolls = ({});

void
add_troll(object troll)
{
    Trolls += ({troll});
}

void
remove_troll(object troll)
{
    Trolls -= ({Trolls});
}

void
sunrise()
{
    if (!sizeof(Trolls))
	return;

    Trolls->sunrise();
}

void
sunset()
{
    if (!sizeof(Trolls))
	return;

    Trolls->sunset();
}
