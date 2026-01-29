// file name:	waitress.c
// creator(s):	Ilyian (Feb, 1995)
// last update: Lilith, Sep 2021: added chats and asks for Sair Shrine quest
//              Feb, 1996, Cirion: added functions for the hat quest
//		        Denis, May'97: Obsolete code updates.
// purpose:     Waitress for the stormy Haven pub
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/paths.h"
# include "/d/Avenir/include/relation.h"
# include "/d/Avenir/common/port/hat_quest.h";
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
# include <macros.h>
# include <wa_types.h>

inherit "/std/monster";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/spy_npc";
inherit "/d/Avenir/inherit/givetask";
int busy, alarm_id, i;

string *type = (({"beret", "bonnet", "cap", "fedora"}));
string *color = (({"black", "white", "blue", "red", 
          "green", "yellow", "pink", "purple", "raspberry"}));
string *style = (({"fashionable", "simple", "tasteful"}));
string *mat = (({"velvet", "silk", "felt", "lace"}));

string mytype, mycolor, mymat, mystyle;

void      hat_fly_away();
int       busy(int how_long);
void      unbusy();
void      lose_hat();
void      init_quest();

string    ask_about_material();
string    ask_about_color();
string    ask_about_style();
string    ask_about_type();
string    ask_about_hat();
void      reward(object player);

string
my_long()
{
    string str;
    
    str = "This cute little 'thang is bouncing from "+
          "table to table, tidying up and helping customers.\n";

    if (IS_SYBARITE(TP) > 2)
    {
        str += "If you ask nicely, she might be inclined to 'report' "+
               "to you what she has seen today.\n";
    }
    return str;
}

void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name(({"bakona" , "waitress" , "grunshk"}));
    set_title("Grunshk, Head Waitress of the Stormy Haven");
    set_race_name("goblin");
    set_living_name("bakona");
    set_adj("voluptuous");
    add_adj("green-eyed");
    set_gender(G_FEMALE);
    set_long(my_long);

    set_stats(({60, 35, 40, 27, 27, 27}));
    set_alignment(100);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(8);
    add_chat("Hello there, Hon!");
    add_chat("Y'all want a drink now?");
    add_chat("You stand over there by the fire now and warm those "+
             "little bones.");
    add_chat("You be careful out there, hear? You don't want to fall "+
             "over that nasty little ledge..");
    add_chat("Try some of our new imports from Minas Morgul.");
    add_chat("Watch out. There are thieves around here.");
	add_chat("I noticed there was a bit of crumbling happening on one of "
	    +"the walls. I best be gettin to Sair's Shrine to make an offering "
		+"soon.");

    set_act_time(10);
    add_act("emote takes a mug from a table and sets it back over the bar.");
    add_act("wink all");
    add_act("emote throws another log on the fire.");
    add_act("sit on chair");
    add_act("stand");

    add_act("@@hat_chat");

    set_cact_time(10);
    add_cact("scream");
    add_cact("pout");
    add_cact("panic");

    set_cchat_time(5);
    add_cchat("Please, no! Don't hurt me!");
    add_cchat("Your Mama nevuh raised you right!");
    add_cchat("There go your chances for a free drink...");

    add_ask(({"Heboba","heboba"}),"say Ahh, Heboba is a hatmaker "
           +"down in the bazaar. Her work is very fine!",1);
 
    add_ask(({"bazaar"}),"say Hmm ... to get to the bazaar you need "
           +"to go down along the ledge and through the outpost and "
           +"catch the ferry across the dark sea.", 1);

    add_ask(({"what kind", "kind of hat", "type of hat", "specifics",
              "be specific", }),
              "say Oh dear, there are so many styles, materials, and "+
              "colours. Let me think a moment, then ask me for them.", 
              1);
    add_spy_ask();
    spy_auto_intro();
    add_ask(({"style","styles","what style","about style"}),
                VBFC_ME("ask_about_style"));

    add_ask(({"color","colors","what color","about color",
             "colour","colours","what colour","about colour"}),
                VBFC_ME("ask_about_color"));

    add_ask(({"material","materials","what material","about material"}),
                VBFC_ME("ask_about_material"));

    add_ask(({"type","types","what type","about type"}),
                VBFC_ME("ask_about_type"));

    add_ask(({ "hat", "hats", "turban", "beret", "about hat", "about hats",
			 "task", "quest", "help", "assignment" }),
		  VBFC_ME("ask_about_hat"));
    add_ask(({"sair"}), "say Sair is the goddess of the First Hour. She's "
	    +"what keeps walls together and buildings from falling." ,1);
	add_ask(({"shrine", "sairs shrine"}), "say It's located high up in the "
        +"cavern wall. You can only get there if She brings you there.", 1);
    add_ask(({"how to get to shrine"}), "say The only way you're going "
        +"get there is by finding the right one of Sair's Walls.", 1);
    add_ask(({"sairs wall", "sairs walls", "wall", "walls"}), "say When we "
        +"build or excavate walls we carve octagons in them sometimes. If "
        +"you take the time to look carefully, you can find one.", 1);
    add_ask(({"right wall", "wall to shrine"}), "say Ah well that's not my "
        +"place to tell you that. Find a wall with an octagon and use her "
        +"gem. It can take a few tries, so dont give up.", 1);
    add_ask(({"octagon", "octagons"}), 
	    "say The octagon is the symbol of Sair. That and those gemstones "
		+"are sacred to Her.", 1);
    add_ask(({"gem", "gems", "gemstones", "sacred gemstones"}), "say Not "
        +"to be rude, but... you aren't very observant, are you?", 1);	
    add_ask(({"catacombs", "necronisi", "banshee"}), "say The only way to get "
        +"to the Necronisi is if you're dead... or laying in a coffin and "
        +"pretending to be dead.", 1);		

	 init_quest();
}

public void
equip_me()
{
	 seteuid(getuid());
	 MONEY_MAKE_SC(random(25))->move(this_object());
	 MONEY_MAKE_CC(random(40))->move(this_object());
	 clone_object(PORT + "obj/hat.c")->move(this_object());
	 command("wear hat");
}

string
hat_chat()
{
	 if (present("hat", TO))
	 {
		  switch(random(3))
		  {
		  case 1:
				return "smile cheer";
				break;
		  case 2:
				return "bounce joyf";
				break;
		  default:
				return "curtsey";
				break;
		  }
	 }
	 switch(random(3))
	 {
	 case 1:
		  return "say I lost my hat over the ledge.";
		  break;
	 case 2:
		  return "say I hear Heboba makes wonderful hats! I wish I had one.";
		  break;
	 default:
		  return "ponder what she is going to do without her hat.";
		  break;
	 }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
	 switch(emote)
	 {
	 case "frown":
		  set_alarm(3.0, 0.0, &command("say What's wrong, " +
					 actor->query_nonmet_name() + "?"));
		  set_alarm(4.0, 0.0, &command("say You look like y'all could use " +
					  "a drink.."));
	break;
	 case "giggle":
	set_alarm(3.0, 0.0, &command("smile sweet at " +
					  actor->query_real_name()));
	break;
	 }
}

/* ********QUEST FUNCTIONS ********** */

void
init_quest()
{
	 mytype = type[random(sizeof(type))];

	 mystyle = style[random(sizeof(style))];
	 mycolor = color[random(sizeof(color))];
	 mymat = mat[random(sizeof(mat))];
}

void
unbusy()
{
	 remove_alarm(busy);
	 busy = 0;
	 return;
}

int
busy(int how_long)
{
	if (get_alarm(alarm_id) || query_attack() || busy)
		 return 1;

	busy = set_alarm(itof(how_long), 0.0, unbusy);
	return 0;
}

void lose_hat()
{
	 if (!busy(50) && present("hat", TO))
	 {
		  i = 0;
		  alarm_id = set_alarm(2.0, 4.0, hat_fly_away);
	 }
}

void hat_fly_away()
{
	 object hat;

	 i++;
	 switch(i)
	 {
	 case 1:
		  set_act_time(900);
		  set_chat_time(900);
		  command("emote sweeps some dirt out of the doorway.");
		  break;
	 case 2:
		  command("stand");
		  move_living("south", PORT+"port10");
		  break;
	 case 3:
		  command("emote starts sweeping some dirt over the ledge.");
		  break;
	 case 4:
		  tell_room(ENV(TO), "A great gust of wind suddenly blows "
								  +"along the ledge.\n");
		  command("remove hat");
		  command("emote loses her hat to the wind.");
		  break;
	 case 5:
		  hat = present("hat",TO);
		  if (!hat)
		 return;
		  tell_room(ENV(TO), "The " + hat->short() + " slowly drifts down "
								  +"to the dark sea below.\n");
		  hat->remove_object();
        break;
    case 6:
        command("swear");
        command("swear");
        command("swear");
        command("swear");
        break;
    case 7:
        command("sniff");
        break;
    case 8:
        command("sigh sadly");
        break;
    case 9:
        command("emote looks sadly down the side of the cliff.");
        break;
    case(10):
        move_living("north", PORT+"pub");
        break;

    default:
        set_act_time(10);
        set_chat_time(8);
        command("sit on chair");
        command("cry");
        init_quest();
        remove_alarm(alarm_id);
        alarm_id = 0;
        break;
    }
}

string
ask_about_material()
{
    command("sigh dream");
    command("say They are all so nice, but I think I like "
           +mymat+" the best.");
    return "";
}

string
ask_about_color()
{
    command("say Oh, I love most colours.");
    command("say But I think I like "+mycolor+" best.");
    return "";
}

string
ask_about_style()
{
    command("ponder");
    command("say Hmm .. there are so many different styles...");
    command("say I think I would want something "+mystyle+", though.");
    return "";
}

string
ask_about_type()
{
   command("scratch");
   command("say There are lots of different types, you know.");
   command("say I would want a "+mytype+" if I had to pick.");
   return "";
}

string
ask_about_hat()
{
    if (present("hat", TO))
    {
        command("say Hats are wonderful, aren't they?");
        command("smile coy");
        return "";
    }
    if(TP->test_bit("Avenir",GROUP,BIT))
    {
        command("say It was awfully nice of you to bring "
					+"me a hat before.");
		  command("say I really couldn't ask you to do it again...");
		  command("say But wait...");
		  check_group_one(TP, ({0, 0, 0, 0}));
		  return "";
	 }

	 command("sigh sadly");
	 command("say I lost my hat over the ledge when I was sweeping "
			  +"the floor.");
	 command("say I loved my hat, and now my head will get cold on "
			  +"the way home.");
	 command("say Maybe you could go and fetch me another one? I "
			  +"hear there is a hatshop in the bazaar.");
	 return "";
}

void give_it_back(object what, object from)
{
	 if(!command("give "+what->query_name()+" to "
			 +from->query_real_name()))
		  command("drop "+what->query_name());
	 return;
}

void enter_inv(object what, object from)
{
    ::enter_inv(what, from);

    if (!interactive(from))
        return;
   
    if (!what->id("hat"))
    {
        set_alarm(1.4, 0.0, &command("say Thanks, but I don't know "
            +"what I would do with a "+what->query_name()+"."));
        set_alarm(2.5, 0.0, &give_it_back(what, from));
        return;
    }

    if (query_armour(A_HEAD))
    {
        set_alarm(1.4, 0.0, &command("say Thanks a lot, but I already "
           +"have a hat!"));
        set_alarm(3.4, 0.0, &give_it_back(what, from));
        return;
    }

    if (from->test_bit("Avenir",GROUP,BIT))
    {
        set_alarm(1.4, 0.0, &command("say You brought me a hat again! "
            +"That was so sweet!"));
        set_alarm(3.4, 0.0, &command("wear hat"));
        return;
    }

    if (!what->id("_heboba_hat_from_avenir"))
    {
        set_alarm(1.4, 0.0, &command("say Oh, its very lovely ... "
           +"but I really wanted one that was made by Heboba."));
        set_alarm(3.4, 0.0, &give_it_back(what, from));
        return;
    }

    if (member_array(mytype, what->query_names()) == -1)
    {
        set_alarm(1.4, 0.0, &command("say My oh my ... this just "
            +"won't do..."));
        set_alarm(2.4, 0.0, &command("say Didn't I tell you that I "
            +"wanted a "+mytype+"?"));
        set_alarm(3.4, 0.0, &give_it_back(what, from));
        return;
    }

    if (member_array(mycolor, what->query_adjs()) == -1)
    {
        set_alarm(1.4, 0.0, &command("say Oh dear, oh dear ... this "
           +"just isn't my color I'm afraid."));
        set_alarm(2.4, 0.0, &command("say "+CAP(mycolor)+" really "
           +"suits me better."));
        set_alarm(3.4, 0.0, &give_it_back(what, from));
        return;
    }

    if (member_array(mystyle, what->query_adjs()) == -1)
    {
        set_alarm(1.4, 0.0, &command("say Oh dear, oh dear ... this "
           +"is just not the right style. I had wanted something a "
           +"bit more "+mystyle+"."));
        set_alarm(3.4, 0.0, &give_it_back(what, from));
        return;
    }

    if (member_array(mymat, what->query_adjs()) == -1)
    {
        set_alarm(1.4, 0.0, &command("frown"));
        set_alarm(2.4, 0.0, &command("say Didn't I mention it? I had "
            +"really wanted something made from "+mymat+"..."));
        set_alarm(3.4, 0.0, &give_it_back(what, from));
        return;
    }
 
    busy(15);

    set_alarm(2.0, 0.0, &command("say Oh, you brought me a "+mytype+"!"));
    set_alarm(4.0, 0.0, &command("say And you got it in "+mycolor+" even!"));
    set_alarm(7.0, 0.0, &command("emote runs her fingers along the "+mymat+" of the "
          +what->short()+" and smiles dreamily."));
    set_alarm(9.0, 0.0, &command("say And it is so "+mystyle+" that it will look "
          +"great on me!"));
    set_alarm(11.0, 0.0, &command("wear hat"));
    set_alarm(12.0, 0.0, &command("cheer happ"));
    set_alarm(14.0, 0.0, &command("hug "+from->query_real_name()));
    set_alarm(14.1, 0.0, &reward(from));

    return;
}

void reward(object player)
{
    if (!present(player, ENV(TO)))
        return;

    if (reward_quest("Bakona's Hat", player, GROUP, BIT, EXP, ALIGN, PRESTIGE))
        WRITE_THIS_LOG(QUEST_FILE, player->query_name()
                      +" brought the hat to Bakona: "+EXP+" xp.\n" );
    return;
}

