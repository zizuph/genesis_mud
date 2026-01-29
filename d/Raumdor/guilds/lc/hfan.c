#pragma strict_types
#include "/d/Raumdor/defs.h"
#include <macros.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/d/Raumdor/lib/commands";
inherit "/lib/holdable_item";

void
create_object()
{
    set_name("fan");
    set_adj( ({"elegant","folding"}));
    set_short("elegant folding hand-fan");
    add_name("hand-fan");

    set_long("This is a small folding hand-sized fan. It "+
    "has a polished ebony wood handle, and silk-cream colored fan "+
    "paper that spreads out to reveal a snarling golden dragon.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 8);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
}

int
emote_fslap(string arg)
{
    object *oblist;
    if(!arg)
        return 0;

    oblist = PARSE_THIS(arg, "[at] [the] %i");
    if(!sizeof(oblist))
        return 0;

    actor("You slap the "+short()+" across", oblist, " face, and "+
      "shout, \"Why, I never!\"",1);


    all2act(" slaps "+HIS(TP)+" "+short()+" across", oblist, " face, "+
    "and shouts, \"Why, I never!\"", "", 0, 1, 0);

    target(" slaps "+HIS(TP)+" "+short()+" across your face, and "+
      "shouts, \"Why, I never!\"", oblist, "", ACTION_CONTACT | ACTION_OFFENSIVE);

    return 1;
}

int
emote_frap(string arg)
{
    object *oblist;
    if(!arg)
        return 0;

    oblist = PARSE_THIS(arg, "[at] [the] %i");
    if(!sizeof(oblist))
        return 0;

    actor("You rap your "+short()+" across", oblist, " knuckles, and "+
    "sternly warn, \"Mind your manners!\"", 1);
    all2act(" raps "+HIS(TP)+" "+short()+" across", oblist, " knuckles, "+
    "and sternly warns, \"Mind your manners!\"", "", 0, 1, 0);

    target(" raps "+HIS(TP)+" "+short()+" across your knuckles, and "+
    "sternly warns, \"Mind your manners!\"", oblist, "", ACTION_CONTACT);

    return 1;
}


void
init()
{
    ::init();
    add_action(emote_fslap, "fslap");
    add_action(emote_frap, "frap");
}
