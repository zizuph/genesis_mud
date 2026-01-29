/*
 * sleeper.c
 * An object that takes care of the player when they fall asleep.
 * ( Given by the goblin lord, /d/Rhovanion/common/npcs/goblins/goblin_lord )
 * Written by Trenix@Genesis, 8-17-93
 *
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define TO(str) tell_object(owner,str)  /* Tell owner */
#define ENTRY "/d/Rhovanion/common/ob_caves/inner_entry"

object owner;

void
create_object()
{
    set_name("sleeper");
    set_pname("sleepers");
    set_short(0);
    set_long(0);
    set_no_show();
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,0);
    owner = 0;
}

void assign_owner(object player)
{
    if ( objectp(player) )
    {
        owner = player;
    }
}

void start_sleep()
{
    int level;

    level = 1;
    call_out("messages", 1, level);
    return;
}

void messages(int level)
{
    /* Error codes:
     * If the default case is reached, which should never happen,
     * the mortal is made aware of the bug and is told to notify
     * a Rhovanion wizard giving the error code of 10. I picked
     * 10 due to the ordering of the messages, could have picked
     * -1 I suppose.  /Trenix
     */

    switch(level)
    {
        case 1 :
        {
            TO("You feel yourself drifting away from reality.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 2 :
        {
            TO("All of a sudden you feel very much at peace.\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 3 :
        {
            TO("You begin to move through layers of mist,\neach one softly "+
               "touching you as you pass.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 4 :
        {
            TO("Somehow the mist seems to be taking on a life of its own,\n");
            TO("perhaps trying to lead you somewhere.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 5 :
        {
            TO("The mist is beginning to shape itself into a familiar "+
               "form.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 6 :
        {
            TO("The mist continues to change and adds color.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 7 :
        {
            TO("Suddenly you realize the mist is you. Strangly enough,\n"+
               "you don't feel afraid of it, rather a strong "+
               "attachment.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 8 :
        {
            TO("You feel a pulling force bringing you closer to the "+
               "mist.\n\n");
            call_out("messages", 10, level+1);
            break;
        }
        case 9 :
        {
            TO("The mist begins to join with you making one being.\n");
            TO("Somehow you feel its always been there, just never "+
               "noticed.\n");
            TO("You feel much more rested than before.\n\n");
            owner->set_mana( ( ( owner->query_max_mana() ) / 3 ) * 2 );
            /* 2/3 of full mana restored. */
            call_other(ENTRY,"??");  /* Load or reference */
            tell_room(find_object(ENTRY),capitalize(owner->query_name())+
                      " arrives from nowhere.\n");
            owner->move_living( "M", ENTRY, 1 );
            TO("You find yourself in new surroundings.\n");
            call_out("remove_object", 1);
            break;
        }
        default :
        {
            /* This should never happen. */
            TO("You feel something has gone wrong in your dream and you\n");
            TO("should tell a Rhovanion wizard. Error code: 10.\n\n");
        }
    }
}

init()
{
    add_action("cmd_trap", "", 1);
}

int cmd_trap(string str)
{
    string verb, tmp1, tmp2;

    verb = query_verb();
    if ( !verb || !stringp(verb) )
    {
        return 0;
    }
    if ( owner->query_wiz_level() )
    {
        TO("You are granted access outside your dream due to your wizard "+
           "status.\n");
        return 0;
    }
    switch(verb)
    {
        case "commune" :
        case "reply" :
        case "bug" :
        case "sysbug" :
        case "typo" :
        case "idea" :
        case "praise" :
        case "vitals" :
        {
            return 0;
        }
        if ( verb == "look" && !str )
        {
            TO("You see an endless void of mist in all directions.\n");
            return 1;
        }
        sscanf(str," at %s",tmp1);
        sscanf(str," %s",tmp2);
        if ( ( verb == "look" && tmp1 ) ||
             ( ( verb == "exa" || verb == "examine" ) && tmp2 ) )
        {
            tmp1 = lower_case(tmp1);
            if ( !tmp1 )
            {
                tmp1 = lower_case(tmp2);
            }
            if ( tmp1 == "me" || tmp1 == "myself" ||
                 tmp1 == owner->query_real_name() )
            {
                return 0;
            }
            if ( tmp1 == "mist" )
            {
                TO("It's a soft white mist flowing all around you.\n");
                return 1;
            }
            TO("You find no "+tmp1+".\n");
            return 1;
        }
        TO("You find yourself unable to do that.\n");
        return 1;
    }
}

/* EOF */
