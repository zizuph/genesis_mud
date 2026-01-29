inherit "/d/Rhovanion/lib/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

static int *skill_arr;
static string *form;
static int *vals;

void set_up_skills();

void create_room()
{
    set_short("Adventurer's guild");
    set_long("You stand in the room where the people of Esgaroth come " +
        "to receive instruction and enlightenment in the ways of the world.  " +
        "Perhaps they would be willing to train you for a fee, or let you " +
        "meditate here.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Rhovanion/common/esgaroth/es-6-12", "west");
    skill_arr = ({ SS_LOC_SENSE, SS_TRADING, SS_APPR_VAL, SS_LANGUAGE });
     form = ({ "avoid getting lost", "trade for a profit",   
        "evaluate an object", "interperet other languages" });
    vals = ({ 50, 30, 50, 30 });

    set_up_skills();
}

void init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
}

void
set_up_skills()
{
    int i;
    for (i=0; i< sizeof(skill_arr); i ++)
        sk_add_train(skill_arr[i], form[i], 0, 0, vals[i]);
}

void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}
