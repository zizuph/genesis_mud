 
 /*  Spirit Circle of Psuchae Lay Shadow  */
 /*           July 24th, 2003             */
 /*                Jaacar                 */
           
#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_lay_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

static int prot;
public string *titles = ({"Spirit of Air",
                          "Spirit of Earth",
                          "Spirit of Fire",
                          "Spirit of Water"});

string query_guild_style_lay() { return SPIRIT_GUILD_STYLE; }
string query_guild_name_lay() { return SPIRIT_GUILD_NAME; }

int
query_guild_tax_lay()
{
    return SPIRIT_GUILD_TAX_LAY;
}

int
add_lay_shadow(object who)
{
    return shadow_me(who, "layman", SPIRIT_GUILD_STYLE, SPIRIT_GUILD_NAME);
}

void
init_lay_shadow(string str)
{
    ::init_lay_shadow();
}

int
query_guild_keep_player(object ob)
{
    return 1;
}

string
query_guild_title_lay()
{
    int flag;
    object who;

    who = query_shadow_who();
    flag = who->query_skill(SS_PATRON_ELEMENTAL);

    seteuid(getuid());
    switch(flag)
    {
        case 0:
            return "";        // none (Weren't a Worshipper)
            break;
        case FIRE_FLAG:
            if (who->query_prop(HIDE_LAYMAN_TITLE))
                return "";
            else
                return titles[2]; // fire
            break;
        case EARTH_FLAG:
            if (who->query_prop(HIDE_LAYMAN_TITLE))
                return "";
            else
                return titles[1]; // stone
            break;
        case AIR_FLAG:
            if (who->query_prop(HIDE_LAYMAN_TITLE))
                return "";
            else
                return titles[0]; // wind
            break;
        default:
            if (who->query_prop(HIDE_LAYMAN_TITLE))
                return "";
            else
                return titles[3]; // wave
            break;
    }
}

public mixed 
wield(object weapon) 
{ 
    if (weapon->query_prop(SPIRIT_CUTTING_KNIFE))    // Allow this knife
    {                                                // So they can get
        return shadow_who->wield(weapon);            // Leftovers from bodies.
    }

    if (weapon->query_prop("mystic_weapon"))
    {
        return shadow_who->wield(weapon);
    }

    if (weapon->weapon_type() == "club")
    {
        return shadow_who->wield(weapon);    // Allow all clubs to be wielded
    }

    if (weapon->query_dt() != W_BLUDGEON && (!(shadow_who->query_wiz_level()))) 
        return "You cannot wield that weapon, it is not a bludgeoning weapon.\n"; 
    return shadow_who->wield(weapon); 
}

mixed
query_guild_trainer_lay()
{
    return ({ SPIRIT_TRAINER });
}

