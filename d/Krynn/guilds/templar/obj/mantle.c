/** 
 * Templar Knights guild object
 * Code borrowed with love from the Minotaurs
 * Louie 2004
 */


#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include "../local.h"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>

/** proto **/
int worn = 0;
public int query_holder_level_lay();

void
create_object()
{
    set_name("mantle");
    add_name(GUILD_OBJ_NAME);
    add_adj(({"black","decorative","silver-trimmed"}));

    set_short("black silver-trimmed mantle");

    set_long("This decorative mantle is provided to all "+
        "those who strive to protect the interests of Her "+
        "Majesty, the Dark Queen Takhisis.  " +
        "For more information use [help templar menu].\n");

    add_prop(OBJ_M_NO_DROP, 1);
    //add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_I_VALUE, 2000);

    seteuid(getuid(TO));


}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    
    if (!ADMIN->query_member(to) && !to->query_wiz_level())
    {
        tell_room(environment(TO), "The mantle slowly "+
            "shrivels and disappears.\n", 0);
        TO->remove_object();
    }

    object *everything = all_inventory(to);
    int i = 0, k = 0;
    for (int i = 0; i < sizeof(everything); i++) {
        if (everything[i]->id(GUILD_OBJ_NAME))
        {
            if (k) { everything[i]->remove_object(); }
            k = 1;
        }
    }

}


string
show_subloc(string subloc, object me, object for_obj)
{

    string templar_desc;

    if (ADMIN->query_templar_rank(me) > 0)
        templar_desc = "membership in the Templar Knights of Takhisis";
    else
        templar_desc = "position as a Warrior of Neraka";

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You are wearing a black silver-trimmed mantle " +
            "across your shoulders.\n";
 
    if (for_obj == me)
        return "You are wearing a black silver-trimmed mantle "+
            "across your shoulders, indicating your "+templar_desc+
            ".\n";
    else
        return C(PRONOUN(me)) + " is wearing a black silver-trimmed "+
        "mantle across " + HIS(me)+
        " shoulders, indicating " +HIS(me)+ " " +templar_desc+ ".\n";

}


int
query_worn_item()
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
 
 
    i = parse_command(str,TP,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
        return 0;

    if (!ADMIN->query_member(TP))
    {
        notify_fail("You do not appear worthy to wear this.\n");
        return 0;
    }

    if(query_worn_item())
    {
        notify_fail("You are already wearing it.\n");
        return 0;
    }
     
    write("With a flourish, you throw the black silver-trimmed mantle "+
        "across your shoulders, letting it drape down your back.\n");
    say("With a flourish, "+QTNAME(TP)+ " throws the black silver-trimmed "+
        "mantle across " +HIS(TP)+
        " shoulders, letting it drape down "+HIS(TP)+" back.\n");
    TP->add_subloc("templar_lay_guild", TO);
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
 
    if( !query_worn_item() )
    {
        notify_fail("You are not wearing it.\n");
        return 0;
    }
 
    i = parse_command(str,who,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
        return 0;
 
    who->catch_msg("You remove the black silver-trimmed mantle.\n");
 
    tell_room(E(who),QCTNAME(who)+ " removes the black silver-trimmed "+
        "mantle.\n", who);
    who->remove_subloc("templar_lay_guild");
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

public int
query_holder_level_lay()
{
    object ob;
    
    if (ob = environment())
    {
        return ob->query_guild_level_lay();
    }
    
    return 0;
}
