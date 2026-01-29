/*
 * This is a standard leftover heart, but with a property set
 * for the uruk quest in Rohan. This code used to be in the
 * separate uruk corpse, but that created lots of error messages.
 *
 * Eowul, Oktober 10th, 2008
 */

inherit "/std/leftover";

void create_leftover()
{
    ::create_leftover();
}

void enter_env(object to, object from)
{
    if(objectp(to) && to->query_prop("_elfhelm_uruk_quest")) {
        this_object()->add_prop("_elfhelm_uruk_quest_leftover", 1);
    }
    ::enter_env(to, from);
}
