/*  /d/Raumdor/common/beach/bountiful/obj/int_report.c
 *
 *  Quest Item, imbued with Exposive runes.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
remove_me()
{
    remove_object();
}


int
read_report(string str)
{
    write("You examine the intelligence report closer. For a "
    +"brief moment, you see letters written on the "
    +"report, which are resembling a rune, or runes you "
    +"don't understand. Suddenly, the runes starts to glow "
    +"alerting red!\nThe runes protecting the intelligence report "
    +"sparks and explodes violently in your face!\n");
    
    say(QCTNAME(this_player()) + " reads the intelligence report.\nSuddenly, it "
    +"explodes violently, causing massive damage!\n");
    
    this_player()->command("scream");
    this_player()->run_away();
    
    this_player()->set_hp(1);
    this_player()->set_mana(1);
    this_player()->set_fatigue(1);
    
    remove_object();
    
    return 1;
}


int
destroy_report(string str)
{
    if (str == "report")
    {
        write("You destroy the intelligence report!\n");
        set_alarm(1.0, 0.0, &remove_object());
        
        return 1;
    }
    
    return 0;
}


void
create_object()
{
    set_name("_spy_intelligence_report");
    add_name("report");
    set_adj("intelligence");
    
    set_short("intelligence report");
    
    set_pshort("intelligence reports");
    
    set_long("This is a fine scroll of papyrus that contains "
    +"intelligence for lich Gylar. A magical aura comes from a "
    +"rune upon the scroll. You "
    +"may <destroy report> if you wish "
    +"to rid yourself of it.\n");
    
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    
    add_item( ({ "rune"  }), "You carefully glance at the "
    +"scroll and the rune without trying to read it. For some "
    +"reason, reading the scroll feels like a very bad idea.\n");
    
    add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This report has been enhanced by "
        + "protective magic.\n",1,
        "The report contains an explosive rune that will detonate "
        +"if the wrong eyes pry on the content of it.\n",20}));

    add_prop(OBJ_S_WIZINFO, "The explosive rune on this report will "
    +"explode in the face of the reader, setting hp and mana to 1, and "
    +"max out fatigue + forcing them to scream and flee 1 room.\n");
    
    set_alarm(300.0, 0.0, &remove_me());
}


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void
init()
{
    ::init();
    add_action(read_report,"read");
    add_action(destroy_report, "destroy");
}