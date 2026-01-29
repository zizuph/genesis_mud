/*
 * skull.c
 *
 * Blizzard, 14/06/2003
 */

#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public int    polish_me(string str);
public int    stare_into(string str);
public int    slap_skull(string str);

int           skull_alarm_id, skull_active;

public void
create_object()
{
    set_name("skull");
    set_short("elf skull");
    set_adj(({ "elf", "elven" }));
    set_long("This is a polished elf skull. It seems to be looking at " +
        "you with its empty eyeholes.\n");
    add_item(({ "eyeholes", "eyehole", "eyes", "eye" }),
        "There are two deep, empty eyeholes in the skull. There is " +
        "something intriguing, that makes you to gaze into them.\n"); 
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_M_NO_SELL, 1);
    
}

void
init()
{
    ::init();
    add_action(polish_me, "polish");
    add_action(polish_me, "rub");
    add_action(stare_into, "stare");
    add_action(stare_into, "gaze");
    add_action(slap_skull, "slap");
    add_action(slap_skull, "calm");
}

public int
slap_skull(string str)
{
    if ( !strlen(str) || !parse_command(str, ({}), 
        "[a] [an] [the] [elf] 'skull'")  )
    {
        notify_fail(capitalize(query_verb()) + " the skull?\n", 0);
        return 0;
    }
    
    if ( !skull_active )
    {
        write("You slap the elf skull, but nothing happens.\n");
        say(QCTNAME(TP) + " slaps the elf skull, but nothing happens.\n");
        return 1;
    }
    
    write("You slap the elf skull, as you got tired of it.\n" +
        "The elf skull goes 'All right!'.\n");
    tell_room(E(TP), QCTNAME(TP) + " slaps the elf skull.\n" +
        "The elf skull goes 'All right!'.\n", TP);
    skull_active = 0;
    
    remove_alarm(skull_alarm_id);
        
    return 1;

}

public void
skull_msg()
{
    object ob = E(TO);
    
    if ( !living(ob) )
        return;
        
    if ( !skull_active )
        return;
        
    switch ( random(8) )
    {
    case 0:
        tell_object(ob, "The elf skull goes 'Booooooo'.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", goes 'Boooooooo'.\n", ob);
    break;
    case 1:
        tell_object(ob, "The elf skull produces some clicking noise.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", produces some clicking noise.\n", ob);
    break;
    case 2:
        tell_object(ob, "The elf skull tries to produce a screaming " +
            "sound.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", tries to produce a screaming sound.\n", ob);
    break;
    case 3:
        tell_object(ob, "The elf skull moves its jaw.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", moves its jaw.\n", ob);
    break;
    case 4:
        tell_object(ob, "The elf skull goes 'Where are my ears?!'.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", goes 'Where are my ears?!'.\n", ob);
    break;
    case 5:
        tell_object(ob, "The elf skull sings 'My ears, pointy ears. It's good to " +
            "have ...' and goes 'Hey! Where are my ears?!'.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", sings 'My ears, pointy ears. It's good to have ...' and " +
            "goes 'Hey! Where are my ears?!'.\n", ob);
    break;
    case 6:
        tell_object(ob, "The elf skull goes 'You! Why I do not feel my legs?!'.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) + 
            ", goes 'You! Why I do not feel my legs?!'.\n", ob);            
    break;
    case 7:
        tell_object(ob, "The elf skull goes 'I need to fix my hair style.'.\n");
        tell_room(E(ob), "The elf skull, held by " + QTNAME(ob) +
            ", goes 'I need to fix my hair style.'.\n", ob);
    break;        
    }

    skull_alarm_id = set_alarm(70.0, 0.0, skull_msg);    
}
    
public void
speak_up(object ob)
{
    if ( !skull_active )
    {
        tell_object(ob, "\nThe elf skull produces a clicking noise 'What? " +
            "What do you want from me?'.\n");
        tell_room(E(ob), "\nThe elf skull, held by " + QTNAME(ob) +
            ", produces a clicking noise 'What?! What do you want " +
            "from me?!'.\n", ob);
        skull_active = 1;
        skull_alarm_id = set_alarm(30.0, 0.0, skull_msg);   
        return;
    }
    
    write("\nThe elf skull goes 'What?!'.\n");
    say("\nThe elf skull, held by " + QTNAME(TP) + ", goes 'What?!'.\n");
    
}

public void
answer_me(object ob)
{
    tell_object(ob, "\nThe elf skull produces a clicking noise " +
        "'Eh? What are you talking about?'.\n");
    tell_room(E(ob), "\nThe elf skull, held by " + QTNAME(ob) + 
         ", produces a clicking noise 'Eh? What are you talking " +
         "about!?'.\n", ob);
}

public int
stare_into(string str)
{
    if ( !strlen(str) || !parse_command(str, ({}),
        "[into] [in] [the] [empty] 'eyeholes' / 'eyes'"))
    {
        notify_fail(capitalize(query_verb()) + " into the eyeholes?\n", 0);
        return 0;
    }

    write("You stare into the empty eyeholes of the elf skull " +
        "thoughtfully and ask philosophically 'To be ... or not to be?'.\n");
    tell_room(E(TP), QCTNAME(TP) + " stares into the empty eyeholes " +
        "of the elf skull thoughtfully and asks philosophically " +
        "'To be ... or not to be?'.\n", TP);
    set_alarm(3.0, 0.0, &answer_me(TP));

    return 1;

}

public int
polish_me(string str)
{
    if ( !strlen(str) || !parse_command(str, ({}),
        "[a] [an] [the] [elf] 'skull'") )
    {
        notify_fail(capitalize(query_verb()) + " the skull?", 0);
        return 0;
    }

    write("You hold the " + short() + " at the level of your eyes " +
        "and rub it gently. For a moment you think there can be " +
        "seen a gleam, deep in the empty eyeholes.\n");
    tell_room(E(TP), QCTNAME(TP) + " holds the " + short() + 
        " at the level of " + POSSESSIVE(TP) + " eyes and rubs it " +
        "gently.\n", TP);
    
    set_alarm(3.0, 0.0, &speak_up(TP));
        
    return 1;
 
}

