#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include "guild.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"

int worn = 0;

void
create_object()
{
    set_name("ring");
    add_name(GUILD_EMBLEM_ID);
    add_adj(({"golden","thick"}));

    set_short("thick golden ring");

    set_long("Upon reciting the litany of the minotaurs, you were gifted a thick " +
       "golden ring crafted of white gold. Fine runes have been carved upon it, " +
       "indicating that [help minotaurs menu] will provide you with " +
       "more information on the Bloodsea minotaurs.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_I_VALUE, 2000);

    seteuid(getuid(TO));


}

string
show_subloc(string subloc, object me, object for_obj)
{

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You are wearing a golden ring in your bullish nose.\n";
 
    if (for_obj == me)
        return "You are wearing a golden ring in your bullish nose, " +
        "indicating you are a warrior of the Bloodsea Isles.\n";
    else
        return C(PRONOUN(me)) + " is wearing a golden ring in " + HIS(me)+
        " bullish nose, indicating " +HE(me)+ " is a warrior of the Bloodsea " +
        "Isles.\n";

}


int
query_worn_ring()
{
    return worn;
}
 
 
int
wear(string str)
{
 
    int i;
    mixed oblist;
 
    if ( !str )
        return 0;
 
    if(query_worn_ring())
    {
        notify_fail("You are already wearing it.\n");
        return 0;
    }
 
    i = parse_command(str,TP,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
        return 0;
 
    write("You insert the thick golden ring into your bullish nose.\n");
    say(QCTNAME(TP)+ " inserts a thick golden ring into " +HIS(TP)+
      " bullish nose.\n");
    TP->add_subloc("minotaur_lay_guild", TO);
    set_no_show_composite(1);
    worn = 1;
 
    return 1;
}
 
 
varargs int
remove(string str, object who = TP)
{
    int i;
    mixed oblist;
 
    if ( !str )
        return 0;
 
    if( !query_worn_ring() )
    {
        notify_fail("You are not wearing it.\n");
        return 0;
    }
 
    i = parse_command(str,who,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
        return 0;
 
    who->catch_msg("You remove the thick golden ring from your bullish nose.\n");
 
    tell_room(E(who),QCTNAME(who)+ " removes a thick golden ring from " +
      HIS(who)+ " bullish nose.\n", who);
    who->remove_subloc("minotaur_lay_guild");
    set_no_show_composite(0);
 
    worn = 0;
 
    return 1;
}
 
void
init()
{
    ::init();
 
    ADA("wear");
    ADA("remove");
}
