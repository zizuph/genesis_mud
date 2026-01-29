#pragma strict_types

inherit  "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include "guild.h"

#define  MAX_GUILD_LEVEL   8
#define  SUBLOC            "_shieldbearer_emblem_subloc_"

static string  *material = ({ "wooden", "brass", "copper",
                              "bronze", "iron", "silver",
                              "golden", "steel", "dwarven-steel" });
object         owner;
int            worn       = 0;

public string  query_color();
string         metal_type = query_color();

void
create_object()
{
    set_name("emblem");
    add_name(GUILD_EMBLEM_ID);
    add_name("brooch");
    set_short("@@short_desc@@");
    set_adj("buckler");
    add_adj(metal_type);
    set_long("This simple-looking @@query_color@@ brooch " +
        "is oval shaped and reminds you of a small buckler. It does not " +
        "seem to be designed for decorative purposes but rather as a sort " +
        "of token. There is a symbol of two twin peaks carved on " +
        "its surface. Just below it you notice a few dwarven runes, " +
        "that you understand to mean something like <help shieldbearer>. " +
        "The brooch may be fastened to your shoulder thanks to a smartly " +
        "designed clasp that keeps it firmly in place.\n");
    
    add_item(({ "runes", "dwarven runes", "symbol", "twin peaks" }),
        "Just below two twin peaks, the symbol of Iron Delving, " +
        "some dwarven runes have been carved on the surface of the " +
        "brooch. Taking a closer look at them you manage to recognize " +
        "the words <help shieldbearer>.\n");
        
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    
    remove_prop(OBJ_I_VALUE);
}

public int
query_guild_level()
{
    owner = E(TO);
    
    if ( interactive(owner) )
        return MIN(MAX_GUILD_LEVEL, owner->query_stat(SS_LAYMAN) / 17);
    else 
        return 4;
}

public string
query_color()
{
    remove_adj(metal_type);
    metal_type = material[query_guild_level()];
    add_adj(metal_type);
    
    return metal_type;

}

public string
short_desc()
{
    string color;
    
    color = query_color();
    
    return color + " buckler brooch";    
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if ( me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) )
        return "You have your " + short() + " fastened to your left " +
            "shoulder.\n";
    
    if ( for_obj == me )
        return "You are wearing the " + short() + " with the symbol " +
            "of two twin peaks attached to your left shoulder.\n";
    else
        return C(PRONOUN(me)) + " is wearing the " + short() +
            " with the symbol of two twin peaks attached to " + HIS(me) +
            " left shoulder.\n";
}

public int
query_worn_emblem()
{
    return worn;
}

public int
wear(string str)
{

    int   i;
    mixed oblist;
        
    if ( !str )
        return 0;
    
    if ( !TP->query_wiz_level() &&
        ( TP->query_guild_name_lay() != "Shieldbearers of Iron Delving" ) )
    {
        notify_fail("You try to wear the " + short() + ", but you can not " +
            "do it for some reason.\n");
        return 0;
    }
    
    if( query_worn_emblem() )
    {
        notify_fail("You are already wearing it.\n");
        return 0;
    }
                                    
    i = parse_command(str, TP, "[the] %i", oblist);
    
    if( i != 1 || !oblist || member_array(TO, oblist) < 0 || oblist[0] == 0 )
        return 0;
    
    write("You attach the " + short() + " to your left shoulder.\n");
    say(QCTNAME(TP) + " attaches the " + short() + " to " + HIS(TP) +
        " left shoulder.\n");

    TP->add_subloc(SUBLOC, TO);
    set_no_show_composite(1);
    worn = 1;
    
    return 1;
}

varargs int
remove(string str, object who = TP)
{
    int   i;
    mixed oblist;
    
    if ( !str )
        return 0;
        
    if ( !query_worn_emblem() )
    {
        notify_fail("You are not wearing it.\n");
        return 0;
    }
    
    i = parse_command(str, who, "[the] %i", oblist); 
    
    if( i != 1 || !oblist || member_array(TO, oblist) < 0 || oblist[0] == 0 )	
        return 0;
    
    who->catch_msg("You remove your " + short() + ".\n");
    tell_room(E(who), QCTNAME(who) + " removes " + HIS(who) + " " + 
        short() + ".\n", who);

    who->remove_subloc(SUBLOC);
    set_no_show_composite(0);
    worn = 0;

    return 1;
}

public void
init()
{
    ::init();

    add_action(wear, "wear");
    add_action(wear, "attach");
    add_action(remove, "remove");
}

