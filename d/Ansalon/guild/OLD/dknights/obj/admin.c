inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

void
create_object()
{
    seteuid(getuid());
    add_name("admin");
    set_short("admin object");
    set_long("For the death knights\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
}

int
demote(string whom)
{
    //The player is a rose knight -> Sword Knight
    if (TP->test_bit("ansalon",3,8))
    {
        TP->clear_bit(3,8);
        write("You demote the knight.\n");
        return 1;
    }

    //The player is a sword knight -> Crown Knight
    if (TP->test_bit("ansalon",3,9))
    {
        TP->clear_bit(3,9);
        write("You demote the knight.\n");
        return 1;
    }

    //The player is a crown knight -> Squire
    if (TP->test_bit("ansalon",3,10))
    {
        TP->clear_bit(3,10);
        write("You demote the knight.\n");
        return 1;
    }

    if (!TP->test_bit("ansalon",3,10) || !TP->test_bit("ansalon",3,9) || !TP->test_bit("ansalon",3,8))
    {
        write("That knight is already a squire, you can't demote him more.\n");
    }
    return 1;
}


int
promote(string whom)
{
    //The player is a rose knight -> Do nothing.
    if (TP->test_bit("ansalon",3,8))
    {
        write("That knight is already a Knight of the Rose.\n");
        return 1;
    }

    //The player is a sword knight -> Rose.
    if (TP->test_bit("ansalon",3,9))
    {
        TP->set_bit(3,8);
        if (TP->query_guild_level_occ() > MAX_GUILD_LEVEL_SWORD)
        {
            //TP->set_guild_level_occ(GUILD_TAX * MAX_GUILD_LEVEL_SWORD)
        }
    }

    //The player is a crown knight -> Sword.
    if (TP->test_bit("ansalon",3,10))
    {
        TP->set_bit(3,9);
        if (TP->query_guild_level_occ() > MAX_GUILD_LEVEL_CROWN)
        {
            //TP->set_guild_level_occ(GUILD_TAX * MAX_GUILD_LEVEL_CROWN)
        }
    }

    //The player is a squire -> Crown.
    if (!TP->test_bit("ansalon",3,10) || !TP->test_bit("ansalon",3,9) || !TP->test_bit("ansalon",3,8))
    {
        TP->set_bit(3,10); 
        if (TP->query_guild_level_occ() > MAX_GUILD_LEVEL_SQUIRE)
        {
            //TP->set_guild_level_occ(GUILD_TAX * MAX_GUILD_LEVEL_SQUIRE)
        }
    }
    return 1;
}

init()
{
    add_action("promote", "promote");
    add_action("demote", "demote");
    ::init();
}




