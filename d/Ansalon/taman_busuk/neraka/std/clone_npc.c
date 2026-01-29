/* This is included in the base rooms */

varargs object
clone_npc(string file, mixed colour, int do_not_arm)
{
    object ob;

    if (!stringp(file) || (file == ""))
        return 0;

    ob = clone_object(file);
    if (!objectp(ob))
        return 0;

    if (stringp(colour) && function_exists("set_colour",ob))
        ob->set_colour(colour);

    if (!do_not_arm && function_exists("arm_me",ob))
        ob->arm_me();

    ob->move_living("xxx",this_object());

    return ob;
}
