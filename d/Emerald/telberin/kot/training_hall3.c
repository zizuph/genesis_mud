#include "../defs.h";

inherit TELBERIN_ROOM;
inherit "/d/Emerald/lib/train";

#include "/d/Emerald/common/guild/kot/guild.h"
#include "/d/Emerald/sys/skills.h"
#include <ss_types.h>
#include <stdproperties.h>

#define SK_ADD(snum, desc) sk_add_train(snum, desc);

void
create_telberin_room()
{
    set_short("KoT training hall");

    add_prop(ROOM_I_INSIDE, 1);

    create_skill_raise();

    SK_ADD(SS_TRADING, "");
    SK_ADD(SS_AWARENESS, "");
    SK_ADD(SS_LANGUAGE, "");
    SK_ADD(SS_ELEMENT_LIFE, "");
    SK_ADD(SS_SPELLCRAFT, "");
    SK_ADD(SS_HERBALISM, "");
    SK_ADD(SS_FORM_CONJURATION, "");
    SK_ADD(SS_FORM_ENCHANTMENT, "");
    SK_ADD(SS_FORM_DIVINATION, "");

    add_exit("training_hall1", "north");
}

void
init()
{
    ::init();
    init_skill_raise();
}

int
sk_query_max(int snum)
{
    mixed file;

    setuid();
    seteuid(getuid());

    if (this_player()->query_kot_lay_member())
    {
        file = this_player()->query_guild_trainer_lay();
    }
    else if (this_player()->query_kot_occ_member())
    {
        file = this_player()->query_guild_trainer_occ();
    }
    else
    {
        return 0;
    }

    if (pointerp(file))
    {
        file = file[0];
    }

    if (!strlen(file))
    {
        return 0;
    }

    return file->sk_query_max();
}
