
#pragma save_binary

inherit "/std/monster";

#include "../goblins.h"

#define GUILD_TYPE  "race"
#define GUILD_STYLE "popular"
#define GUILD_NAME  "Tribe of the Red Eyed Goblins"
#define SHADOW      GOBLIN_GUILD_DIR + "goblin_shadow"

int allow_player(object player);
int allow_players_guilds(object player);

create_monster()
{
    int i;

    set_name("korg");
    set_long("The king looks old, but quite tough.\n");
    set_race_name("goblin");
    set_adj("ruddy-faced");
    set_adj("imposing");

    set_gender(0); /* male = 0, female = 1, other = 2 */

    default_config_mobile(120);

    set_alignment(-400);

    seq_new("intro");
    seq_addfirst("intro", ({"introduce me", "say Me greet you."}));
    trig_new("%s 'introduces' %s", "do_introduce");
    trig_new("%s 'says:' %s 'join' %s 'tribe' %s", "do_join");
    trig_new("%s 'says:' %s 'leave' %s 'tribe' %s", "do_leave");
}

void
do_introduce(string str1, string str2)
{
    command("intro");
}

void
do_get(string str1, string str2)
{
    command("get all");
}

void
do_join(string who, string junk1, string junk2, string junk3)
{
    object shadow;
    int result;
    object player;

    player = find_player(lower_case(who));

    if (!allow_player(player)) {
      command("say You aren't fit to join this tribe!\n");
	return;
    }

    if (!allow_players_guilds(player)) {
      command("say You have already joined a guild we cannot accept.\n");
	return;
    }

    seteuid(getuid(this_object()));
    shadow = clone_object(SHADOW);
    if ((result = shadow->shadow_me(player, GUILD_TYPE,
		GUILD_STYLE, GUILD_NAME)) != 1)
    {
    /* result = -1 (no name), -2 (wrong type), -3 (no style set),
                -4 (the guild the player already joined don't want this tribe.)
		-5 (couldn't shadow the player, security problems. )
                Probably they have set the notify_fail() appropriate.
		0 (already member or player wasn't set properly) */

    /* This is one of the few times you destruct is OK to use... */
        destruct(shadow);
	return;
      command("say For unknown reasons we couldn't help you join " +
 		  "our tribe.\n");
    }

    command("say You are now a new member of this tribe.\n");
    return;
}

int
allow_player(object player)
{
  /* As for query_race vs query_race_name, we only want true goblins */
  /* not variants */
    if (player->query_race_name() != "goblin")
    {
	command("say This tribe is only for goblins! Go away!\n");
	return 0;
    }

    if (player->query_guild_member(GUILD_NAME))
    {
	command("say You are already a member of our tribe.\n");
	return 0;
    }

/* You could test if the player has solved the guild quest or anything... */
    return 1;
}

allow_players_guilds(object player)
{
    if (player->query_guild_member(GUILD_TYPE))
    {
	command("say You are already a member of another " + 
		    GUILD_TYPE + " guild.\n"); 
	return 0;
    }

    return 1;
}

do_leave(string who, string junk1, string junk2, string junk3)
{
    object player;

    player = find_player(lower_case(who));

    if (player->query_guild_name_race() != GUILD_NAME) 
    {
      command("say You no member of tribe, Stoopid!\n");
	return 0;
    }

    if (player->remove_guild_race())
	command("shout You left our beloved tribe.  Now get out!\n");
    else
	command("say There was a strange error, I'm afraid you are\n" +
	      "stuck with us.  Perhaps the great Quis can help you.\n");

    return 1;
}
