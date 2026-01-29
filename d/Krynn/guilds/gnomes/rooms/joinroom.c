/* created by Dajala 
 * The gnomes' racial guild main room.
 */

#pragma save_binary

inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include "../modules.h"
#include <macros.h>
#include <ss_types.h>


int free = 2;
object board;

void reset_room();

void
create_room()
{
  set_short("The inventors' guild main chamber");
  set_long("This round cave is the Inventor Guild's main chamber. Its high, "
	   + "dome-like ceiling makes you feel rather small and unimportant. "
	   + "Thick pillars, arranged in a circle, support the dome. The " +
	   "one closest to the entrance looks thicker though. In the " +
	   "middle of the circle, which happens to be the middle of the " +
	   "cave, you see a stone platform with a desk on it. On the desk " +
	   "there lies a leather-bound book. Arrayed " +
	   "around the central platform are wooden benches. Inside the " +
	   "pillars you spot tiny cubicles, and to the southeast is an alcove " +
       "decorated with bunk beds.\n");
  
  add_exit(ROOMS + "galery", "northeast", 0);
  add_exit(ROOMS + "workshop", "west", "@@myexit");
  add_exit(ROOMS + "trainroom", "north", 0);
  add_exit(ROOMS + "planner", "south", "@@myexit");
  add_exit(ROOMS + "common", "common", 0);
  add_exit("/d/Krynn/gnome/shop", "east", 0);

  LIGHT;
  INSIDE;

  add_item(({"platform", "desk"}),
	"Platform and desk are made from one, single stone. Or at least "
	+ "that is what it looks like. The sides of the desk are decorated "
	+ "with beautiful carvings. On the desk there lies a leather-bound "
	+ "book.\n");
  add_item(({"carvings", "carvings on desk", "carving"}),
	"You see different carvings on the four sides of the desk.\n");
  add_item(({"south carving", "first carving"}), 
	"The carving shows the inauguration of the first Head Tinker in "
	+ "this guild taking place right here. The benches are filled with "
	+ "hundreds of gnomes cheering for the an elderly, wizened gnome "
	+ "standing on this side of the desk.\n");       
  add_item(({"west carving", "second carving"}),
	"The carving depicts gnomes at work in the planning chamber of "
	+ "the Inventor guild.\n");
  add_item(({"north carving", "third carving"}),
	"The carving shows the founder of this community, dressed in a long "
	+ "robe, as he enters the cave-system (on foot by that time) "
	+ "accompanied by three other elderly gnomes.\n");
  add_item(({"east carving", "fourth carving"}),
	"The carving depicts gnomes building machines of every description.\n");
  add_item(({"pillar", "pillars", "thick pillar"}),
	"The pillars are thick. It would need six gnomes "
	+ "to form a chain around the thinner ones. On the inside of the "
	+ "thicker one, closest to the northwestern exit, you see a heavy, "
	+ "iron plaque. That's probably the reason why it's thicker! "
	+ "Inside the pillars there are tiny cubicles.\n");
  add_item("plaque",
	   "You can read it.\n");
  add_item("benches",
	"Made from wood they form circles inside the circle "
	+ "of pillars emphasizing the platform as center of the "
	+ "cave.\n");
  add_item(({"ceiling" , "dome"}), "@@my_ceiling");
  add_cmd_item("plaque","read",
	"Here, fellow gnome, you can 'join! the Inventor Guild'. "
	+ "But before you do so, you should read the book on the desk to "
	+ "find out more about us. In case you want to leave again, "
	+ "you have to part with your gizmo. Should you lose it, "
	+ "you can 'receive replacement' here.\n");

  add_item(({"book","the book"}),"The black, leather-bound book is thick. "
		+ "You can read it.\n");
  add_cmd_item(({"book","the book"}),"read",
	  "The book is divided into chapters:\n"
	+ "Chapter 1: The Inventor Guild.\n"
	+ "Chapter 2: What we offer.\n"
	+ "Chapter 3: Tax.\n"
	+ "Chapter 4: Leaving.\n"
  + "Chapter 5: Restoration.\n"
  + "Appendix.\n");
  add_cmd_item("chapter 1", "read",
	"You read:\n"
	+ "The Inventors Guild is devoted to furthering the technological\n"
	+ "progress of the gnomes here in this mountain, in Mount Nevermind\n"
	+ "and all over the world. So a member of this guild shall devote a\n"
	+ "considerable amount of time in thinking, planning and the study of\n"
	+ "science and engineering. A major part of the advancement inside\n"
	+ "the guild can be achieved by inventing.\n");
  add_cmd_item("chapter 2", "read",
	"You read:\n"
	+ "This guild basically offers the following three things:\n"
	+ "1.\nMembers in good standing of the gnome's Inventor Guild may fully\n"
	+ "utilize the guild's facilities.\n"
	+ "2.\nYou will receive your personal gizmo, onto which, once you\n"
	+ "obtained the necessary skill and status within the guild, you can\n"
	+ "attach self-built modules each of which enables you to perform\n"
	+ "specific actions. A list of modules is available in the workshop\n"
	+ "west of here.\n"
	+ "3.\nArmavir, the master inventor, will help you to train a fine\n"
	+ "selection of skills including the special skill BUILD.\n"
	+ "Refer to the appendix for additional information on BUILD.\n\n"
	+ "To join the guild use: join! the inventor guild.\n");
  add_cmd_item("chapter 3", "read",
	"You read:\n"
	+ "We gnomes pride ourselves in our inventions, and such creativity "
	+ "requires a great deal of effort.  We, therefore, suggest that a "
	+ "small tax of " + GNOME_TAX + "% be enforced.\n");
  add_cmd_item("chapter 4", "read",
	"You read:\n"
	+ "Should you desire to leave our fine guild, prepare yourself "
	+ "to 'part with gizmo'.\n");
  add_cmd_item("chapter 5", "read",
	"You read:\n"
  + "In the rare case that you should loose your precious gizmo, do not hesitate "
  + "to ask for help here. You will 'receive replacement' immediately.\n");
  add_item(({"cubicle", "cubicles"}),
	"This is the thought-enhancing facility provided by the guild. As far as\n"
	+ "you can see, all of them are currently in use, but you might still find\n"
	+ "one free for you to enter.\n");
  add_cmd_item("appendix", "read",
	"You read:\n"
	+ "Once trained in the unique skill BUILD you will be able to 'analyze'\n"
	+ "magical objects. You can take them apart to find out more about their\n"
	+ "magical properties. Obviously, the object itself will be lost in the\n"
	+ "process but you will earn invaluable knowledge.\n");

    add_item(({"alcove", "beds", "bunk beds"}), "In the southeast corner of "+
    "this cave room is an alcove decorated with plain bunk beds, you could " +
    "probably 'start here' to awake in this room.\n");
    
  reset_room();
}

void
init()
{
    ::init();
    ADD("join_guild","join!");
    ADD("leave","part");
    ADA("enter");
    ADD("start_here", "start");
    ADA("receive");
}

void
reset_room()
{
    seteuid(getuid());
    if (board)
        return;
    board = clone_object(GOBJ + "noteboard");
   //board->set_fuse(1);
    board->move(TO,1);
}    

string
my_ceiling()
{
    string str, race;
    str = "The high dome-like ceiling makes you feel ";
    race = TP->query_race();
    if(race != "gnome" && race != "hobbit" && race != "dwarf")
	str += " as small as all the gnomes around here.\n";
    else str += " rather unimportant.\n";
    return str;
}

int
myexit()
{
    if(!GMEMBER(TP))
    {
	write("A gnome tells you: 'Sorry,MembersOnly!' and is gone again.\n");
	say(QCTNAME(TP) + " tries to enter the room to the south but is "
		+ "stopped by a gnome.\n");
	return 1;
    }
    return 0;
}

int
fix_member(object player)
{
    int    *gizmo;
    object  ob;
    
    setuid();
    seteuid(getuid());
    
    if (!MANAGER->load_member(player->query_real_name()))
    {
        if (P("k_gizmo", player))
        {
            gizmo = (P("k_gizmo", player))->query_modules();
            (P("k_gizmo", player))->remove_object();
        }
            
        player->remove_guild_race();
        player->remove_autoshadow("/d/Krynn/gnome/guild/obj/race_shadow.c");
        player->remove_autoshadow("/d/Krynn/gnome/guild/obj/race_sha.c");
        player->remove_cmdsoul("/d/Krynn/gnome/guild/kgnome_soul.c");
        player->remove_cmdsoul("/d/Krynn/gnome/guild/obj/kgnome_soul");
        player->update_hooks();
            
        if (clone_object(GNOME_SHADOW)->shadow_me(player,"race","race", GNOME_NAME) > 0)
        {
            if (player->query_default_start_location() == "/d/Krynn/gnome/guild/joinroom")
                player->set_default_start_location(ROOMS + "joinroom");
            
            ob = clone_object(GNOME_OBJ);
            ob->soul(player);
            ob->move(player);
            ob->config();
                
            if (pointerp(gizmo))
                ob->set_modules(gizmo);
             
            player->update_hooks();
            player->add_subloc(KGN_SUB, GNOME_SHADOW);
            MANAGER->add_member(player);
    
            if (player->query_skill(SS_PROMOTE) != MANAGER->query_promote(player))
            {
                MANAGER->set_promote(player, player->query_skill(SS_PROMOTE));
            }
                
            write("You have now moved your research to the new facilites.\n");
            
            return 1;
        }
        else
        {
            write("Please notify " + GUILDMASTERS[0] + ", something went " +
            "wrong when you transferred.\n");
            return 1;
        }
    }
    
    return 0;
}

int
join_guild(string str)
{
    int     result;
    object  ob;

    NF("Join what? The Inventor Guild?\n");
    if (!str)
      return 0;
    if (!(str == "the inventor guild" || str == "the Inventor Guild"))
      return 0;
    
    NF("You are already a member of this guild.\n");
    if (GMEMBER(TP))
      return fix_member(this_player());
    
    NF("Only gnomes are allowed to join the Inventor Guild. We don't "
	+ "allow minor races to become members!\n");
    if (TP->query_race_name() != "gnome")
	return 0;
    NF("You are already a member of another racial guild.\n");
    if (TP->query_guild_name_race())
      return 0;
    NF("You are not yet worthy to join this guild. Ask Armavir for "
		+ "help and a way to prove yourself.\n");
    if (!(TP->test_bit("Krynn",GGUILD_GROUP, GQUEST_BIT)))
      return 0;
   
    
    seteuid(getuid(TO));
    result = (clone_object(GNOME_SHADOW)->shadow_me(TP,"race","race", GNOME_NAME));
    NF("You are already a member of another race guild.\n");
    if (result == 0)
      return 0;
  
    NF("Other guilds you have joined prevent you from joining here!\n");
    if (result == -4)
      return 0;
    
    TP->clear_guild_stat(SS_RACE);
    TP->set_bit(GGUILD_GROUP, GMEMBER_BIT);
    TP->setup_skill_decay();
    ob = clone_object(GNOME_OBJ);
    ob->soul(TP);
    ob->move(TP);
    ob->config();
    TP->update_hooks();
    TP->add_subloc(KGN_SUB, GNOME_SHADOW);
    MANAGER->add_member(TP);
    
    write_file(JOINLOG, ctime(time()) + " " + TP->query_real_name() +
    " has joined the guild.\n");
    
    write("Everybody present, including the gnomes inside the cubicles " +
	"smile at you happily, cheer and congratulate you on joining the " +
	"famous inventors guild.\n");
    say ("Everybody present, including the gnomes inside the cubicles " +
	"smile at " + QTNAME(TP) + " happily, cheer and congratulate " +
	OBJECTIVE(TP) + " on joining the famous inventor guild.\n");
    write("If you wish to start here, you are welcome to do so.\n");
    set_alarm(2.0, -1.0, "join_2", TP);
    return 1;
}

void
join_2(object player)
{
   player->catch_msg("An elderly gnome steps forward and hands your new "
	+ "gizmo to you.\nThe elderly gnome says: WelcomeToOurGuild!\n");
   tell_room(E(player),"An elderly gnome steps forward and hands something "
	+ "to " + QTNAME(player) + ".\nThe elderly gnome says: WelcomeTo"
	+ "OurGuild!\n", player);
}

void
do_leave(object player)
{
    int i;
  
    seteuid(getuid());
        
    player->remove_guild_race();  /* removes shadow */
    player->clear_guild_stat(SS_RACE);
    player->remove_skill(SS_BUILD);
    player->remove_skill(SS_PROMOTE);
    
    if (player->query_default_start_location() == ROOMS + "joinroom.c" &&
        !player->query_wiz_level())
        player->set_default_start_location(player->query_def_start());
    
    player->remove_autoshadow(GNOME_SHADOW);
    player->remove_cmdsoul(GNOME_SOUL);
    player->clear_bit(GGUILD_GROUP, GMEMBER_BIT);
    player->update_hooks();
    player->remove_subloc(KGN_SUB);
    player->setup_skill_decay();
    rm(MEMBER_DIR(player->query_real_name()) + ".o");
    
    write_file(LEAVELOG, ctime(time()) + " " + TP->query_real_name() +
    " has left the guild.\n");
    
    if (P("k_gizmo", player))
    {
        (P("k_gizmo", player))->remove_object();
        if(E(player) == TO)
            player->catch_msg("You hand back your gizmo.\n");
    }
}

int
leave(string str)
{
    NF("Part with what? The gizmo? I hope, you are sure about " +
    "that...\n");
    if (!str)
        return 0;
    if (str != "with gizmo" && str != "with the gizmo")
        return 0;
    NF("You are not a member of this guild.\n");
    if (!GMEMBER(TP))
        return 0;

    setuid();
    seteuid(getuid(TO));

    do_leave(TP);
    write("All the gnomes around in the room, including the many " +
    "in the cubicles, look at you in disbelief, sigh and continue " +
    "with their business, obviously ignoring you on purpose.\n");
    tell_room(TO, QCTNAME(TP) + " leaves the guild and the working all around " +
    "stops immediately. Every gnome present looks at " + QTNAME(TP) +
    " in disbelief, sighs and continues with his business.\n", TP);
    return 1;
}

int
enter(string str)
{
    NF("Enter what?\n");
    if (str != "cubicle")
        return 0;
    
    NF("You enter the cubicle but are repelled by millions of thoughts " +
    "rushing into your brain at high speed. Only a gnomes mind can " +
    "stand or understand them.\n");
    if(TP->query_race_name() != "gnome")
    {
        say(QCTNAME(TP)+ " enters a cubicle but comes out again at once.\n");
        TP->command("confused");
        return 0;
    }
    
    NF("All cubicles are occupied at the moment. You have to wait for one " +
    "to become free\n");
    if (free == 0)
        return 0;
    
    TP->set_stat_extra(3 ,(TP->query_stat_extra(3)) + 10);
    write("You squeeze yourself into a free cubicle.\n");
    
    if (free == 2)
        TP->move_living("into a cubicle", ROOMS + "cubicle1", 1, 0);
    
    if (free == 1)
        TP->move_living("into a cubicle", ROOMS + "cubicle2", 1, 0);
    return 1;
}

void
one_more_free()
{
   free -= 1;
}

int
start_here(string str)
{
    if(!GMEMBER(TP))
        return 0;
    
    NF("Start where? Here?\n");
    if(str != "here")
        return 0;
    
    TP->set_default_start_location(ROOMS + "joinroom");
    write("Ok. From now on you will start here.\n");
    return 1;
}

int
receive(string str)
{
    object gizmo;
    string name, *buffer;
    int i, mem_count, result;
   
    name = (TP->query_real_name()) + ".";
    setuid();
    seteuid(getuid());
   
// Check membership
    NF("A gnome runs by and pops a flag at you. You read:\nMembers only!");
    if(!MANAGER->load_member(this_player()->query_real_name()))
        return 0;
   
    NF("Receive what? A replacement?\n");
    if((str != "replacement") && (str != "a replacement"))
        return 0;

    TP->set_bit(GGUILD_GROUP, GMEMBER_BIT);
    
// Repair missing subloc
    buffer = TP->query_sublocs();
    for(i = 0; i < sizeof(buffer); i++)
        if(buffer[i] == KGN_SUB)
   		{
            result = 1;
            mem_count = 1;
        }
        
    if(result == 1)
	     TP->add_subloc(KGN_SUB, GNOME_SHADOW);
     
    result = mem_count = 0;
    
// Replace missing gizmo and soul
   if(!(P("k_gizmo", TP)))
   {
	    gizmo = clone_object(GOBJ + "gizmo");
	    gizmo->move(TP);
	    gizmo->config();
	    write("You receive a brand new gizmo as a replacement.\n");
	    write("It still gleams and shines but obviously has no modules attached.\n");
	    say(QCTNAME(TP) + " receives a new gizmo.\n");
	    gizmo->soul(TP);
      mem_count = 1;
   }
   
// Replace missing Shadow 
    buffer = explode(read_file(JOINLOG), "\n");
    for(i=0; i < sizeof(buffer); i++)
        if(buffer[i] == GNOME_SHADOW + ":")
            result = 1;
    
    if (result == 1) 
    {
        result = (clone_object(GNOME_SHADOW)->shadow_me(TP,"race","race", GNOME_NAME));
        mem_count = 1;
    }
    
    TP->update_hooks(); 
    TP->setup_skill_decay();
    
    NF("A gnome frowns at you saying:\nNothingToBeDone.PleaseDon'tBotherMeAgain.\n");
    if (mem_count)
        write("A gnome smiles at you saying:\nYouAreFullyRestored.MoreLuckNextTime!\n");
    
    return mem_count;
}
