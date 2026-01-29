/*
 * /d/Shire/claws/join.c
 *
 * This is the room where orcs join the glorious ranks of the Black Claws.
 *
 * Turgon, 15.10.96
 *
 * Modification log:
 *
 *
 */

#pragma save_binary

inherit "/d/Shire/room";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Shire/guild/claws/claw_defs.h"
#include "/d/Shire/skills.h"
#include "/d/Shire/bits.h"
#include "/d/Shire/defs.h"

#define LOG_BOOK "/d/Shire/guild/claws/log/new_members
#define CLAW_LOG "/d/Shire/claws/log/claws"
#define LOG_SIZE 25000
#define WRITE_NAME(x) sprintf("%-11s", capitalize((x)->query_real_name()))

string read_sign();

void
create_room()
{
    set_short("End of tunnel");
    set_long("The tunnel ends right in front of a strong-looking "+
    "iron gate, which leads further north. South the path disappears "+
    "deeper into the mountain. The hall is dimly lit by a few torches, and "+
    "on the eastern side of the gate a quite large desk stands. There "+
    "are some papers on the desk, and hanging above the desk is a small, "+
    "readable sign. Water drips down from the walls, and the air is "+
    "humid and cold. The water which has gathered on the floor seems "+
    "to float underneath the gate, northwards.\n");

    add_item(({"sign", "readable sign"}), VBFC("read_sign"));
    add_item(({"gate", "iron gate"}), "The gate seems impenetratable, and it "+
    "seems impossible to open it from here. You gather it must be barred "+
    "in some way from the other side. Maybe knocking on it will help?\n");
    add_item("desk", "The desk has seen better days, but it seems to be usable "+
    "to store some papers on. They appear to be some kind of contract.\n");
    
    //EXIT("south", "/d/Shire/claws/rooms/path1");
    add_exit("meeting", "north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    create_guild_support();
}

nomask public void
init()
{
    ::init();
    init_guild_support();

    add_action("do_sign", "sign");
    add_action("do_erase", "erase");
    add_action("do_read", "read");
}

int
do_read(string str)
{
    if (!strlen(str))
    {
    notify_fail("Read what?\n");
    return 0;
    }

    if (str != "sign")
    {
    notify_fail("Read the sign perhaps?\n");
    return 0;
    }

    write(read_sign());
    return 1;
}


string
read_sign()
{
    string text = "";
    text +=
      "I, Bolg, son of Azog the mighty, need new fighters in our fight "+
      "against those foul and vicious dwarves, and the cursed elves. "+
      "If you are willing to "+
      "join the Black Claws, you must <sign contract>. If you wish to "+
      "leave us, you can <erase contract> to remove your name from it."+
      " But be warned. Leaving us will be punished with death, and "+
      "removeal of all guild skills!.\n"+
      " May the force be with you.\n";
    return text;
}

/*
 * Function name: log_guild
 * Description:   Logs certain actions of the members.
 * Arguments:     text - the text to log.
 */
nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(CLAW_LOG) > LOG_SIZE)
        rename(CLAW_LOG, (CLAW_LOG +".old"));

    write_file(CLAW_LOG, text);
}

/*
 * Function name: do_sign
 * Description:   Makes the player member of Black Claw Clan.
 * Arguments:     str - The command to write "sign contract".
 * Returns:       1 - If success, 0 if failure.
 */
nomask static int
do_sign(string str)
{
    object tp = this_player();
    object shadow;
    string who;
    int result;
    string race;

    race = tp->query_race_name();

    notify_fail("What do you want to sign?!?\n");
    if (!str)
        return 0;

    if (str != "contract")
    {
        write("Try with <sign contract>.\n");
        return 1;
    }

    if ((race == "elf") || (race == "dwarf"))
    {
        write("Only humans and gobbies can sign that contract!\n");
        return 1;
    }

    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        write("You are already a member!\n");
        return 1;
    }

    shadow = clone_object(SHADOW);

    if((result = shadow->shadow_me(tp, "occupational", GUILD_STYLE, GUILD_NAME)) != 1)
    {
        log_guild(ctime(time()) +" "+WRITE_NAME(tp)+" failed to add shadow "+
        "with result "+result+".\n");
        write("An error occured whilst Melkor tried to medle with your soul. "+
        "please leave a bug report about this.\n");
        return 1;
    }

    write("You quickly scrabble your name, or what appears to be some letters"+
    	" onto the contract.\n"+
    "You feel yourself lifted to new heights, as some weird power float "+
    "through your soul.\n\n\n");
    write("A voice shouts from behind the gate: Welcome into our ranks "+
    tp->query_real_name()+".\n\n");
    write("The gate opens up, and you are pulled through it, and it closes "+
    "behind you.\n");
    say(QCTNAME(tp)+" leans over the desk and scrabbles something on the "+
    "paper laying there.\n\n\n");
    say("A voice shouts from behind the gate: Welcome into our ranks "+
       tp->query_real_name()+".\n");
    say("The gate opens up, and someone pulls "+QTNAME(tp)+" through it.\n"+
    "The gate closes immediately.\n");
       tp->move_living("M", "/d/Shire/claws/rooms/meeting", 0, 1);

    set_alarm(1.0,0.0, "init_me", tp);
    log_guild(ctime(time())+" "+WRITE_NAME(tp)+" joined the Black Claws.\n");
      THRONE->add_member(TP->query_real_name(), SCOUT);
    write("You're scout now!\n");

    tp->clear_guild_stat(SS_OCCUP);
    tp->set_guild_pref(SS_OCCUP, GUILD_TAX);
    //tp->add_cmdsoul(GUILD_SOUL);
    tp->update_hooks();
    return 1;
}

int
init_me(object ob)
{
    ob->init_occ_shadow();
    return 1;
}

/*
 * Function name: erase
 * Description:   leave the guild
 * arguments:     str - 'name'
 */
nomask static int
do_erase(string str)
{
    object tp = this_player();
    int result;

    seteuid(getuid());

    notify_fail("Erase what?\n");
    if (!str)
        return 0;

    notify_fail("Erase name you mean?\n");
    if (str != "name")
        return 0;

	if (tp->query_guild_name_occ() != GUILD_NAME)
	{
		write("How can you leave something you are not a part of?\n");
		return 1;
	}

	if (!tp->remove_guild_occ())
	{
		write("Something went wrong. Melkor wants you to stay a little "+
		"longer. If you still wish to leave the guild, make a bug report "+
		"which says: Error while removing shadow!.\n");
		return 1;
	}

	write("All of a sudden, a horde of Orcs comes out of the gate and "+
		"overwhelm you in a vicious attack. You try to hold them back, but "+
		"they are simply all over you, hacking and slashing their weapons "+
		"upon you. Just as you managed to cut a way past them, you feel "+
		"something that cleaves deep into your skull. You cry out in pain "+
		"and everything turns black. You die in the spot, with your head "+
		"crushed!\n");
	say("All of a sudden a horde of Orcs comes running out through the gate."+
		"They attack "+QTNAME(tp)+" in a vicious attack, hacking and "+
		"slashing their weapons into "+HIM_HER(tp)+". Just as "+QTNAME(tp)+
		"managed to cut a path through all the orcs, a giant Uruk comes up "+
		"from behind and cleaves his vicious scimitar into "+QTNAME(tp)+"'s "+
		"skull. "+QTNAME(tp)+" dies instantly, with a scream of pain echoing "+
		"through the tunnels!\n\n");

	write("Unfortunately, the real death hasn't been installed yet.\n");
	
	// Here we make the player pay! with DEATH!

    THRONE->remove_member(this_player()->query_real_name());
    //tp->remove_cmdsoul(GUILD_SOUL);
    //tp->remove_skill(BLACK_CLAW);
    //tp->remove_skill(SS_CLAW);
    //tp->remove_skill(SS_SHIELD);
    //tp->update_hooks();
    tp->set_default_start_location(tp->query_def_start());
    //tp->do_die();

    tp->start_skill_decay();

    log_guild(ctime(time())+" "+WRITE_NAME(tp)+" left the guild!\n");
    
    return 1;
}


/*
 * Function name: remove_player_changed_race
 * Description:   Removes a player from the guild if he changed race.
 * Arguments:     tp - Player to remove.
 */

nomask void
remove_player_changed_race(object tp)
{
	tp->catch_msg("\n   You have changed race!\n"+
				  "Since we do not allow your new race in our guild,\n"+
				  "you will be removed from the Black Claw Clan!\n");

	tp->catch_msg("You feel something leave your soul, all of a sudden you die!\n");
	log_guild(ctime(time())+" "+WRITE_NAME(tp)+" removed due to race change!\n");
	this_player()->remove_guild_occ();
}

