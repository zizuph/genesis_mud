/*
 * Master Bedroom in the vampire manor
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
int do_drink(string str);
int do_stand(string str);
mixed filter_the_blind(object ob);

void
create_vamp_room()
{
    set_short("master bedroom");
    set_long("This is the master bedroom of the manor.  "+
        "The room is dominated by a large bed with a massive wooden "+
        "headboard.  "+
        "To the right of the bed is a large cabinet, while to the "+
        "left of the bed is a water basin.  "+
        "\n");

    add_exit("upperhall1.c", "east");

    add_item(({"east","hall","hallway"}),
        "To the east is the hallway.\n");

    add_item(({"bed","large bed"}),
        "The bed is extremely large and plush, and appears very "+
        "comfortable.\n");

    add_item(({"headboard","massive headboard","wooden headboard",
        "massive wooden headboard"}),
        "The headboard is slightly circular, while at each end twin heads of "+
        "two serpents curl upward and inward, facing toward each other.\n");

    add_item(({"serpents","twin serpents","twin heads","serpent heads",
        "heads"}),
        "The twin heads of the serpents face each other over the "+
        "headboard of the bed.  \n");

    add_item(({"cabinet","large cabinet","shell","empty shell",
        "shelves","empty shelves","doors"}),
        "The cabinet is large and wooden, with feet carved into the shape "+
        "of eagle talons.  "+
        "The doors have been broken off, and the shelves inside destroyed.  "+
        "All the remains is the empty shell.\n");

    add_item(({"feet","talons","eagle talons","eagle feet"}),
        "The feet of the destroyed cabinet are carved into the shape "+
        "of eagle talons.\n");

    add_item(({"basin","water basin","blood"}),
        "The water basin is full of blood.\n");
}

void
init() {
    ::init();
    add_action(do_drink, "drink");
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
        && str != "in bed"
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


int do_drink(string str)
{
    if (!strlen(str))
    {
        notify_fail("Drink from the basin?\n");
        return 0;
    }

    if (str != "from the basin"
        && str != "from basin"
        && str != "basin"
        && str != "blood"
        && str != "blood from basin"
        && str != "blood from the basin"
        && str != "the blood"
        && str != "the blood from the basin")
    {
        notify_fail("Drink from the basin?\n");
        return 0;
    }

    object tp = this_player();

    write("You dip your hand into the cold blood pooled in the "+
        "water basin and raise it to your lips,  "+
        "feeling the thick film of the blood slipping between "+
        "your fingers.  When your hand reaches your mouth, "+
        "you realize it is completely clean - the blood on it "+
        "has disappeared.\n");

    tell_room(this_object(),
        QCTNAME(tp)+" puts "+tp->query_possessive()+" hand "+
        "into the water basin and pulls it out, cupping it as "+
        "if scooping water out.  You notice "+
        tp->query_possessive()+" hand is empty.\n",
        filter_the_blind(tp), tp);

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
