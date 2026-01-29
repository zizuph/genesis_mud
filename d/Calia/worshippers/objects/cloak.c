
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include WORSHIP_HEADER

string fcolour = "dull";

#define tp this_player()
#define SECTION(x) x->query_skill(SS_PATRON_ELEMENTAL)

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
    set_ac(0);
    set_at(A_ROBE);
    set_af(this_object());
    set_am( ({0, 0, 0}) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,1);
}

short_desc()
{
    string sht_desc;
    fcolour = align();
    sht_desc = fcolour+" cloak";
    return sht_desc;
}

long_desc()
{
    string lng_desc;
    lng_desc = "It is "+LANG_ADDART(align())+" cloak.\n";
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
        return "dull";

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

mixed
wear(object what)
{
    if (IS_MEMBER(tp))
    {
        this_object()->add_prop(OBJ_M_NO_DROP,"You have to remove it first!\n");
        say("As "+QTNAME(tp)+" wears a cloak around "+
            tp->query_possessive()+" shoulders, it "+
            "changes colours!\n");
        tell_object(tp,"As you wear the cloak over your "+
            "shoulders, it changes colour!\n");
        return 1;
    }
    this_object()->add_prop(OBJ_M_NO_DROP,"You have to remove it first!\n");
    return 0;
}

mixed
remove(object what)
{
    if (IS_MEMBER(tp))
    {
        this_object()->remove_prop(OBJ_M_NO_DROP);
        say("As "+QTNAME(tp)+" removes "+tp->query_possessive()+
            " cloak, it changes colours.\n");
        tell_object(tp,"As you remove the cloak, it changes "+
            "colours.\n");
        return 1;
    }
    this_object()->remove_prop(OBJ_M_NO_DROP);
    return 0;
}
