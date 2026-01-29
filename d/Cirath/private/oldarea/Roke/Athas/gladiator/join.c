/* This is the main Gladiator guild room. Here you can join, leave and list. */

inherit "/lib/guild_support";
inherit "/std/room";

#include "guild.h"
#include <stdproperties.h>
#include <macros.h>

#define JOIN_LOG GLAD_DIR+"log/gladiator.join"
#define ASK_LOG GLAD_DIR+"log/gladiator.ask"

#define WRITE_LOG(F, O, T)  write_file( F, sprintf("%-52s (%s)\n",    \
                            O->query_name()+" "+ T, ctime(time())))

void
create_room()
{
	object book;
	object scroll;
	object book1;

    set_short("Gladiators room");
    set_long(break_string("This room is small, inside the building with "+
	"only wax candles to light the room. The floor is sandy and the "+
	"walls are all constructed from hard sand-stone. There is a hall "+
	"to the east. In here, you may <enter training>, <leave guild>, "+
	"<ask for cuirasse> , <update membership> or <list>."
     + "\n",78)+"@@trap_door@@");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(GLAD_DIR+"entrance", "east", 0, 1);
    add_item(({"wax candles","candles","candle","light"}),"The wax candles "+
	"are all lit, to provide light in this inside room.\n");
    add_item(({"sand-stone","walls","wall"}),"The walls are all "+
	"solidly constructed from sand-stone, a material that seems\nto "+
	"prevalent in this area.\n");
    add_item(({"floor","sand","sandy floor"}),"The floor is quite sandy, "+
	"no carpets since they would get dirty quickly.\n");
   add_item(({"stone"}),"The stone in the floor looks a bit loose. It may be "+
     "possible to get a fingerhold on it and lift it out.\n");
   add_item(({"scratch marks","marks"}),"There is a stone on the "+
          "floor that has been scratched in a peculiar way.\n");

	book1=clone_object(GLAD_DIR+"book1");
	book1->move(this_object() ,1);

	book=clone_object(GLAD_DIR+"book");
	book->move(this_object() ,1);
	
        scroll=clone_object(GLAD_DIR+"scroll");
        scroll->move(this_object() ,1);
}

string
trap_door()
{
   if(this_player()->query_skill(SS_AWARENESS)>20)
     return"You notice some interesting scratch marks "+
          "on the floor.\n";

   else
   return "";
}

void
init()
{
    ::init();
    add_action("join", "enter");
    add_action("my_leave", "leave");
    add_action("ask", "ask");
    add_action("list", "list");
    add_action("update","update");
    add_action("do_lift","lift");
}

int
update(string str)
{
    object shadow;

    if (!str || str!="membership")
    {
        NF("To update your membership type 'update membership'\n");
        return 0;
    }
    if (!IS_MEMBER(TP))
    {
        write("But you are not a member!\n");
        return 1;
    }
    if (TP->query_guild_name_occ() != GUILD_NAME)
    {
        write("Updating your shadow.\n");
        TP->remove_guild_occ();
        shadow = clone_object(GUILD_SHADOW);
        if ((shadow->shadow_me(this_player(), GUILD_TYPE,
                               GUILD_STYLE, GUILD_NAME)) != 1)
        {
            "secure/master"->do_debug("destroy",shadow);
            write("Hmm... Something is wrong. Please talk to a wiz about this.\n");
            return 1;
        }
    }
    write("Done.\n");
    return 1;
}

int
do_lift(string str)
{
  if(!str || str!="stone")
  {
    NF("What are you trying to lift?\n");
    return 0;
  }
  else
  TP->move_living(" through a trap door in the floor",TYR+"stadium/p1");
  write("You lift the stone and slip down the trap door.\n");
  return 1;
}

int
join(string str)
{
    object cuir, shadow;

    if (str!="training")
    {
        write("Want to what? Enter what?\n");
        return 1;
    }

    if (this_player()->query_guild_member(GUILD_TYPE))
    {
        notify_fail("You can't be a member of two occupational guilds!\n");
        return 0;
    }
    shadow = clone_object(GUILD_SHADOW);
    notify_fail("How odd. For some reason you cannot join us.\n");
    if (shadow->shadow_me(this_player(), GUILD_TYPE, GUILD_STYLE,
        GUILD_NAME)!=1)
    {
        shadow->remove_object();
        return 0;
    }
    this_player()->set_bit(2, 18);
    write("You can now call yourself a true Gladiator.\n");
    cuir = present(CUIR_ID, this_player());
    if (!cuir)
    {
        cuir = clone_object(GLAD_DIR+"cuirasse");
        cuir -> move(this_player());
        write("You receive a cuirasse as a membership token.\n");
        say(QCTNAME(this_player())+" joins the Guild of Gladiators.\n");
	WRITE_LOG(JOIN_LOG, TP, "has just joined the guild.");
    }
    return 1;
}

int
my_leave(string str)
{
    object cuir;

    if (str!="guild")
    {
        notify_fail("What do you wish to leave? The guild?\n");
        return 0;
    }

    if (this_player()->query_guild_name_occ()!=GUILD_NAME)
    {
        notify_fail("You can't leave a guild you are not a member of.\n");
        return 0;
    }
    if (this_player()->remove_guild_occ())
    {
        write("You are no longer a member of the Guild of Gladiators.\n");
	tell_room(this_object(), "The Master kills "+QTNAME(TP)+
		  " for leaving the Guild.\n", TP);
	TP->catch_msg("The Master kills you in one swipe for "+
		      "leaving the Guild.\n");
        this_player()->clear_bit(GLAD_GROUP, GLAD_MEMBER);
        cuir = present(CUIR_ID, this_player());
        if (cuir)
        {
            cuir->remove_object();
            write("Your cuirasse is taken from you.\n");
            say(QCTNAME(this_player())+" leaves the guild.\n");
        }
        this_player()->remove_cmdsoul(GLAD_SOUL);
	this_player()->heal_hp(-100000);
	this_player()->do_die(this_object());
	this_player()->remove_skill(SS_BERSERK);
	this_player()->remove_skill(SS_CHARGE);
	if (this_player()->query_skill(SS_DEFENCE) >5)
	  this_player()->set_skill(SS_DEFENCE, 5);
	this_player()->remove_skill(SS_UNARM_COMBAT);
	this_player()->remove_skill(SS_2H_COMBAT);
	this_player()->remove_skill(SS_PARRY);
	if (this_player()->query_skill(SS_APPR_OBJ) >50)
	  this_player()->set_skill(SS_APPR_OBJ, 50);
	if (this_player()->query_skill(SS_APPR_MON) >50)
	  this_player()->set_skill(SS_APPR_MON, 50);
	if (this_player()->query_skill(SS_WEP_AXE) >30)
	  this_player()->set_skill(SS_WEP_AXE, 30);
	WRITE_LOG(JOIN_LOG, TP, "has just left the guild.");
    }
    else
        write("Because of an error, you remain with us.\n");
    return 1;
}

int
list()
{

    string str;

    str = this_player()->list_major_guilds();
    if (str)
        write("You are a member of the following guilds.\n" + str);
    else
        write("You are not a member of any important guilds.\n");

return 1;
}

int
ask(string str)
{
    object cuir;

    if (str!="cuirasse" && str!="for cuirasse")
        return 0;
    if (!IS_MEMBER(this_player()))
    {
        write("But you are not a member of this guild. "
            + "Only gladiators get a cuirasse.\n");
        return 1;
    }
    cuir = present(CUIR_ID, this_player());
    if (cuir)
    {
        write("Imbecile, you already have a cuirasse.\n");
        return 1;
    }
    cuir = clone_object(GLAD_DIR+"cuirasse");
    cuir -> move(this_player());
    write("You are presented a brand new cuirasse. Keep it safe.\n");
    say(QCTNAME(this_player())+" is given a new cuirasse.\n");
    WRITE_LOG(ASK_LOG, TP, "has just asked for a new cuirasse.");
    return 1;
}
