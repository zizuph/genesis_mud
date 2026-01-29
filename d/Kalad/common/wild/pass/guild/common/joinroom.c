/* This is the main drow guild room. Here you can join, leave and list.
*/

inherit "/lib/guild_support";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#define TO this_object()
#define TP this_player()
#define DROW_GUILD_BIT 1
#define FOURTH_GROUP 4
object guard;
object guard2;
object insignia;

void
create_room()
{

    set_short("Entrance to the Academy");
    set_long("This is the first room of the Drow Academy, here, young "
	+"student hopefuls pledge their lives to Lloth, the Spider Queen. "
	+"The room is dimly lit, with intricate glowing carvings wrapping "
	+"around the room. An altar sits in the middle of the room, a "
	+"goblet sitting in the middle of it. It has two drow priests "
	+"standing at its right and left. Passages open up to the east "
   +"west, from the west comes the sounds of clashing weapons, from "
   +"the east comes naught but silence. A passage to the north "
	+"is also present, but there are two guards with halberds "
	+"guarding the entrance to it.\n");
    add_item(({"room"}),"It is a room carved from stone.\n");
    add_item(({"students"}),"They look like initiates in the Academy "
	+"who are trying to carry out their duties.\n");
    add_item(({"carvings","carving"}),"They are intricate designs resembling "
	+"spiders and spider webs. A strange blue glow seems to emmanate "
	+"from each one.\n");
    add_item(({"altar"}),"It is sitting in the middle of the room. The "
	+"material it is made of is strange, it seems like a mithril "
	+"or adamantine material. There are carvings of spiders on it. "
	+"It seems to have a blood colored stain on it, but the light in "
	+"here is too dim to tell.\n");
    add_item(({"goblet"}),"A silver goblet that is filled with a reddish "
	+"liquid. It looks to have had lots of use.\n");
    add_item(({"passage","passages"}),"There are passages carved from "
   +"stone, and lead east, west, and north.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(DGUILD + "common/trainroom", "west", 0);
    add_exit(DGUILD + "common/libr", "east", 0);
    add_exit(DGUILD + "common/s1", "north", "@@is_member", 0, 2);
    add_cmd_item("sign","read","Here you can "
        + "join or leave the Drow Academy. If you enter the schooling, "
        + "you will have to pledge your life to Lloth, the Lady of Spiders. "
        + "To join you must <offer soul> to Lloth and to leave, you must "
        + "<revoke pledge> if you revoke your pledge, Lloth will be "
        + "displeased, and will drain some of your experience and skills"
        + "from you. Other things you can do are <list> your guilds, "
	+ "<update membership>, and <request> another insignia.\n");
set_alarm(1.0,0.0,"reset_room");
   insignia = clone_object(DGUILD + "obj/insignia");
}
void
init()
{
    ::init();
    add_action("do_try","try");
    add_action("do_try","offer");
    add_action("my_leave", "revoke");
    add_action("request", "request");
    add_action("list", "list");
   add_action("make", "make");
    add_action("update","update");
}
do_try(string str)
{
    object shadow,insignia;
    int i;
    object *souls;

    if(str == "soul")
      {

     if (TP->query_race_name() != "human" && "elf")
          {
            notify_fail("You are an inferior race, please leave our guild.\n");
            return 0;
          }
/*
        if (!(driftwood = present("driftwood", TP))){
          write("You must seek the wood which flows with the currents.\n");
          return 1;
        }
*/

        if (TP->query_guild_member(GUILD_TYPE))
          {
	  notify_fail("Lloth only accepts total submission, you "
		+"may not be a member of any other guild and be "
		+"in her Academy. "
                        + "Imbecile! Begone before Lloth feasts on "
			+ "you blood\n");
            return 0;
          }

        shadow = clone_object(GUILD_SHADOW);
        notify_fail("How odd. For some reason you cannot seem to enter "+
                    "schooling. Please leave a bug report here.\n");
        if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
                              GUILD_NAME)!=1)
        {
            shadow->remove_object();
            return 0;
        }
        TP->set_bit(FOURTH_GROUP,DROW_GUILD_BIT);
        write("You have entered the Drow Academy. Praise Lloth!\n");

        log_file("hobbits",TP->query_real_name()+" joined "+
                 extract(ctime(time()),4,15)+".\n");
/*
       if (driftwood = present("driftwood", TP)){
            driftwood->remove_object();
*/

        TP->add_cmdsoul(DROW_SOUL);

        seteuid(getuid(TO));
        souls = TP->query_cmdsoul_list();
        for (i = 0; i < sizeof(souls); i++)
            TP->remove_cmdsoul(souls[i]);
        TP->add_cmdsoul(DROW_SOUL);
        for (i = 0; i < sizeof(souls); i++)
            if (souls[i] != DROW_SOUL)
                TP->add_cmdsoul(souls[i]);

        TP->update_hooks();
        insignia = present("insignia", TP);
        if (!insignia)
        {
            insignia = clone_object(DGUILD + "insignia");
            insignia -> move(TP);
   write("The blood in the goblet begins to froth, and a glowing "
	+"insignia rises from it, naming you as a member of the Academy "
	+"You quickly take the insignia and fasten it around your neck.\n");
        }
        return 1;
     }
    return 0;
}

my_leave(string str)
{
    object insignia;
    int result;
    object sould;



    if (str!="pledge")
    {
        write("What do you wish to revoke?\n");
        return 1;
    }

    if (this_player()->query_guild_name_lay()!=GUILD_NAME)
    {
        notify_fail("You cannot leave the Academy if you never entered!\n");
        return 0;
    }
    if (TP->remove_guild_lay())
    {
        write("You are no longer a member of the Academy. Go forth "
	+"in shame.\n");
        this_player()->clear_bit(FOURTH_GROUP,DROW_GUILD_BIT);
       insignia = present("insignia", TP);
        if (insignia)
        {
            insignia->remove_object();
    write("The anger of Lloth has come upon you, leave our guild and "
	+"never return! If you enter here again, you will be attacked "
	+"slain without remorse.\n");
            say(QCTNAME(TP) + " has "+ TP->query_possessive() +" insignia destroyed.\n");
            log_file("hobbits",TP->query_real_name()+" left   "+
                     extract(ctime(time()),4,15)+".\n");
        }
        TP->remove_cmdsoul(DROW_SOUL);
        TP->update_hooks();
    }
    else
        write("You cannot escape the grasp of Lloth! Please make "+
              "a bug report in this room.\n");
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
request(string str)
{
    object insignia;

    if (str!="insignia" && str!="my insignia")
        return 0;
    if (TP->query_guild_name_lay()!=GUILD_NAME)
    {
        write("But you are not a member of this guild. "+
                "Only true drow may receive their replacement "+
                "insignias.\n");
        return 1;
    }
    insignia = present("insignia", TP);
    if (insignia)
    {
        write("You already have an insignia fool!\n");
        return 1;
    }
    insignia = clone_object(DGUILD + "insignia");
    insignia -> move(TP);
    write("You are presented with a brand new insignia.\n"
         + "Be more careful next time, Lloth hates incompetence.\n");
    say(QCTNAME(TP)+" is given "+ TP->query_possessive() +" insignia back.\n");
    return 1;
}
/*
make()
{
   if (IS_MEMBER)
   {
        clone_object(DGUILD + "driftwood")->move(TP);
        write("You get a small piece of driftwood to induct "+
              "a new member.\n");
        return 1;
    }
    write("You are not a member here, begone before Lloth devours you!\n");
    return 1;
}
*/
void
soul(object ob)
{
    object spells;
    int i;
    string *souls;

    seteuid(getuid(TO));
    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
        ob->remove_cmdsoul(souls[i]);
    ob->add_cmdsoul(DROW_SOUL);
    for (i = 0; i < sizeof(souls); i++)
        if (souls[i] != DROW_SOUL)
            ob->add_cmdsoul(souls[i]);
    ob->update_hooks();
}

int
update(string str)
{
    object shadow;

    if (!str || str != "membership")
    {
        notify_fail("Update what?\n");
        return 0;
    }

    if (!IS_MEMBER && TP->query_guild_name_race()!=GUILD_NAME)
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    if (!IS_MEMBER)
    {
        write("Updating bit.\n");
        TP->set_bit(FOURTH_GROUP,DROW_GUILD_BIT);
        if (TP->test_bit("Kalad",FOURTH_GROUP,DROW_GUILD_BIT))
            if (TP->query_guild_name_occ() != "Vampyre Guild")
                TP->clear_bit(FOURTH_GROUP,DROW_GUILD_BIT);
    }

    if (TP->query_guild_name_race()!=GUILD_NAME)
    {
        write("Updating shadow.\n");
        shadow = clone_object(GUILD_SHADOW);
        if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,GUILD_NAME)!=1)
        {
 write("Couldn't update your shadow. Please contact a wizard about this.+n");
            shadow->remove_object();
        }
    }

    write("Done!\n");
    return 1;
}
reset_room()
{
if (!guard || !guard2)
        {
guard = clone_object(DGUILD + "npc/guard");
guard->move_living("xxx", TO);
guard2 = clone_object(DGUILD + "npc/guard");
guard2->move_living("xxx", TO);
guard->team_join(guard2);
guard2->team_join(guard);
        }
}

is_member()
{
    object *ob;
    int pres,i;
if(IS_MEMBER){
return 0;
    }
    if (this_player()->query_guild_name_race()==GUILD_NAME)
        return 0;

   if (insignia = present("house insignia", TP)){
        return 0;
    }

    ob = FILTER_LIVE(all_inventory(this_room()));
    pres = 0;
    for (i = 0; i < sizeof(ob); i++){
if (ob[i]->query_name() == "Guard"){
            pres = 1;
        }
    }
    if (pres == 1){
        write("The guards cross their halberds, preventing you from going that way.\n");
        say("The guards cross their halberds, preventing you from going that way.\n");
    }

    return pres;
}
