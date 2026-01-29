/* File name   : emotes.c
 * Description : Shieldbearers' emotes. This file is included by
 *               dwarf_lay_soul.c
 *
 * Blizzard, 16.08.2003
 */

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <options.h>
#include <cmdparse.h>
#include "guild.h"

string   shield_short;
                                                                                
public mixed
query_shield()
{
    object who;
    who = TP;
    
    if ( who->query_armour(W_RIGHT)->query_at() == A_SHIELD )
        shield_short = who->query_armour(W_RIGHT)->short();
    else if ( who->query_armour(W_LEFT)->query_at() == A_SHIELD )
        shield_short = who->query_armour(W_LEFT)->short();
    else
        shield_short = 0;
    
    return shield_short;
}

/*
 * Function name: emote_cmdlist
 * Description  : Get the emotes available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
emote_cmdlist()
{
    return ([
        /* Command name : Function name */
        "help"          : "help",
        "shready"       : "emote_ready",
        "shrest"        : "emote_rest",
        "shhide"        : "emote_hide",
        "shtrust"       : "emote_trust",
        "shdoubt"       : "emote_doubt",
        "shvictory"     : "emote_victory",
        "shadjust"      : "emote_adjust",
        "shpat"         : "emote_pat",
        "shsong"        : "emote_song",
        "shpolish"      : "emote_polish",
        "shinspect"     : "emote_inspect",
        "shglare"       : "emote_glare",
        "shgrin"        : "emote_grin",
    ]);
}

public int
help(string str)
{
    string subject, filename;
    
    if ( !str )
        return 0;
    
    setuid();
    seteuid(getuid());
    
    if ( str == "shieldbearer" || str == "bearer" )
    {
        cat(GUILD_HELP_DIR + "help");
        return 1;
    }
    
    if(sscanf(str, "shieldbearer %s", subject) != 1)
        if(sscanf(str, "bearer %s", subject) != 1)
            return 0;
    
    filename = GUILD_HELP_DIR + subject;
    
    if( file_size(filename) > 0 )
    {
        cat(filename);
        return 1;
    }
    
    notify_fail("There is no help on that subject I'm afraid.\n");
    return 0;
}

public int
emote_ready(string str)
{
    string  weapon_short;
    string *how = parse_adverb_with_space(str, "loudly", 0); 
    
    if ( strlen(how[0]) )
    {
        notify_fail("Thump your shield how?\n");
        return 0;
    }
    
    if ( !query_shield() )
    {
        notify_fail("But you are not wearing a shield.\n");
        return 0;
    }
    
    if ( sizeof(TP->query_weapon(-1)) < 1 )
    {
        write("You thump your " + shield_short + how[1] +
            " with a clenched fist.\n");
        allbb(" thumps " + HIS(TP) + " " + shield_short + how[1] +
            " with a clenched fist.");
        return 1;
    }
        
    weapon_short = (TP->query_weapon(-1)[0])->short();
    
    write("You thump your " + shield_short + how[1] + " with your " +
        weapon_short + " as you await the battle.\n");
    say(QCTNAME(TP) + " thumps " + HIS(TP) + " " + shield_short + how[1] +
        " with " + HIS(TP) + " " + weapon_short + " as " + HE(TP) + 
        " awaits the battle.\n");
    return 1;
}

public int
emote_rest(string str)
{
    if ( strlen(str) )
    {
        notify_fail("You want just rest, right?\n");
        return 0;
    }
        
    if ( !query_shield() )
    {
        notify_fail("But you are not wearing a shield you could rest on!\n");
        return 0;
    }
    
    write("You place your arms on the " + shield_short + ", resting " +
        "briefly.\n");
    allbb(" places " + HIS(TP) + " arms on the " + shield_short +
        ", resting briefly.");
    return 1;
}
    
public int
emote_hide(string str)
{
    if ( strlen(str) )
    {
        notify_fail("Just hide, it's simple!\n");
        return 0;
    }
    
    if ( !query_shield() )
    {
        notify_fail("You can not hide under a shield while you are not " +
            "wearing any!\n");
        return 0;
    }
    
    if ( E(TP)->query_prop(ROOM_I_INSIDE) )
    {
        write("You hide behind your " + shield_short + ".\n");
        allbb(" hides behind " + HIS(TP) + " " + shield_short + ".");
        return 1;
    }
        
    write("You stare into the sky and raise your " + shield_short + 
        ", trying to hide under it.\n");
    allbb(" stares into the sky and raises " + HIS(TP) + " " + shield_short + 
        ", trying to hide under it.");
    return 1;
}

public int
emote_trust(string str)
{
    if ( strlen(str) )
    {
        notify_fail("Just trust it or not.\n");
        return 0;
    }
    
    if ( !query_shield() )
    {
        notify_fail("You can not trust a shield you are not wearing!\n");
        return 0;
    }
    
    write("Bringing the " + shield_short + " closer to your body, you " +
        "trust it will never fail you.\n");
    say("Bringing the " + shield_short + " closer to " + HIS(TP) + " body, " +
        QTNAME(TP) + " seems to be trusting it absolutely.\n");
    return 1;
}

public int
emote_doubt(string str)
{
    object shield;
    
    if ( !str )
    {
        notify_fail("Express your doubts about what shield?\n");
        return 0;
    }
    
    parse_command(str, TP, "%o", shield);
    
    if ( !shield->check_armour() )
    {
        notify_fail("Express your doubts about what shield?\n");
        return 0;
    }
    
    if ( shield->query_at() != A_SHIELD )
    {
        notify_fail("You surely would not trust anything but a shield!\n");
        return 0;
    }
    
    write("With a wry expression on your face you wonder if it is worthy " +
        "to place much reliance to the " + shield->short() + ".\n");
    allbb(" seems to be doubtful about " + HIS(TP) + " " +
        shield->short() + ".");
    return 1;
}
 
public int
emote_adjust(string str)
{
    object shield;
        
    if ( !str )
    {
        notify_fail("Adjust what shield?\n");
        return 0;
    }
    
    parse_command(str, TP, "%o", shield);
    
    if ( !shield->check_armour() || (shield->query_at() != A_SHIELD) )
    {
        notify_fail("Adjust what shield?\n");
        return 0;
    }
    
    if ( shield->query_worn() != TP )
    {
        notify_fail("You are trying to adjust the " + shield->short() +
            " while you are not even wearing it!\n");
        return 0;
    }
     
    write("You adjust your " + shield->short() + ", firmly fastening it " +
        "to your forearm.\n");
    allbb(" adjusts " + HIS(TP) + " " + shield->short() + ", firmly " +
        "fastening it to " + HIS(TP) + " forearm.");
    return 1;
}
 
public int
emote_victory(string str)
{
    if ( strlen(str) )
        return 0;
        
    if ( !query_shield() )
    {
        write("You roar and raise your fist victoriously.\n");
        allbb(" roars and raises " + HIS(TP) + " fist victoriously.");
        return 1;
    }
     
    write("You roar and raise your " + shield_short + " in victory!\n");
    allbb(" roars and raises " + HIS(TP) + " " + shield_short +
        " in victory!");
    return 1;
}
 
public int
emote_pat(string str)
{
    object *ob;
     
    if ( !query_shield() )
    {
        notify_fail("You can not pat someone with a shield while " +
            "you are not wearing any.\n");
        return 0;
    }
    
    if ( !strlen(str) )
    {
        notify_fail("Who do you want to pat with your shield?\n");
        return 0;
    }
     
    ob = parse_this(str, "[at] [the] %l");
     
    if ( !sizeof(ob) )
    {
        notify_fail("Who do you want to pat with your shield?\n");
        return 0;
    }
     
    actor("You pat", ob, " in the back with your " + shield_short +  ".");
    target(" pats you in the back with " + HIS(TP) + " " + shield_short +
        ".", ob);
    all2act(" pats", ob, " in the back with " + HIS(TP) + " " +
        shield_short + ".");
    return 1;
}
    
public void
verse_two()
{
    string song;

    song = "\n\n Out of the mountains in the midst of the air,\n"+
        "   The axes are dreaming dreaming of rock,\n"+
        "      Of metal alive through the ages of ore,\n" +
        "          Stone on metal metal on stone.\n" +
        "              The soldier's heart contains and dreams\n" +
        "                  The battlefield.\n" +
        "                      Come back in glory\n" +
        "                          Or on your shield.\n\n\n";

    write("You continue to sing:" + song);
    TP->tell_watcher(QCTNAME(TP) + " continues to sing:" +song);
}

public void
verse_three()
{
    string song;

    song = "\n\n         Red of iron imagined from the vein,\n" +
        "       Green of brass green of copper\n" +
        "    Sparked in the fire the forge of the world,\n" +
        " Consumed in its dream as it dives into the bone.\n" +
        "     The soldier's heart lies down, completes\n" +
        "          The battlefield.\n" +
        "              Come back in glory\n\n" +
        "                  Or on your shield.\n\n\n";

    write("You continue to sing:" +song+
        "\nYour blood stirred by the song, you feel ready for battle.\n");
    TP->tell_watcher(QCTNAME(TP)+ " continues to sing:" +song+
        "\n" +QCTNAME(TP)+ " falls silent, and looks ready for battle.\n");
}

public int
emote_song(string str)
{
    string song;

    if(strlen(str))
	return 0;

    song = "\n        Under the hills the heart of the axe\n" +
        "      Arises from cinders the still core of the fire,\n" +
        "    Heated and hammered the handle an afterthought,\n" +
        "  For the hills are forging the first breath of war.\n" +
        "       The soldier's heart sires and brothers\n" +
        "             The battlefield.\n" +
        "                  Come back in glory\n" +
        "                       Or on your shield.\n\n\n";
 
    write("Your voice rises in a dwarven song:\n" +song);
    TP->tell_watcher(QCTNAME(TP)+ "'s voice rises in a dwarven song:\n" +song);

    set_alarm(3.0, 0.0, &verse_two());
    set_alarm(6.0, 0.0, &verse_three());

    return 1;

}
        
public int
emote_polish(string str)
{
    string  weapon_short;
    string *how = parse_adverb_with_space(str, "idly", 0); 
    
    if ( strlen(how[0]) )
    {
        notify_fail("Polish your shield how?\n");
        return 0;
    }
    
    if ( !query_shield() )
    {
        notify_fail("But you are not wearing a shield.\n");
        return 0;
    }
    
    write("You" + how[1] + " polish your " + shield_short + ".\n");
    allbb(how[1] + " polishes " + HIS(TP) + " " + shield_short + ".");

    return 1;
}

public int
emote_inspect(string str)
{
    object *shields;
    object shield;
    
    if ( !strlen(str) )
    {
        str = "shield";
    }
    
    if ( !parse_command(lower_case(str), TP, "[the] %i", shields) ||
        !sizeof(shields = NORMAL_ACCESS(shields, 0, 0)) )
    {
        notify_fail("Inspect what?\n");
        return 0;
    }
    
    shield = shields[0];
    
    if ( !shield->check_armour() || (shield->query_at() != A_SHIELD) )
    {
        notify_fail("You can inspect shields only.\n");
        return 0;
    }
    
    write("You run your hand over the front of the " + shield->short() +
        " inspecting it for dents or cracks.\n" +
        shield->arm_condition_desc());
    allbb(" runs " + HIS(TP) + " hand over the front of the " +
        shield->short() + " inspecting it carefully.");
    
    return 1;
         
}

public int
emote_glare(string str)
{
    object *ob;
     
    if ( !query_shield() )
    {
        notify_fail("But you are not wearing any shield .\n");
        return 0;
    }
    
    if ( !strlen(str) )
    {
        notify_fail("Who do you want to glare at?\n");
        return 0;
    }
     
    ob = parse_this(str, "[at] [the] %l");
     
    if ( !sizeof(ob) )
    {
        notify_fail("Who do you want to glare at?\n");
        return 0;
    }
     
    actor("You glare over the top of your " + shield_short + 
        " at", ob, ".");
    target(" glares over the top of " + HIS(TP) + " " + shield_short +
        " at you.", ob);
    all2act(" glares over the top of " + HIS(TP) + " " + shield_short +
        " at", ob, ".");

    return 1;
}

public int
emote_grin(string str)
{
    string *how = parse_adverb_with_space(str, "confidently", 0); 
    
    if ( strlen(how[0]) )
    {
        notify_fail("Grin how?\n");
        return 0;
    }

    if ( !query_shield() )
    {
        write("You grin" + how[1] + ", thinking about your enemies.\n");
        allbb(" grins" + how[1] + ".");

        return 1;
    }
    
    write("You grin" + how[1] + " knowing that your " + shield_short + 
        " is stronger than your enemies' skulls.\n");
    allbb(" grins" + how[1] + " like " + HE(TP) + " could crush " +
        "any skull with " + HIS(TP) + " " + shield_short + ".");
        
    return 1;
}

