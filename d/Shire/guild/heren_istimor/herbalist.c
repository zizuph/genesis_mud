#pragma strict_types
#pragma save_binary

#include "/d/Shire/common/defs.h"
#include "/d/Shire/guild/heren_istimor/heren_istimor.h"

inherit "/d/Shire/lib/herbalist.c";
inherit "/d/Shire/std/monster.c";

#define HERB_SAVE  HEREN_ISTIMOR_DIR + "herb_save"
#define BAG_PROP  "_heren_istimor_bought_herb_bag"

void
create_shire_monster()
{
    if (!IS_CLONE)
    return;

    set_name("gilestel");
    add_name("herbalist");
    set_race_name("elf");
    set_living_name("gilestel");
    set_title("the Herbalist of the Heren Istimor");
    set_adj("curious");
    add_adj("smiling");
    set_long("@@long_func");
    set_stats(({ 55, 55, 60, 99, 98, 55 }));
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT,63000);
    add_prop(CONT_I_HEIGHT,174);
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");

    set_skill(SS_HERBALISM,96);
    set_skill(SS_UNARM_COMBAT,65);
    set_skill(SS_DEFENCE,52);

    set_chat_time(7);
    add_chat("I am Gilestel, the Herbalist!");
    add_chat("You would not have any unknown herbs, would you?");
    add_chat("You know the old saying: There is an herb for every occasion.");
    add_chat("I think I have seen most herbs in the world by now.");
    add_chat("If you have an unknown herb, you can let me identify it for you.");
    add_chat("I still have not discovered the virtues of kingsfoil.");
    add_chat("You never know when a herb might come in handy.");
    add_chat("I've heard that the rangers have books on herbs in their library.");
    add_chat("I lived most of my life in Beleriand, before the Sundering.");
    add_chat("Too bad that there is no book where to find which herbs in the Shire!");
    add_chat("If you ask me, I can tell you about herbs and lore.");

    set_act_time(4);
    add_act("@@announce_selling");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));

    set_introduce(1);
    add_equipment(HEREN_ISTIMOR_GUILD_OBJ);

    set_herbalist_id_herbs();
    set_max_herbs_kept(1000);
    configure_herbalist(HERB_SAVE);
}

void
init_living()
{
    init_herbalist();
    ::init_living();
}

void
enter_inv(object herb, object from)
{
    ::enter_inv(herb, from);
    init_herbalist_identify(herb,from);
}

string
announce_selling()
{
    if (query_herb_list_size())
    command("say I have herbs for sale too, would you like some?");
    else command("say I should go and search for more herbs.");
    return "";
}

string
long_func()
{
    string long_str;
    long_str = "This is Gilestel, the Herbalist for Heren Istimor. He keeps a great "+
    "store of herbs and can identify almost any herb for you.  He will both buy "+
    "and sell herbs in addition to identifying them for you.";
    if (TP->query_wiz_level())
    return break_string(long_str+" Type 'stat herbalist' for more info.\n",75);
    return break_string(long_str+"\n",75);
}

string
wizinfo()
{
    string str;

    str = "This Herbalist stores up to "+query_herbs_max_kept()+
    " herbs of same type at one time.\n\n";

    if (!query_herb_list_size())
    {
    str += "The herbalist has no herbs for sale now.\n";
    return str;
    }
    str += "The herbalist has these herbs for sale:\n";
    str += query_herb_list();
    str +="-Lord Igneous-\n";
    TP->more(str);
    return "";
}



int
purchase_bag()
{
    object bag;

    if (TP->query_prop(BAG_PROP))
    {
    command("say I have given you a herb bag already.");
    command("say Please do not be greedy.");
    return 1;
    }

    setuid(); seteuid(getuid());
    bag = clone_object(HEREN_ISTIMOR_DIR + "herbbag");
    bag->move(TO);
    tell_room(environment(),"The herbalist draws a bag from his pocket.\n");
    command("say I cannot take money for that, "+
      ((TP->query_gender() == G_MALE) ? "sir" : "mylady")+"!");
      bag->move(TP);
    write("The herbalist gives you a herb bag.\n");


/*
if (!command("give "+bag->query_name()+" to "+TP->query_real_name()))
    {
    command("hmm");
    command("say I wonder where that "+TP->query_race_name()+" took off to?");
    command("say I'll have to keep this bag for myself then.");
    }
    else
*/

    TP->add_prop(BAG_PROP,1);
    return 1;
}


int
do_buy(string str)
{
    str = lower_case(str);


    if(str == "herbbag" || str == "herb-bag" || str == "bag")
    {
    purchase_bag();
    return 1;
    }
    return ::do_buy(str);
}


string
ask_herbs()
{
    command("say Herbs?");
    command("say Well, I know most of them!");
    command("say You can buy some from me, and I sell herbs, too!");
    command("say If you have an unknown herb, I can try to identify");
    command("say it for you, if you give it to me.");
    command("say If you want to learn about herblore, ask me about it.");
    return "";
}

string
ask_lore()
{
    command("say Herb lore?");
    command("say Well, there are only few who know as much about herbs as I do!");
    command("say But even I do not know all the places where herbs grow!");
    command("say You might check in the library here.");
    command("say But the books there are ancient.");
    return "";
}

string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}
