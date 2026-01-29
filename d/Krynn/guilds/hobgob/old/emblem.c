#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include "guild.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

int worn = 0;

void
create_object()
{
    set_name(({"wardrum","drum"}));
    add_name(GUILD_EMBLEM_ID);
    add_adj(({"primitive","war"}));

    set_short("primitive wardrum");

    set_long("You look upon a primitive goblin wardrum, used by goblinoid " +
       "raiders to notify others of their location over long distances. This " +
       "was gifted to you by the hobgoblin shaman when you first claimed your " +
       "place amongst the tribes of Throtyl, and you believe his dark enchantments " +
       "have made this instrument far more effective than what you would expect " +
       "from this crude wooden cylinder with humanskin stretched over both ends. " +
       "Goblinish markings, reading [help hobgoblin help], have been burnt along " +
       "the instrument, and a leather strap has been attached to it allowing you to " +
       "wear the drum across your back.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME,  4000);
    add_prop(OBJ_I_VALUE, 2000);

    seteuid(getuid(TO));


}

string
show_subloc(string subloc, object me, object for_obj)
{

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You are wearing a primitive wardrum across your back.\n";
 
    if (for_obj == me)
        return "You are wearing the wardrum of a Throtyl raider across your " +
        "back.\n";
    else
        return C(PRONOUN(me)) + " is wearing a primitive wardrum strapped across " + 
        HIS(me)+ " back, the totem of a hobgoblin raider from Throtyl.\n";

}


int
query_worn_drum()
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
 
    if(query_worn_drum())
    {
        notify_fail("You are already wearing it.\n");
        return 0;
    }
 
    i = parse_command(str,TP,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
        return 0;
 
    write("You roughly throw the primitive wardrum across your back.\n");
    say(QCTNAME(TP)+ " roughly throws " +HIS(TP)+ " primitive wardrum across " +
      HIS(TP)+ " back.\n");
    TP->add_subloc("hobgoblin_lay_guild", TO);
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
 
    if( !query_worn_drum() )
    {
        notify_fail("You are not wearing it.\n");
        return 0;
    }
 
    i = parse_command(str,who,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
        return 0;
 
    who->catch_msg("You pull the primitive wardrum from your back.\n");
 
    tell_room(E(who),QCTNAME(who)+ " pulls the primitive wardrum from " +
      HIS(who)+ " back.\n", who);
    who->remove_subloc("hobgoblin_lay_guild");
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
