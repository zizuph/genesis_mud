/*
* Created by: Luther
* Date: Dec 2001
*
* File: /d/Cirath/guilds/militia/room/joinroom.c
* Comments: Militia Joinroom
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
#include "/d/Cirath/tyr/tyr.h"
#define MILITIA_JOIN "_militia_join"

void
reset_room()
{
    object npc = present ("hercule", TO);
    if(!objectp(npc))
    {
        bring_room_mob("guard",MILITIA_NPC + "guard",1,1);
    }
}



void
create_room()
{
        set_short("Guardhouse");
        set_long("You have entered a small guardhouse that stands "
        	+"before a small building with a walled in courtyard.  "
        	+"Inside the courtyard you can see people sparring "
        	+"with staffs and shields.  A desk is present here "
        	+"with a ledger sitting on it.  You also see a large "
        	+"poster on the wall that looks interesting.\n");
        add_item("desk","It is made of stone and wood and looks very "
        	+"sturdy.  A ledger is sitting on it.\n");
        add_item("ledger","It looks to have names scrawled in it.  "
        	+"Apparently they have joined some sort of militia.\n");
        add_item("building","A bland 2 story building made of some form "
        	+"of sandstone.\n");
    add_item("poster","It looks to have a picture and some readable "
    +"text.\n");
        add_cmd_item("poster","read","@@poster");

        INSIDE

		add_exit(MILITIA_ROOM + "m1","northeast");
		add_exit(MILITIA_ROOM + "m7","south");
		add_exit(MILITIA_ROOM + "m8","east");
		add_exit(TYR_WARREN + "rd_vr_05","west");
        reset_room();
}
void init()
{
        ::init();
        add_action("join", "enter");
}
poster()
{
        say(QCTNAME(TP) + " examines the poster on the wall.\n");
        write("The image of a large warrior wielding a spear and "
             +"wearing a shield while standing atop the massive "
             +"wall of Tyr dominates the picture.  At the bottom "
             +"you see some text which reads: \n"
             +"         Join the Tyrian Militia Today!!!\n"
             +"         Learn how to use polearms to spear your enemies!\n"
             +"         Learn how to defend youself properly with a shield!\n"
             +"         We also offer training in basic defensive skills and\n"
             +"         basic wilderness skills.\n\n"
             +"         To join you must first receive backing from a noble \n"
             +"         house in Tyr.  Ask the nobles about us, and they can\n"
             +"         help.  Then just come here, enter service, and you will\n"
             +"         be part of a special brotherhood.\n\n"
             +"		Disclaimer:  We charge our members an 8% tax to learn\n"
             +"		our skills and use our benefits.  We also only allow the\n"
             +"		most moral and good people to remain in our ranks.  \n"
             +"		Should the Militia receive news otherwise, members will\n"
             +"		be exiled.\n");
             
           return 1;

}


int join(string str)
{
  string file;
  object sh;

  NF("Wizards get messed up when they join this way.\n");
  if (TP->query_wiz_level()) return 0;

  NF("Enter what?\n");
  if (str != "service") return 0;

  NF("You already serve the Militia!\n");
  if (IS_TYR_MILITIA(TP)) return 0;

  NF("You may not give your freedom away while your soul is still "+
     "owned by another layman guild.\n");
  if (TP->query_guild_member_lay()) return 0;

  NF("The nobles do not like those who kill the innocent!\n");
  if (TP->query_alignment() < 0) return 0;

  NF("The Militia is in disarray: Tell a wizard.\n");
  if(!(sh=CO(MILITIA_SHADOW))) return 0;
  if (!TP->query_prop(MILITIA_JOIN))
  {
        NF("You have no Noble house backing your application.\n");
        return 0;
  }
  switch(sh->shadow_me(TP, MILITIA_GUILD_TYPE, MILITIA_GUILD_STYLE,
MILITIA_GUILD_NAME))
  {
    case 1:
       write("You sign your name in the large ledger on the desk.  "
	+"You are now a member of the Tyrian Militia, serve us "
	+"well.\n");
        say(QCTNAME(TP)+" just enrolled in the Tyrian Militia.\n");
        break;
    case -4:
        NF("Your other guilds won't let you enroll today.\n");
        return 0;
    default:
        NF("Couldn't join you...please notify a wizard.\n");
        return 0;
  }

        TP->setup_skill_decay();
        TP->clear_guild_stat(SS_LAYMAN);
        TP->add_cmdsoul(MILITIA_SOUL);
        TP->update_hooks();
      clone_object(MILITIA_OBJ + "baldric.c")->move(TP,1);
     write_file(MILITIA_JOIN_LOG, this_interactive()->query_name() +
       " joined the Tyrian Militia.\n");
 return 1;
}

