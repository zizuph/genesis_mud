/*
 * KNIFE_SERVER.c
 * Stores location of knife.
 * THIS IS NOT TO BE CLONED!
 */

#include "/d/Emerald/defs.h"

inherit "/std/object";

int knife_loc_num;
int allow_knife;

void relocate_knife();
int query_knife_location();
void set_allow_knife(int a);
int query_allow_knife();

void reset_object();

void
create_object()
{
    set_name("knife_server");
    reset_object();
}

void
reset_object()
{
    relocate_knife();
    set_allow_knife(1);
}

void
relocate_knife()
{
    knife_loc_num = random(22)+1;
}

int
query_knife_location()
{
    return knife_loc_num;
}

void
set_allow_knife(int a)
{
    allow_knife = a;
}

int
query_allow_knife()
{
    return allow_knife;
}
