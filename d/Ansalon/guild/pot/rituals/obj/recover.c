/* Stralle @ Genesis 040302
 */

#pragma strict_types

inherit "/std/object";

object gObj;

void
create_object()
{
    set_short("recover object");
}

void
init_recover(string arg)
{
    object sh;
    string filename, args, tmp;
    int t, s;

    if (!strlen(arg))
        return;

    sscanf(arg, "%s:%s", filename, args);

    if (!strlen(filename))
        return;

    seteuid(getuid());

    gObj = clone_object(filename);
    gObj->init_recover(args);

    sscanf(args, "%s#ENCH#%d##%d##%s#ENCH#%s", tmp, t, s, filename, tmp);

    sh = clone_object(filename);
    if (t >= 0)
        sh->set_enchantment_duration(t);
    if (s >= 0)
        sh->set_enchantment_strength(s);
    sh->enchant(gObj);

    /* Must do this to get the proper name 'You recover blah'
     */
    set_short(gObj->short());
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if(objectp(to) && objectp(gObj))
        gObj->move(to, 1);

    set_alarm(1.0, 0.0, &remove_object());
}
