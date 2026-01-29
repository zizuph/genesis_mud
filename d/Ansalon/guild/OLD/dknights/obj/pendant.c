
#pragma strict_types

inherit "/std/armour.c";
inherit "/lib/commands.c";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h> 
#include <files.h>
#include <formulas.h>
#include <std.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

void
create_armour()
{
    set_name("pendant");
    set_adj("blackened");
    add_adj("silver");
    set_short("blackened silver pendant");
    set_at(A_NECK);
    set_long("This is a blackened silver pendant.");

    add_prop(OBJ_M_NO_DROP, "You find it impossible to drop your "+short()+".\n");
    add_prop(DKNIGHT_ARMOUR,1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  100);
    add_prop(OBJ_I_VOLUME,  100);
    set_may_recover();
    remove_prop(OBJ_I_VALUE);
}


// PROMOTE THE TARGET, IF HE OR SHE HAS REACHED THE MAX TITLE.
int
promote(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
       notify_fail("Promote whom?\n");
       return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
       notify_fail("Promote whom?\n");
       return 0;
    }

    obj = ob[0];


    // SWORD ORDER TO ROSE ORDER.
    if (obj->test_bit("ansalon",3,10))
    {
        write("You can't promote that person any higher then the Rose Order.\n");
        return 1;
    }
    if (obj->test_bit("ansalon",3,9))
    {
        if (obj->query_stat(SS_OCCUP) / 14 >= MAX_GUILD_LEVEL_SWORD)
        {
            write("You promote "+obj->query_name()+ " from the Sword Order to "+
                  "the Rose Order.\n");
            obj->set_bit(3,10);
        }
        else
        {
            write("That person has not reached the highest title within the Sword "+
                  "Order.\n"+
                  "You fail to promote "+HIM(obj)+".\n");
        }
        return 1;
    }

    // CROWN ORDER TO SWORD ORDER.
    if (obj->test_bit("ansalon",3,8))
    {
        if (obj->query_stat(SS_OCCUP) / 14 >= MAX_GUILD_LEVEL_CROWN)
        {
            write("You promote "+obj->query_name()+ " from the Crown Order to "+
                  "the Sword Order.\n");
            obj->set_bit(3,9);
        }
        else
        {
            write("That person has not reached the highest title within the Crown "+
                  "Order.\n"+
                  "You fail to promote "+HIM(obj)+".\n");
        }
        return 1;
    }


    // SQUIRE TO CROWN ORDER.
    if (obj->query_stat(SS_OCCUP) / 14 >= MAX_GUILD_LEVEL_SQUIRE)
    {
        write("You promote "+obj->query_name()+ " from squire to "+
              "the Crown Order.\n");
        obj->set_bit(3,8);
    }
    else
    {
        write("That person has not reached the highest title as a squire.\n"+
              "You fail to promote "+HIM(obj)+".\n");
    }

    return 1;
}


void
init()
{
    ::init();
    add_action("promote", "promote");

}
