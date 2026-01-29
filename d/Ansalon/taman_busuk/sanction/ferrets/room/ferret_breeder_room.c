/*
 * ferret_breeder_room.c
 * First room in the ferret shack, has NPC that sells stuff and gives
 * hints to quest.
 * 
 * Ares, July 2004
 * Mirandus February 19th, 2015 - Updated strings for quest
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "../defs.h"

inherit SANCINROOM;
inherit "/d/Ansalon/lib/pub";

object ferret_toy;
object ferret_toy2;
object ferret_toy3;
object deanak;

int did_quest1;
int did_quest2;
int do_open(string str);
int do_fetch(string str);

void
reset_sanction_room()
{
   if(!objectp(ferret_toy))
      {
      ferret_toy = clone_object(OBJ_DIR + "ferret_toy");
      ferret_toy->move(this_object());
      }
      if(!objectp(ferret_toy2))
      {
      ferret_toy2 = clone_object(OBJ_DIR + "ferret_toy2");
      ferret_toy2->move(this_object());
      }
      if(!objectp(ferret_toy3))
      {
      ferret_toy3 = clone_object(OBJ_DIR + "ferret_toy3");
      ferret_toy3->move(this_object());
      }
   if(!objectp(deanak))
      {
      deanak = clone_object(NPC_DIR + "deanak");
      deanak->move(this_object());
      }
   did_quest1 = 0;
   did_quest2 = 0;
      
}

void
create_sanction_room()
{
    set_short("A strong smelling ferret breeding room");
    set_long("This is the rundown home of a ferret breeder. "+
    "Three six-foot high cages cover the far wall and contain "+
    "dozens of ferrets. The floor is littered with a disgusting "+
    "mixture of fur, small toys and feces, especially in the corners. "+
    "Near the entrance there is a desk with a small jar of toothpicks "+
    "and a small plaque sitting on it. Behind the desk is a large bin "+
    "with many long pikes in it. Above the cages is a dusty sign. "+
    "There is a door near the back of the room. \n");
    
    add_item(({"cage", "cages"}),
    "These cages are filled with about four dozen ferrets. "+
    "The cages have toys for the ferrets to play with, "+
    "hammocks for them to rest in, several levels to play on, "+
    "and tunnels that connect the three cages. Surprisingly, "+
    "the cages are in good condition and are very clean, obviously "+
    "the owner cares more about the appearance of these cages and "+
    "the well-being of the ferrets than he does the appearance "+
    "of the shack you stand in. \n");
    
    add_item(({"tunnels", "levels"}),
    "Tunnels weave in and out of the cages. They go up and down "+
    "to different levels in the cage. These just add to the exciting life "+
    "that a ferret has when stuck in a cage. \n");
    
    add_item(({"hammock", "hammocks"}),
    "You count nine hammocks in the cages, each of them has a ferret or two "+
    "sleeping in it. This is where they spend most of their time "+
    "everyday, dead asleep. \n");
    
    add_item(({"bin", "pikes"}),
    "A large dirty bin is set in the corner behind the desk. In it are "+
    "several pikes.  Perhaps you can purchase some pikes from the "+
    "current resident? \n");
    
    add_item(({"jar of toothpicks", "toothpicks", "jar", "small jar"}),
    "A little jar of toothpicks, the only clean thing in this whole "+
    "room other than the ferret cages. \n");
    
    add_item(({"ferrets"}),
    "You see many ferrets inside the cages. Most are asleep, but "+
    "there are one or two that are looking at you and wondering why "+
    "you're in their litter box.  \n");
    
    add_item(({"plaque", "small plaque"}),
    "A small plaque sits on the desk. You can read it if you want to. \n");
    
    add_item(({"dusty sign", "sign"}),
    "There is a sign caked with dust above the ferret cages. "+
    "Perhaps you should read it? \n");
    
    add_cmd_item("plaque","read","@@read_plaque");
    add_cmd_item("sign", "read","@@read_sign");
    add_cmd_item("dusty sign", "read","@@read_sign");
    
    add_item(({"desk"}),
    "A small desk with four drawers. It has a plaque sitting on it. "+
    "There is also a small jar of toothpicks. "+
    "All along the desk there are small bite marks. \n");
    
    add_item(({"marks", "bite marks"}),
    "When out of their cages, ferrets can be quite the pest. If it isn't a "+
    "clump of fur on the ground or using a corner to relieve themselves, "+
    "a ferret has only one other way of marking their territory - their teeth. "+
    "Baby ferrets are especially prone to biting anything in their path. \n");
    
    add_item(({"drawer", "drawers"}),
    "There are four drawers in this desk. Three are locked and one isn't so you "+
    "could open it if you wish. \n");
    
    add_item(({"document", "documents"}),
    "There are six total. Each is titled: -*-Rodent Death Certificate-*- and goes "+
    "on to list a name. \n");
    
    add_item(({"toys", "feces", "corners", "fur", "floor"}),
    "This floor hasn't been swept for a while and needs it badly. "+
    "Ferret toys litter the floor, obviously they get a lot of "+
    "play time outside their cages. In every corner of the room, "+
    "there is ferret feces stacked a good six inches high. "+
    "There are also clumps of fur everywhere on the floor. \n");
    
    add_drink_object(({"meat","ferret meat"}),
    "/d/Ansalon/taman_busuk/sanction/ferrets/obj/ferret_meat.c", 24);
    
    add_drink_object(({"pike"}),
    "/d/Ansalon/taman_busuk/sanction/ferrets/obj/pike.c", 1728);

    
    add_exit(ROOM_DIR + "ferret_backroom", "backroom");
    add_exit(ROOM_DIR + "ferret_kitchen", "kitchen");
    add_exit("/d/Ansalon/taman_busuk/sanction/room/city/street17.c", "west");
    
    reset_sanction_room();
}

void
init()
{
    ::init();
    add_action(do_open,"open");
    add_action(do_fetch,"fetch");
    init_pub();
    
}

string
read_plaque()
{
    return "The small plaque reads: \n"+
      "OFFICER DEANAK JONIKUS \n";
}

string
read_sign()
{
    return "The sign reads: \n \n"+
    "PET FERRETS - 2 GOLD \n"+
    "FERRET MEAT - 2 SILVER \n"+
    "STURDY PIKE - 1 PLATINUM \n\n";
}

int
do_open(string str)
{
    notify_fail("Open what?\n");
    if((!str) || (!strlen(str)) || (str != "drawer"))
        return 0;

    if(did_quest1)
    {
        write("You have already done this, no need to do it again. \n");
        return 1;
    }

    did_quest1=1;

    write("You open the drawer but it is broken! Parts of the drawer fall to "+
        "to the ground. With that drawer gone, you can see into one of the "+
        "locked drawers. You see several papers inside that you could fetch. \n");
    say(QCTNAME(TP)+" pulls out the drawer but it's broken and falls to the "+
        "floor with a clatter.\n");

    reset_euid();

    clone_object(OBJ_DIR + "broken_drawer")->move(TO);

    return 1;
}

int
do_fetch(string str)
{

    object ob;
   
    string *names = ({ "SLICK", "LILLY", "CURLS", "ELMANTIA", "MISS LADY", "SIR IKE" });
    int k;
    k = sizeof(names);
    
    notify_fail("Fetch what?\n");
    if((!str) || (!strlen(str)) || (str != "papers from locked drawer")
		&&(str != "papers") && (str != "papers from drawer"))
        return 0;

    if(did_quest2)
    {
        write("The drawer is empty. \n");
        return 1;
    }

    did_quest2=1;

    write("You get on your hands and knees and reach into the exposed drawer. "+
        "With much effort, you pull out six papers. \n");
    say(QCTNAME(TP)+" reaches into the exposed drawer and pulls some papers out. \n");

    reset_euid();
    
    while (k--)
    {
        ob = clone_object(OBJ_DIR + "paper");
        ob->set_ferret_name(names[k]);
        ob->move(this_player());
    }

   
    

    return 1;
}


