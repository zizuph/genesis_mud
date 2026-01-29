//
// srshadow - guild shadow for the Order of Sean-Rhian
//
// History:
// Date        Coder            Action
// ----------  ---------------  -----------------------------------
// 7/5/98      Zima             Created
//
#pragma save_binary
 
#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <formulas.h>
 
inherit "/std/guild/guild_occ_sh";
 
//
// greeting - Delivers a greetings message to the player, adds
//            the cmdsoul and guild object.
//
static void greeting()
{
    object gobj;
 
    // give greeting
    setuid(); seteuid(getuid());
    tell_object(shadow_who,
       "Luaidh bi Ardaugh agus Maighal agus an Solsheyderi!\n");
 
    // add the command soul
    shadow_who->add_cmdsoul(SR_SOUL);
    shadow_who->update_hooks();
 
    // give the guild object (not autoload); logout/in to recover if lost
    if (!present(GUILD_OBJ, shadow_who))
    {
        seteuid(getuid());
        gobj = clone_object(GUILD_OBJ_PATH);
        if (gobj->move(shadow_who,1))
        {
            tell_object(shadow_who, "You drop your "+(gobj->short())+".\n");
            gobj->move(environment(shadow_who));
        }
    }
}
 
//
// query_sr_title
//
public string query_sr_title()
{
   int level = shadow_who->query_skill(SS_SR_LEVEL);
   int kirk  = shadow_who->query_skill(SS_SR_KIRK);
   return (SR_MASTER)->query_sr_title(level,kirk);
}
 
//
// init_occ_shadow
//
public void init_occ_shadow(string str)
{
   ::init_occ_shadow(str);
   set_alarm(2.0,0.0,&greeting());
}
 
//
// query/set_sr_level
//
public int query_sr_level() { return shadow_who->query_skill(SS_SR_LEVEL); }
public void set_sr_level(int level)
{
   shadow_who->set_skill(SS_SR_LEVEL,level);
}
 
//
// query/set_sr_kirk
//
public int query_sr_kirk() { return shadow_who->query_skill(SS_SR_KIRK); }
public void set_sr_kirk (int kirk)
{
   shadow_who->set_skill(SS_SR_KIRK, kirk);
}

//
// query/set/add_sr_harmony
//
public int query_sr_harmony() 
{ 
	return shadow_who->query_skill(SS_SR_HARMONY); 
}
public void set_sr_harmony(int h)
{
   shadow_who->set_skill(SS_SR_HARMONY, h);
}
public void add_sr_harmony(int amt)
{
	int h  = query_sr_harmony();
	int nh = h + amt;
	if (h<0) return;  // spells have been disabled?  
	if (nh<0)				
		set_sr_harmony(0);
	else if (nh>SR_HARMONY_MAX)
		set_sr_harmony(SR_HARMONY_MAX);
	else
		set_sr_harmony(nh);
} 

//
// short query functions
//
public int    is_saggart()            { return 1; }
public string query_guild_title_occ() { return query_sr_title(); }
public string query_guild_style_occ() { return GUILD_STYLE; }
public string query_guild_name_occ()  { return GUILD_NAME; }
public int    query_guild_tax_occ()   { return GUILD_TAX; }
public int    query_guild_not_allow_join_occ
              (object tp, string t, string s,string n) { return 1; }
