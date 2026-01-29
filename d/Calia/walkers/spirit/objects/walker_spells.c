
#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/d/Calia/worshippers/spells/spellcasting";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Calia/walkers/specials/walker_council.h"


public int
query_spell_mess(string verb, string arg)
{
    write("You draw power from the planes of shadow.\n");
    say(QCTNAME(TP)+" draws power from the planes of shadow.\n");
    return 1;
}

void
activate_spells()
{
    if (TP->query_skill(SS_WALKER_PUNISHMENT) == SPELL_BANNED)
    {
        write("You have been banned by the Walkers Council "+
            "from using the gifts of Psuchae.\n");
        THIS->remove_object();
        return;
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_ONE_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_THREE_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_EIGHT_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
    {
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
    {
    }
}

void
create_object()
{
    set_name("_spirit_walker_spells_");
    add_name("walker_spells");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_no_show();
}

string
query_auto_load()
{
    return MASTER + ":";
}

void
init()
{
    ::init();
    activate_spells();
}
