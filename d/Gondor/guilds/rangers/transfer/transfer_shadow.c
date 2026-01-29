/*
 * /d/Gondor/common/guild/ranger_shadow.c
 *
 * This shadow will replace the old Ranger's shadow. It will be
 * responsible for transfering over all Rangers who have the old
 * shadow. This should not be removed after it is put in place,
 * as people are restored with old shadows, and it will be easier
 * on the AoP this way.
 *
 * Gwyneth, 2002
 *
 */
inherit "/std/guild/guild_occ_sh";
inherit "/d/Gondor/common/lib/binbit.c";
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define TRANSFER_ROOM (RANGERS_DIR + "transfer/transfer")

public int
query_guild_tax_occ()
{
    /* This is a temporary shadow. The Ranger will only have this
       until transfered, and not be able to do anything until then. */
    return 1;
}

public string
query_guild_style_occ()
{
    return "ranger";
}

public string
query_guild_name_occ()
{
    /* The old name */
    return "Gondorian Rangers Guild";
}

int
query_is_ranger_pupil()
{
    return (query_bin_bits(1, 16, 2, query_shadow_who()) == 0);
}

string
query_company()
{
    if (query_bin_bits(1,16,2,query_shadow_who()) == 3)
        set_bin_bits(1,16,2,query_shadow_who(), 2);
    return COMPANY_TITLE[query_bin_bits(1,16,2,query_shadow_who())];
}

public string
query_guild_skill_name(int type)
{
    switch (type)
    {
    case SS_HEARING:
        return "hearing";
        break;
    case SS_BRAWLING:
        return "brawling";
        break;
    case SS_PUNISHMENT:
    case SS_PUNISHED:
    case SS_REWARDED:
    case SS_MASTER_TASK:
    case SS_RANGER_SPELL_LIST:
    case SS_RANGER_DISFAVOUR:
        return "";
        break;
    }
    return query_shadow_who()->query_guild_skill_name(type);
}

public int
query_guild_not_allow_join_occ(object player, string type,
  string style, string name)
{
    return 0;
}

/*
 * Function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
static int
query_guild_keep_player(object ob)
{
    return 1;
}

nomask public string
query_guild_title_occ()
{
    return "";
}

int
query_guild_leader_occ()
{
    return 0;
}

mixed
query_guild_trainer_occ()
{
    /* Don't let any skills decay that they might be using. Let
       them decay after they decide which company they want to join. */
    return ({ RANGERS_NOR_TRAIN, RANGERS_ITH_TRAIN });
}


void
init_transfer()
{
    string start_room = shadow_who->query_default_start_location();
    start_room = extract(start_room, 0, 22);

    if (shadow_who->query_wiz_level())
    {
        shadow_who->catch_tell("The Ranger shadow has been changed! As you " +
            "are a wizard, you will have to add the new shadow yourself.\n" +
            "To avoid seeing this message next time you log in, type " +
            "'Call me remove_transfer_shadow' and then do " +
            "'Call me add_autoshadow " +
            "/d/Gondor/guilds/rangers/shadow/rangers_shadow'.\n");
        return;
    }

    setuid();
    seteuid(getuid());
    TRANSFER_ROOM->teleledningsanka();

    shadow_who->set_default_start_location(TRANSFER_ROOM);
    if (file_name(environment(shadow_who)) != TRANSFER_ROOM)
        shadow_who->move_living("X", TRANSFER_ROOM);
}

void
init_occ_shadow(string arg)
{
    set_alarm(2.0, 0.0, &init_transfer());
}

void
remove_transfer_shadow()
{
    shadow_who->remove_autoshadow(this_object());
}
