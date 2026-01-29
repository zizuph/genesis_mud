
inherit "/std/monster.c";

#include "/d/Shire/common/defs.h"
#include <ss_types.h>
//By Dunstable, from the wise monk in the monk guild of Roke

#define h_nam(x) (member_array(x,what->query_names())>-1)

#define HONEY 1
#define MUSTARD 2
#define BOWL 4
#define SPOON 8
#define SAUSAGE 16
#define PAN 32
#define CLOTH 64
#define CLOVE 128
#define SAVORY 256
#define THYME 512
#define MINT 1024
#define CHERVIL 2048
#define DONE (HONEY|MUSTARD|BOWL|SPOON|SAUSAGE|PAN|CLOTH|CLOVE|SAVORY|THYME|MINT|CHERVIL)

//   Protoypes
void re_intro();
void cookit(object player);
void give_it(object player);
void introduce_me();
void thank_chat(object *ob_list);

string *visitors;
int *bitm;
int not_intro, intro_id, re_intro_id;

void
create_monster()
{

    set_name("bedelia");
    set_title("Underhill, Chief Cook and Bottle Washer of the Pipe and Fork");
    add_name(({"cook","woman"}));
    set_adj(({"tall","busy"}));
    set_race_name("hobbit");
    set_gender(1);
    set_long("This tired busy hobbit is looking around for her things.  Perhaps "+
      "you could help her find them?\n");

    MAKE_MONEY;
    default_config_npc(45);
    set_alignment(200);

    seteuid(getuid(TO));


    visitors = ({});
    bitm = ({});

    add_ask(({"help","job","task","quest"}),VBFC_ME("ask_help"));
    add_ask(({"pie","pies","bumbleberry pie"}),VBFC_ME("ask_pie"));
    set_default_answer("I don't know what you are talking about.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_HERBALISM,100);
    restore_object(MICH_DIR + "visitors");
}

string
ask_help()
{
    command("say I don't need much help, I guess I'm ok for now.");
    command("say Thank you for asking though.");
    command("say You might see the Mayor, he'd know more than me.");
    return "";
}

string
ask_pie()
{
    command("say I bake bumbleberry pies, and they are wonderful!");
    return "";
}

int
add_introduced(string str)
{
    if (not_intro)  
	return 1;
    if (intro_id)
    {   
	if (ftoi(get_alarm(intro_id)[2]) != 0)
	{
	    intro_id = set_alarm(4.0,0.0,&introduce_me());
	}
    }
    return 1;
}

void
introduce_me()
{
    command("introduce myself");
    not_intro = 1;
    if (re_intro_id)
    {
	if (ftoi(get_alarm(re_intro_id)[2]) != 0)
	{
	    re_intro_id = set_alarm(15.0,0.0,&re_intro());
	}  
    }
}

void
re_intro()
{
    not_intro = 0;
}


void
enter_inv(object what, object from)
{
    int ran;
    object *ob_list = ({ what, from });

    ::enter_inv(what, from);

    if (!from) /* Perhaps it was cloned and moved to me... */
	return;
    ran = 1 + random(10);
    set_alarm(itof(random(8)), 0.0, &thank_chat(ob_list));
    //call_out("thank_chat", 1+random(10), ({ from, what }));
    // WE dont use call_outs anymore!
}


thank_chat(object *foo)
{
    object from,what;
    int index;
    int temp;

    what = foo[0];
    from = foo[1];


    if (!objectp(what))
	return;

    if(h_nam("_shire_mixing_spoon_"))
    {
	if(!from->query_prop("_i_got_the_mixing_spoon_"))
	{
	    set_alarm(2.0,0.0, &command("say I don't want that, it looks stolen!"));
	    set_alarm(5.0,0.0, &command("emote breaks the spoon in half."));
	    //call_out("command",2,"say I don't want that, it looks stolen!");
	    //call_out("command",5,"emote breaks the spoon in half.");
	    what->remove_object();
	    return;
	}
    }

    if (member_array("_shire_pieplate_",what->query_names()) != -1)
    {
	command("smile");
	set_alarm(2.0,0.0, &command("say You want me to make a pie?"));
	set_alarm(5.0,0.0, &command("say Ok, but I'll need ingredients..."));
	set_alarm(7.0,0.0, &command("say I need a mixing bowl..."));
	set_alarm(10.0,0.0, &command("say and a pack of mustard seeds..."));
	set_alarm(13.0,0.0, &command("say I need also a bottle of honey..."));
	set_alarm(15.0,0.0, &command("say a spoon, a pan, a sausage...a cloth..."));
	set_alarm(20.0,0.0, &command("say And the herbs- clove, savory, thyme..."));
	set_alarm(25.0,0.0, &command("say mint, and chervil, yes, I'll need chervil."));
	set_alarm(32.0,0.0, &command("say We have recently moved and all of "+
	    "my things are lost."));
	set_alarm(35.0,0.0, &command("sigh"));
	/*      call_out("command",2,"say You want me to make a pie?");
	call_out("command",5,"say Ok, but I'll need ingredients...");
	call_out("command",7,"say I need a mixing bowl...");
	call_out("command",10,"say and a pack of mustard seeds...");
	call_out("command",13,"say I need also a bottle of honey...");
	call_out("command",15,"say a spoon, a pan, a sausage...a cloth...");
	call_out("command",20,"say And the herbs- clove, savory, thyme...");
	call_out("command",25,"say mint, and chervil, yes, I'll need chervil.");
	call_out("command",32,"say We have recently moved and all of my ");
	call_out("command",35,"say things are lost.");
	call_out("command",40,"sigh");
	*/
	set_this_player(from);

	if(member_array(TP->query_real_name(),visitors)<0)
	{
	    visitors += ({TP->query_real_name()});
	    bitm += ({0});
	}
	what->remove_object();

	index = member_array(TP->query_real_name(),visitors);
	if(bitm[index] == DONE)
	{
	    set_alarm(40.0,0.0,&command("think"));
	    set_alarm(45.0,0.0,&command("say Hmmm seems you've already given me "+
		"everything...  so I guess I will make that pie for you now."));
	    set_alarm(47.0,0.0,&cookit(from));
	}
	save_object(MICH_DIR +"visitors");
	return 1;
    }

    index = member_array(TP->query_real_name(),visitors);

    if(index < 0)
    {
	command("say What am I supposed to do with this?");
	command("say You can't ask me to cook something for you without a pan!");
	command("drop all");
	return 1;
    }

    temp = bitm[index];

    if(h_nam("_shire_honey_"))
	bitm[index] = bitm[index] | HONEY;
    if(h_nam("_shire_mustard_"))
	bitm[index] = bitm[index] | MUSTARD;
    if(h_nam("_shire_mixing_bowl_"))
	bitm[index] = bitm[index] | BOWL;
    if(h_nam("_shire_mixing_spoon_"))
	bitm[index] = bitm[index] | SPOON;
    if(h_nam("_shire_sausage_"))
	bitm[index] = bitm[index] | SAUSAGE;
    if(h_nam("_shire_baking_pan_"))
	bitm[index] = bitm[index] | PAN;
    if(h_nam("_shire_cloth_"))
	bitm[index] = bitm[index] | CLOTH;
    if(what->query_herb_name() == "clove")
	bitm[index] = bitm[index] | CLOVE;
    if(what->query_herb_name() =="savory")
	bitm[index] = bitm[index] | SAVORY;
    if(what->query_herb_name() == "thyme")
	bitm[index] = bitm[index] | THYME;
    if(what->query_herb_name() == "mint")
	bitm[index] = bitm[index] | MINT;
    if(what->query_herb_name() == "chervil")
	bitm[index] = bitm[index] | CHERVIL;

    if (bitm[index] == temp)
    {
	command("say I don't want this!");
	command("drop all");
	return;
    }

    if(bitm[index] == DONE)
	set_alarm(1.0,0.0,&cookit(from));

    command("say I will start making the pie.");

    what->remove_object();
    save_object(MICH_DIR + "visitors");
}

void
cookit(object player)
{
    set_alarm(5.0,0.0, "tap");
    set_alarm(10.0,0.0, "emote opens the stove and "+
      "pulls out a hot pie!\n");
    set_alarm(15.0,0.0,&give_it(player));
    /*  call_out("command",5,"tap");
    call_out("command",10,"emote opens the stove and pulls out a hot pie!\n");
    call_out("giveit",15);*/
}

void
give_it(object player)
{
    int index;
    object pie;

    set_this_player(player);
    pie =  clone_object(MICH_DIR + "obj/bumbleberry_pie");
    pie->move(TP,1);
    TP->add_prop("_had_the_pie_cooked_",1);

    command("say Here's your pie!");
    TP->catch_msg(QCTNAME(TO) + " gives you a pie.\n");
    say(QCTNAME(TO) + " gives "+QTNAME(TP)+" a pie.\n");
    command("smile joy");

    index = member_array(TP->query_real_name(),visitors);

    visitors = exclude_array(visitors,index,index);
    bitm = exclude_array(bitm,index,index);

    save_object(MICH_DIR + "visitors");
}
