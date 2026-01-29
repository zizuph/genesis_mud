/*
hilt.c
-----

Coded by Arman Kharas 19 May 2003


*/

inherit "/std/object";
inherit "/lib/holdable_item"; 
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"



void
create_object()
{
   set_name("hilt");
   add_name("_mishakal_blade_hilt");
   set_adj("blue-steel");
   set_short("blue-steel hilt");
   set_long("This is all that remains of a sword of some kind, an elaborate "+
    "hilt made of blue-steel. It looks ancient, although doesn't seem to have "+
    "been affected by time at all. You notice some runes enscribed along the "+
    "guard.\n");

    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This was once a holy blade wielded by a disciple of the old " +
        "goddess, Mishakal. It now is missing its blade, useless as " +
        "a weapon.\n",10}));

    add_item("runes","Elvish runes run along the guard of this hilt. You could " +
      "try and read them.\n");
    add_cmd_item(({"runes","guard","hilt"}),"read",
      "@@read_writing");
   
   set_slots(W_ANYH);

   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(OBJ_I_VALUE, 0);
}

string
read_writing()
{
    if(TP->query_skill(SS_LANGUAGE) < 50 && TP->query_race() != "elf")
    return "Along the guard of the hilt are elvish runes which you are unable "+
    "to interpret.\n";
    else
    return "Along the guard of the hilt is written in elvish 'Quen Illumini'. " +
    "You notice at the beginning and end of these runes is the symbol of " +
    "infinity, two circles joined.\n";
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
 
    holdable_item_leave_env(env, to);
}