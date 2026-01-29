/* Dummy control panel. ~puzzle/objects/control_panel */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

int slot_state, button_state;

string *slot_mess =

 ({ ({ "All three of the slots are empty",			/* 000 (0) */
       "You hear a rumbling to your north." }),
    ({ "The triangle slot is filled",				/* 001 (1) */
       "Someone pokes you in the ribs." }),
    ({ "The square slot is filled",				/* 010 (2) */
       "You suddenly feel in a state of high spirits." }),
    ({ "Both the triangle and square slots are filled",		/* 011 (3) */
       "A voice in your mind says something undiscernable." }),
    ({ "The circle slot is filled",				/* 100 (4) */
       "The torch flickers as an icy wind blows through the room." }),
    ({ "Both the triangle and circle slots are filled",		/* 101 (5) */
       "The control panel makes a coughing noise but nothing happens." }),
    ({ "Both the square and circle slots are filled",		/* 110 (6) */
       "You feel a tap on your shoulder." }),
    ({ "All three slots are filled",				/* 111 (7) */
       "The control panel shakes and vibrates noisily." }) });

string *button_mess =

 ({ ({ "All four of the buttons are currently off",		/* 0000 (00) */
       "" }),
    ({ "The button numbered 1 is currently lit",		/* 0001 (01) */
       "You hear a loud CLUNK to the west." }),
    ({ "The button numbered 2 is currently lit",		/* 0010 (02) */
       "The control panel makes a strange whirring noise." }),
    ({ "The buttons numbered 1 and 2 are currently lit",        /* 0011 (03) */
       "You hear a scream to the northwest." }),
    ({ "The button numbered 3 is currently lit",		/* 0100 (04) */
       "A whooshing noise comes from one of the rooms to the southwest." }),
    ({ "The buttons numbered 1 and 3 are currently lit",	/* 0101 (05) */
       "The lights on the control panel blink on and off for a few seconds." }),
    ({ "The buttons numbered 2 and 3 are currently lit",	/* 0110 (06) */
       "A voice in your mind says: The monkey can be very useful." }),
    ({ "The buttons numbered 1, 2 and 3 are currently lit",	/* 0111 (07) */
       "You hear a load SMASH somewhere to the south." }),
    ({ "The button numbered 4 is currently lit",		/* 1000 (08) */
       "A gong sounds in the distance." }),
    ({ "The buttons numbered 1 and 4 are currently lit",	/* 1001 (09) */
       "Your eyesight blurs for a second then regains normality." }),
    ({ "The buttons numbered 2 and 4 are currently lit",	/* 1010 (10) */
       "Branches of electricity arc out from the control panel to you!" }),
    ({ "The buttons numbered 1, 2 and 4 are currently lit",	/* 1011 (11) */
       "The control panel emits a loud ringing noise!" }),
    ({ "The buttons numbered 3 and 4 are currently lit",	/* 1100 (12) */
       "A door slams somewhere above you." }),
    ({ "The buttons numbered 1, 3 and 4 are currently lit",	/* 1101 (13) */
       "You hear a horrifyingly evil cackle behind you." }),
    ({ "The buttons numbered 2, 3 and 4 are currently lit",	/* 1110 (14) */
       "A voice in your mind says: Treasure lies beyond the Apollyon room." }),
    ({ "All the four buttons are currently lit",		/* 1111 (15) */
       "The ground shakes and trembles with the force of an earthquake." }) });

void create_object()
{
    set_name("panel");
    add_adj("control");
    set_long("@@long_desc");

    add_prop(OBJ_M_NO_GET, "The control panel is fastened to the wall.\n");

    add_item("slots", "@@exa_items|slots@@");
    add_item("buttons", "@@exa_items|buttons@@");
}

void init()
{
    ::init();

    add_action("insert_slot", "put");
    add_action("insert_slot", "place");
    add_action("insert_slot", "insert");

    add_action("press_button", "push");
    add_action("press_button", "press");
}

string long_desc()
{
    return "A roughly rectangular metallic object fixed to one of the walls. "+
        "On it are four buttons numbered 1 to 4 and three small slots in the "+
        "shape of a triangle, a square and a circle. "+
        button_mess[button_state][0]+" and "+L(slot_mess[slot_state][0])+".\n";
}

string exa_items(string arg)
{
    if(arg == "slots") return slot_mess[button_state][0]+".\n";
    if(arg == "buttons") return button_mess[button_state][0]+".\n";

    return "Please contact a wizard and inform them about this, as it is "+
        "a bug and should be fixed.\n";
}

int press_button(string arg)
{
    string button_string;
    int button_number, button_bit = 1, i, old_state;

    if(!strlen(arg))
        return 0;

    if(parse_command(arg, TP, "'all' 'buttons' [on] [the] [control] [panel]"))
    {
        button_state ^= 15;

        TP->catch_msg("You "+query_verb()+" all the buttons on "+
            LANG_THESHORT(TO)+".\n");

        tell_room(E(TO), QCTNAME(TP)+" presses some buttons on "+
            LANG_THESHORT(TO)+".\n", TP);

        tell_room(E(TO), button_mess[button_state][1]+"\n");
        return 1;
    }

    if(!sscanf(arg, "button %s", button_string) &&
       !sscanf(arg, "%s button", button_string))
    {
        notify_fail(C(query_verb())+" what?\n");
        return 0;
    }

    if(!(button_number = LANG_NUMW(button_string)) &&
       !(button_number = LANG_ORDW(button_string)))
    {
        notify_fail(C(query_verb())+" which button?\n");
        return 0;
    }

    if(button_number < 1 || button_number > 4)
    {
        notify_fail("There are only four buttons. Press which one?\n");
        return 0;
    }

    button_number --;

    old_state     = button_state;
    button_bit    = ftoi(pow(2.0, itof(button_number)));
    button_state ^= button_bit;

    tell_room(E(TO), QCTNAME(TP)+" presses a button on "+
            LANG_THESHORT(TO)+".\n", TP);

    if(button_state > old_state)
    {
        TP->catch_msg("You "+query_verb()+" the button and it lights up.\n");
        tell_room(E(TO), button_mess[button_state][1] + "\n");
    }
    else
        TP->catch_msg("You "+query_verb()+" the button and the light fades.\n");

    return 1;
}

int insert_slot(string arg)
{
    object obj;
    int shape_bit = 0, old_state;

    if(!strlen(arg))
        return 0;

    if(!parse_command(arg, TP, "%o 'in' / 'into' 'slot'", obj))
    {
        notify_fail(C(query_verb())+" what into where?\n");
        return 0;
    }

    if(E(obj) != TP)
    {
        write("You must be holding "+LANG_THESHORT(obj)+" first.\n");
        return 1;
    }

    switch(obj->query_name())
    {
        case "triangle":
            shape_bit = 1;
            break;

        case "square":
            shape_bit = 2;
            break;

        case "circle":
            shape_bit = 4;
            break;

        default:
            write(C(LANG_THESHORT(obj))+" doesn't seem to fit.\n");
            return 1;
    }

    old_state   = slot_state;
    slot_state ^= shape_bit;

    if(slot_state > old_state)
    {
        TP->catch_msg("You "+query_verb()+" "+LANG_THESHORT(obj)+" into "+
            "the corresponding slot.\n");

        tell_room(E(TO), QCTNAME(TP)+" "+query_verb()+"s something into "+
            LANG_THESHORT(TO)+".\n", TP);

        tell_room(E(TO), slot_mess[slot_state][1]+"\n");

        obj->remove_object();
    }
    else
        TP->catch_msg("You are unable to "+query_verb()+" "+
            LANG_THESHORT(obj)+" into the control panel because the slot "+
            "is already filled.\n");
    return 1;
}
