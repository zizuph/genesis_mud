/* 
 * /d/Ansalon/guild/society/obj/nametag.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Kender nametags that allow title changes 
 * Gwyneth, June 1999 
 */
inherit "/std/object";

#include <stdproperties.h>

string owner = "";

void
create_object()
{
    set_name("nametag");
    add_name("_kender_name_tag");
    add_name("tag");
    set_adj("blank");
    add_adj("name");
    set_short("blank nametag");
    set_pshort("blank nametags");
    set_long("This nametag allows you to change your title.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
}

void
set_owner(object who)
{
    owner = who->query_real_name();
}

string
query_owner()
{
    return owner;
}

void
give_message(object room)
{
    tell_room(room, "The " + short() + " gets caught " +
        "in a gust of wind and blows away.\n");
}

public void
remove_nametag()
{
    this_object()->remove_object();
}

void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if((!inv->query_wiz_level()
      && inv->query_real_name() != owner && 
      living(inv)) ||
      inv->query_prop(ROOM_I_IS))
    {
        set_alarm(0.1, 0.0, &give_message(inv));
        set_alarm(0.2, 0.0, &remove_nametag());
    }
}



