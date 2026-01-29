/* made by Aridor, 02/95 */
/* This is the weapon base for the weapons Darrag the dwarven smith
 * makes in his forge.
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

string recover_string;

void
create_weapon()
{
    set_adj("custom");
    add_prop(OBJ_M_NO_SELL, 1);
}

void
set_weapon_data(string data)
{
    string* txt = explode(data,"&&");
    string typ = txt[0];
    string qual = txt[1];
    string mat = txt[2];
    string for_who = txt[3];
    int wp_hit = atoi(txt[4]);
    int wp_pen = atoi(txt[5]);
    int wp_typ = atoi(txt[6]);
    int wp_style = atoi(txt[7]);
    int wgt;
    
    recover_string = "!!" + data;
    set_name(typ);
    set_long("A very " + qual + " weapon, made by Darrag, the Dwarven " +
		  "Smith. " +
		  "Your name has been encarved on one side.\n");
    set_short(qual+" "+mat+" "+typ);
    add_adj(qual);
    add_adj(mat);
    set_adj(""+ capitalize(for_who) + "'s");
    set_default_weapon(wp_hit, wp_pen, wp_typ, wp_style, W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(wp_hit,wp_pen));
    wgt = F_WEIGHT_DEFAULT_WEAPON(wp_pen, wp_typ);
    add_prop(OBJ_I_WEIGHT, wgt);
    add_prop(OBJ_I_VOLUME, wgt / 10);
}

string
query_recover()
{
    return ::query_recover() + recover_string;
}

void
init_recover(string str)
{
    ::init_recover(str);
    set_weapon_data(explode(str,"!!")[1]);
}
