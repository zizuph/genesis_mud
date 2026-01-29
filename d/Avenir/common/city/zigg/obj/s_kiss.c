// blind_obj ("s_kiss.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Kiss object for Salilus' portal
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"salilus::kiss"}));

}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    set_alarm(30.0, 0.0 , &remove_object());
}
