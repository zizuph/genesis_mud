/*
 * Living room in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define ON_SOFA "_on_sofa"
#define IN_CHAIR "_in_chair"

//proto
int do_sit(string str);
int do_stand(string str);
mixed filter_the_blind(object ob);

void
create_room()
{
    ::create_room();    
    set_short("living room");
    set_long("This spacious room was intended to host a number of "+
        "guests.  "+
        "The walls are adorned with various paintings, while various "+
        "chairs and sofas litter the room.  "+
        "An ornate doorless archway leads to the east, to the "+
        "entry hall of the manor.  "+
        "\n");

    add_exit("entry.c", "east");

    add_item(({"hall","large hall","entry hall","large entry hall",
        "east"}),
        "To the east is the large entry hall of the manor.\n");

    add_item(({"chair","chairs","sofa","sofas","various chairs",
        "various sofas","various chairs and sofas"}),
        "The chairs and sofas look well-worn, and are used for "+
        "guests to sit in while visiting the occupants of "+
        "the manor.  "+
        "\n");

    add_item(({"archway","doorless archway","ornate archway",
        "ornate doorless archway","west"}),
        "The archway to the east is decorated with various "+
        "symbols and designs of unknown origin gilded in silver "+
        "and gold.  "+
        "It leads to "+
        "the entry hall of the manor.\n");

    add_item(({"symbols","designs","symbols and designs",
        "designs and symbols","symbol","design"}),
        "Although the symbols on the archway are too archaic "+
        "to determine the origins of, you cannot help but imagine "+
        "many of them as abstract representations of knives, "+
        "needles, or stakes.\n");

    add_item(({"walls","paintings","various paintings"}),
        "There are four portraits hanging around the room.\n");

    add_item(({"portraits","four portraits",
        "portraits hanging around the room"}),
        "There are four portraits hanging around the "+
        "room.  A portrait of a nobleman, "+
        "a portrait of a noblewoman, a portrait of a "+
        "child, and a portrait of a huntsman.\n");


    add_item(({"portrait"}),
        "Which portrait do you wish to look at?  "+
        "The portrait of a nobleman, the portrait of "+
        "a noblewoman, the portrait of a child, "+
        "or the portrait of a huntsman?\n");

    add_item(({"first portrait","nobleman","noble man",
        "portrait of a nobleman","portrait of the nobleman",
        "portrait of nobleman","the portrait of a nobleman",
        "the portrait of the nobleman"}),
        "The portrait of the nobleman shows a solemn looking "+
        "man in a black doublet.  His hair is short and grey, "+
        "and a thin moustache runs along his upper lip.  "+
        "A nameplate at the bottom of the portrait reads \"Edward\".  "+
        "\n");

    add_item(({"second portrait","noblewoman","noble woman",
        "woman","portrait of a noblewoman","portrait of the noblewoman",
        "portrait of noblewoman","the portrait of a noblewoman",
        "the portrait of the noblewoman"}),
        "The portrait of the noblewoman shows a blond lady "+
        "wearing a large red gown, seated with her hands folded "+
        "neatly in her lap.  "+
        "A necklace of thick gold surrounds her neck, and her "+
        "eyes sparkle with a deep blue colour.  "+
        "A nameplate at the bottom of the portrait reads \"Madaelin\".  "+
        "\n");

    add_item(({"third portrait","child","portrait of a child",
        "portrait of the child","the portrait of a child",
        "the portrait of the child"}),
        "The portrait of the child shows a small girl, blond "+
        "haired and blue eyed.  "+
        "She is wearing a pale lavender dress and holding a "+
        "bouquet of wild flowers.  "+
        "A nameplate at the bottom of the portrait reads \"Isabella\".  "+
        "\n");

    add_item(({"fourth portrait","huntsman","portrait of a huntsman",
        "the portrait of a huntsman","portrait of the huntsman",
        "the portrait of the huntsman"}),
        "The portrait of the huntsman shows an enormous barrel-chested "+
        "man dressed in hunting leathers.  A thick red beard hangs "+
        "down to nearly his chest, while his head is shaved.  "+
        "A nameplate at the bottom of the portrait reads \"Bear\".  "+
        "\n");
    //Paintings tell a story of former vampires, the family who
    //lived here, etc
    /*
        We know there was a father, a mother, a child, and a 
        huntsman named Bear who fought the vampire in the 
        child's bedroom and broke the bed.
    */
}

void 
init()
{    
    ::init();
    add_action(do_sit, "sit");
    add_action(do_stand, "stand");
}

int 
do_sit(string str)
{
    object tp = this_player();
    if (tp->query_prop(ON_SOFA)){
        notify_fail("You are already sitting on a sofa.\n");
        return 0;
    }

    if (tp->query_prop(IN_CHAIR)) {
        notify_fail("You are already sitting in a chair.\n");
        return 0;
    }

    switch (str) {
        case "on sofa":
        case "on a sofa":
        case "on the sofa":
        case "sofa":
            tp->catch_msg("You sit down on a sofa.\n");
            tell_room(this_object(),QCTNAME(tp)+" sits down on a sofa.\n",
            filter_the_blind(tp), tp);
            tp->add_prop(ON_SOFA, 1);
            tp->add_prop(LIVE_S_EXTRA_SHORT," sitting on a sofa");
            break;
        case "in chair":
        case "in a chair":
        case "in the chair":
        case "chair":
            tp->catch_msg("You sit down in a chair.\n");
            tell_room(this_object(),QCTNAME(tp)+" sits down in a chair.\n",
            filter_the_blind(tp), tp);
            tp->add_prop(IN_CHAIR, 1);
            tp->add_prop(LIVE_S_EXTRA_SHORT," sitting in a chair");
            break;
        default:
            notify_fail("Sit on a sofa or in a chair?\n");
            return 0;
    }

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

    if (tp->query_prop(ON_SOFA)) {
        tp->catch_msg("You stand up from the sofa.\n");
        tell_room(this_object(),QCTNAME(tp)+" stands up from the sofa.\n",
            filter_the_blind(tp), tp);
        tp->remove_prop(ON_SOFA);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
    } else if (tp->query_prop(IN_CHAIR)) {
        tp->catch_msg("You stand up from your chair.\n");
        tell_room(this_object(),QCTNAME(tp)+" stands up from "+
            tp->query_possessive()+" chair.\n",
            filter_the_blind(tp), tp);
        tp->remove_prop(IN_CHAIR);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
    } else {
        notify_fail("You are not sitting on anything.\n");
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

        if (ob->query_prop(ON_SOFA)) {
            ob->catch_msg("You stand up from the sofa.\n");
            ob->remove_prop(ON_SOFA);
            ob->remove_prop(LIVE_S_EXTRA_SHORT);
        } else if (ob->query_prop(IN_CHAIR)) {
            ob->catch_msg("You stand up from your chair.\n");
            ob->remove_prop(IN_CHAIR);
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
