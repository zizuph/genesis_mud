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

    SK_ADD(SS_DEFENSE, "");
    SK_ADD(SS_PARRY, "");
    SK_ADD(SS_WEP_SWORD, "");
    SK_ADD(SS_APPR_MON, "");

#ifdef SS_PROT_CLARITY
    sk_add_train(SS_PROT_CLARITY, "", "clarity", 130, 50, SS_WIS, 45);
#endif

#ifdef SS_PROT_2H_SWORD
    sk_add_train(SS_PROT_2H_SWORD, "", "2-handed sword", 130, 50, SS_DEX, 125);
#endif

    add_exit("training_hall1", "south");
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
