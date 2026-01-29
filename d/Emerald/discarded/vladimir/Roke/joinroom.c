/* This is the main hobbit guild room. Here you can join, leave and list.
*/

inherit "/lib/guild_support";
inherit "/std/room";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/bits.h"
#include "/d/Shire/hobbit/hobbitdefs.h"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#define TO this_object()
#define TP this_player()



string title;
object driftwood;


void
create_room()
{

    set_short("A rustic room");
    set_long("This is an old, rustic room. The floor is made of some "+
             "sort of wood arranged in a block pattern. There are torches "+
             "mounted firmly to each wall, giving the room a magnificant "+
             "glow. There is a small hole in the wall with a sign just "+
             "above it. There are seven paintings standing prominantly on "+
             "the wall.\n");
    add_item(({"pictures","paintings"}), "To look at each individual painting "+
               "try to examine first painting, second painting, etc etc.\n");
    add_item(({"first painting"}), "This is a painting of a strong elven "+
               "wizard. He is depicted giving money to lonely, poor hobbits. "+
               "On the bottom of the painting are the words:\n" 
             + "Lord Dunstable Hurin, Mayor of the Shire and friend of hobbits.\n");
    add_item(({"second painting"}), "You notice this is a painting of a "+
               "fellow hobbit. He is depicted as eating large amounts of food "+
               "from a enormous banquet table. Across the bottom of the picture "+
               "are the words:\n"
             + "Sir Dondon The Windlord Of The Shires.\n");
   add_item(({"third painting"}), "A small female gnome is shown within "+
               "this particular painting. She seems to be in a room with "+
               "many books. It looks like she is writting a new one now. "+
               "The following words cover the bottom of the painting:\n"
             + "Dame Anri the beloved scribe of Michel Delving.\n");
   add_item(({"fourth painting"}), "While grasping stars in the sky and "+
               "balancing the planets on his shoulders, a purple-haired gnome "+
               "looks fierce and mysterious. You notice the following "+
               "written on the bottom of the painting:\n"
             + "Sir Astro the Master of the Stars.\n");
   add_item(({"fifth painting"}), "This is a picture of a dwarf that "+
              "seems to be casting a powerful spell. Globes of white "+
              "swirl around him. There is mist everywhere. Below the "+
              "painting is an inscription:\n"
            + "Sir Dain High White Wizard of the Shire.\n");
   add_item(({"sixth painting"}), "Black paint covers the scene. "+
              "A grim human wizard stands enshrouded in black. He "+
              "looks up, glaring at you.\n"
            + "You feel eery presence.\n"
            + "Sir Odin Friend of the Lord, the Blind Sorcerer, the "+
              "Fifth, the Far King, Black Numenorean, Ruler of the "+
              "Deeps.\n");
   add_item(({"seventh painting"}), "A beautiful elf stands amongst "+
              "a room filled with various swords. She holds a wicked "+
              "sword above her head. The words:\n"
            + "Dame Shanna Mistress of the Swords.\n"
            + "are written across the bottom.\n");
   add_item(({"hole"}), "It seems very small, about the size of your pipe.\n");
    
    add_prop(ROOM_I_INSIDE, 1);


    add_exit(HOBGLD_DIR + "hall", "south", 0);

    add_item(({"sign"}),"Here you can "
        + "join or leave the Nimblefingered Hobbits Guild. "
        + "To join, you must <start smoking> or <break habit> "
        + "to quit our family. You can also do "
        + "<update membership>. Members can"
        + " <request> to have their pipes back."
        + " join.\n");

    add_cmd_item("sign","read","Here you can"
        + "join or leave the Nimblefingered Hobbits Guild. "
        + "To join, you must <start smoking> or <break habit> "
        + "to quit our family. You can also do "
        + "<update membership>. "
 + "You may also <list> to see what guilds you are already a part of."      
        + " Members can"
        + " <request> to have their pipes back."
        + " join.\n");
}

void
init()
{
    ::init();
    add_action("do_try","try");
    add_action("do_try","begin");
    add_action("my_leave", "break");
    add_action("request", "request");
    add_action("list", "list");
   add_action("make", "make");
    add_action("update","update");
}


do_try(string str)
{
    object shadow,pipe;
    int i;
    object *souls;

    if(str == "smoking")
      {
	
        if (TP->query_race_name() != "hobbit")
	  {
	    notify_fail("You are not a hobbit, please leave our guild.\n");
	    return 0;
	  }
	
	if (!(driftwood = present("driftwood", TP))){
	  write("You must seek the wood which flows with the currents.\n");
	  return 1;
	}
	
	
        if (TP->query_guild_member(GUILD_TYPE))
	  {
            notify_fail("You cannot be a member of two racial guilds!\n"
			+ "Geeze! What were you thinking?\n");
	    return 0;
	  }
	
        shadow = clone_object(GUILD_SHADOW);
        notify_fail("How odd. For some reason you cannot seem to pick "+
                    "up the habbit. Please leave a bug report here.\n");
        if (shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
                              GUILD_NAME)!=1)
        {
            shadow->remove_object();
            return 0;
        }
        TP->set_bit(FOURTH_GROUP,HOBBIT_GUILD_BIT);
        write("You have now become a habitual pipe smoker.\n");

        log_file("hobbits",TP->query_real_name()+" joined "+
                 extract(ctime(time()),4,15)+".\n");


        if (driftwood = present("driftwood", TP)){
            driftwood->remove_object();
        }

        TP->add_cmdsoul(HOBB_SOUL);

        seteuid(getuid(TO));
        souls = TP->query_cmdsoul_list();
        for (i = 0; i < sizeof(souls); i++)
            TP->remove_cmdsoul(souls[i]);
        TP->add_cmdsoul(HOBB_SOUL);
        for (i = 0; i < sizeof(souls); i++)
            if (souls[i] != HOBB_SOUL)
                TP->add_cmdsoul(souls[i]);

        TP->update_hooks();

        pipe = present("pipe", TP);
        if (!pipe)
        {
            pipe = clone_object(HOBGLD_DIR + "pipe");
            pipe -> move(TP);
   write("You hear a soft rattling sound coming from the hole "+
         "in front of you. Eventually, a pipe comes sliding from "+
         "inside the hole, into your hands.\n"
       + "You pick it up, light it, and take a long drag.\n");
            say(QCTNAME(TP) + " Takes a pipe from the hole in the "+
                    "wall and begins to smoke it, immediately.\n");
        }
        return 1;
}
    return 0;
  }

my_leave(string str)
{
    object pipe;
    int result;
    object sould;



    if (str!="habit")
    {
        write("What do you wish to break?\n");
        return 1;
    }

    if (this_player()->query_guild_name_race()!=GUILD_NAME)
    {
        notify_fail("You cannot stop smoking, when you never started!\n"); 
        return 0;
    }
    if (TP->remove_guild_race())
    {
        write("You are no longer a habitual smoker.\n");
        this_player()->clear_bit(FOURTH_GROUP,HOBBIT_GUILD_BIT);
       pipe = present("pipe", TP);
        if (pipe)
        {
            pipe->remove_object();
    write("Your pipe is ripped from your hands and destroyed "+
          "right before your eyes. You have a feeling of overwhelming "+
          "deppression come over you, like the roll of thunder.\n");
            say(QCTNAME(TP) + " has "+ TP->query_possessive() +" pipe destroyed.\n");
            log_file("hobbits",TP->query_real_name()+" left   "+
                     extract(ctime(time()),4,15)+".\n");
        }
        TP->remove_cmdsoul(HOBB_SOUL);
        TP->update_hooks();
    }
    else
        write("You cannot seem to break the habit! Please make "+
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
    object pipe;

    if (str!="pipe" && str!="my pipe")
        return 0;
    if (TP->query_guild_name_race()!=GUILD_NAME)
    {
        write("But you are not a member of this guild. "+
                "Only the Nimblefingered ones may receive their "+
                "pipes back.\n");
        return 1;
    }
    pipe = present("pipe", TP);
    if (pipe)
    {
        write("You already have a pipe silly!\n");
        return 1;
    }
    pipe = clone_object(HOBGLD_DIR + "pipe");
    pipe -> move(TP);
    write("You are presented with a brand new pipe!\n"
         + "You relax, sit back and take a loooooong drag.\n");
    say(QCTNAME(TP)+" is given "+ TP->query_possessive() +" back.\n");
    return 1;
}
make()
{
   if (IS_MEMBER)
   {
        clone_object(HOBGLD_DIR + "driftwood")->move(TP);
        write("You get a small piece of driftwood to induct "+
              "a new member.\n");
        return 1;
    }
    write("You are not a member, silly you!\n");
    return 1;
}

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
    ob->add_cmdsoul(HOBB_SOUL);
    for (i = 0; i < sizeof(souls); i++)
        if (souls[i] != HOBB_SOUL)
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
        TP->set_bit(FOURTH_GROUP,HOBBIT_GUILD_BIT);
        if (TP->test_bit("Shire",FOURTH_GROUP,HOBBIT_GUILD_BIT))
            if (TP->query_guild_name_occ() != "Vampyre Guild")
                TP->clear_bit(FOURTH_GROUP,HOBBIT_GUILD_BIT);
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

