
/*
 * cloak.c
 *
 * A colour changing cloak for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, August 1st, 2003
 * 
 * Previous update: 2003/08/07
 * Fixed lowering of hood when removing, Lavellan, 2010/09/04   
 *
 */


#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include SPIRIT_HEADER

string fcolour = "dull";
int hood = 0;
string cloak_desc = "";

#define SECTION(x) x->query_skill(SS_PATRON_ELEMENTAL)
#define WEARING_SPIRIT_CLOAK "_wearing_spirit_cloak"

mapping colours = ([FIRE_FLAG:({"glowing white","blazing blue","golden",
                   "flaxen","lemon-coloured","ocher",
                   "apricot-coloured","pulsating orange","mandarin-coloured",
                   "tangerine-coloured","brick red","ruby red",
                   "blood red","crimson red","midnight black"}),
                   AIR_FLAG:({"clear crystalline","shimmering translucent",
                   "unclouded clear","filmy opaque",
                   "hazy white","airy white","obscure white","iridescent opal",
                   "murky white","mist grey","smoke grey","dark grey",
                   "dusky grey","shadowy grey","thundercloud grey"}),
                   EARTH_FLAG:({"sparkling diamond-coloured","sculptured marble-coloured",
                   "translucent quartz-coloured","stiff calcite-coloured",
                   "patterned limestone-coloured","eye-catching mica-coloured",
                   "pale talc-coloured","sturdy granite-coloured",
                   "smooth chert-coloured","viscuous serpentine-coloured",
                   "layered shale-coloured","unyielding hematite-coloured",
                   "solid slate-coloured","absorbing coal-coloured",
                   "glossy obsidian-coloured"}),
                   WATER_FLAG:({"sparkling blue","sleek cerulean","glittering icy blue",
                   "iridescent teal","gleaming turquoise","luminescent sapphire",
                   "pale sky blue","brilliant aquamarine","deep azure",
                   "dusky indigo","morose cobalt","royal blue",
                   "midnight blue","demure ebony","primordial black"})]);

string align();

void
create_armour()
{
    set_name("cloak");
    add_name("_wor_cloak_");
    set_short(VBFC_ME("short_desc"));
    set_long(VBFC_ME("long_desc"));
    set_ac(5);
    set_at(A_ROBE);
    set_af(TO);
    set_am( ({1, 1, 1}) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,1);
}

string
short_desc()
{
    string sht_desc;
    fcolour = align();
    sht_desc = fcolour+" cloak";
    cloak_desc = sht_desc;
    if (hood == 1)
        sht_desc += " with the hood raised";
    else
        sht_desc += " with the hood lowered";
    return sht_desc;
}

string
long_desc()
{
    string lng_desc;
    lng_desc = "It is "+LANG_ADDART(align())+" cloak. You see "+
        "small shimmering letters on the bottom that say "+
        "'help cloak'. ";
    if (hood == 1)
        lng_desc += "The hood is raised.\n";
    else
        lng_desc += "The hood is lowered.\n";
    return lng_desc;
}

string
align()
{
  int al;
  object who;

    who = query_worn();
    if (!who)
        return "dull";

    if (!(IS_MEMBER(who)))
        return "dull";   

    if (!SECTION(who))
    {
        al = who->query_alignment();
        switch(al)
        {
            case 1200:
                fcolour = "pulsating emerald green";
                break;
            case 1000..1199:
                fcolour = "aquamarine";
                break;
            case 800..999:
                fcolour = "platinum white";
                break;
            case 600..799:
                fcolour = "crimson";
                break;
            case 400..599:
                fcolour = "royal blue";
                break;
            case 200..399:
                fcolour = "golden";
                break;
            case 1..199:
                fcolour = "silver";
                break;
            case 0:
                fcolour = "transparent";
                break;
            case -199..-1:
                fcolour = "light brown";
                break;
            case -399..-200:
                fcolour = "dark brown";
                break;
            case -599..-400:
                fcolour = "light grey";
                break;
            case -799..-600:
                fcolour = "stone grey";
                break;
            case -999..-800:
                fcolour = "dark grey";
                break;
            case -1199..-1000:
                fcolour = "charcoal black";
                break;
            case -1200:
                fcolour = "pulsating midnight black";
                break;
            default:
                fcolour = "dull";
                break;
        }
        return fcolour;
    }

    else
    {
        al = who->query_alignment();
        switch(al)
        {
        case 1200:
            fcolour = colours[SECTION(who)][0];
            break;
        case 1000..1199:
            fcolour = colours[SECTION(who)][1];
            break;
        case 800..999:
            fcolour = colours[SECTION(who)][2];
            break;
        case 600..799:
            fcolour = colours[SECTION(who)][3];
            break;
        case 400..599:
            fcolour = colours[SECTION(who)][4];
            break;
        case 200..399:
            fcolour = colours[SECTION(who)][5];
            break;
        case 1..199:
            fcolour = colours[SECTION(who)][6];
            break;
        case 0:
            fcolour = colours[SECTION(who)][7];
            break;
        case -199..-1:
            fcolour = colours[SECTION(who)][8];
            break;
        case -399..-200:
            fcolour = colours[SECTION(who)][9];
            break;
        case -599..-400:
            fcolour = colours[SECTION(who)][10];
            break;
        case -799..-600:
            fcolour = colours[SECTION(who)][11];
            break;
        case -999..-800:
            fcolour = colours[SECTION(who)][12];
            break;
        case -1199..-1000:
            fcolour = colours[SECTION(who)][13];
            break;
        case -1200:
            fcolour = colours[SECTION(who)][14];
            break;
        default:
            fcolour = "dull";
            break;
        }
        return fcolour;
    }
}

int
update_short_desc()
{
    fcolour = align();
    cloak_desc = fcolour+" cloak";
    return 1;
}

mixed
wear(object what)
{
    TP->add_prop(WEARING_SPIRIT_CLOAK,1);
    hood = 0;
    TO->add_prop(OBJ_M_NO_DROP,"You have to remove it first!\n");
    if (IS_MEMBER(TP))
    {
//        TO->add_prop(OBJ_M_NO_DROP,"You have to remove it first!\n");
        say("As "+QTNAME(TP)+" wears a cloak around "+
            HIS+" shoulders, it changes colours!\n");
        tell_object(TP,"As you wear the cloak over your "+
            "shoulders, it changes colour!\n");
        TO->update_short_desc();
        return 1;
    }
//    hood = 0;
//    TO->add_prop(OBJ_M_NO_DROP,"You have to remove it first!\n");
    return 0;
}

mixed
remove(object what)
{
    TP->remove_prop(WEARING_SPIRIT_CLOAK);
    hood = 0;
    TO->remove_prop(OBJ_M_NO_DROP);
    if (IS_MEMBER(TP))
    {
//        TO->remove_prop(OBJ_M_NO_DROP);
        say("As "+QTNAME(TP)+" removes "+HIS+" cloak, it changes colours.\n");
        tell_object(TP,"As you remove the cloak, it changes "+
            "colours.\n");
        return 1;
    }
//    hood = 0;
//    TO->remove_prop(OBJ_M_NO_DROP);
    return 0;
}

int
do_bow()
{
    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    write("You bow slightly, stretching your "+cloak_desc+" out as you do so.\n");
    say(QCTNAME(TP)+" bows slightly, stretching "+HIS+" "+cloak_desc+" out as "+
        HE+" does so.\n");
    return 1; 
}

int
do_cover()
{
    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    write("You cover your eyes with your "+cloak_desc+".\n");
    say(QCTNAME(TP)+" covers "+HIS+" eyes with "+HIS+" "+cloak_desc+".\n");
    return 1; 
}

int
do_cry()
{
    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    write("You cry into your "+cloak_desc+".\n");
    say(QCTNAME(TP)+" pulls "+HIS+" "+cloak_desc+" over "+HIS+" face and begins to "+
        "cry silently into it.\n");
    return 1;
}

int
do_lower()
{
    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    if (hood == 0)
    {
        NF("The hood is already lowered.\n");
        return 0;
    }

    write("You lower the hood of your "+cloak_desc+".\n");
    say(QCTNAME(TP)+" lowers the hood of "+HIS+" "+cloak_desc+".\n");
    hood = 0;
    return 1;
}

int
do_pull()
{
    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    write("You pull your "+cloak_desc+" tightly around your body.\n");
    say(QCTNAME(TP)+" pulls "+HIS+" "+cloak_desc+" tightly around "+HIS+" body.\n");
    return 1;
}

int
do_raise()
{
    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    if (hood == 1)
    {
        NF("The hood is already raised.\n");
        return 0;
    }

    write("You raise the hood of your "+cloak_desc+", casting shadows over "+
        "your face.\n");
    say(QCTNAME(TP)+" raises the hood of "+HIS+" "+cloak_desc+", casting shadows "+
        "over "+HIS+" face.\n");
    hood = 1;
    return 1;
}

int
do_shake(string str)
{
    if (!str)
        str = "dirt";

    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    write("You shake the "+str+" off of your "+cloak_desc+".\n");
    say(QCTNAME(TP)+" shakes the "+str+" off of "+HIS+" "+cloak_desc+".\n");
    return 1;
}

int
do_turn(string str)
{
    object player;

    if (!str)
    {
        NF("Turn to face whom?\n");
        return 0;
    }

    if (!TP->query_prop(WEARING_SPIRIT_CLOAK))
    {
        NF("You must be wearing the cloak to use the emotes of it.\n");
        return 0;
    }

    player = present(str, environment(TP));

    if (!player)
    {
        NF(capitalize(str)+" is not in the room.\n");
        return 0;
    }

    write("You turn to face "+player->query_the_name(TP)+", your "+cloak_desc+" "+
        "rippling as you move. Your "+cloak_desc+" settles gracefully around you.\n");
    player->catch_msg(TP->query_The_name(player)+" turns to face you, "+
        HIS+" "+cloak_desc+" rippling as "+HE+" moves. "+capitalize(HIS)+" "+cloak_desc+" "+
        "settles gracefully around "+HIM+".\n");
    say(QCTNAME(TP)+" turns to face "+QTNAME(player)+", "+HIS+" "+cloak_desc+" "+
        "rippling as "+HE+" moves. "+capitalize(HIS)+" "+cloak_desc+" settles "+
        "gracefully around "+HIM+".\n",({TP,player}));
    return 1;
}

int
do_help(string str)
{
    if (!str || str != "cloak")
        return 0;

    write("When the cloak is worn, you have the following emotes:\n"+
        "clbow                  - bow slightly, stretching your cloak out as\n"+
        "                         you do so.\n"+
        "clcover                - cover your eyes with your cloak.\n"+
        "clcry                  - pull your cloak over your face and cry.\n"+
        "cllower                - lower the hood on your cloak.\n"+
        "clpull                 - pull your cloak around you.\n"+
        "clraise                - raise the hood on your cloak.\n"+
        "clshake <what>         - shake the <what> off of your cloak.\n"+
        "                         NOTE: Do not abuse this one, it could be\n"+
        "                               removed if abused.\n"+
        "clturn <player>        - turn to face <player> making your cloak ripple.\n"+
        "\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_bow,"clbow");
    add_action(do_cover,"clcover");
    add_action(do_cry,"clcry");
    add_action(do_help,"help");
    add_action(do_pull,"clpull");
    add_action(do_raise,"clraise");
    add_action(do_lower,"cllower");
    add_action(do_shake,"clshake");
    add_action(do_turn,"clturn");
}
