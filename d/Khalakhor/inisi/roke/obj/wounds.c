/*
 * Wounds object, to self-kill NPCs cleanly
 * Tapakah, 06/2021
 */

#pragma strict_types

inherit "/std/object";

void
suicide ()
{
  remove_object();
}

void
create_object ()
{
  set_name("wounds");
  set_short("wounds");
  set_long("wounds");
  set_alarm(10.0, 0.0, suicide);
}
