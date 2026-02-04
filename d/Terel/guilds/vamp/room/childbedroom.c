/*
 * Child's Bedroom in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define ON_BED "_on_bed"
//proto
int do_lie(string str);
int do_stand(string str);
mixed filter_the_blind(object ob);

void
create_vamp_room()
{
    set_short("small bedroom");
    set_long("This is a small bedroom, apparently for a child.  "+
        "The walls are covered in small drawings of animals such "+
        "as horses and dogs.  "  +
        "The bed is bare and the supporting wood at the base has "+
        "been cracked and broken.  "+
        "There is still a large ornate post at each corner that "+
        "once supported a canopy, probably of silk or velvet.  "+
        "There is a closet to the north.  "+
        "\n");

    add_exit("upperhall1.c", "southeast");
    add_exit("childcloset.c","north");

    add_item(({"north","closet"}),
        "To the north is the closet.\n");

    add_item(({"southeast","hall","hallway"}),
        "To the southeast is the hallway.\n");

    add_item(({"wall","walls","drawings","animals","dogs",
        "horses","bears","small drawings","dancing bears"}),
        "The walls are decorated with drawings of animals.  "+
        "A quick scan reveals many horses in various stages "+
        "of running, various herding and hunting dogs, "+
        "an even a few bears who appear to be dancing.\n");

    add_item(({"bed"}),
        "The bed is devoid of any covering, and appears useless "+
        "due to the base being cracked neatly in two.  "+
        "Four ornate posts once supported a canopy of some sort "+
        "around the bed.\n");

    add_item(({"base","bed base","crack","broken base",
        "cracked base"}),
        "The base of the bed is cracked neatly in two, causing the "+
        "entire bed to fold in on itself.\n");

    add_item(({"posts","ornate posts","four posts","four ornate posts",
        "canopy" }),
        "The four ornate posts around the bed are carved with the same "+
        "depictions of animals that decorate the walls.  "+
        "There are many horses, various types of dogs, and occasionally "+
        "a dancing bear.  "+
        "The posts were once used to hold a canopy of silk or velvet "+
        "around the bed, but the material has long since been removed, "+
        "leaving only the posts.\n");

}

void
init() {
    ::init();
    add_action(do_lie, "lie");
    add_action(do_lie, "lay");
    add_action(do_stand, "stand");
}

int do_lie(string str)
{
    if (!strlen(str)) {
        notify_fail("Lie down on the bed?\n");
        return 0;
    }

    if (str != "on bed"
        && str !="on the bed"
        && str !="bed"
        && str != "down on the bed"
        && str != "down on bed") 
    {
        notify_fail("Lie down on the bed?\n");
        return 0;
    }

    object tp = this_player();
    if (tp->query_prop(ON_BED))
    {
        notify_fail("You are already lying on the bed.\n");
        return 0;
    }

    tp->catch_msg("You lie down on the bed.\n");
    tell_room(this_object(),QCTNAME(tp)+" lies down on the bed.\n",
    filter_the_blind(tp), tp);

    tp->add_prop(ON_BED, 1);
    tp->add_prop(LIVE_S_EXTRA_SHORT," lying on the bed");
      
    return 1;
}

int 
do_stand(string str)
{
    if (strlen(str && str != "up"))
    {
        notify_fail("Stand up?\n");
        return 0;
    }

    object tp = this_player();

    if (tp->query_prop(ON_BED)) {
        tp->catch_msg("You get up from the bed.\n");
        tell_room(this_object(),QCTNAME(tp)+" gets up from the bed.\n",
        filter_the_blind(tp), tp);
        tp->remove_prop(ON_BED);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
    } else {
        notify_fail("You are not lying on the bed.\n");
        return 0;
    }

    return 1;
}


void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);    
    
    if(!objectp(to) || !objectp(ob))
            return;
            
    if (!interactive(ob))
        return;

    if (ob->query_prop(ON_BED)) {
        ob->catch_msg("You get up from the bed.\n");
        ob->remove_prop(ON_BED);
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
    } 
}

mixed
filter_the_blind(object ob) {
    mixed all = all_inventory(this_object());
    mixed result = ({ ob });
    
    if (!all || !sizeof(all)) {
        return result;
    }

    mixed peeps = FILTER_LIVE(all);
    int i;
    if (!peeps || !(i = sizeof(peeps))) {
        return result;
    }

    while (i--) {
        if (!CAN_SEE_IN_ROOM(peeps[i]) || !CAN_SEE(peeps[i], ob)) {
            result += ({ peeps[i] });
        }
    }

    return result;

}

