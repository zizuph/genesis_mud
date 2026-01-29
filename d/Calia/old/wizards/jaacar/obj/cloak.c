
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

string fcolour = "orange";
#define tp this_player()

string align();

void
create_armour()
{
    set_name("cloak");
    set_short(VBFC_ME("short_desc"));
    set_long(VBFC_ME("long_desc"));
    set_ac(8);
    set_at(A_ROBE);
    set_am( ({1, 1, 1}) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2500);
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
    lng_desc = "It is a long "+align()+" cloak.\n";
    return lng_desc;
}

string
align()
{
  int al;
  object who;

    who = query_worn();
    if (!who)
        return "orange";


    al = who->query_alignment();
    switch(al)
    {
        case 1200:
            fcolour = "glowing yellow";
            break;
        case -1200:
            fcolour = "blood red";
            break;
        case 0:
            fcolour = "pulsating orange";
            break;
        case 1000..1199:
            fcolour = "golden";
            break;
        case 800..999:
            fcolour = "canary coloured";
            break;
        case 600..799:
            fcolour = "lemon coloured";
            break;
        case 400..599:
            fcolour = "saffron";
            break;
        case 200..399:
            fcolour = "flaxen";
            break;
        case 1..199:
            fcolour = "ocher";
            break;
        case -1..-199:
            fcolour = "apricot coloured";
            break;
        case -200..-399:
            fcolour = "tangerine coloured";
            break;
        case -400..-599:
            fcolour = "crimson";
            break;
        case -600..-799:
            fcolour = "scarlet";
            break;
        case -800..-999:
            fcolour = "ruby red";
            break;
        case -1000..-1199:
            fcolour = "brick red";
            break;
        default:
            fcolour = "orange";
            break;
    }
    return fcolour;
    
}
